// InputPane.cpp : implementation file
//

#include "stdafx.h"
#include "M3da.h"
#include "InputPane.h"

// CInputPane

IMPLEMENT_DYNAMIC(CInputPane, CDockablePane)

CInputPane::CInputPane() {
}

CInputPane::~CInputPane() {
}

BEGIN_MESSAGE_MAP(CInputPane, CDockablePane)
ON_WM_CREATE()
ON_WM_SIZE()
//  ON_WM_CLOSE()
// momo change command box color
ON_WM_CTLCOLOR()
// momo change command box color
END_MESSAGE_MAP()

// CInputPane message handlers

int CInputPane::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	// m_Font.CreateStockObject(DEFAULT_GUI_FONT);
	CRect rectDummy(10, 10, 50, 500);
	rectDummy.SetRectEmpty();

	// Create tabs window:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1)) {
		TRACE0("Failed to create output tab window\n");
		return -1; // fail to create
	}
	CRect AAA(10, 10, 500, 150);
	Edit1.Create(ES_AUTOVSCROLL | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN, AAA, &m_wndTabs, IDS_EDIT1);
	Edit2.Create(ES_AUTOVSCROLL | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN, AAA, &m_wndTabs, IDS_EDIT2);
	// Edit3.Create(ES_AUTOVSCROLL |WS_BORDER|WS_CHILD | WS_VISIBLE|ES_MULTILINE|ES_WANTRETURN ,AAA,&m_wndTabs,IDS_EDIT3);
	// Esp_Mod_Scrollbar_Start: Added Scrollbars to the third edit box
	Edit3.Create(ES_AUTOVSCROLL | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN, AAA, &m_wndTabs, IDS_EDIT3);
	// Esp_Mod_Scrollbar_End
	//// momo ModernOpenGL_Start
	////EditViewScales.Create(ES_AUTOVSCROLL | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN, AAA, &m_wndTabs, IDS_EDIT_VIEW_SCALES);
	//// momo ModernOpenGL_End

	// Esp_Mod_Font_Start: Initialized font and assigned to windows. The number in the next line sets the font size, where 100 is about 12pt (normal).
	// momo
	// momo// m_Font.CreatePointFont(150, _T("Arial")); // Change "Arial" to any font installed on your system. there are many installed already by windows. you can search Fonts in window settings. Personalization > Fonts. Also could change the size by tweeking first argument.
	m_Font.CreateFont(
	    -13, 0, 0, 0, FW_BLACK, FALSE, FALSE, FALSE,
	    ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	    CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS,
	    _T("Arial"));
	// momo
	Edit1.SetFont(&m_Font);
	Edit2.SetFont(&m_Font);
	Edit3.SetFont(&m_Font);
	// Esp_Mod_Font_End
	//// momo ModernOpenGL_Start
	////EditViewScales.SetFont(&m_Font);
	//// momo ModernOpenGL_End

	// MoMo_Start
	Edit1.SetReadOnly(TRUE);
	Edit2.SetReadOnly(TRUE);
	// MoMo_End

	return 0;
}

void CInputPane::OnSize(UINT nType, int cx, int cy) {
	CDockablePane::OnSize(nType, cx, cy);
	m_wndTabs.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	// TODO: Add your message handler code here

	CRect CbarSz;
	this->GetWindowRect(&CbarSz);
	// avoids overlapping with the arrow controls on the bottom left
	CbarSz.DeflateRect(0, 15);
	int h = CbarSz.Height();
	int w = CbarSz.Width();
	int TxtH = 25;
	Edit1.MoveWindow(5, 5, w / 2 - 5, h - TxtH - 10, TRUE);
	Edit2.MoveWindow(w / 2 + 5, 5, w / 2 - 10, h - 10, TRUE);
	Edit3.MoveWindow(5, h - TxtH - 5, w / 2 - 5, TxtH, TRUE);
	//// momo ModernOpenGL_Start
	////Edit2.MoveWindow(w / 2 + 5, 5, w / 2 - 10, h / 4, TRUE);
	////EditViewScales.MoveWindow(w / 2 + 5, h / 4 + 10, w / 4, h * 3 / 4 - 10, TRUE);
	//// momo ModernOpenGL_End
}

// void CInputPane::OnClose()
//{
//   // TODO: Add your message handler code here and/or call default
//
//   //CDockablePane::OnClose();
// }
