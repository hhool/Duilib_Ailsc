#pragma once

namespace DuiLib
{
	class UILIB_API CWinWndUI :
		public CControlUI
	{
	public:
		CWinWndUI();
		virtual void SetInternVisible(bool bVisible = true);
		virtual void SetPos(RECT rc);
		BOOL Attach(HWND hWndNew);
		HWND Detach();
	protected:
		HWND m_hWnd;

	};
}


