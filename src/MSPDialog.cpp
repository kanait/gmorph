//
// MSPDialog.cpp
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"
#include "OpenGL.h"
#include "MSPDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "edit.h"
#include "sellist.h"

/////////////////////////////////////////////////////////////////////////////
// CMSPDialog ダイアログ


CMSPDialog::CMSPDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMSPDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMSPDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}

CMSPDialog::Create()
{
	return CDialog::Create( CMSPDialog::IDD );
}

void CMSPDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMSPDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMSPDialog, CDialog)
	//{{AFX_MSG_MAP(CMSPDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSPDialog メッセージ ハンドラ

void CMSPDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
//	CDialog::OnOK();
	ScreenAtr *screen;

	// src
	screen = &(swin->screenatr[SCREEN_SRC]);
	if ( screen->sel_first != NULL ) {
// delete shortest path
//		if ( sg_create_spath( screen ) == FALSE ) {
//			AfxMessageBox("Can't create a shortest path.");
//		}
		FreeSelectList( screen );
		screen->wnd->RedrawWindow();
	} 

	// dist
	screen = &(swin->screenatr[SCREEN_DIST]);
	if ( screen->sel_first != NULL ) {
// delete shortest path
//		if ( sg_create_spath( screen ) == FALSE ) {
//			AfxMessageBox("Can't create a shortest path.");
//		}
		FreeSelectList( screen );
		screen->wnd->RedrawWindow();
	} 
	
	CListBox* clist = (CListBox* )GetDlgItem( IDC_MSP_PV );
	clist->ResetContent();

}

void CMSPDialog::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
//	CDialog::OnCancel();
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	DestroyWindow();
}

extern CMSPDialog* mspd;

void CMSPDialog::PostNcDestroy() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
//	CDialog::PostNcDestroy();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	mspd = NULL;

	delete this;
}
