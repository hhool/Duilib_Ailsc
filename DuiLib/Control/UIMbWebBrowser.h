#pragma once
/*
miniblink �ؼ�
����ⲿ��Ҫʹ��wke��غ�����Ҫ��ʼ��mb INIT_MB
jsĬ��֧��window.CallDuiMsg ������
*/
namespace DuiLib
{
#define INIT_MB()\
	{\
	wkeSetWkeDllPath(L".//node.dll");\
	wkeInitialize(); }\

	class CMbWebBrowserUI;
	class IMBWenviewEvent
	{
	public:
		virtual void onDidCreateScriptContextCallback(wkeWebView webView, CMbWebBrowserUI* pwebBrowser, wkeWebFrameHandle frameId, void* context, int extensionGroup, int worldId){}
		virtual bool handleTitleChanged(wkeWebView webWindow, CMbWebBrowserUI* pwebBrowser, const wchar_t* title){ return false; }
		virtual void handleDocumentReady(wkeWebView webWindow, CMbWebBrowserUI* pwebBrowser){}
		virtual void handleWindowDestroy(wkeWebView webWindow, CMbWebBrowserUI* pwebBrowser){}
		virtual bool handleWindowClosing(wkeWebView webWindow, CMbWebBrowserUI* pwebBrowser){ return true; }
		virtual wkeWebView onCreateView(wkeWebView webWindow, CMbWebBrowserUI* pwebBrowser, wkeNavigationType navType, const wchar_t* url, const wkeWindowFeatures* features){ return nullptr; }
		virtual void onLoadUrlEnd(wkeWebView webView, CMbWebBrowserUI* pwebBrowser, const wchar_t* url, void* job, void* buf, int len){}
		virtual bool onLoadUrlBegin(wkeWebView webView, CMbWebBrowserUI* pwebBrowser, const wchar_t* url, void* job){ return false; }
		virtual void onLoadingFinish(wkeWebView webView, CMbWebBrowserUI* pwebBrowser, const wchar_t* url, wkeLoadingResult result, const wkeString failedReason){}
		virtual void onLoadUrlFail(wkeWebView webView, CMbWebBrowserUI* pwebBrowser, const wchar_t* url, wkeNetJob job){}
		virtual jsValue OnJsCallDuiMsg(CMbWebBrowserUI * pwebBrowser, jsExecState es){ return 0; }
	};

	class DUILIB_API CMbWebBrowserUI:
		public CWinWndUI
	{
	public:
		CMbWebBrowserUI();
		//���ڶ�������
		CMbWebBrowserUI(wkeWebView m_webView);
		~CMbWebBrowserUI();
		static bool InitMb();
		static wkeWebView CreateWebWindow(wkeWindowType type, HWND parent, int x, int y, int width, int height);
		static wkeWebView CreateWebCustomWindow(const wkeWindowCreateInfo* info);
		virtual LPCTSTR GetClass() const;
		virtual LPVOID GetInterface(LPCTSTR pstrName);
		void SetPos(RECT rc, bool bNeedInvalidate);
		void Move(SIZE szOffset, bool bNeedInvalidate);
		void SetInternVisible(bool bVisible);
		void SetVisible(bool bVisible);
		void RegisterWebEvent(IMBWenviewEvent *pIwebEvnet);
		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		

		//web �����¼�,���������װ���õ�web�¼�������ɲο�wek.h 
		//���������ģ��(exe)����wke������Ҫ��ʼ��wke INIT_MB
		wkeWebView GetWebView();
		HWND GetwkeWindowHandle();
		void SetHomePage(LPCWSTR lpszUrl);
		LPCWSTR GetHomePage();
		void LoadUrl(LPCWSTR lpszUrl);
		void Refresh();
		void SetTitle(LPCWSTR lpszUrl);
		void ShowDevTool();
		bool CanGoBack() const;
		bool GoBack();
		bool CanGoForward() const;
		bool GoForward();
		void SetCookieEnabled(bool enable);
		bool IsCookieEnabled() const;

		//c++ js ����
		//����js
		jsValue CallJs(const char* funcname, jsValue* params, int params_count);
		static jsValue CallJs(jsExecState es, const char* funcname, jsValue* params, int params_count);
		//ע��Ĭ�Ͽɹ�js���õĺ���,js��ֱ�ӵ���DuiCallMsg���ݲ���
		static friend jsValue WKE_CALL_TYPE CallDuiMsg(jsExecState es, void* param);
	protected:
		
		void InitWebEventHandle();
		//web���ü����¼�
		static friend void WKE_CALL_TYPE onDidCreateScriptContextCallback(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int extensionGroup, int worldId);
		static friend void WKE_CALL_TYPE handleTitleChanged(wkeWebView webWindow, void* param, const wkeString title);
		static friend void WKE_CALL_TYPE handleDocumentReady(wkeWebView webWindow, void* param);
		static friend void WKE_CALL_TYPE handleWindowDestroy(wkeWebView webWindow, void* param);
		static friend bool WKE_CALL_TYPE handleWindowClosing(wkeWebView webWindow, void* param);
		static friend wkeWebView WKE_CALL_TYPE onCreateView(wkeWebView webWindow, void* param, wkeNavigationType navType, const wkeString url, const wkeWindowFeatures* features);
		static friend void WKE_CALL_TYPE onLoadUrlEnd(wkeWebView webView, void* param, const char* url, void* job, void* buf, int len);
		static friend bool WKE_CALL_TYPE onLoadUrlBegin(wkeWebView webView, void* param, const char* url, void* job);
		static friend void WKE_CALL_TYPE onLoadingFinish(wkeWebView webView, void* param, const wkeString url, wkeLoadingResult result, const wkeString failedReason);
		static friend void WKE_CALL_TYPE onLoadUrlFail(wkeWebView webView, void* param, const utf8* url, wkeNetJob job);
	protected:
		bool DoCreateControl();
		
	private:
		wkeWebView m_webView;
		IMBWenviewEvent *m_pIWebEvent;
		std::wstring m_sHomePage;	// Ĭ��ҳ��
		static bool m_bInit;
	};
}


