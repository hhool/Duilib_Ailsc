#include "stdafx.h"
#include "UIAlignLayout.h"

namespace DuiLib
{
	CAlignLayoutUI::CAlignLayoutUI() :m_align(DT_CENTER|DT_VCENTER)
	{
	}

	LPCTSTR CAlignLayoutUI::GetClass() const
	{
		return DUI_CTR_ALIGNLAYOUT;
	}

	LPVOID CAlignLayoutUI::GetInterface(LPCTSTR pstrName)
	{
		if (_tcscmp(pstrName, DUI_CTR_ALIGNLAYOUT) == 0) return static_cast<CAlignLayoutUI*>(this);
		return CContainerUI::GetInterface(pstrName);
	}

	void CAlignLayoutUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if (_tcscmp(pstrName, _T("align")) == 0)
		{
			if (_tcscmp(pstrValue, _T("left")) == 0)
			{
				m_align &= ~(DT_CENTER | DT_RIGHT);
				m_align |= DT_LEFT;
			}
			else if (_tcscmp(pstrValue, _T("right")) == 0)
			{
				m_align &= ~(DT_CENTER | DT_LEFT);
				m_align |= DT_RIGHT;
			}
			else if (_tcscmp(pstrValue, _T("center")) == 0)
			{
				m_align &= ~(DT_LEFT | DT_RIGHT);
				m_align |= DT_CENTER;
			}
		}
		else if (_tcscmp(pstrName, _T("valign")) == 0)
		{
			if (_tcscmp(pstrValue, _T("top")) == 0)
			{
				m_align &= ~(DT_VCENTER | DT_BOTTOM);
				m_align |= DT_TOP;
			}
			else if (_tcscmp(pstrValue, _T("bottom")) == 0)
			{
				m_align &= ~(DT_VCENTER | DT_TOP);
				m_align |= DT_BOTTOM;
			}
			else if (_tcscmp(pstrValue, _T("center")) == 0)
			{
				m_align &= ~(DT_LEFT | DT_RIGHT);
				m_align |= DT_VCENTER;
			}
		}
		else CContainerUI::SetAttribute(pstrName, pstrValue);
	}

	void CAlignLayoutUI::SetAlign(int align)
	{
		if (m_align != align)
		{
			m_align = align;
			NeedParentUpdate();
		}
	}

	void CAlignLayoutUI::SetPos(RECT rc, bool bNeedInvalidate)
	{
		CControlUI::SetPos(rc, bNeedInvalidate);
		rc = m_rcItem;

		// Adjust for inset
		rc.left += m_rcInset.left;
		rc.top += m_rcInset.top;
		rc.right -= m_rcInset.right;
		rc.bottom -= m_rcInset.bottom;

		for (int i = 0; i < m_items.GetSize();++i)
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_items[i]);
			if(!pControl->IsVisible()) continue;;
			if (pControl->IsFloat()) 
			{
				SetFloatPos(0);
				continue;
			}
	
			RECT rcPadding = pControl->GetPadding();
			rc.left += rcPadding.left;
			rc.top += rcPadding.top;
			rc.right -= rcPadding.right;
			rc.bottom -= rcPadding.bottom;

			SIZE szAvailable = { rc.right - rc.left, rc.bottom - rc.top };

			SIZE sz = pControl->EstimateSize(szAvailable);
			if( sz.cx == 0 ) {
				sz.cx = MAX(0, szAvailable.cx);
			}
			if( sz.cx < pControl->GetMinWidth() ) sz.cx = pControl->GetMinWidth();
			if( sz.cx > pControl->GetMaxWidth() ) sz.cx = pControl->GetMaxWidth();

			if(sz.cy == 0) {
				sz.cy = MAX(0, szAvailable.cy);
			}
			if( sz.cy < pControl->GetMinHeight() ) sz.cy = pControl->GetMinHeight();
			if( sz.cy > pControl->GetMaxHeight() ) sz.cy = pControl->GetMaxHeight();

			//此时模式为LEFT|TOP
			RECT rcCtrl = { rc.left, rc.top, rc.left + sz.cx, rc.top + sz.cy};
			//如果右对齐
			if (m_align & DT_RIGHT && sz.cx < szAvailable.cx)
			{
				rcCtrl.right = rc.right;
				rcCtrl.left = rcCtrl.right - sz.cx;
			}
			else if (m_align & DT_CENTER && sz.cx < szAvailable.cx)
			{
				rcCtrl.left += (szAvailable.cx - sz.cx)/2;
				rcCtrl.right = rcCtrl.left + sz.cx;
			}

			//底部对齐
			if (m_align & DT_BOTTOM && sz.cy < szAvailable.cy)
			{
				rcCtrl.bottom = rc.bottom;
				rcCtrl.top = rcCtrl.bottom - sz.cy;
			}
			else if (m_align & DT_VCENTER && sz.cy < szAvailable.cy)
			{
				rcCtrl.top += (szAvailable.cy - sz.cy) / 2;
				rcCtrl.bottom = rcCtrl.top + sz.cy;
			}
			pControl->SetPos(rcCtrl, false);
		}
	}
}
