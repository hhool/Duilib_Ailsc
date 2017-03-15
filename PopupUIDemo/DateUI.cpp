#include "stdafx.h"
#include "DateUI.h"

static TCHAR g_Mounth[12][12] = { _T("一月"), _T("二月"), _T("三月"), _T("四月"), _T("五月"), _T("六月"),
									_T("七月"), _T("八月"), _T("九月"), _T("十月"), _T("十一月"), _T("十二月") };
CDateUI::CDateUI()
{
	m_pOowner = NULL;
	m_pLabel_date = NULL;
	GetLocalTime(&m_time);
}

void CDateUI::Notify(TNotifyUI& msg)
{
	if (msg.sType == DUI_MSGTYPE_WINDOWINIT && m_pManager)
	{
		m_pLabel_date = dynamic_cast<CLabelUI *>(m_pManager->FindControl(_T("date")));
	}
	else if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (msg.pSender->GetName() == _T("year_1"))
		{
			m_time.wYear -= 1;
			UpDateUI();
		}
		else if (msg.pSender->GetName() == _T("year_2"))
		{
			m_time.wYear += 1;
			UpDateUI();
		}
		if (msg.pSender->GetName() == _T("mouth_1"))
		{
			if (m_time.wMonth == 1)
			{
				m_time.wMonth = 12;
				m_time.wYear -= 1;
			}
			else
			{
				m_time.wMonth -= 1;
			}
			
			UpDateUI();
		}
		else if (msg.pSender->GetName() == _T("mouth_2"))
		{
			if (m_time.wMonth == 12)
			{
				m_time.wMonth = 1;
				m_time.wYear += 1;
			}
			else
			{
				m_time.wMonth += 1;
			}
			UpDateUI();
		}
		else if (_tcsncmp(msg.pSender->GetName().GetData(), _T("day"), 3) == 0)
		{
			m_time.wDay = _ttol(msg.pSender->GetText());

			if (m_pOowner)
			{
				CDuiString strtime;
				strtime.Format(_T("%d-%d-%d"), m_time.wYear, m_time.wMonth, m_time.wDay);
				m_pOowner->SetText(strtime);
			}
		}
	}
}
//使用PopupUI的字符串初始化CChildLayoutUI2017-3-14
void CDateUI::initUIData( CPopupUI *pOowner)
{
	if (pOowner == NULL) return;
	m_pOowner = pOowner;
	CDuiString strPopupUIString = m_pOowner->GetText();
	TCHAR *pContext = NULL;
	const TCHAR *pText = _tcstok_s((TCHAR *)strPopupUIString.GetData(), _T("-"), &pContext);
	if (pText && _ttol(pText) > 0)
	{
		m_time.wYear = _ttol(pText);
		pText = _tcstok_s(NULL, _T("-"), &pContext);

		if (pText  && _ttol(pText) > 0)
		{
			m_time.wMonth = _ttol(pText);

			pText = _tcstok_s(NULL, _T("-"), &pContext);
			if (pText  && _ttol(pText) > 0)
				m_time.wDay = _ttol(pText);
		}
	}	

	UpDateUI();
}


int CDateUI::GetWeek(int yera, int mounth, int day)
{
	if (mounth == 1 || mounth == 2) //把一月和二月换算成上一年的十三月和是四月  
	{
		mounth += 12;
		yera--;
	}
	int Week = (day + 2 * mounth + 3 * (mounth + 1) / 5 + yera + yera / 4 - yera / 100 + yera / 400) % 7;
	return Week;
}

#define leap(year) (((year%4==0)&&(year%100!=0))||((year%4==0)&&(year%400==0))) 

int CDateUI::GetMounthLastDay(int year, int mounth)
{
	switch (mounth)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 2:
		if (leap(year))
			return 29;
		else
			return 28;
	default:
		return 30;
	}
}

//将CChildLayoutUI 格式化，形成字符给PopupUI
CDuiString CDateUI::FormatStringToPopUI()
{
	CDuiString strTime;
	strTime.Format(_T("%d-%d-%d"), m_time.wYear, m_time.wMonth, m_time.wDay);
	return strTime;
}


void CDateUI::UpDateUI()
{
	///> 更新控件数据
	int nWeek = GetWeek(m_time.wYear, m_time.wMonth, 1);
	int nTotalDay = GetMounthLastDay(m_time.wYear, m_time.wMonth);

	nWeek = (nWeek + 1) % 7;
	CDuiString strDay = _T("");
	///> 没有日期的地方隐藏日期按钮
	///> 隐藏开始位置按钮
	for (int i = 0; i < nWeek; ++i)
	{
		strDay.Format(_T("day%d"), i);
		CControlUI *pDay = m_pManager->FindControl(strDay);
		_ASSERT(pDay);
		if (pDay)
		{
			pDay->SetEnabled(false);
			pDay->SetText(_T(""));
		}
	}
	///> 隐藏末尾位置按钮
	for (int i = nTotalDay + nWeek; i < 42; ++i)
	{
		strDay.Format(_T("day%d"), i);
		CControlUI *pDay = m_pManager->FindControl(strDay);
		_ASSERT(pDay);
		if (pDay)
		{
			pDay->SetEnabled(false);
			pDay->SetText(_T(""));
		}
	}
	///> 更新日历
	for (int nIndex = 0; nIndex < nTotalDay; ++nIndex)
	{
		strDay.Format(_T("day%d"), nWeek + nIndex);
		CControlUI *pDay = m_pManager->FindControl(strDay);
		_ASSERT(pDay);
		if (pDay)
		{
			strDay.Format(_T("%d"), nIndex + 1);
			pDay->SetEnabled(true);
			pDay->SetKillPupup(true);
			pDay->SetText(strDay);
		}

	}

	///> 更新日期
	if (m_pLabel_date)
	{
		strDay.Format(_T("%s %d"), g_Mounth[m_time.wMonth - 1], m_time.wYear);
		m_pLabel_date->SetText(strDay);
	}
}