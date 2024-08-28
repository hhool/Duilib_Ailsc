#ifndef __UIALIGNLAYOUT_H__
#define __UIALIGNLAYOUT_H__

#pragma once
/*
排列布局，仅限一个子控件，
align="left" "right" "center"
valign="top" "bottom" "center"
*/
namespace DuiLib
{
	class DUILIB_API CAlignLayoutUI : public CContainerUI
	{
	public:
		CAlignLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);


		void SetPos(RECT rc, bool bNeedInvalidate = true);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void SetAlign(int align = DT_CENTER);
	private:
		int m_align;//默认居中

	};
}
#endif // __UITABLAYOUT_H__
