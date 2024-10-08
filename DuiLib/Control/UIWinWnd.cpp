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
			::PostMessage(m_hWnd,WM_CLOSE,0,0);
		}
		else
		{
			if (::IsWindow(m_hWnd))
				::ShowWindow(m_hWnd, SW_HIDE);
		}
	}

	LPCTSTR CWinWndUI::GetClass() const
	{
		return DUI_CTR_WIND;
	}

	LPVOID CWinWndUI::GetInterface(LPCTSTR pstrName)
	{
		if (lstrcmp(pstrName, DUI_CTR_WIND) == 0) return this;
		return __super::GetInterface(pstrName);
	}

	void CWinWndUI::SetInternVisible(bool bVisible)
	{
		__super::SetInternVisible(bVisible);
		::ShowWindow(m_hWnd, bVisible);
	}

	void CWinWndUI::Move(SIZE szOffset, bool bNeedInvalidate)
	{
		__super::Move(szOffset, bNeedInvalidate);
		RECT rc = GetPos();
		::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
	}

	void CWinWndUI::SetPos(RECT rc, bool bNeedInvalidate)
	{
		__super::SetPos(rc);
		::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
	}

	bool CWinWndUI::DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl)
	{
		bool bRet = __super::DoPaint(hDC, rcPaint, pStopControl);
		if (m_hWnd &&::IsWindow(m_hWnd))
		{
			::InvalidateRect(m_hWnd, NULL, FALSE);
		}
		return bRet;
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

