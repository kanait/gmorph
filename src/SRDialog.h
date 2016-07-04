#if !defined(AFX_SRDIALOG_H__A20A96A2_496A_11D2_AB68_00E029217E15__INCLUDED_)
#define AFX_SRDIALOG_H__A20A96A2_496A_11D2_AB68_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SRDialog.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSRDialog �_�C�A���O

class CSRDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CSRDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	BOOL Create( void );

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSRDialog)
	enum { IDD = IDD_SET_RADIUS };
	double	m_radius_cyl;
	double	m_radius_sph;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CSRDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSRDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SRDIALOG_H__A20A96A2_496A_11D2_AB68_00E029217E15__INCLUDED_)
