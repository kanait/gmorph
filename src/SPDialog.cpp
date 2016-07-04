// SPDialog.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "OpenGL.h"
#include "SPDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "edit.h"
#include "sellist.h"

/////////////////////////////////////////////////////////////////////////////
// CSPDialog �_�C�A���O


CSPDialog::CSPDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSPDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSPDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}

CSPDialog::Create()
{
	return CDialog::Create( CSPDialog::IDD );
}

void CSPDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSPDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSPDialog, CDialog)
	//{{AFX_MSG_MAP(CSPDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSPDialog ���b�Z�[�W �n���h��

void CSPDialog::OnOK() 
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
		if ( sg_create_spath( screen ) == FALSE ) {
			AfxMessageBox("Can't create a shortest path.");
		}
		FreeSelectList( screen );
		screen->wnd->RedrawWindow();
	} 

	// dist
	screen = &(swin->screenatr[SCREEN_DIST]);
	if ( screen->sel_first != NULL ) {
		if ( sg_create_spath( screen ) == FALSE ) {
			AfxMessageBox("Can't create a shortest path.");
		}
		FreeSelectList( screen );
		screen->wnd->RedrawWindow();
	} 
	
	CWnd* wnd;
	CString string;
	
	wnd = GetDlgItem( IDC_CSP_SRC );
	if ( wnd == NULL ) return;
	string.Format("");
	wnd->SetWindowText( string );

	wnd = GetDlgItem( IDC_CSP_DIST );
	if ( wnd == NULL ) return;
	string.Format("");
	wnd->SetWindowText( string );

}

void CSPDialog::OnCancel() 
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
//	CDialog::OnCancel();
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	DestroyWindow();
}

extern CSPDialog* cspd;

void CSPDialog::PostNcDestroy() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
//	CDialog::PostNcDestroy();
	FreeSelectList( &(swin->screenatr[SCREEN_SRC]) );
	FreeSelectList( &(swin->screenatr[SCREEN_DIST]) );

	cspd = NULL;

	delete this;
}

