#ifndef __UIGRIDLAYOUT_H__
#define __UIGRIDLAYOUT_H__

#pragma once
/*
类网格Grid布局，需要指定列数和item大小
*/
namespace DuiLib
{
	class DUILIB_API CGridLayoutUI : public CContainerUI
	{
	public:
		CGridLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		virtual bool Add(CControlUI* pControl);
		virtual bool AddAt(CControlUI* pControl, int iIndex);
		CControlUI* AddTemplate();
		CControlUI* AddTemplateAt(int iIndex);
		void SetPos(RECT rc, bool bNeedInvalidate = true);

		int GetFixedColumns() const;
		void SetFixedColumns(int iColums);
		int GetChildVPadding() const;
		void SetChildVPadding(int iPadding);
		//如果字符串以<开头则认为是xml字符串，否则认为是文件
		void SetItemTemplateXml(CDuiString xml);

		SIZE GetItemSize() const;
		void SetItemSize(SIZE szSize);
		int GetColumns() const;
		int GetRows() const;
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	protected:
		SIZE m_szItem;
		int m_nColumns;
		int m_nRows;

		int m_nColumnsFixed;
		int m_iChildVPadding;
		bool m_bIgnoreItemPadding;
		CDuiString m_ItemtemplateXml;
	};
}
#endif // __UITILELAYOUT_H__
