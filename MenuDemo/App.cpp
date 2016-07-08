// App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
/*Duilib �˵�ʹ��
1.new CMenuWnd ����һ��Menu����
2.�ƶ�Menu�����ݺ�λ�ã�Init
���Init֮����Ҫ��̬�޸���������Ҫ��GetMenuUI��Ȼ���MenuUI��������
3.��ʾmenu ShowWindow
4.Menu�¼�������Ӧitemclick��Ϣ��������֮��return������Ҫ�����ײ㴦��
*/
class CFrameWindowWnd: public WindowImplBase
{
public:
	CFrameWindowWnd(){};
	virtual CDuiString GetSkinFolder() {return _T("");}
	virtual CDuiString GetSkinFile(){return _T("skin/menu/menuwnd.xml");}
	virtual LPCTSTR GetWindowClassName(void) const  {return _T("CFrameWindowWnd");}

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
