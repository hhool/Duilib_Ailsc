#pragma once
/*
miniblink 控件
如果外部需要使用wke相关函数需要初始化mb INIT_MB
js默认支持window.CallDuiMsg 方法，
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
		//用于独立窗口
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
		virtual void Delete();

		//web 常用事件,这里仅仅封装常用的web事件，更多可参考wek.h 
		//如果在其他模块(exe)调用wke函数需要初始化wke INIT_MB
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
		//cookie设置
		void SetCookieEnabled(bool enable);
		bool IsCookieEnabled() const;
		const wchar_t* GetCookie();
		//cookie格式必须是类似:cna=4UvTFE12fEECAXFKf4SFW5eo; expires=Tue, 23-Jan-2029 13:17:21 GMT; path=/; domain=.youku.com
		void SetCookie(const char* utf8_url, const char* utf_8_cookie);
		void SetCookieJarPath(const WCHAR* path);
		void SetCookieJarFullPath(const WCHAR* path);
		void ClearCookie();

		//
		void SetLocalStorageFullPath(const WCHAR* path);
		void AddPluginDirectory(const WCHAR* path);
		//c++ js 交互
		//调用js
		jsValue CallJs(const char* funcname, jsValue* params, int params_count);
		static jsValue CallJs(jsExecState es, const char* funcname, jsValue* params, int params_count);
		//注册默认可供js调用的函数,js可直接调用DuiCallMsg传递参数
		static friend jsValue WKE_CALL_TYPE CallDuiMsg(jsExecState es, void* param);
		//参数获取
		static int JsArgCount(jsExecState es);
		static jsType JsArgType(jsExecState es, int argIdx);
		static jsValue JsArg(jsExecState es, int argIdx);
		//js 和 C++ 类型转换
		jsValue JsString(const wchar_t* val);
		static jsValue JsString(jsExecState es, const wchar_t* val);
		static jsValue JsNull();
		static jsValue JsUndefined();
		static jsValue JsBool(bool b);
		static jsValue JsDouble(double ival);
		static jsValue JsFloat(float ival);
		static jsValue JsInt(int ival);
		static bool JsIsNumber(jsValue v);
		static bool JsIsString(jsValue v);
		static bool JsIsBoolean(jsValue v);
		static bool JsIsObject(jsValue v);
		static bool JsIsFunction(jsValue v);
		static bool JsIsUndefined(jsValue v);
		static bool JsIsNull(jsValue v);
		static bool JsIsArray(jsValue v);
		static bool JsIsTrue(jsValue v);
		static bool JsIsFalse(jsValue v);

		static int JsToInt(jsExecState es, jsValue v);
		static float JsToFloat(jsExecState es, jsValue v);
		static double JsToDouble(jsExecState es, jsValue v);
		static const char* JsToDoubleString(jsExecState es, jsValue v);
		static BOOL JsToBoolean(jsExecState es, jsValue v);
		static jsValue JsArrayBuffer(jsExecState es, const char* buffer, size_t size);
		static wkeMemBuf* JsGetArrayBuffer(jsExecState es, jsValue value);
		static const utf8* JsToTempString(jsExecState es, jsValue v);
		static const wchar_t* JsToTempStringW(jsExecState es, jsValue v);

	protected:
		void InitWebEventHandle();
		//web常用监听事件
		static friend void WKE_CALL_TYPE onDidCreateScriptContextCallback(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int extensionGroup, int worldId);
		static friend void WKE_CALL_TYPE handleTitleChanged(wkeWebView webWindow, void* param, const wkeString title);
		static friend void WKE_CALL_TYPE handleDocumentReady(wkeWebView webWindow, void* param);
		static friend void WKE_CALL_TYPE handleWindowDestroy(wkeWebView webWindow, void* param);
		static friend bool WKE_CALL_TYPE handleWindowClosing(wkeWebView webWindow, void* param);
		static friend wkeWebView WKE_CALL_TYPE onCreateView(wkeWebView webWindow, void* param, wkeNavigationType navType, const wkeString url, const wkeWindowFeatures* features);
		static friend bool WKE_CALL_TYPE onLoadUrlBegin(wkeWebView webView, void* param, const char* url, void* job);
		static friend void WKE_CALL_TYPE onLoadingFinish(wkeWebView webView, void* param, const wkeString url, wkeLoadingResult result, const wkeString failedReason);
		static friend void WKE_CALL_TYPE onLoadUrlFail(wkeWebView webView, void* param, const utf8* url, wkeNetJob job);
	protected:
		void DoInit();
		
	private:
		wkeWebView m_webView;
		IMBWenviewEvent *m_pIWebEvent;
		std::wstring m_sHomePage;	// 默认页面
		static bool m_bInit;
	};
}


