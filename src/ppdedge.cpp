/* Copyright (c) 1997 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"

/***************************************
  Edge
****************************************/

Sped *create_ppdedge(Sppd *ppd)
{
  Sped *ed;

  ed = (Sped *) malloc(sizeof(Sped));

  ed->nxt = (Sped *) NULL;
  if (ppd->sped == (Sped *) NULL) {
    ed->prv   = (Sped *) NULL;
    ppd->eped = ppd->sped = ed;
  } else {
    ed->prv   = ppd->eped;
    ppd->eped = ppd->eped->nxt = ed;
  }

  /* edge color */
  ed->col = EDGEWHITE;
  
  /* IDs */
  ed->no  = ppd->eid;
  
  /* type */
  ed->type = EDGE_ORIGINAL;

  /* links */
  ed->sv = (Spvt *) NULL;
  ed->ev = (Spvt *) NULL;
  ed->lf = (Spfc *) NULL;
  ed->rf = (Spfc *) NULL;

  /* quadtree */
/*   ed->qe = (QEdge *) NULL; */

  /* edge -> vertex links */
  ed->evn   = 0;
  ed->sedvt = (Edvt *) NULL;
  ed->eedvt = (Edvt *) NULL;

  /* loop check */
  ed->used_loop = SMD_OFF;
  
  /* for morphing */
/*   ed->med   = (Sped *) NULL; */

  /* for shortest-path */
  ed->sp_type  = SP_EDGE_NORMAL;
  ed->cal_subgraph = SMD_OFF;
  ed->org_ed   = NULL;

  ed->group_id = SMDNULL;

  /* for copy_ppd */
  ed->ned = (Sped *) NULL;
  
  /* for creating hppdlod */
  ed->atr = EDGEINTERNAL;

  /* for checking egde-face links */
  ed->fn = 0;
  
  // for SparseMatrix (fairing)
  ed->ewt = 0.0;

  ++( ppd->en );
  ++( ppd->eid );
  
  return ed;
}

void free_ppdedge( Sped *ed, Sppd *ppd )
{
  void free_ppdedgevertex( Sped * );
  
  if (ed == (Sped *) NULL) return;

  free_ppdedgevertex( ed );

  if (ppd->sped == ed) {
    if ((ppd->sped = ed->nxt) != (Sped *) NULL)
      ed->nxt->prv = (Sped *) NULL;
    else {
      ppd->eped = (Sped *) NULL;
    }
  } else if (ppd->eped == ed) {
    ed->prv->nxt = (Sped *) NULL;
    ppd->eped = ed->prv;
  } else {
    ed->prv->nxt = ed->nxt;
    ed->nxt->prv = ed->prv;
  }

  free(ed);
  --( ppd->en );
}

void free_ppdedge_withqtree(Sped *ed, Sppd *ppd)
{
  void  delete_qtree_edge(QEdge *, QTree *);
  void  free_ppdedge(Sped *, Sppd *);
    
/*   if (ed->qe != (QEdge *) NULL) { */
/*     qe = ed->qe; */
/*     qt = qe->qt; */
/*     delete_qtree_edge(qe, qt); */
/*   } */
  free_ppdedge(ed, ppd);
}

void FreeSped( Sped *ed, Sppd *ppd )
{
  void FreeVted( Spvt *, Sped * );
  void free_ppdedge( Sped *, Sppd * );

  if ( ed == NULL ) return;
  FreeVted( ed->sv, ed );
  FreeVted( ed->ev, ed );
  free_ppdedge( ed, ppd );
}

/* vertex -> edge */

Edvt *create_edvtx(Sped *edge, Spvt *vt)
{
  Edvt *ev;

  if (vt == (Spvt *) NULL) return (Edvt *) NULL;
  
  ev = (Edvt *) malloc(sizeof(Edvt));

  ev->nxt = (Edvt *) NULL;
  if (edge->sedvt == (Edvt *) NULL) {
    ev->prv       = (Edvt *) NULL;
    edge->eedvt = edge->sedvt = ev;
  } else {
    ev->prv       = edge->eedvt;
    edge->eedvt = edge->eedvt->nxt = ev;
  }

  /* edge */
  ev->ed = edge;
  /* vertex */
  ev->vt = vt;
  ev->val = 0.0;
  ev->int_ed = (Sped *) NULL;
  
  ++(edge->evn);
  
  return ev;
}

void insert_edvtx( Sped *ed, Spvt *vt, Sped *int_edge, double val )
{
  Edvt   *ev, *nev;
  Edvt   *create_edvtx(Sped *, Spvt *);

  if ( ed == (Sped *) NULL ) return;
  
  /* first */
  if (ed->sedvt == (Edvt *) NULL) {
    ev = create_edvtx(ed, vt);
    ev->val = val;
    ev->int_ed = int_edge;
    return;
  }
  
  /* calc angle */
  ev    = ed->sedvt;
  while ((ev != (Edvt *) NULL) && (val > ev->val)) {
    ev = ev->nxt;
  }

  /* last */
  if (ev == (Edvt *) NULL) {
    ev = create_edvtx(ed, vt);
    ev->val = val;
    ev->int_ed = int_edge;
    return;
  } 

  nev = (Edvt *) malloc(sizeof(Edvt));

  nev->prv = ev->prv;
  nev->nxt = ev;
  if (ev->prv != (Edvt *) NULL) 
    ev->prv->nxt = nev;
  ev->prv = nev;
  if (ed->sedvt == ev) ed->sedvt = nev;

  nev->ed = ed;
  nev->vt = vt;
  nev->val = val;
  nev->int_ed = int_edge;

  ++( ed->evn );
  
  return;
}

void free_ppdedgevertex(Sped *ed)
{
  Edvt *ev, *evnxt;
  void free_edvtx(Edvt *, Sped *);

  for (ev = ed->sedvt; ev != (Edvt *) NULL; ev = evnxt) {
    evnxt = ev->nxt;
    free_edvtx(ev, ed);
    
  }
  ed->evn = 0;
  ed->sedvt = ed->eedvt = (Edvt *) NULL;
}

void free_edvtx(Edvt *ev, Sped *ed)
{
  if (ev == (Edvt *) NULL) return;

  ev->ed = (Sped *) NULL;
  ev->vt = (Spvt *) NULL;
  
  if (ed->sedvt == ev) {
    if ((ed->sedvt = ev->nxt) != (Edvt *) NULL)
      ev->nxt->prv = (Edvt *) NULL;
    else {
      ed->eedvt = (Edvt *) NULL;
    }
  } else if (ed->eedvt == ev) {
    ev->prv->nxt = (Edvt *) NULL;
    ed->eedvt = ev->prv;
  } else {
    ev->prv->nxt = ev->nxt;
    ev->nxt->prv = ev->prv;
  }
  free(ev);
  --( ed->evn );
}

void edge_length( Sppd *ppd )
{
  int  i;
  Sped *ed;
  double V3DistanceBetween2Points( Vec *, Vec * );
  
  for ( i = 0, ed = ppd->sped; ed != (Sped *) NULL; ed = ed->nxt, ++i ) {

    ed->length = V3DistanceBetween2Points( &(ed->sv->vec), &(ed->ev->vec) );
    if ( i ) {
      
      if ( ed->length > ppd->max_edge_length ) {
	ppd->max_edge_length = ed->length;
      }
      
    } else {
      ppd->max_edge_length = ed->length;
    }
    
  }
}

Sped *find_ppdedge(Spvt *sv, Spvt *ev)
{
  Vted *ve;
  
  ve = sv->svted;
  while (ve != (Vted *) NULL) {
    if ( ( (ve->ed->sv == sv) && (ve->ed->ev == ev) ) ||
	 ( (ve->ed->sv == ev) && (ve->ed->ev == sv) ) ) {
      return ve->ed;
    }
    ve = ve->nxt;
  }
  return (Sped *) NULL;
}
      

