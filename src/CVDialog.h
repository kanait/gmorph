//
// CVDialog.h
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#if !defined(AFX_CVDIALOG_H__969674B1_45F4_11D2_AB65_00E029217E15__INCLUDED_)
#define AFX_CVDIALOG_H__969674B1_45F4_11D2_AB65_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CCVDialog �_�C�A���O

class CCVDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CCVDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	~CCVDialog( void );
	BOOL Create();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CCVDialog)
	enum { IDD = IDD_CREATE_CV };
	int		m_ccv_src;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CCVDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CCVDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CVDIALOG_H__969674B1_45F4_11D2_AB65_00E029217E15__INCLUDED_)
