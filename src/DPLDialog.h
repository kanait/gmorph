#if !defined(AFX_DPLDIALOG_H__9989C772_478E_11D2_AB66_00E029217E15__INCLUDED_)
#define AFX_DPLDIALOG_H__9989C772_478E_11D2_AB66_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DPLDialog.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDPLDialog �_�C�A���O

class CDPLDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CDPLDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	BOOL Create( void );
// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDPLDialog)
	enum { IDD = IDD_DELETE_PPDLOOP };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDPLDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDPLDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DPLDIALOG_H__9989C772_478E_11D2_AB66_00E029217E15__INCLUDED_)
