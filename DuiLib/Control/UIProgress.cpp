#include "stdafx.h"
#include "UIProgress.h"

namespace DuiLib
{
	CProgressUI::CProgressUI() : m_bHorizontal(true), m_nMin(0), m_nMax(100), m_nValue(0)
	{
		m_rcImgPadding.left = m_rcImgPadding.right = m_rcImgPadding.top = m_rcImgPadding.bottom = 0;
		m_uTextStyle = DT_SINGLELINE | DT_CENTER;
		SetFixedHeight(12);
	}

	LPCTSTR CProgressUI::GetClass() const
	{
		return DUI_CTR_PROGRESS;
	}

	LPVOID CProgressUI::GetInterface(LPCTSTR pstrName)
	{
		if( _tcscmp(pstrName, DUI_CTR_PROGRESS) == 0 ) return static_cast<CProgressUI*>(this);
		return CLabelUI::GetInterface(pstrName);
	}

	bool CProgressUI::IsHorizontal()
	{
		return m_bHorizontal;
	}

	void CProgressUI::SetHorizontal(bool bHorizontal)
	{
		if( m_bHorizontal == bHorizontal ) return;

		m_bHorizontal = bHorizontal;
		Invalidate();
	}

	int CProgressUI::GetMinValue() const
	{
		return m_nMin;
	}

	void CProgressUI::SetMinValue(int nMin)
	{
		m_nMin = nMin;
		Invalidate();
	}

	int CProgressUI::GetMaxValue() const
	{
		return m_nMax;
	}

	void CProgressUI::SetMaxValue(int nMax)
	{
		m_nMax = nMax;
		Invalidate();
	}

	int CProgressUI::GetValue() const
	{
		return m_nValue;
	}

	void CProgressUI::SetValue(int nValue,bool bNotify)
	{
		m_nValue = nValue;
		if (m_nValue > m_nMax) m_nValue = m_nMax;
		if (m_nValue < m_nMin) m_nValue = m_nMin;
		Invalidate();

		if(bNotify)
			m_pManager->SendNotify(this, DUI_MSGTYPE_VALUECHANGED);
	}

	LPCTSTR CProgressUI::GetForeImage() const
	{
		return m_diFore.sDrawString;
	}

	void CProgressUI::SetForeImage(LPCTSTR pStrImage)
	{
		if( m_diFore.sDrawString == pStrImage && m_diFore.pImageInfo != NULL ) return;
		m_diFore.Clear();
		m_diFore.sDrawString = pStrImage;
		Invalidate();
	}

	RECT CProgressUI::GetImgPadding() const
	{
		return m_rcImgPadding;
	}

	void CProgressUI::SetImgPadding(RECT rcPadding)
	{
		m_rcImgPadding = rcPadding;
		NeedUpdate();
	}


	void CProgressUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if( _tcscmp(pstrName, _T("foreimage")) == 0 ) SetForeImage(pstrValue);
		else if( _tcscmp(pstrName, _T("hor")) == 0 ) SetHorizontal(_tcscmp(pstrValue, _T("true")) == 0);
		else if( _tcscmp(pstrName, _T("min")) == 0 ) SetMinValue(_ttoi(pstrValue));
		else if( _tcscmp(pstrName, _T("max")) == 0 ) SetMaxValue(_ttoi(pstrValue));
		else if( _tcscmp(pstrName, _T("value")) == 0 ) SetValue(_ttoi(pstrValue));
		else if (_tcscmp(pstrName, _T("imgpadding")) == 0) {
			RECT rcPadding = { 0 };
			LPTSTR pstr = NULL;
			rcPadding.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);
			rcPadding.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
			rcPadding.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);
			rcPadding.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);
			SetImgPadding(rcPadding);
		}
		else CLabelUI::SetAttribute(pstrName, pstrValue);
	}

	void CProgressUI::PaintStatusImage(HDC hDC)
	{
		if( m_nMax <= m_nMin ) m_nMax = m_nMin + 1;
		if( m_nValue > m_nMax ) m_nValue = m_nMax;
		if( m_nValue < m_nMin ) m_nValue = m_nMin;

		RECT rc = {0};
		if( m_bHorizontal ) {
			rc.right = (m_nValue - m_nMin) * (m_rcItem.right - m_rcItem.left) / (m_nMax - m_nMin);
			rc.bottom = m_rcItem.bottom - m_rcItem.top;
		}
		else {
			rc.top = (m_rcItem.bottom - m_rcItem.top) * (m_nMax - m_nValue) / (m_nMax - m_nMin);
			rc.right = m_rcItem.right - m_rcItem.left;
			rc.bottom = m_rcItem.bottom - m_rcItem.top;
		}

		rc.top += m_rcImgPadding.top;
		rc.left += m_rcImgPadding.left;
		rc.right -= m_rcImgPadding.right;
		rc.bottom -= m_rcImgPadding.bottom;
		m_diFore.rcDestOffset = rc;
		if( DrawImage(hDC, m_diFore) ) return;
	}

	void CProgressUI::PaintBkImage(HDC hDC)
	{
		RECT rc = { 0 };
		rc.right = m_rcItem.right - m_rcItem.left;
		rc.bottom = m_rcItem.bottom - m_rcItem.top;

		rc.top += m_rcImgPadding.top;
		rc.left += m_rcImgPadding.left;
		rc.right -= m_rcImgPadding.right;
		rc.bottom -= m_rcImgPadding.bottom;
		m_diBk.rcDestOffset = rc;
		DrawImage(hDC, m_diBk);
	}

	SIZE CProgressUI::EstimateSize(SIZE szAvailable)
	{
		if (m_cxyFixed.cy == 0) return CDuiSize(m_cxyFixed.cx, m_pManager->GetFontInfo(GetFont())->tm.tmHeight + 8);
		return CControlUI::EstimateSize(szAvailable);
	}
}
