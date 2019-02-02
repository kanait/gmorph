//
// edit.cpp
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include <math.h>
#include "smd.h"
#include "ppdvertex.h"
#include "ppdedge.h"
#include "ppdface.h"
#include "ppdloop.h"
#include "hppd.h"
#include "edit.h"
#include "sgraph.h"

// Create Boundary Loop
static Sped *find_boundaryedge( Spvt *v )
{
	Vted *ve;
	
	if ( v == (Spvt *) NULL ) return NULL;
	
	for ( ve = v->svted; ve != (Vted *) NULL; ve = ve->nxt ) {
		if ( ve->ed->atr == EDGEBOUNDARY ) return ve->ed;
	}
	
	return NULL;
}

static Sped *find_nextedge( Spvt *vt, Sped *ed, Splp *lp )
{
	Vted *ve;
	Spvt *nvt;
	
	if ( vt == (Spvt *) NULL ) return (Sped *) NULL;
	
	for ( ve = vt->svted; ve != (Vted *) NULL; ve = ve->nxt ) {
		
		if ( (ve->ed != ed) && (ve->ed->atr == EDGEBOUNDARY) ) {
			
			nvt = another_vt( ve->ed, vt );
			
			/* first vertex */
			if ( (lp->splv != (Splv *) NULL) && (lp->lvn != 1) ) {
				if ( nvt == lp->splv->vt ) return ve->ed;
			}
			
			if ( find_ppdloopvertex( lp, nvt ) == (Splv *) NULL ) {
				return ve->ed;
			}
			
		}
		
	}
	return (Sped *) NULL;
}

static Splp *ppdfindloop( Sppd *ppd, Spvt *v )
{
	Splp *loop;
	Splv *lv;
	Sped *e0, *e1, *ed;
	Spvt *v0, *v1, *nv;
	
	if ( v == (Spvt *) NULL ) return (Splp *) NULL;
	
	if ( (e0 = find_boundaryedge( v )) == (Sped *) NULL ) return (Splp *) NULL;
	
	/* initialize loop */
	v0 = v1 = v;
	loop = create_ppdloop( ppd );
	lv = create_ppdloopvertex( loop );
	lv->vt = v0;
	
	while ( 1 ) {
		
		if ( (e1 = find_nextedge( v0, e0, loop )) == (Sped *) NULL ) {
			AfxMessageBox("Create Boundary Loop: can't find a loop.");
			free_ppdloop( loop, ppd );
			return (Splp *) NULL;
		}

		nv = another_vt( e1, v0 );
		if ( nv == v1 ) {
			CString string;
			string.Format("loop created. sum of vertices: %d", loop->lvn );
			AfxMessageBox( string );
			loop->type = CLOSEDLOOP;
			
			for ( lv = loop->splv; lv->nxt != (Splv *) NULL; lv = lv->nxt ) {
				if ( (ed = find_ppdedge( lv->vt, lv->nxt->vt )) != NULL ) {
					ed->used_loop = SMD_ON;
				}
			}
			if ( (ed = find_ppdedge( loop->splv->vt, loop->eplv->vt )) != NULL ) {
				ed->used_loop = SMD_ON;
			}
			
			return (Splp *) loop;
		}
		
		lv = create_ppdloopvertex( loop );
		lv->vt = nv;
		
		if (loop->lvn > ppd->vn ) {
			AfxMessageBox("Create Loop: can't find closed loop.");
			free_ppdloop( loop, ppd );
			return (Splp *) NULL;
		}
		
		/* next step */
		e0 = e1;
		v0 = nv;
		
	}
	
}

BOOL create_boundaryloop( ScreenAtr *screen )
{
	if ( screen->current_ppd == (Sppd *) NULL ) return FALSE;
	if ( screen->n_sellist != 1 ) {
		return FALSE;
	}
	
	Sppd *ppd  = screen->current_ppd;
	Spvt *vt   = screen->sel_first->vt;
	
	if ( ppdfindloop( ppd, vt ) == NULL ) {
		return FALSE;
	}
	
	return TRUE;
}

/////////////////////////////////////////////
// "Create PPDFace" functions 
/////////////////////////////////////////////

static BOOL CreatePPDFaceCheck( ScreenAtr *screen, Sppd *ppd )
{
  Spvt *sv, *ev;
  Sped *ed;
  CString string;
  Sped *find_ppdedge( Spvt *, Spvt * );
  Spfc *find_ppdface_ppdedge( Sped *, Spvt *, Spvt * );
  
  /* faces must be triangle */
  if ( screen->n_sellist != TRIANGLE ) {
    AfxMessageBox("The number of selected vertices are not three.");
    return FALSE;
  }

  /* boundary edge check */
  for ( SelList *sl = screen->sel_first; sl != (SelList *) NULL; sl = sl->nxt ) {
    
    sv = sl->vt;
    ev = ( sl->nxt != NULL ) ? sl->nxt->vt : screen->sel_first->vt;
    
    if ( (ed = find_ppdedge( sv, ev )) != (Sped *) NULL ) {
      if ( ed->fn == 2 ) {
		  string.Format("Edge No.%d has two faces any longer.", ed->no);
		  AfxMessageBox( string );
		  return FALSE;
      }
      if ( find_ppdface_ppdedge( ed, sv, ev ) != (Spfc *) NULL ) {
		  string.Format("Edge No.%d has a face in the same side of an edge any longer.", ed->no);
		  AfxMessageBox( string );
		  return FALSE;
      }
    }
    
  }
  
  return TRUE;
  
}

static void CreateFace( ScreenAtr *screen, Sppd *ppd )
{
  Spfc *fc;
  Spvt *sv, *ev;
  Sphe *he;
  Vted *ve;
  Sped *ed;
  
  fc = create_ppdface( ppd );

  for ( SelList *sl = screen->sel_first; sl != (SelList *) NULL; sl = sl->nxt ) {
    
    sv = sl->vt;

    he = create_ppdhalfedge( fc );
    he->vt = sv;
    
    ev = ( sl->nxt != NULL ) ? sl->nxt->vt : screen->sel_first->vt;
    
    if ( (ed = find_ppdedge( sv, ev )) == (Sped *) NULL ) {
      
      ed = create_ppdedge( ppd );
      /* edge - vertex */
      ed->sv = sv;
      ed->ev = ev;
      /* vertex - edge */
      ve = create_vtxed( sv, ed );
      ve = create_vtxed( ev, ed );
      /* edge - face */
      ed->lf =  fc;
      
    } else {
      
      /* edge - face */
      if ( (ed->sv == sv) && (ed->ev == ev ) ) {
		  ed->lf  = fc;
      } else {
		  ed->rf  = fc;
      }
      
    }
    
    he->ed  = ed;
    ++(ed->fn);
  }

  calc_fnorm( fc );
  
}

BOOL create_face( ScreenAtr *screen )
{
  Sppd *ppd = screen->current_ppd;

  if ( ppd == NULL ) return FALSE;

  if ( CreatePPDFaceCheck( screen, ppd ) != SMD_ON ) {
    return FALSE;
  }

  CreateFace( screen, ppd );

  return TRUE;
}

/////////////////////////////////////////////
// Delete PPD Face functions
/////////////////////////////////////////////

static void DeleteFace( Spfc *fc, Sppd *ppd )
{
  Sped *ed;
  Sphe *he;
  
  if (fc == (Spfc *) NULL) return;

  he = fc->sphe;
  while ( he != (Sphe *) NULL ) {
    ed = he->ed;
    he = free_ppdhalfedge( he, fc );
    /* important. */
    if ( !(ed->fn) ) {
      free_ppdedge( ed, ppd );
    }
  }

  if ( ppd->spfc == fc ) {
    if ((ppd->spfc = fc->nxt) != (Spfc *) NULL)
      fc->nxt->prv = (Spfc *) NULL;
    else {
      ppd->epfc = (Spfc *) NULL;
    }
  } else if (ppd->epfc == fc) {
    fc->prv->nxt = (Spfc *) NULL;
    ppd->epfc = fc->prv;
    
  } else {
    fc->prv->nxt = fc->nxt;
    fc->nxt->prv = fc->prv;
  }

  free(fc);
  --( ppd->fn );
  
}

BOOL delete_face( ScreenAtr *screen )
{
  Sppd *ppd = screen->current_ppd;
  for ( SelList* sl = screen->sel_first; sl != (SelList *) NULL; sl = sl->nxt ) {
    DeleteFace( sl->fc, ppd );
    sl->fc = (Spfc *) NULL;
  }
  return TRUE;
}

/////////////////////////////////////////////
// "Create CV" functions 
/////////////////////////////////////////////

BOOL create_hvertex( void )
{
  HPpd    *hppd;
  Spvt    *vt1, *vt2;
  HVertex *hvt;
  
  ScreenAtr *screen1 = &(swin->screenatr[SCREEN_SRC]);
  ScreenAtr *screen2 = &(swin->screenatr[SCREEN_DIST]);

  if ( !(screen1->n_sellist) || !(screen2->n_sellist) ) return FALSE;

  vt1 = screen1->sel_first->vt;
  vt2 = screen2->sel_first->vt;

  if ( (vt1->sp_type != SP_VERTEX_NORMAL) ||
       (vt2->sp_type != SP_VERTEX_NORMAL) ) {
    return FALSE;
  }

  /* create hppd */
  if ( swin->hppd == (HPpd *) NULL ) {
    hppd = swin->hppd = create_hppd();
    
    hppd->ppd1 = screen1->current_ppd;
    hppd->ppd2 = screen2->current_ppd;
    
  } else {
    hppd = swin->hppd;
  }
    
  /* create hvertex */
  hvt = create_hppdvertex( hppd );
  hvt->vt1 = vt1;
  hvt->vt2 = vt2;
  /* change vt->sp_type */
  hvt->vt1->sp_type = SP_VERTEX_HVERTEX;
  hvt->vt2->sp_type = SP_VERTEX_HVERTEX;
  vt1->hvt = hvt;
  vt2->hvt = hvt;

  return TRUE;  
//  FreeSelectList( screen1 );
//  FreeSelectList( screen2 );
}

/////////////////////////////////////////////
// "Delete HVertex" functions 
/////////////////////////////////////////////

static BOOL delete_hvertex_screen( ScreenAtr *screen )
{
  HVertex *hvt;

  for ( SelList *sl = screen->sel_first; sl != (SelList *) NULL; sl = sl->nxt ) {
    
    if ( (hvt = sl->hvt) != (HVertex *) NULL ) {
      
      hvt->vt1->sp_type = SP_VERTEX_NORMAL;
      hvt->vt2->sp_type = SP_VERTEX_NORMAL;
      hvt->vt1->hvt = (HVertex *) NULL;
      hvt->vt2->hvt = (HVertex *) NULL;

      free_hppdvertex( hvt, swin->hppd );
    }
  }
  return TRUE;
}

BOOL delete_hvertex( void )
{
  ScreenAtr *screen1 = &(swin->screenatr[SCREEN_SRC]);
  if ( delete_hvertex_screen( screen1 ) == TRUE ) {
	  return TRUE;
  }

  ScreenAtr *screen2 = &(swin->screenatr[SCREEN_DIST]);
  if ( delete_hvertex_screen( screen2 ) == FALSE ) {
	  return FALSE;
  }

  return TRUE;
}

/////////////////////////////////////////////
// "Create CMesh" functions 
/////////////////////////////////////////////

static BOOL CheckHppdFace( ScreenAtr *screen, HPpd *hppd )
{
  SelList   *sl;
  HVertex *shvt, *ehvt;
  HEdge   *hed;
  
  if ( hppd == (HPpd *) NULL ) return FALSE;
  if ( screen == (ScreenAtr *) NULL ) return FALSE;
  
  shvt = screen->sel_last->hvt;
  for ( sl = screen->sel_first; sl != (SelList *) NULL; sl = sl->nxt ) {
    
    ehvt = sl->hvt;
    if ( (hed = find_hppdedge( shvt, ehvt, hppd )) != (HEdge *) NULL ) {

      if ( (hed->rf != (HFace *) NULL) && (hed->lf != (HFace *) NULL) )
	return FALSE;
    }
    shvt = ehvt;
  }

  return TRUE;
}

BOOL create_hface( void )
{
  ScreenAtr *screen, *screen1, *screen2;
  HPpd      *hppd;
  HVertex   *shvt, *ehvt;
  HFace     *hfc;
  HEdge     *hed;
  HHalfedge *hhe;
  SelList   *sl;
  
  screen1 = &(swin->screenatr[SCREEN_SRC]);
  screen2 = &(swin->screenatr[SCREEN_DIST]);

  if ( (hppd = swin->hppd) == (HPpd *) NULL ) {
    return FALSE;
  }
    
  if ( !(screen1->n_sellist) && !(screen2->n_sellist) ) {
    return FALSE;
  }

  if ( screen1->n_sellist ) {
    screen = screen1;
  } else {
    screen = screen2;
  }

  /* only a triangle is generated */
  if ( screen->n_sellist < TRIANGLE ) {
    return FALSE;
  }

  /* one of edges has more than 3 faces */
  if ( CheckHppdFace( screen, hppd ) == FALSE ) {
    return FALSE;
  }
    
  hfc = create_hppdface( hppd );

  shvt = screen->sel_last->hvt;
  for ( sl = screen->sel_first; sl != (SelList *) NULL; sl = sl->nxt ) {

    hhe = create_hppdhalfedge( hfc );
    ehvt = hhe->vt = sl->hvt;

    /* create harmonic edge */
    if ( (hed = find_hppdedge( shvt, ehvt, hppd )) == (HEdge *) NULL ) {
      
      hed = create_hppdedge( hppd );
      hed->sv = shvt;
      hed->ev = ehvt;

      /* make ppd open loop and link PPDLoop to HEdge */
/*       hed->lp1 = ShortestPath_Dijkstra( screen1->current_ppd, shvt->vt1, ehvt->vt1 ); */
/*       hed->lp1->hed = hed; */
      
/*       hed->lp2 = ShortestPath_Dijkstra( screen2->current_ppd, shvt->vt2, ehvt->vt2 ); */
/*       hed->lp2->hed = hed; */

    } 
    /* link HHalfedge to HEdge */
    hhe->hed = hed;
    
    /* link HEdge to HFace */
    if ( hed->rf == (HFace *) NULL ) hed->rf = hfc;
    else hed->lf = hfc;

    /* next vertex */
    shvt = ehvt;
  }

  calc_hppdfnorm( hfc  );

  return TRUE;
}

/////////////////////////////////////////////
// "Delete HFace" functions 
/////////////////////////////////////////////

static void delete_hedge_face_link( HEdge *hed, HFace *hfc )
{
  if ( hed->rf == hfc ) {
    hed->rf = (HFace *) NULL;
    return;
  } else {
    hed->lf = (HFace *) NULL;
    return;
  }
}

static BOOL delete_hface_screen( ScreenAtr *screen )
{
  HPpd *hppd;
  SelList *sl;
  HFace *hfc;
  HHalfedge *he;

  hppd = swin->hppd;
  
  for ( sl = screen->sel_first; sl != (SelList *) NULL; sl = sl->nxt ) {

    if ( (hfc = sl->hfc) != (HFace *) NULL ) {

      /* delete edges */
      he = hfc->shhe;
      do {

		  if ( another_hface( he->hed, hfc ) == (HFace *) NULL ) {
			  free_hppdedge( he->hed, hppd );
		  } else {
			  delete_hedge_face_link( he->hed, hfc );
		  }
	
      } while ( (he = he->nxt) != hfc->shhe );
      
      free_hppdface( hfc, hppd );

      sl->hfc = (HFace *) NULL;
    }
  }

  return TRUE;
}

BOOL delete_hface( void )
{
  ScreenAtr *screen1 = &(swin->screenatr[SCREEN_SRC]);
  if ( delete_hface_screen( screen1 ) == TRUE ) {
	  return TRUE;
  }

  ScreenAtr *screen2 = &(swin->screenatr[SCREEN_DIST]);
  if ( delete_hface_screen( screen2 ) == FALSE ) {
	  return FALSE;
  } 

  return TRUE;
}

/////////////////////////////////////////////
// "Create Spath" functions 
/////////////////////////////////////////////

/* Shortest-Path between two Vertices Widget */
#define TWO_VERTICES 2
#define SUB_RATIO 0.5
//double sub_ratio = 0.5;

//extern void drawwindow( void );

BOOL sg_create_spath( ScreenAtr *screen )
{
  int  i, iter;
  BOOL isCalculated;
  Sppd *ppd;
  Spvt *src, *dist;
  SGraph *sg, *org_sg, *new_sg;
  SGlp *org_lp, *tmp_lp;
//  SGvt *sgsrc, *sgdist;
  
  if ( screen->current_ppd == (Sppd *) NULL ) return FALSE;
  if ( screen->n_sellist != TWO_VERTICES ) {
    return FALSE;
  }

  ppd  = screen->current_ppd;
  src  = screen->sel_first->vt;
  dist = screen->sel_first->nxt->vt;

  if ( (src == NULL) || (dist == NULL) ) return FALSE;
  if ( src == dist ) return FALSE;

  // ‚±‚ê‚Í‚¢‚ç‚È‚¢D
//  free_sglp( screen->lp );
  if ( screen->nsg != NULL ) {
	  free_sgraph( screen->nsg );
	  screen->nsg = NULL;
  }

  sg = initialize_sgraph( ppd );

  sg->src  = find_sgvt_from_spvt( sg, src );
  sg->dist = find_sgvt_from_spvt( sg, dist );
  
//  if ( (sg->src == NULL) || (sg->dist == NULL) ) return FALSE;

  i = 0;
  iter = 20;
  org_sg = sg;
  org_lp = NULL;
  new_sg = NULL;
  tmp_lp = NULL;
  isCalculated = FALSE;
  double sub_ratio = SUB_RATIO;

  while ( (i < iter) && (isCalculated == FALSE) ) {
    
	  if ( org_sg != sg ) add_vertices_edges_sgraph( org_sg );

	  tmp_lp = ShortestPath_Dijkstra_SGraph( org_sg, org_sg->src, org_sg->dist );

	  new_sg = sglp_to_sgraph( tmp_lp, org_sg );

	  if ( i > 4 ) {
		  if ( fabs( new_sg->lp->length - org_sg->lp->length ) < 1.0e-05 ) {
			  isCalculated = TRUE;
		  }
	  }
    
	  free_sglp( tmp_lp );
	  tmp_lp = NULL;

	  /* delete old graph and path */
	  if ( org_sg != sg ) {
		  free_sgraph( org_sg );
		  org_sg = NULL;
		  org_lp = NULL;
	  }
	  org_sg = new_sg;
	  org_lp = new_sg->lp;
	  ++i;
	  sub_ratio *= SUB_RATIO;
	  screen->nsg = org_sg;
	  screen->lp  = org_lp;

	  // drawwindow routine
	  screen->wnd->RedrawWindow();

  }

//  free_sgraph( org_sg );

  return TRUE;
}

/////////////////////////////////////////////
// "Delete Spath" functions 
/////////////////////////////////////////////

static void free_splp_shortest_path( Splp *lp, Sppd *ppd )
{
  Sped  *ed;
//  Sple  *le;
  Splv  *lv, *plv;
  Spvt  *vt;
  HEdge *hed;
  
  /* delete loopedges */
/*   for ( le = lp->sple; le != (Sple *) NULL; le = le->nxt ) { */

  plv = lv = lp->splv;
  lv  = lv->nxt;

  while ( lv != (Splv *) NULL ) {

    if ( (ed = find_ppdedge( plv->vt, lv->vt )) != (Sped *) NULL ) {
	    
      /*
	If there is no link to the faces( ed->type == EDGE_ADDED ), an
	edge is SP_EDGE_STEINER, thus it's deleted. else an edge is
	SP_EDGE_NORMAL, thus it should be left.
      */
      if ( (ed->type == EDGE_ADDED ) ) {
	FreeSped( ed, ppd );
      } else {
	ed->sp_type = SP_EDGE_NORMAL;
      }

    }

    if ( lv == lp->eplv ) break;
    plv = lv;
    lv = lv->nxt;

  }

  /* delete loopedges */
  for ( lv = lp->splv; lv != (Splv *) NULL; lv = lv->nxt ) {
    /*
      If there is no link to the edges, a vertex is SP_VERTEX_STEINER,
      thus it's deleted. else if a vertex is SP_VERTEX_NORMAL, thus it
      should be left.
    */
    vt = lv->vt;
    vt->lp = NULL;
    --( vt->spn );
    
    /* steiner points */
    if ( vt->sp_ed != NULL ) {
      
      vt->sp_ed = NULL;
      free_ppdvertex( vt, ppd );
      
    } else {

      if ( vt->sp_type != SP_VERTEX_HVERTEX ) {
	vt->sp_type = SP_VERTEX_NORMAL;
      }
      
    }
  }

  if ( lp->hed != NULL ) {

    hed = lp->hed;
    if ( hed->lp1 == lp ) hed->lp1 = NULL;
    if ( hed->lp2 == lp ) hed->lp2 = NULL;

  }

  free_splp( lp );

}
    
BOOL delete_spath( ScreenAtr *screen )
{
  Sppd *ppd;
  Splp *lp;
  SelList *sl;
  
  ppd = screen->current_ppd;
  for ( sl = screen->sel_first; sl != (SelList *) NULL; sl = sl->nxt ) {

    lp = sl->lp;
    free_splp_shortest_path( lp, ppd );
    sl->lp = (Splp *) NULL;
    
  }

  return TRUE;
}

/////////////////////////////////////////////
// "Create Spath Manual" functions 
/////////////////////////////////////////////

static Splp *sellist_to_splp( ScreenAtr *screen )
{
  SelList *sl;
  Splp    *lp;
  Spvt    *vt, *sv, *ev;
  Splv    *lv;
  Sped    *ed;

  lp = create_splp();
  lp->type  = SHORTESTPATH;

  for ( sl = screen->sel_first; sl != (SelList *) NULL; sl = sl->nxt ) {
    vt = sl->vt;
    lv = create_ppdloopvertex( lp );
    lv->vt = sl->vt; 
    ++( vt->spn );
    if ( (sl != screen->sel_first) && (sl != screen->sel_last) ) {
      vt->sp_type = SP_VERTEX_BOUNDARY;
      vt->lp = lp;
    }
  }

  lv = lp->splv;
  while ( lv != lp->eplv ) {
    sv = lv->vt;
    ev = lv->nxt->vt;
    if ( (ed = find_ppdedge( sv, ev )) != (Sped *) NULL ) {
      ed->sp_type = SP_EDGE_BOUNDARY;
    }
    lv = lv->nxt;
  }

  return lp;
}

BOOL manual_spath( ScreenAtr *screen )
{
  Sppd  *ppd;
  Splp  *lp;
  Spvt  *sv, *ev;
  HEdge *hed;
//  SelList *sl;
  
  ppd = screen->current_ppd;

  /* check whether shortest path can be created or not. */

  if ( screen->n_sellist < 2 ) {
    return FALSE;
  }

  sv = screen->sel_first->vt;
  ev = screen->sel_last->vt;
  hed = find_hppdedge_from_spvt( sv, ev, screen, swin->hppd );

  if ( hed == NULL ) {
    return FALSE;
  }

  if ( screen->no == SCREEN_SRC ) {
	  
	  if ( (lp = hed->lp1) != NULL ) return FALSE;

  } else {

	  if ( (lp = hed->lp2) != NULL ) return FALSE;

  }
      
  lp = sellist_to_splp( screen );

  if ( screen->no == SCREEN_SRC ) hed->lp1 = lp;
  else hed->lp2 = lp;
  lp->hed = hed;
  
  return TRUE;
}

