#pragma once

// CMyEdit

class CMyEdit: public CEdit {
		DECLARE_DYNAMIC(CMyEdit)

	public:
		CMyEdit();
		virtual ~CMyEdit();
		// momo change command box color
		void SetBgColor(COLORREF clr);
		// momo change command box color

	protected:
		DECLARE_MESSAGE_MAP()
		// momo change command box color
		afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	private:
		COLORREF m_bgColor;
		CBrush m_brush;
		// momo change command box color
	public:
		afx_msg void OnEnChange();
		afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
		afx_msg void OnClose();
		virtual BOOL PreTranslateMessage(MSG* pMsg);
};
