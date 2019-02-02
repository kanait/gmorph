//
// CVDialog.h
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#if !defined(AFX_CVDIALOG_H__969674B1_45F4_11D2_AB65_00E029217E15__INCLUDED_)
#define AFX_CVDIALOG_H__969674B1_45F4_11D2_AB65_00E029217E15__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CCVDialog ダイアログ

class CCVDialog : public CDialog
{
// コンストラクション
public:
	CCVDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
	~CCVDialog( void );
	BOOL Create();

// ダイアログ データ
	//{{AFX_DATA(CCVDialog)
	enum { IDD = IDD_CREATE_CV };
	int		m_ccv_src;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CCVDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CCVDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CVDIALOG_H__969674B1_45F4_11D2_AB65_00E029217E15__INCLUDED_)
