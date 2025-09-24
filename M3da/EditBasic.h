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
		// momo custom right click for edit text
		afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
		afx_msg void OnEdit12RightClickUndo();
		afx_msg void OnEdit12RightClickCut();
		afx_msg void OnEdit12RightClickCopy();
		afx_msg void OnEdit12RightClickPaste();
		afx_msg void OnEdit12RightClickDelete();
		afx_msg void OnEdit12RightClickSelectAll();
		afx_msg void OnEdit12RightClickClearAll();
		afx_msg void OnEdit12RightClickLock();
		afx_msg void OnEdit12RightClickUnlock();
		// momo custom right click for edit text
		// momo change command box color
		afx_msg HBRUSH CtlColor(CDC* cDC, UINT nCtlColor);

	private:
		COLORREF m_bgColor;
		CBrush m_brush;
		// momo change command box color
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
};
