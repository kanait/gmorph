// OpenGLView.h : COpenGLView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLVIEW_H__11D0ECDC_2844_11D2_AB51_00E029217E15__INCLUDED_)
#define AFX_OPENGLVIEW_H__11D0ECDC_2844_11D2_AB51_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class COpenGLView : public CView
{
protected: // シリアライズ機能のみから作成します。
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)

// アトリビュート
public:
	COpenGLDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(COpenGLView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
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

#ifndef _DEBUG  // OpenGLView.cpp ファイルがデバッグ環境の時使用されます。
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
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_OPENGLVIEW_H__11D0ECDC_2844_11D2_AB51_00E029217E15__INCLUDED_)
