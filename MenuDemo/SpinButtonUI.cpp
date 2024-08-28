#include "stdafx.h"
#include "SpinButtonUI.h"
#include <string>


CSpinButtonUI::CSpinButtonUI()
{
	m_pEditUI = NULL;
	m_pLeftBtnUI = NULL;
	m_pRightBtnUI = NULL;
}


CSpinButtonUI::~CSpinButtonUI()
{
}

void CSpinButtonUI::DoInit()
{
	__super::DoInit();
	m_pEditUI = dynamic_cast<CEditUI *>(FindSubControl(_T("edit")));
	m_pLeftBtnUI = dynamic_cast<CButtonUI *>(FindSubControl(_T("left_arrow")));
	m_pRightBtnUI = dynamic_cast<CButtonUI *>(FindSubControl(_T("right_arrow")));
}

void CSpinButtonUI::Notify(TNotifyUI& msg)
{
	//这里把消息传递到顶层外围窗口，让最外层的窗口有机会处理该消息
	__super::Notify(msg);

	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (msg.pSender == m_pLeftBtnUI)
		{
			LONGLONG val = _ttoi(m_pEditUI->GetText());
			TCHAR szBuf[128] = _T("");
			_sntprintf(szBuf, 128, _T("%d"), --val);
			m_pEditUI->SetText(szBuf);
		}
		else if (msg.pSender == m_pRightBtnUI)
		{
			LONGLONG val = _ttoi(m_pEditUI->GetText());
			TCHAR szBuf[128] = _T("");
			_sntprintf(szBuf, 128, _T("%d"), ++val);
			m_pEditUI->SetText(szBuf);
		}
	}
}