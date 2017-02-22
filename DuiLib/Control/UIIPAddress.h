#ifndef UIIPAddress_h__
#define UIIPAddress_h__
/*/////////////////////////////////////////////////////////////
//
// 文件名称	:	UIIPAddress.h
// 创建人		: 	daviyang35@QQ.com
// 创建时间	:	2015-05-08 11:40:49
// 说明			:	IPAddress控件，类CEditUI包装系统IPAddress控件
/////////////////////////////////////////////////////////////*/
#pragma once

namespace DuiLib
{

class DUILIB_API CIPAddressUI
	: public CLabelUI
{
	friend class CIPAddressWnd;
public:
	CIPAddressUI(void);
	virtual ~CIPAddressUI(void);
	void DoInit();
	UINT GetControlFlags() const;
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	void DoEvent(TEventUI& event);
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	virtual void SetText(LPCTSTR pstrText);
public:
	void SetAddress(_In_ BYTE nField0, _In_ BYTE nField1, _In_ BYTE nField2, _In_ BYTE nField3);
	void SetFieldRange(_In_ int nField, _In_ BYTE nLower, _In_ BYTE nUpper);

	void GetAddress(_Out_ BYTE& nField0, _Out_ BYTE& nField1, _Out_ BYTE& nField2, _Out_ BYTE& nField3) const;
	void GetAddress(_Out_ DWORD& dwAddress) const;
	CDuiString GetIPAddress();

private:
	CIPAddressWnd* m_pWindow;
	UINT m_uButtonState;
	BYTE m_nFiledRange[4][2];//nidex - 0min 1max
	BYTE m_nField0;
	BYTE m_nField1;
	BYTE m_nField2;
	BYTE m_nField3;
};

}

#endif // UIIPAddress_h__
