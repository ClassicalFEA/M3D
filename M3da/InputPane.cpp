// InputPane.cpp : implementation file
//

#include "stdafx.h"
#include "M3da.h"
#include "InputPane.h"
// momo make main buttons
#include "GLOBAL_VARS.h"
// momo make main buttons

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
	CRect rcEdit1(7, 7, 155, 40);
	Edit1.Create(ES_AUTOVSCROLL | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN, rcEdit1, &m_wndTabs, IDS_EDIT1);
	CRect rcEdit2(167, 7, 155, 40);
	Edit2.Create(ES_AUTOVSCROLL | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN, rcEdit2, &m_wndTabs, IDS_EDIT2);
	// Edit3.Create(ES_AUTOVSCROLL |WS_BORDER|WS_CHILD | WS_VISIBLE|ES_MULTILINE|ES_WANTRETURN ,AAA,&m_wndTabs,IDS_EDIT3);
	// Esp_Mod_Scrollbar_Start: Added Scrollbars to the third edit box
	// momo make main buttons
	// momo// Edit3.Create(ES_AUTOVSCROLL | WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN, AAA, &m_wndTabs, IDS_EDIT3);
	CRect rcEdit3(7, 52, 254, 20);
	Edit3.Create(ES_AUTOVSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN, rcEdit3, &m_wndTabs, IDS_EDIT3);
	CRect rcCancel(262, 52, 30, 20);
	buttonCancel.Create(_T("Cancel"), WS_CHILD | WS_VISIBLE | BS_FLAT | BS_PUSHBUTTON, rcCancel, &m_wndTabs, IDC_BUTTON_CANCEL);
	buttonCancel.EnableWindowsTheming(FALSE);
	buttonCancel.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	buttonCancel.m_bDrawFocus = FALSE;
	buttonCancel.SetFaceColor(RGB(128, 0, 0), TRUE);
	buttonCancel.SetTextColor(RGB(240, 240, 240));
	CRect rcDone(292, 52, 30, 20);
	buttonDone.Create(_T("Done"), WS_CHILD | WS_VISIBLE | BS_FLAT | BS_PUSHBUTTON, rcDone, &m_wndTabs, IDC_BUTTON_DONE);
	buttonDone.EnableWindowsTheming(FALSE);
	buttonDone.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	buttonDone.m_bDrawFocus = FALSE;
	buttonDone.SetFaceColor(RGB(0, 0, 0), TRUE);
	buttonDone.SetTextColor(RGB(240, 240, 240));

	// momo make main buttons
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
	// momo make main buttons
	buttonCancel.SetFont(&m_Font);
	buttonDone.SetFont(&m_Font);
	// momo make main buttons
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
	Edit1.MoveWindow(5, 5, w / 2 - 5, h - TxtH - 10 - 1, TRUE);
	Edit2.MoveWindow(w / 2 + 5, 5, w / 2 - 10, h - 10, TRUE);
	// momo make main buttons
	// momo// Edit3.MoveWindow(5, h - TxtH - 5, w / 2 - 5, TxtH, TRUE);
	int mainButtonsWidth = 60;
	CRect rc;
	Edit1.GetClientRect(&rc);
	int vScrollWidth = ::GetSystemMetrics(SM_CXVSCROLL);
	Edit3.MoveWindow(5, h - TxtH - 5, w / 2 - 5 - 2 * mainButtonsWidth - vScrollWidth - 2, TxtH, TRUE);
	buttonCancel.MoveWindow(5 + w / 2 - 5 - 2 * mainButtonsWidth - vScrollWidth - 1, h - TxtH - 5, mainButtonsWidth, TxtH, TRUE);
	buttonDone.MoveWindow(5 + w / 2 - 5 - 1 * mainButtonsWidth - vScrollWidth, h - TxtH - 5, mainButtonsWidth, TxtH, TRUE);
	buttonCancel.RedrawWindow();
	buttonDone.RedrawWindow();
	// momo make main buttons
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

// momo make main buttons
BEGIN_MESSAGE_MAP(CMyTabCtrl, CMFCTabCtrl)
ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CMyTabCtrl::OnButtonCancelClick)
ON_BN_CLICKED(IDC_BUTTON_DONE, &CMyTabCtrl::OnButtonDoneClick)
END_MESSAGE_MAP()

void CMyTabCtrl::OnButtonCancelClick() {
	OnCancelClicked();
}

void CMyTabCtrl::OnButtonDoneClick() {
	OnDoneClicked();
}
// momo make main buttons
