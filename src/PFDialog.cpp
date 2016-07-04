// PFDialog.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CPFDialog �_�C�A���O


CPFDialog::CPFDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPFDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPFDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
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
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPFDialog, CDialog)
	//{{AFX_MSG_MAP(CPFDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPFDialog ���b�Z�[�W �n���h��

void CPFDialog::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
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
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
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
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
//	CDialog::PostNcDestroy();

	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	cpfd = NULL;

	delete this;
}
