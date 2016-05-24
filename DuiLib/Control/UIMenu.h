#ifndef __UIMENU_H__
#define __UIMENU_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "../Utils/observer_impl_base.hpp"

namespace DuiLib {

/////////////////////////////////////////////////////////////////////////////////////
//
struct ContextMenuParam
{
	// 1: remove all
	// 2: remove the sub menu
	WPARAM wParam;
	HWND hWnd;
};

enum MenuAlignment
{
	eMenuAlignment_Left = 1 << 1,
	eMenuAlignment_Top = 1 << 2,
	eMenuAlignment_Right = 1 << 3,
	eMenuAlignment_Bottom = 1 << 4,
};

typedef class ObserverImpl<BOOL, ContextMenuParam> ContextMenuObserver;
typedef class ReceiverImpl<BOOL, ContextMenuParam> ContextMenuReceiver;

extern ContextMenuObserver s_context_menu_observer;

class CListUI;
class CMenuUI : public CListUI
{
public:
	CMenuUI();
	~CMenuUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
	CControlUI *FindControl(LPCTSTR pstrSubControlName);
	virtual void DoEvent(TEventUI& event);
    virtual bool Add(CControlUI* pControl);
    virtual bool AddAt(CControlUI* pControl, int iIndex);
    virtual int GetItemIndex(CControlUI* pControl) const;
    virtual bool SetItemIndex(CControlUI* pControl, int iIndex);
    virtual bool Remove(CControlUI* pControl, bool bDoNotDestroy=false);
	SIZE EstimateSize(SIZE szAvailable);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
};

/////////////////////////////////////////////////////////////////////////////////////
//
class CMenuElementUI;
class DUILIB_API CMenuWnd : public CWindowWnd, public ContextMenuReceiver,public INotifyUI

{
public:
	CMenuWnd(CPaintManagerUI *pParentPm, HWND hParent = NULL);
	/*
	@param point 菜单位置
	@param pOwner 是属于哪个菜单的子菜单，如果不是则填NULL
	@param xml xml文件可是是资源xml也可以是文件xml
	@param pSkinType 资源文件类型 _T("xml")
	*/
	BOOL Init(POINT point, STRINGorID xml, LPCTSTR pSkinType = NULL, CMenuElementUI* pOwner = NULL);
	CMenuUI *GetMenuUI();
	void ShowWindow();
protected:
    LPCTSTR GetWindowClassName() const;
    void OnFinalMessage(HWND hWnd);
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL Receive(ContextMenuParam param);
	virtual void Notify(TNotifyUI& msg);
private:
	HWND m_hParent;
	POINT m_BasedPoint;
	STRINGorID m_xml;
	CDuiString m_sType;
    CPaintManagerUI m_pm;
    CMenuElementUI* m_pOwner;
    CMenuUI* m_pMenuUI;
	CPaintManagerUI *m_pParentPm;//Parent的PM 用于消息传递到外部
};

class CListContainerElementUI;
class DUILIB_API CMenuElementUI : public CListContainerElementUI
{
	friend CMenuWnd;
public:
    CMenuElementUI();
	~CMenuElementUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

	void DrawItemText(HDC hDC, const RECT& rcItem);

	SIZE EstimateSize(SIZE szAvailable);

	bool Activate();

	void DoEvent(TEventUI& event);


	CMenuWnd* GetMenuWnd();

	void CreateMenuWnd();

protected:
	CMenuWnd* m_pWindow;
};

} // namespace DuiLib

#endif // __UIMENU_H__
