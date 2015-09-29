#pragma once
#include "dui.h"

class CMainFram:public WindowImplBase
{
public:
	CMainFram(void);
	~CMainFram(void);

	virtual LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual CControlUI *CreateControl(LPCTSTR pstrClass);
	void AddListItem(int fileindex,CDuiString szFileName, CDuiString szFilePath);
private:
	CListUI *m_pList;
};

