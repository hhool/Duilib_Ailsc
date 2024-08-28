#pragma once
#include <string>
#include <map>
#include <functional>
#include <mutex>
#include <set>
#include <queue>
#include <condition_variable>
#include "Core/UIManager.h"
/*
not check md5,just check_file is exist
*/
namespace DuiLib
{
	class TaskQue
	{
	public:
		void add(const std::string &url)
		{
			{
				std::unique_lock<std::mutex> lk(m_mtx);
				if (m_urls.count(url)) return;
				m_que_urls.push(url);
				m_urls.insert(m_urls.begin(), url);
			}
			m_cond.notify_one();
		}
		std::string get(int milliseconds = 1000)
		{
			std::unique_lock<std::mutex> lk(m_mtx);
			if (m_cond.wait_for(lk, std::chrono::milliseconds(milliseconds), [this]() {return !m_que_urls.empty(); }))
			{
				std::string url = m_que_urls.front();
				m_que_urls.pop();
				m_urls.erase(url);
				return url;
			}
			return "";
		}

	private:
		std::mutex m_mtx;
		std::condition_variable m_cond;
		std::set<std::string> m_urls;
		std::queue<std::string> m_que_urls;
	};

	class CImgCache
	{
		enum ImgCacheStatus
		{
			eimg_cache_status_ing,
			eimg_cache_status_ok,
			eimg_cache_status_temp_failed,
			eimg_cache_status_failed,
		};

		typedef struct ImgCacheData
		{
			std::string file_path;
			std::string img_ur;
			ImgCacheStatus status;
			int try_count;

			ImgCacheData()
			{
				try_count = 0;
				status = eimg_cache_status_ok;
			}
		}ImgCacheData;
	public:
		static CImgCache& instance();
		static void SetDownloadFileHandler(PDuiDownloadFile download_file);
		void addUrl(const std::string& url);
		int getUrlStatus(const char* url);
		std::string getFileFullPath(const char* url);
	protected:
		CImgCache();
		
		//complete
		//void complete(int err_code,file_name,void *ptr)
		//0-OK -1-download failed,-2-param invalid ,1-cache ing 2-下载失败，不在尝试
		int syncDoCache(const char* url, __out std::string& file_path);

		void _work();
	private:
		std::map<std::string, std::shared_ptr<ImgCacheData> > m_map_url_data;
		std::mutex m_mtx;
		std::string m_files_dir;
		TaskQue m_task_que;
		static PDuiDownloadFile m_download_file;
	};
};
