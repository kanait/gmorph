#if !defined(AFX_PLDIALOG_H__969674B3_45F4_11D2_AB65_00E029217E15__INCLUDED_)
#define AFX_PLDIALOG_H__969674B3_45F4_11D2_AB65_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PLDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CPLDialog ダイアログ

class CPLDialog : public CDialog
{
// コンストラクション
public:
	CPLDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
	~CPLDialog( void );
	BOOL Create();

// ダイアログ データ
	//{{AFX_DATA(CPLDialog)
	enum { IDD = IDD_CREATE_PPDLOOP };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CPLDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CPLDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PLDIALOG_H__969674B3_45F4_11D2_AB65_00E029217E15__INCLUDED_)
