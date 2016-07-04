/* Copyright (c) 1997 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"

/***************************************
  Loop
****************************************/

Splp *create_splp( void )
{
  Splp *lp;

  lp = (Splp *) malloc(sizeof(Splp));
  
  lp->nxt = (Splp *) NULL;
  lp->prv = (Splp *) NULL;

  /*  total loop vertex */
  lp->lvn   = 0;
  /* corner loop vertex */
  lp->lcvn  = 0; 
  lp->splv  = (Splv *) NULL;
  lp->eplv  = (Splv *) NULL;

  /*  total loop edge */
  lp->len   = 0;
  lp->sple  = (Sple *) NULL;
  lp->eple  = (Sple *) NULL;

  lp->hed   = (HEdge *) NULL;
  lp->col   = LOOPBLUE;
  
  return lp;
}

/* loop */
Splp *create_ppdloop( Sppd *ppd )
{
  Splp *lp;

  lp = (Splp *) malloc(sizeof(Splp));

  lp->nxt = (Splp *) NULL;
  if (ppd->splp == (Splp *) NULL) {
    lp->prv = (Splp *) NULL;
    ppd->eplp = ppd->splp = lp;
  } else {
    lp->prv   = ppd->eplp;
    ppd->eplp = ppd->eplp->nxt = lp;
  }

  /*  total loop vertex */
  lp->lcvn  = 0; 
  lp->lvn   = 0;
  lp->splv  = (Splv *) NULL;
  lp->eplv  = (Splv *) NULL;

  /*  total loop edge */
  lp->len   = 0;
  lp->sple  = (Sple *) NULL;
  lp->eple  = (Sple *) NULL;

  /* id */
  lp->no   = ppd->lid;
  
  /* open flag */
  lp->type = CLOSEDLOOP;

  /* links to _hedge */
  lp->hed  = (HEdge *) NULL;
  
  lp->col   = LOOPBLUE;
  
  ++( ppd->ln );
  ++( ppd->lid );
  
  return lp;
}

Splp *find_ppdloop( Sppd *ppd, Spvt *vt )
{
  Splv *lv;
  Splp *lp;
  
  for ( lp = ppd->splp; lp != (Splp *) NULL; lp = lp->nxt ) {

    for ( lv = lp->splv; lv != (Splv *) NULL; lv = lv->nxt ) {
      if ( lv->vt == vt ) return lp;
    }
  }
  return (Splp *) NULL;
}

void free_splp( Splp *lp )
{
  Splv *lv, *nlv;
  Sple *le, *nle;
  void free_ppdloopvertex(Splv *, Splp *);
  void free_ppdloopedge(Sple *, Splp *);
  
  if (lp == (Splp *) NULL) return;
  
  /* free loopvertex */
  for (lv = lp->splv; lv != (Splv *) NULL; lv = nlv) {
/*     display("\taa\n"); */
    nlv = lv->nxt;
    --( lv->vt->spn );
    free_ppdloopvertex( lv, lp );
  }
  
  /* free loopedge */
  for (le = lp->sple; le != (Sple *) NULL; le = nle) {
    nle = le->nxt;
    free_ppdloopedge(le, lp);
  }
  
  free( lp );
}

void free_ppdloop(Splp *lp, Sppd *ppd)
{
  Splv *lv, *nlv;
  Sple *le, *nle;
  void free_ppdloopvertex(Splv *, Splp *);
  void free_ppdloopedge(Sple *, Splp *);
			 
  if (lp == (Splp *) NULL) return;
  
  /* free loopvertex */
  for (lv = lp->splv; lv != (Splv *) NULL; lv = nlv) {
    nlv = lv->nxt;
    free_ppdloopvertex(lv, lp);
  }
  
  /* free loopedge */
  for (le = lp->sple; le != (Sple *) NULL; le = nle) {
    nle = le->nxt;
    free_ppdloopedge(le, lp);
  }
  
  if (ppd->splp == lp) {
    if ((ppd->splp = lp->nxt) != (Splp *) NULL)
      lp->nxt->prv = (Splp *) NULL;
    else {
      ppd->eplp = (Splp *) NULL;
    }
  } else if (ppd->eplp == lp) {
    lp->prv->nxt = (Splp *) NULL;
    ppd->eplp = lp->prv;
    
  } else {
    lp->prv->nxt = lp->nxt;
    lp->nxt->prv = lp->prv;
  }
  
  free( lp );
  --( ppd->ln );
}

/* loop vertex */
Splv *create_ppdloopvertex( Splp *loop )
{
  Splv *lv;

  lv = (Splv *) malloc(sizeof(Splv));
  
  lv->nxt = (Splv *) NULL;
  if (loop->splv == (Splv *) NULL) {
    lv->prv = (Splv *) NULL;
    loop->eplv = loop->splv = lv;
  } else {
    lv->prv    = loop->eplv;
    loop->eplv = loop->eplv->nxt = lv;
  }

  /* id */
  lv->no   = loop->lvn;
  
  /* back loop */
/*   lv->bplp = loop; */
  
  /* vertex */
  lv->vt  = (Spvt *) NULL;
  
  /* vertex type */
  lv->type = LOOPVT_CORNER;

  /* links to hgvt ( for hloop ) */
  lv->hgvt = (HGvt *) NULL;
  
  ++( loop->lvn );

  return lv;
}

Splv *find_ppdloopvertex( Splp *lp, Spvt *vt )
{
  Splv *lv;

  if ( lp == (Splp *) NULL ) return (Splv *) NULL;
  
  for ( lv = lp->splv; lv != (Splv *) NULL; lv = lv->nxt ) {
    if ( lv->vt == vt ) return lv;
  }
  return (Splv *) NULL;
}

void free_ppdloopvertex( Splv *lv, Splp *loop )
{
  if (lv == (Splv *) NULL) return;

  lv->vt->lp = (Splp *) NULL;
  
  if (loop->splv == lv) {
    if ((loop->splv = lv->nxt) != (Splv *) NULL)
      lv->nxt->prv = (Splv *) NULL;
    else {
      loop->eplv = (Splv *) NULL;
    }
  } else if (loop->eplv == lv) {
    lv->prv->nxt = (Splv *) NULL;
    loop->eplv = lv->prv;
    
  } else {
    lv->prv->nxt = lv->nxt;
    lv->nxt->prv = lv->prv;
  }
  
  free(lv);
  --( loop->lvn );
}

/* loop edge */
Sple *create_ppdloopedge(Splp *loop)
{
  Sple *le;

  le = (Sple *) malloc(sizeof(Sple));
  
  le->nxt = (Sple *) NULL;
  if (loop->sple == (Sple *) NULL) {
    le->prv = (Sple *) NULL;
    loop->eple = loop->sple = le;
  } else {
    le->prv    = loop->eple;
    loop->eple = loop->eple->nxt = le;
  }

  /* id */
  le->no   = loop->len;
  
  /* edge */
  le->ed  = (Sped *) NULL;
  
  /* links to hged ( for hloop ) */
/*   le->hged = (HGed *) NULL; */
  
  ++( loop->len );

  return le;
}

void free_ppdloopedge(Sple *le, Splp *loop)
{
  if (le == (Sple *) NULL) return;
  
  if (loop->sple == le) {
    if ((loop->sple = le->nxt) != (Sple *) NULL)
      le->nxt->prv = (Sple *) NULL;
    else {
      loop->eple = (Sple *) NULL;
    }
  } else if (loop->eple == le) {
    le->prv->nxt = (Sple *) NULL;
    loop->eple = le->prv;
    
  } else {
    le->prv->nxt = le->nxt;
    le->nxt->prv = le->prv;
  }
  
  free(le);
  --( loop->len );
}

Splp *reverse_ppdloop( Splp *lp )
{
  Splp *nlp;
  Splv *lv, *nlv;
  Splp *create_splp( void );
  
  nlp = create_splp();
  nlp->type  = SHORTESTPATH;

  lv = lp->eplv;
  while (1) {
    
    nlv = create_ppdloopvertex( nlp );
    nlv->vt = lv->vt;

    if ( lv == lp->splv ) break;
    lv = lv->prv;

  }
  
  return nlp;
}