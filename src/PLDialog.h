#if !defined(AFX_PLDIALOG_H__969674B3_45F4_11D2_AB65_00E029217E15__INCLUDED_)
#define AFX_PLDIALOG_H__969674B3_45F4_11D2_AB65_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PLDialog.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CPLDialog �_�C�A���O

class CPLDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CPLDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	~CPLDialog( void );
	BOOL Create();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CPLDialog)
	enum { IDD = IDD_CREATE_PPDLOOP };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CPLDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CPLDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PLDIALOG_H__969674B3_45F4_11D2_AB65_00E029217E15__INCLUDED_)
