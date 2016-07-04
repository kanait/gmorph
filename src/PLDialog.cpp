// PLDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "OpenGL.h"
#include "PLDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "edit.h"
#include "sellist.h"

/////////////////////////////////////////////////////////////////////////////
// CPLDialog ダイアログ


CPLDialog::CPLDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPLDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPLDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}

CPLDialog::~CPLDialog( void )
{
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );
}

CPLDialog::Create()
{
	return CDialog::Create( CPLDialog::IDD );
}

void CPLDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPLDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPLDialog, CDialog)
	//{{AFX_MSG_MAP(CPLDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPLDialog メッセージ ハンドラ

void CPLDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
//	if (!UpdateData(TRUE)) {
//		TRACE0("UpdateData failed during dialog termination.\n");
//		return;
//	}

	ScreenAtr *screen;

	// src
	screen = &(swin->screenatr[SCREEN_SRC]);
	if ( screen->sel_first != NULL ) {
		create_boundaryloop( screen );
		FreeSelectList( screen );
		screen->wnd->RedrawWindow();
		return;
	} 

	// dist
	screen = &(swin->screenatr[SCREEN_DIST]);
	if ( screen->sel_first != NULL ) {
		create_boundaryloop( screen );
		FreeSelectList( screen );
		screen->wnd->RedrawWindow();
		return;
	} 

//	CDialog::OnOK();
}

void CPLDialog::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
//	CDialog::OnCancel();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	DestroyWindow();
}

extern CPLDialog* cpld;

void CPLDialog::PostNcDestroy() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
//	CDialog::PostNcDestroy();

	cpld = NULL;

	delete this;
}
