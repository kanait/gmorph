#if !defined(AFX_CMDIALOG_H__969674B4_45F4_11D2_AB65_00E029217E15__INCLUDED_)
#define AFX_CMDIALOG_H__969674B4_45F4_11D2_AB65_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CMDialog.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CCMDialog �_�C�A���O

class CCMDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CCMDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	BOOL Create( void );

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CCMDialog)
	enum { IDD = IDD_CREATE_CMESH };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CCMDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CCMDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CMDIALOG_H__969674B4_45F4_11D2_AB65_00E029217E15__INCLUDED_)
