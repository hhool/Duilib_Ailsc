#include "stdafx.h"
#include "ImgCache.h"
#include "StringUtil.h"
#include "Md5Util.h"
#include <Shlwapi.h>
#include <direct.h>
#include <io.h>
/*
缓存url文件，支持并发数量3线程
缓存文件默认保存在当前目录icons目录
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

	//开启三个线程同时下载
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
	//设置之前必须初始化m_download_file
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
		//重试
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

		//如果已经缓存中则直接返回
		if (data->status == eimg_cache_status_ing)
		{
			return 1;
		}

		//检查缓存是否存在,如果存在则直接返回
		if (_access(data->file_path.c_str(), 00) == 0)
		{
			data->status = eimg_cache_status_ok;
			return 0;
		}

		//标记为缓存中
		data->status = eimg_cache_status_ing;
		temp_try_count = ++data->try_count;
	}


	//如果缓存不存在则下载文件,下载完成之后标记状态为完成不管成功和失败
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