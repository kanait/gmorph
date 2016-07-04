#if !defined(AFX_SRDIALOG_H__A20A96A2_496A_11D2_AB68_00E029217E15__INCLUDED_)
#define AFX_SRDIALOG_H__A20A96A2_496A_11D2_AB68_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SRDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSRDialog ダイアログ

class CSRDialog : public CDialog
{
// コンストラクション
public:
	CSRDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
	BOOL Create( void );

// ダイアログ データ
	//{{AFX_DATA(CSRDialog)
	enum { IDD = IDD_SET_RADIUS };
	double	m_radius_cyl;
	double	m_radius_sph;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CSRDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSRDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SRDIALOG_H__A20A96A2_496A_11D2_AB68_00E029217E15__INCLUDED_)
