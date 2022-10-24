#include "stdafx.h"
#include "UIFunctionalLayout.h"


namespace DuiLib
{

CUIFunctionalLayout::CUIFunctionalLayout(void)
{
}


CUIFunctionalLayout::~CUIFunctionalLayout(void)
{
	m_pManager->RemoveNotifier(this);
}

LPVOID CUIFunctionalLayout::GetInterface(LPCTSTR pstrName)
{
	
	if (_tcscmp(pstrName, DUI_CTR_FUNCTIONALLAYOUT) == 0) return static_cast<CUIFunctionalLayout*>(this);
	return __super::GetInterface(pstrName);
}

LPCTSTR CUIFunctionalLayout::GetClass() const
{
	return DUI_CTR_FUNCTIONALLAYOUT;
}


void CUIFunctionalLayout::DoInit()
{
	__super::DoInit();
	m_pManager->AddNotifier(this);
}

void CUIFunctionalLayout::Notify(TNotifyUI& msg)
{
}
void CUIFunctionalLayout::initUIData(CControlUI *m_pOowner){}

}