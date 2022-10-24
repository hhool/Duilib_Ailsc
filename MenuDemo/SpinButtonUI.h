#pragma once
class CSpinButtonUI:public CUIFunctionalLayout
{
public:
	CSpinButtonUI();
	~CSpinButtonUI();
	virtual void DoInit();
	virtual void Notify(TNotifyUI& msg);

private:
	CEditUI *m_pEditUI;
	CButtonUI *m_pLeftBtnUI;
	CButtonUI *m_pRightBtnUI;
};

