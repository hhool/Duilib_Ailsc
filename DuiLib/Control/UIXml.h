#pragma once
namespace DuiLib
{
	class UILIB_API CXmlUI:public CControlUI
	{
	public:
		explicit CXmlUI(void);
		explicit CXmlUI(LPCTSTR xmlPath);
		CControlUI *Load(LPCTSTR xmlPath);
		operator CControlUI *();
		~CXmlUI(void){};

	private:
		CControlUI *m_pControl;
	};
}


