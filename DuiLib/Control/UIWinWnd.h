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
		BOOL Attach(HWND hWndNew);
		HWND Detach();
		void DieWithControl(BOOL bDieWithControl);
	protected:
		HWND m_hWnd;
		BOOL m_bDieWithControl;//�Ƿ����ſؼ����ٵ�ʱ��һ��Close

	};
}


