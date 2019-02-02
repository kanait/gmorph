//
// CMDialog.cpp
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"
#include "OpenGL.h"
#include "CMDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "edit.h"
#include "sellist.h"

/////////////////////////////////////////////////////////////////////////////
// CCMDialog ダイアログ


CCMDialog::CCMDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCMDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCMDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}

CCMDialog::Create()
{
//	m_ccv_src = 0;
	return CDialog::Create( CCMDialog::IDD );
}

void CCMDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCMDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCMDialog, CDialog)
	//{{AFX_MSG_MAP(CCMDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCMDialog メッセージ ハンドラ

void CCMDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
//	CDialog::OnOK();

	if ( create_hface() == FALSE ) {
		AfxMessageBox("Can't exec Create CMesh.");
	}
	
	CListBox* clist = (CListBox* )GetDlgItem( IDC_CCM_CV_LIST );
	clist->ResetContent();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );
	// redraw all
	swin->screenatr[SCREEN_SRC].wnd->RedrawWindow();
	swin->screenatr[SCREEN_DIST].wnd->RedrawWindow();
}

void CCMDialog::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
	CListBox* clist = (CListBox* )GetDlgItem( IDC_CCM_CV_LIST );
	clist->ResetContent();

	//CDialog::OnCancel();
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	DestroyWindow();
}

extern CCMDialog* ccmd;

void CCMDialog::PostNcDestroy() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
//	CDialog::PostNcDestroy();
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	ccmd = NULL;
	delete this;
}
