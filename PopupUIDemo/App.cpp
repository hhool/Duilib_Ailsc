// App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DateUI.h"
/*
实现DateUI控件思想

*/
CUIFunctionalLayout *CreatePopupUI()
{
	return new CDateUI;
}

class CFrameWindowWnd : public WindowImplBase, IMBWenviewEvent
{
public:
	virtual bool handleTitleChanged(wkeWebView webWindow, CMbWebBrowserUI* pwebBrowser, const wchar_t* title)
	{ 
		return false;
	}
	virtual void onLoadUrlEnd(wkeWebView webView, CMbWebBrowserUI* pwebBrowser, const wchar_t* url, void* job, void* buf, int len)
	{
		int a = 0;
	}
	virtual bool onLoadUrlBegin(wkeWebView webView, CMbWebBrowserUI* pwebBrowser, const wchar_t* url, void* job)
	{
		return false;
	}
	virtual void onLoadingFinish(wkeWebView webView, CMbWebBrowserUI* pwebBrowser, const wchar_t* url, wkeLoadingResult result, const wkeString failedReason)
	{
		int a = 0;
		pwebBrowser->ShowDevTool();
	}
	virtual void onLoadUrlFail(wkeWebView webView, CMbWebBrowserUI* pwebBrowser, const wchar_t* url, wkeNetJob job)
	{
		int a = 0;
	}
	virtual jsValue OnJsCallDuiMsg(CMbWebBrowserUI * pwebBrowser, jsExecState es)
	{
		int a = 0;
		return 0;
	}
	CFrameWindowWnd(){};
	virtual CDuiString GetSkinFolder() {return _T("");}
	virtual CDuiString GetSkinFile(){return _T("skin/popup/popup.xml");}
	virtual LPCTSTR GetWindowClassName(void) const  {return _T("CFrameWindowWnd");}
	virtual void InitWindow()
	{
		__super::InitWindow();
		m_pPupUI  = dynamic_cast<CPopupUI *>(m_PaintManager.FindControl(_T("DateTime")));
		m_pWebUI = dynamic_cast<CMbWebBrowserUI *>(m_PaintManager.FindControl(_T("web")));
		m_pWebUI->RegisterWebEvent(this);
		m_pWebUI->SetHomePage(L"file:///F:/project/CefDemo/x64/Debug/test.html");
		if(m_pPupUI)
		{
			///> 设置需要处理PopUI的事件对象，功能性事件处理封装在CDateUI
			m_pPupUI->SetCreatePopupUI(CreatePopupUI);
			///> 初始化事件
			SYSTEMTIME ltime;
			GetLocalTime(&ltime);
			///> 格式约定和CDateUI保持一致
			CDuiString str;
			str.Format(_T("%d-%d-%d"),ltime.wYear,ltime.wMonth,ltime.wDay);
			m_pPupUI->SetText(str);
		}

		
		//测试Attach窗口
		CMbWebBrowserUI *pWenUI = new CMbWebBrowserUI(CMbWebBrowserUI::CreateWebWindow(WKE_WINDOW_TYPE_POPUP, NULL, 0, 0, 800, 600));
		pWenUI->LoadUrl(L"https://www.baidu.com");
		pWenUI->SetInternVisible(true);
	}

	virtual void Notify(TNotifyUI& msg)
	{
		__super::Notify(msg);
		if (msg.pSender->GetName() == _T("test"))
		{
			static bool bVisible = false;
			m_pWebUI->SetVisible(bVisible);
			bVisible = !bVisible;
		}
	}

private:
	CPopupUI *m_pPupUI;
	CMbWebBrowserUI *m_pWebUI;
};


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
    HRESULT Hr = ::CoInitialize(NULL);
    if( FAILED(Hr) ) return 0;


    CFrameWindowWnd* pFrame = new CFrameWindowWnd();
    if( pFrame == NULL ) return 0;
    pFrame->Create(NULL, _T("这是一个最简单的测试用exe，修改test1.xml就可以看到效果"), UI_WNDSTYLE_FRAME|WS_CLIPCHILDREN, WS_EX_WINDOWEDGE);
    pFrame->CenterWindow();
    pFrame->ShowModal();
    ::CoUninitialize();
    return 0;
}
