#include "stdafx.h"
#include "SpinButtonUI.h"
#include <string>


CSpinButtonUI::CSpinButtonUI()
{
	m_pEditUI = NULL;
	m_pLeftBtnUI = NULL;
	m_pRightBtnUI = NULL;
}


CSpinButtonUI::~CSpinButtonUI()
{
}

void CSpinButtonUI::DoInit()
{
	__super::DoInit();
	m_pEditUI = dynamic_cast<CEditUI *>(FindSubControl("edit"));
	m_pLeftBtnUI = dynamic_cast<CButtonUI *>(FindSubControl("left_arrow"));
	m_pRightBtnUI = dynamic_cast<CButtonUI *>(FindSubControl("right_arrow"));
}

void CSpinButtonUI::Notify(TNotifyUI& msg)
{
	//�������Ϣ���ݵ�������Χ���ڣ��������Ĵ����л��ᴦ�����Ϣ
	__super::Notify(msg);

	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (msg.pSender == m_pLeftBtnUI)
		{
			LONGLONG val = std::atoi(m_pEditUI->GetText());
			m_pEditUI->SetText(std::to_string(--val).c_str());
		}
		else if (msg.pSender == m_pRightBtnUI)
		{
			LONGLONG val = std::atoi(m_pEditUI->GetText());
			m_pEditUI->SetText(std::to_string(++val).c_str());
		}
	}
}