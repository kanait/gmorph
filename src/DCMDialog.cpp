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
// CDCMDialog �_�C�A���O


CDCMDialog::CDCMDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDCMDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDCMDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
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
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDCMDialog, CDialog)
	//{{AFX_MSG_MAP(CDCMDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCMDialog ���b�Z�[�W �n���h��

void CDCMDialog::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
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
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
//	CDialog::OnCancel();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );
	
	DestroyWindow();
}

extern CDCMDialog* dcmd;

void CDCMDialog::PostNcDestroy() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
//	CDialog::PostNcDestroy();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	dcmd = NULL;

	delete this;
}
