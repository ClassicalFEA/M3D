
// M3daView.cpp : implementation of the CM3daView class
//

#include "stdafx.h"
#include "M3da.h"
#include "M3daDoc.h"
#include "M3daView.h"
#include "resource.h"
#include "math.h"
#include "GLOBAL_VARS.h"
// MoMo_Start
#include "AppSettings.h"
// MoMo_End
DSP_Triad tOrient;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CM3daView

IMPLEMENT_DYNCREATE(CM3daView, CView)

BEGIN_MESSAGE_MAP(CM3daView, CView)
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CM3daView::OnFilePrintPreview)
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_LBUTTONDBLCLK()
ON_WM_MOUSEMOVE()
ON_WM_SIZE()
ON_WM_MOVE()
ON_WM_RBUTTONDOWN()
ON_WM_RBUTTONUP()
// momo
// momo// ON_COMMAND(ID_VIEW_DISPLAYALL, &CM3daView::OnViewDisplayall)
// momo
ON_COMMAND(ID_VIEW_DISPLAYSELECTED, &CM3daView::OnViewDisplayselected)
ON_COMMAND(ID_VIEW_DISPLAYGROUP, &CM3daView::OnViewDisplaygroup)
ON_COMMAND(ID_VIEW_WIREFRAME, &CM3daView::OnViewWireframe)
ON_COMMAND(ID_VIEW_SHADED, &CM3daView::OnViewShadedWithEdges)
// momo on off button and menu
ON_UPDATE_COMMAND_UI(ID_VIEW_WIREFRAME, &CM3daView::OnUpdateViewWireframe)
ON_UPDATE_COMMAND_UI(ID_VIEW_SHADED, &CM3daView::OnUpdateViewShadedWithEdges)
ON_UPDATE_COMMAND_UI(ID_VIEW_DISPLAYSELECTED, &CM3daView::OnUpdateDisplayselected)
ON_COMMAND(ID_VIEW_SHADED_WITHOUT_EDGES, &CM3daView::OnViewShadedWithoutEdges)
ON_UPDATE_COMMAND_UI(ID_VIEW_SHADED_WITHOUT_EDGES, &CM3daView::OnUpdateViewShadedWithoutEdges)
// momo on off button and menu
ON_COMMAND(ID_VIEW_LOCATEEYE, &CM3daView::OnViewLocateeye)
ON_COMMAND(ID_VIEW_RESETVIEW, &CM3daView::OnViewResetview)
//  ON_WM_MOUSEHWHEEL()
ON_WM_MBUTTONDBLCLK()
ON_WM_MBUTTONUP()
ON_WM_MOUSEWHEEL()
ON_COMMAND(ID_VIEW_ZOOMALL, &CM3daView::OnViewZoomall)
ON_WM_MBUTTONDOWN()
ON_COMMAND(ID_VIEW_TOP, &CM3daView::OnViewTop)
ON_COMMAND(ID_VIEW_FRONT, &CM3daView::OnViewFront)
ON_COMMAND(ID_VIEW_LEFTXY, &CM3daView::OnViewLeftxy)
ON_COMMAND(ID_VIEW_BACK, &CM3daView::OnViewBack)
ON_COMMAND(ID_VIEW_RIGHT, &CM3daView::OnViewRight)
ON_COMMAND(ID_VIEW_BOTTOMXZ, &CM3daView::OnViewBottomxz)
ON_COMMAND(ID_PROJWP, &CM3daView::OnProjwp)
ON_COMMAND(ID_PROJ_FRONT, &CM3daView::OnProjFront)
ON_COMMAND(ID_PROJ_BOTTOMXZ, &CM3daView::OnProjBottomxz)
ON_COMMAND(ID_PROJ_TOP, &CM3daView::OnProjTop)
ON_COMMAND(ID_PROJ_LEFTXY, &CM3daView::OnProjLeftxy)
ON_COMMAND(ID_PROJ_RIGHT, &CM3daView::OnProjRight)
ON_COMMAND(ID_PROJ_BACK, &CM3daView::OnProjBack)
ON_COMMAND(ID_PROJISO1, &CM3daView::OnProjso1)
ON_COMMAND(ID_PROJISO2, &CM3daView::OnPropiso2)
ON_COMMAND(ID_EDIT_UNDO, &CM3daView::OnEditUndo)
ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CM3daView::OnUpdateEditUndo)
ON_COMMAND(ID_EDIT_REDO, &CM3daView::OnEditRedo)
ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CM3daView::OnUpdateEditRedo)
END_MESSAGE_MAP()

// CM3daView construction/destruction

CM3daView::CM3daView() {
	// TODO: add construction code here
	m_iFuncKey = 0;
	bF = TRUE;
	tOrient.Create(1);
}

CM3daView::~CM3daView() {
}

BOOL CM3daView::PreCreateWindow(CREATESTRUCT& cs) {
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CM3daView drawing

void CM3daView::OnDraw(CDC* pDC) {
	int x;
	int y;

	x = pDC->GetDeviceCaps(VERTRES);
	y = pDC->GetDeviceCaps(HORZRES);
	m_rcClient = CRect(0, 0, y, x);
	GetDocument()->SetScreenMat(m_rcClient);
	CM3daDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SetView(this);
	if (bF == TRUE) {
		CDC* pDC2 = this->GetDC();
		pDoc->InitOGL(pDC2);
		bF = FALSE;
	}
	// momo gdi to og
	// momo// pDoc->Draw(tOrient.RetrieveMat(), pDC, 4);
	pDoc->Draw(tOrient.RetrieveMat(), 4);
	// momo gdi to og
}

// CM3daView printing

void CM3daView::OnFilePrintPreview() {
	AFXPrintPreview(this);
}

BOOL CM3daView::OnPreparePrinting(CPrintInfo* pInfo) {
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CM3daView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: add extra initialization before printing
}

void CM3daView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: add cleanup after printing
}

void CM3daView::OnRButtonUp(UINT nFlags, CPoint point) {
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CM3daView::OnContextMenu(CWnd* pWnd, CPoint point) {
	// momo
	//  momo// theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT_MANAGER, point.x, point.y, this, TRUE);
	// momo
}

// CM3daView diagnostics

#ifdef _DEBUG
void CM3daView::AssertValid() const {
	CView::AssertValid();
}

void CM3daView::Dump(CDumpContext& dc) const {
	CView::Dump(dc);
}

CM3daDoc* CM3daView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CM3daDoc)));
	return (CM3daDoc*) m_pDocument;
}
#endif //_DEBUG

void CM3daView::m_UpdateTriad(int iMag) {
	double d1;
	double d2;
	double dWidth = m_rcClient.right - m_rcClient.left;
	double dHeight = m_rcClient.bottom - m_rcClient.top;
	CPoint point;
	double dX1;
	double dY1;
	double dZ1;
	double dSR;
	d1 = m_PointNew.x - m_PointOld.x;
	d2 = m_PointNew.y - m_PointOld.y;
	double WPSize;
	WPSize = GetDocument()->GetWPSize();
	if (m_iFuncKey == 1) // calculate translation
	{
		// Calculate a meaningful translation

		dX1 = 2 * (d1 / dWidth) * WPSize;
		dY1 = -2 * (d2 / dWidth) * WPSize;
		dZ1 = 0;
		tOrient.Trans(dX1, dY1, dZ1);
	} else if (m_iFuncKey == 2) // scale // momo: zoom
	{
		double dS = tOrient.GetScl(); // new
		dSR = 0.1;
		if (iMag < 2) {
			dSR = 0.02;
		}
		if (d2 < 0) {
			tOrient.Scl(-dS * dSR * gZOOM_SCL);
		} else {
			tOrient.Scl(dS * dSR * gZOOM_SCL);
		}
		// momo
		// momo// } else if (m_iFuncKey == 3) // scale
	} else if (m_iFuncKey == 3) // rotate
	                            // momo
	{
		dSR = 1;
		if (iMag < 2) {
			dSR = 0.5;
		}
		d1 = 180 * d1 / dHeight * dSR;
		d2 = 180 * d2 / dHeight * dSR;
		if (m_PointOld.x > (dWidth * 0.8)) {
			tOrient.Rot(0.0f, 0.0f, (float) -d2);
		} else {
			tOrient.Rot((float) d2, (float) d1, 0.0f);
		}
	}
}

// momo gdi to og
// void CM3daView::ClearScr()
//
//{
//	CRect rc;
//	CDC* pDC = this->GetDC();
//	GetClientRect(&rc);
//	CBrush br(RGB(0, 0, 0));
//	pDC->FillRect(&rc, &br);
//	ReleaseDC(pDC);
//}
// momo gdi to og
// CM3daView message handlers

void CM3daView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// TODO: Add your message handler code here and/or call default

	if ((nChar == 112) || (nChar == 17)) { // momo: F1 key or Ctrl key (move)
		m_iFuncKey = 1;
	} else if (nChar == 113) { // momo: F2 key (zoom)
		m_iFuncKey = 2;
	} else if ((nChar == 114) || (nChar == 16)) { // momo: F3 key or Shift key (rotate)
		m_iFuncKey = 3;
	} else if (nChar == 13) { // momo: Enter key (done)
		m_iFuncKey = 4;
	} else if (nChar == 27) { // momo: Escape key (cancel)
		m_iFuncKey = 5;
	} else if (nChar == 46) { // momo: Delete key (delete)
		m_iFuncKey = 6;
	} else {
		m_iFuncKey = 0;
	}
	m_iMouseButStat = 0;
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CM3daView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// TODO: Add your message handler code here and/or call default
	if ((m_iFuncKey == 1) || (m_iFuncKey == 2) || (m_iFuncKey == 3)) {
		// momo gdi to og
		// momo// CDC* pDC = this->GetDC();
		// momo gdi to og
		GetDocument()->SetView(this);
		CRect C;
		GetDocument()->SetScreenMat(C);
		// momo gdi to og
		// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
		GetDocument()->Draw(tOrient.RetrieveMat(), 4);
		// momo// ReleaseDC(pDC);
		// momo gdi to og
	} else if (m_iFuncKey == 4) {
		// MoMo_Start
		if (!SeedVals.IsSeedMode) {
			// MoMo_End
			outtextMSG2("D");
			// MoMo_Start
		} else {
			outtextMSG2("Done");
		}
		// MoMo_End
	} else if (m_iFuncKey == 5) {
		// MoMo_Start
		if (!SeedVals.IsSeedMode) {
			// MoMo_End
			outtextMSG2("C");
			// MoMo_Start
		} else {
			outtextMSG2("Cancel");
		}
		// MoMo_End
	} else if (m_iFuncKey == 6) {
		GetDocument()->DeleteObjs();
	} else {
	}
	m_iFuncKey = 0;
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CM3daView::OnLButtonDown(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	m_iMouseButStat = 1;
	// GetDocument()->SetLineStart(point);
	m_PointDown = point;

	CView::OnLButtonDown(nFlags, point);
}

void CM3daView::OnLButtonUp(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	CRect C;
	if (m_iMouseButStat == 1) {
		CView::OnLButtonUp(nFlags, point);
		int iMag;
		int iX, iY;
		iX = point.x - m_PointDown.x;
		iY = point.y - m_PointDown.y;
		double a, b;
		b = iX * iX + iY * iY;
		a = sqrt(b);
		iMag = (int) a;
		// momo
		// if (iMag > 20) {
		if (m_leftIsDragging) { // stop selection cadr
			// momo
			// MoMo_Start
			// if (CurrentBufferResult) {
			m_leftIsDragging = false;
			//}
			// MoMo_End
			GetDocument()->SelectBox(m_PointDown, point);
			// momo gdi to og
			// momo// CDC* pDC = this->GetDC();
			// momo gdi to og
			GetDocument()->SetView(this);
			GetDocument()->SetScreenMat(C);
			// momo gdi to og
			// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 5);
			GetDocument()->Draw(tOrient.RetrieveMat(), 5);
			// momo// ReleaseDC(pDC);
			// momo gdi to og
		} else {
			// momo gdi to og2
			// CDC* pDC = this->GetDC();
			//// if (GetDocument()->isBlackDisp())
			////   GetDocument()->SetPen(pDC,255,255,255);
			//// else
			////   GetDocument()->SetPen(pDC,0,0,0);
			//// Draw tick marker
			// CPen* Pen = new CPen(PS_SOLID, 1, RGB(255, 0, 0));
			// CPen* OldPen = pDC->SelectObject(Pen);
			// pDC->MoveTo(point.x - 5, point.y);
			// pDC->LineTo(point.x + 5, point.y);
			// pDC->MoveTo(point.x, point.y - 5);
			// pDC->LineTo(point.x, point.y + 5);
			//// GetDocument()->RestorePen(pDC);
			// pDC->SelectObject(OldPen);
			// delete (Pen);
			// ReleaseDC(pDC);
			mClickPoint.IsClicked = true;
			mClickPoint.x = point.x;
			mClickPoint.y = point.y;
			GetDocument()->Draw(tOrient.RetrieveMat(), 5);
			//  momo gdi to og2
			GetDocument()->DoMsg(1, point, point, _T("MouseInp"));
		}
	}
	m_iMouseButStat = 0;
	GetDocument()->SetView(this);
	// MoMo_Start
	m_leftIsDragging = false;
	// MoMo_End
	CView::OnLButtonUp(nFlags, point);
}

void CM3daView::OnLButtonDblClk(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	// momo gdi to og
	// momo// GetDocument()->UpTree();
	GetDocument()->UpTree(point);
	// momo gdi to og
	CView::OnLButtonDblClk(nFlags, point);
}

void CM3daView::OnMouseMove(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	int iMag = 0;
	int iX, iY;
	double a, b;
	CRect rc;
	m_PointNew = point;
	if ((m_iFuncKey != 0)) {
		iX = m_PointNew.x - m_PointOld.x;
		iY = m_PointNew.y - m_PointOld.y;
		b = iX * iX + iY * iY;
		a = sqrt(b);
		iMag = (int) a;
		m_UpdateTriad(iMag);
		// MoMo_Start
		if (iMag > 5 && m_iFuncKey == 1) { // start middle mouse draging
			m_middleIsDraging = true;
		}
		// MoMo// m_PointOld = m_PointNew;
		// MoMo_End
		// momo gdi to og
		// momo// CDC* pDC = this->GetDC();
		// momo gdi to og
		GetDocument()->SetView(this);
		// momo gdi to og
		// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 3);
		GetDocument()->Draw(tOrient.RetrieveMat(), 3);
		// momo gdi to og
		//// momo ModernOpenGL_Start
		////if (pDC != NULL) {
		//// momo ModernOpenGL_End
		// momo// ReleaseDC(pDC);
		//// momo ModernOpenGL_Start
		////}
		//// momo ModernOpenGL_End
	} else if (m_iMouseButStat == 1) {
		iX = m_PointNew.x - m_PointDown.x;
		iY = m_PointNew.y - m_PointDown.y;
		b = iX * iX + iY * iY;
		a = sqrt(b);
		iMag = (int) a;
		// iMag = (int) sqrt(pow(m_PointNew.x - m_PointDown.x,2) + pow(m_PointNew.y - m_PointDown.y,2));
		// momo
		// if (iMag > 20) {
		if (iMag > 5 || m_leftIsDragging) { // start selection cadr
			// momo
			// MoMo_Start
			// if (CurrentBufferResult) {
			m_leftIsDragging = true;
			m_x1 = m_PointDown.x;
			m_y1 = m_PointDown.y;
			m_x2 = point.x;
			m_y2 = point.y;
			//}
			// MoMo_End
			// momo gdi to og
			// momo// CDC* pDC = this->GetDC();
			// momo gdi to og
			GetDocument()->SetView(this);
			// MoMo_Start
			if (nFlags & MK_LBUTTON) {
				// MoMo_End
				// momo gdi to og
				// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 3);
				GetDocument()->Draw(tOrient.RetrieveMat(), 3);
				// momo gdi to og
				// momo// GetDocument()->DrawDrag(pDC, m_PointDown, point);
				// MoMo_Start
			} else {
				m_leftIsDragging = false;
				m_iMouseButStat = 0;
				CRect C;
				GetDocument()->SelectBox(m_PointDown, m_PointOld);
				GetDocument()->SetScreenMat(C);
				// momo gdi to og
				// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 5);
				GetDocument()->Draw(tOrient.RetrieveMat(), 5);
				// momo gdi to og
			}
			// MoMo_End
			// momo gdi to og
			// momo// ReleaseDC(pDC);
			// momo gdi to og
		}
	} else if (GetDocument()->isDragging()) {
		iX = m_PointNew.x - m_PointDown.x;
		iY = m_PointNew.y - m_PointDown.y;
		b = iX * iX + iY * iY;
		a = sqrt(b);
		iMag = (int) a;
		// iMag = (int) sqrt(pow(m_PointNew.x - m_PointDown.x,2) + pow(m_PointNew.y - m_PointDown.y,2));
		// momo
		// if (iMag > 20) {
		if (iMag > 0) { // apply draw draging
			// momo
			// momo gdi to og
			// momo// CDC* pDC = this->GetDC();
			// momo gdi to og
			GetDocument()->SetView(this);
			GetDocument()->DragUpdate(m_PointNew);
			// momo gdi to og
			// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 3);
			GetDocument()->Draw(tOrient.RetrieveMat(), 3);
			// momo gdi to og
			// GetDocument()->SetLineEnd(m_PointNew);
			// GetDocument()->LineDrag(pDC, m_PointDown, m_PointNew);
			// momo// ReleaseDC(pDC);
		}
	}

	m_PointOld = point;
	CView::OnMouseMove(nFlags, point);
}

void CM3daView::OnSize(UINT nType, int cx, int cy) {
	CView::OnSize(nType, cx, cy);
	CRect C;
	GetDocument()->SetView(this);
	GetDocument()->SetScreenMat(C);
	// TODO: Add your message handler code here
}

void CM3daView::OnMove(int x, int y) {
	CView::OnMove(x, y);
	CRect C;
	// GetDocument()->SetView(this);
	// GetDocument()->SetScreenMat(C);
	//  TODO: Add your message handler code here
}

void CM3daView::OnRButtonDown(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	// theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	CView::OnRButtonDown(nFlags, point);
}

// momo
// void CM3daView::OnViewDisplayall() {
//	// TODO: Add your command handler code here
//	// GetDocument()->DspAll();
//	if (GetDocument()->isMenuNULL())
//		outtextMSG2("DSPALL");
//	// CDC* pDC = this->GetDC();
//	// GetDocument()->SetView(this);
//	// GetDocument()->Draw(tOrient.RetrieveMat(),pDC,4);
//	// ReleaseDC(pDC);
//}
// momo

void CM3daView::OnViewDisplayselected() {
	// TODO: Add your command handler code here
	if (GetDocument()->isMenuNULL())
	// momo
	// momo// outtextMSG2("DSPSEL");
	{
		ButtonPush.SelectedOn = !ButtonPush.SelectedOn;
		if (ButtonPush.SelectedOn) {
			outtextMSG2("DSPSEL");
			outtext1("Selected Objects Visibility ON");
		} else {
			outtextMSG2("DSPALL");
			outtext1("Selected Objects Visibility OFF");
		}
	}
	// momo
	// GetDocument()->DspSel();
	// CDC* pDC = this->GetDC();
	// GetDocument()->SetView(this);
	// GetDocument()->Draw(tOrient.RetrieveMat(),pDC,4);
	// ReleaseDC(pDC);
}

void CM3daView::OnViewDisplaygroup() {
	// TODO: Add your command handler code here
	// GetDocument()->Dsp_Group();
	// if (GetDocument()->isMenuNULL())
	outtextMSG2("DSPGP");
}

void CM3daView::OnViewWireframe() {
	// TODO: Add your command handler code here
	// momo on off button and menu
	ButtonPush.WireFrame = !ButtonPush.WireFrame;
	// if (ButtonPush.WireFrame) {
	//	outtext1("Draw Wire Frame.");
	// } else {
	//	outtext1("Draw Shaded.");
	// }
	if (ButtonPush.WireFrame) {
		outtext1("Draw Wire Frame.");
		if (ButtonPush.DrawModeCurrent == 2) {
			ButtonPush.DrawModeOut = 3;
		} else if (ButtonPush.DrawModeCurrent == 3) {
			ButtonPush.DrawModeOut = 2;
		}
		ButtonPush.DrawModeCurrent = 1;
		ButtonPush.WireFrame = true;
		ButtonPush.ShadedWithEdges = false;
		ButtonPush.ShadedWithoutEdges = false;
	} else {
		if (ButtonPush.DrawModeOut != 3) {
			ButtonPush.DrawModeCurrent = 3;
			outtext1("Draw Shaded Without Edges.");
			ButtonPush.WireFrame = false;
			ButtonPush.ShadedWithEdges = false;
			ButtonPush.ShadedWithoutEdges = true;
		} else {
			outtext1("Draw Shaded With Edges.");
			ButtonPush.DrawModeCurrent = 2;
			ButtonPush.WireFrame = false;
			ButtonPush.ShadedWithEdges = true;
			ButtonPush.ShadedWithoutEdges = false;
		}
	}
	// momo// outtext1("Draw Wire Frame.");
	// momo on off button and menu
	// ClearScr();
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo on off button and menu
	// momo// GetDocument()->SetDrawType(0);
	GetDocument()->SetDrawType((int) !ButtonPush.WireFrame, !ButtonPush.ShadedWithoutEdges);
	// momo on off button and menu
	GetDocument()->InvalidateOGL();
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

void CM3daView::OnViewShadedWithEdges() {
	// TODO: Add your command handler code here
	// momo on off button and menu
	ButtonPush.ShadedWithEdges = !ButtonPush.ShadedWithEdges;
	// if (ButtonPush.WireFrame) {
	//	outtext1("Draw Wire Frame.");
	// } else {
	//	outtext1("Draw Shaded.");
	// }
	if (ButtonPush.ShadedWithEdges) {
		outtext1("Draw Shaded With Edges.");
		if (ButtonPush.DrawModeCurrent == 1) {
			ButtonPush.DrawModeOut = 3;
		} else if (ButtonPush.DrawModeCurrent == 3) {
			ButtonPush.DrawModeOut = 1;
		}
		ButtonPush.DrawModeCurrent = 2;
		ButtonPush.WireFrame = false;
		ButtonPush.ShadedWithEdges = true;
		ButtonPush.ShadedWithoutEdges = false;
	} else {
		if (ButtonPush.DrawModeOut != 3) {
			ButtonPush.DrawModeCurrent = 3;
			outtext1("Draw Shaded Without Edges.");
			ButtonPush.WireFrame = false;
			ButtonPush.ShadedWithEdges = false;
			ButtonPush.ShadedWithoutEdges = true;
		} else {
			outtext1("Draw Wire Frame.");
			ButtonPush.DrawModeCurrent = 1;
			ButtonPush.WireFrame = true;
			ButtonPush.ShadedWithEdges = false;
			ButtonPush.ShadedWithoutEdges = false;
		}
	}
	// momo// outtext1("Draw Shaded.");
	// momo on off button and menu
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo on off button and menu
	// momo// GetDocument()->SetDrawType(1);
	GetDocument()->SetDrawType((int) !ButtonPush.WireFrame, !ButtonPush.ShadedWithoutEdges);
	// momo on off button and menu
	GetDocument()->InvalidateOGL();
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

// momo
void CM3daView::OnViewShadedWithoutEdges() {
	ButtonPush.ShadedWithoutEdges = !ButtonPush.ShadedWithoutEdges;
	if (ButtonPush.ShadedWithoutEdges) {
		outtext1("Draw Shaded Without Edges.");
		if (ButtonPush.DrawModeCurrent == 1) {
			ButtonPush.DrawModeOut = 2;
		} else if (ButtonPush.DrawModeCurrent == 2) {
			ButtonPush.DrawModeOut = 1;
		}
		ButtonPush.DrawModeCurrent = 3;
		ButtonPush.WireFrame = false;
		ButtonPush.ShadedWithEdges = false;
		ButtonPush.ShadedWithoutEdges = true;
	} else {
		if (ButtonPush.DrawModeOut != 2) {
			outtext1("Draw Shaded With Edges.");
			ButtonPush.DrawModeCurrent = 2;
			ButtonPush.WireFrame = false;
			ButtonPush.ShadedWithEdges = true;
			ButtonPush.ShadedWithoutEdges = false;
		} else {
			outtext1("Draw Wire Frame.");
			ButtonPush.DrawModeCurrent = 1;
			ButtonPush.WireFrame = true;
			ButtonPush.ShadedWithEdges = false;
			ButtonPush.ShadedWithoutEdges = false;
		}
	}
	GetDocument()->SetView(this);
	GetDocument()->SetDrawType((int) !ButtonPush.WireFrame, !ButtonPush.ShadedWithoutEdges);
	GetDocument()->InvalidateOGL();
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
}
// momo

// momo on off button and menu
void CM3daView::OnUpdateViewWireframe(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(ButtonPush.WireFrame);
}

void CM3daView::OnUpdateViewShadedWithEdges(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(ButtonPush.ShadedWithEdges);
}

void CM3daView::OnUpdateViewShadedWithoutEdges(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(ButtonPush.ShadedWithoutEdges);
}

void CM3daView::OnUpdateDisplayselected(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(ButtonPush.SelectedOn);
}
// momo on off button and menu

void CM3daView::OnViewLocateeye() {
	// TODO: Add your command handler code here
	C3dVector vP;
	vP = GetDocument()->GetViewPt();
	tOrient.SetEye(vP.x, vP.y, vP.z);
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

void CM3daView::OnViewResetview() {
	// TODO: Add your command handler code here
	tOrient.ReSet();
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

// BOOL CM3daView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//   // This feature requires Windows Vista or greater.
//   // The symbol _WIN32_WINNT must be >= 0x0600.
//   // TODO: Add your message handler code here and/or call default
//   double dSR;
//   double dS = tOrient.GetScl(); // new
//   dSR=0.1;
//	if (zDelta < 0)
//   {
//      tOrient.Scl(-dS*dSR);
//	}
//	else
//   {
//	  tOrient.Scl(dS*dSR);
//	}
//   return CView::OnMouseHWheel(nFlags, zDelta, pt);
// }

void CM3daView::OnMButtonDblClk(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	outtextMSG2("C");
	CView::OnMButtonDblClk(nFlags, point);
}

void CM3daView::OnMButtonUp(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default

	m_iFuncKey = 0;
	CView::OnMButtonUp(nFlags, point);

	// MoMo_Start
	if (!SeedVals.IsSeedMode) {
		if (!m_middleIsDraging) {
			// MoMo_End
			outtextMSG2("D");
			// MoMo_Start
		}
	} else {
		if (!m_middleIsDraging) {
			outtextMSG2("Done");
		}
		m_middleIsDraging = false;
	}
	// MoMo_End
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo gdi to og
	//// momo ModernOpenGL_Start
	////if (pDC != NULL) {
	//// momo ModernOpenGL_End
	// momo// ReleaseDC(pDC);
	//// momo ModernOpenGL_Start
	////}
	//// momo ModernOpenGL_End
}

BOOL CM3daView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	// TODO: Add your message handler code here and/or call default

	double dS = tOrient.GetScl(); // new
	double dSR;
	dSR = 0.1;
	if (zDelta < 0) {
		tOrient.Scl(-dS * dSR * gZOOM_SCL);
	} else {
		tOrient.Scl(dS * dSR * gZOOM_SCL);
	}
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo gdi to og
	//// momo ModernOpenGL_Start
	////if (pDC != NULL) {
	//// momo ModernOpenGL_End
	// momo// ReleaseDC(pDC);
	//// momo ModernOpenGL_Start
	////}
	//// momo ModernOpenGL_End
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CM3daView::OnViewZoomall() {
	// TODO: Add your command handler code here
	C3dVector vP;
	int iYExt;
	int i;

	vP = GetDocument()->GetMeshCentre();
	tOrient.SetEye(vP.x, vP.y, vP.z);
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	// Centre the mesh and redraw
	// GetDocument()->Draw(tOrient.RetrieveMat(),pDC,5);
	GetDocument()->SetToScr2(tOrient.RetrieveMat());
	// Get the span of the model in pixels

	iYExt = GetDocument()->GetMeshYExt();
	if (iYExt > 0) {
		tOrient.dSclFact = 1;
		GetDocument()->SetToScr2(tOrient.RetrieveMat());
		// GetDocument()->Draw(tOrient.RetrieveMat(),pDC,5);
		double dS;
		iYExt = GetDocument()->GetMeshYExt();
		dS = GetDocument()->GetHeight() / iYExt;
		for (i = 10; i > 0; i--) {
			tOrient.dSclFact = dS / i;
			// momo gdi to og
			// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 5);
			GetDocument()->Draw(tOrient.RetrieveMat(), 5);
			// momo gdi to og
		}
		GetDocument()->SetToScr2(tOrient.RetrieveMat());
	}
	// momo gdi to og
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

void CM3daView::OnMButtonDown(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default

	CView::OnMButtonDown(nFlags, point);
	m_iFuncKey = 1;
}

void CM3daView::OnViewTop() {
}

void CM3daView::OnViewFront() {
	// TODO: Add your command handler code here
}

void CM3daView::OnViewLeftxy() {
	// TODO: Add your command handler code here
}

void CM3daView::OnViewBack() {
	// TODO: Add your command handler code here
}

void CM3daView::OnViewRight() {
	// TODO: Add your command handler code here
}

void CM3daView::OnViewBottomxz() {
	// TODO: Add your command handler code here
}

void CM3daView::OnProjwp() {
	// TODO: Add your command handler code here
	C3dMatrix mat;
	mat = GetDocument()->GetWPmat();
	tOrient.SetVIEW(mat);
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

void CM3daView::OnProjFront() {
	// TODO: Add your command handler code here
	tOrient.SetFrontView();
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

void CM3daView::OnProjBottomxz() {
	// TODO: Add your command handler code here
	tOrient.SetBottomView();
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

void CM3daView::OnProjTop() {
	// TODO: Add your command handler code here
	tOrient.SetTopView();
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

void CM3daView::OnProjLeftxy() {
	// TODO: Add your command handler code here
	tOrient.SetLeftView();
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

void CM3daView::OnProjRight() {
	// TODO: Add your command handler code here
	tOrient.SetRightView();
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

void CM3daView::OnProjBack() {
	// TODO: Add your command handler code here
	tOrient.SetBackView();
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

void CM3daView::OnProjso1() {
	// TODO: Add your command handler code here
	C3dMatrix mat;
	mat.MakeUnit();

	mat.Rotate(0, 45.0, 0);
	mat.Rotate(-35.564, 0.0, 0);
	tOrient.SetVIEW(mat);
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

void CM3daView::OnPropiso2() {
	// TODO: Add your command handler code here
	C3dMatrix mat;
	mat.MakeUnit();

	mat.Rotate(0, -45.0, 0);
	mat.Rotate(-35.564, 0.0, 0);
	tOrient.SetVIEW(mat);
	// momo gdi to og
	// momo// CDC* pDC = this->GetDC();
	// momo gdi to og
	GetDocument()->SetView(this);
	// momo gdi to og
	// momo// GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
	GetDocument()->Draw(tOrient.RetrieveMat(), 4);
	// momo// ReleaseDC(pDC);
	// momo gdi to og
}

void CM3daView::OnEditUndo() {
	// TODO: Add your command handler code here
	CM3daDoc* pDoc = NULL;
	pDoc = GetDocument();
	if (pDoc != NULL) {
		if (pDoc->bFinalChkPt == FALSE) {
			pDoc->CheckPoint();
			pDoc->bFinalChkPt = TRUE;
		}
		pDoc->Undo();
		// momo gdi to og
		// momo// CDC* pDC = this->GetDC();
		// momo// pDoc->Draw(tOrient.RetrieveMat(), pDC, 4);
		pDoc->Draw(tOrient.RetrieveMat(), 4);
		// momo// ReleaseDC(pDC);
		// momo gdi to og
	}
	// pDoc->UpdateAllViews(NULL);
}

void CM3daView::OnUpdateEditUndo(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
	CM3daDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->CanUndo());
}

void CM3daView::OnEditRedo() {
	// TODO: Add your command handler code here
	CM3daDoc* pDoc = GetDocument();
	pDoc->Redo();
	pDoc->UpdateAllViews(NULL);
}

void CM3daView::OnUpdateEditRedo(CCmdUI* pCmdUI) {
	// TODO: Add your command update UI handler code here
	CM3daDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->CanRedo());
}
