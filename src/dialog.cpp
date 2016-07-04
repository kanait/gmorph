* Copyright (c) 1998 Takashi Kanai; All rights reserved. */

#include "stdafx.h"
#include "OpenGL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"

// Dialog input 
#include "PLDialog.h"
#include "DPLDialog.h"
#include "PFDialog.h"
#include "DPFDialog.h"
#include "CVDialog.h"
#include "CMDialog.h"
#include "DCMDialog.h"
#include "SPDialog.h"
#include "DSPDialog.h"
#include "MSPDialog.h"

extern CPLDialog* cpld;
extern CDPLDialog* dpld;
extern CPFDialog* cpfd;
extern CDPFDialog* dpfd;
extern CCVDialog* ccvd;
extern CCMDialog* ccmd;
extern CDCMDialog* dcmd;
extern CSPDialog* cspd;
extern CDSPDialog* dspd;
extern CMSPDialog* mspd;

void SelectToDialog( int edit_type, ScreenAtr *screen )
{
	CWnd* wnd;
	CListBox* clist;
	CString string;

	switch ( edit_type ) {

	case EDIT_CREATE_PPDLOOP:

		// vertex no.
		if ( cpld == NULL ) return;

		wnd = cpld->GetDlgItem( IDC_CPL_VT );
		if ( wnd == NULL ) return;
		string.Format("%d", screen->sel_first->vt->no );
		wnd->SetWindowText( string );

		// screen no.
		wnd = cpld->GetDlgItem( IDC_CPL_SC );
		if ( wnd == NULL ) return;
		string.Format("%d", screen->no );
		wnd->SetWindowText( string );

		return;

	case EDIT_DELETE_PPDLOOP:

		if ( dpld == NULL ) return;

		// loop no.
		wnd = dpld->GetDlgItem( IDC_DPL_PL );
		if ( wnd == NULL ) return;
		string.Format("%d", screen->sel_first->lp->no );
		wnd->SetWindowText( string );

		return;

	case EDIT_CREATE_PPDFACE:

		if ( cpfd == NULL ) return;

		clist = (CListBox* )cpfd->GetDlgItem( IDC_CPF_PV_LIST );
		ASSERT( clist );
		if (  clist == NULL ) return;
		
		string.Format("Vert(%d) - No.%d", 
			screen->n_sellist, 	screen->sel_last->vt->no );
		clist->AddString( string );
		return;

	case EDIT_DELETE_PPDFACE:

		if ( dpfd == NULL ) return;

		wnd = dpfd->GetDlgItem( IDC_DPF_PF );
		ASSERT( wnd ); if ( wnd == NULL ) return;

		string.Format("%d", screen->sel_first->fc->no );
		wnd->SetWindowText( string );
		return;

	case EDIT_CREATE_CV:

		if ( ccvd == NULL ) return;

		int id;
		if ( screen->no == SCREEN_SRC ) id = IDC_EDIT_CCV_SRC;
		else id = IDC_EDIT_CCV_DIST;

		wnd = ccvd->GetDlgItem( id );
		if ( wnd == NULL ) return;
		string.Format("%d", screen->sel_first->vt->no );
		wnd->SetWindowText( string );
		return;

	case EDIT_CREATE_CMESH:

		clist = (CListBox* )ccmd->GetDlgItem( IDC_CCM_CV_LIST );
		ASSERT( clist );
		if (  clist == NULL ) return;
		
		string.Format("CV(%d) - No.%d", 
			screen->n_sellist, 	screen->sel_last->hvt->no );
		clist->AddString( string );
		return;

	case EDIT_DELETE_CMESH:

		if ( dcmd == NULL ) return;

		wnd = dcmd->GetDlgItem( IDC_DCM_CM );
		ASSERT( wnd );
		if ( wnd == NULL ) return;
		string.Format("%d", screen->sel_first->hfc->no );
		wnd->SetWindowText( string );
		return;

	case EDIT_CREATE_SPATH:

		if ( cspd == NULL ) return;

		if ( screen->n_sellist == 1 ) {
			wnd = cspd->GetDlgItem( IDC_CSP_SRC );
			ASSERT( wnd );
			if ( wnd == NULL ) return;
			string.Format("%d", screen->sel_first->vt->no );
			wnd->SetWindowText( string );
		} else if ( screen->n_sellist == 2 ) {
			wnd = cspd->GetDlgItem( IDC_CSP_DIST );
			ASSERT( wnd );
			if ( wnd == NULL ) return;
			string.Format("%d", screen->sel_first->nxt->vt->no );
			wnd->SetWindowText( string );
		}
		return;

	case EDIT_DELETE_SPATH:

		if ( dspd == NULL ) return;

		wnd = dspd->GetDlgItem( IDC_DSP_SP );
		ASSERT( wnd );
		if ( wnd == NULL ) return;
		string.Format("%d", screen->sel_first->lp->hed->no );
		wnd->SetWindowText( string );

		wnd = dspd->GetDlgItem( IDC_DSP_SC );
		ASSERT( wnd );
		if ( wnd == NULL ) return;
		string.Format("%d", screen->no+1 );
		wnd->SetWindowText( string );

		return;

	case EDIT_CREATE_SPATH_MANU:

		if ( mspd == NULL ) return;
		clist = (CListBox* )mspd->GetDlgItem( IDC_MSP_PV );
		ASSERT( clist );
		if (  clist == NULL ) return;
		
		string.Format("Vertex(%d) - No.%d", 
			screen->n_sellist,screen->sel_last->vt->no );
		clist->AddString( string );

		return;
	}
}