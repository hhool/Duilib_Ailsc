#ifndef CompositeUI_h__
#define CompositeUI_h__
#pragma once
/*20161108
Note：混合布局，用于对布局进行功能性封装
功能性事件响应请从Notify派生
记得重写CreateControl DUI_CTR_COMPOSITELAYOUT 在这里创建对应的对象
*/
namespace DuiLib
{
class CPopupUI;
class DUILIB_API CCompositeLayoutUI
	: public CChildLayoutUI
	, public INotifyUI
{
public:
	CCompositeLayoutUI(void);
	virtual ~CCompositeLayoutUI(void);

	virtual LPVOID GetInterface(LPCTSTR pstrName);
	virtual LPCTSTR GetClass() const;

	virtual void AddNotifyFilter(INotifyUI *pFilter);
	virtual void RemoveNotifyFilter(INotifyUI *pFilter);

	virtual void DoInit();
	virtual void Notify(TNotifyUI& msg);

	///;just for PopupUI使用
	virtual void initUIData(CPopupUI *m_pOowner);//使用PopupUI的字符串初始化CChildLayoutUI
private:
	CDuiPtrArray m_arrayNotifyFilters;
};

}

#endif // CompositeUI_h__
