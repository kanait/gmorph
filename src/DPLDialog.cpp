//
// DPLDialog.cpp
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"
#include "OpenGL.h"
#include "DPLDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "edit.h"
#include "sellist.h"

/////////////////////////////////////////////////////////////////////////////
// CDPLDialog �_�C�A���O


CDPLDialog::CDPLDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDPLDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDPLDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}

CDPLDialog::Create()
{
	return CDialog::Create( CDPLDialog::IDD );
}

void CDPLDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDPLDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDPLDialog, CDialog)
	//{{AFX_MSG_MAP(CDPLDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDPLDialog ���b�Z�[�W �n���h��

void CDPLDialog::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
//	CDialog::OnOK();

//	if ( create_hvertex() == FALSE ) {
//		AfxMessageBox("Can't exec Create CV.");
//	}

	CEdit* cedit;
	cedit = (CEdit* )GetDlgItem( IDC_DPL_PL );
	cedit->SetWindowText("");

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );
}

void CDPLDialog::OnCancel() 
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
//	CDialog::OnCancel();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	DestroyWindow();
}

extern CDPLDialog* dpld;

void CDPLDialog::PostNcDestroy() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
	//CDialog::PostNcDestroy();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	dpld = NULL;

 	delete this;
}
