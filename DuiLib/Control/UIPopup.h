#ifndef __UIPOPUPUI_H__
#define __UIPOPUPUI_H__

#pragma once
/*
add by jefcat
date:20170315
note:实现多功能悬浮窗口，需要设置弹出窗口的大小以及弹出窗口需要的xml
由于弹出窗口样式以及功能的不确定性，所以需要由外部从CCompositeLayoutUI派生控件，控制事件处理。
CPopupUI：：SetCreatePopupUI设置创建的对象,否则默认创建ChildLayoutUI
弹出窗口所有的事件都在派生里面处理，或者外部窗口处理

xml:
eg:<Popup name="DateTime" popboxsize="177,192"  popxml="skin/popup/DateUI/DateTime.xml" direct="bottom" />

具体Demo：see PopupUIDemo 封装的日期控件
*/
namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//
typedef CUIFunctionalLayout *(*CRETAE_POPUP_UI)();
class CPopupWnd;
class DUILIB_API CPopupUI : public CButtonUI
{
	friend class CPopupWnd;
public:
	CPopupUI();
	~CPopupUI();
    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
	void DoEvent(TEventUI& event);
    void DoInit();
    UINT GetControlFlags() const;
	bool Activate();
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	///>设置动态创建PopupUI对象
	void SetCreatePopupUI(CRETAE_POPUP_UI pCreateUI);
	//设置弹出窗口的大小
	SIZE GetPopBoxSize();
	void SetPopBoxSize(SIZE szDropBoxSize);
	//设置弹出窗口加载的xml
	void SetPopupXml(const CDuiString &strXml);
	const CDuiString GetPopupXml();
	//设置弹出窗口的首要弹出方向
	void SetDirect(bool bTop);
	bool IsTopDirect();

private:
	CUIFunctionalLayout *CreatePopUI();
private:
	CPopupWnd *m_pWindow;
	SIZE m_szDropBoxSize;//(200,100)
	CDuiString m_strPopXml;
	bool m_bTopDirect;//是否以向上弹出为首要位置
	CRETAE_POPUP_UI m_pPopUICreate;
};

} // namespace DuiLib

#endif // __UICOMBO_H__
