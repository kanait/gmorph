/* Copyright (c) 1997-1998 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "hged.h"

/* hgppd edge */
HGed *create_hgppdedge( HGfc *fc )
{
  HGed *ed;

  ed = (HGed *) malloc(sizeof(HGed));

  ed->nxt = (HGed *) NULL;
  if (fc->shged == (HGed *) NULL) {
    ed->prv   = (HGed *) NULL;
    fc->ehged = fc->shged = ed;
  } else {
    ed->prv   = fc->ehged;
    fc->ehged = fc->ehged->nxt = ed;
  }

  ed->no = fc->hgen;

  /* reference ppd edge */
  ed->ed = (Sped *) NULL;

  /* HG vertex links */
  ed->sv = (HGvt *) NULL;
  ed->ev = (HGvt *) NULL;

  /* HG surface links */
  ed->rf = (HGsf *) NULL;
  ed->lf = (HGsf *) NULL;
  
  /* links to HGedvt */
  ed->hgevn = 0;
  ed->shgev = (HGedvt *) NULL;
  ed->ehgev = (HGedvt *) NULL;

  /* links to HGeded */
  ed->mhgedn = 0;
  ed->smhged = (HGeded *) NULL;
  ed->emhged = (HGeded *) NULL;
  
  /* for harmonic map */
  ed->sid = SMDNULL;
  ed->sp_type = SP_EDGE_NORMAL;

  /* used in "edge_edge_intersection */
  ed->pass = SMD_OFF;

  ++( fc->hgen );

  return ed;
}

void free_hgppdedge( HGed *ed, HGfc *fc )
{
  
  if (ed == (HGed *) NULL) return;

  ed->ed = (Sped *) NULL;
  
  if (fc->shged == ed) {
    if ((fc->shged = ed->nxt) != (HGed *) NULL)
      ed->nxt->prv = (HGed *) NULL;
    else {
      fc->ehged = (HGed *) NULL;
    }
  } else if (fc->ehged == ed) {
    ed->prv->nxt = (HGed *) NULL;
    fc->ehged = ed->prv;
  } else {
    ed->prv->nxt = ed->nxt;
    ed->nxt->prv = ed->prv;
  }

  free(ed);
  --( fc->hgen );
}

HGed *find_hgppdedge( HGvt *sv, HGvt *ev )
{
  HGvted *ve;
  
  ve = sv->shgve;
  while (ve != (HGvted *) NULL) {
    if ( ( (ve->ed->sv == sv) && (ve->ed->ev == ev) ) ||
         ( (ve->ed->sv == ev) && (ve->ed->ev == sv) ) ) {
      return ve->ed;
    }
    ve = ve->nxt;
  }
  return (HGed *) NULL;
}

HGedList *create_hgedlist( void )
{
  HGedList *hgedlist;

  hgedlist = (HGedList *) malloc( sizeof(HGedList) );
  
  hgedlist->en = 0;
  hgedlist->senode = hgedlist->eenode = (HGedNode *) NULL;

  return hgedlist;
}

void free_hgedlist( HGedList *hgedlist )
{
  HGedNode *enode, *nenode;
  
  for ( enode = hgedlist->senode; enode != (HGedNode *) NULL; enode = nenode ) {
    nenode = enode->nxt;
    free_hgednode( enode, hgedlist );
  }
  
  free( hgedlist );
}

HGedNode *create_hgednode( HGed *ed, HGedList *hgedlist )
{
  HGedNode *enode;

  enode = (HGedNode *) malloc(sizeof(HGedNode));

  enode->nxt = (HGedNode *) NULL;
  if (hgedlist->senode == (HGedNode *) NULL) {
    enode->prv   = (HGedNode *) NULL;
    hgedlist->eenode = hgedlist->senode = enode;
  } else {
    enode->prv   = hgedlist->eenode;
    hgedlist->eenode = hgedlist->eenode->nxt = enode;
  }

  enode->ed = ed;
  ++( hgedlist->en );

  return enode;
}
  
void free_hgednode( HGedNode *enode, HGedList *hgedlist )
{
  if (enode == (HGedNode *) NULL) return;

  if (hgedlist->senode == enode) {
    if ((hgedlist->senode = enode->nxt) != (HGedNode *) NULL)
      enode->nxt->prv = (HGedNode *) NULL;
    else {
      hgedlist->eenode = (HGedNode *) NULL;
    }
  } else if (hgedlist->eenode == enode) {
    enode->prv->nxt = (HGedNode *) NULL;
    hgedlist->eenode = enode->prv;
  } else {
    enode->prv->nxt = enode->nxt;
    enode->nxt->prv = enode->prv;
  }

  free( enode );
  --( hgedlist->en );
}
  
void free_start_hgednode( HGedList *hgedlist )
{
  HGedNode *enode;
  void free_hgednode( HGedNode *, HGedList * );
  
  enode = hgedlist->senode;

  free_hgednode( enode, hgedlist );
}

/* HG edge -> vertex */
HGedvt *create_hgedvt( HGvt *hgvt, HGed *hged )
{
  int i;
  HGedvt *ev;

  if ( hged == (HGed *) NULL) return (HGedvt *) NULL;
  
  ev = (HGedvt *) malloc(sizeof(HGedvt));

  ev->nxt = (HGedvt *) NULL;
  if (hged->shgev == (HGedvt *) NULL) {
    ev->prv       = (HGedvt *) NULL;
    hged->ehgev = hged->shgev = ev;
  } else {
    ev->prv       = hged->ehgev;
    hged->ehgev = hged->ehgev->nxt = ev;
  }

  /* intersection point */
  ev->vt = hgvt;

  /* for creating gppd edge */
  ev->lf = NULL;
  ev->rf = NULL;

  ev->mate = NULL;

  /* other intersected edges */
  ev->intsec_ed = NULL;

  ev->rotation = EDGE_END;

  for ( i = 0; i < NUM_INTERSECTION_EDGE; ++i ) {
    ev->mhged[i] = NULL;
  }
  
  ++(hged->hgevn);
  
  return ev;
}

void free_hgppdedgevertex( HGed *ed )
{
  HGedvt *ev, *evnxt;

  for ( ev = ed->shgev; ev != (HGedvt *) NULL; ev = evnxt ) {
    evnxt = ev->nxt;
    free_hgedvt( ev, ed );
  }
  ed->hgevn = 0;
  ed->shgev = ed->ehgev = (HGedvt *) NULL;
}

void free_hgedvt( HGedvt *ev, HGed *ed )
{
  if (ev == (HGedvt *) NULL) return;

  ev->vt = (HGvt *) NULL;
  
  if (ed->shgev == ev) {
    if ((ed->shgev = ev->nxt) != (HGedvt *) NULL)
      ev->nxt->prv = (HGedvt *) NULL;
    else {
      ed->ehgev = (HGedvt *) NULL;
    }
  } else if (ed->ehgev == ev) {
    ev->prv->nxt = (HGedvt *) NULL;
    ed->ehgev = ev->prv;
  } else {
    ev->prv->nxt = ev->nxt;
    ev->nxt->prv = ev->prv;
  }
  free(ev);
  --( ed->hgevn );
}


/* for sorting intersection points */
/* used in "HGedvtSort" */

HGedvtList *create_hgedvtlist( void )
{
  HGedvtList *hgedvtlist;

  hgedvtlist = (HGedvtList *) malloc( sizeof(HGedvtList) );
  
  hgedvtlist->en = 0;
  hgedvtlist->senode = hgedvtlist->eenode = (HGedvtNode *) NULL;

  return hgedvtlist;
}

void free_hgedvtlist( HGedvtList *hgedvtlist )
{
  HGedvtNode *enode, *nenode;
  
  for ( enode = hgedvtlist->senode; enode != (HGedvtNode *) NULL; enode = nenode ) {
    nenode = enode->nxt;
    free_hgedvtnode( enode, hgedvtlist );
  }
  
  free( hgedvtlist );
}

HGedvtNode *create_hgedvtnode( HGedvtList *hgedvtlist )
{
  HGedvtNode *enode;

  enode = (HGedvtNode *) malloc(sizeof(HGedvtNode));

  enode->nxt = (HGedvtNode *) NULL;
  if (hgedvtlist->senode == (HGedvtNode *) NULL) {
    enode->prv   = (HGedvtNode *) NULL;
    hgedvtlist->eenode = hgedvtlist->senode = enode;
  } else {
    enode->prv   = hgedvtlist->eenode;
    hgedvtlist->eenode = hgedvtlist->eenode->nxt = enode;
  }

  enode->sf = NULL;
  enode->ef = NULL;
  enode->mate = NULL;
  enode->intsec_ed = NULL;
  enode->vt = NULL;
  
  ++( hgedvtlist->en );

  return enode;
}

HGedvtNode *create_start_hgedvtnode( HGedvtList *hgedvtlist )
{
  HGedvtNode *newnode, *prvnode;
  
  if ( hgedvtlist->senode == (HGedvtNode *) NULL ) {
    newnode = create_hgedvtnode( hgedvtlist );
    return newnode;
  } else {
    
    newnode = (HGedvtNode *) malloc(sizeof(HGedvtNode));
    
    prvnode = hgedvtlist->senode;
    newnode->prv = (HGedvtNode *) NULL;
    newnode->nxt = prvnode;
    prvnode->prv = newnode;
    hgedvtlist->senode = newnode;

    newnode->sf = NULL;
    newnode->ef = NULL;
    newnode->mate = NULL;
    newnode->intsec_ed = NULL;
    newnode->vt = NULL;
  
    return newnode;
  }
  
}

HGedvtNode *create_end_hgedvtnode( HGedvtList *hgedvtlist )
{
  HGedvtNode *node;
  
  node = create_hgedvtnode( hgedvtlist );

  return node;
}

void free_hgedvtnode( HGedvtNode *enode, HGedvtList *hgedvtlist )
{
  if (enode == (HGedvtNode *) NULL) return;

  if (hgedvtlist->senode == enode) {
    if ((hgedvtlist->senode = enode->nxt) != (HGedvtNode *) NULL)
      enode->nxt->prv = (HGedvtNode *) NULL;
    else {
      hgedvtlist->eenode = (HGedvtNode *) NULL;
    }
  } else if (hgedvtlist->eenode == enode) {
    enode->prv->nxt = (HGedvtNode *) NULL;
    hgedvtlist->eenode = enode->prv;
  } else {
    enode->prv->nxt = enode->nxt;
    enode->nxt->prv = enode->prv;
  }

  free( enode );
  --( hgedvtlist->en );
}
  
void free_start_hgedvtnode( HGedvtList *hgedvtlist )
{
  HGedvtNode *enode;
  
  enode = hgedvtlist->senode;

  free_hgedvtnode( enode, hgedvtlist );
}

/* HG edge -> mhged for storing intersection edges */
/* use only hgfc1, hgfc2 */
HGeded *create_hgeded( HGed *hged )
{
  HGeded *eded;

  if ( hged == (HGed *) NULL) return (HGeded *) NULL;
  
  eded = (HGeded *) malloc(sizeof(HGeded));

  eded->nxt = (HGeded *) NULL;
  if (hged->smhged == (HGeded *) NULL) {
    eded->prv       = (HGeded *) NULL;
    hged->emhged = hged->smhged = eded;
  } else {
    eded->prv       = hged->emhged;
    hged->emhged = hged->emhged->nxt = eded;
  }

  /* morphing edges  */
  eded->mhged = NULL;

  ++( hged->mhgedn );
  
  return eded;
}

void free_hgppdedgeedge( HGed *ed )
{
  HGeded *eded, *edednxt;

  for ( eded = ed->smhged; eded != (HGeded *) NULL; eded = edednxt ) {
    edednxt = eded->nxt;
    free_hgeded( eded, ed );
  }
  ed->mhgedn = 0;
  ed->smhged = ed->emhged = (HGeded *) NULL;
}

void free_hgeded( HGeded *eded, HGed *ed )
{
  if (eded == (HGeded *) NULL) return;

  eded->mhged = (HGed *) NULL;
  
  if (ed->smhged == eded) {
    if ((ed->smhged = eded->nxt) != (HGeded *) NULL)
      eded->nxt->prv = (HGeded *) NULL;
    else {
      ed->emhged = (HGeded *) NULL;
    }
  } else if (ed->emhged == eded) {
    eded->prv->nxt = (HGeded *) NULL;
    ed->emhged = eded->prv;
  } else {
    eded->prv->nxt = eded->nxt;
    eded->nxt->prv = eded->prv;
  }
  free( eded );
  --( ed->mhgedn );
}


