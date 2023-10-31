// App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SpinButtonUI.h"
/*Duilib �˵�ʹ��
1.new CMenuWnd ����һ��Menu����
2.�ƶ�Menu�����ݺ�λ�ã�Init
���Init֮����Ҫ��̬�޸���������Ҫ��GetMenuUI��Ȼ���MenuUI��������
3.��ʾmenu ShowWindow
4.Menu�¼�������Ӧitemclick��Ϣ��������֮��return������Ҫ�����ײ㴦��
*/

CUIFunctionalLayout *CreatePopupUI()
{
	return new CSpinButtonUI;
}

class CFrameWindowWnd: public WindowImplBase
{
public:
	CFrameWindowWnd(){};
	virtual CDuiString GetSkinFolder() {return _T("");}
	virtual CDuiString GetSkinFile(){return _T("skin/menu/menuwnd.xml");}
	virtual LPCTSTR GetWindowClassName(void) const  {return _T("CFrameWindowWnd");}
	virtual CControlUI* CreateControl(LPCTSTR pstrClass)
	{
		if (lstrcmp(pstrClass, _T("SpinButton")) == 0)
		{
			return new CSpinButtonUI();
		}
		return NULL;
	}
	virtual void InitWindow()
	{
		CGridLayoutUI *pGridUI = dynamic_cast<CGridLayoutUI *>(m_PaintManager.FindControl(_T("grid_layout")));
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();
		pGridUI->AddTemplate();

		CPopupUI *popup_wnd = dynamic_cast<CPopupUI *>(m_PaintManager.FindControl(_T("popup_wnd")));
		popup_wnd->SetCreatePopupUI(CreatePopupUI);
	}
	virtual void Notify(TNotifyUI& msg)
	{
		if(msg.sType == DUI_MSGTYPE_MENU)
		{
			CMenuWnd* pMenu = new CMenuWnd(&m_PaintManager, m_hWnd);
			CDuiPoint point = msg.ptMouse;
			ClientToScreen(m_hWnd, &point);
			///> DefaultMenu�н����ƶ���Menu����ʽ������������Ҫ��̬����
			///> ��Ȼ���DefaultMenu �ƶ���menu�ľ���������Ҫ��̬����
			STRINGorID xml(_T("skin/Menu/DefaultMenu.xml"));
			if (pMenu->Init(point, xml))
			{
				///> ֧�ֶ�̬�޸�
				CMenuUI *pMenuUI = pMenu->GetMenuUI();
				CMenuElementUI *pEditMenuElement = new CMenuElementUI;
				pEditMenuElement->SetText(_T("  �༭  "));
				CMenuElementUI *pModMenuElement = new CMenuElementUI;
				pModMenuElement->SetText(_T("  �޸�  "));
				pModMenuElement->SetName(_T("modProj"));
				CMenuElementUI *pDelMenuElement = new CMenuElementUI;
				pDelMenuElement->SetText(_T("  ɾ��  "));
				pDelMenuElement->SetName(_T("delProj"));
				pEditMenuElement->Add(pModMenuElement);
				pEditMenuElement->Add(pDelMenuElement);
				pMenuUI->Add(pEditMenuElement);
			}
			pMenu->ShowWindow();
		}
		///> ��Ӧ�˵���Ϣ
		else if(msg.sType == DUI_MSGTYPE_ITEMCLICK && msg.pSender->GetInterface(DUI_CTR_MENUELEMENT))
		{
			if (msg.pSender->GetName() == _T("modProj"))
			{
				MessageBox(NULL,_T("�޸�"),_T("������ʾ"),MB_OK);
			}
			///> Menu �е����÷��
			else if (msg.pSender->GetName() == _T("delProj"))
			{
				MessageBox(NULL,_T("ɾ��"),_T("������ʾ"),MB_OK);
			}
			return;//��ҪReturn������ܱ�������Ϊ��ʱpSender�Ѿ����٣�����Ҫ�����ײ�
		}
		else if (msg.sType == DUI_MSGTYPE_CLICK  && msg.pSender->GetInterface(DUI_CTR_BUTTON))
		{
			if (msg.pSender->GetName() == _T("tab0"))
			{
				CTabLayoutUI *pTabLayout = dynamic_cast<CTabLayoutUI *>(m_PaintManager.FindControl(_T("tab_layout")));
				if (pTabLayout)
					pTabLayout->SelectItem(0);
			}
			else if (msg.pSender->GetName() == _T("tab1"))
			{
				CTabLayoutUI *pTabLayout = dynamic_cast<CTabLayoutUI *>(m_PaintManager.FindControl(_T("tab_layout")));
				if (pTabLayout)
					pTabLayout->SelectItem(1);
			}
			else if (msg.pSender->GetName() == _T("tab2"))
			{
				CTabLayoutUI *pTabLayout = dynamic_cast<CTabLayoutUI *>(m_PaintManager.FindControl(_T("tab_layout")));
				if (pTabLayout)
					pTabLayout->SelectItem(2);
			}
			if (msg.pSender->GetName() == _T("slider_tab0"))
			{
				CSliderTabLayoutUI *pTabLayout = dynamic_cast<CSliderTabLayoutUI *>(m_PaintManager.FindControl(_T("slider_tab_layout")));
				if (pTabLayout)
					pTabLayout->SelectItem(0);
			}
			else if (msg.pSender->GetName() == _T("slider_tab1"))
			{
				CSliderTabLayoutUI *pTabLayout = dynamic_cast<CSliderTabLayoutUI *>(m_PaintManager.FindControl(_T("slider_tab_layout")));
				if (pTabLayout)
					pTabLayout->SelectItem(1);
			}
			else if (msg.pSender->GetName() == _T("slider_tab2"))
			{
				CSliderTabLayoutUI *pTabLayout = dynamic_cast<CSliderTabLayoutUI *>(m_PaintManager.FindControl(_T("slider_tab_layout")));
				if (pTabLayout)
					pTabLayout->SelectItem(2);
			}
		}
		else if (msg.sType == DUI_MSGTYPE_CLICK)
		{
			int a = 0;
		}
		__super::Notify(msg);
	}

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
