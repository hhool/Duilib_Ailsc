// App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

/***虚拟列表使用说明**
1.在属性里面设置virtual属性为true，或者在代码里面SetVirtual
2.设置虚拟列表的数据格式SetVirtualItemFormat，设置格式的时候请设置行高
3.设置虚表数据个数SetVirtualItemCount
4.响应DUI_MSGTYPE_DRAWITEM绘画虚表内容
5.响应DUI_MSGTYPE_SORT 设置数据排序，排序后内容发生改变再次设置改变后的数据个数
*/
CControlUI* CreateVirtualItem()
{
	CListHBoxElementUI *pHBox = new CListHBoxElementUI;
	//> 设置行高
	pHBox->SetFixedHeight(28);
	///> 位置
	CCheckBoxUI *pCheckBox = new CCheckBoxUI;
	pCheckBox->SetAttributeList(_T("selectedimage=\"file='skin\\res\\checked.png' dest='0,2,16,18'\" normalimage=\"file='skin\\res\\unchecked.png' dest='0,2,16,18'\""));
	pCheckBox->SetFixedHeight(16);
	pCheckBox->SetFixedWidth(30);

	//> 名称
	CLabelUI *pLabel = new CLabelUI;

	///> 操作区域
	CHorizontalLayoutUI *pHorizon = new CHorizontalLayoutUI;
	CButtonUI *pButton = new CButtonUI;
	pButton->SetAttributeList(_T("normalimage=\"file='skin\\res\\btn_normal.png'\" hotimage=\"file='skin\\res\\btn_hot.png'\" pushedimage=\"file='skin\\res\\btn_pushed.png'\""));
	pButton->SetFixedHeight(16);
	pButton->SetFixedWidth(30);
	pButton->SetText(_T("编辑"));
	CHorizontalLayoutUI *pAxis = new CHorizontalLayoutUI;
	pAxis->SetFixedWidth(20);

	CButtonUI *pButton2 = new CButtonUI;
	pButton2->SetAttributeList(_T("normalimage=\"file='skin\\res\\btn_normal.png'\" hotimage=\"file='skin\\res\\btn_hot.png'\" pushedimage=\"file='skin\\res\\btn_pushed.png'\""));
	pButton2->SetFixedHeight(16);
	pButton2->SetFixedWidth(30);
	pButton2->SetText(_T("删除"));

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
		///> 设置数据行为格式,这里使用模板数据，所以不需要设置CreateVirtualItem
		//m_plist->SetVirtualItemFormat(CreateVirtualItem);
		TCHAR szBuf[10] = _T("");
		for (int i = 1;i <= ITEMCOUNT;++i)
		{
			_stprintf_s<10>(szBuf,_T("%06d"),i);
			m_vdata.push_back(szBuf);
		}
		m_plist->SetVirtualItemCount(ITEMCOUNT);

		//非虚表设置数据
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
		///> 如果是排序
		if(msg.sType == DUI_MSGTYPE_SORT)
		{
			///> 升序排序
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
    pFrame->Create(NULL, _T("这是一个最简单的测试用exe，修改test1.xml就可以看到效果"), UI_WNDSTYLE_FRAME|WS_CLIPCHILDREN, WS_EX_WINDOWEDGE);
    pFrame->CenterWindow();
    pFrame->ShowModal();
    ::CoUninitialize();
    return 0;
}
