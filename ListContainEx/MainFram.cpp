#include "MainFram.h"
#define WIN_BTN_TEST 0x201
CMainFram::CMainFram(void)
{
}


CMainFram::~CMainFram(void)
{
}

LPCTSTR CMainFram::GetWindowClassName() const
{
	return _T("DUI_MAINFRAM");
}

DuiLib::CDuiString CMainFram::GetSkinFile()
{
	return _T("duilib.xml");
}

DuiLib::CDuiString CMainFram::GetSkinFolder()
{
	return _T("UI");
}

CDuiString szfileName[4] = {_T("windows"),_T("C++"),_T("数据库"),_T("高数")};
CDuiString szfilePath[4] = {_T("C:\\"),_T("D:\\"),_T("E:\\"),_T("F:\\")};
void CMainFram::InitWindow()
{

	m_pList = static_cast<CListUI *>(m_PaintManager.FindControl(_T("ListDemo1")));
	if(m_pList)
	{
		CDuiString str;
		CDuiString strFilename;
		CDuiString strFilePatn;
		for (int i = 0; i < 100; i++)
		{
			strFilename.Format(_T("%s-%d"),szfileName[i%4]);
			strFilePatn.Format(_T("%s-%d"),szfilePath[i%4]);
			AddListItem(i,strFilename,strFilePatn);
		}
		RECT rtList = m_pList->GetPos();
		///> 必须SetPos让Contain计算内部控件位置
		m_pList->SetPos(rtList);
	}
}

///> 排序函数
bool g_bUp[3] = {true,true,true};
namespace DuiLib
{
	int CALLBACK SortByIndex(UINT_PTR pe1, UINT_PTR pe2,UINT_PTR pContext)
	{
		CListContainerElementExUI* pEUI1 = (CListContainerElementExUI*)pe1;
		CListContainerElementExUI* pEUI2 = (CListContainerElementExUI*)pe2;

		CLabelUI *pLabel1 =static_cast<CLabelUI *>(pEUI1->FindSubControl(_T("fileindex")));
		CLabelUI *pLabel2 =static_cast<CLabelUI *>(pEUI2->FindSubControl(_T("fileindex")));
		if(g_bUp[0])
		{
			if(_ttol((pLabel1)->GetText()) < _ttol((pLabel2)->GetText())) return 1;
			if(_ttol((pLabel1)->GetText()) > _ttol((pLabel2)->GetText())) return -1;
		}
		else
		{
			if(_ttol((pLabel1)->GetText())< _ttol((pLabel2)->GetText())) return -1;
			if(_ttol((pLabel1)->GetText()) > _ttol((pLabel2)->GetText())) return 1;
		}
		return 0;
	}

	int CALLBACK SortByName(UINT_PTR pe1, UINT_PTR pe2,UINT_PTR pContext)
	{
		CListContainerElementExUI* pEUI1 = (CListContainerElementExUI*)pe1;
		CListContainerElementExUI* pEUI2 = (CListContainerElementExUI*)pe2;

		CLabelUI *pLabel1 =static_cast<CLabelUI *>(pEUI1->FindSubControl(_T("filename")));
		CLabelUI *pLabel2 =static_cast<CLabelUI *>(pEUI2->FindSubControl(_T("filename")));
		if(g_bUp[1])
		{
			if(_tcscmp(pLabel1->GetText(),pLabel2->GetText()) < 0) return 1;
			if(_tcscmp(pLabel1->GetText(),pLabel2->GetText()) > 0) return -1;
		}
		else
		{
			if(_tcscmp(pLabel1->GetText(),pLabel2->GetText()) < 0) return -1;
			if(_tcscmp(pLabel1->GetText(),pLabel2->GetText()) > 0) return 1;
		}
		return 0;
	}

	int CALLBACK SortByPath(UINT_PTR pe1, UINT_PTR pe2,UINT_PTR pContext)
	{
		CListContainerElementExUI* pEUI1 = (CListContainerElementExUI*)pe1;
		CListContainerElementExUI* pEUI2 = (CListContainerElementExUI*)pe2;

		CLabelUI *pLabel1 =static_cast<CLabelUI *>(pEUI1->FindSubControl(_T("filepath")));
		CLabelUI *pLabel2 =static_cast<CLabelUI *>(pEUI2->FindSubControl(_T("filepath")));
		if(g_bUp[2])
		{
			if(_tcscmp(pLabel1->GetText(),pLabel2->GetText()) < 0) return 1;
			if(_tcscmp(pLabel1->GetText(),pLabel2->GetText()) > 0) return -1;
		}
		else
		{
			if(_tcscmp(pLabel1->GetText(),pLabel2->GetText()) < 0) return -1;
			if(_tcscmp(pLabel1->GetText(),pLabel2->GetText()) > 0) return 1;
		}
		return 0;
	}

	void ModifyMenu(CMenuUI *pMenu)
	{
		CDuiString strName = pMenu->GetName();
		int a = 0;
	}
	void MenuClick(CDuiString strMenuElementName)
	{
		int a = 0;
	}
}
//////////////////////////////////////////////////////////////////////////
void CMainFram::Notify( TNotifyUI& msg )
{
	__super::Notify(msg);
	if(msg.sType == DUI_MSGTYPE_HEADERCLICK)
	{
		if(msg.pSender->GetName() == _T("fileindex"))
		{
			m_pList->SortItems(SortByIndex,0);
			g_bUp[0] = !g_bUp[0];
		}
		else if(msg.pSender->GetName() == _T("filename"))
		{
			m_pList->SortItems(SortByName,0);
			g_bUp[1] = !g_bUp[1];
		}
		else if(msg.pSender->GetName() == _T("filepatn"))
		{
			m_pList->SortItems(SortByPath,0);
			g_bUp[2] = !g_bUp[2];
		}
	}
	else if(msg.sType == DUI_MSGTYPE_MENU)
	{
		CMenuWnd *pMenu = new CMenuWnd();
		pMenu->SetMenuClickFunc(MenuClick);
		pMenu->SetModifyMenuFunc(ModifyMenu);
		CPoint point = msg.ptMouse;
		ClientToScreen(m_hWnd, &point);
		pMenu->Init(point,_T("duiMenu.xml"));
		
	}
	else if(msg.sType == DUI_MSGTYPE_ITEMSELECT)
	{
		int a = 0;
	}
	else if(msg.sType == DUI_MSGTYPE_ITEMCLICK)
	{
		int a = 0;
	}
}


void CMainFram::AddListItem( int fileindex,CDuiString szFileName, CDuiString szFilePath )
{
	CListContainerElementExUI *pListContain = new CListContainerElementExUI;
	pListContain->SetFixedHeight(32);
	CDuiString strIndex;
	strIndex.Format(_T("%d"),fileindex);
	CLabelUI *pLabel = new CLabelUI;
	pLabel->ApplyAttributeList(_T("name=\"fileindex\" align=\"center\" textcolor=\"#ff000000\""));
	pLabel->SetText(strIndex);

	CLabelUI *pLabel2 = new CLabelUI;
	pLabel2->ApplyAttributeList(_T("name=\"filename\" align=\"left\" textcolor=\"#ffff0000\""));
	pLabel2->SetText(szFileName);

	CLabelUI *pLabel3 = new CLabelUI;
	pLabel3->ApplyAttributeList(_T("name=\"filepath\" align=\"left\" textcolor=\"#ff0000ff\""));
	pLabel3->SetText(szFilePath);

	CVerticalLayoutUI *pv = new CVerticalLayoutUI;

	CButtonUI *pButtonOpen = new CButtonUI;
	pButtonOpen->SetAttribute(_T("bkcolor"),_T("#ffff0000"));
	pButtonOpen->SetFixedHeight(15);
	pButtonOpen->SetText(_T("Open"));

	CButtonUI *pButtonOpen2 = new CButtonUI;
	pButtonOpen2->SetAttribute(_T("bkcolor"),_T("#ff0ff00f"));
	pButtonOpen2->SetFixedHeight(15);
	pButtonOpen2->SetText(_T("Delete"));

	pv->Add(pButtonOpen);
	pv->Add(pButtonOpen2);

	pListContain->Add(pLabel);
	pListContain->Add(pLabel2);
	pListContain->Add(pLabel3);
	pListContain->Add(pv);
	
	m_pList->Add(pListContain);
}

LRESULT CMainFram::OnCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	if(LOWORD(wParam) == WIN_BTN_TEST)
	{
	
	}
	return 0;
}

CControlUI *CMainFram::CreateControl(LPCTSTR pstrClass)
{
	if(lstrcmp(pstrClass,_T("Winbtn")) == 0)
	{
		CWinWndUI *pWinWnd = new CWinWndUI;
		HWND    hWnd  = ::CreateWindow(_T("BUTTON"), _T("win32"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, m_PaintManager.GetPaintWindow(),(HMENU)WIN_BTN_TEST, NULL, NULL);
		pWinWnd->Attach(hWnd); 
		return pWinWnd;
	}
	return NULL;
}

