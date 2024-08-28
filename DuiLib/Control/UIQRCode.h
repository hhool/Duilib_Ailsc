#pragma once
#include "../Utils/qrcodegen.hpp"
using qrcodegen::QrCode;
namespace DuiLib
{
	class DUILIB_API CQRCodeUI : public CControlUI
	{
	public:
		CQRCodeUI();
		~CQRCodeUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void QREncodeBinary(const std::vector<std::uint8_t> &data);
		void QREncodeText(CDuiString strText);
		void SetQrEcc(QrCode::Ecc ecc);
		bool IsQrEmpty();
		virtual void PaintBkImage(HDC hDC);
	private:
		QrCode m_QrCode;//isempty
		QrCode::Ecc m_errCorLvl;//容错率
		DWORD m_dwQRColor;
		DWORD m_dwQRBkColor;
	};
};

