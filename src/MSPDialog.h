#if !defined(AFX_MSPDIALOG_H__295527D2_484A_11D2_AB66_00E029217E15__INCLUDED_)
#define AFX_MSPDIALOG_H__295527D2_484A_11D2_AB66_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MSPDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CMSPDialog ダイアログ

class CMSPDialog : public CDialog
{
// コンストラクション
public:
	CMSPDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
	BOOL Create( void );

// ダイアログ データ
	//{{AFX_DATA(CMSPDialog)
	enum { IDD = IDD_CREATE_SPATH_MANU };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CMSPDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMSPDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MSPDIALOG_H__295527D2_484A_11D2_AB66_00E029217E15__INCLUDED_)
