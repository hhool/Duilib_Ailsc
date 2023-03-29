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
		//�Ƿ�ʹ��Բ��ģʽ
		void SetCircleMode(bool bCircleMode);
		bool isCircleMode();
		void DoEvent(TEventUI& event);
		bool DrawImage(HDC hDC, TDrawInfo& drawInfo);
		RECT GetIconRect();
		void SetCursorFlagUsed(bool bUse);

		static CDuiStringPtrMap m_IconData;
	private:
		RECT m_rtIconPadding;
		Image *m_pImage;
		bool m_isFromHicon;
		bool m_bSetCursor;
		bool m_bCircleMode;//Բ��ģʽ
	};
};

#endif //__UIICON_H__

