// OpenGL.h : OPENGL �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//

#if !defined(AFX_OPENGL_H__11D0ECD4_2844_11D2_AB51_00E029217E15__INCLUDED_)
#define AFX_OPENGL_H__11D0ECD4_2844_11D2_AB51_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// COpenGLApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� OpenGL.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class COpenGLApp : public CWinApp
{
public:
	COpenGLApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(COpenGLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(COpenGLApp)
	afx_msg void OnAppAbout();
	afx_msg void OnAppExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_OPENGL_H__11D0ECD4_2844_11D2_AB51_00E029217E15__INCLUDED_)
