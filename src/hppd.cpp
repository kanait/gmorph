//
// hppd.cpp
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "hppd.h"
#include "ppd.h"
#include "ppdloop.h"
#include "ppdedge.h"
#include "hgppd.h"
#include "sellist.h"
#include "veclib.h"

/******************************************************************
                       HPpd functions 
******************************************************************/

HPpd *create_hppd(void)
{
  HPpd *ppd;
  
  if ((ppd = (HPpd *) malloc(sizeof(HPpd))) == (HPpd *) NULL) {
    return (HPpd *) NULL;
  }
  
  /* face */
  ppd->fn   = 0;
  ppd->fid  = 0;
  ppd->shfc = (HFace *) NULL;
  ppd->ehfc = (HFace *) NULL;
  
  /* vertex */
  ppd->vn   = 0;
  ppd->vid  = 0;
  ppd->shvt = (HVertex *) NULL;
  ppd->ehvt = (HVertex *) NULL;
  
  /* edge */
  ppd->en   = 0;
  ppd->eid  = 0;
  ppd->shed = (HEdge *) NULL;
  ppd->ehed = (HEdge *) NULL;

  /* for grouping */
  ppd->hgppd1 = (HGppd *) NULL;
  ppd->hgppd2 = (HGppd *) NULL;
  
  /* for morphing */
  ppd->gppd  = (Sppd *) NULL;
  
  return ppd;
}

void FreeHppdEdge ( HPpd *ppd )
{
  HEdge *edge, *nedge;
  
  /* edge */
  for (edge = ppd->shed; edge != (HEdge *) NULL; edge = nedge) {
    nedge = edge->nxt;
    free_hppdedge(edge, ppd);
  }
  ppd->en = 0;
  ppd->shed = ppd->ehed = (HEdge *) NULL;
}

void FreeHppdFace( HPpd *ppd )
{
  HFace *face, *nface;
  void free_hppdface(HFace *, HPpd *);

  /* face */
  for (face = ppd->shfc; face != (HFace *) NULL; face = nface) {
    nface = face->nxt;
    free_hppdface(face, ppd);
  }
  ppd->fn = 0;
  ppd->shfc = ppd->ehfc = (HFace *) NULL;
}

void free_hppd( HPpd *ppd )
{
  HFace *face, *nface;
  HVertex *vertex, *nvertex;
  HEdge *edge, *nedge;

  if ( ppd == (HPpd *) NULL ) return;

  if ( ppd->gppd != (Sppd *) NULL ) free_ppd( ppd->gppd );
  
  FreeHGppd( ppd );

  /* edge */
  for (edge = ppd->shed; edge != (HEdge *) NULL; edge = nedge) {
    nedge = edge->nxt;
    free_hppdedge( edge, ppd );
  }
  /* face */
  for (face = ppd->shfc; face != (HFace *) NULL; face = nface) {
    nface = face->nxt;
    free_hppdface( face, ppd );
  }
  /* vertex */
  for (vertex = ppd->shvt; vertex != (HVertex *) NULL; vertex = nvertex) {
    nvertex = vertex->nxt;
    free_hppdvertex( vertex, ppd );
  }

  if ( ppd->ppd1 != (Sppd *) NULL ) free_ppd( ppd->ppd1 );
  if ( ppd->ppd2 != (Sppd *) NULL ) free_ppd( ppd->ppd2 );
  
  /* ppd */
  free( ppd );
}

void calc_hppdfnorm( HFace *hface  )
{
  HHalfedge *he;
  HVertex *hv1, *hv2, *hv3;
  Vec    vec1, vec2, vec3, vec4, vec5;

  he = hface->shhe;
  
  hv1 = he->vt;
  hv2 = he->nxt->vt;
  hv3 = he->nxt->nxt->vt;

  /* no.1 */
  vec1.x = hv1->vt1->vec.x;
  vec1.y = hv1->vt1->vec.y;
  vec1.z = hv1->vt1->vec.z;
  vec2.x = hv2->vt1->vec.x;
  vec2.y = hv2->vt1->vec.y;
  vec2.z = hv2->vt1->vec.z;
  vec3.x = hv3->vt1->vec.x;
  vec3.y = hv3->vt1->vec.y;
  vec3.z = hv3->vt1->vec.z;
  V3Sub( &vec2, &vec1, &vec4 );
  V3Sub( &vec3, &vec1, &vec5 );
  V3Cross( &vec4, &vec5, &(hface->nrm1) );
  V3Normalize( &(hface->nrm1) );

  /* no.2 */
  vec1.x = hv1->vt2->vec.x;
  vec1.y = hv1->vt2->vec.y;
  vec1.z = hv1->vt2->vec.z;
  vec2.x = hv2->vt2->vec.x;
  vec2.y = hv2->vt2->vec.y;
  vec2.z = hv2->vt2->vec.z;
  vec3.x = hv3->vt2->vec.x;
  vec3.y = hv3->vt2->vec.y;
  vec3.z = hv3->vt2->vec.z;
  V3Sub( &vec2, &vec1, &vec4 );
  V3Sub( &vec3, &vec1, &vec5 );
  V3Cross( &vec4, &vec5, &(hface->nrm2) );
  V3Normalize( &(hface->nrm2) );
}

/***************************************
  Vertex
****************************************/

/* vertex */
HVertex *create_hppdvertex(HPpd *ppd)
{
  HVertex *vt;

  vt = (HVertex *) malloc(sizeof(HVertex));

  vt->nxt = (HVertex *) NULL;
  if (ppd->shvt == (HVertex *) NULL) {
    vt->prv   = (HVertex *) NULL;
    ppd->ehvt = ppd->shvt = vt;
  } else {
    vt->prv   = ppd->ehvt;
    ppd->ehvt = ppd->ehvt->nxt = vt;
  }

  vt->vt1 = (Spvt *) NULL;
  vt->vt2 = (Spvt *) NULL;

  vt->col = PNTGREEN;
  vt->no  = ppd->vid;
  vt->sid = SMDNULL;

  vt->atr = VTXINTERNAL;
  
  ++( ppd->vn );
  ++( ppd->vid );

  return vt;
}

HVertex *list_hppdvertex(HPpd *ppd, Id id)
{
  HVertex *vt;
  
  for (vt = ppd->shvt; vt != (HVertex *) NULL; vt = vt->nxt) {
    if (vt->no == id) return vt;
  }
  return (HVertex *) NULL;
}

void free_hppdvertex(HVertex *vt, HPpd *ppd)
{
  
  if (vt == (HVertex *) NULL) return;
  
  if (ppd->shvt == vt) {
    if ((ppd->shvt = vt->nxt) != (HVertex *) NULL)
      vt->nxt->prv = (HVertex *) NULL;
    else {
      ppd->ehvt = (HVertex *) NULL;
    }
  } else if (ppd->ehvt == vt) {
    vt->prv->nxt = (HVertex *) NULL;
    ppd->ehvt = vt->prv;
  } else {
    vt->prv->nxt = vt->nxt;
    vt->nxt->prv = vt->prv;
  }

  free(vt);
  --( ppd->vn );
}

/***************************************
  Edge
****************************************/

HEdge *create_hppdedge( HPpd *ppd )
{
  HEdge *ed;

  ed = (HEdge *) malloc(sizeof(HEdge));

  ed->nxt = (HEdge *) NULL;
  if (ppd->shed == (HEdge *) NULL) {
    ed->prv   = (HEdge *) NULL;
    ppd->ehed = ppd->shed = ed;
  } else {
    ed->prv   = ppd->ehed;
    ppd->ehed = ppd->ehed->nxt = ed;
  }

  ed->evn = 0;
  ed->sedvt = ed->eedvt = (Hedvt *) NULL;
  
  ed->sv  = (HVertex *) NULL;
  ed->ev  = (HVertex *) NULL;

  ed->lp1 = (Splp *) NULL;
  ed->lp2 = (Splp *) NULL;
  ed->mlp = (Splp *) NULL;
  
  ed->rf  = (HFace *) NULL;
  ed->lf  = (HFace *) NULL;

  ed->col = EDGEWHITE;
  ed->atr = EDGEINTERNAL;

  ed->no  = ppd->eid;

  ++( ppd->en );
  ++( ppd->eid );
  
  return ed;
}

HEdge *find_hppdedge( HVertex *shvt, HVertex *ehvt, HPpd *hppd )
{
  HEdge *hed;
  
  if ( shvt == (HVertex *) NULL ) return (HEdge *) NULL;
  if ( ehvt == (HVertex *) NULL ) return (HEdge *) NULL;
  
  for ( hed = hppd->shed; hed != (HEdge *) NULL; hed = hed->nxt ) {
    
    if ( (shvt->no == hed->sv->no) && (ehvt->no == hed->ev->no) )
      return hed;
    if ( (ehvt->no == hed->sv->no) && (shvt->no == hed->ev->no) )
      return hed;

  }
  return (HEdge *) NULL;
}
  
HEdge *find_hppdedge_from_spvt( Spvt *sv, Spvt *ev, ScreenAtr *screen, HPpd *hppd )
{
  HEdge *hed;
  Spvt *ppdsv, *ppdev;

  if ( hppd == NULL ) return (HEdge *) NULL;
  if ( sv == (Spvt *) NULL ) return (HEdge *) NULL;
  if ( ev == (Spvt *) NULL ) return (HEdge *) NULL;
  
  for ( hed = hppd->shed; hed != (HEdge *) NULL; hed = hed->nxt ) {

    ppdsv = ( screen->no == SCREEN_SRC ) ? hed->sv->vt1 : hed->sv->vt2;
    ppdev = ( screen->no == SCREEN_SRC ) ? hed->ev->vt1 : hed->ev->vt2;
    
    if ( (ppdsv == sv) && (ppdev == ev) ) return hed;
    if ( (ppdsv == ev) && (ppdev == sv) ) return hed;

  }
  return (HEdge *) NULL;
}
  
void free_hppdedge( HEdge *ed, HPpd *ppd )
{
  if (ed == (HEdge *) NULL) return;

  free_hppdedgevertex( ed );

  /* delete shortest-path */
  free_splp( ed->lp1 );
  free_splp( ed->lp2 );
  
  if (ppd->shed == ed) {
    if ((ppd->shed = ed->nxt) != (HEdge *) NULL)
      ed->nxt->prv = (HEdge *) NULL;
    else {
      ppd->ehed = (HEdge *) NULL;
    }
  } else if (ppd->ehed == ed) {
    ed->prv->nxt = (HEdge *) NULL;
    ppd->ehed = ed->prv;
  } else {
    ed->prv->nxt = ed->nxt;
    ed->nxt->prv = ed->prv;
  }

  free(ed);
  --( ppd->en );
}

/*
  Edge -> Vertex 
  for hppd_to_gppd (vt is a gppd's vertex)
*/

Hedvt *create_hedvt( HEdge *edge, Spvt *vt )
{
  Hedvt *ev;

  if (vt == (Spvt *) NULL) return (Hedvt *) NULL;
  
  ev = (Hedvt *) malloc(sizeof(Hedvt));

  ev->nxt = (Hedvt *) NULL;
  if (edge->sedvt == (Hedvt *) NULL) {
    ev->prv       = (Hedvt *) NULL;
    edge->eedvt = edge->sedvt = ev;
  } else {
    ev->prv       = edge->eedvt;
    edge->eedvt = edge->eedvt->nxt = ev;
  }

  /* vertex */
  ev->vt = vt;
  ev->val = 0.0;
  
  ++(edge->evn);
  
  return ev;
}

Hedvt *insert_hedvt( HEdge *hed, Spvt *vt, double val )
{
  Hedvt   *ev, *nev;
  
  /* first */
  if (hed->sedvt == (Hedvt *) NULL) {
    ev = create_hedvt( hed, vt );
    ev->val = val;
    return ev;
  }
  
  /* calc angle */
  ev    = hed->sedvt;
  while ((ev != (Hedvt *) NULL) && (val > ev->val)) {
    ev = ev->nxt;
  }

  /* last */
  if (ev == (Hedvt *) NULL) {
    ev = create_hedvt( hed, vt );
    ev->val = val;
    return ev;
  } 

  nev = (Hedvt *) malloc(sizeof(Hedvt));

  nev->prv = ev->prv;
  nev->nxt = ev;
  if (ev->prv != (Hedvt *) NULL) 
    ev->prv->nxt = nev;
  ev->prv = nev;
  if (hed->sedvt == ev) hed->sedvt = nev;

  nev->vt = vt;
  nev->val = val;

  ++( hed->evn );

  return nev;
}

void free_hppdedgevertex( HEdge *ed )
{
  Hedvt *ev, *evnxt;

  for (ev = ed->sedvt; ev != (Hedvt *) NULL; ev = evnxt) {
    evnxt = ev->nxt;
    free_hedvt( ev, ed );
    
  }
  ed->evn = 0;
  ed->sedvt = ed->eedvt = (Hedvt *) NULL;
}

void free_hedvt( Hedvt *ev, HEdge *ed )
{
  if (ev == (Hedvt *) NULL) return;

  ev->vt = (Spvt *) NULL;
  
  if (ed->sedvt == ev) {
    if ((ed->sedvt = ev->nxt) != (Hedvt *) NULL)
      ev->nxt->prv = (Hedvt *) NULL;
    else {
      ed->eedvt = (Hedvt *) NULL;
    }
  } else if (ed->eedvt == ev) {
    ev->prv->nxt = (Hedvt *) NULL;
    ed->eedvt = ev->prv;
  } else {
    ev->prv->nxt = ev->nxt;
    ev->nxt->prv = ev->prv;
  }
  free(ev);
  --( ed->evn );
}

/***************************************
  Face
****************************************/

/* face */
HFace *create_hppdface( HPpd *ppd )
{
  HFace *fc;

  fc = (HFace *) malloc(sizeof(HFace));
  
  fc->nxt = (HFace *) NULL;

  if (ppd->shfc == (HFace *) NULL) {
    fc->prv = (HFace *) NULL;
    ppd->ehfc = ppd->shfc = fc;
  } else {
    fc->prv   = ppd->ehfc;
    ppd->ehfc = ppd->ehfc->nxt = fc;
  }

  fc->hen   = 0;
  fc->shhe  = (HHalfedge *) NULL;
  fc->no    = ppd->fid;
  fc->col   = FACEBLUE;

  /* hgfc */
  fc->hgfc1 = (HGfc *) NULL;
  fc->hgfc2 = (HGfc *) NULL;
  fc->mhgfc = (HGfc *) NULL;
  
  /* hloop */
  fc->hloop = (HLoop *) NULL;
  
  fc->col = FACEBLUE;

  ++( ppd->fn );
  ++( ppd->fid );

  return fc;
}

HFace *another_hface( HEdge *ed, HFace *fc )
{
  if ( ed == (HEdge *) NULL ) return (HFace *) NULL;
  if ( fc == (HFace *) NULL ) return (HFace *) NULL;

  if ( ed->rf == fc ) return ed->lf;
  else return ed->rf;
}

HFace *list_hppdface( HPpd *ppd, Id id )
{
  HFace *fc;

  if ( id == SMDNULL ) 
    return (HFace *) NULL;
  
  for ( fc = ppd->shfc; fc != (HFace *) NULL; fc = fc->nxt ) {
    if (fc->no == id) return fc;
  }
  return (HFace *) NULL;
}

int find_hppdface_edge_links( HFace *hfc, HEdge *hed )
{
  HHalfedge *he;
  HVertex *vt, *nvt;
  
  he = hfc->shhe;

  do {
    vt  = he->vt;
    nvt = he->nxt->vt;

    if ( (hed->sv == vt) && (hed->ev == nvt ) ) {
      he->hed = hed;
      /* in order */
      return SMD_OFF;
    }
    if ( (hed->ev == vt) && (hed->sv == nvt ) ) {
      he->hed = hed;
      /* reverse */
      return SMD_ON;
    }
  } while ( (he = he->nxt) != hfc->shhe );

  // ‚±‚±‚Ü‚Å‚­‚é‚Æ‚ ‚â‚µ‚¢D
  return SMD_ON;
}
    
void free_hppdface( HFace *fc, HPpd *ppd )
{
  HHalfedge *he;
  
  if (fc == (HFace *) NULL) return;

  free_hgfc( fc->mhgfc );
  
  if ( fc->hloop != (HLoop *) NULL ) {
    free_splp( fc->hloop->lp1 );
    free_splp( fc->hloop->lp2 );
    free( fc->hloop );
  }
    
  /* free halfedge */
  he = fc->shhe;
  while (he != (HHalfedge *) NULL) {
    he = free_hppdhalfedge(he, fc);
  }
  
  if (ppd->shfc == fc) {
    if ((ppd->shfc = fc->nxt) != (HFace *) NULL)
      fc->nxt->prv = (HFace *) NULL;
    else {
      ppd->ehfc = (HFace *) NULL;
    }
  } else if (ppd->ehfc == fc) {
    fc->prv->nxt = (HFace *) NULL;
    ppd->ehfc = fc->prv;
    
  } else {
    fc->prv->nxt = fc->nxt;
    fc->nxt->prv = fc->prv;
  }

/*   free(fc->nrm); */
  free(fc);
  --( ppd->fn );
}

/* halfedge */
HHalfedge *create_hppdhalfedge(HFace *fc)
{
  HHalfedge *he;

  he = (HHalfedge *) malloc(sizeof(HHalfedge));
  
  if (fc->shhe == (HHalfedge *) NULL) {	/* first */
    fc->shhe = he;
    he->prv  = he;
    he->nxt  = he;
  } else {
    he->prv  = fc->shhe->prv;
    he->nxt  = fc->shhe;
    fc->shhe->prv->nxt = he;
    fc->shhe->prv = he;
  }
  /* id */
  he->no = fc->hen;
  /* start vertex */
  he->vt  = (HVertex *) NULL;

  /* links to hedge */
  he->hed = (HEdge *) NULL;
  
  ++( fc->hen );

  return he;
}

HHalfedge *free_hppdhalfedge(HHalfedge *he, HFace *face)
{
  HHalfedge *newhe;
  
  if (he->nxt == he) {
    free(he);
    --(face->hen);
    return (HHalfedge *) NULL;
  } else {
    newhe = he->nxt;
    he->prv->nxt = he->nxt;
    he->nxt->prv = he->prv;
    free(he);
    --(face->hen);
    return newhe;
  }
}

void calc_hppd_boundary( HPpd *ppd )
{
  HEdge *e;
  
  for ( e = ppd->shed; e != (HEdge *) NULL; e = e->nxt ) {

    if ( (e->lf == (HFace *) NULL) || (e->rf == (HFace *) NULL) ) {
      e->atr     = EDGEBOUNDARY;
      e->sv->atr = VTXEXTERNAL;
      e->ev->atr = VTXEXTERNAL;
    } else {
      e->atr = EDGEINTERNAL;
    }
    
  }
}

#define LP_START 0
#define LP_END   1

int lp_start_end( Splp *lp, Spvt *vt )
{
  if ( lp->splv->vt == vt ) return LP_START;
  else return LP_END;
}

void create_hloop( HFace *hfc, HPpd *hppd )
{
  int i;
  HLoop *hloop;
  Splp *nlp, *lp;
  Spvt *sv;
  Splv  *nlv, *lv, *lprv;
  Sple  *nle;
  HHalfedge *he;
  HVertex *hvt;
  HEdge   *hed;
  Sped    *ed;
  
  hloop = hfc->hloop = (HLoop *) malloc( sizeof(HLoop) );
  
  for ( i = 0; i < 2; ++i ) {

    nlp = create_splp();
    nlp->type = HLOOP;
    
    /* initialize */
    if ( !i ) hloop->lp1 = nlp; else hloop->lp2 = nlp;
    
    he = hfc->shhe;
    do {
      
      hvt = he->vt;
      sv = ( !i ) ? hvt->vt1 : hvt->vt2;
      hed = he->hed;
      lp = ( !i ) ? hed->lp1 : hed->lp2;

      if ( lp_start_end( lp, sv ) == LP_START ) {

	lv = lp->splv;
	while ( lv != lp->eplv ) {
	  
	  /* create loopvertex */
	  nlv = create_ppdloopvertex( nlp );
	  nlv->vt = lv->vt;

	  lprv = lv;
	  lv   = lv->nxt;
	  
	  /* create loopedge */
	  ed = (Sped *) NULL;
	  if ( (ed = find_ppdedge( lprv->vt, lv->vt )) != (Sped *) NULL ) {
	    nle = create_ppdloopedge( nlp );
	    nle->ed = ed;
	  }
	}
	  
      } else {
	
	lv = lp->eplv;
	while ( lv != lp->splv ) {

	  /* create loopvertex */
	  nlv = create_ppdloopvertex( nlp );
	  nlv->vt = lv->vt;

	  lprv = lv;
	  lv   = lv->prv;
	  
	  /* create loopedge */
	  ed = (Sped *) NULL;
	  if ( (ed = find_ppdedge( lprv->vt, lv->vt )) != (Sped *) NULL ) {
	    nle = create_ppdloopedge( nlp );
	    nle->ed = ed;
	  }
	  
	}
	  
      }
    } while ( (he = he->nxt) != hfc->shhe );

  }
}

