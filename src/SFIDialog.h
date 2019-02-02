//
// SFIDialog.h
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#if !defined(AFX_SFIDIALOG_H__31C98633_48A3_11D2_AB68_00E029217E15__INCLUDED_)
#define AFX_SFIDIALOG_H__31C98633_48A3_11D2_AB68_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CSFIDialog �_�C�A���O

class CSFIDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CSFIDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSFIDialog)
	enum { IDD = IDD_FAIR_COE };
	double	m_sfi_lmd;
	int		m_sfi_num;
	double	m_sfi_kpb;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CSFIDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSFIDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SFIDIALOG_H__31C98633_48A3_11D2_AB68_00E029217E15__INCLUDED_)
