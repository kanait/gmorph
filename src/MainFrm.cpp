//
// MainFrm.cpp
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"
#include "OpenGL.h"
#include "SFIDialog.h"

#include "MainFrm.h"
#include "OpenGLDoc.h"
#include "OpenGLView.h"
#include "DistView.h"

#include "smd.h"
#include "ppd.h"
#include "ppdlist.h"
#include "ppdface.h"
#include "ppdnormal.h"
#include "gmorph.h"
#include "sigproc.h"
#include "hppd.h"
#include "pov.h"
#include "file.h"
#include "sgpaths.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_COAXIS, OnUpdateMenuScreenCoaxis)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_CV, OnUpdateMenuScreenCv)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_GROUP, OnUpdateMenuScreenGroup)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_HMAP, OnUpdateMenuScreenHmap)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_LOOP, OnUpdateMenuScreenLoop)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_PCM, OnUpdateMenuScreenPcm)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_SHADING, OnUpdateMenuScreenShading)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_SPATH, OnUpdateMenuScreenSpath)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_WIREFRAME, OnUpdateMenuScreenWireframe)
	ON_COMMAND(ID_MENU_SCREEN_SHADING, OnMenuScreenShading)
	ON_COMMAND(ID_MENU_SCREEN_WIREFRAME, OnMenuScreenWireframe)
	ON_COMMAND(ID_MENU_SCREEN_COAXIS, OnMenuScreenCoaxis)
	ON_COMMAND(ID_MENU_SCREEN_VERT, OnMenuScreenVert)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_VERT, OnUpdateMenuScreenVert)
	ON_COMMAND(ID_FILE_OPEN_DIST, OnFileOpenDist)
	ON_COMMAND(ID_FILE_OPEN_GMH, OnFileOpenGmh)
	ON_COMMAND(ID_FILE_SAVE_GMH, OnFileSaveGmh)
	ON_COMMAND(ID_FILE_SAVE_SRC, OnFileSaveSrc)
	ON_COMMAND(ID_FILE_SAVE_DIST, OnFileSaveDist)
	ON_COMMAND(ID_MORPH_CREATE_GPPD, OnMorphCreateGppd)
	ON_COMMAND(ID_MORPH_DELETE_GPPD, OnMorphDeleteGppd)
	ON_COMMAND(ID_MORPH_RESET, OnMorphReset)
	ON_COMMAND(ID_MORPH_SET_DIV, OnMorphSetDiv)
	ON_COMMAND(ID_MORPH_SPATH_CLEAR, OnMorphSpathClear)
	ON_COMMAND(ID_MORPH_SPATH_CREATE, OnMorphSpathCreate)
	ON_COMMAND(ID_MORPH_START, OnMorphStart)
	ON_COMMAND(ID_MENU_SCREEN_CV, OnMenuScreenCv)
	ON_COMMAND(ID_MENU_SCREEN_GROUP, OnMenuScreenGroup)
	ON_COMMAND(ID_MENU_SCREEN_HMAP, OnMenuScreenHmap)
	ON_COMMAND(ID_MENU_SCREEN_LOOP, OnMenuScreenLoop)
	ON_COMMAND(ID_MENU_SCREEN_PCM, OnMenuScreenPcm)
	ON_COMMAND(ID_MENU_SCREEN_SPATH, OnMenuScreenSpath)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_ENHANCED, OnUpdateMenuScreenEnhanced)
	ON_COMMAND(ID_MENU_SCREEN_ENHANCED, OnMenuScreenEnhanced)
	ON_COMMAND(ID_MENU_SCREEN_SMOOTH, OnMenuScreenSmooth)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_SMOOTH, OnUpdateMenuScreenSmooth)
	ON_COMMAND(ID_MENU_SCREEN_INTERP, OnMenuScreenInterp)
	ON_UPDATE_COMMAND_UI(ID_MENU_SCREEN_INTERP, OnUpdateMenuScreenInterp)
	ON_COMMAND(ID_FILE_SAVE_POV, OnFileSavePov)
	ON_COMMAND(ID_FILE_RECORD_POV, OnFileRecordPov)
	ON_COMMAND(ID_FILE_RECORD_BMP, OnFileRecordBmp)
	ON_COMMAND(ID_FILE_RECORD_PPD, OnFileRecordPpd)
	ON_COMMAND(ID_MENU_GENER_INTERP, OnMenuGenerInterp)
	ON_COMMAND(ID_MENU_FAIR_SP, OnMenuFairSp)
	ON_COMMAND(ID_FILE_OPEN_GPPD, OnFileOpenGppd)
	ON_COMMAND(ID_FILE_SAVE_GPPD, OnFileSaveGppd)
	ON_COMMAND(ID_MENU_SCREEN_RADIUS, OnMenuScreenRadius)
	ON_COMMAND(ID_MENU_SET_CONST, OnMenuSetConst)
	//}}AFX_MSG_MAP
//	ON_COMMAND_RANGE(ID_STYLE_LEFT, ID_STYLE_JUSTIFIED, OnChangeStyle)
//	ON_UPDATE_COMMAND_UI_RANGE(ID_STYLE_LEFT, ID_STYLE_JUSTIFIED, OnUpdateStyle)
	ON_COMMAND_RANGE(ID_EDIT_CREATE_PPDLOOP, ID_EDIT_CREATE_SPATH_MANUAL, 
					OnChangeStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_EDIT_CREATE_PPDLOOP, 
								ID_EDIT_CREATE_SPATH_MANUAL, 
								OnUpdateStyle)
//	ON_COMMAND_RANGE(IDS_CREATE_PPDLOOP, IDS_CREATE_SPATH_MANUAL, 
//					OnChangeStyleCombo)
//	ON_UPDATE_COMMAND_UI_RANGE(IDS_CREATE_PPDLOOP, 
//								IDS_EDIT_CREATE_SPATH_MANUAL, 
//								OnUpdateStyle)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ステータス ライン インジケータ
	ID_INDICATOR_KANA,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの構築/消滅

CMainFrame::CMainFrame()
{
	// TODO: この位置にメンバの初期化処理コードを追加してください。
	Swin *create_swin( void );

	swin = create_swin();
}

CMainFrame::~CMainFrame()
{
	void free_swin( Swin * );

	free_swin( swin );
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME) )
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // 作成に失敗
	}

	HWND hwndToolBarCtrl =
		m_wndToolBar.GetToolBarCtrl().m_hWnd;

	LONG lStyle =
		GetWindowLong( hwndToolBarCtrl, GWL_STYLE );

	lStyle |= TBSTYLE_FLAT;

	SetWindowLong( hwndToolBarCtrl, GWL_STYLE, lStyle );
	
	// StyleBar
   	if (!CreateStyleBar())
		return -1;

	// StatusBar
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // 作成に失敗
	}

	// TODO: もしツール チップスが必要ない場合、ここを削除してください。
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: ツール バーをドッキング可能にしない場合は以下の３行を削除
	//       してください。
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking( CBRS_ALIGN_ANY );
	DockControlBar( &m_wndToolBar );

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して、Window クラスやスタイルを
	//       修正してください。

	// window size

	cs.cx = swin->width;
	cs.cy = swin->height;

	cs.style &= ~WS_MAXIMIZEBOX;
	cs.style &= ~WS_THICKFRAME;

	return CFrameWnd::PreCreateWindow( cs );
}
// MySplitterWnd Member functions
//void CMySplitterWnd::OnLButtonDown(UINT nFlags, CPoint point)
//{
//    if (m_bTracking) return;    
//
//	int nHTInfo = HitTest(point);
//
//    if ( nHTInfo != 101 ) StartTracking(nHTInfo);
//}

// for Splitter, etc.
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
//	return CFrameWnd::OnCreateClient(lpcs, pContext);

//	CString string;
//	string.Format("w, h: %d %d", 
//					swin->screenatr[SCREEN_SRC].width,
//					swin->screenatr[SCREEN_SRC].height );
//	AfxMessageBox( string );

	ScreenAtr *screen1, *screen2;
	screen1 = &(swin->screenatr[SCREEN_SRC]);
	screen2 = &(swin->screenatr[SCREEN_DIST]);

//	CString string;
//	string.Format("(all) w, h: %d %d",  lpcs->cx, lpcs->cy );
//	AfxMessageBox( string );

	VERIFY( m_wndSplitter.CreateStatic( this, 1, 2 ) );
	m_wndSplitter.CreateView( 0, 0, RUNTIME_CLASS( COpenGLView ),
			CSize( 0, 0 ), pContext );
	m_wndSplitter.CreateView( 0, 1, RUNTIME_CLASS( CDistView ),
			CSize( 0, 0 ), pContext );

	screen1->wnd = m_wndSplitter.GetPane( 0, 0 );
	screen2->wnd = m_wndSplitter.GetPane( 0, 1 );

//	COpenGLView* pWnd = (COpenGLView *) m_wndSplitter.GetPane( 0, 0 );
//	CSize size = pWnd->GetTotalSize();

	m_wndSplitter.SetColumnInfo( 0, screen1->width, 0 );
	m_wndSplitter.SetColumnInfo( 1, screen2->width, 0 );
	m_wndSplitter.SetRowInfo( 0, screen1->height, 0 );

//	if ( !m_wndSplitter.CreateStatic( this, 1, 2 ) ||
//		!m_wndSplitter.CreateView( 0, 0, RUNTIME_CLASS( COpenGLView ),
//		CSize( screen1->width, screen1->height ), pContext)  ||
//		!m_wndSplitter.CreateView( 0, 1, RUNTIME_CLASS( CDistView ),
//		CSize( screen2->width, screen2->height ), pContext) ) {
//		TRACE0("Fail to create a split window.\n");
//		return FALSE;
//	}
//	m_wndSplitter.SetScrollStyle( WS_HSCROLL );

	return TRUE;
}

// for EditBar, etc.
static UINT BASED_CODE styles[] =
{
	// same order as in the bitmap 'styles.bmp'
	ID_SEPARATOR,           // for combo box (placeholder)
	ID_SEPARATOR,
	ID_EDIT_CREATE_PPDLOOP,
	ID_EDIT_DELETE_PPDLOOP,
	ID_EDIT_CREATE_PPDFACE,
	ID_EDIT_DELETE_PPDFACE,
	ID_EDIT_CREATE_CV,
	ID_EDIT_MOVE_CV,
	ID_EDIT_DELETE_CV,
	ID_EDIT_CREATE_CMESH,
	ID_EDIT_DELETE_CMESH,
	ID_EDIT_CREATE_SPATH,
	ID_EDIT_DELETE_SPATH,
	ID_EDIT_CREATE_SPATH_MANUAL,
//	ID_STYLE_LEFT,
//	ID_STYLE_CENTERED,
//	ID_STYLE_RIGHT,
//	ID_STYLE_JUSTIFIED,
};

BOOL CMainFrame::CreateStyleBar()
{
	const int nDropHeight = 400;

	if (!m_wndStyleBar.Create(this, WS_CHILD|WS_VISIBLE|CBRS_TOP|
			CBRS_TOOLTIPS|CBRS_FLYBY ) ||
		!m_wndStyleBar.LoadBitmap(IDB_EDITBAR_BITMAP) ||
		!m_wndStyleBar.SetButtons(styles, sizeof(styles)/sizeof(UINT)))
	{
		TRACE0("Failed to create stylebar\n");
		return FALSE;       // fail to create
	}

	// Create the combo box
	m_wndStyleBar.SetButtonInfo( 0, IDW_COMBO, TBBS_SEPARATOR, 150 );

	// Design guide advises 12 pixel gap between combos and buttons
	m_wndStyleBar.SetButtonInfo( 1, ID_SEPARATOR, TBBS_SEPARATOR, 10 );
	CRect rect;
	m_wndStyleBar.GetItemRect(0, &rect);
	rect.top = 0;
	rect.bottom = rect.top + nDropHeight;
	if (!m_wndStyleBar.m_comboBox.Create(
			CBS_DROPDOWNLIST|WS_VISIBLE|WS_TABSTOP,
			rect, &m_wndStyleBar, IDW_COMBO) )
	{
		TRACE0("Failed to create combo-box\n");
		return FALSE;
	}

	//  Fill the combo box
	CString szStyle;
	if (szStyle.LoadString(IDS_CREATE_PPDLOOP))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_DELETE_PPDLOOP))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_CREATE_PPDFACE))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_DELETE_PPDFACE))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_CREATE_CV))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_MOVE_CV))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_DELETE_CV))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_CREATE_CMESH))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_DELETE_CMESH))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_DELETE_SPATH))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_CREATE_SPATH))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_DELETE_SPATH))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_DELETE_SPATH))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);
	if (szStyle.LoadString(IDS_CREATE_SPATH_MANUAL))
		m_wndStyleBar.m_comboBox.AddString((LPCTSTR)szStyle);

//	CString string;
//	string.Format("item: %d",  m_wndStyleBar.m_comboBox.GetCount());
//	AfxMessageBox( string );

	//  Create a font for the combobox
	LOGFONT logFont;
	memset(&logFont, 0, sizeof(logFont));

	if (!::GetSystemMetrics(SM_DBCSENABLED))
	{
		// Since design guide says toolbars are fixed height so is the font.
#ifndef _MAC
		logFont.lfHeight = -12;
#else
		logFont.lfHeight = -14;     // looks better than 12 on Mac
#endif
		logFont.lfWeight = FW_BOLD;
		logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_MODERN;
		CString strDefaultFont;
		strDefaultFont.LoadString(IDS_DEFAULT_FONT);
		lstrcpy(logFont.lfFaceName, strDefaultFont);
		if (!m_wndStyleBar.m_font.CreateFontIndirect(&logFont))
			TRACE0("Could Not create font for combo\n");
		else
			m_wndStyleBar.m_comboBox.SetFont(&m_wndStyleBar.m_font);
	}
	else
	{
		m_wndStyleBar.m_font.Attach(::GetStockObject(SYSTEM_FONT));
		m_wndStyleBar.m_comboBox.SetFont(&m_wndStyleBar.m_font);
	}

	HWND hwndStyleBarCtrl =
		m_wndStyleBar.GetToolBarCtrl().m_hWnd;

	LONG lStyle =
		GetWindowLong( hwndStyleBarCtrl, GWL_STYLE );

	lStyle |= TBSTYLE_FLAT;

	SetWindowLong( hwndStyleBarCtrl, GWL_STYLE, lStyle );	

	return TRUE;
}

#include "PLDialog.h"
#include "DPLDialog.h"
#include "PFDialog.h"
#include "DPFDialog.h"
#include "CVDialog.h"
#include "CMDialog.h"
#include "DCMDialog.h"
#include "SPDialog.h"
#include "MSPDialog.h"
#include "DSPDialog.h"

CPLDialog *cpld;
CDPLDialog *dpld;
CPFDialog *cpfd;
CDPFDialog *dpfd;
CCVDialog *ccvd;
CCMDialog *ccmd;
CDCMDialog *dcmd;
CSPDialog *cspd;
CDSPDialog *dspd;
CMSPDialog *mspd;

void CMainFrame::OnChangeStyle( UINT nID )
{
	switch ( swin->edit_type ) {

	case EDIT_CREATE_PPDLOOP:

		if ( cpld != NULL ) {
			delete cpld;
			cpld = NULL;
		}
		break;
			
	case EDIT_DELETE_PPDLOOP:

		if ( dpld != NULL ) {
			delete dpld;
			dpld = NULL;
		}
		break;
			
	case EDIT_CREATE_PPDFACE:

		if ( cpfd != NULL ) {
			delete cpfd;
			cpfd = NULL;
		}
		break;
			
	case EDIT_DELETE_PPDFACE:

		if ( dpfd != NULL ) {
			delete dpfd;
			dpfd = NULL;
		}
		break;
			
	case EDIT_CREATE_CV:

		if ( ccvd != NULL ) {
			delete ccvd;
			ccvd = NULL;
		}
		break;

	case EDIT_CREATE_CMESH:

		if ( ccmd != NULL ) {
			delete ccmd;
			ccmd = NULL;
		}
		break;

	case EDIT_DELETE_CMESH:

		if ( dcmd != NULL ) {
			delete dcmd;
			dcmd = NULL;
		}
		break;

	case EDIT_CREATE_SPATH:

		if ( cspd != NULL ) {
			delete cspd;
			cspd = NULL;
		}
		break;

	case EDIT_DELETE_SPATH:

		if ( dspd != NULL ) {
			delete dspd;
			dspd = NULL;
		}
		break;

	case EDIT_CREATE_SPATH_MANU:

		if ( mspd != NULL ) {
			delete mspd;
			mspd = NULL;
		}
		break;
	}

	m_wndStyleBar.m_comboBox.SetCurSel((int)(nID-ID_STYLE_BASE));
	swin->edit_type = nID-ID_STYLE_BASE;

	BOOL bResult;

	switch ( swin->edit_type ) {

	case EDIT_CREATE_PPDLOOP:

		cpld = new CPLDialog;
		ASSERT_VALID( cpld );

		bResult = cpld->Create();
		ASSERT( bResult );

		break;
			
	case EDIT_DELETE_PPDLOOP:

		dpld = new CDPLDialog;
		ASSERT_VALID( dpld );

		bResult = dpld->Create();
		ASSERT( bResult );

		break;
			
	case EDIT_CREATE_PPDFACE:

		cpfd = new CPFDialog;
		ASSERT_VALID( cpfd );

		bResult = cpfd->Create();
		ASSERT( bResult );

		break;
			
	case EDIT_DELETE_PPDFACE:

		dpfd = new CDPFDialog;
		ASSERT_VALID( dpfd );

		bResult = dpfd->Create();
		ASSERT( bResult );

		break;
			
	case EDIT_CREATE_CV:

		ccvd = new CCVDialog;
		ASSERT_VALID( ccvd );

		bResult = ccvd->Create();
		ASSERT( bResult );

		break;

	case EDIT_CREATE_CMESH:

		ccmd = new CCMDialog;
		ASSERT_VALID( ccmd );

		bResult = ccmd->Create();
		ASSERT( bResult );

		break;

	case EDIT_DELETE_CMESH:

		dcmd = new CDCMDialog;
		ASSERT_VALID( dcmd );

		bResult = dcmd->Create();
		ASSERT( bResult );

		break;

	case EDIT_CREATE_SPATH:

		cspd = new CSPDialog;
		ASSERT_VALID( cspd );

		bResult = cspd->Create();
		ASSERT( bResult );

		break;

	case EDIT_DELETE_SPATH:

		dspd = new CDSPDialog;
		ASSERT_VALID( dspd );

		bResult = dspd->Create();
		ASSERT( bResult );

		break;

	case EDIT_CREATE_SPATH_MANU:

		mspd = new CMSPDialog;
		ASSERT_VALID( mspd );

		bResult = mspd->Create();
		ASSERT( bResult );

		break;
	}

//	CString string;
//	string.Format("Selected Edit Type No.%d", swin->edit_type );
//	AfxMessageBox( string );
}

//void CMainFrame::OnChangeStyleCombo( UINT nID )
//{
//	swin->edit_type = nID-IDS_STYLE_BASE;
//	CString string;
//	string.Format("Selected Edit Type No.%d", swin->edit_type );
//	AfxMessageBox( string );
//}

void CMainFrame::OnUpdateStyle(CCmdUI* pCmdUI)
{
	UINT nIndex = m_wndStyleBar.m_comboBox.GetCurSel();
	if ( (UINT)(ID_STYLE_BASE+nIndex) == pCmdUI->m_nID ) {
		pCmdUI->SetCheck( 1 );
	} else 
		pCmdUI->SetCheck( 0 );
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame メッセージ ハンドラ

static char BASED_CODE szppdFilter[] = "PPD Files (*.ppd)|*.ppd|All Files (*.*)|*.*||";
static char BASED_CODE szgmhFilter[] = "GMH Files (*.gmh)|*.gmh|All Files (*.*)|*.*||";
static char BASED_CODE szpovFilter[] = "POV Files (*.pov)|*.pov|All Files (*.*)|*.*||";

void CMainFrame::OnFileOpen() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください

	// 第一引数は OPEN のとき TRUE
	// 第二、三引数はファイルの種類
	CFileDialog filedlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						szppdFilter, NULL );

	if( filedlg.DoModal() == IDOK) {
//		CWaitCursor wait;
		CString filename;
		filename = filedlg.GetPathName();
		//filenameに選択したファイルのフルパスが入る

		char *lp;
		lp = filename.GetBuffer( BUFSIZ );
		Sppd *ppd;
		if ( (ppd = open_ppd( lp )) == NULL ) {
			AfxMessageBox("Filename was bad!");
			return;
		}
		
		if ( swin->screenatr[SCREEN_SRC].current_ppd != NULL ) {
			free_ppd( swin->screenatr[SCREEN_SRC].current_ppd );
			swin->screenatr[SCREEN_SRC].view_ppd = NULL;
		}

		swin->screenatr[SCREEN_SRC].current_ppd = ppd;
		swin->screenatr[SCREEN_SRC].view_ppd = ppd;
			
		InvalidateRect( NULL, FALSE );
	}
	
}

void CMainFrame::OnFileSaveSrc() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CFileDialog filedlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						szppdFilter, NULL );

	if( filedlg.DoModal() == IDOK) {
//		CWaitCursor wait;
		CString filename;
		filename = filedlg.GetPathName();
		//filenameに選択したファイルのフルパスが入る

		char *lp;
		lp = filename.GetBuffer( BUFSIZ );
		if ( swin->screenatr[SCREEN_SRC].current_ppd != (Sppd *) NULL ) {
			write_ppd_file( lp, swin->screenatr[SCREEN_SRC].current_ppd );
			strcpy( swin->screenatr[SCREEN_SRC].current_ppd->filename, lp );
		}
	}
}

void CMainFrame::OnFileOpenDist() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
	CFileDialog filedlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						szppdFilter, NULL );

	if( filedlg.DoModal() == IDOK) {
//		CWaitCursor wait;
		CString filename;
		filename = filedlg.GetPathName();
		//filenameに選択したファイルのフルパスが入る

		char *lp;
		lp = filename.GetBuffer( BUFSIZ );
		Sppd *ppd;
		if ( (ppd = open_ppd( lp )) == NULL ) {
			AfxMessageBox("Filename was bad!");
			return;
		}
		
		if ( swin->screenatr[SCREEN_DIST].current_ppd != NULL ) {
			free_ppd( swin->screenatr[SCREEN_DIST].current_ppd );
			swin->screenatr[SCREEN_DIST].view_ppd = NULL;
		}

		swin->screenatr[SCREEN_DIST].current_ppd = ppd;
		swin->screenatr[SCREEN_DIST].view_ppd = ppd;
			
		InvalidateRect( NULL, FALSE );
	}
	
}

void CMainFrame::OnFileSaveDist() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CFileDialog filedlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						szppdFilter, NULL );

	if( filedlg.DoModal() == IDOK) {
//		CWaitCursor wait;
		CString filename;
		filename = filedlg.GetPathName();
		//filenameに選択したファイルのフルパスが入る

		char *lp;
		lp = filename.GetBuffer( BUFSIZ );
		if ( swin->screenatr[SCREEN_DIST].current_ppd != (Sppd *) NULL ) {
			write_ppd_file( lp, swin->screenatr[SCREEN_DIST].current_ppd );
			strcpy( swin->screenatr[SCREEN_DIST].current_ppd->filename, lp );
		}
	}
}

void CMainFrame::OnFileOpenGmh() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CFileDialog filedlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						szgmhFilter, NULL );

	if( filedlg.DoModal() == IDOK) {
//		CWaitCursor wait;
		CString filename;
		filename = filedlg.GetPathName();
		//filenameに選択したファイルのフルパスが入る

		char *lp;
		lp = filename.GetBuffer( BUFSIZ );

		// Free previous gmh.
		if ( swin->hppd != NULL ) {
			free_hppd( swin->hppd );
		}

		// Open gmh file
		if ( (swin->hppd = open_gmh_file( lp )) == NULL ) {
			AfxMessageBox("Filename was bad!");
			return;
		}

		// Assign ppd files
		if ( swin->hppd->ppd1 != (Sppd *) NULL ) {
			swin->screenatr[SCREEN_SRC].current_ppd = swin->hppd->ppd1;
			swin->screenatr[SCREEN_SRC].view_ppd    = swin->hppd->ppd1;
		}
		if ( swin->hppd->ppd2 != (Sppd *) NULL ) {
			swin->screenatr[SCREEN_DIST].current_ppd = swin->hppd->ppd2;
			swin->screenatr[SCREEN_DIST].view_ppd    = swin->hppd->ppd2;
		}

		// Set window title in titlebar
//		set_windowtitle( str );

		SetWindowText( filename );

		InvalidateRect( NULL, FALSE );
	}
}

void CMainFrame::OnFileSaveGmh() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
	CFileDialog filedlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						szgmhFilter, NULL );

	if( filedlg.DoModal() == IDOK) {
		CString filename;
		filename = filedlg.GetPathName();
		//filenameに選択したファイルのフルパスが入る

		char *lp;
		lp = filename.GetBuffer( BUFSIZ );

		write_gmh_file( lp, swin->hppd );
	}

}

// POV-RAY file
void CMainFrame::OnFileSavePov() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CFileDialog filedlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
				szpovFilter, NULL );

	if( filedlg.DoModal() == IDOK) {
		CString filename;
		filename = filedlg.GetPathName();
		//filenameに選択したファイルのフルパスが入る

		char *povname;
		povname = filename.GetBuffer( BUFSIZ );
		
//		CString string;
//		string.Format("%s", lp );
//		AfxMessageBox( string );
		Sppd *ppd = swin->screenatr[SCREEN_SRC].current_ppd;
		char header[BUFSIZ], incname[BUFSIZ];
		filehead( povname, header );
		sprintf( incname, "%s.inc", header );
		write_ppdpov_file( povname, incname, ppd, &(swin->screenatr[SCREEN_SRC]) );
	}

}

void CMainFrame::OnFileOpenGppd() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
	CFileDialog filedlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						szppdFilter, NULL );

	if( filedlg.DoModal() == IDOK) {
//		CWaitCursor wait;
		CString filename;
		filename = filedlg.GetPathName();
		//filenameに選択したファイルのフルパスが入る

		char *lp;
		lp = filename.GetBuffer( BUFSIZ );
		Sppd *ppd;
		if ( (ppd = open_ppd( lp )) == NULL ) {
			AfxMessageBox("Filename was bad!");
			return;
		}
		swin->morph_ppd = ppd;
	}
}

////////////////////////////////////////////////////////////////////////
// Update Menu Screen Functions
////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateMenuScreenShading(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.shading == SMD_OFF ) {
		//swin->dis3d.shading = SMD_OFF;
		pCmdUI->SetCheck( 0 );
	} else {
//		swin->dis3d.shading = SMD_ON;
		pCmdUI->SetCheck( 1 );
	}
}

void CMainFrame::OnUpdateMenuScreenWireframe( CCmdUI* pCmdUI ) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.wire == SMD_OFF ) {
		pCmdUI->SetCheck( 0 );
	} else {
		pCmdUI->SetCheck( 1 );
	}
}

void CMainFrame::OnUpdateMenuScreenCoaxis(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.coaxis == SMD_OFF ) {
		pCmdUI->SetCheck( 0 );
	} else {
		pCmdUI->SetCheck( 1 );
	}
}

void CMainFrame::OnUpdateMenuScreenVert(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.vertex == SMD_OFF ) {
		pCmdUI->SetCheck( 0 );
	} else {
		pCmdUI->SetCheck( 1 );
	}
}

void CMainFrame::OnUpdateMenuScreenCv(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.cpoint == SMD_OFF ) {
		pCmdUI->SetCheck( 0 );
	} else {
		pCmdUI->SetCheck( 1 );
	}
}

void CMainFrame::OnUpdateMenuScreenGroup(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.group == SMD_OFF ) {
		pCmdUI->SetCheck( 0 );
	} else {
		pCmdUI->SetCheck( 1 );
	}
}

void CMainFrame::OnUpdateMenuScreenHmap(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.hmap == SMD_OFF ) {
		pCmdUI->SetCheck( 0 );
	} else {
		pCmdUI->SetCheck( 1 );
	}
}

void CMainFrame::OnUpdateMenuScreenLoop(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.loop == SMD_OFF ) {
		pCmdUI->SetCheck( 0 );
	} else {
		pCmdUI->SetCheck( 1 );
	}
}

void CMainFrame::OnUpdateMenuScreenPcm(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.cmesh == SMD_OFF ) {
		pCmdUI->SetCheck( 0 );
	} else {
		pCmdUI->SetCheck( 1 );
	}
}

void CMainFrame::OnUpdateMenuScreenSpath(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.spath == SMD_OFF ) {
		pCmdUI->SetCheck( 0 );
	} else {
		pCmdUI->SetCheck( 1 );
	}
}

////////////////////////////////////////////////////////////////////////
// Menu Screen Functions
////////////////////////////////////////////////////////////////////////
void CMainFrame::OnMenuScreenShading() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->dis3d.shading == SMD_ON ) 
		swin->dis3d.shading = SMD_OFF;
	else 
		swin->dis3d.shading = SMD_ON;

	InvalidateRect( NULL, FALSE );
}

void CMainFrame::OnMenuScreenWireframe() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->dis3d.wire == SMD_ON ) 
		swin->dis3d.wire = SMD_OFF;
	else 
		swin->dis3d.wire = SMD_ON;

	InvalidateRect( NULL, FALSE );
}

void CMainFrame::OnMenuScreenCoaxis() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->dis3d.coaxis == SMD_ON ) 
		swin->dis3d.coaxis = SMD_OFF;
	else 
		swin->dis3d.coaxis = SMD_ON;

	InvalidateRect( NULL, FALSE );
}

void CMainFrame::OnMenuScreenVert() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->dis3d.vertex == SMD_ON ) 
		swin->dis3d.vertex = SMD_OFF;
	else 
		swin->dis3d.vertex = SMD_ON;

	InvalidateRect( NULL, FALSE );
}


void CMainFrame::OnMenuScreenCv() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
	if ( swin->dis3d.cpoint == SMD_ON ) 
		swin->dis3d.cpoint = SMD_OFF;
	else 
		swin->dis3d.cpoint = SMD_ON;

	InvalidateRect( NULL, FALSE );
}

void CMainFrame::OnMenuScreenGroup() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->dis3d.group == SMD_ON ) 
		swin->dis3d.group = SMD_OFF;
	else 
		swin->dis3d.group = SMD_ON;

	InvalidateRect( NULL, FALSE );
}

void CMainFrame::OnMenuScreenHmap() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->dis3d.hmap == SMD_ON ) 
		swin->dis3d.hmap = SMD_OFF;
	else 
		swin->dis3d.hmap = SMD_ON;

	InvalidateRect( NULL, FALSE );
}

void CMainFrame::OnMenuScreenLoop() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->dis3d.loop == SMD_ON ) 
		swin->dis3d.loop = SMD_OFF;
	else 
		swin->dis3d.loop = SMD_ON;

	InvalidateRect( NULL, FALSE );
}

void CMainFrame::OnMenuScreenPcm() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->dis3d.cmesh == SMD_ON ) 
		swin->dis3d.cmesh = SMD_OFF;
	else 
		swin->dis3d.cmesh = SMD_ON;

	InvalidateRect( NULL, FALSE );
}

void CMainFrame::OnMenuScreenSpath() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->dis3d.spath == SMD_ON ) 
		swin->dis3d.spath = SMD_OFF;
	else 
		swin->dis3d.spath = SMD_ON;

	InvalidateRect( NULL, FALSE );
}

////////////////////////////////////////////////////////////////////////
// smooth Display.
////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateMenuScreenEnhanced(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.smooth == SMD_OFF ) {
		pCmdUI->SetCheck( 0 );
	} else {
		pCmdUI->SetCheck( 1 );
	}
}

void CMainFrame::OnMenuScreenEnhanced() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->dis3d.enhanced == SMD_ON ) 
		swin->dis3d.enhanced = SMD_OFF;
	else 
		swin->dis3d.enhanced = SMD_ON;

	InvalidateRect( NULL, FALSE );
}

////////////////////////////////////////////////////////////////////////
// Smooth Shading
////////////////////////////////////////////////////////////////////////
void CMainFrame::OnMenuScreenSmooth() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->dis3d.smooth == SMD_ON ) 
		swin->dis3d.smooth = SMD_OFF;
	else 
		swin->dis3d.smooth = SMD_ON;

	InvalidateRect( NULL, FALSE );
}

void CMainFrame::OnUpdateMenuScreenSmooth(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.smooth == SMD_OFF ) {
		pCmdUI->SetCheck( 0 );
	} else {
		pCmdUI->SetCheck( 1 );
	}
}

////////////////////////////////////////////////////////////////////////
// Interpolation Mesh Toggle
////////////////////////////////////////////////////////////////////////
void CMainFrame::OnMenuScreenInterp() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->dis3d.interp == SMD_ON ) {
		swin->dis3d.interp = SMD_OFF;
		swin->screenatr[SCREEN_SRC].view_ppd 
			= swin->screenatr[SCREEN_SRC].current_ppd;
		swin->screenatr[SCREEN_DIST].view_ppd 
			= swin->screenatr[SCREEN_DIST].current_ppd;	
	} else {
		swin->dis3d.interp = SMD_ON;
		swin->screenatr[SCREEN_SRC].view_ppd 
			= swin->morph_ppd;
		swin->screenatr[SCREEN_DIST].view_ppd = NULL;
		resetmorphppd( swin->morph_ppd );
	}

	InvalidateRect( NULL, FALSE );
}

void CMainFrame::OnUpdateMenuScreenInterp(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if ( swin->dis3d.interp == SMD_OFF ) {
		pCmdUI->SetCheck( 0 );
	} else {
		pCmdUI->SetCheck( 1 );
	}
}


//void CMainFrame::OnEditMakePpdface() 
//{
//	swin->edit_type = EDIT_FACE;
//}

//void CMainFrame::OnEditDeletePpdface() 
//{
//	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
//	swin->edit_type = EDIT_DEL_FACE;
//}

//////////////////////////////////////////////////////////////////////
// "Morph" Commands 
//////////////////////////////////////////////////////////////////////

void CMainFrame::OnMorphSpathCreate() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if ( swin->hppd == NULL ) return;
	SGShortestPathsCreate( swin->hppd );
}

void CMainFrame::OnMorphSpathClear() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
}

void CMainFrame::OnMorphCreateGppd() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
	if ( swin->hppd == (HPpd *) NULL ) {
		AfxMessageBox("We have not read a gmh file.");
		return;
	}
  
	if ( swin->morph_ppd != (Sppd *) NULL ) {
		clear_gmorph( swin->hppd );
		swin->morph_ppd = (Sppd *) NULL;
	}

	DWORD start = GetTickCount();
	if ( (swin->morph_ppd = ppdgmorph_v2( swin->hppd )) == (Sppd *) NULL ) {
		return;
	}
	DWORD end = GetTickCount();

	CString string, tmpstr, space;

	Sppd *ppd = swin->morph_ppd;

	string.Format( "GPPD information:\n\n" );
	tmpstr.Format( "Vertex:\t%d\n", ppd->vn );
	string += tmpstr;
	tmpstr.Format( "Face:\t%d\n", ppd->fn );
	string += tmpstr;
	tmpstr.Format( "\n" );
	string += tmpstr;
	tmpstr.Format( "Processed Time: %.2g sec (%u msec)", 
		((double) end - (double) start ) / 1000.0, end - start );
	string += tmpstr;
	AfxMessageBox( string );

//	PrintGPpd( swin->morph_ppd, end - start );
}

/*
void PrintGPpd( Sppd *ppd, int time )
{
	CString string, tmpstr, space;

	string.Format( "GPPD information:\n\n" );
	tmpstr.Format( "Vertex:\t%d\n", ppd->vn );
	string += tmpstr;
	tmpstr.Format( "Face:\t%d\n", ppd->fn );
	string += tmpstr;
	tmpstr.Format( "\n" );
	string += tmpstr;
	tmpstr.Format( "Processed Time: %d msec.", time );
	string += tmpstr;
	AfxMessageBox( string );
}
*/

void CMainFrame::OnMorphDeleteGppd() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
}

void CMainFrame::OnMorphStart() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	int  i, a;
	Spvt *v;
	Spfc *fc;

	if ( !(swin->dis3d.interp) ) {
		AfxMessageBox("Please set interpolation mesh toggle is on.");
		return;
	}

	Sppd *ppd = swin->morph_ppd;
    if ( ppd == (Sppd *) NULL ) {
		AfxMessageBox("GPPD is not calculated.");
		return;
	}

    int div = swin->mdiv - 1;
	for ( a = 0; a <= div; ++a ) {
		double q = (double) a / (double) div;
		double p = 1.0 - q;
		Vec *mvec1 = ppd->mvec1;
		Vec *mvec2 = ppd->mvec2;
		for (i = 0, v = ppd->spvt; v != (Spvt *) NULL; ++i, v = v->nxt) {
			v->vec.x = p * mvec1[i].x + q * mvec2[i].x;
			v->vec.y = p * mvec1[i].y + q * mvec2[i].y;
			v->vec.z = p * mvec1[i].z + q * mvec2[i].z;
		}
		/* update normal */
		for	( fc = ppd->spfc; fc != (Spfc *) NULL; fc = fc->nxt ) 
			calc_fnorm( fc );

		if ( swin->dis3d.smooth ) ppdnorm( ppd );

		swin->screenatr[SCREEN_SRC].wnd->RedrawWindow();
    }
}	

void CMainFrame::OnMorphReset() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	resetmorphppd( swin->morph_ppd );
	InvalidateRect( NULL, FALSE );
}

void CMainFrame::OnMorphSetDiv() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
}

// Record Files
void CMainFrame::OnFileRecordPov() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CFileDialog filedlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
				szpovFilter, NULL );

	if( filedlg.DoModal() == IDOK) {
		CString filename;
		filename = filedlg.GetPathName();
		//filenameに選択したファイルのフルパスが入る

		char *lp;
		lp = filename.GetBuffer( BUFSIZ );
		
//		CString string;
//		string.Format("%s", lp );
//		AfxMessageBox( string );

		Sppd *ppd = swin->morph_ppd;
		char header[BUFSIZ], povname[BUFSIZ], incname[BUFSIZ];
		filehead( lp, header );
		int div = swin->mdiv - 1;
		for ( int i = 0; i <= div; ++i ) {
			sprintf( povname, "%s%03d.pov", header, i+1 );
			sprintf( incname, "%s%03d.inc", header, i+1 );

			// create ppd
			double q = (double) i / (double) div;
			double p = 1.0 - q;
			Vec *mvec1 = ppd->mvec1;
			Vec *mvec2 = ppd->mvec2;
			int j;
			Spvt *v;
			for (j = 0, v = ppd->spvt; v != (Spvt *) NULL; ++j, v = v->nxt) {
				v->vec.x = p * mvec1[j].x + q * mvec2[j].x;
				v->vec.y = p * mvec1[j].y + q * mvec2[j].y;
				v->vec.z = p * mvec1[j].z + q * mvec2[j].z;
			}
			/* update normal */
			for	( Spfc *fc = ppd->spfc; fc != (Spfc *) NULL; fc = fc->nxt ) 
				calc_fnorm( fc );
			
			ppdnorm( ppd );

			write_ppdpov_file( povname, incname, ppd, &(swin->screenatr[SCREEN_SRC]) );
		}
	}

}

void CMainFrame::OnFileRecordBmp() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
}

void CMainFrame::OnFileRecordPpd() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
}

void CMainFrame::drawwindow()
{
	RedrawWindow();
}

#include "SIPDialog.h"

CSIPDialog* sipd;

// Fairing Functions
void CMainFrame::OnMenuGenerInterp() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください

	if ( swin->morph_ppd == NULL ) {
		AfxMessageBox(" gppd is not found. ");
		return;
	}

	sipd = new CSIPDialog;
	ASSERT_VALID( sipd );

	BOOL bResult = sipd->Create();
	ASSERT( bResult );
	
}

void CMainFrame::OnMenuFairSp() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください

	if ( swin->morph_ppd == NULL ) {
		AfxMessageBox(" gppd is not found. ");
		return;
	}
	
	CSFIDialog sfidlg( NULL );
	if( sfidlg.DoModal() == IDOK) {
		double	lambda = sfidlg.m_sfi_lmd;
		double	kpb = sfidlg.m_sfi_kpb;
		double  mu = 1.0 / ( kpb - (1.0 / lambda) );
		int		num = sfidlg.m_sfi_num;

		// ppd_signal_processing( swin->morph_ppd, lambda, mu, num );
		AfxMessageBox("fairing is done.");

		swin->screenatr[SCREEN_SRC].wnd->RedrawWindow();
		
	}
}


void CMainFrame::OnFileSaveGppd() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
	CFileDialog filedlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						szppdFilter, NULL );

	if( filedlg.DoModal() == IDOK) {
		CString filename;
		filename = filedlg.GetPathName();
		//filenameに選択したファイルのフルパスが入る

		char *lp;
		lp = filename.GetBuffer( BUFSIZ );
		if ( swin->morph_ppd != (Sppd *) NULL ) {
			write_ppd_file( lp, swin->morph_ppd );
			strcpy( swin->morph_ppd->filename, lp );
		}
	}
}

#include "SRDialog.h"

void CMainFrame::OnMenuScreenRadius() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください

	CSRDialog* srd = new CSRDialog;
	ASSERT_VALID( srd );

	BOOL bResult = srd->Create();
	ASSERT( bResult );
}

void CMainFrame::OnMenuSetConst() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
}
