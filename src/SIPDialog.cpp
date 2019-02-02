//
// SIPDialog.cpp
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"
#include "OpenGL.h"
#include "SIPDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "gmorph.h"

/////////////////////////////////////////////////////////////////////////////
// CSIPDialog �_�C�A���O


CSIPDialog::CSIPDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSIPDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSIPDialog)
	m_prm_val = 0.5;
	//}}AFX_DATA_INIT
}

CSIPDialog::Create( void )
{
	return CDialog::Create( CSIPDialog::IDD );
}

void CSIPDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSIPDialog)
	DDX_Text(pDX, IDC_SIP_PRM, m_prm_val);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSIPDialog, CDialog)
	//{{AFX_MSG_MAP(CSIPDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSIPDialog ���b�Z�[�W �n���h��

void CSIPDialog::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
// CDialog::OnOK();

	UpdateData( TRUE );

	setinterpppd( swin->morph_ppd, m_prm_val );

	swin->screenatr[SCREEN_SRC].wnd->RedrawWindow();

}

void CSIPDialog::OnCancel()
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
//	CDialog::OnCancel();

	DestroyWindow();
}

void CSIPDialog::PostNcDestroy() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
//	CDialog::PostNcDestroy();

	delete this;
}
