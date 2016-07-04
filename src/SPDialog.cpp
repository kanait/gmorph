// SPDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "OpenGL.h"
#include "SPDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "edit.h"
#include "sellist.h"

/////////////////////////////////////////////////////////////////////////////
// CSPDialog ダイアログ


CSPDialog::CSPDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSPDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSPDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}

CSPDialog::Create()
{
	return CDialog::Create( CSPDialog::IDD );
}

void CSPDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSPDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSPDialog, CDialog)
	//{{AFX_MSG_MAP(CSPDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSPDialog メッセージ ハンドラ

void CSPDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
//	CDialog::OnOK();

//	if ( create_hface() == FALSE ) {
//		AfxMessageBox("Can't exec Create PPDFace.");
//	}

	ScreenAtr *screen;

	// src
	screen = &(swin->screenatr[SCREEN_SRC]);
	if ( screen->sel_first != NULL ) {
		if ( sg_create_spath( screen ) == FALSE ) {
			AfxMessageBox("Can't create a shortest path.");
		}
		FreeSelectList( screen );
		screen->wnd->RedrawWindow();
	} 

	// dist
	screen = &(swin->screenatr[SCREEN_DIST]);
	if ( screen->sel_first != NULL ) {
		if ( sg_create_spath( screen ) == FALSE ) {
			AfxMessageBox("Can't create a shortest path.");
		}
		FreeSelectList( screen );
		screen->wnd->RedrawWindow();
	} 
	
	CWnd* wnd;
	CString string;
	
	wnd = GetDlgItem( IDC_CSP_SRC );
	if ( wnd == NULL ) return;
	string.Format("");
	wnd->SetWindowText( string );

	wnd = GetDlgItem( IDC_CSP_DIST );
	if ( wnd == NULL ) return;
	string.Format("");
	wnd->SetWindowText( string );

}

void CSPDialog::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
//	CDialog::OnCancel();
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	DestroyWindow();
}

extern CSPDialog* cspd;

void CSPDialog::PostNcDestroy() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
//	CDialog::PostNcDestroy();
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	cspd = NULL;

	delete this;
}

