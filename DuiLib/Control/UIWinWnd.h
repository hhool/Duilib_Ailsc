#pragma once

namespace DuiLib
{
	class UILIB_API CWinWndUI :
		public CControlUI
	{
	public:
		CWinWndUI(BOOL bDieWithControl = TRUE);
		~CWinWndUI();
		virtual void SetInternVisible(bool bVisible = true);
		virtual void SetPos(RECT rc);
		BOOL Attach(HWND hWndNew);
		HWND Detach();
		void DieWithControl(BOOL bDieWithControl);
	protected:
		HWND m_hWnd;
		BOOL m_bDieWithControl;//是否随着控件销毁的时候一起Close

	};
}


