#if !defined(AFX_SIPDIALOG_H__31C98630_48A3_11D2_AB68_00E029217E15__INCLUDED_)
#define AFX_SIPDIALOG_H__31C98630_48A3_11D2_AB68_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SIPDialog.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSIPDialog �_�C�A���O

class CSIPDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CSIPDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	BOOL Create( void );

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSIPDialog)
	enum { IDD = IDD_INTERP_PARAMS };
	double	m_prm_val;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CSIPDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSIPDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SIPDIALOG_H__31C98630_48A3_11D2_AB68_00E029217E15__INCLUDED_)
