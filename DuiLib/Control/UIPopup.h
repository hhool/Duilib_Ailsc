#ifndef __UIPOPUPUI_H__
#define __UIPOPUPUI_H__

#pragma once
/*
add by jefcat
date:20170315
note:ʵ�ֶ๦���������ڣ���Ҫ���õ������ڵĴ�С�Լ�����������Ҫ��xml
���ڵ���������ʽ�Լ����ܵĲ�ȷ���ԣ�������Ҫ���ⲿ��CCompositeLayoutUI�����ؼ��������¼�����
CPopupUI����SetCreatePopupUI���ô����Ķ���,����Ĭ�ϴ���ChildLayoutUI
�����������е��¼������������洦�������ⲿ���ڴ���

xml:
eg:<Popup name="DateTime" popboxsize="177,192"  popxml="skin/popup/DateUI/DateTime.xml" direct="bottom" />

����Demo��see PopupUIDemo ��װ�����ڿؼ�
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
	///>���ö�̬����PopupUI����
	void SetCreatePopupUI(CRETAE_POPUP_UI pCreateUI);
	//���õ������ڵĴ�С
	SIZE GetPopBoxSize();
	void SetPopBoxSize(SIZE szDropBoxSize);
	//���õ������ڼ��ص�xml
	void SetPopupXml(const CDuiString &strXml);
	const CDuiString GetPopupXml();
	//���õ������ڵ���Ҫ��������
	void SetDirect(bool bTop);
	bool IsTopDirect();

private:
	CUIFunctionalLayout *CreatePopUI();
private:
	CPopupWnd *m_pWindow;
	SIZE m_szDropBoxSize;//(200,100)
	CDuiString m_strPopXml;
	bool m_bTopDirect;//�Ƿ������ϵ���Ϊ��Ҫλ��
	CRETAE_POPUP_UI m_pPopUICreate;
};

} // namespace DuiLib

#endif // __UICOMBO_H__
