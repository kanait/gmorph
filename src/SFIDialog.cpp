//
// SFIDialog.cpp
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"
#include "OpenGL.h"
#include "SFIDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSFIDialog �_�C�A���O


CSFIDialog::CSFIDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSFIDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSFIDialog)
	m_sfi_lmd = 0.7;
	m_sfi_num = 50;
	m_sfi_kpb = 0.1;
	//}}AFX_DATA_INIT
}


void CSFIDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSFIDialog)
	DDX_Text(pDX, IDC_SFI_LMD, m_sfi_lmd);
	DDX_Text(pDX, IDC_SFI_NUM, m_sfi_num);
	DDX_Text(pDX, IDC_SFI_KPB, m_sfi_kpb);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSFIDialog, CDialog)
	//{{AFX_MSG_MAP(CSFIDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSFIDialog ���b�Z�[�W �n���h��

void CSFIDialog::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
//	UpdateData(TRUE);

	CDialog::OnOK();
}

void CSFIDialog::OnCancel() 
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
	CDialog::OnCancel();
}
