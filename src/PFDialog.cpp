// PFDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "OpenGL.h"
#include "PFDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "edit.h"
#include "sellist.h"

/////////////////////////////////////////////////////////////////////////////
// CPFDialog ダイアログ


CPFDialog::CPFDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPFDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPFDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}

CPFDialog::Create()
{
//	m_ccv_src = 0;
	return CDialog::Create( CPFDialog::IDD );
}

void CPFDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPFDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPFDialog, CDialog)
	//{{AFX_MSG_MAP(CPFDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPFDialog メッセージ ハンドラ

void CPFDialog::OnOK() 
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

		if ( create_face( screen ) == FALSE ) {
			AfxMessageBox("Can't create a face.");
		}
		FreeSelectList( screen );
		
		screen->wnd->RedrawWindow();

	} 

	// dist
	screen = &(swin->screenatr[SCREEN_DIST]);
	if ( screen->sel_first != NULL ) {

		if ( create_face( screen ) == FALSE ) {
			AfxMessageBox("Can't create a face.");
		}
		FreeSelectList( screen );

		screen->wnd->RedrawWindow();
	} 
	
	CListBox* clist = (CListBox* )GetDlgItem( IDC_CPF_PV_LIST );
	clist->ResetContent();

}

void CPFDialog::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
//	CDialog::OnCancel();

	CListBox* clist = (CListBox* )GetDlgItem( IDC_CPF_PV_LIST );
	clist->ResetContent();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	DestroyWindow();

}

extern CPFDialog* cpfd;

void CPFDialog::PostNcDestroy() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
//	CDialog::PostNcDestroy();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	cpfd = NULL;

	delete this;
}
