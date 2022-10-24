// App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

/***�����б�ʹ��˵��**
1.��������������virtual����Ϊtrue�������ڴ�������SetVirtual
2.���������б�����ݸ�ʽSetVirtualItemFormat�����ø�ʽ��ʱ���������и�
3.����������ݸ���SetVirtualItemCount
4.��ӦDUI_MSGTYPE_DRAWITEM�滭�������
5.��ӦDUI_MSGTYPE_SORT ��������������������ݷ����ı��ٴ����øı������ݸ���
*/
CControlUI* CreateVirtualItem()
{
	CListHBoxElementUI *pHBox = new CListHBoxElementUI;
	//> �����и�
	pHBox->SetFixedHeight(28);
	///> λ��
	CCheckBoxUI *pCheckBox = new CCheckBoxUI;
	pCheckBox->SetAttributeList(_T("selectedimage=\"file='skin\\res\\checked.png' dest='0,2,16,18'\" normalimage=\"file='skin\\res\\unchecked.png' dest='0,2,16,18'\""));
	pCheckBox->SetFixedHeight(16);
	pCheckBox->SetFixedWidth(30);

	//> ����
	CLabelUI *pLabel = new CLabelUI;

	///> ��������
	CHorizontalLayoutUI *pHorizon = new CHorizontalLayoutUI;
	CButtonUI *pButton = new CButtonUI;
	pButton->SetAttributeList(_T("normalimage=\"file='skin\\res\\btn_normal.png'\" hotimage=\"file='skin\\res\\btn_hot.png'\" pushedimage=\"file='skin\\res\\btn_pushed.png'\""));
	pButton->SetFixedHeight(16);
	pButton->SetFixedWidth(30);
	pButton->SetText(_T("�༭"));
	CHorizontalLayoutUI *pAxis = new CHorizontalLayoutUI;
	pAxis->SetFixedWidth(20);

	CButtonUI *pButton2 = new CButtonUI;
	pButton2->SetAttributeList(_T("normalimage=\"file='skin\\res\\btn_normal.png'\" hotimage=\"file='skin\\res\\btn_hot.png'\" pushedimage=\"file='skin\\res\\btn_pushed.png'\""));
	pButton2->SetFixedHeight(16);
	pButton2->SetFixedWidth(30);
	pButton2->SetText(_T("ɾ��"));

	pHorizon->Add(pButton);
	pHorizon->Add(pAxis);
	pHorizon->Add(pButton2);

	pHBox->Add(pCheckBox);
	pHBox->Add(pLabel);
	pHBox->Add(pHorizon);

	return pHBox;
}

const int  ITEMCOUNT = 10000;
class CFrameWindowWnd: public WindowImplBase
{
public:
	CFrameWindowWnd(){};
	virtual CDuiString GetSkinFolder() {return _T("");}
	virtual CDuiString GetSkinFile(){return _T("skin/virlist/virlist.xml");}
	virtual LPCTSTR GetWindowClassName(void) const  {return _T("CFrameWindowWnd");}
	virtual void InitWindow()
	{
		__super::InitWindow();
		m_plist = static_cast<CListUI*>(m_PaintManager.FindControl(_T("list")));
		m_plist1 = static_cast<CListUI*>(m_PaintManager.FindControl(_T("list1")));
		///> ����������Ϊ��ʽ,����ʹ��ģ�����ݣ����Բ���Ҫ����CreateVirtualItem
		//m_plist->SetVirtualItemFormat(CreateVirtualItem);
		TCHAR szBuf[10] = _T("");
		for (int i = 1;i <= ITEMCOUNT;++i)
		{
			_stprintf_s<10>(szBuf,_T("%06d"),i);
			m_vdata.push_back(szBuf);
		}
		m_plist->SetVirtualItemCount(ITEMCOUNT);

		//�������������
		CDuiString strFormat;
		for (int i = 0; i < 50;++i)
		{
			CListHBoxElementUI *pHBox = dynamic_cast<CListHBoxElementUI *>(m_plist1->AddTemplate());
			strFormat.Format(_T("%d"), i + 1);
			pHBox->GetItemAt(0)->SetText(strFormat);
			strFormat.Format(_T("%06d"), i + 1);
			pHBox->GetItemAt(1)->SetText(strFormat);
		}
	}

	virtual void Notify(TNotifyUI& msg)
	{
		///> ���������
		if(msg.sType == DUI_MSGTYPE_SORT)
		{
			///> ��������
			if(msg.wParam == ESORT::E_SORT_ASC)
			{
				std::sort(m_vdata.begin(),m_vdata.end(),[](CDuiString &item1,CDuiString &item2)
				{
					return item1 < item2;
				});
				m_plist->SetVirtualItemCount(ITEMCOUNT);
			}
			else if(msg.wParam == ESORT::E_SORT_DESC)
			{
				std::sort(m_vdata.begin(),m_vdata.end(),[](CDuiString &item1,CDuiString &item2)
				{
					return item2 < item1;
				});
				m_plist->SetVirtualItemCount(ITEMCOUNT);
			}
		}
		else if(msg.sType == DUI_MSGTYPE_DRAWITEM)
		{
			DrawItem((CControlUI*)msg.wParam,msg.lParam);
		}
		__super::Notify(msg);
	}

	void DrawItem(CControlUI *pControl,int nRow)
	{
		CDuiString strFormat;
		CListHBoxElementUI *pHBox = static_cast<CListHBoxElementUI*>(pControl->GetInterface(DUI_CTR_LISTHBOXELEMENT));
		if(pHBox && nRow < ITEMCOUNT)
		{
			strFormat.Format(_T("%d"),nRow+1);
			pHBox->GetItemAt(0)->SetText(strFormat);
			pHBox->GetItemAt(1)->SetText(m_vdata[nRow]);
		}
	}

private:
	CListUI *m_plist;
	CListUI *m_plist1;
	std::vector<CDuiString> m_vdata;
};


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
    HRESULT Hr = ::CoInitialize(NULL);
    if( FAILED(Hr) ) return 0;


    CFrameWindowWnd* pFrame = new CFrameWindowWnd();
    if( pFrame == NULL ) return 0;
    pFrame->Create(NULL, _T("����һ����򵥵Ĳ�����exe���޸�test1.xml�Ϳ��Կ���Ч��"), UI_WNDSTYLE_FRAME|WS_CLIPCHILDREN, WS_EX_WINDOWEDGE);
    pFrame->CenterWindow();
    pFrame->ShowModal();
    ::CoUninitialize();
    return 0;
}
