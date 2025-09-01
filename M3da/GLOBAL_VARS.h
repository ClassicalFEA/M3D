#pragma once

// MoMo_Start
#include <windows.h>
#include <afx.h>
class DSP_Triad;
class Symbol;
class PropTable;
class MatTable;
// MoMo_End

extern int gBACKGRD_COL;
extern bool gDOUBLEBUFF;
extern double gZOOM_SCL;
extern double gPT_SIZE;
extern double gND_SIZE;
extern double gLM_SIZE;
extern double gEL_SIZE;
extern double gED_SIZE;
extern double gFC_SIZE;
extern double gWP_SIZE;
extern double gBM_SIZE;
extern double gTXT_SIZE;
extern double gDIM_SCALE;
extern double gDIM_FILSZ;
extern double gDIM_OFFSZ;
extern double gTXT_HEIGHT;
extern double gDIM_RADSZ;
extern double gDIM_CVORD;
extern BOOL gDSP_CPTS;
extern BOOL gDSP_CIRS;
// MoMo_Start
struct SeedValues {
		BOOL IsSeedMode;
		BOOL SelectSurface;
		BOOL SelectSurfaceCurves;
		BOOL SelectLock;
		double InputedMeshElementSize = 1.0;
		int InputedSeedNumbers = 0;
};
extern SeedValues SeedVals;
extern CString LastRequest;
extern BOOL CurrentBufferResult;
extern BOOL m_leftIsDragging;
extern int m_x1;
extern int m_y1;
extern int m_x2;
extern int m_y2;
extern BOOL DeSelectAll;
extern BOOL StartLoad;
// MoMo_End
// momo
const int MAX_RESSETS = 10000;
extern int SelRowsCurrent[MAX_RESSETS][2];
extern int SelRowsNew[MAX_RESSETS][2];
extern bool DeselectCadrMode;
extern int SelectMode;
extern int MainDrawState;
extern bool AxisOrigin;
extern bool AxisCorner;
// momo
// momo change command box color
struct CommandIsActive {
		bool CurrentState;
		bool NewState;
		bool ChangeEdit1;
};
extern CommandIsActive CommIsActive;
// momo change command box color
// momo on off button and menu
struct ButtonPushed {
		bool Points;
		bool WireFrame;
		bool ShadedWithEdges;
		bool ShadedWithoutEdges;
		int DrawModeCurrent;
		int DrawModeOut;
		bool ControlPoint;
		bool DisplayAll;
		bool DisplaySelected;
		bool CurvesOn;
		bool SurfaceOn;
		bool CoordsOn;
		bool NodeOn;
		bool ElementOn;
		bool BoundaryConditionsOn;
		bool ShellThicknessOn;
		bool ElementCoordSysOn;
		bool SurfaceDirectionMarkersOn;
		bool WorkplaneOn;
		bool LabelOn;
		bool GeomOn;
		bool FiniteOn;
		bool QfilterNodesOn;
		bool QfilterElementsOn;
		bool QfilterPointsOn;
		bool QfilterCurvesOn;
		bool QfilterSurfacesOn;
		bool SelectedOn;
		bool FullBody;
		bool PartOfBody;
		bool CenterOfBody;
};
extern ButtonPushed ButtonPush;
// momo on off button and menu
// momo gdi to og2
struct ClickPoint {
		bool IsClicked;
		int x;
		int y;
};
extern ClickPoint mClickPoint;
// momo gdi to og2
// momo change Display Flags Method
struct DisplayFlags {
		bool DSP_WIREFRAME;
		bool DSP_SHADED_WITH_EDGES;
		bool DSP_NODES;
		bool DSP_NODES_ASK;
		bool DSP_SHADED_EDGES;
		bool DSP_ELEMENTS;
		bool DSP_CURVES;
		bool DSP_SURFACES;
		bool DSP_THK;
		bool DSP_OFF;
		bool DSP_SURC;
		bool DSP_POINTS;
		bool DSP_BLACK;
		bool DSP_ASSEM;
		bool DSP_CONT;
		bool DSP_RESLAB;
		bool DSP_RESDEF;
		bool DSP_ELSYS;
		bool DSP_BC;
		bool DSP_GRAD;
		bool DSP_MATL;
		bool DSP_COORD;
		bool DSP_WP;
		bool DSP_SURFU;
		bool DSP_ANIMATION;
		bool DSP_ANIMPOSNEG;
		bool DSP_VEC;
};
// momo change Display Flags Method
extern BOOL gDSP_BACK;
extern BOOL gORTHO;
extern DSP_Triad tOrient;
extern int iNoSymbols;
extern double dAveW;
extern double dAveH;
extern Symbol* pSymTable[10000];
extern int gDIM_PREC;
extern double gDIM_SIZE;
extern int gCUR_RES;
extern double gDRILL_KS; // K value for shell drilling
extern double gRIGID_MULTIPLIER; // multiplier to factor psuedo rigid elemenys K values
extern double gVSTIFF_KS;
extern double gDEF_E;
extern double gDEF_V;
extern double gDEF_DEN;
extern double gDEF_COND;
extern double gSTIFF_BDIA;
extern double gDEF_CTE;
extern double gDEF_THERM_LNK;
extern double gDEF_SOL_TOL;
extern PropTable* PropsT;
extern MatTable* MatT;

// Esp_Mod_Labels_4_27_2025_Start: Added global var for label display
extern bool gLBL_DSP_TRG;
// Esp_Mod_Labels_4_27_2025_End