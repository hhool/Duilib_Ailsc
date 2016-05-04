#include "stdafx.h"
#include "UIWinWnd.h"

namespace DuiLib
{
	CWinWndUI::CWinWndUI(BOOL bDieWithControl):m_hWnd(NULL)
	{
		m_bDieWithControl = bDieWithControl;
	}

	CWinWndUI::~CWinWndUI()
	{
		if(m_hWnd && m_bDieWithControl && IsWindow(m_hWnd))
		{
			::SendMessage(m_hWnd,WM_CLOSE,0,0);
		}
	}
	void CWinWndUI::SetInternVisible(bool bVisible)
	{
		__super::SetInternVisible(bVisible);
		::ShowWindow(m_hWnd, bVisible);
	}

	void CWinWndUI::SetPos(RECT rc)
	{
		__super::SetPos(rc);
		::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
	}

	BOOL CWinWndUI::Attach(HWND hWndNew)
	{
		if (! ::IsWindow(hWndNew))
		{
			return FALSE;
		}

		m_hWnd = hWndNew;
		return TRUE;
	}

	HWND CWinWndUI::Detach()
	{
		HWND hWnd = m_hWnd;
		m_hWnd = NULL;
		return hWnd;
	}

	void CWinWndUI::DieWithControl(BOOL bDieWithControl)
	{
		m_bDieWithControl = bDieWithControl;
	}
}

