#include "stdafx.h"
#include "UIIPAddress.h"
#include <windowsx.h>

#ifndef MAKEIPADDRESS
#define MAKEIPADDRESS(b1,b2,b3,b4)  ((LPARAM)(((DWORD)(b1)<<24)+((DWORD)(b2)<<16)+((DWORD)(b3)<<8)+((DWORD)(b4))))
#endif // !MAKEIPADDRESS

namespace DuiLib
{
//////////////////////////////////////////////////////////////////////////
// CIPAddressWnd
class CIPAddressWnd
    : public CWindowWnd
{
public:
    CIPAddressWnd();
    ~CIPAddressWnd();

    void Init(CIPAddressUI *pOwner);

    RECT CalPos();

    LPCTSTR GetWindowClassName() const;
    LPCTSTR GetSuperClassName() const;
    void OnFinalMessage(HWND hWnd);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	LRESULT OnEditChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);

public:
    // Determines if all fields in the IP address control are blank.
    BOOL IsBlank() const;

    // Clears the contents of the IP address control.
    void ClearAddress();

    // Retrieves the address values for all four fields in the IP address control.
    int GetAddress(_Out_ BYTE & nField0, _Out_ BYTE & nField1, _Out_ BYTE & nField2, _Out_ BYTE & nField3) const;
    int GetAddress(_Out_ DWORD & dwAddress) const;

    // Sets the address values for all four fields in the IP address control.
    void SetAddress(_In_ DWORD dwAddress);
    void SetAddress(_In_ BYTE nField0, _In_ BYTE nField1, _In_ BYTE nField2, _In_ BYTE nField3);

    // Sets the keyboard focus to the specified field in the IP address control.
    void SetFieldFocus(_In_ WORD nField);

    // Sets the valid range for the specified field in the IP address control.
    void SetFieldRange(_In_ int nField, _In_ BYTE nLower, _In_ BYTE nUpper);

private:
    bool m_bInit;
    CIPAddressUI *m_pOwner;
};

CIPAddressWnd::CIPAddressWnd()
    : m_bInit(false)
    , m_pOwner(NULL)
{
}

CIPAddressWnd::~CIPAddressWnd()
{
}

void CIPAddressWnd::Init(CIPAddressUI *pOwner)
{
    m_pOwner = pOwner;
    CDuiRect rcPos = CalPos();
    // the IP Address Control must be a child
    UINT uStyle = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_CHILD;
	if (!::IsWindow(m_pOwner->GetManager()->GetPaintWindow()))return;
	Create(m_pOwner->GetManager()->GetPaintWindow(), NULL, uStyle, 0, rcPos.left, rcPos.top, rcPos.GetWidth(), rcPos.GetHeight());
	SetAddress(m_pOwner->m_nField0,m_pOwner->m_nField1,m_pOwner->m_nField2,m_pOwner->m_nField3);
	SetFieldRange(0, m_pOwner->m_nFiledRange[0][0], m_pOwner->m_nFiledRange[0][1]);
	SetFieldRange(1, m_pOwner->m_nFiledRange[1][0], m_pOwner->m_nFiledRange[1][1]);
	SetFieldRange(2, m_pOwner->m_nFiledRange[2][0], m_pOwner->m_nFiledRange[2][1]);
	SetFieldRange(3, m_pOwner->m_nFiledRange[3][0], m_pOwner->m_nFiledRange[3][1]);
	::ShowWindow(m_hWnd, SW_SHOWNOACTIVATE);
	::SetFocus(m_hWnd);
	m_bInit = true;
}

RECT CIPAddressWnd::CalPos()
{
    CDuiRect rcPos = m_pOwner->GetPos();
    return rcPos;
}

LPCTSTR CIPAddressWnd::GetWindowClassName() const
{
    return _T("IPAddressWnd");
}

LPCTSTR CIPAddressWnd::GetSuperClassName() const
{
    return WC_IPADDRESS;
}

void CIPAddressWnd::OnFinalMessage(HWND hWnd)
{
	m_pOwner->Invalidate();

	m_pOwner->m_pWindow = NULL;
	delete this;
}

LRESULT CIPAddressWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	if(uMsg == WM_NOTIFY)
	{
		LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>((LPNMHDR)lParam);
		if (pIPAddr && pIPAddr->hdr.code == IPN_FIELDCHANGED)
		{
			m_pOwner->GetManager()->SendNotify(m_pOwner, DUI_MSGTYPE_IPFIELDCHANGED, pIPAddr->iField, pIPAddr->iValue);
		}
	}
	else if(uMsg == OCM_COMMAND)
	{
		if(GET_WM_COMMAND_CMD(wParam, lParam) == EN_SETFOCUS)
		{
			//lRes = OnEditChanged(uMsg, wParam, lParam, bHandled);
		}
		else if(GET_WM_COMMAND_CMD(wParam, lParam) == EN_KILLFOCUS)
		{
			lRes = OnKillFocus(uMsg, wParam, lParam, bHandled);
		}
		else if(GET_WM_COMMAND_CMD(wParam, lParam) == EN_CHANGE)
		{
			lRes = OnEditChanged(uMsg, wParam, lParam, bHandled);
		}
		else if(GET_WM_COMMAND_CMD(wParam, lParam) == EN_UPDATE)
		{
			RECT rcClient;
			::GetClientRect(m_hWnd, &rcClient);
			::InvalidateRect(m_hWnd, &rcClient, FALSE);
		}
	}
	else if(uMsg == WM_KEYDOWN)
	{
		if(TCHAR(wParam) == VK_RETURN)
		{
			m_pOwner->GetManager()->SendNotify(m_pOwner, DUI_MSGTYPE_EDITRETURN);
		}
		else
		{
			bHandled = FALSE;
		}
	}
	else
	{
		bHandled = FALSE;
	}

	if (!bHandled) return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	return lRes;
}

LRESULT CIPAddressWnd::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	if (!m_bInit || !m_pOwner)return 0;
	LRESULT lRes = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	DWORD dwIPAddress = MAKEIPADDRESS(m_pOwner->m_nField0, m_pOwner->m_nField1, m_pOwner->m_nField2, m_pOwner->m_nField3);
	CDuiString strIPAddress;
	strIPAddress.Format(_T("%u.%u.%u.%u"), m_pOwner->m_nField0, m_pOwner->m_nField1, m_pOwner->m_nField2, m_pOwner->m_nField3);
	m_pOwner->SetText(strIPAddress);
	///>#liulei 20161108 把焦点还给父窗口否则可能Heap崩溃
	///> 触发情况：点击IpCtrl 两个ip之间的那个点就可以重现
	SetFocus(m_pOwner->GetManager()->GetPaintWindow());
	PostMessage(WM_CLOSE);
	return lRes;
}

LRESULT CIPAddressWnd::OnEditChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	if (!m_bInit || !m_pOwner) return 0;
	GetAddress(m_pOwner->m_nField0,m_pOwner->m_nField1,m_pOwner->m_nField2,m_pOwner->m_nField3);
	return S_OK;
}

BOOL CIPAddressWnd::IsBlank() const
{
    ASSERT(::IsWindow(m_hWnd));
    return (BOOL) ::SendMessage(m_hWnd, IPM_ISBLANK, 0, 0L);
}

void CIPAddressWnd::ClearAddress()
{
    ASSERT(::IsWindow(m_hWnd));
    ::SendMessage(m_hWnd, IPM_CLEARADDRESS, 0, 0L);
}

int CIPAddressWnd::GetAddress(_Out_ BYTE & nField0, _Out_ BYTE & nField1, _Out_ BYTE & nField2, _Out_ BYTE & nField3) const
{
    ASSERT(::IsWindow(m_hWnd));
    DWORD dwAddress;
    LRESULT nRetVal = ::SendMessage(m_hWnd, IPM_GETADDRESS, 0, (LPARAM) &dwAddress);
    nField0 = (BYTE) FIRST_IPADDRESS(dwAddress);
    nField1 = (BYTE) SECOND_IPADDRESS(dwAddress);
    nField2 = (BYTE) THIRD_IPADDRESS(dwAddress);
    nField3 = (BYTE) FOURTH_IPADDRESS(dwAddress);
    //IA64: only four fields in an IP address, so an int won't overflow
    return int(nRetVal);
}

int CIPAddressWnd::GetAddress(_Out_ DWORD & dwAddress) const
{
    ASSERT(::IsWindow(m_hWnd));
    return (int) ::SendMessage(m_hWnd, IPM_GETADDRESS, 0, (LPARAM) &dwAddress);
}

void CIPAddressWnd::SetAddress(_In_ DWORD dwAddress)
{
    ASSERT(::IsWindow(m_hWnd));
    ::SendMessage(m_hWnd, IPM_SETADDRESS, 0, (LPARAM) dwAddress);
}

void CIPAddressWnd::SetAddress(_In_ BYTE nField0, _In_ BYTE nField1, _In_ BYTE nField2, _In_ BYTE nField3)
{
    ASSERT(::IsWindow(m_hWnd));
    ::SendMessage(m_hWnd, IPM_SETADDRESS, 0, (LPARAM) MAKEIPADDRESS(nField0, nField1, nField2, nField3));
}

void CIPAddressWnd::SetFieldFocus(_In_ WORD nField)
{
    ASSERT(::IsWindow(m_hWnd));
    ::SendMessage(m_hWnd, IPM_SETFOCUS, (WPARAM) nField, 0);
}

void CIPAddressWnd::SetFieldRange(_In_ int nField, _In_ BYTE nLower, _In_ BYTE nUpper)
{
    ASSERT(::IsWindow(m_hWnd));
    ::SendMessage(m_hWnd, IPM_SETRANGE, (WPARAM) nField, MAKEIPRANGE(nLower, nUpper));
}

//////////////////////////////////////////////////////////////////////////
// CIPAddressUI
CIPAddressUI::CIPAddressUI(void)
	: m_uButtonState(0)
	, m_pWindow(NULL)
	, m_nField0(0)
	, m_nField1(0)
	, m_nField2(0)
	, m_nField3(0)
{
	for (int i = 0; i < 4;++i)
	{
		m_nFiledRange[i][0] = (BYTE)0;
		m_nFiledRange[i][1] = (BYTE)255;
	}
	m_dwBackColor = 0xFF00FF00;
}


CIPAddressUI::~CIPAddressUI(void)
{

}

void CIPAddressUI::DoInit()
{
	if (m_sText == _T(""))
		SetText(_T("0.0.0.0"));
}

UINT CIPAddressUI::GetControlFlags() const
{
	if(!IsEnabled())
		return CControlUI::GetControlFlags();
	return UIFLAG_SETCURSOR | UIFLAG_TABSTOP;
}

LPCTSTR CIPAddressUI::GetClass() const
{
	return DUI_CTR_IPADDRESS;
}

LPVOID CIPAddressUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, DUI_CTR_IPADDRESS) == 0) return static_cast<CIPAddressUI*>(this);
	return CLabelUI::GetInterface(pstrName);
}

void CIPAddressUI::DoEvent(TEventUI& event)
{
	if (!IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND)
	{
		if(m_pParent != NULL)
			m_pParent->DoEvent(event);
		else
			CLabelUI::DoEvent(event);
		return;
	}

	if (event.Type == UIEVENT_SETCURSOR && IsEnabled())
	{
		::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_IBEAM)));
		return;
	}

	if (event.Type == UIEVENT_WINDOWSIZE)
	{
		if(m_pWindow != NULL)
		{
			m_pManager->SetFocusNeeded(this);
		}
	}

	if (event.Type == UIEVENT_SCROLLWHEEL)
	{
		if(m_pWindow != NULL)
		{
			return;
		}
	}

	if (event.Type == UIEVENT_SETFOCUS)
	{
		if (!IsEnabled() || m_pWindow)
		{
			return;
		}

		m_pWindow = new CIPAddressWnd();
		ASSERT(m_pWindow);
		m_pWindow->Init(this);
		Invalidate();
	}

	if (event.Type == UIEVENT_KILLFOCUS && IsEnabled())
	{
		Invalidate();
	}

	if (event.Type == UIEVENT_LBUTTONDOWN || event.Type == UIEVENT_LDBLCLICK || event.Type == UIEVENT_RBUTTONDOWN)
	{
		if( ::PtInRect(&m_rcItem, event.ptMouse) )
		{
			if(IsEnabled())
			{
				GetManager()->ReleaseCapture();

				if(IsFocused() && m_pWindow == NULL)
				{
					m_pWindow = new CIPAddressWnd();
					ASSERT(m_pWindow);
					m_pWindow->Init(this);
				}
				else if(m_pWindow != NULL)
				{

				}
			}
		}
		else
		{
			if ( m_pManager->GetFocus() == this )
				m_pManager->SetFocus(NULL);
		}
		return;
	}

	if (event.Type == UIEVENT_MOUSEMOVE ||
		event.Type == UIEVENT_BUTTONUP ||
		event.Type == UIEVENT_CONTEXTMENU)
	{
		return;
	}

	if (event.Type == UIEVENT_MOUSEENTER)
	{
		if(IsEnabled())
		{
			m_uButtonState |= UISTATE_HOT;
			Invalidate();
		}
		return;
	}

	if (event.Type == UIEVENT_MOUSELEAVE)
	{
		if(IsEnabled())
		{
			m_uButtonState &= ~UISTATE_HOT;
			Invalidate();
		}
		return;
	}

	CLabelUI::DoEvent(event);
}

void CIPAddressUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName, _T("field0")) == 0 ||
		_tcscmp(pstrName, _T("field1")) == 0 ||
		_tcscmp(pstrName, _T("field2")) == 0 ||
		_tcscmp(pstrName, _T("field3")) == 0 )
	{
		LPTSTR pstr = NULL;
		int iVal[2] = { 0, 255 };
		iVal[0] = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);
		iVal[1] = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
		SetFieldRange(pstrName[5] - _T('0'), iVal[0], iVal[1]);
	}
    CLabelUI::SetAttribute(pstrName, pstrValue);
}

void CIPAddressUI::SetText(LPCTSTR pstrText)
{
	if (pstrText == NULL || m_sText == pstrText) return;

	TCHAR szTemp[16] = _T("");
	lstrcpyn(szTemp, pstrText, 16);
	int ifiledval[4] = { 0 };
	int nfiledindex = 0;
	TCHAR *token = NULL, *szsub = NULL;
	szsub = _tcstok_s(szTemp, _T("."), &token);
	while (szsub)
	{
		ifiledval[nfiledindex++] = _ttoi(szsub);
		szsub = _tcstok_s(NULL, _T("."), &token);
	}

	m_nField0 = ifiledval[0];
	m_nField1 = ifiledval[1];
	m_nField2 = ifiledval[2];
	m_nField3 = ifiledval[3];
	SetAddress(m_nField0, m_nField1, m_nField2, m_nField3);
}

void CIPAddressUI::SetAddress(_In_ BYTE nField0, _In_ BYTE nField1, _In_ BYTE nField2, _In_ BYTE nField3)
{
	m_nField0 = nField0;
	m_nField1 = nField1;
	m_nField2 = nField2;
	m_nField3 = nField3;
	CDuiString strIPAddress;
	strIPAddress.Format(_T("%u.%u.%u.%u"), m_nField0, m_nField1, m_nField2, m_nField3);
	CLabelUI::SetText(strIPAddress);
}

void CIPAddressUI::SetFieldRange(_In_ int nField, _In_ BYTE nLower, _In_ BYTE nUpper)
{
	if (nField >= 0 && nField < 4)
	{
		m_nFiledRange[nField][0] = nLower;
		m_nFiledRange[nField][1] = nUpper;
	}
}

void CIPAddressUI::GetAddress(_Out_ BYTE& nField0, _Out_ BYTE& nField1, _Out_ BYTE& nField2, _Out_ BYTE& nField3) const
{
	nField0 = m_nField0;
	nField1 = m_nField1;
	nField2 = m_nField2;
	nField3 = m_nField3;
}

void CIPAddressUI::GetAddress(_Out_ DWORD& dwAddress) const
{
	dwAddress = MAKEIPADDRESS(m_nField0, m_nField1, m_nField2, m_nField3);
}

CDuiString CIPAddressUI::GetIPAddress()
{
	return GetText();
}

}
