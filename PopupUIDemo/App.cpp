// App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DateUI.h"
/*
ʵ��DateUI�ؼ�˼��

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
			///> ������Ҫ����PopUI���¼����󣬹������¼������װ��CDateUI
			m_pPupUI->SetCreatePopupUI(CreatePopupUI);
			///> ��ʼ���¼�
			SYSTEMTIME ltime;
			GetLocalTime(&ltime);
			///> ��ʽԼ����CDateUI����һ��
			CDuiString str;
			str.Format(_T("%d-%d-%d"),ltime.wYear,ltime.wMonth,ltime.wDay);
			m_pPupUI->SetText(str);
		}

		
		//����Attach����
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
    pFrame->Create(NULL, _T("����һ����򵥵Ĳ�����exe���޸�test1.xml�Ϳ��Կ���Ч��"), UI_WNDSTYLE_FRAME|WS_CLIPCHILDREN, WS_EX_WINDOWEDGE);
    pFrame->CenterWindow();
    pFrame->ShowModal();
    ::CoUninitialize();
    return 0;
}
