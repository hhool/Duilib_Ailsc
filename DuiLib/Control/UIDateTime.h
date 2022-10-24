#ifndef __UIDATETIME_H__
#define __UIDATETIME_H__

#pragma once
namespace DuiLib
{
	class CDateTimeWnd;

	/// ʱ��ѡ��ؼ�
	class DUILIB_API CDateTimeUI : public CLabelUI
	{
		friend class CDateTimeWnd;
	public:
		CDateTimeUI();
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;
		HWND GetNativeWindow() const;

		SYSTEMTIME& GetTime();
		void SetTime(SYSTEMTIME* pst);

		void SetReadOnly(bool bReadOnly);
		bool IsReadOnly() const;
		/*
		#liulei 20160714 ��������ʱ�䷶Χ
		������С��ʼʱ��
		@bSet �Ƿ����ã����bSet = false  ��ȡ��ʱ������
		*/
		void SetMinDateTime(const SYSTEMTIME &minsystem,bool bSet = true);
		void SetMaxDateTime(const SYSTEMTIME &maxsystem, bool bSet = true);
		/*
		����ʱ���ά���飬0 - min 1 - max
		*/
		SYSTEMTIME* GetRange(bool &bSetMin,bool &bSetMax);


		void UpdateText();
        void SetPos(RECT rc, bool bNeedInvalidate = true);
        void Move(SIZE szOffset, bool bNeedInvalidate = true);

		void DoEvent(TEventUI& event);
	protected:
		SYSTEMTIME m_sysTime;
		SYSTEMTIME m_sysTimeRange[2];
		bool	   m_bUserTimeRange[2];
		int        m_nDTUpdateFlag;
		bool       m_bReadOnly;
		CDateTimeWnd* m_pWindow;
	};
}
#endif // __UIDATETIME_H__