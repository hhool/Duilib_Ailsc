#include "stdafx.h"
#include "UICompositeLayout.h"


namespace DuiLib
{

CCompositeLayoutUI::CCompositeLayoutUI(void)
{
}


CCompositeLayoutUI::~CCompositeLayoutUI(void)
{
	m_pManager->RemoveNotifier(this);
}

LPVOID CCompositeLayoutUI::GetInterface(LPCTSTR pstrName)
{
	
	if (_tcscmp(pstrName, DUI_CTR_COMPOSITELAYOUT) == 0) return static_cast<CCompositeLayoutUI*>(this);
	return __super::GetInterface(pstrName);
}

LPCTSTR CCompositeLayoutUI::GetClass() const
{
	return DUI_CTR_COMPOSITELAYOUT;
}

void CCompositeLayoutUI::AddNotifyFilter(INotifyUI *pFilter)
{
	if ( m_arrayNotifyFilters.Find(pFilter) == -1)
	{
		m_arrayNotifyFilters.Add(pFilter);
	}
}

void CCompositeLayoutUI::RemoveNotifyFilter(INotifyUI *pFilter)
{
	int nIndex = m_arrayNotifyFilters.Find(pFilter);
	if ( nIndex != -1 )
	{
		m_arrayNotifyFilters.Remove(nIndex);
	}
}

void CCompositeLayoutUI::DoInit()
{
	AddNotifyFilter(this);
	m_pManager->AddNotifier(this);
}

void CCompositeLayoutUI::Notify(TNotifyUI& msg){}
void CCompositeLayoutUI::initUIData(CPopupUI *m_pOowner){}

}