// App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DateUI.h"
/*
实现DateUI控件思想

*/
CCompositeLayoutUI *CreatePopupUI()
{
	return new CDateUI;
}

class CFrameWindowWnd: public WindowImplBase
{
public:
	CFrameWindowWnd(){};
	virtual CDuiString GetSkinFolder() {return _T("");}
	virtual CDuiString GetSkinFile(){return _T("skin/popup/popup.xml");}
	virtual LPCTSTR GetWindowClassName(void) const  {return _T("CFrameWindowWnd");}
	virtual void InitWindow()
	{
		__super::InitWindow();
		m_pPupUI  = dynamic_cast<CPopupUI *>(m_PaintManager.FindControl(_T("DateTime")));
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

	}

	virtual void Notify(TNotifyUI& msg)
	{
		__super::Notify(msg);
	}

private:
	CPopupUI *m_pPupUI;
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
