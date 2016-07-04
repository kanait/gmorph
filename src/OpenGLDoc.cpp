// OpenGLDoc.cpp : COpenGLDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "OpenGL.h"

#include "OpenGLDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGLDoc

IMPLEMENT_DYNCREATE(COpenGLDoc, CDocument)

BEGIN_MESSAGE_MAP(COpenGLDoc, CDocument)
	//{{AFX_MSG_MAP(COpenGLDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLDoc クラスの構築/消滅

COpenGLDoc::COpenGLDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

COpenGLDoc::~COpenGLDoc()
{
}

BOOL COpenGLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

// タイトルをつける場所
// ここよりも　**App::InitInstance の方が良い．
//	CString strTitle = _T("Gmorph Ver2.1a1 (Win32 Version)");
//	SetTitle(strTitle);// ←CDocumentクラスのメンバ関数	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COpenGLDoc シリアライゼーション

void COpenGLDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLDoc クラスの診断

#ifdef _DEBUG
void COpenGLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpenGLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenGLDoc コマンド
