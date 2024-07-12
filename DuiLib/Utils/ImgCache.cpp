#include "stdafx.h"
#include "ImgCache.h"
#include "StringUtil.h"
#include "Md5Util.h"
#include <Shlwapi.h>
#include <direct.h>
#include <io.h>
/*
����url�ļ���֧�ֲ�������3�߳�
�����ļ�Ĭ�ϱ����ڵ�ǰĿ¼iconsĿ¼
*/
namespace DuiLib
{
static const int MAX_TRY = 5;
PDuiDownloadFile CImgCache::m_download_file = nullptr;
CImgCache::CImgCache()
{
	char szFile[2048] = "";
	GetModuleFileNameA(NULL, szFile, 2048);
	PathRemoveFileSpecA(szFile);
	PathAppendA(szFile, "icons");
	m_files_dir = szFile;
	_mkdir(m_files_dir.c_str());

	//���������߳�ͬʱ����
	for (int i = 0;i < 3;++i)
	{
		std::thread t(&CImgCache::_work, this);
		t.detach();
	}
}

CImgCache& CImgCache::instance()
{
	static CImgCache _instance;
	return _instance;
}

//only call once,please set in init,not thread safe
void CImgCache::SetDownloadFileHandler(PDuiDownloadFile download_file)
{
	_ASSERT(m_download_file == nullptr);
	m_download_file = download_file;
}

void CImgCache::addUrl(const std::string& url)
{
	//����֮ǰ�����ʼ��m_download_file
	_ASSERT(m_download_file != nullptr);
	if (m_download_file == nullptr || url.empty()) return;
	m_task_que.add(url);
}

void CImgCache::_work()
{
	std::string url = m_task_que.get();
	if (!url.empty())
	{
		int nret = syncDoCache(url.c_str(), getFileFullPath(url.c_str()));
		//����
		if (nret == -1)
		{
			addUrl(url);
		}
	}
}

std::string CImgCache::getFileFullPath(const char* url)
{
	std::string url_md5 = Md5Util::GetStringMd5(StringUtil::Easy_AnsiToUtf8(url));
	std::string file_name = url_md5 + ".png";

	char szPath[MAX_PATH];
	_snprintf_s(szPath, MAX_PATH, "%s", m_files_dir.c_str());
	PathAppendA(szPath, file_name.c_str());
	return szPath;
}

int CImgCache::getUrlStatus(const char* url)
{
	std::lock_guard<std::mutex> lk(m_mtx);
	std::string url_md5 = Md5Util::GetStringMd5(StringUtil::Easy_AnsiToUtf8(url));
	if (m_map_url_data.count(url_md5))
	{
		auto& data = m_map_url_data[url_md5];
		return data->status;
	}
	return -1;
}

int CImgCache::syncDoCache(const char* url, __out std::string& file_path)
{
	if (url == nullptr)
	{
		return -2;
	}
	std::string url_md5 = Md5Util::GetStringMd5(StringUtil::Easy_AnsiToUtf8(url));
	std::string file_name = url_md5 + ".png";
	int temp_try_count = 0;
	char szPath[MAX_PATH];
	_snprintf_s(szPath, MAX_PATH, "%s", m_files_dir.c_str());
	PathAppendA(szPath, file_name.c_str());
	file_path = szPath;

	{
		std::lock_guard<std::mutex> lk(m_mtx);
		if (m_map_url_data.count(url_md5) <= 0)
		{
			m_map_url_data[url_md5] = std::make_shared<ImgCacheData>();
		}
		auto data = m_map_url_data[url_md5];
		data->file_path = file_path;
		data->img_ur = url;
		if (data->try_count >= MAX_TRY)
		{
			data->status = eimg_cache_status_failed;
			return 2;
		}

		//����Ѿ���������ֱ�ӷ���
		if (data->status == eimg_cache_status_ing)
		{
			return 1;
		}

		//��黺���Ƿ����,���������ֱ�ӷ���
		if (_access(data->file_path.c_str(), 00) == 0)
		{
			data->status = eimg_cache_status_ok;
			return 0;
		}

		//���Ϊ������
		data->status = eimg_cache_status_ing;
		temp_try_count = ++data->try_count;
	}


	//������治�����������ļ�,�������֮����״̬Ϊ��ɲ��ܳɹ���ʧ��
	bool bret = m_download_file ? m_download_file(url, file_path.c_str()) : false;
	//(requests::downloadFile(url, file_path.c_str()) > 0);
	{
		std::lock_guard<std::mutex> lk(m_mtx);
		auto data = m_map_url_data[url_md5];
		data->status = (bret ? eimg_cache_status_ok : (temp_try_count >= MAX_TRY ? eimg_cache_status_failed : eimg_cache_status_temp_failed));
		::PostMessage(HWND_BROADCAST, UM_URL_IMAGE_UPDATE, bret, (LPARAM)data->img_ur.c_str());
	}
	return (bret ? 0 : -1);
}
};