// MainFrm.h : CMainFrame クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__11D0ECD8_2844_11D2_AB51_00E029217E15__INCLUDED_)
#define AFX_MAINFRM_H__11D0ECD8_2844_11D2_AB51_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Instead of using a class here we could have just put these controls
// directly into CMainFrame.  As it is they are sending messages to the
// main frame just like they were part of it instead of part of a control
// bar.
class CStyleBar : public CToolBar
{
public:
	CComboBox   m_comboBox;
	CFont       m_font;
};

//class CMySplitterWnd : public CSplitterWnd {
//
//private:
//
//	DECLARE_DYNCREATE(CSplitterWnd)
//
//protected:
//
//	virtual void OnLButtonDown(UINT nFlags, CPoint point);
//
//};

	
class CMainFrame : public CFrameWnd
{
protected: // シリアライズ機能のみから作成します。
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// アトリビュート
public:

//	CMySplitterWnd m_wndSplitter;
	CSplitterWnd m_wndSplitter;

// オペレーション
public:
	void drawwindow( void );

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	BOOL CreateStyleBar();

protected:  // コントロール バー用メンバ
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
// temp
//	CToolBar    m_wndEditBar;
	CStyleBar   m_wndStyleBar;

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateMenuScreenCoaxis(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuScreenCv(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuScreenGroup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuScreenHmap(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuScreenLoop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuScreenPcm(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuScreenShading(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuScreenSpath(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuScreenWireframe(CCmdUI* pCmdUI);
	afx_msg void OnMenuScreenShading();
	afx_msg void OnMenuScreenWireframe();
	afx_msg void OnMenuScreenCoaxis();
	afx_msg void OnMenuScreenVert();
	afx_msg void OnUpdateMenuScreenVert(CCmdUI* pCmdUI);
	afx_msg void OnFileOpenDist();
	afx_msg void OnFileOpenGmh();
	afx_msg void OnFileSaveGmh();
	afx_msg void OnFileSaveSrc();
	afx_msg void OnFileSaveDist();
	afx_msg void OnMorphCreateGppd();
	afx_msg void OnMorphDeleteGppd();
	afx_msg void OnMorphReset();
	afx_msg void OnMorphSetDiv();
	afx_msg void OnMorphSpathClear();
	afx_msg void OnMorphSpathCreate();
	afx_msg void OnMorphStart();
	afx_msg void OnMenuScreenCv();
	afx_msg void OnMenuScreenGroup();
	afx_msg void OnMenuScreenHmap();
	afx_msg void OnMenuScreenLoop();
	afx_msg void OnMenuScreenPcm();
	afx_msg void OnMenuScreenSpath();
	afx_msg void OnUpdateMenuScreenEnhanced(CCmdUI* pCmdUI);
	afx_msg void OnMenuScreenEnhanced();
	afx_msg void OnMenuScreenSmooth();
	afx_msg void OnUpdateMenuScreenSmooth(CCmdUI* pCmdUI);
	afx_msg void OnMenuScreenInterp();
	afx_msg void OnUpdateMenuScreenInterp(CCmdUI* pCmdUI);
	afx_msg void OnFileSavePov();
	afx_msg void OnFileRecordPov();
	afx_msg void OnFileRecordBmp();
	afx_msg void OnFileRecordPpd();
	afx_msg void OnMenuGenerInterp();
	afx_msg void OnMenuFairSp();
	afx_msg void OnFileOpenGppd();
	afx_msg void OnFileSaveGppd();
	afx_msg void OnMenuScreenRadius();
	afx_msg void OnMenuSetConst();
	//}}AFX_MSG

	afx_msg void OnUpdateStyle(CCmdUI* pCmdUI);
	afx_msg void OnChangeStyle(UINT nID);
//	afx_msg void OnChangeStyleCombo(UINT nID);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MAINFRM_H__11D0ECD8_2844_11D2_AB51_00E029217E15__INCLUDED_)
