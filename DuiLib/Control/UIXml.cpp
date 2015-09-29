#include "stdafx.h"
#include "UIXml.h"

namespace DuiLib
{
	inline CXmlUI::CXmlUI(void)
	{
		m_pControl = NULL;
	}

	inline CXmlUI::CXmlUI(LPCTSTR xmlPath)
	{
		CDialogBuilder build;
		m_pControl = build.Create(xmlPath);
	}

	inline CControlUI *CXmlUI::Load(LPCTSTR xmlPath)
	{
		CDialogBuilder build;
		m_pControl = build.Create(xmlPath);
		return m_pControl;
	}

	inline CXmlUI::operator CControlUI *()
	{
		return m_pControl;
	}
}
