#ifndef __UITREEVIEW_H__
#define __UITREEVIEW_H__

#include <vector>
using namespace std;

#pragma once

namespace DuiLib
{
	class CTreeViewUI;
	class CCheckBoxUI;
	class CLabelUI;
	class COptionUI;

	class DUILIB_API CTreeNodeUI : public CListContainerElementUI
	{
		friend class CTreeViewUI;
	public:
		CTreeNodeUI(CTreeNodeUI* _ParentNode = NULL);
		~CTreeNodeUI(void);

	public:
		LPCTSTR GetClass() const;
		LPVOID	GetInterface(LPCTSTR pstrName);
		void	DoEvent(TEventUI& event);
		void	Invalidate();
		bool	Select(bool bSelect = true, bool bTriggerEvent=true);
		void	SetVisible(bool bVisible = true);
		void	SetUserVisible(bool _IsVisible);
		bool	GetUserVisible();
		bool	Add(CControlUI* _pTreeNodeUI);
		bool	AddAt(CControlUI* pControl, int iIndex);
		void	SetItemFont(int index, bool always);
		void	SetItemText(LPCTSTR pstrValue);
		CDuiString	GetItemText();
		void	CheckBoxSelected(bool _Selected, bool bTriggerEvent = true);
		bool	IsCheckBoxSelected() const;
		bool	IsHasChild() const;
		long	GetTreeLevel() const;
		bool	AddChildNode(CTreeNodeUI* _pTreeNodeUI);
		bool	Remove(CControlUI* pControl);
		bool	RemoveAt(CTreeNodeUI* _pTreeNodeUI);
		void	SetParentNode(CTreeNodeUI* _pParentTreeNode);
		CTreeNodeUI* GetParentNode();
		long	GetCountChild();
		void	SetTreeView(CTreeViewUI* _CTreeViewUI);
		CTreeViewUI* GetTreeView();
		CTreeNodeUI* GetChildNode(int _nIndex);
		void	SetVisibleFolderBtn(bool _IsVisibled);
		bool	GetVisibleFolderBtn();
		void	SetVisibleCheckBtn(bool _IsVisibled);
		bool	GetVisibleCheckBtn();
		void	SetItemTextColor(DWORD _dwItemTextColor);
		DWORD	GetItemTextColor() const;
		void	SetItemHotTextColor(DWORD _dwItemHotTextColor);
		DWORD	GetItemHotTextColor() const;
		void	SetSelItemTextColor(DWORD _dwSelItemTextColor);
		DWORD	GetSelItemTextColor() const;
		void	SetSelItemHotTextColor(DWORD _dwSelHotItemTextColor);
		DWORD	GetSelItemHotTextColor() const;

		void	SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		CDuiPtrArray GetTreeNodes();

		int			 GetTreeIndex();
		int			 GetNodeIndex();

	private:
		void	SetVisibleTag(bool _IsVisible);
		bool	GetVisibleTag();
		CTreeNodeUI* GetLastNode();
		CTreeNodeUI* CalLocation(CTreeNodeUI* _pTreeNodeUI);
	public:
		CHorizontalLayoutUI*	GetTreeNodeHoriznotal() const {return pHoriz;};
		CCheckBoxUI*			GetFolderButton() const {return pFolderButton;};
		CLabelUI*				GetDottedLine() const {return pDottedLine;};
		CCheckBoxUI*			GetCheckBox() const {return pCheckBox;};
		COptionUI*				GetItemButton() const {return pItemButton;};

	private:
		long	m_iTreeLavel;
		bool	m_bUserVisible;
		bool	m_bVisableTag;
		bool	m_bIsCheckBox;
		DWORD	m_dwItemTextColor;
		DWORD	m_dwItemHotTextColor;
		DWORD	m_dwSelItemTextColor;
		DWORD	m_dwSelItemHotTextColor;

		CTreeViewUI*			pTreeView;
		CHorizontalLayoutUI*	pHoriz;
		CCheckBoxUI*			pFolderButton;
		CLabelUI*				pDottedLine;
		CCheckBoxUI*			pCheckBox;
		COptionUI*				pItemButton;

		CTreeNodeUI*			pParentTreeNode;

		CDuiPtrArray			mTreeNodes;
	};

	class DUILIB_API CTreeViewUI : public CListUI,public INotifyUI
	{
	public:
		CTreeViewUI(void);
		~CTreeViewUI(void);

	public:
		virtual LPCTSTR GetClass() const;
		virtual LPVOID	GetInterface(LPCTSTR pstrName);
        virtual bool Add(CControlUI* pControl);
        virtual bool AddAt(CControlUI* pControl, int iIndex);
        virtual bool Remove(CControlUI* pControl, bool bDoNotDestroy=false);
        virtual bool RemoveAt(int iIndex, bool bDoNotDestroy=false);
        virtual void RemoveAll();

        long AddAt(CTreeNodeUI* pControl, int iIndex);
        bool AddAt(CTreeNodeUI* pControl,CTreeNodeUI* _IndexNode);

		virtual bool OnCheckBoxChanged(void* param);
		virtual bool OnFolderChanged(void* param);
		virtual bool OnDBClickItem(void* param);
		virtual bool SetItemCheckBox(bool _Selected,CTreeNodeUI* _TreeNode = NULL);
		virtual void SetItemExpand(bool _Expanded,CTreeNodeUI* _TreeNode = NULL);
		virtual void Notify(TNotifyUI& msg);
		virtual void SetVisibleFolderBtn(bool _IsVisibled);
		virtual bool GetVisibleFolderBtn();
		virtual void SetVisibleCheckBtn(bool _IsVisibled);
		virtual bool GetVisibleCheckBtn();
		virtual void SetItemMinWidth(UINT _ItemMinWidth);
		virtual UINT GetItemMinWidth();
		virtual void SetItemTextColor(DWORD _dwItemTextColor);
		virtual void SetItemHotTextColor(DWORD _dwItemHotTextColor);
		virtual void SetSelItemTextColor(DWORD _dwSelItemTextColor);
		virtual void SetSelItemHotTextColor(DWORD _dwSelHotItemTextColor);
		virtual void SetItemFont(int index);
		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	private:
		UINT m_uItemMinWidth;
		bool m_bVisibleFolderBtn;
		bool m_bVisibleCheckBtn;
	};
}


#endif // __UITREEVIEW_H__
