// DPFDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "OpenGL.h"
#include "DPFDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "edit.h"
#include "sellist.h"

/////////////////////////////////////////////////////////////////////////////
// CDPFDialog ダイアログ


CDPFDialog::CDPFDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDPFDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDPFDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}

CDPFDialog::Create()
{
	return CDialog::Create( CDPFDialog::IDD );
}

void CDPFDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDPFDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDPFDialog, CDialog)
	//{{AFX_MSG_MAP(CDPFDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDPFDialog メッセージ ハンドラ

void CDPFDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
//	CDialog::OnOK();

	ScreenAtr *screen;
	CEdit* cedit;

	// src
	screen = &(swin->screenatr[SCREEN_SRC]);
	if ( screen->sel_first != NULL ) {
		delete_face( screen );
		FreeSelectList( screen );

		cedit = (CEdit* )GetDlgItem( IDC_DPF_PF );
		cedit->SetWindowText("");

		screen->wnd->RedrawWindow();

		return;
	} 

	// dist
	screen = &(swin->screenatr[SCREEN_DIST]);
	if ( screen->sel_first != NULL ) {
		delete_face( screen );
		FreeSelectList( screen );

		cedit = (CEdit* )GetDlgItem( IDC_DPF_PF );
		cedit->SetWindowText("");

		screen->wnd->RedrawWindow();

		return;
	} 
}

void CDPFDialog::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
//	CDialog::OnCancel();
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	DestroyWindow();
}

extern CDPFDialog* dpfd;

void CDPFDialog::PostNcDestroy() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
//	CDialog::PostNcDestroy();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	dpfd = NULL;

	delete this;
}
