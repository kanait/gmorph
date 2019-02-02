//
// sellist.h
// Shortest path functions (SGraph version) 
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

//#include <unistd.h>

#include <math.h>
#include "smd.h"
#include "sgraph.h"
#include "sgpaths.h"
#include "ppdvertex.h"
#include "ppdedge.h"
#include "ppdloop.h"
#include "veclib.h"

/* make shortest-path using SGraph */
void SGShortestPathsCreate( HPpd *hppd )
{
	HEdge  *hed;
	Sppd   *ppd;
	SGraph *sg;
	Spvt   *sv, *ev;
	
	/* initialize */
	/* for calculate shortest-paths */
	
	ppd = hppd->ppd1;
	sg  = initialize_sgraph( ppd );
	for ( hed = hppd->shed; hed != (HEdge *) NULL; hed = hed->nxt ) {
		sv = hed->sv->vt1;
		ev = hed->ev->vt1;
		hed->lp1 = SGShortestPath( sg, ppd, sv, ev );
		hed->lp1->hed = hed;
	}
	free_sgraph( sg );
	
	ppd = hppd->ppd2;
	sg  = initialize_sgraph( ppd );
	for ( hed = hppd->shed; hed != (HEdge *) NULL; hed = hed->nxt ) {
		sv = hed->sv->vt2;
		ev = hed->ev->vt2;
		hed->lp2 = SGShortestPath( sg, ppd, sv, ev );
		hed->lp2->hed = hed;
	}
	free_sgraph( sg );
	
}

Splp *SGShortestPath( SGraph *sg, Sppd *ppd, Spvt *ppdsv, Spvt *ppdev )
{
	Splp  *lp;
	SGvt  *find_sgvt_from_spvt( SGraph *, Spvt * );
	Splp  *ShortestPath_Boundary( Sppd *, Spvt *, Spvt * );
	Splp  *CalcShortestPath( SGraph *, Sppd * );
	
	if ( (ppdsv->atr == VTXEXTERNAL) && (ppdev->atr == VTXEXTERNAL) ) {
		
		lp = ShortestPath_Boundary( ppd, ppdsv, ppdev );
		
	} else {
		
		sg->src  = find_sgvt_from_spvt( sg, ppdsv );
		sg->dist = find_sgvt_from_spvt( sg, ppdev );
		
		if ( (sg->src == NULL) || (sg->dist == NULL) ) {
			return NULL;
		}
		
		lp = CalcShortestPath( sg, ppd );
		
	}
	
	return lp;
}

Splp *CalcShortestPath( SGraph *sg, Sppd *ppd )
{
	int    i, iter;
	BOOL isCalculated;
	SGraph *org_sg, *new_sg;
	SGlp   *org_lp, *tmp_lp;
	Splp   *lp;
	
	i = 0;
	iter = 20;
	org_sg = sg;
	org_lp = NULL;
	new_sg = NULL;
	tmp_lp = NULL;
	isCalculated = FALSE;
	
	while ( (i < iter) && (isCalculated == FALSE) ) {
		
		/* STEP1 */
		if ( org_sg != sg ) {
			add_vertices_edges_sgraph( org_sg );
		}
		/* STEP2 */
		tmp_lp = ShortestPath_Dijkstra_SGraph( org_sg, org_sg->src, org_sg->dist );
		
		/* STEP3 */
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
	}
	
	/* create a new shortest-path loop */
	lp = sglp_to_splp( org_sg->lp, ppd );
	
	free_sgraph( org_sg );
	
	return lp;
}

Splp *sglp_to_splp( SGlp *sglp, Sppd *ppd )
{
	BOOL isVertexDeleted;
	Splp *lp;
	Spvt *ppddist, *ppdsv, *ppdev, *ppdvt;
	Splv *ppdlv;
	Sped *ppded;
	SGvt *sgsrc, *sgdist, *sgvt;
	SGed *sged, *next_sged;
	SGlpvt *lv, *next_lv;
	
	if ( sglp == NULL ) return NULL;
	
	lp = create_splp();
	lp->type  = SHORTESTPATH;
	
	/* starts from distination vertex */
	
	sgsrc  = sglp->elpvt->vt; 
	sgdist = sglp->slpvt->vt; ppddist = sgdist->spvt;
	sgvt = sgsrc;
	sged = NULL;
	
	lv = sglp->elpvt;
	next_lv = lv;
	
	while ( next_lv != sglp->slpvt ) {
		
		isVertexDeleted = FALSE;
		next_lv   = lv->prv;
		next_sged = find_sged( lv->vt, next_lv->vt );
		
		if ( sged != NULL ) {
			if ( ( sged->sped != NULL ) && ( next_sged->sped != NULL ) &&
				( sged->sped == next_sged->sped ) ) {
				isVertexDeleted = TRUE;
			}
		}
		
		if ( isVertexDeleted == FALSE ) {
		/*
        ppdloopvertex is created.
		If sgvt doesn't have a ppdvertex, ppdvertex is also created.
			*/
			sgvt = lv->vt;
			if ( sgvt->spvt == NULL ) {
				ppdvt = create_ppdvertex( ppd );
				ppdvt->vec.x = sgvt->vec.x;
				ppdvt->vec.y = sgvt->vec.y;
				ppdvt->vec.z = sgvt->vec.z;
				ppdvt->type = VERTEX_ADDED;
				ppdvt->bpso = ppd->spso;
				ppdvt->sp_type = SP_VERTEX_STEINER;
				/* if sgvt has spvt, sgvt always has sged. */
				ppdvt->sp_ed  = sgvt->sped;
				ppdvt->sp_val = ( V3DistanceBetween2Points( &(ppdvt->vec),
					&(ppdvt->sp_ed->sv->vec) )
					/ ppdvt->sp_ed->length );
				
			} else {
				ppdvt = sgvt->spvt;
			}
			
			ppdlv = create_ppdloopvertex( lp );
			ppdlv->vt = ppdvt;
			++( ppdvt->spn );
			
			/* change vt->sp_type */
			if ( ppdvt != ppddist ) {
				ppdvt->sp_type = SP_VERTEX_BOUNDARY;
				/* for grouping */
				ppdvt->lp = lp;
			}
			
		}
		
		lv = next_lv;
		sged = next_sged;
		
	}
	
	/* include a last vertex(src) */
	ppdvt = ppddist;
	ppdlv = create_ppdloopvertex( lp );
	ppdlv->vt = ppdvt; ++( ppdvt->spn );
	
	ppdlv = lp->splv;
	while ( ppdlv != lp->eplv ) {
		
		ppdsv = ppdlv->vt;
		ppdev = ppdlv->nxt->vt;
		
		/*
		If there is no ppdedge between two sgvts, ppdedge is also created.
		*/
		if ( (ppded = find_ppdedge( ppdsv, ppdev )) == (Sped *) NULL ) {
			ppded = create_ppdedge( ppd );
			ppded->sv = ppdsv;
			ppded->ev = ppdev;
			ppded->type = EDGE_ADDED;
			(void) create_vtxed( ppdsv, ppded );
			(void) create_vtxed( ppdev, ppded );
		}
		ppded->sp_type = SP_EDGE_BOUNDARY;
		
		ppdlv = ppdlv->nxt;
	}
	
	return lp;
}

Splp *ShortestPath_Boundary( Sppd *ppd, Spvt *src, Spvt *dist )
{
  Sped *ed;
  Spvt *pvt;
  Splp *newlp, *olp, *newnewlp;
  Splv *lv, *newlv, *slv, *tlv;
  
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
         

