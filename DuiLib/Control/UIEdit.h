#ifndef __UIEDIT_H__
#define __UIEDIT_H__

#pragma once

namespace DuiLib
{
	typedef bool(*PCONTROLINPUT)(TCHAR c);

	class CEditWnd;
	class DUILIB_API CEditUI : public CLabelUI
	{
		friend class CEditWnd;
	public:
		CEditUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;
		HWND GetNativeWindow() const;

		///> Edit的输入控制
		void SetControlInput(PCONTROLINPUT inputcontrol);
		void SetEnabled(bool bEnable = true);
		void SetDecimal(bool bDecimal = false);//是否只允许输入带有小数点的数字eg:3.14
		bool IsDecimal();
		void SetDigits(int ndigits);//后面保留位数
		int GetDigits();
		void SetText(LPCTSTR pstrText);
		void SetMaxChar(UINT uMax);
		UINT GetMaxChar();
		void SetReadOnly(bool bReadOnly);
		bool IsReadOnly() const;
		void SetPasswordMode(bool bPasswordMode);
		bool IsPasswordMode() const;
		void SetPasswordChar(TCHAR cPasswordChar);
		TCHAR GetPasswordChar() const;
		bool IsAutoSelAll();
		void SetAutoSelAll(bool bAutoSelAll);
		void SetNumberOnly(bool bNumberOnly);
		bool IsNumberOnly() const;
		int GetWindowStyls() const;
		HWND GetNativeEditHWND() const;

		LPCTSTR GetNormalImage();
		void SetNormalImage(LPCTSTR pStrImage);
		LPCTSTR GetHotImage();
		void SetHotImage(LPCTSTR pStrImage);
		LPCTSTR GetFocusedImage();
		void SetFocusedImage(LPCTSTR pStrImage);
		LPCTSTR GetDisabledImage();
		void SetDisabledImage(LPCTSTR pStrImage);
		void SetNativeEditBkColor(DWORD dwBkColor);
		DWORD GetNativeEditBkColor() const;

		void SetSel(long nStartChar, long nEndChar);
		void SetSelAll();
		void SetReplaceSel(LPCTSTR lpszReplace);

		int GetLowSel();
		int GetHignSel();
		void SetPos(RECT rc, bool bNeedInvalidate = true);
		void Move(SIZE szOffset, bool bNeedInvalidate = true);
		void SetVisible(bool bVisible = true);
		void SetInternVisible(bool bVisible = true);
		SIZE EstimateSize(SIZE szAvailable);
		void DoEvent(TEventUI& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		bool Activate();
		void PaintStatusImage(HDC hDC);
		void PaintText(HDC hDC);
	private:
		bool IsTextHavePoint();//当前数据是否有小数点
		int GetTextDigits(int nSelPos);//获取当前光标之前的数据小数点个数
	protected:
		PCONTROLINPUT m_pInputControl;
		CEditWnd* m_pWindow;
		UINT m_nDigits;
		UINT m_uMaxChar;
		bool m_bDecimal;
		bool m_bReadOnly;
		bool m_bPasswordMode;
		bool m_bAutoSelAll;
		TCHAR m_cPasswordChar;
		UINT m_uButtonState;
		DWORD m_dwEditbkColor;
		int m_iWindowStyls;

		TDrawInfo m_diNormal;
		TDrawInfo m_diHot;
		TDrawInfo m_diFocused;
		TDrawInfo m_diDisabled;
	};
}
#endif // __UIEDIT_H__