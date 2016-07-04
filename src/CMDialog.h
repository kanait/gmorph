#if !defined(AFX_CMDIALOG_H__969674B4_45F4_11D2_AB65_00E029217E15__INCLUDED_)
#define AFX_CMDIALOG_H__969674B4_45F4_11D2_AB65_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CMDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CCMDialog ダイアログ

class CCMDialog : public CDialog
{
// コンストラクション
public:
	CCMDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
	BOOL Create( void );

// ダイアログ データ
	//{{AFX_DATA(CCMDialog)
	enum { IDD = IDD_CREATE_CMESH };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CCMDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CCMDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CMDIALOG_H__969674B4_45F4_11D2_AB65_00E029217E15__INCLUDED_)
