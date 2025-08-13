
// M3da.h : main header file for the M3da application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h" // main symbols
// MoMo_Material_SaveBugV1_05_20_2025_Start
#include <set>
// MoMo_Material_SaveBugV1_05_20_2025_End

// CM3daApp:
// See M3da.cpp for the implementation of this class
//

class CM3daApp: public CWinAppEx {
	public:
		CM3daApp();
		//  Overrides
	public:
		virtual BOOL InitInstance();
		virtual int ExitInstance();
		// Implementation
		COleTemplateServer m_server;
		// Server object for document creation
		BOOL m_bHiColorIcons;

		virtual void PreLoadState();
		virtual void LoadCustomState();
		virtual void SaveCustomState();
		// momo
		void OnFileNewMain();
		void OnFileOpenMain();
		// momo

		afx_msg void OnAppAbout();
		DECLARE_MESSAGE_MAP()
		afx_msg void OnFileRunscriptfile();

		// Esp_Mod_Config_File_Mod_Start//
	private:
		void LoadConfiguration();
		// Esp_Mod_Config_File_Mod_End//
};
// momo
// momo// void outtext1(CString AAA);
// momo// void outtext2(CString AAA);
void outtext1(const CString& AAA);
void outtext1(const char* AAA);
void outtext2(const CString& AAA);
void outtext2(const char* AAA);
// momo
// MoMo_Material_SaveBugV1_05_20_2025_Start
void outtextSprintf(const CString& formatString, int intValue, double floatValue, bool IsInt, int nText);
void outtextMultiLine(const CString& AAA, int nText);
void outtextMultiLine(const char* AAA, int nText);
// MoMo_Material_SaveBugV1_05_20_2025_End
void SendMsg(CString AAA);
void SetFocus();
void outtextMSG(CString AAA);
// momo
// momo// void outtextMSG2(CString AAA);
void outtextMSG2(const CString& AAA);
void outtextMSG2(const char* AAA);
// momo
//// momo ModernOpenGL_Start
////CString ReadText();
////void SetText(CString sIn);
//// momo ModernOpenGL_End
// momo change command box color
void CheckCommandEditColor(bool bForceToCheck);
// momo change command box color
// momo on off button and menu
void CheckPushedButtons(const char* sMode);
// momo on off button and menu

extern CM3daApp theApp;
