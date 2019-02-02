//
// SFIDialog.h
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#if !defined(AFX_SFIDIALOG_H__31C98633_48A3_11D2_AB68_00E029217E15__INCLUDED_)
#define AFX_SFIDIALOG_H__31C98633_48A3_11D2_AB68_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CSFIDialog ダイアログ

class CSFIDialog : public CDialog
{
// コンストラクション
public:
	CSFIDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSFIDialog)
	enum { IDD = IDD_FAIR_COE };
	double	m_sfi_lmd;
	int		m_sfi_num;
	double	m_sfi_kpb;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CSFIDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSFIDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SFIDIALOG_H__31C98633_48A3_11D2_AB68_00E029217E15__INCLUDED_)
