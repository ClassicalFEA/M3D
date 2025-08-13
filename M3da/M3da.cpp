
// M3da.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "M3da.h"
#include "MainFrm.h"

#include "M3daDoc.h"
#include "M3daView.h"

// Esp_Mod_Config_File_Mod_Start
#include "GLOBAL_VARS.h"
// Esp_Mod_Config_File_Mod_End

// momo
#include "AppSettings.h"
// momo

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// MoMo_Start
SeedValues SeedVals;
CString LastRequest = "";
BOOL CurrentBufferResult = false;
BOOL m_leftIsDragging = false;
BOOL DeSelectAll = false;
BOOL StartLoad = true;
int m_x1 = 0;
int m_y1 = 0;
int m_x2 = 0;
int m_y2 = 0;
bool DeselectCadrMode = true;
int SelectMode = 3;
int MainDrawState = 0;
bool AxisOrigin = false;
bool AxisCorner = false;
// MoMo_End
// momo
int SelRowsCurrent[MAX_RESSETS][2];
int SelRowsNew[MAX_RESSETS][2];
// for (int i = 0; i < MAX_RESSETS; i++) {
//	for (int j = 0; j < 2; j++) {
//		SelRowsCurrent[i][j] = 0;
//		SelRowsNew[i][j] = 0;
//	}
// }
// momo
// momo change command box color
CommandIsActive CommIsActive;
// momo change command box color
// momo on off button and menu
ButtonPushed ButtonPush;
// momo on off button and menu

// CM3daApp

BEGIN_MESSAGE_MAP(CM3daApp, CWinAppEx)
ON_COMMAND(ID_APP_ABOUT, &CM3daApp::OnAppAbout)
// Standard file based document commands
// momo
// momo// ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
// momo// ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
// momo
// Standard print setup command
ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
ON_COMMAND(ID_FILE_RUNSCRIPTFILE, &CM3daApp::OnFileRunscriptfile)
END_MESSAGE_MAP()

// CM3daApp construction

CM3daApp::CM3daApp() {
	m_bHiColorIcons = TRUE;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// momo
void CM3daApp::OnFileNewMain() {
	OnFileNew();
}

void CM3daApp::OnFileOpenMain() {
	OnFileOpen();
}
// momo

// The one and only CM3daApp object

CM3daApp theApp;
// This identifier was generated to be statistically unique for your app
// You may change it if you prefer to choose a specific identifier

// {A7226713-7CA7-4243-8B24-4C7AA36D1FA3}
static const CLSID clsid =
    {0xA7226713, 0x7CA7, 0x4243, {0x8B, 0x24, 0x4C, 0x7A, 0xA3, 0x6D, 0x1F, 0xA3}};

const GUID CDECL BASED_CODE _tlid =
    {0x28298EED, 0x2921, 0x46EF, {0x91, 0x77, 0x73, 0x8, 0x5F, 0x11, 0x18, 0x28}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

// Esp_Mod_Config_File_Mod_Start

// Global variables for configuration settings
void CM3daApp::LoadConfiguration() {
	CStdioFile file;
	if (file.Open(_T("config.txt"), CFile::modeRead | CFile::shareDenyWrite)) {
		CString strLine;
		while (file.ReadString(strLine)) {
			strLine.Trim(); // Remove leading/trailing whitespace

			// Skip empty lines or comment lines that start with '*'
			if (strLine.IsEmpty() || strLine.Left(1) == _T("*"))
				continue;

			// Expecting "key, value" format
			int commaPos = strLine.Find(_T(","));
			if (commaPos != -1) {
				CString key = strLine.Left(commaPos);
				CString value = strLine.Mid(commaPos + 1);
				key.Trim();
				value.Trim();

				// Update settings based on key
				if (key.CompareNoCase(_T("background_color")) == 0) {
					gBACKGRD_COL = _ttoi(value);
				} else if (key.CompareNoCase(_T("zoom_scale_factor")) == 0) {
					gZOOM_SCL = _ttof(value);
				} else if (key.CompareNoCase(_T("point_size")) == 0) {
					gPT_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("node_size")) == 0) {
					gND_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("lump_mass_size")) == 0) {
					gLM_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("element_edge_size")) == 0) {
					gEL_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("free_edge_size")) == 0) {
					gED_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("free_face_size")) == 0) {
					gFC_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("workplane_line_weight")) == 0) {
					gWP_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("beam_section_size")) == 0) {
					gBM_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("text_size")) == 0) {
					gTXT_SIZE = _ttoi(value);
				} else if (key.CompareNoCase(_T("drawing_scale_for_dims")) == 0) {
					gDIM_SCALE = _ttof(value);
				} else if (key.CompareNoCase(_T("fillet_size")) == 0) {
					gDIM_FILSZ = _ttof(value);
				} else if (key.CompareNoCase(_T("line_offset")) == 0) {
					gDIM_OFFSZ = _ttof(value);
				} else if (key.CompareNoCase(_T("text_height")) == 0) {
					gTXT_HEIGHT = _ttof(value);
				} else if (key.CompareNoCase(_T("circle_radius_for_circr")) == 0) {
					gDIM_RADSZ = _ttof(value);
				} else if (key.CompareNoCase(_T("spline_order")) == 0) {
					gDIM_CVORD = _ttoi(value);
				} else if (key.CompareNoCase(_T("dimesion_precision")) == 0) {
					gDIM_PREC = _ttoi(value);
				} else if (key.CompareNoCase(_T("dimension_size")) == 0) {
					gDIM_SIZE = _ttof(value);
				} else if (key.CompareNoCase(_T("trim_curve_on_surface_resolution")) == 0) {
					gCUR_RES = _ttoi(value);
				} else if (key.CompareNoCase(_T("shell_drilling_k_value")) == 0) {
					gDRILL_KS = _ttof(value);
				} else if (key.CompareNoCase(_T("stiffness_multiplier_for_m3d_dummy_rigid")) == 0) {
					gRIGID_MULTIPLIER = _ttof(value);
				} else if (key.CompareNoCase(_T("k_for_restraints")) == 0) {
					gVSTIFF_KS = _ttof(value);
				} else if (key.CompareNoCase(_T("default_material_E")) == 0) {
					gDEF_E = _ttof(value);
				} else if (key.CompareNoCase(_T("default_material_v")) == 0) {
					gDEF_V = _ttof(value);
				} else if (key.CompareNoCase(_T("default_material_density")) == 0) {
					gDEF_DEN = _ttof(value);
				} else if (key.CompareNoCase(_T("default_material_thermal_conductivity")) == 0) {
					gDEF_COND = _ttof(value);
				} else if (key.CompareNoCase(_T("default_siff_beam_diameter")) == 0) {
					gSTIFF_BDIA = _ttof(value);
				} else if (key.CompareNoCase(_T("default_material_cte")) == 0) {
					gDEF_CTE = _ttof(value);
				} else if (key.CompareNoCase(_T("default_thermal_link_coeff")) == 0) {
					gDEF_THERM_LNK = _ttof(value);
				} else if (key.CompareNoCase(_T("default_iterative_solver_toleranace")) == 0) {
					gDEF_SOL_TOL = _ttof(value);
				}
			}
		}
		file.Close();
	} else {
		AfxMessageBox(_T("Failed to open config.txt."));
	}
}
// Esp_Mod_Config_File_Mod_End

// CM3daApp initialization

// MoMo: program start from here (int main() or main.cpp)

BOOL CM3daApp::InitInstance() {
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit()) {
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	// MoMo_Start
	// MoMo// SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	SetRegistryKey(_T("M3D-DevM-Reg-14"));
	// MoMo_End
	// momo
	SelRowsCurrent[0][0] = -1;
	ButtonPush.Points = false;
	ButtonPush.WireFrame = true;
	ButtonPush.Shaded = false;
	ButtonPush.ControlPoint = false;
	ButtonPush.DisplayAll = true;
	ButtonPush.DisplaySelected = false;
	ButtonPush.CurvesOn = false;
	ButtonPush.SurfaceOn = false;
	ButtonPush.CoordsOn = false;
	ButtonPush.NodeOn = false;
	ButtonPush.ElementOn = false;
	ButtonPush.BoundaryConditionsOn = false;
	ButtonPush.ShellThicknessOn = false;
	ButtonPush.ElementCoordSysOn = false;
	ButtonPush.SurfaceDirectionMarkersOn = false;
	ButtonPush.WorkplaneOn = false;
	ButtonPush.LabelOn = false;
	ButtonPush.GeomOn = false;
	ButtonPush.FiniteOn = false;
	ButtonPush.QfilterNodesOn = false;
	ButtonPush.QfilterElementsOn = false;
	ButtonPush.QfilterPointsOn = false;
	ButtonPush.QfilterCurvesOn = false;
	ButtonPush.QfilterSurfacesOn = false;
	ButtonPush.SelectedOn = false;
	ButtonPush.FullBody = true;
	ButtonPush.PartOfBody = false;
	ButtonPush.CenterOfBody = true;
	// momo
	// momo change command box color
	CommIsActive.CurrentState = false;
	CommIsActive.NewState = false;
	CommIsActive.ChangeEdit1 = false;
	// momo change command box color
	LoadStdProfileSettings(4); // Load standard INI file options (including MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
	                                             RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	////Esp_Mod_Config_File_Mod_Start//
	// Check if "config.txt" exists in the working directory
	CFileFind finder;
	if (finder.FindFile(_T("config.txt"))) {
		LoadConfiguration();
	} else {
		// TODO: If file no found, for example, set default values and make config.txt based on it
	}
	////Esp_Mod_Config_File_Mod_End//

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
	    IDR_MAINFRAME,
	    RUNTIME_CLASS(CM3daDoc),
	    RUNTIME_CLASS(CMainFrame), // main SDI frame window
	    RUNTIME_CLASS(CM3daView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// Connect the COleTemplateServer to the document template
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template
	m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
	// Note: SDI applications register server objects only if /Embedding
	//   or /Automation is present on the command line

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated) {
		// Register all OLE server factories as running.  This enables the
		//  OLE libraries to create objects from other applications
		COleTemplateServer::RegisterAll();

		// Don't show the main window
		// return TRUE;
	}
	// App was launched with /Unregserver or /Unregister switch.  Unregister
	// typelibrary.  Other unregistration occurs in ProcessShellCommand().
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister) {
		UnregisterShellFileTypes();
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT, NULL, NULL, FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
	}
	// App was launched standalone or with other switches (e.g. /Register
	// or /Regserver).  Update registry entries, including typelibrary.
	else {
		COleTemplateServer::RegisterAll();
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
	}
	// Roy
	// COleTemplateServer::RegisterAll();
	// m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
	// COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	// momo gdi to og
	CAppSettings settings;
	DeselectCadrMode = settings.ReadDeselectCadrMode();
	SelectMode = settings.ReadSelectMode();
	settings.ReadAxisMode(AxisOrigin, AxisCorner);
	// momo gdi to og
	// momo
	bool windowMaximized = settings.ReadWindowState();
	if (windowMaximized) {
		m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	} else {
		// momo
		m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
		// momo
	}
	// momo
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

// CAboutDlg dialog used for App About

int CM3daApp::ExitInstance() {
	// If you initialized COM, uninitialize it
	CoUninitialize();

	// Ensure base class cleanup is performed
	return CWinAppEx::ExitInstance();
}

class CAboutDlg: public CDialog {
	public:
		CAboutDlg();

		// Dialog Data
		enum { IDD = IDD_ABOUTBOX };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

		// Implementation
	protected:
		DECLARE_MESSAGE_MAP()
	public:
};

CAboutDlg::CAboutDlg()
    : CDialog(CAboutDlg::IDD) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)

END_MESSAGE_MAP()

// App command to run the dialog
void CM3daApp::OnAppAbout() {
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CM3daApp customization load/save methods

void CM3daApp::PreLoadState() {
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	// ASSERT(bNameValid);
	// momo
	// momo// GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT_MANAGER);
	// momo
}

void CM3daApp::LoadCustomState() {
}

void CM3daApp::SaveCustomState() {
}

// CM3daApp message handlers

void CM3daApp::OnFileRunscriptfile() {
	// TODO: Add your command handler code here
	char s1[200];
	CString Cmd;

	outtext1("RUN SCRIPT FILE");
	FILE* pFile;
	// TODO: Add your command handler code here
	CFileDialog FDia(TRUE, "txt", "*.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL);
	FDia.DoModal();
	CString sPath = FDia.GetPathName();
	CString sFile = FDia.GetFileName();
	if (sFile != "") {
		pFile = fopen(sPath, "r");
		if (pFile != NULL) {
			while (!feof(pFile)) {
				fgets(s1, 200, pFile);
				Cmd = s1;
				Cmd.Remove('\n');
				SendMsg(Cmd);
			}
		}
		fclose(pFile);
		outtext1("END OF SCRIPT FILE");
	}
}
