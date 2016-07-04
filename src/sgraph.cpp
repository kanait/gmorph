/* Copyright (c) 1997-1998 by Takashi Kanai; All rights reserved. */

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
#include "sgprique.h"
#include "veclib.h"

/* SGraph functions */

SGraph *create_sgraph( void )
{
  SGraph *sg;
  
  sg = (SGraph *) malloc( sizeof(SGraph) );

  sg->sgvtn  = 0;
  sg->sgvtid = 0;
  sg->sgvt  = (SGvt *) NULL;
  sg->egvt  = (SGvt *) NULL;
  sg->sgedn  = 0;
  sg->sgedid = 0;
  sg->sged  = (SGed *) NULL;
  sg->eged  = (SGed *) NULL;
  sg->sgfcn  = 0;
  sg->sgfcid = 0;
  sg->sgfc  = (SGfc *) NULL;
  sg->egfc  = (SGfc *) NULL;

  sg->src = sg->dist = (SGvt *) NULL;
  sg->lp  = (SGlp *) NULL;
  
  return sg;
}

void free_sgraph( SGraph *sg )
{
  if ( sg == NULL ) return;

  sg->src  = NULL;
  sg->dist = NULL;
  if ( sg->lp != (SGlp *) NULL ) {
    free_sglp( sg->lp );
	sg->lp = NULL;
  }
  
  FreeSGEdge( sg );
  FreeSGFace( sg );
  FreeSGVertex( sg );

  free( sg );
}

/* SGvt functions */
SGvt *create_sgvt( SGraph *sg )
{
  SGvt *vt;

  vt = (SGvt *) malloc(sizeof(SGvt));

  vt->nxt = (SGvt *) NULL;
  if (sg->sgvt == (SGvt *) NULL) {
    vt->prv   = (SGvt *) NULL;
    sg->egvt = sg->sgvt = vt;
  } else {
    vt->prv   = sg->egvt;
    sg->egvt = sg->egvt->nxt = vt;
  }

  /* id */
  vt->no   = sg->sgvtid;
  vt->sid  = SMDNULL;
  /* type */
  vt->type = VERTEX_SPATH_ORIGINAL;

  /* vt - edge */
  vt->sgvtedn = 0;
  vt->svted = (SGvted *) NULL;
  vt->evted = (SGvted *) NULL;

  vt->spvt = (Spvt *) NULL;
  vt->sped = (Sped *) NULL;
  
  /* for shortest path */
  vt->pq_type = EMPTY;
  vt->pqc     = (SGPQCont *) NULL;
  
  ++( sg->sgvtn );
  ++( sg->sgvtid );

  return vt;
}

SGvt *CreateSGvtfromSGvt( SGraph *sg, SGvt *sgvt )
{
  SGvt *nsgvt;
  
  nsgvt = create_sgvt( sg );
  nsgvt->vec.x = sgvt->vec.x;
  nsgvt->vec.y = sgvt->vec.y;
  nsgvt->vec.z = sgvt->vec.z;
    
  nsgvt->type = sgvt->type;
  if ( nsgvt->type == VERTEX_SPATH_ORIGINAL ) {
    nsgvt->spvt = sgvt->spvt;
  } else {
    nsgvt->sped  = sgvt->sped;
  }

  return nsgvt;
}

void free_sgvt( SGvt *vt, SGraph *sg )
{
  void FreeSGVertexEdge( SGvt * );
  
  if (vt == (SGvt *) NULL) return;

  FreeSGVertexEdge( vt );
  
  if ( sg->sgvt == vt ) {
    if ( (sg->sgvt = vt->nxt) != (SGvt *) NULL )
      vt->nxt->prv = (SGvt *) NULL;
    else {
      sg->egvt = (SGvt *) NULL;
    }
  } else if (sg->egvt == vt) {
    vt->prv->nxt = (SGvt *) NULL;
    sg->egvt = vt->prv;
  } else {
    vt->prv->nxt = vt->nxt;
    vt->nxt->prv = vt->prv;
  }

  --( sg->sgvtn );
  free( vt );
}


SGvt *another_sgvt( SGed *ed, SGvt *vt )
{
  if ( ed->sv == vt ) return ed->ev;
  else return ed->sv;
}

SGvt *find_sgvt_from_spvt( SGraph *sg, Spvt *ppdvt )
{
  SGvt *vt;
  
  for ( vt = sg->sgvt; vt != (SGvt *) NULL; vt = vt->nxt ) {
    if ( vt->type == VERTEX_SPATH_ORIGINAL ) {
      if ( vt->spvt == ppdvt ) return vt;
    }
  }
  return (SGvt *) NULL;
}

SGvt *find_sgvt_from_spvt_number( SGraph *sg, int id )
{
  SGvt *vt;
  
  for ( vt = sg->sgvt; vt != (SGvt *) NULL; vt = vt->nxt ) {
    if ( vt->type == VERTEX_SPATH_ORIGINAL ) {
      if ( vt->spvt->no == id ) return vt;
    }
  }
  return (SGvt *) NULL;
}

SGvt *find_sgvt_from_sgfc( SGfc *fc, SGvt *vt )
{
  SGfcvt *fv;
  
  for ( fv = fc->sfcvt; fv != (SGfcvt *) NULL; fv = fv->nxt ) {
    if ( fv->vt == vt ) return vt;
  }
  return NULL;
}

void FreeSGVertex( SGraph *sg )
{
  SGvt *vt, *nvt;

  if ( sg == NULL ) return;
  
  for ( vt = sg->sgvt; vt != (SGvt *) NULL; vt = nvt ) {
    nvt = vt->nxt;
    free_sgvt( vt, sg );
  }
  sg->sgvtn = sg->sgvtid = 0;
  sg->sgvt = sg->egvt = (SGvt *) NULL;
}

/* SGvted functions */
SGvted *create_sgvted( SGvt *vt, SGed *ed )
{
  SGvted *ve;

  ve = (SGvted *) malloc( sizeof(SGvted) );

  ve->nxt = (SGvted *) NULL;
  if (vt->svted == (SGvted *) NULL) {
    ve->prv   = (SGvted *) NULL;
    vt->evted = vt->svted = ve;
  } else {
    ve->prv   = vt->evted;
    vt->evted = vt->evted->nxt = ve;
  }

  ve->ed = ed;
  
  ++( vt->sgvtedn );

  return ve;
}

void free_sgvted( SGvted *ve, SGvt *vt )
{
  if ( vt == (SGvt *) NULL ) return;
  if ( ve == (SGvted *) NULL ) return;

  if ( vt->svted == ve ) {
    if ( (vt->svted = ve->nxt) != (SGvted *) NULL )
      ve->nxt->prv = (SGvted *) NULL;
    else {
      vt->evted = (SGvted *) NULL;
    }
  } else if (vt->evted == ve) {
    ve->prv->nxt = (SGvted *) NULL;
    vt->evted = ve->prv;
  } else {
    ve->prv->nxt = ve->nxt;
    ve->nxt->prv = ve->prv;
  }

  --( vt->sgvtedn );
  free( ve );
}

void FreeSGvted( SGvt *vt, SGed *ed )
{
  SGvted *ve;
  void free_sgvted( SGvted *, SGvt * );

  if ( vt == NULL ) return;
  
  for ( ve = vt->svted; ve != (SGvted *) NULL; ve = ve->nxt ) {
    if ( ve->ed == ed ) {
      free_sgvted( ve, vt );
      return;
    }
  }
}

void FreeSGVertexEdge( SGvt *vt )
{
  SGvted *ve, *nve;

  if ( vt == NULL ) return;
  
  for ( ve = vt->svted; ve != (SGvted *) NULL; ve = nve ) {
    nve = ve->nxt;
    free_sgvted( ve, vt );
  }
  vt->sgvtedn = 0;
  vt->svted  = vt->evted = (SGvted *) NULL;
}
    
/* SGed functions */
SGed *create_sged( SGraph *sg )
{
  SGed *ed;

  ed = (SGed *) malloc(sizeof(SGed));

  ed->nxt = (SGed *) NULL;
  if (sg->sged == (SGed *) NULL) {
    ed->prv   = (SGed *) NULL;
    sg->eged = sg->sged = ed;
  } else {
    ed->prv   = sg->eged;
    sg->eged = sg->eged->nxt = ed;
  }

  /* id */
  ed->no   = sg->sgedid;
  ed->sid  = SMDNULL;
  /* type */
  ed->type = EDGE_SPATH_ORIGINAL;

  ed->sv = ed->ev = (SGvt *) NULL;
  ed->lf = ed->rf = (SGfc *) NULL;
  
  ed->sped = (Sped *) NULL;
  ed->spfc = (Spfc *) NULL;
  
  ++( sg->sgedn );
  ++( sg->sgedid );

  return ed;
}

SGed *CreateSGed( SGraph *sg, SGvt *sv, SGvt *ev, Sped *ed )
{
  SGed   *sged;
  
  sged = create_sged( sg );
  sged->sped = ed;
  
  sged->sv = sv;
  sged->ev = ev;
  (void) create_sgvted( sv, sged );
  (void) create_sgvted( ev, sged );
  
  return sged;
}

SGed *CreateSGedfromSGed( SGraph *sg, SGvt *sv, SGvt *ev, SGed *sged )
{
  SGed *nsged;

  nsged = CreateSGed( sg, sv, ev, sged->sped );
  nsged->type = sged->type;
  if ( nsged->type == EDGE_SPATH_ONFACE ) nsged->spfc = sged->spfc;

  return nsged;
}

void free_sged( SGed *ed, SGraph *sg )
{
  if ( ed == (SGed *) NULL ) return;

  if ( sg->sged == ed ) {
    if ( (sg->sged = ed->nxt) != (SGed *) NULL )
      ed->nxt->prv = (SGed *) NULL;
    else {
      sg->eged = (SGed *) NULL;
    }
  } else if (sg->eged == ed) {
    ed->prv->nxt = (SGed *) NULL;
    sg->eged = ed->prv;
  } else {
    ed->prv->nxt = ed->nxt;
    ed->nxt->prv = ed->prv;
  }

  --( sg->sgedn );
  free( ed );
}

void FreeSGed( SGed *ed, SGraph *sg )
{
  if ( ed == NULL ) return;
  FreeSGvted( ed->sv, ed );
  FreeSGvted( ed->ev, ed );
  free_sged( ed, sg );
}
  
void FreeSGEdge( SGraph *sg )
{
  SGed *ed, *ned;

  if ( sg == NULL ) return;
  
  for ( ed = sg->sged; ed != (SGed *) NULL; ed = ned ) {
    ned = ed->nxt;
    free_sged( ed, sg );
  }
  sg->sgedn = sg->sgedid = 0;
  sg->sged = sg->eged = (SGed *) NULL;
}

SGed *find_sged( SGvt *sv, SGvt *ev )
{
  SGvted *ve;
  SGed   *ed;
  
  for ( ve = sv->svted; ve != (SGvted *) NULL; ve = ve->nxt ) {
    ed = ve->ed;
    if ( (ed->sv == sv) && (ed->ev == ev) ) {
      return ed;
    }
    if ( (ed->ev == sv) && (ed->sv == ev) ) {
      return ed;
    }
  }
  
  return (SGed *) NULL;
}
    
      
/* SGfc functions */
SGfc *create_sgfc( SGraph *sg )
{
  SGfc *fc;

  fc = (SGfc *) malloc(sizeof(SGfc));

  fc->nxt = (SGfc *) NULL;
  if (sg->sgfc == (SGfc *) NULL) {
    fc->prv   = (SGfc *) NULL;
    sg->egfc = sg->sgfc = fc;
  } else {
    fc->prv   = sg->egfc;
    sg->egfc = sg->egfc->nxt = fc;
  }

  /* id */
  fc->no   = sg->sgfcid; 
  fc->sid  = SMDNULL;

  /* fc - edge */
  fc->sgfcvtn = 0;
  fc->sfcvt = (SGfcvt *) NULL;
  fc->efcvt = (SGfcvt *) NULL;

  fc->spfc = (Spfc *) NULL;
  
  ++( sg->sgfcn );
  ++( sg->sgfcid );

  return fc;
}

void free_sgfc( SGfc *fc, SGraph *sg )
{
  if (fc == (SGfc *) NULL) return;

  FreeSGFaceVertex( fc );
  
  if ( sg->sgfc == fc ) {
    if ( (sg->sgfc = fc->nxt) != (SGfc *) NULL )
      fc->nxt->prv = (SGfc *) NULL;
    else {
      sg->egfc = (SGfc *) NULL;
    }
  } else if (sg->egfc == fc) {
    fc->prv->nxt = (SGfc *) NULL;
    sg->egfc = fc->prv;
  } else {
    fc->prv->nxt = fc->nxt;
    fc->nxt->prv = fc->prv;
  }

  --( sg->sgfcn );
  free( fc );
}

void FreeSGFace( SGraph *sg )
{
  SGfc *fc, *nfc;

  if ( sg == NULL ) return;
  
  for ( fc = sg->sgfc; fc != (SGfc *) NULL; fc = nfc ) {
    nfc = fc->nxt;
    free_sgfc( fc, sg );
  }
  sg->sgfcn = sg->sgfcid = 0;
  sg->sgfc  = sg->egfc = (SGfc *) NULL;
}

/* SGvted functions */
SGfcvt *create_sgfcvt( SGfc *fc, SGvt *vt )
{
  SGfcvt *fv;

  fv = (SGfcvt *) malloc( sizeof(SGfcvt) );

  fv->nxt = (SGfcvt *) NULL;
  if (fc->sfcvt == (SGfcvt *) NULL) {
    fv->prv   = (SGfcvt *) NULL;
    fc->efcvt = fc->sfcvt = fv;
  } else {
    fv->prv   = fc->efcvt;
    fc->efcvt = fc->efcvt->nxt = fv;
  }

  fv->vt = vt;
  
  ++( fc->sgfcvtn );

  return fv;
}

void free_sgfcvt( SGfcvt *fv, SGfc *fc )
{
  if ( fc == NULL ) return;
  if ( fv == (SGfcvt *) NULL ) return;

  if ( fc->sfcvt == fv ) {
    if ( (fc->sfcvt = fv->nxt) != (SGfcvt *) NULL )
      fv->nxt->prv = (SGfcvt *) NULL;
    else {
      fc->efcvt = (SGfcvt *) NULL;
    }
  } else if ( fc->efcvt == fv ) {
    fv->prv->nxt = (SGfcvt *) NULL;
    fc->efcvt = fv->prv;
  } else {
    fv->prv->nxt = fv->nxt;
    fv->nxt->prv = fv->prv;
  }

  --( fc->sgfcvtn );
  free( fv );
}

void FreeSGFaceVertex( SGfc *fc )
{
  SGfcvt *fv, *nfv;

  if ( fc == NULL ) return;
  
  for ( fv = fc->sfcvt; fv != (SGfcvt *) NULL; fv = nfv ) {
    nfv = fv->nxt;
    free_sgfcvt( fv, fc );
  }
  fc->sgfcvtn = 0;
  fc->sfcvt  = fc->efcvt = (SGfcvt *) NULL;
}

/* SGvt functions */
SGlp *create_sglp( void )
{
  SGlp *lp;

  lp = (SGlp *) malloc( sizeof(SGlp) );

  /* lp - vt */
  lp->sglpvtn = 0;
  lp->slpvt = (SGlpvt *) NULL;
  lp->elpvt = (SGlpvt *) NULL;
  
  /* lp - vt */
  lp->sglpedn = 0;
  lp->slped = (SGlped *) NULL;
  lp->elped = (SGlped *) NULL;

  lp->length = 0.0;
  
  return lp;
}

void free_sglp( SGlp *lp )
{
  if ( lp == NULL ) return;
  
  FreeSGLoopEdge( lp );
  FreeSGLoopVertex( lp );

  free( lp );
}

/* SGlpvt functions */
SGlpvt *create_sglpvt( SGlp *lp, SGvt *vt )
{
  SGlpvt *lv;

  lv = (SGlpvt *) malloc( sizeof(SGlpvt) );

  lv->nxt = (SGlpvt *) NULL;
  if (lp->slpvt == (SGlpvt *) NULL) {
    lv->prv   = (SGlpvt *) NULL;
    lp->elpvt = lp->slpvt = lv;
  } else {
    lv->prv   = lp->elpvt;
    lp->elpvt = lp->elpvt->nxt = lv;
  }

  lv->vt = vt;
  
  ++( lp->sglpvtn );

  return lv;
}

void free_sglpvt( SGlpvt *lv, SGlp *lp )
{
  if (lv == (SGlpvt *) NULL) return;

  if ( lp->slpvt == lv ) {
    if ( (lp->slpvt = lv->nxt) != (SGlpvt *) NULL )
      lv->nxt->prv = (SGlpvt *) NULL;
    else {
      lp->elpvt = (SGlpvt *) NULL;
    }
  } else if (lp->elpvt == lv) {
    lv->prv->nxt = (SGlpvt *) NULL;
    lp->elpvt = lv->prv;
  } else {
    lv->prv->nxt = lv->nxt;
    lv->nxt->prv = lv->prv;
  }

  --( lp->sglpvtn );
  free( lv );
}

void FreeSGLoopVertex( SGlp *lp )
{
  SGlpvt *lv, *nlv;

  if ( lp == NULL ) return;
  
  for ( lv = lp->slpvt; lv != (SGlpvt *) NULL; lv = nlv ) {
    nlv = lv->nxt;
    free_sglpvt( lv, lp );
  }
  lp->sglpvtn = 0;
  lp->slpvt  = lp->elpvt = (SGlpvt *) NULL;
}
    
/* SGlped functions */
SGlped *create_sglped( SGlp *lp, SGed *ed )
{
  SGlped *le;

  le = (SGlped *) malloc( sizeof(SGlped) );

  le->nxt = (SGlped *) NULL;
  if (lp->slped == (SGlped *) NULL) {
    le->prv   = (SGlped *) NULL;
    lp->elped = lp->slped = le;
  } else {
    le->prv   = lp->elped;
    lp->elped = lp->elped->nxt = le;
  }

  le->ed = ed;
  
  ++( lp->sglpedn );

  return le;
}

void free_sglped( SGlped *le, SGlp *lp )
{
  if (le == (SGlped *) NULL) return;

  if ( lp->slped == le ) {
    if ( (lp->slped = le->nxt) != (SGlped *) NULL )
      le->nxt->prv = (SGlped *) NULL;
    else {
      lp->elped = (SGlped *) NULL;
    }
  } else if (lp->elped == le) {
    le->prv->nxt = (SGlped *) NULL;
    lp->elped = le->prv;
  } else {
    le->prv->nxt = le->nxt;
    le->nxt->prv = le->prv;
  }

  --( lp->sglpedn );
  free( le );
}

void FreeSGLoopEdge( SGlp *lp )
{
  SGlped *le, *nle;
  
  if ( lp == NULL ) return;
  
  for ( le = lp->slped; le != (SGlped *) NULL; le = nle ) {
    nle = le->nxt;
    free_sglped( le, lp );
  }
  lp->sglpedn = 0;
  lp->slped  = lp->elped = (SGlped *) NULL;
}

/* create sgraph from ppd */

SGraph *initialize_sgraph( Sppd *ppd )
{
  int    i;
  SGraph *sg;
  Spvt   *vt;
  Spfc   *fc;
  Sped   *ed;
  Sphe   *he;
  SGvt   *sgvt, **tmp_sgvt, *sv, *ev;
  SGfc   *sgfc, **tmp_sgfc;
  SGed   *sged;
  
  sg = create_sgraph();

  /* vertices */
  tmp_sgvt   = (SGvt **) malloc( ppd->vn * sizeof(SGvt *) );
  for ( i = 0, vt = ppd->spvt; vt != (Spvt *) NULL; vt = vt->nxt, ++i ) {
    vt->sid = i;
    sgvt = create_sgvt( sg );
    sgvt->spvt = vt;
    sgvt->type = VERTEX_SPATH_ORIGINAL;
    sgvt->vec.x = vt->vec.x;
    sgvt->vec.y = vt->vec.y;
    sgvt->vec.z = vt->vec.z;
    tmp_sgvt[i] = sgvt;
  }

  /* faces */
  tmp_sgfc = (SGfc **) malloc( ppd->fn * sizeof(SGfc *) );
  for ( i = 0, fc = ppd->spfc; fc != (Spfc *) NULL; fc = fc->nxt, ++i ) {
    fc->sid = i;
    sgfc = create_sgfc( sg );
    sgfc->spfc = fc;
    he = fc->sphe;
    do {
      vt   = he->vt;
      sgvt = tmp_sgvt[ vt->sid ];
      (void) create_sgfcvt( sgfc, sgvt );
    } while ( (he = he->nxt) != fc->sphe );
    tmp_sgfc[i] = sgfc;
  }

  /* edges */
  for ( ed = ppd->sped; ed != (Sped *) NULL; ed = ed->nxt ) {
    sv = tmp_sgvt[ ed->sv->sid ];
    ev = tmp_sgvt[ ed->ev->sid ];
    sged = CreateSGed( sg, sv, ev, ed );
    sged->type = EDGE_SPATH_ORIGINAL;
    ed->length = V3DistanceBetween2Points( &(sged->sv->vec), &(sged->ev->vec) );
    sged->length = ed->length;
    if ( ed->lf != NULL ) sged->lf = tmp_sgfc[ ed->lf->sid ];
    if ( ed->rf != NULL ) sged->rf = tmp_sgfc[ ed->rf->sid ];
  }

  free( tmp_sgvt );
  free( tmp_sgfc );

  add_vertices_edges_sgraph( sg );

  return sg;
}
    
/*
  STEP1:
  add vertices and edges in G
*/

#define NUMMIDPOINT 1
#define SUB_RATIO 0.5

void add_vertices_edges_sgraph( SGraph *sg )
{
  int     i, j, n;
  int     vcnt, escnt, eocnt, edcnt;
  int     num_midpoint, num_midpoint1;
  SGvt    *sgvt, *sv, *ev, *sgvt1, *sgvt2, **mid_sgvt;
  SGed    *sged, *next_sged, *sub_sged;
  SGfcvt  *sgfv1, *sgfv2;
  SGfc    *sgfc;
  Vec     *svec, *evec;
  double  s, t;

  vcnt = escnt = eocnt = edcnt = 0;
  
  /*
    STEP1-1:
    add n vertices on the edge of M
  */

  /* add vertices */
  num_midpoint  = NUMMIDPOINT;
  num_midpoint1 = num_midpoint+1;
  mid_sgvt = (SGvt **) malloc( num_midpoint * sg->sgedn * sizeof(SGvt *) );
  for ( j = 0, sged = sg->sged; sged != NULL; sged = sged->nxt, ++j ) {
    
    sged->sid = j;
    svec = &(sged->sv->vec);
    evec = &(sged->ev->vec);

    if ( sged->type == EDGE_SPATH_ORIGINAL ) {
      for ( i = 0; i < num_midpoint; ++i ) {
	
	sgvt = create_sgvt( sg ); ++vcnt;
	
	s = (double) (i + 1) / (double) num_midpoint1;
	t = 1 - s;
	sgvt->vec.x = t * svec->x + s * evec->x;
	sgvt->vec.y = t * svec->y + s * evec->y;
	sgvt->vec.z = t * svec->z + s * evec->z;
	
	sgvt->type = VERTEX_SPATH_ADDED;
	sgvt->sped = sged->sped;
	
	mid_sgvt[ num_midpoint * sged->sid + i ] = sgvt;

	if ( sged->lf != NULL ) create_sgfcvt( sged->lf, sgvt );
	if ( sged->rf != NULL ) create_sgfcvt( sged->rf, sgvt );
      }
    }
    
  }

  /*
    STEP1-2: condition 2
  */

  n = sg->sgedn; sged = sg->sged;
  j = 0;
  while ( j < n ) {
    
    next_sged = sged->nxt;
    
    if ( sged->type != EDGE_SPATH_ORIGINAL ) {
      sged = next_sged;
      ++j;
      continue;
    }
    
    /* create subdivide edges */
    sv = sged->sv;
    for ( i = 0; i < num_midpoint; ++i ) {
      ev = mid_sgvt[ num_midpoint * sged->sid + i ];

      sub_sged = CreateSGed( sg, sv, ev, sged->sped ); ++escnt;
      sub_sged->type = EDGE_SPATH_ORIGINAL;
      sub_sged->lf = sged->lf;
      sub_sged->rf = sged->rf;
      sub_sged->length = sged->sped->length * SUB_RATIO;
      
      sv = ev;
    }
    ev = sged->ev;
    sub_sged = CreateSGed( sg, sv, ev, sged->sped ); ++escnt;
    sub_sged->type = EDGE_SPATH_ORIGINAL;
    sub_sged->lf = sged->lf;
    sub_sged->rf = sged->rf;
    sub_sged->length = sged->sped->length * SUB_RATIO;
      
    /* delete an original edge */
    FreeSGed( sged, sg ); ++edcnt;

    ++j;
    sged = next_sged;
    
  }
     
  /*
    STEP1-2: condition 1
  */

  for ( sgfc = sg->sgfc; sgfc != (SGfc *) NULL; sgfc = sgfc->nxt ) {
    
    for ( sgfv1 = sgfc->sfcvt; sgfv1 != (SGfcvt *) NULL; sgfv1 = sgfv1->nxt ) {
      sgvt1 = sgfv1->vt;
      for ( sgfv2 = sgfv1->nxt; sgfv2 != (SGfcvt *) NULL; sgfv2 = sgfv2->nxt ) {
	sgvt2 = sgfv2->vt;

	if ( ( isOnDifferentEdges( sgvt1, sgvt2 ) == TRUE ) &&
	     ( find_sged( sgvt1, sgvt2 ) == NULL ) ) {
	  sged = CreateSGed( sg, sgvt1, sgvt2, NULL ); ++eocnt;
	  sged->type = EDGE_SPATH_ONFACE;
	  sged->spfc = sgfc->spfc;
	  sged->length = V3DistanceBetween2Points( &(sged->sv->vec), &(sged->ev->vec) );
	  
	}
      }
    }
  }

  free( mid_sgvt );
}

BOOL isOnDifferentEdges( SGvt *vt1, SGvt *vt2 )
{
  Sped *ed;
  Spvt *vt;
  
  if ( (vt1->type == VERTEX_SPATH_ADDED) &&
       (vt2->type == VERTEX_SPATH_ADDED) ) {
    if ( vt1->sped != vt2->sped ) return TRUE;
  } else if ( (vt1->type == VERTEX_SPATH_ADDED) &&
	      (vt2->type == VERTEX_SPATH_ORIGINAL) ) {
    ed = vt1->sped;
    vt = vt2->spvt;
    if ( (ed->sv != vt) && (ed->ev != vt) ) return TRUE;
  } else if ( (vt1->type == VERTEX_SPATH_ORIGINAL) &&
	      (vt2->type == VERTEX_SPATH_ADDED) ) {
    ed = vt2->sped;
    vt = vt1->spvt;
    if ( (ed->sv != vt) && (ed->ev != vt) ) return TRUE;
  }
  return FALSE;
}

/*
  STEP2:
  calculating a shortest-path using Dijkstra's algorithm
*/

/* Dijkstra's algorithm using SGraph */
SGlp *ShortestPath_Dijkstra_SGraph( SGraph *sg, SGvt *src, SGvt *dist )
{
  int      i;
  int      num1, num2;
  SGvt     *vt, *avt, *min_tvt;
  SGlp     *lp;
  SGPQHeap *pqh;
  SGPQCont *pqc;
  double   min_dis, newlen;
  SGvted   *vted;
  SGVtList *vtlist;
  
  /* Spvt の初期化 */

  for ( i = 0, vt = sg->sgvt; vt != (SGvt *) NULL; vt = vt->nxt, ++i ) {
    vt->sid = i;
    vt->pqc = (SGPQCont *) NULL;
    vt->pq_type = EMPTY;
    if ( vt == src )  vt->pq_type = DELETED;
    
  }

  /* initialize priority queue */
  pqh    = create_sgpqheap( sg->sgvtn );
  vtlist = (SGVtList *) malloc( sg->sgvtn * sizeof(SGVtList) );
  vtlist[src->sid].prv = src;
  vtlist[src->sid].dis = 0.0;

  for ( vted = src->svted; vted != (SGvted *) NULL; vted = vted->nxt ) {
    avt = another_sgvt( vted->ed, src );
    insert_sgpqcont( vted->ed->length, pqh, avt, src );
  }
  
  /* vtlist: S から 1 つのエッジで辿れるものしか値が入らない */
  
  for ( i = 0; i < sg->sgvtn - 1; ++i ) {
    /* min_tvt S に加える */
    min_dis = pqh->pqcont[0].distance;
    min_tvt = pqh->pqcont[0].tgt_vt;
    vtlist[ min_tvt->sid ].prv = pqh->pqcont[0].prv_vt;
    vtlist[ min_tvt->sid ].dis = min_dis;

    /* min_tvt をヒープから消去 */
    deletemin_sgpqcont( pqh );
    
    for ( vted = min_tvt->svted; vted != (SGvted *) NULL; vted = vted->nxt ) {

      avt    = another_sgvt( vted->ed, min_tvt );
      newlen = min_dis + vted->ed->length;
      pqc    = avt->pqc;

      if ( (pqc == (SGPQCont *) NULL) && (avt->pq_type == EMPTY) ) {
	
	insert_sgpqcont( newlen, pqh, avt, min_tvt );
	
      } else if ( pqc != (SGPQCont *) NULL ) {

	/* updated. 97/08/28. modified from original dijkstra's algorithm. */
	if ( fabs( newlen - pqc->distance ) < SMDZEROEPS ) {

 	  num1 = sg_stepnumber_to_src( (SGVtList *) vtlist, pqc->prv_vt, src ); 
 	  num2 = sg_stepnumber_to_src( (SGVtList *) vtlist, min_tvt, src ); 

	  if ( num2 < num1 ) {

	    pqc->distance = newlen;
	    pqc->prv_vt   = min_tvt;
	  
	    adjust_sgpqheap( pqc->id, pqh );
	  }
	  
	} else {
	  
	  if ( newlen < pqc->distance ) {

	    pqc->distance = newlen;
	    pqc->prv_vt   = min_tvt;
	  
	    adjust_sgpqheap( pqc->id, pqh );

	  }
	}
	
      }
    }
  }

  /* VtList to Loop */
  lp = sgvtlist_to_sglp( (SGVtList *) vtlist, src, dist );

  free_sgpqheap( pqh );
  free( vtlist );

  return lp;
}

int sg_stepnumber_to_src( SGVtList *vtlist, SGvt *start, SGvt *goal )
{
  int cnt = 0;
  SGvt *vt;

  vt = start; 

  while ( vt != goal ) {
    ++cnt;
    vt = vtlist[vt->sid].prv;
  }
    
  return cnt;
}

/* for testing */
SGlp *sgvtlist_to_sglp( SGVtList *vtlist, SGvt *src, SGvt *dist )
{
  SGvt *sgvt, *sv, *ev;
  SGlpvt *lv;
  SGlp *lp;
  SGed *ed;

  if ( vtlist == (SGVtList *) NULL ) return (SGlp *) NULL;

  lp = create_sglp();

  /* create loop vertices */
  /* lp includes src and dist. */
  sgvt = dist;
  while ( sgvt != src ) {
    lv = create_sglpvt( lp, sgvt );
    sgvt = vtlist[ sgvt->sid ].prv;
  }

  /* include a last vertex(src) */
  lv = create_sglpvt( lp, sgvt );
  
  /* create loop edges */
  lp->length = 0.0;
  for ( lv = lp->slpvt; lv->nxt != (SGlpvt *) NULL; lv = lv->nxt ) {
    sv = lv->vt;
    ev = lv->nxt->vt;
    ed = find_sged( sv, ev );
    lp->length += ed->length;
  }
  
  /* (dist -> src) -->> (src -> dist) */
/*   nlp = reverse_sglp( lp ); */
/*   free_sglp( lp ); */
  
  return lp;
}

/*
  STEP3:
  create graph G' from SGlp
*/

SGraph *sglp_to_sgraph( SGlp *lp, SGraph *sg )
{
  int     i, n;
  SGlpvt  *lv;
  SGraph  *nsg;
  SGvt    *sgvt, *egvt, *new_sv, *new_ev, *sv, *ev, *next_sgvt;
  SGed    *sged, *new_sged;
  SGfc    *sgfc;
  SGvted  *ve;
  SGlp    *nlp;
  BOOL *sgvtsearch, *sgedsearch, *sgfcsearch;
  SGvt    **new_sgvt;
  SGfc    **new_sgfc;

  /* initialize search functions */
  new_sgvt   = (SGvt **) malloc( sg->sgvtn * sizeof(SGvt *) );
  sgvtsearch = (BOOL *) malloc( sg->sgvtn * sizeof(BOOL) );
  for ( i = 0, sgvt = sg->sgvt; i < sg->sgvtn; ++i, sgvt = sgvt->nxt ) {
    sgvt->sid = i;
    sgvtsearch[i] = FALSE;
    new_sgvt[i] = NULL;
  }
  sgedsearch = (BOOL *) malloc( sg->sgedn * sizeof(BOOL) );
  for ( i = 0, sged = sg->sged; i < sg->sgedn; ++i, sged = sged->nxt ) {
    sged->sid = i;
    sgedsearch[i] = FALSE;
  }
  sgfcsearch = (BOOL *) malloc( sg->sgfcn * sizeof(BOOL) );
  new_sgfc   = (SGfc **) malloc( sg->sgfcn * sizeof(SGfc *) );
  for ( i = 0, sgfc = sg->sgfc; i < sg->sgfcn; ++i, sgfc = sgfc->nxt ) {
    sgfc->sid = i;
    sgfcsearch[i] = FALSE;
    new_sgfc[i] = NULL;
  }
  
  nsg = create_sgraph();
  nlp = create_sglp();

  /* STEP3-1:
    create vertices in G'
  */
  for ( lv = lp->slpvt; lv != (SGlpvt *) NULL; lv = lv->nxt ) {
    sgvt  = lv->vt;
    new_sv = CreateSGvtfromSGvt( nsg, sgvt );
    sgvtsearch[ sgvt->sid ] = TRUE;
    new_sgvt[ sgvt->sid ] = new_sv;
    (void) create_sglpvt( nlp, new_sv );
  }
  
  for ( lv = lp->slpvt; lv != (SGlpvt *) NULL; lv = lv->nxt ) {
    /* create sgvt from loop vertices */
    sgvt  = lv->vt;
    new_sv = new_sgvt[ sgvt->sid ];

    /* create neighbor vertices */
    for ( ve = sgvt->svted; ve != (SGvted *) NULL; ve = ve->nxt ) {
      sged = ve->ed;
      if ( sged->type == EDGE_SPATH_ORIGINAL ) {
	egvt = another_sgvt( sged, sgvt );
	if ( sgvtsearch[ egvt->sid ] == FALSE ) {
	  new_ev = CreateSGvtfromSGvt( nsg, egvt );
	  sgvtsearch[ egvt->sid ] = TRUE;
	  new_sgvt[ egvt->sid ]   = new_ev;
	} else {
	  new_ev = new_sgvt[ egvt->sid ];
	}
	
	if ( sged->lf != (SGfc *) NULL ) {
	  if ( sgfcsearch[ sged->lf->sid ] == FALSE ) {
	    sgfc = create_sgfc( nsg );
	    sgfc->spfc = sged->lf->spfc;
	    sgfcsearch[ sged->lf->sid ] = TRUE;
	    new_sgfc[ sged->lf->sid ] = sgfc;
	  } else {
	    sgfc = new_sgfc[ sged->lf->sid ];
	  }
	  if ( find_sgvt_from_sgfc( sgfc, new_sv ) == NULL )
	    create_sgfcvt( sgfc, new_sv );
	  if ( find_sgvt_from_sgfc( sgfc, new_ev ) == NULL )
	    create_sgfcvt( sgfc, new_ev );
	}
	
	if ( sged->rf != (SGfc *) NULL ) {
	  if ( sgfcsearch[ sged->rf->sid ] == FALSE ) {
	    sgfc = create_sgfc( nsg );
	    sgfc->spfc = sged->rf->spfc;
	    sgfcsearch[ sged->rf->sid ] = TRUE;
	    new_sgfc[ sged->rf->sid ] = sgfc;
	  } else {
	    sgfc = new_sgfc[ sged->rf->sid ];
	  }
	  if ( find_sgvt_from_sgfc( sgfc, new_sv ) == NULL )
	    create_sgfcvt( sgfc, new_sv );
	  if ( find_sgvt_from_sgfc( sgfc, new_ev ) == NULL )
	    create_sgfcvt( sgfc, new_ev );
	}
      }
    }
  }

  /* STEP3-2:
     create edges in G'
  */

  sgvt = sg->sgvt; n = sg->sgvtn; i = 0;
  while ( i < n ) {

    if ( sgvtsearch[ sgvt->sid ] == TRUE ) {
      /* create neighbor vertices */
      for ( ve = sgvt->svted; ve != (SGvted *) NULL; ve = ve->nxt ) {
	sged = ve->ed;
	sv = sged->sv;
	ev = sged->ev;
	if ( (sgvtsearch[ sv->sid ] == TRUE) &&
	     (sgvtsearch[ ev->sid ] == TRUE) &&
	     (sgedsearch[ sged->sid ] == FALSE) ) {
	  new_sv = new_sgvt[ sv->sid ];
	  new_ev = new_sgvt[ ev->sid ];
	  new_sged = CreateSGedfromSGed( nsg, new_sv, new_ev, sged );
	  new_sged->length = sged->length;
	  if ( sged->lf != NULL ) new_sged->lf = new_sgfc[ sged->lf->sid ];
	  if ( sged->rf != NULL ) new_sged->rf = new_sgfc[ sged->rf->sid ];
	}
	sgedsearch[ sged->sid ] = TRUE;
      }
    }
    sgvt = sgvt->nxt; ++i; 
 }

  /* STEP3-3:
     delete vertices and edges in G'
  */

  sgvt = nsg->sgvt; n = nsg->sgvtn;
  i = 0;
  while ( i < n ) {
    next_sgvt = sgvt->nxt;

    if ( sgvt->sgvtedn < 2 ) {
      if ( sgvt->svted != NULL ) {
	sged = sgvt->svted->ed;
	FreeSGed( sged, nsg );
      }
      free_sgvt( sgvt, nsg );
    }

    sgvt = next_sgvt;
    ++i;
  }

  free( sgvtsearch );
  free( sgedsearch );
  free( sgfcsearch );
  free( new_sgvt );
  free( new_sgfc );

  nlp->length = lp->length;
  nsg->lp = nlp;
  nsg->src  = nlp->elpvt->vt;
  nsg->dist = nlp->slpvt->vt;

  return nsg;
}

