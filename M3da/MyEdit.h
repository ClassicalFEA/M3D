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
		// momo custom right click for edit text
		afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
		afx_msg void OnEdit3RightClickUndo();
		afx_msg void OnEdit3RightClickCut();
		afx_msg void OnEdit3RightClickCopy();
		afx_msg void OnEdit3RightClickPaste();
		afx_msg void OnEdit3RightClickDelete();
		afx_msg void OnEdit3RightClickSelectAll();
		afx_msg void OnEdit3RightClickClearAll();
		// momo custom right click for edit text
		// momo change command box color
		afx_msg HBRUSH CtlColor(CDC* cDC, UINT nCtlColor);

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
