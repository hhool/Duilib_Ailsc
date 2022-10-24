#ifndef __UIGRIDLAYOUT_H__
#define __UIGRIDLAYOUT_H__

#pragma once
/*
������Grid���֣���Ҫָ��������item��С
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
		//����ַ�����<��ͷ����Ϊ��xml�ַ�����������Ϊ���ļ�
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
