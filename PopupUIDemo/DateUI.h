#pragma once
/*
add by jefcat 20170315
not:ģ��QQ�����¼�е� ���ڿؼ�
*/
class CDateUI :public CUIFunctionalLayout
{
public:
	CDateUI();
	virtual void Notify(TNotifyUI& msg);
	//ʹ��PopupUI���ַ�����ʼ��CChildLayoutUI2017-3-14
	virtual void initUIData(CControlUI *m_pOowner);
	//��CChildLayoutUI ��ʽ�����γ��ַ���PopupUI
	virtual CDuiString FormatStringToPopUI();

private:
	///> ����UI����
	void UpDateUI();
	///> ��ȡ�������ڼ� 0 - 6 ����һ-������
	int GetWeek(int yera, int mounth, int day);
	///> ��ȡ���µ����һ��
	int GetMounthLastDay(int yera, int mounth);
private:
	CLabelUI *m_pLabel_date;//���ڣ���ʽ 3�� 2017
	SYSTEMTIME m_time;
	CPopupUI *m_pOowner;//Pop��������
};

