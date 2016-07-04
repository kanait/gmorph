#if !defined(AFX_DISTVIEW_H__5FA3EEF0_31C4_11D2_AB57_00E029217E15__INCLUDED_)
#define AFX_DISTVIEW_H__5FA3EEF0_31C4_11D2_AB57_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DistView.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDistView ビュー

class CDistView : public CView
{
protected:
	CDistView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CDistView)

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CDistView)
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CDistView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CDistView)
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

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DISTVIEW_H__5FA3EEF0_31C4_11D2_AB57_00E029217E15__INCLUDED_)
