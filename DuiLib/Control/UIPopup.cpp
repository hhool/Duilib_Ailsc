#include "StdAfx.h"

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//
//
class CPopupWnd : public CWindowWnd, public INotifyUI
{
public:
	void Init(CPopupUI* pOwner);
    LPCTSTR GetWindowClassName() const;
    void OnFinalMessage(HWND hWnd);

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    void EnsureVisible(int iIndex);
    void Scroll(int dx, int dy);
	virtual void Notify(TNotifyUI& msg);
#if(_WIN32_WINNT >= 0x0501)
	virtual UINT GetClassStyle() const;
#endif
public:
    CPaintManagerUI m_pm;
	CPopupUI* m_pOwner;
	CCompositeLayoutUI* m_pLayout;
	bool m_bNotKillWnd;//是否应该关闭窗口
};


void CPopupWnd::Init(CPopupUI* pOwner)
{
	m_pOwner = pOwner;
	m_pLayout = NULL;
	m_bNotKillWnd = false;

	// Position the popup window in absolute space
	SIZE szDrop = m_pOwner->GetPopBoxSize();
	RECT rcOwner = pOwner->GetPos();
	RECT rc = rcOwner;
	///> 首要弹出位置向下
	if (!m_pOwner->IsTopDirect())
	{
		rc.top = rc.bottom;		// 父窗口left、bottom位置作为弹出窗口起点
		rc.bottom = rc.top + szDrop.cy;	// 计算弹出窗口高度
		if (szDrop.cx > 0) rc.right = rc.left + szDrop.cx;	// 计算弹出窗口宽度

		::MapWindowRect(pOwner->GetManager()->GetPaintWindow(), HWND_DESKTOP, &rc);

		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
		CDuiRect rcWork = oMonitor.rcWork;
		if (rc.bottom > rcWork.bottom) {
			rc.left = rcOwner.left;
			rc.right = rcOwner.right;
			if (szDrop.cx > 0) rc.right = rc.left + szDrop.cx;
			rc.top = rcOwner.top - szDrop.cy;
			rc.bottom = rcOwner.top;
			::MapWindowRect(pOwner->GetManager()->GetPaintWindow(), HWND_DESKTOP, &rc);
		}
	}
	else
	{
		rc.bottom = rc.top;		// 父窗口left、bottom位置作为弹出窗口起点
		rc.top = rc.bottom - szDrop.cy;	// 计算弹出窗口高度
		if (szDrop.cx > 0) rc.right = rc.left + szDrop.cx;	// 计算弹出窗口宽度

		::MapWindowRect(pOwner->GetManager()->GetPaintWindow(), HWND_DESKTOP, &rc);

		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
		CDuiRect rcWork = oMonitor.rcWork;
		if (rc.top < rcWork.top) {
			rc.left = rcOwner.left;
			rc.right = rcOwner.right;
			if (szDrop.cx > 0) rc.right = rc.left + szDrop.cx;
			rc.top = rcOwner.bottom;
			rc.bottom = rcOwner.bottom + szDrop.cy;
			::MapWindowRect(pOwner->GetManager()->GetPaintWindow(), HWND_DESKTOP, &rc);
		}
	}


	Create(pOwner->GetManager()->GetPaintWindow(), NULL, WS_POPUP, WS_EX_TOOLWINDOW, rc);
	// HACK: Don't deselect the parent's caption
	HWND hWndParent = m_hWnd;
	while (::GetParent(hWndParent) != NULL) hWndParent = ::GetParent(hWndParent);
	::ShowWindow(m_hWnd, SW_SHOW);
    //::SendMessage(hWndParent, WM_NCACTIVATE, TRUE, 0L);
}

LPCTSTR CPopupWnd::GetWindowClassName() const
{
    return _T("PopupWnd");
}

void CPopupWnd::OnFinalMessage(HWND hWnd)
{
    m_pOwner->m_pWindow = NULL;
    m_pOwner->Invalidate();
	m_pm.RemoveNotifier(this);
	if (m_pOwner->GetManager())
		m_pOwner->GetManager()->SendNotify(m_pOwner, DUI_MSGTYPE_DROPCLOSE);
	m_pOwner = NULL;
    delete this;
}

LRESULT CPopupWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if( uMsg == WM_CREATE )
	{
		m_pm.SetForceUseSharedRes(true);
        m_pm.Init(m_hWnd);
		m_pLayout = m_pOwner->CreatePopUI();/*new CChildLayoutUI*/;
		m_pLayout->SetInset(CDuiRect(1, 1, 1, 1));
		m_pLayout->SetBkColor(0xFFFFFFFF);
		m_pLayout->SetBorderColor(0xFFC6C7D2);
		m_pLayout->SetBorderSize(1);
		m_pLayout->SetAutoDestroy(false);
		m_pm.AddNotifier(this);
        m_pm.AttachDialog(m_pLayout);
		m_pLayout->SetChildLayoutXML(m_pOwner->GetPopupXml());
		m_pLayout->DoInit();
		m_pLayout->Init();
		m_pLayout->initUIData(m_pOwner);
        return 0;
    }
    else if( uMsg == WM_CLOSE ) {
        m_pOwner->SetManager(m_pOwner->GetManager(), m_pOwner->GetParent(), false);
		if( !m_pOwner->IsFloat() ) m_pOwner->SetPos(m_pOwner->GetPos(), false);
		else m_pOwner->SetPos(m_pOwner->GetRelativePos(), false);
        m_pOwner->SetFocus();
    }
    else if( uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONDBLCLK ) {
        POINT pt = { 0 };
        ::GetCursorPos(&pt);
        ::ScreenToClient(m_pm.GetPaintWindow(), &pt);
        CControlUI* pControl = m_pm.FindControl(pt);
        if( pControl && _tcscmp(pControl->GetClass(), DUI_CTR_SCROLLBAR) == 0 ||
			pControl && !pControl->IsKillPopup()) {
			m_bNotKillWnd = true;
        }
    }
    else if( uMsg == WM_LBUTTONUP ) {
		if (m_bNotKillWnd) {
			m_bNotKillWnd = false;
        }
        else {
            POINT pt = { 0 };
            ::GetCursorPos(&pt);
            ::ScreenToClient(m_pm.GetPaintWindow(), &pt);
            CControlUI* pControl = m_pm.FindControl(pt);
            if( pControl&&_tcscmp(pControl->GetClass(), DUI_CTR_SCROLLBAR) != 0 ) PostMessage(WM_KILLFOCUS);
        }
    }
    else if( uMsg == WM_MOUSEWHEEL ) {
        int zDelta = (int) (short) HIWORD(wParam);
        TEventUI event = { 0 };
        event.Type = UIEVENT_SCROLLWHEEL;
        event.wParam = MAKELPARAM(zDelta < 0 ? SB_LINEDOWN : SB_LINEUP, 0);
        event.lParam = lParam;
        event.dwTimestamp = ::GetTickCount();
        m_pOwner->DoEvent(event);
        return 0;
    }
    else if( uMsg == WM_KILLFOCUS ) {
        if( m_hWnd != (HWND) wParam ) {
            HWND hWnd = ::GetFocus();
            HWND hParentWnd = NULL;
            bool bIsChildFocus = false;
            while( hParentWnd = ::GetParent(hWnd) ) {
                if( m_hWnd == hParentWnd ) {
                    bIsChildFocus = true;
                    break;
                }
                hWnd = hParentWnd;
            }
            if (!bIsChildFocus) {
                PostMessage(WM_CLOSE);
                return 0;
            }
        }
    }

    LRESULT lRes = 0;
    if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
    return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

void CPopupWnd::Notify(TNotifyUI& msg)
{
	if (msg.sType == DUI_MSGTYPE_WINDOWINIT 
		|| msg.sType == DUI_MSGTYPE_SETFOCUS
		|| msg.sType == DUI_MSGTYPE_KILLFOCUS)
	{
		return;
	}

	if (m_pOwner && m_pOwner && m_pOwner->GetManager())
		m_pOwner->GetManager()->SendNotify(msg, true);
}
#if(_WIN32_WINNT >= 0x0501)
UINT CPopupWnd::GetClassStyle() const
{
	return __super::GetClassStyle() | CS_DROPSHADOW;
}
#endif
////////////////////////////////////////////////////////


CPopupUI::CPopupUI() : m_pWindow(NULL)
{
	m_pPopUICreate = NULL;
	m_szDropBoxSize.cx = 200;
	m_szDropBoxSize.cy = 100;
	m_strPopXml = _T("");
	m_bTopDirect = true;
}

CPopupUI::~CPopupUI()
{
	if (m_pWindow)
		m_pWindow->SendMessage(WM_CLOSE);
	m_pWindow = NULL;
}

LPCTSTR CPopupUI::GetClass() const
{
	return DUI_CTR_POPUP;
}

LPVOID CPopupUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, DUI_CTR_POPUP) == 0) return static_cast<CPopupUI*>(this);
    return __super::GetInterface(pstrName);
}

UINT CPopupUI::GetControlFlags() const
{
    return UIFLAG_TABSTOP;
}

void CPopupUI::DoInit()
{
	__super::DoInit();
}
void CPopupUI::DoEvent(TEventUI& event)
{
    if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if( m_pParent != NULL ) m_pParent->DoEvent(event);
        else __super::DoEvent(event);
        return;
    }

    if( event.Type == UIEVENT_SETFOCUS ) 
    {
        Invalidate();
    }
    if( event.Type == UIEVENT_KILLFOCUS ) 
    {
        Invalidate();
    }
	if (event.Type == UIEVENT_LBUTTONDOWN)
    {
        if( IsEnabled() ) {
            Activate();
        }
        return;
    }
    if( event.Type == UIEVENT_BUTTONUP )
    {
        return;
    }
    if( event.Type == UIEVENT_MOUSEMOVE )
    {
        return;
    }
    if( event.Type == UIEVENT_CONTEXTMENU )
    {
        return;
    }
    __super::DoEvent(event);
}



bool CPopupUI::Activate()
{
    if( !CControlUI::Activate() ) return false;
    if( m_pWindow ) return true;
    m_pWindow = new CPopupWnd();
    ASSERT(m_pWindow);
    m_pWindow->Init(this);
    if( m_pManager != NULL ) m_pManager->SendNotify(this, DUI_MSGTYPE_DROPDOWN);
    Invalidate();
    return true;
}

void CPopupUI::SetCreatePopupUI(CRETAE_POPUP_UI pCreateUI)
{
	m_pPopUICreate = pCreateUI;
}

SIZE CPopupUI::GetPopBoxSize()
{
	return m_szDropBoxSize;
}

void CPopupUI::SetPopBoxSize(SIZE szDropBoxSize)
{
	m_szDropBoxSize = szDropBoxSize;
}

void CPopupUI::SetPopupXml(const CDuiString &strXml)
{
	m_strPopXml = strXml;
}

const CDuiString CPopupUI::GetPopupXml()
{
	return m_strPopXml;
}

void CPopupUI::SetDirect(bool bTop)
{
	m_bTopDirect = bTop;
}
bool CPopupUI::IsTopDirect()
{
	return m_bTopDirect;
}

CCompositeLayoutUI *CPopupUI::CreatePopUI()
{
	CCompositeLayoutUI *pChild = NULL;
	if (m_pPopUICreate)
		pChild = m_pPopUICreate();
	if (pChild == NULL)
		pChild = new CCompositeLayoutUI;
	return pChild;
}

void CPopupUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName, _T("popboxsize")) == 0)
	{
		SIZE szDropBoxSize = { 0 };
		LPTSTR pstr = NULL;
		szDropBoxSize.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);
		szDropBoxSize.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
		SetPopBoxSize(szDropBoxSize);
	}
	else if (_tcscmp(pstrName, _T("popxml")) == 0) SetPopupXml(pstrValue);
	else if (_tcscmp(pstrName, _T("direct")) == 0) SetDirect(_tcscmp(pstrName, _T("top")) == 0);
	else
		__super::SetAttribute(pstrName, pstrValue);
}

} // namespace DuiLib
