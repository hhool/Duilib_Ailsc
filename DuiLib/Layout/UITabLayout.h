#ifndef __UITABLAYOUT_H__
#define __UITABLAYOUT_H__

#pragma once
/*
TabLayout仅仅包括展示区，不包括标签区域，标签区域自己定制
*/
namespace DuiLib
{
	class DUILIB_API CTabLayoutUI : public CContainerUI
	{
	public:
		CTabLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		bool Add(CControlUI* pControl);
		bool AddAt(CControlUI* pControl, int iIndex);
		bool Remove(CControlUI* pControl, bool bDoNotDestroy=false);
		void RemoveAll();
		int GetCurSel() const;
		bool SelectItem(int iIndex, bool bTriggerEvent=true);
		bool SelectItem(CControlUI* pControl,  bool bTriggerEvent=true);

		void SetPos(RECT rc, bool bNeedInvalidate = true);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	protected:
		int m_iCurSel;
	};
}
#endif // __UITABLAYOUT_H__
