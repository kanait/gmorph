//
// DPFDialog.h
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#if !defined(AFX_DPFDIALOG_H__53ADA712_47A9_11D2_AB66_00E029217E15__INCLUDED_)
#define AFX_DPFDIALOG_H__53ADA712_47A9_11D2_AB66_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDPFDialog �_�C�A���O

class CDPFDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CDPFDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	BOOL Create( void );

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDPFDialog)
	enum { IDD = IDD_DELETE_PPDFACE };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDPFDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDPFDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DPFDIALOG_H__53ADA712_47A9_11D2_AB66_00E029217E15__INCLUDED_)
