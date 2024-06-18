#include "stdafx.h"
#include "UIIcon.h"
#include <string>
#include <sstream> 
#include <shlwapi.h>

namespace DuiLib
{
	CIconUI::CIconUI()
	{
		m_bCircleMode = false;
		m_pImage = nullptr;
		m_bSetCursor = true;
		m_rtIconPadding.left = m_rtIconPadding.right = m_rtIconPadding.top = m_rtIconPadding.bottom = 0;
	}


	CIconUI::~CIconUI()
	{
		if (m_pImage)
			delete m_pImage;
		m_pImage = nullptr;
	}

	bool IsIcoFile(LPCTSTR szfile)
	{
#ifdef _UNICODE
		std::wstring strimg_temp = szfile;
#else
		std::string strimg_temp = szfile;
#endif
		
		size_t ifind = strimg_temp.rfind(_T("."));
		if (ifind != std::string::npos)
			strimg_temp = strimg_temp.substr(ifind);
		if (strimg_temp == _T(".ico"))
			return true;
		return false;
	}

	LPCTSTR CIconUI::GetClass() const
	{
		return DUI_CTR_ICON;
	}

	LPVOID CIconUI::GetInterface(LPCTSTR pstrName)
	{
		if (_tcscmp(pstrName, DUI_CTR_ICON) == 0) return static_cast<CIconUI*>(this);
		return __super::GetInterface(pstrName);
	}

	UINT CIconUI::GetControlFlags() const
	{
		return (IsKeyboardEnabled() ? UIFLAG_TABSTOP : 0) | ((IsEnabled() && m_bSetCursor) ? UIFLAG_SETCURSOR : 0);
	}

	void CIconUI::SetIconPaddding(RECT rtPaddding)
	{
		m_rtIconPadding = rtPaddding;
		Invalidate();
	}

	RECT CIconUI::GetIconPaddding()
	{
		return m_rtIconPadding;
	}

	void CIconUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if (_tcscmp(pstrName, _T("icopadding")) == 0) {
			RECT rcPadding = { 0 };
			LPTSTR pstr = NULL;
			rcPadding.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);
			rcPadding.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
			rcPadding.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);
			rcPadding.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);
			SetIconPaddding(rcPadding);
		}
		else if (_tcscmp(pstrName, _T("bkimage")) == 0) SetBkImage(pstrValue);
		else if (_tcscmp(pstrName, _T("circlemode")) == 0) {
			SetCircleMode(_tcscmp(pstrValue, _T("true")) == 0);
		}
		else
			__super::SetAttribute(pstrName, pstrValue);
	}

	void CIconUI::AttachIcon(HICON hicon)
	{
		if (m_pImage)
			delete m_pImage;
		m_pImage = nullptr;
		m_pImage = Bitmap::FromHICON(hicon);
		Invalidate();
	}

	void CIconUI::SetBkImage(LPCTSTR pStrImage)
	{
		if (pStrImage == nullptr) return;

		if (m_strBkImage != pStrImage)
		{
			m_strBkImage = pStrImage;
			if (m_pImage)
				delete m_pImage;
			m_pImage = nullptr;
		}
		
		if (m_pImage == nullptr)
		{
			std::vector<BYTE> res_data = CRenderEngine::LoadResData(pStrImage);
			if (!res_data.empty())
			{
				IStream* stream = SHCreateMemStream((BYTE*)(&res_data[0]), res_data.size());
				if (stream)
				{
					m_pImage = Image::FromStream(stream);
					stream->Release();
				}
			}
		}
		
		Invalidate();
	}

	void CIconUI::PaintText(HDC hDC)
	{
		if (IsFocused()) m_uButtonState |= UISTATE_FOCUSED;
		else m_uButtonState &= ~UISTATE_FOCUSED;
		if (!IsEnabled()) m_uButtonState |= UISTATE_DISABLED;
		else m_uButtonState &= ~UISTATE_DISABLED;

		if (m_dwTextColor == 0) m_dwTextColor = m_pManager->GetDefaultFontColor();
		if (m_dwDisabledTextColor == 0) m_dwDisabledTextColor = m_pManager->GetDefaultDisabledColor();

		if (m_sText.IsEmpty()) return;
		int nLinks = 0;
		RECT rc = m_rcItem;
		rc.left += m_rcTextPadding.left;
		rc.right -= m_rcTextPadding.right;
		rc.top += m_rcTextPadding.top;
		rc.bottom -= m_rcTextPadding.bottom;

		DWORD clrColor = IsEnabled() ? m_dwTextColor : m_dwDisabledTextColor;

		if (((m_uButtonState & UISTATE_PUSHED) != 0) && (GetPushedTextColor() != 0))
			clrColor = GetPushedTextColor();
		else if (((m_uButtonState & UISTATE_HOT) != 0) && (GetHotTextColor() != 0))
			clrColor = GetHotTextColor();
		else if (((m_uButtonState & UISTATE_FOCUSED) != 0) && (GetFocusedTextColor() != 0))
			clrColor = GetFocusedTextColor();

		__super::PaintText(hDC, clrColor);
	}

	RECT CIconUI::GetIconRect()
	{
		RECT rtItem = { m_rcItem.left + m_rtIconPadding.left, m_rcItem.top + m_rtIconPadding.top, m_rcItem.right - m_rtIconPadding.right, m_rcItem.bottom - m_rtIconPadding.bottom };
		return rtItem;
	}

	void CIconUI::SetCursorFlagUsed(bool bUse)
	{
		m_bSetCursor = bUse;
	}

	void CIconUI::PaintStatusImage(HDC hDC)
	{
		if ((m_uButtonState & UISTATE_HOT) && !(m_uButtonState & UISTATE_DISABLED) && m_dwHotBkColor != 0) {
			CRenderEngine::DrawColor(hDC, m_rcPaint, GetAdjustColor(m_dwHotBkColor));
		}
		//优先Icon
		if (m_pImage == nullptr)
		{
			return __super::PaintStatusImage(hDC);
		}
		RECT rt = GetIconRect();
		if (isCircleMode())
		{
			//计算圆形图片剪切位置，防止图片被压缩变形
			int nwidth = m_pImage->GetWidth() <= m_pImage->GetHeight() ? m_pImage->GetWidth() : m_pImage->GetHeight();
			Bitmap b(nwidth, nwidth);
			Graphics g(&b);
			g.SetSmoothingMode(SmoothingModeHighSpeed);
			g.FillEllipse(&TextureBrush(m_pImage, WrapModeClamp, (m_pImage->GetWidth() - nwidth)/2, (m_pImage->GetHeight() - nwidth) / 2, nwidth, nwidth), 0, 0, nwidth, nwidth);

			Graphics gg(hDC);
			gg.SetSmoothingMode(SmoothingModeHighSpeed);
			gg.DrawImage(&b, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top);
		}
		else
		{
			Graphics gg(hDC);
			gg.DrawImage(m_pImage, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top);
		}
	}

	bool CIconUI::DrawImage(HDC hDC, TDrawInfo& drawInfo)
	{
		if (!isCircleMode())
		{
			RECT rcIcon = GetIconRect();
			rcIcon.left -= m_rcItem.left;
			rcIcon.top -= m_rcItem.top;
			rcIcon.right -= m_rcItem.left;
			rcIcon.bottom -= m_rcItem.top;
			drawInfo.rcDestOffset = rcIcon;
			return CRenderEngine::DrawImage(hDC, m_pManager, m_rcItem, m_rcPaint, drawInfo);
		}

		//填充pImageInfo信息
		if (drawInfo.pImageInfo == nullptr)
		{
			RECT rtItem = { -1, -1, 0, 0 };
			CRenderEngine::DrawImage(hDC, m_pManager, rtItem, m_rcPaint, drawInfo);
		}
		if (drawInfo.pImageInfo)
		{
			RECT rt = GetIconRect();
			Bitmap img(drawInfo.pImageInfo->hBitmap, nullptr);
			Bitmap b(img.GetWidth(), img.GetHeight());
			Graphics g(&b);
			g.SetSmoothingMode(SmoothingModeHighSpeed);
			g.FillEllipse(&TextureBrush(&img), 0, 0, img.GetWidth(), img.GetHeight());

			Graphics gg(hDC);
			gg.SetSmoothingMode(SmoothingModeHighSpeed);
			gg.DrawImage(&b, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top);
		}
		return drawInfo.pImageInfo != nullptr;
	}

	void CIconUI::SetCircleMode(bool bCircleMode)
	{
		if (m_bCircleMode != bCircleMode)
		{
			m_bCircleMode = bCircleMode;
			Invalidate();
		}
	}

	bool CIconUI::isCircleMode()
	{
		return m_bCircleMode;
	}

	void CIconUI::DoEvent(TEventUI& event)
	{
		if (event.Type == UIEVENT_SETCURSOR)
		{
			RECT rtIcon = GetIconRect();
			if (IsEnabled() && ::PtInRect(&rtIcon, event.ptMouse)) {
				::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
			}
			else
			{
				CControlUI::DoEvent(event);
			}
			return;
		}
		__super::DoEvent(event);
	}
};