// DPFDialog.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "OpenGL.h"
#include "DPFDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "edit.h"
#include "sellist.h"

/////////////////////////////////////////////////////////////////////////////
// CDPFDialog �_�C�A���O


CDPFDialog::CDPFDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDPFDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDPFDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}

CDPFDialog::Create()
{
	return CDialog::Create( CDPFDialog::IDD );
}

void CDPFDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDPFDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDPFDialog, CDialog)
	//{{AFX_MSG_MAP(CDPFDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDPFDialog ���b�Z�[�W �n���h��

void CDPFDialog::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
//	CDialog::OnOK();

	ScreenAtr *screen;
	CEdit* cedit;

	// src
	screen = &(swin->screenatr[SCREEN_SRC]);
	if ( screen->sel_first != NULL ) {
		delete_face( screen );
		FreeSelectList( screen );

		cedit = (CEdit* )GetDlgItem( IDC_DPF_PF );
		cedit->SetWindowText("");

		screen->wnd->RedrawWindow();

		return;
	} 

	// dist
	screen = &(swin->screenatr[SCREEN_DIST]);
	if ( screen->sel_first != NULL ) {
		delete_face( screen );
		FreeSelectList( screen );

		cedit = (CEdit* )GetDlgItem( IDC_DPF_PF );
		cedit->SetWindowText("");

		screen->wnd->RedrawWindow();

		return;
	} 
}

void CDPFDialog::OnCancel() 
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
//	CDialog::OnCancel();
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	DestroyWindow();
}

extern CDPFDialog* dpfd;

void CDPFDialog::PostNcDestroy() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
//	CDialog::PostNcDestroy();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	dpfd = NULL;

	delete this;
}
