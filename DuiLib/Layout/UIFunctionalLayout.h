#ifndef _FUNCTIONALUI_h__
#define _FUNCTIONALUI_h__
#pragma once
/*20161108
Note：对布局进行功能性封装,包括控件的自己事件响应
例如日期控件，对日期进行+ - 跳转操作等都封控在内部
*/
namespace DuiLib
{
class CPopupUI;
class DUILIB_API CUIFunctionalLayout
	: public CChildLayoutUI
	, public INotifyUI
{
public:
	CUIFunctionalLayout(void);
	virtual ~CUIFunctionalLayout(void);

	virtual LPVOID GetInterface(LPCTSTR pstrName);
	virtual LPCTSTR GetClass() const;

	virtual void DoInit();
	virtual void Notify(TNotifyUI& msg);

	//初始化CControlUI的UI信息
	virtual void initUIData(CControlUI *m_pOowner);
};

}

#endif // CompositeUI_h__
