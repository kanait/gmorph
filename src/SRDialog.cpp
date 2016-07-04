// SRDialog.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "OpenGL.h"
#include "SRDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"

/////////////////////////////////////////////////////////////////////////////
// CSRDialog �_�C�A���O


CSRDialog::CSRDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSRDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSRDialog)
	ScreenAtr *screen = &(swin->screenatr[SCREEN_SRC]);
	m_radius_cyl = screen->rad_cyl;
	m_radius_sph = screen->rad_sph;
	//}}AFX_DATA_INIT
}

CSRDialog::Create( void )
{
	return CDialog::Create( CSRDialog::IDD );
}

void CSRDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSRDialog)
	DDX_Text(pDX, IDC_RADIUS_CYL, m_radius_cyl);
	DDX_Text(pDX, IDC_RADIUS_SPH, m_radius_sph);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSRDialog, CDialog)
	//{{AFX_MSG_MAP(CSRDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSRDialog ���b�Z�[�W �n���h��

void CSRDialog::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
//	CDialog::OnOK();
	UpdateData(TRUE);

	ScreenAtr *screen;
	screen = &(swin->screenatr[SCREEN_SRC]);
 	screen->rad_sph = m_radius_sph;
	screen->rad_cyl = m_radius_cyl;
	screen->wnd->RedrawWindow();

	screen = &(swin->screenatr[SCREEN_DIST]);
 	screen->rad_sph = m_radius_sph;
	screen->rad_cyl = m_radius_cyl;
	screen->wnd->RedrawWindow();
}

void CSRDialog::OnCancel() 
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
//	CDialog::OnCancel();
	DestroyWindow();
}

void CSRDialog::PostNcDestroy() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
//	CDialog::PostNcDestroy();
	delete this;
}
