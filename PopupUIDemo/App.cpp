// App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DateUI.h"
/*
ʵ��DateUI�ؼ�˼��

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
    pFrame->Create(NULL, _T("����һ����򵥵Ĳ�����exe���޸�test1.xml�Ϳ��Կ���Ч��"), UI_WNDSTYLE_FRAME|WS_CLIPCHILDREN, WS_EX_WINDOWEDGE);
    pFrame->CenterWindow();
    pFrame->ShowModal();
    ::CoUninitialize();
    return 0;
}
