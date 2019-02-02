//
// DCMDialog.cpp
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"
#include "OpenGL.h"
#include "DCMDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "edit.h"
#include "sellist.h"

/////////////////////////////////////////////////////////////////////////////
// CDCMDialog ダイアログ


CDCMDialog::CDCMDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDCMDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDCMDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}

CDCMDialog::Create()
{
	return CDialog::Create( CDCMDialog::IDD );
}

void CDCMDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDCMDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDCMDialog, CDialog)
	//{{AFX_MSG_MAP(CDCMDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCMDialog メッセージ ハンドラ

void CDCMDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
//	CDialog::OnOK();

	if ( delete_hface() == FALSE ) {
		AfxMessageBox("Can't exec Delete CMesh.");
	}
	
	CEdit* cedit;
	cedit = (CEdit* )GetDlgItem( IDC_DCM_CM );
	cedit->SetWindowText("");

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	// redraw all
	swin->screenatr[SCREEN_SRC].wnd->RedrawWindow();
	swin->screenatr[SCREEN_DIST].wnd->RedrawWindow();
}

void CDCMDialog::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
//	CDialog::OnCancel();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );
	
	DestroyWindow();
}

extern CDCMDialog* dcmd;

void CDCMDialog::PostNcDestroy() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
//	CDialog::PostNcDestroy();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	dcmd = NULL;

	delete this;
}
