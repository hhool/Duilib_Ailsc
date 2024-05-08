#include "stdafx.h"
#include "UIMbWebBrowser.h"
#include "../Utils/StringUtil.h"
#include <Shlwapi.h>

namespace DuiLib
{
	bool CMbWebBrowserUI::m_bInit = false;

	CMbWebBrowserUI::CMbWebBrowserUI()
	{
		m_sHomePage = L"";
		m_webView = NULL;
		m_pIWebEvent = NULL;
		InitMb();
	}

	CMbWebBrowserUI::CMbWebBrowserUI(wkeWebView webView)
	{
		m_sHomePage = L"";
		m_pIWebEvent = NULL;
		m_webView = webView;
		InitMb();
		InitWebEventHandle();
		Attach(wkeGetWindowHandle(m_webView));
	}

	CMbWebBrowserUI::~CMbWebBrowserUI()
	{

	}

	LPCTSTR CMbWebBrowserUI::GetClass() const
	{
		return DUI_CTR_MBWEBBROWSER;
	}

	LPVOID CMbWebBrowserUI::GetInterface(LPCTSTR pstrName)
	{
		if (lstrcmp(pstrName, DUI_CTR_MBWEBBROWSER) == 0) return this;
		return __super::GetInterface(pstrName);
	}

	void CMbWebBrowserUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		__super::SetAttribute(pstrName, pstrValue);
		if (_tcscmp(pstrName, _T("homepage")) == 0)
		{
#ifdef _UNICODE
			SetHomePage(pstrValue);
#else
			SetHomePage(StringUtil::Easy_AnsiToUnicode(pstrValue).c_str());
#endif
		}

	}

	void CMbWebBrowserUI::Delete()
	{
		if (m_hWnd && m_bDieWithControl && IsWindow(m_hWnd))
		{
			::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
			Detach();
		}
	}
	void CMbWebBrowserUI::SetHomePage(LPCWSTR lpszUrl)
	{
		m_sHomePage = lpszUrl;
		LoadUrl(lpszUrl);
	}

	LPCWSTR CMbWebBrowserUI::GetHomePage()
	{
		return m_sHomePage.c_str();
	}

	void CMbWebBrowserUI::RegisterWebEvent(IMBWenviewEvent *pIwebEvnet)
	{
		m_pIWebEvent = pIwebEvnet;
	}

	void CMbWebBrowserUI::SetVisible(bool bVisible)
	{
		__super::SetVisible(bVisible);
		SetInternVisible(bVisible);
	}

	void CMbWebBrowserUI::SetInternVisible(bool bVisible)
	{
		__super::SetInternVisible(bVisible);
		::ShowWindow(m_hWnd, bVisible);
	}

	void CMbWebBrowserUI::Move(SIZE szOffset, bool bNeedInvalidate)
	{
		__super::Move(szOffset, bNeedInvalidate);
		RECT rc = GetPos();
		::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
	}

	void CMbWebBrowserUI::SetPos(RECT rc, bool bNeedInvalidate)
	{
		__super::SetPos(rc);
		::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
	}

	void CMbWebBrowserUI::InitWebEventHandle()
	{
		ASSERT(m_webView);
		wkeOnDidCreateScriptContext(m_webView, onDidCreateScriptContextCallback, this);
		wkeOnWindowClosing(m_webView, handleWindowClosing, this);
		wkeOnWindowDestroy(m_webView, handleWindowDestroy, this);
		wkeOnDocumentReady(m_webView, handleDocumentReady, this);
		wkeOnTitleChanged(m_webView, handleTitleChanged, this);
		wkeOnCreateView(m_webView, onCreateView, this);
		wkeOnLoadUrlBegin(m_webView, onLoadUrlBegin, this);
		//wkeOnLoadUrlEnd(m_webView, onLoadUrlEnd, this);
		wkeOnLoadingFinish(m_webView, onLoadingFinish, this);
		wkeOnLoadUrlFail(m_webView, onLoadUrlFail, this);
		//wkeSetDebugConfig(m_webView, "decodeUrlRequest", nullptr);
		wkeJsBindFunction("CallDuiMsg", CallDuiMsg, this, 5);
	}
	bool CMbWebBrowserUI::InitMb()
	{
		if (!m_bInit)
		{
			if (_waccess(L".//node.dll", 00) == 0)
			{
				m_bInit = true;
				INIT_MB();
				return true;
			}
			return false;
		}
		return true;
	}

	wkeWebView CMbWebBrowserUI::CreateWebWindow(wkeWindowType type, HWND parent, int x, int y, int width, int height)
	{
		InitMb();
		return wkeCreateWebWindow(type, parent, x, y, width, height);
	}

	wkeWebView CMbWebBrowserUI::CreateWebCustomWindow(const wkeWindowCreateInfo* info)
	{
		InitMb();
		return wkeCreateWebCustomWindow(info);
	}

	wkeWebView CMbWebBrowserUI::GetWebView()
	{
		return m_webView;
	}

	HWND CMbWebBrowserUI::GetwkeWindowHandle()
	{
		ASSERT(m_webView);
		return wkeGetWindowHandle(m_webView);
	}

	void CMbWebBrowserUI::LoadUrl(LPCWSTR lpszUrl)
	{
		if (m_webView)
		{
			wkeLoadURLW(m_webView, lpszUrl);
		}
	}

	void CMbWebBrowserUI::Refresh()
	{
		ASSERT(m_webView);
		wkeReload(m_webView);
	}

	bool CMbWebBrowserUI::CanGoBack() const
	{
		ASSERT(m_webView);
		return wkeCanGoBack(m_webView);
	}
	
	bool CMbWebBrowserUI::GoBack()
	{
		ASSERT(m_webView);
		return wkeGoBack(m_webView);
	}
	
	bool CMbWebBrowserUI::CanGoForward() const
	{
		ASSERT(m_webView);
		return wkeCanGoForward(m_webView);
	}
	
	bool CMbWebBrowserUI::GoForward()
	{
		ASSERT(m_webView);
		return wkeGoForward(m_webView);
	}
	
	void CMbWebBrowserUI::SetCookieEnabled(bool enable)
	{
		ASSERT(m_webView);
		wkeSetCookieEnabled(m_webView, enable);
	}
	
	bool CMbWebBrowserUI::IsCookieEnabled() const
	{
		ASSERT(m_webView);
		return wkeIsCookieEnabled(m_webView);
	}

	void CMbWebBrowserUI::SetCookie(const char* utf8_url, const char* utf_8_cookie)
	{
		ASSERT(m_webView);
		wkeSetCookie(m_webView, utf8_url, utf_8_cookie);
	}

	void CMbWebBrowserUI::SetCookieJarPath(const WCHAR* path)
	{
		ASSERT(m_webView);
		wkeSetCookieJarPath(m_webView, path);
	}

	void CMbWebBrowserUI::SetCookieJarFullPath(const WCHAR* path)
	{
		ASSERT(m_webView);
		wkeSetCookieJarFullPath(m_webView, path);
	}

	void CMbWebBrowserUI::ClearCookie()
	{
		ASSERT(m_webView);
		wkeClearCookie(m_webView);
	}

	//
	void CMbWebBrowserUI::SetLocalStorageFullPath(const WCHAR* path)
	{
		ASSERT(m_webView);
		wkeSetLocalStorageFullPath(m_webView, path);
	}

	void CMbWebBrowserUI::AddPluginDirectory(const WCHAR* path)
	{
		ASSERT(m_webView);
		wkeAddPluginDirectory(m_webView, path);
	}

	void CMbWebBrowserUI::SetTitle(LPCWSTR lpszUrl)
	{
		if (m_webView)
		{
			wkeSetWindowTitleW(m_webView, lpszUrl);
		}
	}

	void CMbWebBrowserUI::ShowDevTool()
	{
		ASSERT(m_webView);
		wchar_t szPath[MAX_PATH] = L"";
		GetModuleFileNameW(NULL, szPath, MAX_PATH);
		PathRemoveFileSpecW(szPath);
		PathAppendW(szPath, L"front_end");
		PathAppendW(szPath, L"inspector.html");
		if (_waccess(szPath, 00) != 0)
		{
			wchar_t szBuf[1024] = L"";
			_snwprintf_s<1024>(szBuf, 1024, L"调试工具[%s]不存在", szPath);
			MessageBoxW(m_pManager ? m_pManager->GetPaintWindow():NULL, szBuf, L"错误提示", MB_OK);
		}
		else
		{
			wkeShowDevtools(m_webView, szPath, 0, 0);
		}
	}

	void CMbWebBrowserUI::DoInit()
	{
		if (m_bInit && m_webView == NULL)
		{
			wkeWindowCreateInfo info;
			info.size = sizeof(info);
			info.parent = m_pManager->GetPaintWindow();
			info.style = WS_CHILD | WS_VISIBLE;
			info.styleEx = 0;
			info.x = 0;
			info.y = 0;
			info.width = 0;
			info.height = 0;
			info.color = GetBkColor();
			m_webView = wkeCreateWebCustomWindow(&info);
			InitWebEventHandle();
			wkeSetTransparent(m_webView, false);
			wkeShowWindow(m_webView, true);
			if (!m_sHomePage.empty())
			{
				LoadUrl(m_sHomePage.c_str());
			}
			Attach(wkeGetWindowHandle(m_webView));
		}
	}

	jsValue CMbWebBrowserUI::CallJs(const char* funcname, jsValue* params, int params_count)
	{
		ASSERT(m_webView);
		jsExecState es = wkeGlobalExec(m_webView);
		return CallJs(es, funcname, params, params_count);
	}

	jsValue CMbWebBrowserUI::CallJs(jsExecState es, const char* funcname, jsValue* params, int params_count)
	{
		jsValue func = jsGetGlobal(es, funcname);
		if (jsIsFunction(func))
		{
			jsValue ret = jsCallGlobal(es, func, params, params_count);
			return ret;
		}
		return jsUndefined();
	}

	jsValue WKE_CALL_TYPE CallDuiMsg(jsExecState es, void* param)
	{
		CMbWebBrowserUI* pMbWebView = (CMbWebBrowserUI*)param;
		if (pMbWebView && pMbWebView->m_pIWebEvent)
			return pMbWebView->m_pIWebEvent->OnJsCallDuiMsg(pMbWebView, es);

		return jsUndefined();
	}

	int CMbWebBrowserUI::JsArgCount(jsExecState es)
	{
		return jsArgCount(es);
	}
	
	jsType CMbWebBrowserUI::JsArgType(jsExecState es, int argIdx)
	{
		return jsArgType(es, argIdx);
	}

	jsValue CMbWebBrowserUI::JsArg(jsExecState es, int argIdx)
	{
		return jsArg(es, argIdx);
	}

	jsValue CMbWebBrowserUI::JsString(const wchar_t* val)
	{
		jsExecState es = wkeGlobalExec(m_webView);
		return jsStringW(es, val);
	}

	jsValue CMbWebBrowserUI::JsString(jsExecState es, const wchar_t* val)
	{
		return jsStringW(es, val);
	}

	jsValue CMbWebBrowserUI::JsInt(int ival)
	{
		return jsInt(ival);
	}

	jsValue CMbWebBrowserUI::JsFloat(float ival)
	{
		return jsFloat(ival);
	}

	jsValue CMbWebBrowserUI::JsDouble(double ival)
	{
		return jsDouble(ival);
	}

	jsValue CMbWebBrowserUI::JsBool(bool b)
	{
		return jsBoolean(b);
	}

	jsValue CMbWebBrowserUI::JsUndefined()
	{
		return jsUndefined();
	}

	jsValue CMbWebBrowserUI::JsNull()
	{
		return jsNull();
	}

	bool CMbWebBrowserUI::JsIsNumber(jsValue v)
	{
		return jsIsNumber(v);
	}

	bool CMbWebBrowserUI::JsIsString(jsValue v)
	{
		return jsIsString(v);
	}

	bool CMbWebBrowserUI::JsIsBoolean(jsValue v)
	{
		return jsIsBoolean(v);
	}

	bool CMbWebBrowserUI::JsIsObject(jsValue v)
	{
		return jsIsObject(v);
	}

	bool CMbWebBrowserUI::JsIsFunction(jsValue v)
	{
		return jsIsFunction(v);
	}

	bool CMbWebBrowserUI::JsIsUndefined(jsValue v)
	{
		return jsIsUndefined(v);
	}

	bool CMbWebBrowserUI::JsIsNull(jsValue v)
	{
		return jsIsFalse(v);
	}

	bool CMbWebBrowserUI::JsIsArray(jsValue v)
	{
		return jsIsArray(v);
	}

	bool CMbWebBrowserUI::JsIsTrue(jsValue v)
	{
		return jsIsTrue(v);
	}

	bool CMbWebBrowserUI::JsIsFalse(jsValue v)
	{
		return jsIsFalse(v);
	}

	int CMbWebBrowserUI::JsToInt(jsExecState es, jsValue v)
	{
		return jsToInt(es, v);
	}

	float CMbWebBrowserUI::JsToFloat(jsExecState es, jsValue v)
	{
		return jsToFloat(es, v);
	}

	double CMbWebBrowserUI::JsToDouble(jsExecState es, jsValue v)
	{
		return jsToDouble(es, v);
	}

	const char* CMbWebBrowserUI::JsToDoubleString(jsExecState es, jsValue v)
	{
		return jsToDoubleString(es, v);
	}

	BOOL CMbWebBrowserUI::JsToBoolean(jsExecState es, jsValue v)
	{
		return jsToBoolean(es, v);
	}

	jsValue CMbWebBrowserUI::JsArrayBuffer(jsExecState es, const char* buffer, size_t size)
	{
		return jsArrayBuffer(es, buffer,size);
	}

	wkeMemBuf* CMbWebBrowserUI::JsGetArrayBuffer(jsExecState es, jsValue value)
	{
		return jsGetArrayBuffer(es, value);
	}

	const utf8* CMbWebBrowserUI::JsToTempString(jsExecState es, jsValue v)
	{
		return jsToTempString(es, v);
	}

	const wchar_t* CMbWebBrowserUI::JsToTempStringW(jsExecState es, jsValue v)
	{
		return jsToTempStringW(es, v);
	}

	void WKE_CALL_TYPE onDidCreateScriptContextCallback(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int extensionGroup, int worldId)
	{
		CMbWebBrowserUI* pMbWebView = (CMbWebBrowserUI*)param;
		if (pMbWebView && pMbWebView->m_pIWebEvent)
			pMbWebView->m_pIWebEvent->onDidCreateScriptContextCallback(webView, pMbWebView, frameId, context, extensionGroup, worldId);
	}

	// 回调：点击了关闭、返回 true 将销毁窗口，返回 false 什么都不做。
	bool WKE_CALL_TYPE handleWindowClosing(wkeWebView webWindow, void* param)
	{
		CMbWebBrowserUI* pMbWebView = (CMbWebBrowserUI*)param;
		
		if (pMbWebView && pMbWebView->m_pIWebEvent)
			return pMbWebView->m_pIWebEvent->handleWindowClosing(webWindow, pMbWebView);

		return true;
	}

	// 回调：窗口已销毁
	void WKE_CALL_TYPE handleWindowDestroy(wkeWebView webWindow, void* param)
	{
		CMbWebBrowserUI* pMbWebView = (CMbWebBrowserUI*)param;
		if (pMbWebView && pMbWebView->m_pIWebEvent)
			pMbWebView->m_pIWebEvent->handleWindowDestroy(webWindow, pMbWebView);

	}

	// 回调：文档加载成功
	void WKE_CALL_TYPE handleDocumentReady(wkeWebView webWindow, void* param)
	{
		CMbWebBrowserUI* pMbWebView = (CMbWebBrowserUI*)param;
		if (pMbWebView && pMbWebView->m_pIWebEvent)
			pMbWebView->m_pIWebEvent->handleDocumentReady(webWindow, pMbWebView);
	}

	// 回调：页面标题改变
	void WKE_CALL_TYPE handleTitleChanged(wkeWebView webWindow, void* param, const wkeString title)
	{
		CMbWebBrowserUI* pMbWebView = (CMbWebBrowserUI*)param;
		if (pMbWebView && pMbWebView->m_pIWebEvent &&
			pMbWebView->m_pIWebEvent->handleTitleChanged(webWindow, pMbWebView, wkeToStringW(title)))
		{
			return;
		}
		
		if (pMbWebView)
		{
			wkeSetWindowTitleW(webWindow,wkeToStringW(title));
		}
	}

	// 回调：创建新的页面，比如说调用了 window.open 或者点击了 <a target="_blank" .../>
	wkeWebView WKE_CALL_TYPE onCreateView(wkeWebView webWindow, void* param, wkeNavigationType navType, const wkeString url, const wkeWindowFeatures* features)
	{
		CMbWebBrowserUI* pMbWebView = (CMbWebBrowserUI*)param;
		if (pMbWebView && pMbWebView->m_pIWebEvent)
		{
			wkeWebView webview = pMbWebView->m_pIWebEvent->onCreateView(webWindow, pMbWebView, navType, wkeToStringW(url), features);
			if (webview != nullptr)
				return webview;
		}
		
		wkeWebView webview = wkeCreateWebWindow(WKE_WINDOW_TYPE_POPUP, NULL, features->x, features->y, features->width, features->height);
		wkeShowWindow(webview, true);
		return webview;
	}

	bool WKE_CALL_TYPE onLoadUrlBegin(wkeWebView webView, void* param, const char* url, void* job)
	{
		CMbWebBrowserUI* pMbWebView = (CMbWebBrowserUI*)param;
		if (pMbWebView && pMbWebView->m_pIWebEvent)
			return pMbWebView->m_pIWebEvent->onLoadUrlBegin(webView, pMbWebView, StringUtil::Easy_AnsiToUnicode(url).c_str(), job);
		return false;
	}

	void WKE_CALL_TYPE onLoadingFinish(wkeWebView webView, void* param, const wkeString url, wkeLoadingResult result, const wkeString failedReason)
	{
		CMbWebBrowserUI* pMbWebView = (CMbWebBrowserUI*)param;
		if (pMbWebView && pMbWebView->m_pIWebEvent)
			pMbWebView->m_pIWebEvent->onLoadingFinish(webView, pMbWebView, wkeToStringW(url), result, failedReason);
	}

	void WKE_CALL_TYPE onLoadUrlFail(wkeWebView webView, void* param, const utf8* url, wkeNetJob job)
	{
		CMbWebBrowserUI* pMbWebView = (CMbWebBrowserUI*)param;
		if (pMbWebView && pMbWebView->m_pIWebEvent)
			pMbWebView->m_pIWebEvent->onLoadUrlFail(webView, pMbWebView, StringUtil::Easy_Utf8ToUnicode(url).c_str(), job);
	}
}

