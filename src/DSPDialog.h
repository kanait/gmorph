//
// DSPDialog.h
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#if !defined(AFX_DSPDIALOG_H__295527D1_484A_11D2_AB66_00E029217E15__INCLUDED_)
#define AFX_DSPDIALOG_H__295527D1_484A_11D2_AB66_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDSPDialog �_�C�A���O

class CDSPDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CDSPDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	BOOL Create( void );

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDSPDialog)
	enum { IDD = IDD_DELETE_SPATH };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDSPDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDSPDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DSPDIALOG_H__295527D1_484A_11D2_AB66_00E029217E15__INCLUDED_)
