//
// CVDialog.cpp
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"
#include "OpenGL.h"
#include "CVDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "sellist.h"
#include "edit.h"

/////////////////////////////////////////////////////////////////////////////
// CCVDialog �_�C�A���O

CCVDialog::CCVDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCVDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCVDialog)
	m_ccv_src = 0;
	//}}AFX_DATA_INIT
}

CCVDialog::~CCVDialog( void )
{
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );
}

CCVDialog::Create()
{
//	m_ccv_src = 0;
	return CDialog::Create( CCVDialog::IDD );
}

void CCVDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCVDialog)
	DDX_Text(pDX, IDC_EDIT_CCV_SRC, m_ccv_src);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCVDialog, CDialog)
	//{{AFX_MSG_MAP(CCVDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCVDialog ���b�Z�[�W �n���h��

void CCVDialog::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
//	CDialog::OnOK();
//	if (!UpdateData(TRUE)) {
//		TRACE0("UpdateData failed during dialog termination.\n");
//		return;
//	}
//	DestroyWindow();

	if ( create_hvertex() == FALSE ) {
		AfxMessageBox("Can't exec Create CV.");
	}

	CEdit* cedit;
	cedit = (CEdit* )GetDlgItem( IDC_EDIT_CCV_SRC );
	cedit->SetWindowText("");
	cedit = (CEdit* )GetDlgItem( IDC_EDIT_CCV_DIST );
	cedit->SetWindowText("");

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	// redraw all
	swin->screenatr[SCREEN_SRC].wnd->RedrawWindow();
	swin->screenatr[SCREEN_DIST].wnd->RedrawWindow();

}

void CCVDialog::OnCancel() 
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
//	CDialog::OnCancel();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	DestroyWindow();
}

extern CCVDialog* ccvd;

void CCVDialog::PostNcDestroy() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
//	CDialog::PostNcDestroy();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	ccvd = NULL;

	delete this;
}
