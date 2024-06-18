#ifndef __UIICON_H__
#define __UIICON_H__

namespace DuiLib
{
	class DUILIB_API CIconUI :public CButtonUI
	{
	public:
		CIconUI();
		~CIconUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;
		void AttachIcon(HICON hicon);
		void SetBkImage(LPCTSTR pStrImage);
		void PaintText(HDC hDC);
		void PaintStatusImage(HDC hDC);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void SetIconPaddding(RECT rtPaddding);
		RECT GetIconPaddding();
		//是否使用圆角模式
		void SetCircleMode(bool bCircleMode);
		bool isCircleMode();
		void DoEvent(TEventUI& event);
		bool DrawImage(HDC hDC, TDrawInfo& drawInfo);
		RECT GetIconRect();
		void SetCursorFlagUsed(bool bUse);
	private:
		RECT m_rtIconPadding;
		Gdiplus::Image *m_pImage;
		CDuiString m_strBkImage;
		bool m_bSetCursor;
		bool m_bCircleMode;//圆角模式
	};
};

#endif //__UIICON_H__

