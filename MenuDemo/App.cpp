// App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
/*Duilib 菜单使用
1.new CMenuWnd 创建一个Menu窗口
2.制定Menu的内容和位置：Init
如果Init之后需要动态修改内容则需要先GetMenuUI，然后对MenuUI操作即可
3.显示menu ShowWindow
4.Menu事件处理，响应itemclick消息，处理完之后return，不需要交给底层处理
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
			///> DefaultMenu中仅仅制定了Menu的样式，具体内容需要动态增加
			///> 当然如果DefaultMenu 制定了menu的具体项则不需要动态增加
			STRINGorID xml(_T("skin/Menu/DefaultMenu.xml"));
			if (pMenu->Init(point, xml))
			{
				///> 支持动态修改
				CMenuUI *pMenuUI = pMenu->GetMenuUI();
				CMenuElementUI *pEditMenuElement = new CMenuElementUI;
				pEditMenuElement->SetText(_T("  编辑  "));
				CMenuElementUI *pModMenuElement = new CMenuElementUI;
				pModMenuElement->SetText(_T("  修改  "));
				pModMenuElement->SetName(_T("modProj"));
				CMenuElementUI *pDelMenuElement = new CMenuElementUI;
				pDelMenuElement->SetText(_T("  删除  "));
				pDelMenuElement->SetName(_T("delProj"));
				pEditMenuElement->Add(pModMenuElement);
				pEditMenuElement->Add(pDelMenuElement);
				pMenuUI->Add(pEditMenuElement);
			}
			pMenu->ShowWindow();
		}
		///> 响应菜单消息
		else if(msg.sType == DUI_MSGTYPE_ITEMCLICK && msg.pSender->GetInterface(DUI_CTR_MENUELEMENT))
		{
			if (msg.pSender->GetName() == _T("modProj"))
			{
				MessageBox(NULL,_T("修改"),_T("操作提示"),MB_OK);
			}
			///> Menu 中的设置风控
			else if (msg.pSender->GetName() == _T("delProj"))
			{
				MessageBox(NULL,_T("删除"),_T("操作提示"),MB_OK);
			}
			return;//需要Return否则可能崩溃，因为此时pSender已经销毁，不需要传到底层
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
    pFrame->Create(NULL, _T("这是一个最简单的测试用exe，修改test1.xml就可以看到效果"), UI_WNDSTYLE_FRAME|WS_CLIPCHILDREN, WS_EX_WINDOWEDGE);
    pFrame->CenterWindow();
    pFrame->ShowModal();
    ::CoUninitialize();
    return 0;
}
