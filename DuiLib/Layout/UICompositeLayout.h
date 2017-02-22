#ifndef CompositeUI_h__
#define CompositeUI_h__
#pragma once
/*20161108
Note����ϲ��֣����ڶԲ��ֽ��й����Է�װ
�������¼���Ӧ���Notify����
�ǵ���дCreateControl DUI_CTR_COMPOSITELAYOUT �����ﴴ����Ӧ�Ķ���
*/
namespace DuiLib
{

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
private:
	CDuiPtrArray m_arrayNotifyFilters;
};

}

#endif // CompositeUI_h__
