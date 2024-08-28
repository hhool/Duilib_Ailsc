#pragma once

namespace DuiLib
{
	class DUILIB_API CWinWndUI :
		public CControlUI
	{
	public:
		CWinWndUI(BOOL bDieWithControl = TRUE);
		~CWinWndUI();

		virtual LPCTSTR GetClass() const;
		virtual LPVOID GetInterface(LPCTSTR pstrName);
		virtual void Move(SIZE szOffset, bool bNeedInvalidate = true);
		virtual void SetInternVisible(bool bVisible = true);
		virtual void SetPos(RECT rc, bool bNeedInvalidate = true);
		virtual bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
		BOOL Attach(HWND hWndNew);
		HWND Detach();
		void DieWithControl(BOOL bDieWithControl);
	protected:
		HWND m_hWnd;
		BOOL m_bDieWithControl;//是否随着控件销毁的时候一起Close

	};
}


