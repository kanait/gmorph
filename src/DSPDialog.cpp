//
// DSPDialog.cpp
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"
#include "OpenGL.h"
#include "DSPDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "edit.h"
#include "sellist.h"

/////////////////////////////////////////////////////////////////////////////
// CDSPDialog �_�C�A���O


CDSPDialog::CDSPDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDSPDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDSPDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}

CDSPDialog::Create()
{
	return CDialog::Create( CDSPDialog::IDD );
}

void CDSPDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDSPDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDSPDialog, CDialog)
	//{{AFX_MSG_MAP(CDSPDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSPDialog ���b�Z�[�W �n���h��

void CDSPDialog::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
	//CDialog::OnOK();

	ScreenAtr *screen;

	// src
	screen = &(swin->screenatr[SCREEN_SRC]);
	if ( screen->sel_first != NULL ) {
// delete shortest path
		if ( delete_spath( screen ) == FALSE ) {
			AfxMessageBox("Can't delete a shortest path.");
		}
		FreeSelectList( screen );
		screen->wnd->RedrawWindow();
	} 

	// dist
	screen = &(swin->screenatr[SCREEN_DIST]);
	if ( screen->sel_first != NULL ) {
// delete shortest path
		if ( delete_spath( screen ) == FALSE ) {
			AfxMessageBox("Can't delete a shortest path.");
		}
		FreeSelectList( screen );
		screen->wnd->RedrawWindow();
	} 
	
	CWnd* wnd;
	CString string;
	
	wnd = GetDlgItem( IDC_DSP_SP );
	if ( wnd == NULL ) return;
	string.Format("");
	wnd->SetWindowText( string );

	wnd = GetDlgItem( IDC_DSP_SC );
	if ( wnd == NULL ) return;
	string.Format("");
	wnd->SetWindowText( string );

}

void CDSPDialog::OnCancel() 
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
//	CDialog::OnCancel();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	DestroyWindow();
}

extern CDSPDialog* dspd;

void CDSPDialog::PostNcDestroy() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
//	CDialog::PostNcDestroy();
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	dspd = NULL;

	delete this;
}
