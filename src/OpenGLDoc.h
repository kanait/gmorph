// OpenGLDoc.h : COpenGLDoc �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLDOC_H__11D0ECDA_2844_11D2_AB51_00E029217E15__INCLUDED_)
#define AFX_OPENGLDOC_H__11D0ECDA_2844_11D2_AB51_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class COpenGLDoc : public CDocument
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	COpenGLDoc();
	DECLARE_DYNCREATE(COpenGLDoc)

// �A�g���r���[�g
public:
	CRectTracker m_tracker;
	BOOL m_bAllowInvert;

// �I�y���[�V����
public:

//�I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(COpenGLDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~COpenGLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(COpenGLDoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_OPENGLDOC_H__11D0ECDA_2844_11D2_AB51_00E029217E15__INCLUDED_)
