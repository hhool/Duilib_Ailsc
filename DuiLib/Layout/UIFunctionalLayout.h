#ifndef _FUNCTIONALUI_h__
#define _FUNCTIONALUI_h__
#pragma once
/*20161108
Note���Բ��ֽ��й����Է�װ,�����ؼ����Լ��¼���Ӧ
�������ڿؼ��������ڽ���+ - ��ת�����ȶ�������ڲ�
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

	//��ʼ��CControlUI��UI��Ϣ
	virtual void initUIData(CControlUI *m_pOowner);
};

}

#endif // CompositeUI_h__
