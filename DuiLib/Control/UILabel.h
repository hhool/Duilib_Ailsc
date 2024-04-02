#ifndef __UILABEL_H__
#define __UILABEL_H__

namespace DuiLib
{
	class DUILIB_API CLabelUI : public CControlUI
	{
	public:
		CLabelUI();
		~CLabelUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		virtual bool MeasureString(LPCTSTR pstrText, size_t len, SIZE& bounds/*if val != 0 fix val*/);

        void SetFixedWidth(int cx);
        void SetFixedHeight(int cy);
		void SetText(LPCTSTR pstrText);

		void SetTextStyle(UINT uStyle);
		UINT GetTextStyle() const;
		bool IsMultiLine();
		void SetMultiLine(bool bMultiLine = true);
		void SetEstimate(bool bEstimate = false);
		void SetTextColor(DWORD dwTextColor);
		DWORD GetTextColor() const;
		void SetDisabledTextColor(DWORD dwTextColor);
		DWORD GetDisabledTextColor() const;
		void SetFont(int index);
		int GetFont() const;
		RECT GetTextPadding() const;
		void SetTextPadding(RECT rc);
		void SetTextRenderingHint(int nTextRenderingHint = Gdiplus::TextRenderingHintClearTypeGridFit);
		int GetTextRenderingHint(int nTextRenderingHint);
		bool IsShowHtml();
		void SetShowHtml(bool bShowHtml = true);

		SIZE EstimateSize(SIZE szAvailable);
		void DoEvent(TEventUI& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		virtual void PaintText(HDC hDC);
		virtual void PaintText(HDC hDC,DWORD clrColor);

		void		SetEnabledEffect(bool _EnabledEffect);
		bool		GetEnabledEffect();
		void		SetEnabledLuminous(bool bEnableLuminous);
		bool		GetEnabledLuminous();
		void		SetLuminousFuzzy(float fFuzzy);
		float		GetLuminousFuzzy();
		void		SetGradientLength(int _GradientLength);
		int			GetGradientLength();
		void		SetShadowOffset(int _offset,int _angle);
		Gdiplus::RectF		GetShadowOffset();
		void		SetTextColor1(DWORD _TextColor1);
		DWORD		GetTextColor1();
		void		SetTextShadowColorA(DWORD _TextShadowColorA);
		DWORD		GetTextShadowColorA();
		void		SetTextShadowColorB(DWORD _TextShadowColorB);
		DWORD		GetTextShadowColorB();
		void		SetStrokeColor(DWORD _StrokeColor);
		DWORD		GetStrokeColor();
		void		SetGradientAngle(int _SetGradientAngle);
		int			GetGradientAngle();
		void		SetEnabledStroke(bool _EnabledStroke);
		bool		GetEnabledStroke();
		void		SetEnabledShadow(bool _EnabledShadowe);
		bool		GetEnabledShadow();
	
	protected:
		LPWSTR  m_pWideText;
		DWORD	m_dwTextColor;
		DWORD	m_dwDisabledTextColor;
		int		m_iFont;
		UINT	m_uTextStyle;
		RECT	m_rcTextPadding;
		int		m_nTextRenderingHint;//字体优化
		bool	m_bShowHtml;
		bool	m_bEstimate;//是否像Contain一样自己适位置大小，而不是根据位置调整
        SIZE    m_szAvailableLast;
        SIZE    m_cxyFixedLast;
        bool    m_bNeedEstimateSize;

		float					m_fLuminousFuzzy;
		int						m_GradientLength;
		int						m_GradientAngle;
		bool					m_EnableEffect;
		bool					m_bEnableLuminous;
		bool					m_EnabledStroke;
		bool					m_EnabledShadow;
		DWORD					m_dwTextColor1;
		DWORD					m_dwTextShadowColorA;
		DWORD					m_dwTextShadowColorB;
		DWORD					m_dwStrokeColor;
		Gdiplus::RectF					m_ShadowOffset;
	};
}

#endif // __UILABEL_H__