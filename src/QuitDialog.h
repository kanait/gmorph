#if !defined(AFX_QUITDIALOG_H__AC3B06D0_3282_11D2_AB58_00E029217E15__INCLUDED_)
#define AFX_QUITDIALOG_H__AC3B06D0_3282_11D2_AB58_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// QuitDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CQuitDialog ダイアログ

class CQuitDialog : public CDialog
{
// コンストラクション
public:
	CQuitDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CQuitDialog)
	enum { IDD = IDD_QUIT_DIALOG };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CQuitDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CQuitDialog)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_QUITDIALOG_H__AC3B06D0_3282_11D2_AB58_00E029217E15__INCLUDED_)
