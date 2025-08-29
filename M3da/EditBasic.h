#pragma once

// CEditBasic

class CEditBasic: public CEdit {
		DECLARE_DYNAMIC(CEditBasic)

	public:
		CEditBasic();
		virtual ~CEditBasic();
		// momo change command box color
		void SetBgColor(COLORREF clr);
		// momo change command box color

	protected:
		DECLARE_MESSAGE_MAP()
		// momo change command box color
		afx_msg HBRUSH CtlColor(CDC* cDC, UINT nCtlColor);

	private:
		COLORREF m_bgColor;
		CBrush m_brush;
		// momo change command box color
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
};

