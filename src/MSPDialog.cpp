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
// CMSPDialog �_�C�A���O


CMSPDialog::CMSPDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMSPDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMSPDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
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
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMSPDialog, CDialog)
	//{{AFX_MSG_MAP(CMSPDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSPDialog ���b�Z�[�W �n���h��

void CMSPDialog::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
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
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
//	CDialog::OnCancel();
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	DestroyWindow();
}

extern CMSPDialog* mspd;

void CMSPDialog::PostNcDestroy() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
//	CDialog::PostNcDestroy();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	mspd = NULL;

	delete this;
}
