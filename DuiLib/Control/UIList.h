#ifndef __UILIST_H__
#define __UILIST_H__

#pragma once
#include "Layout/UIVerticalLayout.h"
#include "Layout/UIHorizontalLayout.h"

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

typedef int (CALLBACK *PULVCompareFunc)(UINT_PTR, UINT_PTR, UINT_PTR);

////////////////////////////////////#lilei 20160627 �����б�ӿ�/////////////////////////////////////////////////
//PULVirtualPrepareItem δ�����б�׼����������Ϊ����ʽ��
typedef CControlUI* (* PULVirtualItemFormat)();

class CListHeaderUI;
 
#define UILIST_MAX_COLUMNS 64

enum ESORT{ E_SORTNO, E_SORT_ASC, E_SORT_DESC, E_SORT_MAX };

struct DUICopyItem
{
	int nRow;
	int nCol;
	TCHAR *szText;
	int nszText;
};

typedef struct tagTListInfoUI
{
    int nColumns;
    RECT rcColumn[UILIST_MAX_COLUMNS];
    UINT uFixedHeight; 
    int nFont;
    UINT uTextStyle;
    RECT rcTextPadding;
    DWORD dwTextColor;
    DWORD dwBkColor;
    TDrawInfo diBk;
    bool bAlternateBk;
    DWORD dwSelectedTextColor;
    DWORD dwSelectedBkColor;
    TDrawInfo diSelected;
    DWORD dwHotTextColor;
    DWORD dwHotBkColor;
    TDrawInfo diHot;
    DWORD dwDisabledTextColor;
    DWORD dwDisabledBkColor;
    TDrawInfo diDisabled;
    int iHLineSize;
    DWORD dwHLineColor;
    int iVLineSize;
    DWORD dwVLineColor;
    bool bShowHtml;
    bool bMultiExpandable;
} TListInfoUI;


/////////////////////////////////////////////////////////////////////////////////////
//

class IListCallbackUI
{
public:
    virtual LPCTSTR GetItemText(CControlUI* pList, int iItem, int iSubItem) = 0;
};

class IListOwnerUI
{
public:
    virtual TListInfoUI* GetListInfo() = 0;
    virtual int GetCurSel() const = 0;
    virtual bool SelectItem(int iIndex, bool bTakeFocus = false, bool bTriggerEvent=true) = 0;
    virtual void DoEvent(TEventUI& event) = 0;
    virtual bool ExpandItem(int iIndex, bool bExpand = true) = 0;
    virtual int GetExpandedItem() const = 0;
};

class IListUI : public IListOwnerUI
{
public:
    virtual CListHeaderUI* GetHeader() const = 0;
    virtual CContainerUI* GetList() const = 0;
    virtual IListCallbackUI* GetTextCallback() const = 0;
    virtual void SetTextCallback(IListCallbackUI* pCallback) = 0;
};

class IListItemUI
{
public:
    virtual int GetIndex() const = 0;
    virtual void SetIndex(int iIndex) = 0;
    virtual int GetDrawIndex() const = 0;
    virtual void SetDrawIndex(int iIndex) = 0;
    virtual IListOwnerUI* GetOwner() = 0;
    virtual void SetOwner(CControlUI* pOwner) = 0;
    virtual bool IsSelected() const = 0;
    virtual bool Select(bool bSelect = true, bool bTriggerEvent=true) = 0;
    virtual bool IsExpanded() const = 0;
    virtual bool Expand(bool bExpand = true) = 0;
    virtual void DrawItemText(HDC hDC, const RECT& rcItem) = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//
class CListBodyUI;
class CListHeaderUI;
//֧�������б�
class DUILIB_API CListUI : public CVerticalLayoutUI, public IListUI
{
public:
    CListUI();

    LPCTSTR GetClass() const;
    UINT GetControlFlags() const;
    LPVOID GetInterface(LPCTSTR pstrName);
	///////////////////////////////�����б�ӿ� #liulei 20160627/////////////////////////////////////////
	//���ʹ���������б����ⲿ����Rmove,RemoveAt,Add,AddAt,RemoveAll ��Ч
	//> ��������е����ݸ�ʽ,��Ҫָ���иߣ�ԭ��������MFC�����
	void SetVirtualItemFormat(PULVirtualItemFormat vrtualitemfroamt);
	//> �����Ƿ�Ϊ�����ʾ����
	void SetVirtual(bool bUse = false);
	//> ����������ݸ���
	void SetVirtualItemCount(int nCountItem);
	bool IsUseVirtualList() const;
	//> ��ȡ�����и߶ȣ�����и߱��뱣��һ�£���֧�ֶ�̬�иߣ�
	int GetVirtualItemHeight();
	//> ��ȡ������ݸ���
	int GetVirtualItemCount() const;
	//> ����List���ݵ����а�,��Ҫ��Ӧ DUI_MSGTYPE_COPYITEM �¼� nMaxRowItemData ���ΪItem����ɵ����Text
	//>  bUserDefine �Ƿ�Ϊ�û��Զ������ݣ����ڸ��ӵ����ݽṹ��copy����ä�㣬��Ҫ�û��Զ���Copy
	//> bUserDefine ���ΪTRUE ��ᴥ�� DUI_MSGTYPE_COPYITEM Wparam ΪListItem Lparam ΪDUICopyItem��Ҫ�������ݵĵ�ַ��
	BOOL Copy(int nMaxRowItemData = 1024,bool bUserDefine = false);
	///> ����ѡ���еı��,�����Ǹ���Item��Tag�����
	void SetSelectControlTag(INT64 iControlTag);
	INT64 GetSelectControlTag();
	///> �Ƿ����������������Ż����Ż������������ݵ�ʱ��Item���ɼ���������֮��ָ�״̬������ˢ�´�����
	///> Ĭ�Ͽ���, �������Item ���� combo  �����ر��Ż�������combo��ʾ������
	void EnableVirtualOptimize(bool bEnableVirtualO = true);
	/////////////////////////////////////////////�����ǽӿ� #liulei 20161107//////////////////////////////////////////////////////
	void SetSort(int nIndex, ESORT esort, bool bTriggerEvent = false);
	int	 GetSortIndex();
	ESORT GetSortType();
	///////////////////////////////////////////////////////////////////////////////////////////////////////




    bool GetScrollSelect();
    void SetScrollSelect(bool bScrollSelect);
    int GetCurSel() const;
    bool SelectItem(int iIndex, bool bTakeFocus = false, bool bTriggerEvent=true);

    CControlUI* GetItemAt(int iIndex) const;
    int GetItemIndex(CControlUI* pControl) const;
    bool SetItemIndex(CControlUI* pControl, int iIndex);
    bool SetMultiItemIndex(CControlUI* pStartControl, int iCount, int iNewStartIndex);
    int GetCount() const;
	int GetItemCount() const;//��ȡʵ��Item�ĸ���
    bool Add(CControlUI* pControl);
    bool AddAt(CControlUI* pControl, int iIndex);
    bool Remove(CControlUI* pControl, bool bDoNotDestroy=false);
    bool RemoveAt(int iIndex, bool bDoNotDestroy=false);
    void RemoveAll();
	void ResetSortStatus();//�������б�ͷ����״̬
    void EnsureVisible(int iIndex);
    void Scroll(int dx, int dy);

    int GetChildPadding() const;
    void SetChildPadding(int iPadding);

    CListHeaderUI* GetHeader() const;  
    CContainerUI* GetList() const;
    TListInfoUI* GetListInfo();

    UINT GetItemFixedHeight();
    void SetItemFixedHeight(UINT nHeight);
    int GetItemFont(int index);
    void SetItemFont(int index);
    UINT GetItemTextStyle();
    void SetItemTextStyle(UINT uStyle);
    RECT GetItemTextPadding() const;
    void SetItemTextPadding(RECT rc);
    DWORD GetItemTextColor() const;
    void SetItemTextColor(DWORD dwTextColor);
    DWORD GetItemBkColor() const;
    void SetItemBkColor(DWORD dwBkColor);
    LPCTSTR GetItemBkImage() const;
    void SetItemBkImage(LPCTSTR pStrImage);
    bool IsAlternateBk() const;
    void SetAlternateBk(bool bAlternateBk);
    DWORD GetSelectedItemTextColor() const;
    void SetSelectedItemTextColor(DWORD dwTextColor);
    DWORD GetSelectedItemBkColor() const;
    void SetSelectedItemBkColor(DWORD dwBkColor);
    LPCTSTR GetSelectedItemImage() const;
    void SetSelectedItemImage(LPCTSTR pStrImage);
    DWORD GetHotItemTextColor() const;
    void SetHotItemTextColor(DWORD dwTextColor);
    DWORD GetHotItemBkColor() const;
    void SetHotItemBkColor(DWORD dwBkColor);
    LPCTSTR GetHotItemImage() const;
    void SetHotItemImage(LPCTSTR pStrImage);
    DWORD GetDisabledItemTextColor() const;
    void SetDisabledItemTextColor(DWORD dwTextColor);
    DWORD GetDisabledItemBkColor() const;
    void SetDisabledItemBkColor(DWORD dwBkColor);
    LPCTSTR GetDisabledItemImage() const;
    void SetDisabledItemImage(LPCTSTR pStrImage);
    int GetItemHLineSize() const;
    void SetItemHLineSize(int iSize);
    DWORD GetItemHLineColor() const;
    void SetItemHLineColor(DWORD dwLineColor);
    int GetItemVLineSize() const;
    void SetItemVLineSize(int iSize);
    DWORD GetItemVLineColor() const;
    void SetItemVLineColor(DWORD dwLineColor);
    bool IsItemShowHtml();
    void SetItemShowHtml(bool bShowHtml = true);

    void SetMultiExpanding(bool bMultiExpandable); 
    int GetExpandedItem() const;
    bool ExpandItem(int iIndex, bool bExpand = true);

	void SetPos(RECT rc, bool bNeedInvalidate = true);
	void Move(SIZE szOffset, bool bNeedInvalidate = true);
    void DoEvent(TEventUI& event);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    IListCallbackUI* GetTextCallback() const;
    void SetTextCallback(IListCallbackUI* pCallback);

    SIZE GetScrollPos() const;
    SIZE GetScrollRange() const;
    void SetScrollPos(SIZE szPos);
	void DrawVirtualItem(CControlUI *pControl, int nRow);
    void LineUp();
    void LineDown();
    void PageUp();
    void PageDown();
    void HomeUp();
    void EndDown();
    void LineLeft();
    void LineRight();
    void PageLeft();
    void PageRight();
    void HomeLeft();
    void EndRight();
    void EnableScrollBar(bool bEnableVertical = true, bool bEnableHorizontal = false);
    virtual CScrollBarUI* GetVerticalScrollBar() const;
    virtual CScrollBarUI* GetHorizontalScrollBar() const;
    bool SortItems(PULVCompareFunc pfnCompare, UINT_PTR dwData);

private:
	void ResizeVirtualItemBuffer();//��̬���������Ļ�����
	bool AddVirtualItem(CControlUI* pControl);
protected:
	INT64 m_iSelectControlTag;
	bool m_bUseVirtualList;
    bool m_bScrollSelect;
	bool m_bEnableVirtualO;//�Ƿ���������Ż�
    int m_iCurSel;
    int m_iExpandedItem;
    IListCallbackUI* m_pCallback;
    CListBodyUI* m_pList;
    CListHeaderUI* m_pHeader;
    TListInfoUI m_ListInfo;
	PULVirtualItemFormat  m_pVirutalItemFormat;//�������ݸ�ʽָ��
	int m_nVirtualItemHeight;
	int m_nVirtualItemCount;
};

/////////////////////////////////////////////////////////////////////////////////////
//
class CListHeaderItemUI;

class DUILIB_API CListHeaderUI : public CHorizontalLayoutUI
{
public:
	friend CListHeaderItemUI;
	CListHeaderUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
	bool Add(CControlUI* pControl);
	bool AddAt(CControlUI* pControl, int iIndex);
	void RemoveAll();
	bool Remove(CControlUI* pControl, bool bDoNotDestroy = false);
	bool RemoveAt(int iIndex, bool bDoNotDestroy = false);
	void SetVisible(bool bVisible = true);
	void SetItemVisible(int nIndex, bool bVisible = true, bool bInvalidate = true);
	void SetSort(int nIndex, ESORT esort, bool bTriggerEvent = false);
	int	 GetSortIndex();
	ESORT GetSortType();
    SIZE EstimateSize(SIZE szAvailable);

private:
	ESORT m_esrot;//��������
	int	  m_nsrot_index;//�����±�
};


/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListHeaderItemUI : public CContainerUI
{
public:
    CListHeaderItemUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
    UINT GetControlFlags() const;
    void SetEnabled(bool bEnable = true);
	void SetVisible(bool bVisible = true);
	bool IsDragable() const;
    void SetDragable(bool bDragable);
	DWORD GetSepWidth() const;
    void SetSepWidth(int iWidth);
	DWORD GetTextStyle() const;
    void SetTextStyle(UINT uStyle);
	DWORD GetTextColor() const;
    void SetTextColor(DWORD dwTextColor);
    DWORD GetSepColor() const;
    void SetSepColor(DWORD dwSepColor);
	void SetTextPadding(RECT rc);
	RECT GetTextPadding() const;
    void SetFont(int index);
    bool IsShowHtml();
    void SetShowHtml(bool bShowHtml = true);
    LPCTSTR GetNormalImage() const;
    void SetNormalImage(LPCTSTR pStrImage);
    LPCTSTR GetHotImage() const;
    void SetHotImage(LPCTSTR pStrImage);
    LPCTSTR GetPushedImage() const;
    void SetPushedImage(LPCTSTR pStrImage);
    LPCTSTR GetFocusedImage() const;
    void SetFocusedImage(LPCTSTR pStrImage);
    LPCTSTR GetSepImage() const;
    void SetSepImage(LPCTSTR pStrImage);

	/// ���ӱ�ͷ����ͼ��//////////////////////////////////////////////
	void SetEnabledSort(bool bEnableSort);
	void SetSort(ESORT esort, bool bTriggerEvent = true);
	ESORT GetSort();
	void SetSortAscImg(LPCTSTR pStrImage);
	void SetSortDescImg(LPCTSTR pStrImage);
	void SetSortWidth(int nSortWidht);
	void SetSortHeight(int nSrotHeight);
	//////////////////////////////////////////////////////////////

    void DoEvent(TEventUI& event);
    SIZE EstimateSize(SIZE szAvailable);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
    RECT GetThumbRect() const;
	RECT GetSortRect() const;
    void PaintText(HDC hDC);
    void PaintStatusImage(HDC hDC);
private:
	void SetSortStatus(ESORT esort, bool bTriggerEvent = false);
protected:
    POINT ptLastMouse;
    bool m_bDragable;
	bool m_bEnablebSort;
    UINT m_uButtonState;
    int m_iSepWidth;
    DWORD m_dwTextColor;
    DWORD m_dwSepColor;
    int m_iFont;
    UINT m_uTextStyle;
    bool m_bShowHtml;
	RECT m_rcTextPadding;
    TDrawInfo m_diNormal;
    TDrawInfo m_diHot;
    TDrawInfo m_diPushed;
    TDrawInfo m_diFocused;
    TDrawInfo m_diSep;
	TDrawInfo m_diAscSort;
	TDrawInfo m_diDescSort;
	ESORT m_esrot;
	int m_nSortWidth;
	int m_nSortHeight;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListElementUI : public CControlUI, public IListItemUI
{
public:
    CListElementUI();

    LPCTSTR GetClass() const;
    UINT GetControlFlags() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    void SetEnabled(bool bEnable = true);

    int GetIndex() const;
    void SetIndex(int iIndex);
    int GetDrawIndex() const;
    void SetDrawIndex(int iIndex);

    IListOwnerUI* GetOwner();
    void SetOwner(CControlUI* pOwner);
    void SetVisible(bool bVisible = true);

    bool IsSelected() const;
    bool Select(bool bSelect = true, bool bTriggerEvent=true);
    bool IsExpanded() const;
    bool Expand(bool bExpand = true);

    void Invalidate(); // ֱ��CControl::Invalidate�ᵼ�¹�����ˢ�£���д����ˢ������
    bool Activate();

    void DoEvent(TEventUI& event);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    void DrawItemBk(HDC hDC, const RECT& rcItem);

protected:
    int m_iIndex;
    int m_iDrawIndex;
    bool m_bSelected;
    UINT m_uButtonState;
    IListOwnerUI* m_pOwner;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListLabelElementUI : public CListElementUI
{
public:
    CListLabelElementUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    void SetOwner(CControlUI* pOwner);

    void SetFixedWidth(int cx);
    void SetFixedHeight(int cy);
    void SetText(LPCTSTR pstrText);

    void DoEvent(TEventUI& event);
    SIZE EstimateSize(SIZE szAvailable);
    bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

    void DrawItemText(HDC hDC, const RECT& rcItem);

protected:
    SIZE    m_cxyFixedLast;
    bool    m_bNeedEstimateSize;

    SIZE    m_szAvailableLast;
    UINT    m_uFixedHeightLast; 
    int     m_nFontLast;
    UINT    m_uTextStyleLast;
    RECT    m_rcTextPaddingLast;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListTextElementUI : public CListLabelElementUI
{
public:
    CListTextElementUI();
    ~CListTextElementUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
    UINT GetControlFlags() const;
	int GetCount() const;
    LPCTSTR GetText(int iIndex) const;
    void SetText(int iIndex, LPCTSTR pstrText,UINT uTextStyle = 0);

    void SetOwner(CControlUI* pOwner);
    CDuiString* GetLinkContent(int iIndex);

    void DoEvent(TEventUI& event);
    SIZE EstimateSize(SIZE szAvailable);

    void DrawItemText(HDC hDC, const RECT& rcItem);

protected:
    enum { MAX_LINK = 8 };
    int m_nLinks;
    RECT m_rcLinks[MAX_LINK];
    CDuiString m_sLinks[MAX_LINK];
    int m_nHoverLink;
    IListUI* m_pOwner;
    CDuiPtrArray m_aTexts;
	UINT m_uTextsStyle[UILIST_MAX_COLUMNS];
    CDuiString m_sTextLast;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListContainerElementUI : public CContainerUI, public IListItemUI
{
public:
    CListContainerElementUI();

    LPCTSTR GetClass() const;
    UINT GetControlFlags() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    int GetIndex() const;
    void SetIndex(int iIndex);
    int GetDrawIndex() const;
    void SetDrawIndex(int iIndex);

    IListOwnerUI* GetOwner();
    void SetOwner(CControlUI* pOwner);
    void SetVisible(bool bVisible = true);
    void SetEnabled(bool bEnable = true);

    bool IsSelected() const;
    bool Select(bool bSelect = true, bool bTriggerEvent=true);
    bool IsExpandable() const;
    void SetExpandable(bool bExpandable);
    bool IsExpanded() const;
    bool Expand(bool bExpand = true);

    void Invalidate(); // ֱ��CControl::Invalidate�ᵼ�¹�����ˢ�£���д����ˢ������
    bool Activate();

    void DoEvent(TEventUI& event);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
    bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

    void DrawItemText(HDC hDC, const RECT& rcItem);    
    void DrawItemBk(HDC hDC, const RECT& rcItem);

    SIZE EstimateSize(SIZE szAvailable);

protected:
    int m_iIndex;
    int m_iDrawIndex;
    bool m_bSelected;
    bool m_bExpandable;
    bool m_bExpand;
    UINT m_uButtonState;
    IListOwnerUI* m_pOwner;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListHBoxElementUI : public CListContainerElementUI
{
public:
    CListHBoxElementUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    void SetPos(RECT rc, bool bNeedInvalidate = true);
    bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
};

} // namespace DuiLib

#endif // __UILIST_H__
