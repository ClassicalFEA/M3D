#pragma once

#include "MyEdit.h"
#include "EditBasic.h"

// Esp_Mod_Remove_Buttons_Start: Added A custom CMFCTabCtrl class than hides the scroll bar.
class CMyTabCtrl: public CMFCTabCtrl {
	public:
		// Override AdjustTabs to clear the scroll area
		virtual void AdjustTabs() {
			m_bScroll = FALSE;
			CMFCTabCtrl::AdjustTabs();
		}
};
// Esp_Mod_Remove_Buttons_End

// CInputPane

class CInputPane: public CDockablePane {
		DECLARE_DYNAMIC(CInputPane)

	public:
		CInputPane();
		virtual ~CInputPane();
		// Esp_Mod_Remove_Buttons_Start: Added A custom CMFCTabCtrl class than hides the scroll bar.
		CMyTabCtrl m_wndTabs;
		// Esp_Mod_Remove_Buttons_End

		// Esp_Mod_Font_Start: Added CFont object for the font
		CFont m_Font;
		// Esp_Mod_Font_End
		CEditBasic Edit1; // momo: "Command Report Text Box"
		CEditBasic Edit2; // momo: "Information Text Box"
		CMyEdit Edit3; // momo: "Command Entry Text Box"
		//// momo ModernOpenGL_Start
		////CMyEdit EditViewScales;
		//// momo ModernOpenGL_End

	protected:
		DECLARE_MESSAGE_MAP()
	public:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		//  afx_msg void OnClose();
};
