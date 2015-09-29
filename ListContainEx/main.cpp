#include "MainFram.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	CMainFram mainfram;
	mainfram.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	mainfram.CenterWindow();
	mainfram.ShowModal();

	return 0;
}