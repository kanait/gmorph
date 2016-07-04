// OpenGLView.h : COpenGLView �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLVIEW_H__11D0ECDC_2844_11D2_AB51_00E029217E15__INCLUDED_)
#define AFX_OPENGLVIEW_H__11D0ECDC_2844_11D2_AB51_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class COpenGLView : public CView
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)

// �A�g���r���[�g
public:
	COpenGLDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(COpenGLView)
	public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷��ۂɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(COpenGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL SetupPixelFormat( void );

private:
	void SetError( int e );
	BOOL InitializeOpenGL();

	HGLRC m_hRC;
	CDC *m_pDC;

	static const char* const _ErrorStrings[];
	const char* m_ErrorString;
	
	int scrn_x, scrn_y; 
	BOOL moving, scaling;
};

#ifndef _DEBUG  // OpenGLView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline COpenGLDoc* COpenGLView::GetDocument()
   { return (COpenGLDoc*)m_pDocument; }
#endif

// CMyView

//class CMyView : public COpenGLView
//{
//private:
//
//	DECLARE_DYNCREATE(CMyView)
//
//protected:
//
//	virtual void RenderStockScene( void );
//	virtual BOOL RenderScene( void );
//	
//};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_OPENGLVIEW_H__11D0ECDC_2844_11D2_AB51_00E029217E15__INCLUDED_)
