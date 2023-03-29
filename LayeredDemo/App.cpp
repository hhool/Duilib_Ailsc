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
	virtual CDuiString GetSkinFile(){return _T("skin/layered/layeredwnd.xml");}
	virtual LPCTSTR GetWindowClassName(void) const  {return _T("CFrameWindowWnd");}
	virtual CControlUI* CreateControl(LPCTSTR pstrClass)
	{
		return NULL;
	}
	virtual void InitWindow()
	{
	}
	virtual void Notify(TNotifyUI& msg)
	{
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
