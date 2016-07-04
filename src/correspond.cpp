/* Copyright (c) 1997-1998 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "ppd.h"
#include "ppdsolid.h"
#include "ppdpart.h"
#include "ppdvertex.h"
#include "ppdedge.h"
#include "ppdface.h"
#include "ppdloop.h"
#include "hppd.h"
#include "hgppd.h"
#include "hged.h"
#include "correspond.h"
#include "trisquare.h"
#include "veclib.h"
#include "ps.h"

//*****************************************************************************
// STEP 3: Making New PPD
//*****************************************************************************

/* make vertices from HVertex */
Sppd *hppd_to_gppd( HPpd *hppd )
{
  Sppd *gppd;
	
  /* create gppd */
  gppd = hppd->gppd = create_ppd();
  gppd->spso = create_ppdsolid( gppd );
  gppd->sppt = create_ppdpart( gppd );
  gppd->sppt->bpso = gppd->spso;
	
  /* hgppd initialize */
  create_mhgfc( hppd );
  HGfcMakeSign( hppd );
  hvertex_to_gppd( hppd, gppd );
  hedge_to_gppd( hppd, gppd );
  mHGfcOrderBoundaryEdges( hppd );
  hface_to_gppd( hppd, gppd );
	
  return gppd;
}

void create_mhgfc( HPpd *hppd )
{
  HFace *hfc;
	
  for ( hfc = hppd->shfc; hfc != (HFace *) NULL; hfc = hfc->nxt ) {
    hfc->mhgfc = create_hgfc();
    hfc->mhgfc->id = hfc->no;
    /* temp */
    hfc->hgfc1->mhgfc = hfc->mhgfc;
    hfc->hgfc2->mhgfc = hfc->mhgfc;
  }
}

void HGfcMakeSign( HPpd *hppd )
{
  int   i;
  HGvt  *vt;
  HFace *hfc;
	
  for ( hfc = hppd->shfc; hfc != (HFace *) NULL; hfc = hfc->nxt ) {
		
    i = 0;
    for ( vt = hfc->hgfc1->shgvt; vt != (HGvt *) NULL; vt = vt->nxt ) {
      vt->sign = i;
      ++i;
    }
    for ( vt = hfc->hgfc2->shgvt; vt != (HGvt *) NULL; vt = vt->nxt ) {
      vt->sign = i;
      ++i;
    }
		
  }
	
}

/************************************************************************ */
/************************************************************************ */

/* make vertices from HVertex */
void hvertex_to_gppd( HPpd *hppd, Sppd *gppd )
{
  HVertex *hvt;
  Spvt *mvt;
  HFace *hfc;
  HGvt *hgvt1, *hgvt2, *mhgvt;
	
  for ( hvt = hppd->shvt; hvt != (HVertex *) NULL; hvt = hvt->nxt ) {
		
    /* create mvt */
    mvt = create_ppdvertex( gppd );
    hvt->vt1->mvt = mvt;
    hvt->vt2->mvt = mvt;
    mvt->bpso = gppd->spso;
    mvt->sp_type = SP_VERTEX_HVERTEX;
    mvt->from = FROM_HVERTEX;
		
    /* create hgvt */
    for ( hfc = hppd->shfc; hfc != (HFace *) NULL; hfc = hfc->nxt ) {
			
      if ( (hgvt1 = hgvt_in_hgfc( hvt->vt1, hfc->hgfc1 )) != (HGvt *) NULL ) {
				
	mhgvt = create_hgppdvertex( hfc->mhgfc );
	mhgvt->vt = mvt;
	mhgvt->uvw.x = hgvt1->uvw.x;
	mhgvt->uvw.y = hgvt1->uvw.y;
	mhgvt->sp_type = SP_VERTEX_HVERTEX;
	mvt->from = FROM_HVERTEX;
				/* link mhgvt with hgvt1 */
	hgvt1->mhgvt = mhgvt;
				
				/* link mhgvt with hgvt2 */
	hgvt2 = hgvt_in_hgfc( hvt->vt2, hfc->hgfc2 );
	hgvt2->mhgvt = mhgvt;
				
      }
			
    }
		
  }
	
}    

HGvt *hgvt_in_hgfc( Spvt *vt, HGfc *hgfc )
{
  HGvt *hgvt;
	
  for ( hgvt = hgfc->shgvt; hgvt != (HGvt *) NULL; hgvt = hgvt->nxt ) {
    if ( hgvt->vt == vt ) return hgvt;
  }
  return (HGvt *) NULL;
}

HGed *hged_in_hgfc( Spvt *sv, Spvt *ev, HGfc *hgfc )
{
  HGed *hged;
	
  if ( hgfc == (HGfc *) NULL ) return (HGed *) NULL;
  for ( hged = hgfc->shged; hged != (HGed *) NULL; hged = hged->nxt ) {
    /* これを使わなくてもよいように修正すべき */
    if ( (hged->sv->vt == sv) && (hged->ev->vt == ev) ) 
      return hged;
    if ( (hged->sv->vt == ev) && (hged->ev->vt == sv) )
      return hged;
  }
  return hged;
    
}
/************************************************************************ */
/************************************************************************ */

/* Making vertices, edges from HEdge */
void hedge_to_gppd( HPpd *hppd, Sppd *gppd )
{
  int    i;
  HEdge  *hed;
  double *prm1, *prm2;
  Splp   *lp1, *lp2;
  Splv   *lv;
  Spvt   *mvt;
  Sped   *med;
  HGvt   *hgvt, *mhgvt;
  Hedvt  *ev, *pev;
  HGed   *mhged;
  HGfc   *rhgfc1, *lhgfc1, *rhgfc2, *lhgfc2, *rmhgfc, *lmhgfc;
	
  for ( hed = hppd->shed; hed != (HEdge *) NULL; hed = hed->nxt ) {
		
    lp1 = hed->lp1;
    lp2 = hed->lp2;
		
    if ( hed->rf != (HFace *) NULL ) {
      rhgfc1 = hed->rf->hgfc1;
      rhgfc2 = hed->rf->hgfc2;
      rmhgfc = hed->rf->mhgfc;
    }
    if ( hed->lf != (HFace *) NULL ) {
      lhgfc1 = hed->lf->hgfc1;
      lhgfc2 = hed->lf->hgfc2;
      lmhgfc = hed->lf->mhgfc;
    }
		
    prm1 = (double *) malloc( lp1->lvn * sizeof( double ) );
    prm2 = (double *) malloc( lp2->lvn * sizeof( double ) );
		
    if ( hed->rf != (HFace *) NULL ) {
      lpprm_hgfc( lp1, lp1->lvn, prm1, rhgfc1 );
      lpprm_hgfc( lp2, lp2->lvn, prm2, rhgfc2 );
    } else {
      lpprm_hgfc( lp1, lp1->lvn, prm1, lhgfc1 );
      lpprm_hgfc( lp2, lp2->lvn, prm2, lhgfc2 );
    }
		
    /* loop 1 */
    for ( i = 0, lv = lp1->splv; lv != (Splv *) NULL; lv = lv->nxt, ++i ) {
			
      if ( (lv != lp1->splv) && (lv != lp1->eplv) ) {
				
				/* creating mvt */
	mvt = create_ppdvertex( gppd );
	lv->vt->mvt = mvt;
	mvt->bpso = gppd->spso;
	mvt->sp_type = SP_VERTEX_BOUNDARY;
	mvt->from  = FROM_SRC;
	mvt->vec.x = lv->vt->vec.x;
	mvt->vec.y = lv->vt->vec.y;
	mvt->vec.z = lv->vt->vec.z;
				
				/* creating mhgvt */
	if ( hed->rf != (HFace *) NULL ) {
	  mhgvt = create_hgppdvertex( rmhgfc );
	  mhgvt->vt = mvt;
	  mhgvt->sp_type = SP_VERTEX_BOUNDARY;
	  mhgvt->from = FROM_SRC;
	  hgvt = hgvt_in_hgfc( lv->vt, rhgfc1 );
	  mhgvt->uvw.x = hgvt->uvw.x;
	  mhgvt->uvw.y = hgvt->uvw.y;
	  hgvt->mhgvt = mhgvt;
	}
				
	if ( hed->lf != (HFace *) NULL ) {
	  mhgvt = create_hgppdvertex( lmhgfc );
	  mhgvt->vt = mvt;
	  mhgvt->sp_type = SP_VERTEX_BOUNDARY;
	  mhgvt->from = FROM_SRC;
	  hgvt = hgvt_in_hgfc( lv->vt, lhgfc1 );
	  mhgvt->uvw.x = hgvt->uvw.x;
	  mhgvt->uvw.y = hgvt->uvw.y;
	  hgvt->mhgvt  = mhgvt;
	}
				
	insert_hedvt( hed, mvt, prm1[i] );
				
      }
      else {
				
	insert_hedvt( hed, lv->vt->mvt, prm1[i] );
				
      }
    }
		
    /* loop 2 */
    for ( i = 0, lv = lp2->splv; lv != (Splv *) NULL; lv = lv->nxt, ++i ) {
			
      if ( (lv != lp2->splv) && (lv != lp2->eplv) ) {
				
				/* creating mvt */
	mvt = create_ppdvertex( gppd );
	lv->vt->mvt = mvt;
	mvt->bpso = gppd->spso;
	mvt->sp_type = SP_VERTEX_BOUNDARY;
	mvt->from = FROM_TARGET;
	mvt->vec.x = lv->vt->vec.x;
	mvt->vec.y = lv->vt->vec.y;
	mvt->vec.z = lv->vt->vec.z;
				
				/* creating mhgvt */
	if ( hed->rf != (HFace *) NULL ) {
	  mhgvt = create_hgppdvertex( rmhgfc );
	  mhgvt->vt = mvt;
	  mhgvt->sp_type = SP_VERTEX_BOUNDARY;
	  mhgvt->from = FROM_TARGET;
	  hgvt = hgvt_in_hgfc( lv->vt, rhgfc2 );
	  mhgvt->uvw.x = hgvt->uvw.x;
	  mhgvt->uvw.y = hgvt->uvw.y;
	  hgvt->mhgvt  = mhgvt;
	}
				
	if ( hed->lf != (HFace *) NULL ) {
	  mhgvt = create_hgppdvertex( lmhgfc );
	  mhgvt->vt = mvt;
	  mhgvt->sp_type = SP_VERTEX_BOUNDARY;
	  mhgvt->from = FROM_TARGET;
	  hgvt = hgvt_in_hgfc( lv->vt, lhgfc2 );
	  mhgvt->uvw.x = hgvt->uvw.x;
	  mhgvt->uvw.y = hgvt->uvw.y;
	  hgvt->mhgvt  = mhgvt;
	}
				
	insert_hedvt( hed, mvt, prm2[i] );
				
      }
			
    }
		
    /* create merging loop */
    hed->mlp = create_splp();
		
    ev = hed->sedvt;
    while ( 1 ) {
			
      /* create merging loop */
      lv = create_ppdloopvertex( hed->mlp );
      lv->vt = ev->vt;
			
      pev = ev;
      ev = ev->nxt;
      if ( ev == (Hedvt *) NULL ) break;
			
      /* creating med */
      med = create_ppdedge( gppd );
      med->sv = pev->vt;
      med->ev = ev->vt;
      med->sp_type = SP_EDGE_BOUNDARY;
			
      /* creating mhged */
      if ( hed->rf != (HFace *) NULL ) {
	mhged = create_hgppdedge( rmhgfc );
	mhged->sv = hgvt_in_hgfc( med->ev, rmhgfc );
	mhged->ev = hgvt_in_hgfc( med->sv, rmhgfc );
	mhged->ed = med;
	mhged->sp_type = SP_EDGE_BOUNDARY;
      }
			
      if ( hed->lf != (HFace *) NULL ) {
	mhged = create_hgppdedge( lmhgfc );
	mhged->sv = hgvt_in_hgfc( med->sv, lmhgfc );
	mhged->ev = hgvt_in_hgfc( med->ev, lmhgfc );
	mhged->ed = med;
	mhged->sp_type = SP_EDGE_BOUNDARY;
      }
			
    }
		
    free(prm1); free(prm2);
		
    /* hged->sp_type == SP_EDGE_BOUNDARY の整列 */
    /* 本当はこんなところでやるべきことではない */
		
    if ( hed->rf != (HFace *) NULL ) {
      HGvtIncludeHGed( hed, lp1, lp2, rhgfc1, rhgfc2, FROM_TARGET );
      HGvtIncludeHGed( hed, lp2, lp1, rhgfc2, rhgfc1, FROM_SRC );
    }
    if ( hed->lf != (HFace *) NULL ) {
      HGvtIncludeHGed( hed, lp1, lp2, lhgfc1, lhgfc2, FROM_TARGET );
      HGvtIncludeHGed( hed, lp2, lp1, lhgfc2, lhgfc1, FROM_SRC );
    }
		
  }
  
  /* あとの 3D vector の計算のために Hedvt は残しておく */
}

/* hgvt1 の hged2 に対する inc_ed を定める */
void HGvtIncludeHGed( HEdge *hed, Splp *lp1, Splp *lp2,
		      HGfc *hgfc1, HGfc *hgfc2, int from )
{
  int  i;
  HGedArray *harray;
  Splv *lv;
  Spvt *vt;
  HGed *ed;
  HGvt *hgvt;
  Hedvt *ev;
	
  harray = (HGedArray *) malloc( lp2->lvn * sizeof( HGedArray ) );
  i = 0;
  for ( lv = lp2->splv; lv->nxt != (Splv *) NULL; lv = lv->nxt ) {
    harray[i].ed = hged_in_hgfc( lv->vt, lv->nxt->vt, hgfc2 );
    ++i;
  }
	
  i = 0;
  ed = harray[i].ed;
  for ( ev = hed->sedvt; ev != (Hedvt *) NULL; ev = ev->nxt ) {
		
    if ( ev->vt->from != from ) {
      vt   = spvt_from_mvt_in_lp( ev->vt, lp1 );
      hgvt = hgvt_in_hgfc( vt, hgfc1 );
      hgvt->inc_ed = ed;
			
    } else {
      ++i;
      ed = harray[i].ed;
    }
  }
	
  free( harray );
}

/* find ppdvertex from morph ppd vertex in loop */
Spvt *spvt_from_mvt_in_lp( Spvt *mvt, Splp *lp )
{
  Splv *lv;
	
  for ( lv = lp->splv; lv != (Splv *) NULL; lv = lv->nxt ) {
    if ( lv->vt->mvt == mvt ) return lv->vt;
  }
  return (Spvt *) NULL;
}

void lpprm( Splp *lp, int vn, double *prm )
{
  int    i = 0;
  double sum = 0.0;
  Splv   *plv, *lv;
	
  lv = lp->splv;
  while (1) {
    prm[i] = sum; ++i;
    plv = lv;
    lv = lv->nxt;
    if ( lv == (Splv *) NULL ) break;
    sum += V3DistanceBetween2Points( &(plv->vt->vec), &(lv->vt->vec) );
  }
	
  for ( i = 0; i < vn; ++i ) {
    prm[i] /= sum;
  }
}

void lpprm_hgfc( Splp *lp, int vn, double *prm, HGfc *hgfc )
{
  int    i = 0;
  double sum = 0.0;
  HGvt   *hv, *phv;
  Splv   *plv, *lv;
	
  lv = lp->splv;
  hv = hgvt_in_hgfc( lv->vt, hgfc );
  while ( 1 ) {
    prm[i] = sum; ++i;
    if ( i == vn ) break;
    plv = lv; phv = hv;
    lv = lv->nxt;
    hv = hgvt_in_hgfc( lv->vt, hgfc );
    sum += ( V2DistanceBetween2Points( &(phv->uvw), &(hv->uvw) ) );
  }
	
  for ( i = 0; i < vn; ++i ) {
    prm[i] /= sum;
  }
}

/************************************************************************ */
/************************************************************************ */

void mHGfcOrderBoundaryEdges( HPpd *hppd )
{
  int   reverse;
  HFace *hf;
  HHalfedge *he;
  HEdge *hed;
  HVertex *shvt, *ehvt;
  HGfc  *hgfc;
  HGed  *hged;
  Spvt  *svt, *evt;
  HGvt  *hgvt, *shgvt, *ehgvt;
  Splp  *lp;
  Splv  *lv;
	
  for ( hf = hppd->shfc; hf != (HFace *) NULL; hf = hf->nxt ) {
    hgfc = hf->mhgfc;
		
    he = hf->shhe;
    do {
			
      hed  = he->hed;
      shvt = he->vt;
      ehvt = he->nxt->vt;
			
      lp   = hed->mlp;
			
      svt = shvt->vt1->mvt;
      evt = ehvt->vt1->mvt;
      shgvt = hgvt_in_hgfc( svt, hgfc );
      ehgvt = hgvt_in_hgfc( evt, hgfc );
			
      if ( shvt == hed->sv ) reverse = SMD_OFF;
      else                   reverse = SMD_ON;
			
      for ( lv = lp->splv; lv->nxt != (Splv *) NULL; lv = lv->nxt ) {
				
	hged = hged_in_hgfc( lv->vt, lv->nxt->vt, hgfc );
				
	if ( !reverse ) {
	  if ( hged->sv->vt != lv->vt ) {
	    hgvt     = hged->sv;
	    hged->sv = hged->ev;
	    hged->ev = hgvt;
	  }
	} else {
	  if ( hged->ev->vt != lv->vt ) {
	    hgvt     = hged->sv;
	    hged->sv = hged->ev;
	    hged->ev = hgvt;
	  }
	}
				
				/* for create HGvted */
	hged->sv->startedge = hged;
	hged->ev->endedge   = hged;
      }
			
    } while ( (he = he->nxt) != hf->shhe );
  }
	
}

/************************************************************************ */
/************************************************************************ */

/* make vertices, edges, faces from HFace */
void hface_to_gppd( HPpd *hppd, Sppd *gppd )
{
  HFace *hfc;
  HGfc  *hgfc1, *hgfc2, *mhgfc;
  char  str[BUFSIZ];
	
  for ( hfc = hppd->shfc; hfc != (HFace *) NULL; hfc = hfc->nxt ) {
		
    hgfc1 = hfc->hgfc1;
    hgfc2 = hfc->hgfc2;
    mhgfc = hfc->mhgfc;
		
    /* make harmonic map */
    if ( swin->savehmtops ) {
      sprintf( str, "hgfc1hrm%d.ps", hfc->no );
      hgfc_harmonicmap_to_ps( str, hgfc1 );
      sprintf( str, "hgfc2hrm%d.ps", hfc->no );
      hgfc_harmonicmap_to_ps( str, hgfc2 );
    }
		
    /* make hgsf  */
    hgppdface_to_hgppdsurface( hgfc1 );
    hgppdface_to_hgppdsurface( hgfc2 );
		
    /* 二つの hgfc を合成 */
    hgfc_to_mhgfc( hgfc1, hgfc2, mhgfc );
		
    HGfcTriangulation_noEdge( mhgfc );
		
    if ( swin->savehmtops ) {
      sprintf( str, "mhgfchrm%d.ps", hfc->no );
      hgfc_harmonicmap_to_ps( str, mhgfc );
    }
		
    /* mhgfc の頂点はすべてここで gppd の頂点にする */
    mhgfc_to_gppd( mhgfc, gppd );
		
  }
	
}

/************************************************************************ */

void hgppdface_to_hgppdsurface( HGfc *hgfc )
{
  HGvt *hgvt;
	
  /* これはいいかげん */
  makehgvtedlink( hgfc );
	
  for ( hgvt = hgfc->shgvt; hgvt != (HGvt *) NULL; hgvt = hgvt->nxt ) 
    HGfcMakeHGsfFromHGvt( hgvt, hgfc );
	
  HGfcTriangulation( hgfc );
}

void makehgvtedlink( HGfc *hgfc )
{
  HGed   *hged;
	
  for ( hged = hgfc->shged; hged != (HGed *) NULL; hged = hged->nxt ) {
    insert_hgvted( hged->sv, hged );
    insert_hgvted( hged->ev, hged );
  }
}

void HGfcMakeHGsfFromHGvt( HGvt *vt, HGfc *hgfc )
{
  HGvted *hgve;
	
  for ( hgve = vt->shgve; hgve != (HGvted *) NULL; hgve = hgve->nxt ) {
		
    if ( TRUE == HGsfCreateCheck( vt, hgve->ed ) ) {
      (void) HGsfCreate( vt, hgve->ed, hgfc );
    }
		
  }
	
}

BOOL HGsfCreateCheck( HGvt *start_vertex, HGed *start_edge )
{
  HGvt *vt, *nvt;
  HGed *ed, *ned;
  HGsf *sf;
	
  vt = start_vertex;
  ed = start_edge;
	
  // Changed on Sep. 1, 1998
  if ( (vt == NULL) || (ed == NULL) ) return FALSE;
	
  while (1) {
    
    // Changed on Sep. 1, 1998
    //		このコメントをはずすと moser-kanai が通る
    if ( (vt == NULL) || (ed == NULL) ) return FALSE;
		
    if ( ( ed->sp_type == SP_EDGE_BOUNDARY ) && ( ed->ev == vt ) ) {
      /* boundary rotation */
      return FALSE;
    }
		
    sf = HGedLeftFace( ed, vt );
    if ( sf != (HGsf *) NULL ) {
      /* already exist HGsf */
      return FALSE;
    }
		
    nvt = HGedAnotherVertex( ed, vt );
    ned = HGvtedNextCCWEdge( nvt, ed );
		
    if ( nvt == start_vertex ) {
      return TRUE;
    }
		
    if ( (nvt == vt ) || (ned == ed ) ) {
      return FALSE;
    }
    vt = nvt;
    ed = ned;
  }
	
}

void HGsfCreate( HGvt *start_vertex, HGed *start_edge, HGfc *hgfc )
{
  HGvt *vt, *nvt;
  HGed *ed, *ned;
  HGsf *sf;
  HGhe *he;
	
  sf = create_hgppdsurface( hgfc );
	
  vt = start_vertex;
  ed = start_edge;
	
  while (1) {
		
    he = create_hgppdhalfedge( sf );
    he->vt = vt;
    he->ed = ed;
    HGedAppendLeftFace( ed, vt, sf );
		
    nvt = HGedAnotherVertex( ed, vt );
    ned = HGvtedNextCCWEdge( nvt, ed );
		
    if ( nvt == start_vertex ) {
      return;
    }
    vt = nvt;
    ed = ned;
  }
	
}

/************************************************************************ */

/* Merge Two hgfcs */
void hgfc_to_mhgfc( HGfc *hgfc1, HGfc *hgfc2, HGfc *mhgfc )
{
  /* hgvt の頂点を mhgfc にする */
  hgvt_to_mhgvt( hgfc1, mhgfc, SRC );
  hgvt_to_mhgvt( hgfc2, mhgfc, TARGET );
	
  /* エッジの合成 */
  hged_to_mhged( hgfc1, hgfc2, mhgfc );
  mhgfc_create_mhgsf( mhgfc );
}  

/***********************************/

/* create mvt from hgvt */

void hgvt_to_mhgvt( HGfc *hgfc, HGfc *mhgfc, int from )
{
  HGvt *hgvt, *mhgvt;
	
  for ( hgvt = hgfc->shgvt; hgvt != (HGvt *) NULL; hgvt = hgvt->nxt ) {
		
    if ( hgvt->vt->sp_type == SP_VERTEX_NORMAL ) {
			
      /* create mhgvt */
      mhgvt = create_hgppdvertex( mhgfc );
      mhgvt->uvw.x = hgvt->uvw.x;
      mhgvt->uvw.y = hgvt->uvw.y;
      mhgvt->from  = from;
      hgvt->mhgvt = mhgvt;
    }
		
  }
}

/***********************************/

void hged_to_mhged( HGfc *hgfc1, HGfc *hgfc2, HGfc *mhgfc )
{
	
  /** ここを位相優先法，記号摂動法にもとづく方法に変える **/
  /* エッジ間の交点を調べ，mhgfc に頂点を生成する */
  hgfc_edge_edge_intersection( hgfc1, hgfc2, mhgfc );
	
  /* hged のエッジ分割情報をもとに，mhgfc のエッジを生成 */
  mhgfc_create_mhged( hgfc1, hgfc2, mhgfc );
}

/* Edge-Edge Intersection */
/*
  This algorithm is based on:
  James R. Kent, Wayne E. Carlson and Richard E. Parent,
  "Shape Transformation for Polyhedral Objects", in SIGGRAPH'92
  - 5.2 The Merging Algorithm -
*/
/* 
isLineSegmentCrossing を記号摂動法に代える
*/

/*
(sv->sp_type == SP_VERTEX_BOUNDARY) || (ev->sp_type != SP_VERTEX_BOUNDARY)  
の場合は別処理をする必要がある
-> する必要なし?
*/

void hgfc_edge_edge_intersection( HGfc *hgfc1, HGfc *hgfc2, HGfc *mhgfc )
{
  int  flag;
  HGed *ed, *e1, *e2;
  HGsf *sf, *nf, *f2;
  HGvt *sv, *ev, *mhgvt, *tmp_vt;
  HGhe *he;
  HGvted *vted;
  HGedvt *hgedvt1, *hgedvt2;
  HGedList *edgelist1, *edgelist2;
	
  /* initialize hged in hgfc1 */
  for ( ed = hgfc1->shged; ed != (HGed *) NULL; ed = ed->nxt ) {
    if ( ed->sp_type != SP_EDGE_BOUNDARY ) ed->pass = SMD_ON;
    else ed->pass = SMD_OFF;
  }
	
  for ( ed = hgfc1->shged; ed != (HGed *) NULL; ed = ed->nxt ) {
		
    if ( ed->pass == SMD_ON ) {
			
      edgelist1 = create_hgedlist();
      (void) create_hgednode( ed, edgelist1 );
      ed->pass = SMD_OFF;
			
      flag = SMD_OFF;
      if ( (sf = find_hgsf_in_hgfc( ed->sv, hgfc2 )) != (HGsf *) NULL ) {
	if ( ed->sv->sp_type == SP_VERTEX_NORMAL ) {
	  ed->sv->inc_sf = sf;
	}
	flag = SMD_ON;
      }
      if ( (sf = find_hgsf_in_hgfc( ed->ev, hgfc2 )) != (HGsf *) NULL ) {
	if ( ed->ev->sp_type == SP_VERTEX_NORMAL ) {
	  ed->ev->inc_sf = sf;
	}
	flag = SMD_ON;
      }
			
      if ( !flag ) {
	free_hgedlist( edgelist1 );
	continue;
      }
			
      while ( edgelist1->en ) {
				
	e1 = edgelist1->senode->ed;
				
				
	if ( (f2 = includeHGsf( e1->sv )) != (HGsf *) NULL ) {
	  sv = e1->sv;
	  ev = e1->ev;
	} else if ( (f2 = includeHGsf( e1->ev )) != (HGsf *) NULL ) {
	  sv = e1->ev;
	  ev = e1->sv;
	  /* swap */
	  tmp_vt = e1->sv;
	  e1->sv = e1->ev;
	  e1->ev = tmp_vt;
	} else {
	  free_start_hgednode( edgelist1 );
	  continue;
	}
				
				/* add the edges originating at v1 to edgelist */
	if ( sv->sp_type != SP_VERTEX_HVERTEX ) {
	  for ( vted = sv->shgve; vted != (HGvted *) NULL; vted = vted->nxt ) {
	    if ( vted->ed->pass == SMD_ON ) {
							
	      (void) create_hgednode( vted->ed, edgelist1 );
	      vted->ed->pass = SMD_OFF;
	    }
	  }
	}
				
	edgelist2 = create_hgedlist();
	he = f2->shghe;
	do {
	  if ( TRUE == isEdgeValidforCandidate( e1, he->ed ) ) {
	    (void) create_hgednode( he->ed, edgelist2 );
	  }
	} while ( (he = he->nxt) != f2->shghe );
				
				/* 一本のエッジの交点探索 */
	while ( edgelist2->en ) {
					
	  e2 = edgelist2->senode->ed;
					
	  if ( isHGvtLineSegmentCrossing( sv, ev, e2->sv, e2->ev) == TRUE ) {
						
	    /* create hgppdvertex */
	    mhgvt = create_hgppdvertex( mhgfc );

	    /* これはあとで求める */
	    /* 	    mhgvt->vt = mvt; */
	    mhgvt->sp_type = SP_VERTEX_NORMAL;
	    mhgvt->from = FROM_INTSEC;
	    LineIntersectionPoint( &(sv->uvw), &(ev->uvw),
				   &(e2->sv->uvw), &(e2->ev->uvw),
				   &(mhgvt->uvw) );
						
	    /* insert hgedvt in e1, e2 */
	    /* hged2 の方は，hged1 の rv と lv を格納しておく */
	    /* create vertex->edge in counter-clockwise */
	    hgedvt1 = create_hgedvt( mhgvt, e1 );
	    hgedvt1->intsec_ed = e2;
	    hgedvt1->rf = e2->rf;
	    hgedvt1->lf = e2->lf;
	    /* set edge rotation */
	    /* 	    if ( TRUE == isLeftSide( &(e1->sv->uvw), &(e1->ev->uvw), &(e2->sv->uvw) ) ) { */
	    if ( TRUE == isHGvtLeftSide( e1->sv, e1->ev, e2->sv ) ) {
	      hgedvt1->rotation = EDGE_END;
	    } else {
	      hgedvt1->rotation = EDGE_START;
	    }
						
	    hgedvt2 = create_hgedvt( mhgvt, e2 );
	    hgedvt2->intsec_ed = e1;
	    hgedvt2->rf = e1->rf;
	    hgedvt2->lf = e1->lf;
	    /* set edge rotation */
	    if ( TRUE == isHGvtLeftSide( e2->sv, e2->ev, e1->sv ) ) {
	      hgedvt2->rotation = EDGE_END;
	    } else {
	      hgedvt2->rotation = EDGE_START;
	    }
						
	    hgedvt1->mate = hgedvt2;
	    hgedvt2->mate = hgedvt1;
						
	    nf = another_hgsf( e2, f2 );
						
	    if ( nf == (HGsf *) NULL ) break;
						
	    he = nf->shghe;
	    do {
	      if ( he->ed != e2 ) {
		if ( TRUE == isEdgeValidforCandidate( e1, he->ed ) ) {
		  (void) create_hgednode( he->ed, edgelist2 );
		}
	      }
	    } while ( (he = he->nxt) != nf->shghe );
						
	    f2 = nf;
	  }
	  free_start_hgednode( edgelist2 );
	}
				
				
	if ( ev->sp_type == SP_VERTEX_NORMAL ) ev->inc_sf = f2;
	else if ( ev->sp_type != SP_VERTEX_HVERTEX ) {
	  for ( vted = ev->shgve; vted != (HGvted *) NULL; vted = vted->nxt ) {
	    if ( vted->ed->pass == SMD_ON ) {
	      (void) create_hgednode( vted->ed, edgelist1 );
	      vted->ed->pass = SMD_OFF;
	    }
	  }
	}
				
	free_hgedlist( edgelist2 );
	free_start_hgednode( edgelist1 );
				
				
      } /* while ( edgelist1->en ) */
	  
      free_hgedlist( edgelist1 );
      
    } /* if ( ed->pass == SMD_ON ) */
	
	
  }
  
  /* あとの 3D vector の計算のために HGedvt は残しておく */
}

BOOL isEdgeValidforCandidate( HGed *e1, HGed *e2 )
{
	
  if ( e2->sp_type == SP_EDGE_BOUNDARY ) return FALSE;
	
  if ( e2->sv->sp_type == SP_VERTEX_HVERTEX ) {
    if ( e1->sv->sp_type == SP_VERTEX_HVERTEX ) {
      if ( e2->sv->mhgvt == e1->sv->mhgvt ) return FALSE;
    }
    if ( e1->ev->sp_type == SP_VERTEX_HVERTEX ) {
      if ( e2->sv->mhgvt == e1->ev->mhgvt ) return FALSE;
    }
  }
    
  if ( e2->ev->sp_type == SP_VERTEX_HVERTEX ) {
    if ( e1->sv->sp_type == SP_VERTEX_HVERTEX ) {
      if ( e2->ev->mhgvt == e1->sv->mhgvt ) return FALSE;
    }
    if ( e1->ev->sp_type == SP_VERTEX_HVERTEX ) {
      if ( e2->ev->mhgvt == e1->ev->mhgvt ) return FALSE;
    }
  }
	
  return TRUE;
}

HGsf *includeHGsf( HGvt *vt )
{
	
  HGed *hged;
	
  if ( vt->sp_type == SP_VERTEX_NORMAL ) {
		
    if ( vt->inc_sf != (HGsf *) NULL ) return vt->inc_sf;
    else return (HGsf *) NULL;
    
  } else if ( vt->sp_type == SP_VERTEX_BOUNDARY ) {
		
    hged = vt->inc_ed;
    /*     if ( hged == NULL ) return NULL; */
    if ( hged->rf != (HGsf *) NULL ) return hged->rf;
    else return hged->lf;
		
  } 
	
  return (HGsf *) NULL;
	
}

HGsf *find_hgsf_in_hgfc( HGvt *hgvt, HGfc *hgfc )
{
  HGsf    *sf;
  HGed    *hged;
	
  if ( hgvt->sp_type == SP_VERTEX_NORMAL ) {
		
    /* Kent の方法と同じ */
    if ( hgvt->inc_sf != (HGsf *) NULL ) return hgvt->inc_sf;
		
    for ( sf = hgfc->shgsf; sf != (HGsf *) NULL; sf = sf->nxt ) {
			
      /*       if ( isPointinHGsf( sf, &(hgvt->uvw) ) == TRUE ) return sf; */
      if ( isHGvtinHGsf( sf, hgvt ) == TRUE ) return sf;
			
    }
    return (HGsf *) NULL;
		
  } else if ( hgvt->sp_type == SP_VERTEX_BOUNDARY ) {
		
    /* use boundary information */
    /* 境界でのエッジの位相は固定して扱う */
    /* hedge_to_gppd によって決まる境界エッジの位相を用いる */
		
    hged = hgvt->inc_ed;
		
    if ( hged->rf != (HGsf *) NULL ) return hged->rf;
    else return hged->lf;
		
  } else {
		
    return (HGsf *) NULL;
		
  }
	
}

void mhgfc_create_mhged( HGfc *hgfc1, HGfc *hgfc2, HGfc *mhgfc )
{
  HGed *hged;
	
  /* sort H2's intersection points */
  /* H1's points have already sorted. */
  /* decide hgvt1's inc_sf ( used in "hface_calc_morph_vector"(morphvec.c) ) */
  /* まだよく整理されていない */
	
  for ( hged = hgfc2->shged; hged != (HGed *) NULL; hged = hged->nxt ) 
    HGedvtSort( hged );
	
  /* create mhged */
  HGfcCreatemHGed( hgfc1, mhgfc );
  HGfcCreatemHGed( hgfc2, mhgfc );
	
  /* create mhgvt->mhged links */
  mHGfcCreateHGvted( hgfc1, hgfc2, mhgfc );
	
  /* re-order hgvted */
  /* あまりよい方法ではない */
  HVertexCreateHGvted( mhgfc );
}

void HGedvtSort( HGed *hged )
{
  BOOL    reverse;
  HGsf       *sf, *ef;
  HGedvt     *hgev, *nhgev;
  HGedvtList *hgedvtlist;
  HGedvtNode *node;
	
  if ( !(hged->hgevn) ) return;
	
  hgedvtlist = create_hgedvtlist();
  /* insert first hgedvt to hgedvtlist */
  hgev = hged->shgev;
  node = create_end_hgedvtnode( hgedvtlist );
  node->intsec_ed = hgev->intsec_ed;
  node->vt = hgev->vt;
  node->sf = hgev->lf;
  node->ef = hgev->rf;
  node->mate = hgev->mate;
  free_hgedvt( hgev, hged );
	
  sf = node->sf;
  ef = node->ef;
	
  while ( hged->hgevn ) {
		
    for ( hgev = hged->shgev; hgev != (HGedvt *) NULL; hgev = nhgev ) {
			
      nhgev = hgev->nxt;
			
      if ( sf == hgev->lf ) {
				/* change surface */
	sf = hgev->rf;
	node = create_start_hgedvtnode( hgedvtlist );
	node->intsec_ed = hgev->intsec_ed;
	node->vt = hgev->vt;
	node->sf = hgev->rf;
	node->ef = hgev->lf;
	node->mate = hgev->mate;
	node->rotation = hgev->rotation;
	free_hgedvt( hgev, hged );
	continue;
      } else if ( sf == hgev->rf ) {
				/* change surface */
	sf = hgev->lf;
	node = create_start_hgedvtnode( hgedvtlist );
	node->intsec_ed = hgev->intsec_ed;
	node->vt = hgev->vt;
	node->sf = hgev->lf;
	node->ef = hgev->rf;
	node->mate = hgev->mate;
	node->rotation = hgev->rotation;
	free_hgedvt( hgev, hged );
	continue;
      }
      if ( ef == hgev->lf ) {
				/* change surface */
	ef = hgev->rf;
	node = create_end_hgedvtnode( hgedvtlist );
	node->intsec_ed = hgev->intsec_ed;
	node->vt = hgev->vt;
	node->sf = hgev->lf;
	node->ef = hgev->rf;
	node->mate = hgev->mate;
	node->rotation = hgev->rotation;
				
	free_hgedvt( hgev, hged );
	continue;
      } else if ( ef == hgev->rf ) {
				/* change surface */
	ef = hgev->lf;
	node = create_end_hgedvtnode( hgedvtlist );
	node->intsec_ed = hgev->intsec_ed;
	node->vt = hgev->vt;
	node->sf = hgev->rf;
	node->ef = hgev->lf;
	node->mate = hgev->mate;
	node->rotation = hgev->rotation;
	free_hgedvt( hgev, hged );
	continue;
      }
    }
		
  } /*  while ( hged->hgevn ) */
	
  /* decide order */
  /* ちょっといいかげん */
  reverse = HGedvtDecideOrder( hged->sv, hged->ev, sf, ef );
	
  /* decide include sf */
  if ( reverse == FALSE ) {
    if ( hged->sv->sp_type == SP_VERTEX_NORMAL ) {
      hged->sv->inc_sf = sf;
    }
    if ( hged->ev->sp_type == SP_VERTEX_NORMAL ) {
      hged->ev->inc_sf = ef;
    }
  } else {
    if ( hged->sv->sp_type == SP_VERTEX_NORMAL ) {
      hged->sv->inc_sf = ef;
    }
    if ( hged->ev->sp_type == SP_VERTEX_NORMAL ) {
      hged->ev->inc_sf = sf;
    }
  }
	
  /* re-create hgedvt */
  if ( reverse == FALSE ) {
    for ( node = hgedvtlist->senode; node != (HGedvtNode *) NULL; node = node->nxt ) {
      hgev = create_hgedvt( node->vt, hged );
      hgev->lf = node->sf;
      hgev->rf = node->ef;
      hgev->intsec_ed = node->intsec_ed;
      hgev->mate = node->mate;
      hgev->rotation = node->rotation;
    }
  } else {
    for ( node = hgedvtlist->eenode; node != (HGedvtNode *) NULL; node = node->prv ) {
      hgev = create_hgedvt( node->vt, hged );
      hgev->lf = node->ef;
      hgev->rf = node->sf;
      hgev->intsec_ed = node->intsec_ed;
      hgev->mate = node->mate;
      hgev->rotation = node->rotation;
    }
  }
	
  free_hgedvtlist( hgedvtlist );
	
}

BOOL HGedvtDecideOrder( HGvt *sv, HGvt *ev, HGsf *sf, HGsf *ef )
{
  HGed *inc_ed;
  HGsf *fc;
	
  if ( sf == ef ) return FALSE;
	
  if ( sv->sp_type == SP_VERTEX_NORMAL ) {
    if ( isHGvtinHGsf( sf, sv ) == TRUE  ) return FALSE;
    if ( isHGvtinHGsf( ef, sv ) == TRUE  ) return TRUE;
  }
    
  if ( ev->sp_type == SP_VERTEX_NORMAL ) {
    if ( isHGvtinHGsf( ef, ev ) == TRUE  ) return FALSE;
    if ( isHGvtinHGsf( sf, ev ) == TRUE  ) return TRUE;
  }
    
  if ( sv->sp_type == SP_VERTEX_BOUNDARY ) {
    inc_ed = sv->inc_ed;
    fc = ( inc_ed->lf != (HGsf *) NULL ) ? inc_ed->lf : inc_ed->rf;
    if ( fc == sf ) return FALSE;
    if ( fc == ef ) return TRUE;
  }
    
  if ( ev->sp_type == SP_VERTEX_BOUNDARY ) {
    inc_ed = ev->inc_ed;
    fc = ( inc_ed->lf != (HGsf *) NULL ) ? inc_ed->lf : inc_ed->rf;
    if ( fc == ef ) return FALSE;
    if ( fc == sf ) return TRUE;
  }
    
  /* ここまでくるということはかなりあやしい */
  return FALSE;
}    

void HGfcCreatemHGed( HGfc *hgfc, HGfc *mhgfc )
{
  HGed *hged;
	
  for ( hged = hgfc->shged; hged != (HGed *) NULL; hged = hged->nxt ) 
    HGedCreatemHGed( hged, mhgfc );
}

void HGedCreatemHGed( HGed *hged, HGfc *mhgfc )
{
  HGed *mhged, *prv_mhged;
  HGeded *hgee;
  HGedvt *hgev, *mate_hgev;
	
  if ( hged->sp_type != SP_EDGE_NORMAL ) return;
	
  mhged = create_hgppdedge( mhgfc );
  mhged->sv = hged->sv->mhgvt;
  hgee = create_hgeded( hged );
  hgee->mhged = mhged;
	
  for ( hgev = hged->shgev; hgev != (HGedvt *) NULL; hgev = hgev->nxt ) {
		
    prv_mhged = mhged;
    prv_mhged->ev = hgev->vt;
    mhged = create_hgppdedge( mhgfc );
    mhged->sv = hgev->vt;
    hgee = create_hgeded( hged );
    hgee->mhged = mhged;
		
    hgev->mhged[0] = prv_mhged;
    hgev->mhged[2] = mhged;
		
    mate_hgev = hgev->mate;
		
    if ( mate_hgev->rotation == EDGE_START ) {
      mate_hgev->mhged[1] = prv_mhged;
      mate_hgev->mhged[3] = mhged;
    } else {
      mate_hgev->mhged[1] = mhged;
      mate_hgev->mhged[3] = prv_mhged;
    }
  }
  mhged->ev = hged->ev->mhgvt;
}

void mHGfcCreateHGvted( HGfc *hgfc1, HGfc *hgfc2, HGfc *mhgfc )
{
  int  i;
  HGed *hged;
  HGedvt *hgev;
  HGvted *mvted;
  HGvt *mhgvt;
	
  HGfcCreateHGvted( hgfc1, mhgfc );
  HGfcCreateHGvted( hgfc2, mhgfc );
	
  for ( hged = hgfc1->shged; hged != (HGed *) NULL; hged = hged->nxt ) {
		
    for (hgev = hged->shgev; hgev != (HGedvt *) NULL; hgev = hgev->nxt ) {
			
      mhgvt = hgev->vt;
			
      for ( i = 0; i < NUM_INTERSECTION_EDGE; ++i ) {
	mvted = create_hgvted( mhgvt, hgev->mhged[i] );
      }
    }
  }
}

void HGfcCreateHGvted( HGfc *hgfc, HGfc *mhgfc )
{
  HGvt   *hgvt, *mhgvt;
  HGed   *start_hged, *end_hged, *hged;
  HGvted *mvted, *ve, *start_ve, *end_ve;
  HGvted *create_hgvted(HGvt *, HGed *);
  HGvted *find_hgvted( HGvt *, HGed * );
  HGed   *find_hgvted_startedge_boundary( HGvt * );
  HGed   *find_hgvted_endedge_boundary( HGvt * );
	
  for ( hgvt = hgfc->shgvt; hgvt != (HGvt *) NULL; hgvt = hgvt->nxt ) {
		
    /* すでに時計と反対周りに並んでいるはず */
    mhgvt = hgvt->mhgvt;
		
    if ( hgvt->sp_type != SP_VERTEX_NORMAL ) {
			
      /* startedge, endedge are created in "mHGfcOrderBoundaryEdges" */
			
      /* store start edge */
      /* consider in the case of duplicate edges */
      if ( hgvt->sp_type == SP_VERTEX_HVERTEX ) {
	if ( (mvted = find_hgvted( mhgvt, mhgvt->startedge )) == NULL ) {
	  mvted = create_hgvted( mhgvt, mhgvt->startedge );
	}
      } else {
	mvted = create_hgvted( mhgvt, mhgvt->startedge );
      }
			
      start_hged = find_hgvted_startedge_boundary( hgvt );
      start_ve   = find_hgvted( hgvt, start_hged );
      end_hged   = find_hgvted_endedge_boundary( hgvt );
      end_ve     = find_hgvted( hgvt, end_hged );
			
      ve = start_ve;
			
      while ( 1 ) {
				
	ve = ve->nxt;
	if ( ve == (HGvted *) NULL ) ve = hgvt->shgve;
	if ( ve == end_ve ) break;
				
				/* store normal edge */
	hged = ve->ed;
	if ( hged->sv == hgvt ) {
	  mvted = create_hgvted( mhgvt, hged->smhged->mhged );
	} else {
	  mvted = create_hgvted( mhgvt, hged->emhged->mhged );
	}
				
      }
			
      /* store end edge */
      /* consider in the case of duplicate edges */
      if ( hgvt->sp_type == SP_VERTEX_HVERTEX ) {
	if ( (mvted = find_hgvted( mhgvt, mhgvt->endedge )) == NULL ) {
	  mvted = create_hgvted( mhgvt, mhgvt->endedge );
	}
      } else {
	mvted = create_hgvted( mhgvt, mhgvt->endedge );
      }
			
    } else {
			
      for ( ve = hgvt->shgve; ve != (HGvted *) NULL; ve = ve->nxt ) {
				
	hged = ve->ed;
	if ( hged->sv == hgvt ) {
	  mvted = create_hgvted( mhgvt, hged->smhged->mhged );
	} else {
	  mvted = create_hgvted( mhgvt, hged->emhged->mhged );
	}
				
      }
			
    }
  }
	
}

HGed *find_hgvted_startedge_boundary( HGvt *hgvt )
{
  HGed   *ed;
  HGvted *ve;
	
  for ( ve = hgvt->shgve; ve != (HGvted *) NULL; ve = ve->nxt ) {
    ed = ve->ed;
    if ( ed->sp_type == SP_EDGE_BOUNDARY ) {
      if ( ed->sv == hgvt ) return ed;
    }
  }
  return NULL;
}

HGed *find_hgvted_endedge_boundary( HGvt *hgvt )
{
  HGed   *ed;
  HGvted *ve;
	
  for ( ve = hgvt->shgve; ve != (HGvted *) NULL; ve = ve->nxt ) {
    ed = ve->ed;
    if ( ed->sp_type == SP_EDGE_BOUNDARY ) {
      if ( ed->ev == hgvt ) return ed;
    }
  }
  return NULL;
}

void HVertexCreateHGvted( HGfc *hgfc )
{
  int n, i;
  HGvted *ve;
  HGvt *hgvt, *v;
  HGed  *ed;
  HGedArray *harray;
	
  for ( hgvt = hgfc->shgvt; hgvt != (HGvt *) NULL; hgvt = hgvt->nxt ) {
		
    if ( hgvt->sp_type == SP_VERTEX_HVERTEX ) {
			
      harray = (HGedArray *) malloc( hgvt->hgven * sizeof( HGedArray ) );
			
      n = hgvt->hgven;
      i = 0;
      for ( ve = hgvt->shgve; ve != (HGvted *) NULL; ve = ve->nxt ) {

	if ( ve->ed->sp_type == SP_EDGE_NORMAL ) {
	  harray[i++].ed = ve->ed;
	}

      }
      free_hgppdvertexedge( hgvt );
			
      /* store start and end (boundary) edges */
      (void) create_hgvted( hgvt, hgvt->startedge );
      (void) create_hgvted( hgvt, hgvt->endedge );
			
      for ( i = 0; i < n - 2; ++i ) {
	ed = harray[i].ed;
	if ( ed->sv == hgvt ) v = ed->ev;
	else                  v = ed->sv;
	ve = find_right_hgvted( v, hgvt );
				
	InsertHGvted( hgvt, ve, ed );
				
      }
      free( harray );
    }
  }
}

HGvted *find_right_hgvted( HGvt *v, HGvt *hgvt )
{
  HGvted *ve;
  HGvt *sv, *ev;
	
  for ( ve = hgvt->shgve; ve != (HGvted *) NULL; ve = ve->nxt ) {
    if ( ve->ed->sv == hgvt ) {
      sv = ve->ed->sv;
      ev = ve->ed->ev;
    } else {
      sv = ve->ed->ev;
      ev = ve->ed->sv;
    }
    /*     if ( FALSE == isLeftSide( &(sv->uvw), &(ev->uvw), &(v->uvw) ) ) { */
    if ( FALSE == isHGvtLeftSide( sv, ev, v ) ) {
      return ve;
    }
  }
  return hgvt->ehgve;
}
/***********************************/

void mhgfc_create_mhgsf( HGfc *hgfc )
{
  for ( HGvt *hgvt = hgfc->shgvt; hgvt != (HGvt *) NULL; hgvt = hgvt->nxt ) 
    HGfcMakeHGsfFromHGvt( hgvt, hgfc );
}

/************************************************************************ */

/* vt->mvt は基本的には必要ない ? */
void mhgfc_to_gppd ( HGfc *mhgfc, Sppd *gppd )
{
  HGvt *hgvt;
  HGsf *hgsf;
  HGhe *hghe;
  Spvt *mvt;
  Spfc *mfc;
  Sphe *mhe;
  Sped *ed, *ned;
	
  for ( hgvt = mhgfc->shgvt; hgvt != (HGvt *) NULL; hgvt = hgvt->nxt ) {
		
    if ( hgvt->sp_type == SP_VERTEX_NORMAL ) {
      mvt = create_ppdvertex( gppd );
      hgvt->vt = mvt;
      mvt->bpso = gppd->spso;
      mvt->sp_type = SP_VERTEX_NORMAL;
      mvt->from = hgvt->from;
    }
  }
	
  for ( hgsf = mhgfc->shgsf; hgsf != (HGsf *) NULL; hgsf = hgsf->nxt ) {
		
    mfc = create_ppdface( gppd );
    mfc->bpso = gppd->spso;
    mfc->bppt = gppd->sppt;
		
    hghe = hgsf->shghe;
    do {
      mhe = create_ppdhalfedge( mfc );
      mhe->vt = hghe->vt->vt;
    } while ( (hghe = hghe->nxt) != hgsf->shghe );
		
  }
	
  /* free edges (not needed) */
  for ( ed = gppd->sped; ed != (Sped *) NULL; ed = ned ) {
    ned = ed->nxt;
    free_ppdedge( ed, gppd );
  }
	
}
