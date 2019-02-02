//
// DistView.cpp
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"
#include "OpenGL.h"

#include "OpenGLDoc.h"
#include "DistView.h"

#include "Material.h"

// Include the OpenGL headers
#include "gl\gl.h"
#include "gl\glu.h"
//#include "gl\glaux.h"

// from C 
#include "smd.h"
#include "draw.h"
#include "screen.h"
#include "pick.h"
#include "dialog.h"
//#include "sellist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char* const CDistView::_ErrorStrings[]= {
	{"No Error"}, // 0
	{"Unable to get a DC"}, // 1
	{"ChoosePixelFormat failed"}, // 2
	{"SelectPixelFormat failed"}, // 3
	{"wglCreateContext failed"}, // 4
	{"wglMakeCurrent failed"}, // 5
	{"wglDeleteContext failed"}, // 6
	{"SwapBuffers failed"},  // 7
};

/////////////////////////////////////////////////////////////////////////////
// CDistView

IMPLEMENT_DYNCREATE(CDistView, CView)

CDistView::CDistView() : 
	m_hRC(0), m_pDC(0), m_ErrorString(_ErrorStrings[0])
{
}

CDistView::~CDistView()
{
}

BOOL CDistView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

//	cs.cx = swin->screenatr[SCREEN_DIST].width;
//	cs.cy = swin->screenatr[SCREEN_DIST].height;

	moving = FALSE;
	scaling = FALSE;

	return CView::PreCreateWindow(cs);
}

BEGIN_MESSAGE_MAP(CDistView, CView)
	//{{AFX_MSG_MAP(CDistView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDistView 診断

#ifdef _DEBUG
void CDistView::AssertValid() const
{
	CView::AssertValid();
}

void CDistView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

void CDistView::SetError( int e )
{
	// if there was no previous error, 
	// then save this one
	if ( _ErrorStrings[0] == m_ErrorString ) {
		m_ErrorString = _ErrorStrings[e];
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDistView メッセージ ハンドラ

int CDistView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: この位置に固有の作成用コードを追加してください

	InitializeOpenGL();

	return 0;
}

BOOL CDistView::InitializeOpenGL()
{
	m_pDC = new CClientDC( this );

	if ( m_pDC == NULL ) { // failure to get DC
		SetError(1);
		return FALSE;
	}

	if ( !SetupPixelFormat() ) {
		return FALSE;
	}

	if ( (m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc()) )
		== 0 ) {
		SetError(4);
		return FALSE;
	}

	if ( ::wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) == FALSE ) {
		SetError(5);
		return FALSE;
	}

	// specify black as clear color
	::glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	// specify the back of the buffer as clear depth
	::glClearDepth( 1.0f );
	// enable depth testing
	::glEnable( GL_DEPTH_TEST );
	::glDepthFunc( GL_LESS );

	// define lights
	::glEnable( GL_LIGHTING );
	::glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	
	// LIGHT No.0
	GLfloat lightZeroPosition[] = {100.0f, 50.0f, 100.0f, 0.0f};
	GLfloat lightZeroColor[] = {0.8f, 0.8f, 0.8f, 1.0f}; // green-tinted 
	::glEnable(GL_LIGHT0);
	::glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);
	::glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
	::glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, (GLfloat) 0.1);
	::glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, (GLfloat) 0.05);

	// LIGHT No.1
	GLfloat lightOnePosition[] = {-100.0f, 50.0f, 100.0f, 0.0f};
	GLfloat lightOneColor[] = {0.8f, 0.8f, 0.8f, 1.0f}; // red-tinted 
	::glEnable(GL_LIGHT1);
	::glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);
	::glLightfv(GL_LIGHT1, GL_DIFFUSE, lightOneColor);
	::glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, (GLfloat) 0.1);
	::glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, (GLfloat) 0.05);

	::glDisable( GL_LIGHTING );
  
	return TRUE;
}

BOOL CDistView::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
		1,								// version number
		PFD_DRAW_TO_WINDOW |			// support window
		PFD_SUPPORT_OPENGL |			// support OpenGL
		PFD_DOUBLEBUFFER,				// double buffered
		PFD_TYPE_RGBA,					// RGBA type
		24,								// 24-bit color depth
		0, 0, 0, 0, 0, 0,				// color bits ignored
		0,								// no alpha buffer
		0,								// shift bit ignored
		0,								// no accumulation buffer
		0, 0, 0, 0,						// accum bits ignored
		16,								// 16-bit z-buffer
		0,								// no stencil buffer
		0,								// no auxiliary buffer
		PFD_MAIN_PLANE,					// main layer
		0,								// reserved
		0, 0, 0							// layer masks ignored
	};
	int pixelformat;

	if ( (pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd))
		== 0 ) {
		SetError(2);
		return FALSE;
	}

	if ( ::SetPixelFormat( m_pDC->GetSafeHdc(), pixelformat, &pfd )
		== FALSE ) {
		SetError(3);
		return FALSE;
	}

	return TRUE;
}

void CDistView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	
	if ( ::wglMakeCurrent( 0, 0 ) == FALSE ) {
		SetError(2);
	}
	if ( ::wglDeleteContext( m_hRC ) == FALSE ) {
		SetError(6);
	}
	if ( m_pDC ) {
		delete m_pDC;
	}

}

BOOL CDistView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
//	return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

void CDistView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください

	ScreenAtr *screen;
	screen = &(swin->screenatr[SCREEN_DIST]);
	screen->width = cx; screen->height = cy;

//	CString string;
//	string.Format("(dist) w, h: %d %d", screen->width, screen->height );
//	AfxMessageBox( string );

}

/////////////////////////////////////////////////////////////////////////////
// CDistView 描画

void CDistView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください

	if ( ::wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) == FALSE ) {
		SetError(5);
		return;
	}

	ScreenAtr *screen;
	screen = &( swin->screenatr[SCREEN_DIST] );

	clear_gl3d( screen );
	::glPushMatrix();
	view_init( screen );

	::glPushMatrix();
	draws3d( screen );
	::glPopMatrix();

	::glFinish();

	if ( ::SwapBuffers( m_pDC->GetSafeHdc() ) == FALSE ) {
		SetError(7);
	}

}


void CDistView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
	CView::OnLButtonDown(nFlags, point);

	scrn_x = point.x;
	scrn_y = point.y;
	if ( GetKeyState( VK_SHIFT ) < 0 ) { 
		moving = TRUE;
		return;
	}

	if ( GetKeyState( VK_CONTROL ) < 0 ) {
		scaling = TRUE;
		return;
	}

	moving  = FALSE;
	scaling = FALSE;

	ScreenAtr *screen = &(swin->screenatr[SCREEN_DIST]);

	COpenGLDoc* pDoc = (COpenGLDoc *) GetDocument();
	CRect rectSave;
	pDoc->m_tracker.GetTrueRect(rectSave);
	if (pDoc->m_tracker.HitTest(point) < 0) {

		// just to demonstrate CRectTracker::TrackRubberBand
		CRectTracker tracker;
		// (8,8) 以上のサイズにならないとラバーバンドにならない
		if (tracker.TrackRubberBand(this, point, pDoc->m_bAllowInvert)) {

			// pick area
			if ( edit_pick_area( 
				scrn_x, 
				scrn_y, 
				scrn_x + tracker.m_rect.Width(),
				scrn_y + tracker.m_rect.Height(),
				swin->edit_type, 
				screen
				) == TRUE ) {

				// input vertex ID to src edit box
				SelectToDialog( swin->edit_type, screen );

				InvalidateRect( NULL, FALSE );
			}
//			CString string;
//			string.Format("(begin) %d %d (end) %d %d", 
//				scrn_x, scrn_y,
//				scrn_x + tracker.m_rect.Width(),
//				scrn_y + tracker.m_rect.Height()
//				);
//			AfxMessageBox( string );
			// see if rubber band intersects with the doc's tracker

		} else {

			// pick only
			if ( edit_pick( point.x, point.y, swin->edit_type, screen )
				== TRUE ) {

				// input vertex ID to src edit box
				SelectToDialog( swin->edit_type, screen );

				InvalidateRect( NULL, FALSE );
			}

		}

	} else if (pDoc->m_tracker.Track(this, point, pDoc->m_bAllowInvert)) {

		// normal tracking action, when tracker is "hit"
		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL, (LPARAM)(LPCRECT)rectSave);
		pDoc->UpdateAllViews(NULL);

	} else {

	}
}

void CDistView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
	CView::OnLButtonUp(nFlags, point);

	moving  = FALSE;
	scaling = FALSE;
}

void CDistView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
	CView::OnMouseMove(nFlags, point);

	if ( moving && (GetKeyState(VK_SHIFT) < 0 ) ) { 

		int dx = point.x - scrn_x;
		int dy = point.y - scrn_y;
		update_screen3d_rotate( &(swin->screenatr[SCREEN_DIST]), dx, dy );
		scrn_x = point.x;
		scrn_y = point.y;
		InvalidateRect( NULL, FALSE );

	} else if ( scaling && (GetKeyState(VK_CONTROL) < 0 ) ) { 

		int dx = point.x - scrn_x;
		int dy = point.y - scrn_y;
		update_screen3d_zoom( &(swin->screenatr[SCREEN_DIST]), dx, dy );
		scrn_x = point.x;
		scrn_y = point.y;
		InvalidateRect( NULL, FALSE );

	}
}
