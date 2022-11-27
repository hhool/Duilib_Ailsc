#include "StdAfx.h"
#include "UIQRCode.h"


namespace DuiLib
{
	CQRCodeUI::CQRCodeUI()
	{
		m_errCorLvl = QrCode::Ecc::HIGH;
		m_QrCode = QrCode::encodeText("https://gitee.com/Ailsc/Duilib", m_errCorLvl);
		m_dwQRColor = 0xff000000;
		m_dwQRBkColor = 0xffffffff;
	}
	
	CQRCodeUI::~CQRCodeUI()
	{
	}

	LPCTSTR CQRCodeUI::GetClass() const
	{
		return DUI_CTR_QRCODE;
	}

	LPVOID CQRCodeUI::GetInterface(LPCTSTR pstrName)
	{
		if (_tcscmp(pstrName, DUI_CTR_QRCODE) == 0) return static_cast<CQRCodeUI*>(this);
		return CControlUI::GetInterface(pstrName);
	}

	void CQRCodeUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if (_tcscmp(pstrName, _T("text")) == 0){
			QREncodeText(pstrValue);
		}
		else if(_tcscmp(pstrName, _T("qrcolor")) == 0){
			while (*pstrValue > _T('\0') && *pstrValue <= _T(' ')) pstrValue = ::CharNext(pstrValue);
			if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			m_dwQRColor = _tcstoul(pstrValue, &pstr, 16);
		}
		else if(_tcscmp(pstrName, _T("qrbkcolor")) == 0){
			while (*pstrValue > _T('\0') && *pstrValue <= _T(' ')) pstrValue = ::CharNext(pstrValue);
			if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			m_dwQRBkColor = _tcstoul(pstrValue, &pstr, 16);
		}
		else if (_tcscmp(pstrName, _T("errlevel")) == 0)
		{
			int ecc = _ttoi(pstrValue);
			if (ecc >= QrCode::Ecc::LOW && ecc <= QrCode::Ecc::HIGH)
			{
				SetQrEcc((QrCode::Ecc)ecc);
			}
		}
		else
			__super::SetAttribute(pstrName, pstrValue);
	}

	void CQRCodeUI::QREncodeText(CDuiString strText)
	{
		if (!strText.IsEmpty())
		{
			m_QrCode = QrCode::encodeText(strText.GetData(), m_errCorLvl);
		}
	}

	void CQRCodeUI::QREncodeBinary(const std::vector<std::uint8_t> &data)
	{
		if (!data.empty())
		{
			m_QrCode = QrCode::encodeBinary(data, m_errCorLvl);
		}
	}
	
	void CQRCodeUI::SetQrEcc(QrCode::Ecc ecc)
	{
		m_errCorLvl = ecc;
	}

	void CQRCodeUI::PaintBkImage(HDC hDC)
	{
		HDC hMemDc = CreateCompatibleDC(hDC);
		HBITMAP hMemBitMap = CreateCompatibleBitmap(hDC, m_QrCode.getSize(), m_QrCode.getSize());
		SelectObject(hMemDc, hMemBitMap);

		RECT rt = { 0, 0, m_QrCode.getSize(), m_QrCode.getSize() };
		FillRect(hMemDc, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
		for (int y = 0; y < m_QrCode.getSize(); y++)
		{
			for (int x = 0; x < m_QrCode.getSize(); x++)
			{
				if (m_QrCode.getModule(x, y) == 0)
				{
					BYTE bBGRA[4] = { 0 };
					memcpy(bBGRA, &m_dwQRColor, sizeof(m_dwQRColor));
					SetPixel(hMemDc, x, y, RGB(bBGRA[2], bBGRA[1], bBGRA[0]));
				}
				else
				{
					BYTE bBGRA[4] = { 0 };
					memcpy(bBGRA, &m_dwQRBkColor, sizeof(m_dwQRBkColor));
					SetPixel(hMemDc, x, y, RGB(bBGRA[2], bBGRA[1], bBGRA[0]));
				}
			}
		}
		//show center in control
		int nWidth = (m_rcItem.right - m_rcItem.left) - m_rcPadding.left - m_rcPadding.right;
		int nHeight = (m_rcItem.bottom - m_rcItem.top) - m_rcPadding.top - m_rcPadding.bottom;

		int nCodeWitdh = min(nWidth, nHeight);
		int nStartX = m_rcItem.left + m_rcPadding.left + (nWidth - nCodeWitdh) / 2;
		int nStartY = m_rcItem.top + m_rcPadding.top + (nHeight - nCodeWitdh) / 2;
		StretchBlt(hDC, nStartX, nStartY, nCodeWitdh, nCodeWitdh, hMemDc, 0, 0, m_QrCode.getSize(), m_QrCode.getSize(), SRCCOPY);
		DeleteDC(hMemDc);
		DeleteObject(hMemBitMap);
	}
};
