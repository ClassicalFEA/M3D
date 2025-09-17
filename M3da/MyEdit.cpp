// MyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "M3da.h"
#include "MyEdit.h"
// MoMo_Start
#include "GLOBAL_VARS.h"
// MoMo_End
// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

// momo change command box color
// CMyEdit::CMyEdit() {
//}
CMyEdit::CMyEdit()
    : m_bgColor(::GetSysColor(COLOR_WINDOW)) {
	m_brush.CreateSolidBrush(m_bgColor);
}
// momo change command box color

CMyEdit::~CMyEdit() {
}

BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
ON_CONTROL_REFLECT(EN_CHANGE, &CMyEdit::OnEnChange)
ON_WM_SYSCOMMAND()
ON_WM_CLOSE()
// momo change command box color
ON_WM_CTLCOLOR_REFLECT()
// momo change command box color
// momo custom right click for edit text
ON_WM_CONTEXTMENU()
ON_COMMAND(ID_EDIT3_RIGHTCLICK_UNDO, &CMyEdit::OnEdit3RightClickUndo)
ON_COMMAND(ID_EDIT3_RIGHTCLICK_CUT, &CMyEdit::OnEdit3RightClickCut)
ON_COMMAND(ID_EDIT3_RIGHTCLICK_COPY, &CMyEdit::OnEdit3RightClickCopy)
ON_COMMAND(ID_EDIT3_RIGHTCLICK_PASTE, &CMyEdit::OnEdit3RightClickPaste)
ON_COMMAND(ID_EDIT3_RIGHTCLICK_DELETE, &CMyEdit::OnEdit3RightClickDelete)
ON_COMMAND(ID_EDIT3_RIGHTCLICK_SELECTALL, &CMyEdit::OnEdit3RightClickSelectAll)
ON_COMMAND(ID_EDIT3_RIGHTCLICK_CLEARALL, &CMyEdit::OnEdit3RightClickClearAll)
// momo custom right click for edit text
END_MESSAGE_MAP()

// CMyEdit message handlers

void CMyEdit::OnEnChange() {
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	outtextMSG(_T("AA"));
	// momo change command box color
	CheckCommandEditColor(false);
	// momo change command box color
}

void CMyEdit::OnSysCommand(UINT nID, LPARAM lParam) {
	// TODO: Add your message handler code here and/or call default

	CEdit::OnSysCommand(nID, lParam);
}

void CMyEdit::OnClose() {
	// TODO: Add your message handler code here and/or call default

	CEdit::OnClose();
}

BOOL CMyEdit::PreTranslateMessage(MSG* pMsg) {
	// TODO: Add your specialized code here and/or call the base class
	// MoMo_Start
	// MoMo// if (pMsg->wParam == VK_ESCAPE) {
	if (pMsg->wParam == VK_ESCAPE && pMsg->message == WM_KEYDOWN) {
		if (!SeedVals.IsSeedMode) {
			outtextMSG2("C");
		} else {
			outtextMSG2("Cancel");
		}
		// MoMo_End
		return TRUE;
		// MoMo_Start
	} else if (pMsg->message == WM_KEYDOWN && (::GetKeyState(VK_CONTROL) & 0x8000)) {
		switch (pMsg->wParam) {
			case 'C': // Ctrl+C
				Copy();
				return TRUE;
			case 'X': // Ctrl+X
				Cut();
				return TRUE;
			case 'V': // Ctrl+V
				Paste();
				return TRUE;
			case 'A': // Ctrl+A
				SetSel(0, -1);
				return TRUE;
		}
		return CEdit::PreTranslateMessage(pMsg);
		// MoMo_End
	} else {
		return CEdit::PreTranslateMessage(pMsg);
	}
}

// momo change command box color
void CMyEdit::SetBgColor(COLORREF clr) {
	m_bgColor = clr;
	if (m_brush.GetSafeHandle())
		m_brush.DeleteObject();
	m_brush.CreateSolidBrush(m_bgColor);
	Invalidate();
}

HBRUSH CMyEdit::CtlColor(CDC* cDC, UINT /*nCtlColor*/) {
	cDC->SetBkColor(m_bgColor);
	return (HBRUSH) m_brush.GetSafeHandle();
}
// momo change command box color

// momo custom right click for edit text
void CMyEdit::OnContextMenu(CWnd* pWnd, CPoint point) {
	if (point.x == -1 && point.y == -1) {
		CRect rc;
		GetWindowRect(&rc);
		point = rc.CenterPoint();
	}
	CMenu menu;
	menu.CreatePopupMenu();
	bool bReadOnly = (GetStyle() & ES_READONLY) != 0;
	int nStart = 0, nEnd = 0;
	GetSel(nStart, nEnd);
	bool hasSelection = (nStart != nEnd);
	BOOL canUndo = CanUndo();
	BOOL hasClipboardText = ::IsClipboardFormatAvailable(CF_TEXT) || ::IsClipboardFormatAvailable(CF_UNICODETEXT);
	CString cur;
	GetWindowText(cur);
	menu.AppendMenu(MF_STRING, ID_EDIT3_RIGHTCLICK_UNDO, _T("Undo"));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_EDIT3_RIGHTCLICK_CUT, _T("Cut"));
	menu.AppendMenu(MF_STRING, ID_EDIT3_RIGHTCLICK_COPY, _T("Copy"));
	menu.AppendMenu(MF_STRING, ID_EDIT3_RIGHTCLICK_PASTE, _T("Paste"));
	menu.AppendMenu(MF_STRING, ID_EDIT3_RIGHTCLICK_DELETE, _T("Delete"));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_EDIT3_RIGHTCLICK_SELECTALL, _T("Select All"));
	menu.AppendMenu(MF_STRING, ID_EDIT3_RIGHTCLICK_CLEARALL, _T("Clear All"));
	if (canUndo) {
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_UNDO, MF_BYCOMMAND | MF_ENABLED);
	} else {
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_UNDO, MF_BYCOMMAND | MF_GRAYED);
	}
	if (hasSelection) {
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_CUT, MF_BYCOMMAND | MF_ENABLED);
	} else {
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_CUT, MF_BYCOMMAND | MF_GRAYED);
	}
	if (hasSelection) {
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_COPY, MF_BYCOMMAND | MF_ENABLED);
	} else {
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_COPY, MF_BYCOMMAND | MF_GRAYED);
	}
	if (hasClipboardText) {
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_PASTE, MF_BYCOMMAND | MF_ENABLED);
	} else {
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_PASTE, MF_BYCOMMAND | MF_GRAYED);
	}
	if (hasSelection) {
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_DELETE, MF_BYCOMMAND | MF_ENABLED);
	} else {
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_DELETE, MF_BYCOMMAND | MF_GRAYED);
	}
	if (!cur.IsEmpty()) {
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_SELECTALL, MF_BYCOMMAND | MF_ENABLED);
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_CLEARALL, MF_BYCOMMAND | MF_ENABLED);
	} else {
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_SELECTALL, MF_BYCOMMAND | MF_GRAYED);
		menu.EnableMenuItem(ID_EDIT3_RIGHTCLICK_CLEARALL, MF_BYCOMMAND | MF_GRAYED);
	}
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CMyEdit::OnEdit3RightClickUndo() {
	if (CanUndo())
		Undo();
}

void CMyEdit::OnEdit3RightClickCut() {
	Cut();
}

void CMyEdit::OnEdit3RightClickCopy() {
	Copy();
}

void CMyEdit::OnEdit3RightClickPaste() {
	Paste();
}

void CMyEdit::OnEdit3RightClickDelete() {
	SendMessage(WM_CLEAR);
}

void CMyEdit::OnEdit3RightClickSelectAll() {
	SetSel(0, -1);
	SetFocus();
}

void CMyEdit::OnEdit3RightClickClearAll() {
	SetWindowText(_T(""));
}
// momo custom right click for edit text
