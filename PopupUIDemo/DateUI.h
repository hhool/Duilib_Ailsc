#pragma once
/*
add by jefcat 20170315
not:模仿QQ聊天记录中的 日期控件
*/
class CDateUI :public CUIFunctionalLayout
{
public:
	CDateUI();
	virtual void Notify(TNotifyUI& msg);
	//使用PopupUI的字符串初始化CChildLayoutUI2017-3-14
	virtual void initUIData(CControlUI *m_pOowner);
	//将CChildLayoutUI 格式化，形成字符给PopupUI
	virtual CDuiString FormatStringToPopUI();

private:
	///> 更新UI数据
	void UpDateUI();
	///> 获取当天星期几 0 - 6 星期一-星期日
	int GetWeek(int yera, int mounth, int day);
	///> 获取当月的最后一天
	int GetMounthLastDay(int yera, int mounth);
private:
	CLabelUI *m_pLabel_date;//日期，格式 3月 2017
	SYSTEMTIME m_time;
	CPopupUI *m_pOowner;//Pop所属窗口
};

