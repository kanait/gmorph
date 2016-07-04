/* Copyright (c) 1997-1998 Takashi Kanai; All rights reserved. */

#include "cinc.h"
#include "motif.h"
#include "gldef.h"
#include "smd.h"

#include "Progress.h"

/* Motif functions */
void makeshortestpathcb( Widget w, XtPointer cld, XtPointer *cad )
{
  HPpd *hppd;
  void clear_paths( HPpd * );
  void make_shortest_path( HPpd * );
  
  if ( (hppd = swin->hppd) == (HPpd *) NULL ) {
    return;
  }
  clear_paths( hppd );

  /* make shortest path and make hloop */
  displayinfo("calculate shortest-path... \n");
  make_shortest_path( hppd );
  displayinfo("done. \n");
}

void clearshortestpathcb( Widget w, XtPointer cld, XtPointer *cad )
{
  HPpd *hppd;
  void clear_paths( HPpd * );
  
  if ( (hppd = swin->hppd) == (HPpd *) NULL ) {
    return;
  }
  clear_paths( hppd );
}

/* make shortest-path */
void make_shortest_path( HPpd *hppd )
{
  int   cnt, i;
  double dcnt;
  Sped  *ed;
  HEdge *hed;
  HFace *hfc;
  Sppd  *ppd;
  Splp  *ShortestPath_Dijkstra( Sppd *, Spvt *, Spvt * );
  Splp  *ShortestPath_Boundary( Sppd *, Spvt *, Spvt * );
  void  initialize_shortestpath( Sppd * );
  void  exit_shortestpath( Sppd * );
  void  time_start(void);
  void  time_stop(void);
  /* initialize */
  /* for calculate shortest-paths */

  display("sublength = %g\n", swin->sublength);
  initialize_shortestpath( hppd->ppd1 );
  initialize_shortestpath( hppd->ppd2 );
  
  display("number of hedge: %d\n", hppd->en );
  time_start();
  ProgressSetValue( 0 );
  
  for ( i = 0, hed = hppd->shed; hed != (HEdge *) NULL; hed = hed->nxt, ++i ) {

    dcnt = (double) i / (double) hppd->en * 100.0;
    cnt = (int) dcnt;
    ProgressSetValue( cnt );
    
    if ( (hed->rf == (HFace *) NULL) || (hed->lf == (HFace *) NULL) ) {
      hed->atr = EDGEBOUNDARY;
    }
    display("calc: hedge %d/%d... ", hed->no+1, hppd->en);
    if ( hed->atr != EDGEBOUNDARY ) {
      display("normal ");
      hed->lp1 = ShortestPath_Dijkstra( hppd->ppd1, hed->sv->vt1, hed->ev->vt1 );
      hed->lp1->hed = hed;
      hed->lp2 = ShortestPath_Dijkstra( hppd->ppd2, hed->sv->vt2, hed->ev->vt2 );
      hed->lp2->hed = hed;
    } else {
      display("boundary ");
      hed->lp1 = ShortestPath_Boundary( hppd->ppd1, hed->sv->vt1, hed->ev->vt1 );
      hed->lp1->hed = hed;
      hed->lp2 = ShortestPath_Boundary( hppd->ppd2, hed->sv->vt2, hed->ev->vt2 );
      hed->lp2->hed = hed;
    }
    display("done.\n");
  }
  display("time:shortest-path\n");
  time_stop();
  
  exit_shortestpath( hppd->ppd1 );
  exit_shortestpath( hppd->ppd2 );
}

void initialize_shortestpath( Sppd *ppd )
{
  Spvt *vt;
  void  normalize_ppd( Sppd * );
  void  make_subgraph( Sppd * );
  void  edge_length( Sppd * );
 
  for ( vt = ppd->spvt; vt != (Spvt *) NULL; vt = vt->nxt ) {
    vt->spn = 0;
  }
  
  /* needed for calculating shortest paths */
  normalize_ppd( ppd );
  edge_length( ppd );
  make_subgraph( ppd );
}

void exit_shortestpath( Sppd *ppd )
{
  void  unnormalize_ppd( Sppd * );
  void  delete_subgraph( Sppd * );
  void  edge_length( Sppd * );
  
  delete_subgraph( ppd );
  unnormalize_ppd( ppd );
  edge_length( ppd );
}

Splp *ShortestPath_Dijkstra( Sppd *ppd, Spvt *src, Spvt *dist )
{
  int    i, j;
  int    num1, num2;
  Spvt   *vt, *avt, *min_tvt;
  Sped   *ed;
  Splp   *lp;
  PQHeap *pqh;
  PQCont *pqc;
  double min_dis, newlen;
  Vted   *vted;
  VtList *vtlist;
  PQHeap *create_pqheap(int);
  void   insert_pqcont(double, PQHeap *, Spvt *, Spvt *);
  void   deletemin_pqcont(PQHeap *);
  void   adjust_pqheap(Id, PQHeap *);
  Spvt   *another_vt(Sped *, Spvt *);
  Splp   *vtlist_to_ppdloop( VtList *, Spvt *, Spvt * );
  int    stepnumber_to_src( VtList *, Spvt *, Spvt * );
  void   free_pqheap ( PQHeap * );
  
  /* Spvt の初期化 */

/*   display("src %d dist %d\n", src->no, dist->no ); */
  for ( vt = ppd->spvt; vt != (Spvt *) NULL; vt = vt->nxt ) {
    vt->pqc = (PQCont *) NULL;
    vt->pq_type = EMPTY;
    if ( vt->no == src->no ) {
      vt->pq_type = DELETED;
    }
  }

  /* initialize priority queue */
  pqh    = create_pqheap( ppd->vn );
  vtlist = (VtList *) malloc( ppd->vn * sizeof(VtList) );
  vtlist[src->no].prv = src;
  vtlist[src->no].dis = 0.0;

  for ( vted = src->svted; vted != (Vted *) NULL; vted = vted->nxt ) {
    
    avt = another_vt( vted->ed, src );
/*     if ( avt == dist ) { */
/*       display("insert dist. ed %d length %g\n", vted->ed->no, vted->ed->length); */
/*     } */
    insert_pqcont( vted->ed->length, pqh, avt, src );
  }
  
  /* vtlist: S から 1 つのエッジで辿れるものしか値が入らない */
  
  for ( i = 0; i < ppd->vn - 1; ++i ) {
    /* min_tvt S に加える */
    min_dis = pqh->pqcont[0].distance;
    min_tvt = pqh->pqcont[0].tgt_vt;
/*     display("min_tvt %d\n", min_tvt->no ); */
    vtlist[ min_tvt->no ].prv = pqh->pqcont[0].prv_vt;
    vtlist[ min_tvt->no ].dis = min_dis;

    /* min_tvt をヒープから消去 */
    deletemin_pqcont( pqh );
    
    for ( vted = min_tvt->svted; vted != (Vted *) NULL; vted = vted->nxt ) {

      avt    = another_vt( vted->ed, min_tvt );
      newlen = min_dis + vted->ed->length;
      pqc    = avt->pqc;

/*       if ( avt == dist ) { */
/* 	display("************** %d **************** begin. \n", avt->no); */
/*       } */
      if ( (pqc == (PQCont *) NULL) && (avt->pq_type == EMPTY) ) {
	
/* 	if ( avt == dist ) { */
/* 	  display("insert dist. ed %d length %g\n", vted->ed->no,  */
/* 		  newlen); */
/* 	} */
	insert_pqcont( newlen, pqh, avt, min_tvt );
	
      } else if ( pqc != (PQCont *) NULL ) {

	/* updated. 97/08/28. modified from original dijkstra's algorithm. */
	if ( fabs( newlen - pqc->distance ) < SMDZEROEPS ) {

	  num1 = stepnumber_to_src( (VtList *) vtlist, pqc->prv_vt, src );
	  num2 = stepnumber_to_src( (VtList *) vtlist, min_tvt, src );

/* 	  if ( avt == dist ) { */
/* 	    display("(pqc->prv) %d = len %g num %d (min_tvt) %d len %g num %d\n", */
/* 		    pqc->prv_vt->no, pqc->distance, num1, */
/* 		    min_tvt->no, newlen, num2 ); */
/* 	  } */
	  
	  if ( num2 < num1 ) {

	    pqc->distance = newlen;
	    pqc->prv_vt   = min_tvt;
	  
	    adjust_pqheap( pqc->id, pqh );
	  }
	  
	} else {
	  
	  if ( newlen < pqc->distance ) {

/* 	    if ( avt == dist ) { */
/* 	      display("(pqc->prv) %d < len %g (min_tvt) %d len %g\n", */
/* 		      pqc->prv_vt->no, pqc->distance, */
/* 		      min_tvt->no, newlen ); */
/* 	    } */
	  
	    pqc->distance = newlen;
	    pqc->prv_vt   = min_tvt;
	  
	    adjust_pqheap( pqc->id, pqh );

	  }
	}
      }
/*       if ( avt == dist ) { */
/* 	display("************** %d **************** end.\n\n", avt->no); */
/*       } */
    }
  }

  /* VtList to Loop */
  lp = vtlist_to_ppdloop( (VtList *) vtlist, src, dist );
  
  free_pqheap( pqh );
  free( vtlist );

  return lp;
}

int stepnumber_to_src( VtList *vtlist, Spvt *start, Spvt *goal )
{
  int cnt = 0;
  Spvt *vt;

  vt = start; 

  while ( vt != goal ) {
    ++cnt;
    vt = vtlist[vt->no].prv;
  }
    
  return cnt;
}

Splp *vtlist_to_ppdloop( VtList *vtlist, Spvt *src, Spvt *dist )
{
  int  i, flag;
  Spvt *vt, *next_vt;
  Splv *lv;
  Splp *lp, *nlp;
  Sped *ed, *next_ed;
  Splp *create_splp( void );
  void free_splp( Splp * );
  Splp *reverse_ppdloop( Splp * );
  Splv *create_ppdloopvertex( Splp * );
  Sped *find_ppdedge( Spvt *, Spvt * );

  if ( vtlist == (VtList *) NULL ) return (Splp *) NULL;

  lp = create_splp();
  lp->type  = SHORTESTPATH;
  
  /* lp includes src and dist. */
  vt = dist;
  ed = NULL;
  next_vt = vt;

  while ( next_vt != src ) {

    flag = SMD_OFF;
    next_vt = vtlist[next_vt->no].prv;
    next_ed = find_ppdedge( vt, next_vt );

    if ( ed != NULL ) {
      if ( ( ed->org_ed != NULL ) && ( next_ed->org_ed != NULL ) &&
	   ( ed->org_ed == next_ed->org_ed ) ) {
	flag = SMD_ON;
	display("deleted.\n");
      }
    }

    if ( !flag ) {
      lv = create_ppdloopvertex( lp );
      lv->vt = vt; ++( vt->spn );
      /* change vt->sp_type */
      if ( vt != dist ) {
	vt->sp_type = SP_VERTEX_BOUNDARY;
	/* for grouping */
	vt->lp = lp;
      }
      if ( (ed = find_ppdedge( vt, next_vt )) != (Sped *) NULL ) {
	ed->sp_type = SP_EDGE_BOUNDARY;
      }

      vt = next_vt;
    }
    
    ed = next_ed;
    
  }
  
  /* include a last vertex(src) */
  vt = next_vt;
  lv = create_ppdloopvertex( lp );
  lv->vt = vt; ++( vt->spn );

  /* (dist -> src) -->> (src -> dist) */
  nlp = reverse_ppdloop( lp );
  free_splp( lp );
  
  return nlp;
}

Splp *reverse_ppdloop( Splp *lp )
{
  Splp *nlp;
  Splv *lv, *nlv;
  Sple *le, *nle;
  Splp *create_splp( void );
  Splv *create_ppdloopvertex( Splp * );
  Sple *create_ppdloopedge( Splp * );
  
  nlp = create_splp();
  nlp->type  = SHORTESTPATH;

  lv = lp->eplv;
  while (1) {
    
    nlv = create_ppdloopvertex( nlp );
    nlv->vt = lv->vt;

    if ( lv == lp->splv ) break;
    lv = lv->prv;

  }
  
/*   le = lp->eple; */
/*   while (1) { */
    
/*     nle = create_ppdloopedge( nlp ); */
/*     nle->ed = le->ed; */

/*     if ( le == lp->sple ) break; */
/*     le = le->prv; */

/*   } */
  
  return nlp;
}

void cancel_create_shortestpath( ScreenAtr *screen )
{
  void FreeSelectList( ScreenAtr * );
  
  FreeSelectList( screen );
}

void cancel_delete_shortestpath( ScreenAtr *screen )
{
  void FreeSelectList( ScreenAtr * );
  
  FreeSelectList( screen );
}
  
void clear_paths( HPpd *hppd )
{
  HVertex *hvt;
  HFace *hfc, *nhfc;
  void FreeHppdShortestPath( HPpd * );
  void FreeHppdFaceLoop( HPpd * );
  void clear_ppd( Sppd * );

  
  if ( hppd == (HPpd *) NULL ) return;

  FreeHppdShortestPath( hppd );
/*   FreeHppdFaceLoop( hppd ); */

  /* clear ppds */
  clear_ppd( hppd->ppd1 );
  clear_ppd( hppd->ppd2 );

  for ( hvt = hppd->shvt; hvt != (HVertex *) NULL; hvt = hvt->nxt ) {
    hvt->vt1->sp_type = SP_VERTEX_HVERTEX;
    hvt->vt2->sp_type = SP_VERTEX_HVERTEX;
  }
}
    
void FreeHppdShortestPath ( HPpd *ppd )
{
  HEdge *edge;
  void free_splp( Splp * );
  
  for ( edge = ppd->shed; edge != (HEdge *) NULL; edge = edge->nxt ) {
    free_splp( edge->lp1 ); edge->lp1 = (Splp *) NULL;
    free_splp( edge->lp2 ); edge->lp2 = (Splp *) NULL;
  }
}

void FreeHppdFaceLoop( HPpd *ppd )
{
  HFace *face;
  void free_splp( Splp * );

  for ( face = ppd->shfc; face != (HFace *) NULL; face = face->nxt ) {
    if ( face->hloop != (HLoop *) NULL ) {
      free_splp( face->hloop->lp1 );
      free_splp( face->hloop->lp2 );
      free( face->hloop ); face->hloop = (HLoop *) NULL;
    }
  }
}
  
/* make subgraph */
/*
   ・ Steiner 点の数の決定 
   - エッジの最大長さを決定 
   - デフォルトの m = 6 
   - 各エッジについての Steiner 点の数の決定 
   ・ subgraph の生成
*/

#define STEINER_POINT   5
#define SUB 0.01 /* for bunny-tiger */
/*#define SUB 0.005*/ /* for Delorian-Porsche */

void make_subgraph( Sppd *ppd )
{
  double al, be;
  int  num, i, num1;
  int  vn, en;
  Sped *ed, *e0, *e1, *e2, *new_ed;
  Spvt *vt, *v0, *v1, *v2;
  Spfc *fc;
  Edvt *edvt0, *edvt1, *edvt2;
  Sphe *he;
  double avr_length;
  int decide_steiner_number( double, double, int, double * );
  Edvt *create_edvtx( Sped *, Spvt * );
  Spvt *create_ppdvertex( Sppd * );
  Sped *create_ppdedge( Sppd * );
  Vted *create_vtxed( Spvt *, Sped * );
  double V3DistanceBetween2Points( Vec *, Vec * );
  void free_ppdedgevertex( Sped * );

  vn = en = 0;
  ppd->avr_edge_length = ppd->max_edge_length / (double) (STEINER_POINT + 1);
  
  /* create (1) steiner points (2) edge->vertex link (temporary) */

  for ( ed = ppd->sped; ed != (Sped *) NULL; ed = ed->nxt ) {
/*     num = ed->num_steiner_point */
/*       = decide_steiner_number( ed->length, ppd->avr_edge_length, */
/* 			       STEINER_POINT, &avr_length ); */
    num = ed->num_steiner_point = (int) (ed->length / swin->sublength);

/*     display("ed %d length %g num %d\n", ed->no, ed->length, num ); */
    
    /* start point */
    create_edvtx( ed, ed->sv );

    /* end point */

    num1 = num + 1;
    for ( i = 0; i < num; ++i ) {
      vt = create_ppdvertex( ppd );
      vt->type = VERTEX_ADDED;
      vt->bpso = ppd->spso;
      ++vn;

      /* information for steiner type */
      vt->sp_type = SP_VERTEX_STEINER;
      vt->sp_ed   = ed;

      al = (double) ( num - i ) / (double) num1;
      be = 1.0 - al;
      vt->sp_val = al;
      
      vt->vec.x = ed->sv->vec.x * al + ed->ev->vec.x * be;
      vt->vec.y = ed->sv->vec.y * al + ed->ev->vec.y * be;
      vt->vec.z = ed->sv->vec.z * al + ed->ev->vec.z * be;
      
      create_edvtx( ed, vt );
    }
    
    create_edvtx( ed, ed->ev );
  }

  /* create edge of subgraphs */
  
  for ( fc = ppd->spfc; fc != (Spfc *) NULL; fc = fc->nxt ) {

    /* create new edge for neighbor steiner points */
    he = fc->sphe;
    do {
      ed = he->ed;

      if ( (ed->num_steiner_point) && (ed->cal_subgraph != SMD_ON) ) {
	
	edvt0 = ed->sedvt;

	while ( edvt0->nxt != (Edvt *) NULL ) {

	  /* create new edge */
	  edvt1 = edvt0->nxt;
	  new_ed = create_ppdedge( ppd ); ++en;
	  new_ed->type = EDGE_ADDED;
	  new_ed->sv = edvt0->vt;
	  new_ed->ev = edvt1->vt;
	  new_ed->sp_type = SP_EDGE_STEINER;
	  /* it's original edge */
	  new_ed->org_ed  = ed;
	  (void) create_vtxed( edvt0->vt, new_ed );
	  (void) create_vtxed( edvt1->vt, new_ed );
	  new_ed->length = V3DistanceBetween2Points( &(new_ed->sv->vec),
						     &(new_ed->ev->vec) ) + 1.0e-05;
	  
	  edvt0 = edvt1;
	}

	ed->cal_subgraph = SMD_ON;
      }

      /* create new edge for steiner points in diffrent edges */
      e0 = he->ed;
      e1 = he->nxt->ed;
      if ( (e0->num_steiner_point) && (e1->num_steiner_point) ) {
	
	for ( edvt0 = e0->sedvt; edvt0 != (Edvt *) NULL;
	      edvt0 = edvt0->nxt ) {
	  if ( (edvt0 != e0->sedvt) && (edvt0 != e0->eedvt) ) {
	    
	    for ( edvt1 = e1->sedvt; edvt1 != (Edvt *) NULL;
		  edvt1 = edvt1->nxt ) {
	      if ( (edvt1 != e1->sedvt) && (edvt1 != e1->eedvt) ) {

		new_ed = create_ppdedge( ppd ); ++en;
		new_ed->sv = edvt0->vt;
		new_ed->ev = edvt1->vt;
		new_ed->type = EDGE_ADDED;
		new_ed->sp_type = SP_EDGE_STEINER;
		/* it's original edge */
		new_ed->org_ed  = NULL;
		(void) create_vtxed(edvt0->vt, new_ed);
		(void) create_vtxed(edvt1->vt, new_ed);
		new_ed->length = V3DistanceBetween2Points( &(new_ed->sv->vec),
							   &(new_ed->ev->vec) );

	      }
	    }
	  }
	}
      }

      
    } while( (he = he->nxt) != fc->sphe );
    

    /* for v0 */
    v0 = fc->sphe->vt;
    v1 = fc->sphe->nxt->vt;
    v2 = fc->sphe->prv->vt;
    e0 = fc->sphe->ed;
    e1 = fc->sphe->nxt->ed;
    e2 = fc->sphe->prv->ed;
    for ( edvt0 = e1->sedvt; edvt0 != (Edvt *) NULL; edvt0 = edvt0->nxt ) {
      
      if ( (edvt0->vt != v1) && (edvt0->vt != v2) ) {
	new_ed = create_ppdedge( ppd ); ++en;
	new_ed->sv = v0;
	new_ed->ev = edvt0->vt;
	new_ed->type = EDGE_ADDED;
	new_ed->sp_type = SP_EDGE_STEINER;
	/* it's original edge */
	new_ed->org_ed  = NULL;
	new_ed->length = V3DistanceBetween2Points( &(new_ed->sv->vec), &(new_ed->ev->vec) );
	(void) create_vtxed(v0, new_ed);
	(void) create_vtxed(edvt0->vt, new_ed);
	
      }
      
    }
    /* for v1 */
    for ( edvt0 = e2->sedvt; edvt0 != (Edvt *) NULL; edvt0 = edvt0->nxt ) {
      
      if ( (edvt0->vt != v2) && (edvt0->vt != v0) ) {
	new_ed = create_ppdedge( ppd ); ++en;
	new_ed->sv = v1;
	new_ed->ev = edvt0->vt;
	new_ed->type = EDGE_ADDED;
	new_ed->sp_type = SP_EDGE_STEINER;
	/* it's original edge */
	new_ed->org_ed  = NULL;
	new_ed->length = V3DistanceBetween2Points( &(new_ed->sv->vec), &(new_ed->ev->vec) );
	(void) create_vtxed(v1, new_ed);
	(void) create_vtxed(edvt0->vt, new_ed);
	
      }
      
    }
    /* for v2 */
    for ( edvt0 = e0->sedvt; edvt0 != (Edvt *) NULL; edvt0 = edvt0->nxt ) {
      
      if ( (edvt0->vt != v0) && (edvt0->vt != v1) ) {
	new_ed = create_ppdedge( ppd ); ++en;
	new_ed->sv = v2;
	new_ed->ev = edvt0->vt;
	new_ed->type = EDGE_ADDED;
	new_ed->sp_type = SP_EDGE_STEINER;
	/* it's original edge */
	new_ed->org_ed  = NULL;
	new_ed->length = V3DistanceBetween2Points( &(new_ed->sv->vec), &(new_ed->ev->vec) );
	(void) create_vtxed(v2, new_ed);
	(void) create_vtxed(edvt0->vt, new_ed);

      }
      
    }
  }

  /* free edge->vertex links */

  for ( ed = ppd->sped; ed != (Sped *) NULL; ed = ed->nxt ) {
    free_ppdedgevertex( ed );
  }

  display("subgraph created. vn %d en %d\n", vn, en );
  return;
}

int decide_steiner_number( double edlen, double interval, int num_steiner,
			   double *avr_length )
{
  int num, i;
  double   val, subval, sublen, tmpval;

  *avr_length = edlen;
  num = 0;
  subval = fabs( *avr_length - interval );
  
  for ( i = 2; i < num_steiner + 1; ++i ) {
    sublen = edlen / (double) i;

    if ( (tmpval = fabs ( sublen - interval )) < subval ) {
      *avr_length = sublen;
      subval      = tmpval;
      num         = i - 1;
    }
  }

  return num;
}

void delete_subgraph( Sppd *ppd )
{
  Spvt *vt, *nvt;
  Sped *ed, *ned;
  Vted *ve, *nve;
  void free_vtxed(Vted *, Spvt *);
  void free_ppdvertex( Spvt *, Sppd * );
  void free_ppdedge( Sped *, Sppd * );

  if ( ppd == (Sppd *) NULL ) return;
  
  /* delete vertices */
  for ( vt = ppd->spvt; vt != (Spvt *) NULL; vt = nvt ) {

    /* delete vertex-edge links */
    nvt = vt->nxt;
    nve = (Vted *) NULL;
    for ( ve = vt->svted; ve != (Vted *) NULL; ve = nve ) {

      nve = ve->nxt;
      if ( ve->ed->sp_type == SP_EDGE_STEINER ) {
	free_vtxed( ve, vt );
      }

    }
    if ( vt->sp_type == SP_VERTEX_STEINER ) {
      free_ppdvertex( vt, ppd );
    }
  }

  /* delete edges */
  for ( ed = ppd->sped; ed != (Sped *) NULL; ed = ned ) {
  
    ned = ed->nxt;
    if ( ed->sp_type == SP_EDGE_STEINER ) {
      free_ppdedge( ed, ppd );
    }
  }
}

Splp *ShortestPath_Boundary( Sppd *ppd, Spvt *src, Spvt *dist )
{
  Sped *ed;
  Spvt *pvt;
  Splp *newlp, *olp, *newnewlp;
  Splv *lv, *newlv, *slv, *tlv;
  Splp *find_ppdloop( Sppd *, Spvt * );
  Splp *create_splp( void );
  Splv *find_ppdloopvertex( Splp *, Spvt * );
  Splv *create_ppdloopvertex( Splp * );
  Sped *find_ppdedge( Spvt *, Spvt * );
  void free_splp( Splp * );
  Splp *reverse_ppdloop( Splp * );
  
  if ( (olp = find_ppdloop( ppd, dist )) == (Splp *) NULL )
    return (Splp *) NULL;
  
  if ( (slv = find_ppdloopvertex( olp, dist )) == (Splv *) NULL )
    return (Splp *) NULL;

  /* next direction */
  lv = slv;
  lv = lv->nxt;
  while (1) {
    if ( lv == (Splv *) NULL ) lv = olp->splv;
    if ( (lv->vt->sp_type == SP_VERTEX_HVERTEX) && (lv->vt != src) )
      break;
    if ( lv->vt == src ) {
      /* find */
      newlp = create_splp();
      newlp->type  = SHORTESTPATH;
      
      tlv = slv;
      newlv = create_ppdloopvertex( newlp );
      newlv->vt = tlv->vt; ++( newlv->vt->spn );
      
      pvt = tlv->vt; tlv = tlv->nxt;
      
      while (1) {
	if ( tlv == (Splv *) NULL ) tlv = olp->splv;
	
	newlv = create_ppdloopvertex( newlp );
	newlv->vt = tlv->vt; ++( newlv->vt->spn );

	ed = (Sped *) NULL;
	if ( (ed = find_ppdedge( pvt, tlv->vt )) != (Sped *) NULL ) {
	  ed->sp_type = SP_EDGE_BOUNDARY;
	}
	
	if ( tlv->vt == src ) {

	  /* a shortest-path is created */
	  if ( newlp->splv->vt == src ) {
	    return newlp;
	  } else {
	    newnewlp = reverse_ppdloop( newlp );
	    free_splp( newlp );
	    return newnewlp;
	  }
	  
	} else {
	  newlv->vt->sp_type = SP_VERTEX_BOUNDARY;
	}
	
	pvt = tlv->vt; tlv = tlv->nxt;
      }
    }
    lv = lv->nxt;
  }
  /* prev direction */
  lv = slv;
  lv = lv->prv;
  while (1) {
    if ( lv == (Splv *) NULL ) lv = olp->eplv;
    if ( (lv->vt->sp_type == SP_VERTEX_HVERTEX) && (lv->vt != src) )
      return (Splp *) NULL;
    if ( lv->vt == src ) {
      /* find */
      newlp = create_splp();
      newlp->type  = SHORTESTPATH;
      
      tlv = slv;
      newlv = create_ppdloopvertex( newlp );
      newlv->vt = tlv->vt; ++( newlv->vt->spn );

      pvt = tlv->vt; tlv = tlv->prv; 

      while (1) {
	
	if ( tlv == (Splv *) NULL ) tlv = olp->eplv;
	
	newlv = create_ppdloopvertex( newlp );
	newlv->vt = tlv->vt; ++( newlv->vt->spn );
	
	ed = (Sped *) NULL;
	if ( (ed = find_ppdedge( pvt, tlv->vt )) != (Sped *) NULL ) {
	  ed->sp_type = SP_EDGE_BOUNDARY;
	}
	
	if ( tlv->vt == src ) {
	  
	  /* a shortest-path is created */
	  if ( newlp->splv->vt == src ) {
	    return newlp;
	  } else {
	    newnewlp = reverse_ppdloop( newlp );
	    free_splp( newlp );
	    return newnewlp;
	  }
	  
	} else {
	  newlv->vt->sp_type = SP_VERTEX_BOUNDARY;
	}
	
	pvt = tlv->vt; tlv = tlv->prv; 
      }
    }
    lv = lv->prv;
  }
  return (Splp *) NULL;
}	
      
      
