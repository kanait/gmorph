//
// sellist.cpp
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

/**************************************
 SelList Functions 
**************************************/

static SelList *create_sellist( ScreenAtr *screen )
{
  SelList *sl;

  sl = (SelList *) malloc(sizeof(SelList));

  sl->nxt = (SelList *) NULL;
  if (screen->sel_first == (SelList *) NULL) {
    sl->prv = (SelList *) NULL;
    screen->sel_last = screen->sel_first = sl;
  } else {
    sl->prv = screen->sel_last;
    screen->sel_last = screen->sel_last->nxt = sl;
  }

  sl->pid = SMDNULL;
  sl->vt  = (Spvt *) NULL;
  sl->hvt = (HVertex *) NULL;
  sl->hfc = (HFace *) NULL;
  sl->fc  = (Spfc *) NULL;
  sl->lp  = (Splp *) NULL;
  
  ++(screen->n_sellist);

  return sl;
}

static void free_sellist(SelList *sl, ScreenAtr *screen)
{
  Spvt    *vt;
  HVertex *hvt;
  HFace   *hfc;
  Spfc    *fc;
  Splp    *lp;

  if (sl == (SelList *) NULL) return;
  if (screen == (ScreenAtr *) NULL) return;

  /* ppd vertex */
  if ( (vt = sl->vt) != (Spvt *) NULL ) {
    
    vt->col = PNTGREEN;
    if ( vt->sp_type == SP_VERTEX_HVERTEX ) {
      hvt = vt->hvt;
      hvt->col = PNTGREEN;
    }

  }
  sl->vt = (Spvt *) NULL;

  if ( (hvt = sl->hvt) != (HVertex *) NULL ) {
    
    hvt->col = PNTGREEN;
    hvt->vt1->col = PNTGREEN;
    hvt->vt2->col = PNTGREEN;
    
  }
  sl->hvt = (HVertex *) NULL;

  /* hppd face */
  if ( (hfc = sl->hfc) != (HFace *) NULL ) {

    hfc->col = FACEBLUE;

  }
  
  if ( (fc = sl->fc) != (Spfc *) NULL ) {

    fc->col = FACEBLUE;

  }
  
  if ( (lp = sl->lp) != (Splp *) NULL ) {

    lp->col = LOOPBLUE;

  }
  
  /* cut links */
  if (screen->sel_first == sl) {
    if ((screen->sel_first = sl->nxt) != (SelList *) NULL)
      sl->nxt->prv = (SelList *) NULL;
    else
      screen->sel_last = (SelList *) NULL;
  } else if (screen->sel_last == sl) {
    sl->prv->nxt = (SelList *) NULL;
    screen->sel_last = sl->prv;
  } else {
    sl->prv->nxt = sl->nxt;
    sl->nxt->prv = sl->prv;
  }

  free(sl);
  --(screen->n_sellist);
}

/* create select list (ppd vertex) */
SelList *create_selectlist_vt( ScreenAtr * screen, Spvt *vt )
{
  SelList *sl;
  HVertex *hvt;

  if (vt == (Spvt *) NULL)
    return (SelList *) NULL;

  sl = create_sellist( screen );

  sl->vt = vt;
  
  /* change color */
  vt->col = PNTRED;
  if ( vt->sp_type == SP_VERTEX_HVERTEX ) {
    hvt = vt->hvt; 
	if ( hvt != NULL ) hvt->col = PNTRED;
  }

//  displayinfo("(Screen No.%d) Vertex No.%d is selected.\n", screen->no+1, vt->no );
  screen->sellist_flag = SMD_ON;

  return sl;
}

/* create select list (ppd loop) */
SelList *create_selectlist_hvt(ScreenAtr * screen, HVertex *hvt)
{
  SelList *sl;

  if (hvt == (HVertex *) NULL) return (SelList *) NULL;

  sl = create_sellist(screen);
  sl->hvt = hvt;
  
  /* change color */
  hvt->col = PNTRED;
  hvt->vt1->col = PNTRED;
  hvt->vt2->col = PNTRED;

//  displayinfo("(Screen No.%d) CVP No.%d is selected.\n", screen->no+1, hvt->no );
  screen->sellist_flag = SMD_ON;

  return sl;
}

/* create select list (ppd loop) */
SelList *create_selectlist_hface( ScreenAtr * screen, HFace *hfc )
{
  SelList *sl;

  if (hfc == (HFace *) NULL) return (SelList *) NULL;
  
  sl = create_sellist( screen );
  sl->hfc = hfc;
  
  /* change color */
  hfc->col = FACERED;
  
//  displayinfo("(Screen No.%d) PCM Face No.%d is selected.\n", screen->no+1, hfc->no );
  screen->sellist_flag = SMD_ON;

  return sl;
}

/* create select list (ppd loop) */
SelList *create_selectlist_ppdface( ScreenAtr * screen, Spfc *fc )
{
  SelList *sl;

  if (fc == (Spfc *) NULL) return (SelList *) NULL;
  
  sl = create_sellist( screen );
  sl->fc = fc;
  
  /* change color */
  fc->col = FACERED;

  screen->sellist_flag = SMD_ON;
//  displayinfo("(Screen No.%d) PPD Face No.%d is selected.\n", screen->no+1, fc->no );

  return sl;
}

/* create select list (ppd loop) */
SelList *create_selectlist_lp( ScreenAtr * screen, Splp *lp )
{
  SelList *sl;

  if ( lp == (Splp *) NULL) return (SelList *) NULL;

  sl = create_sellist( screen );

  sl->lp = lp;
  
  /* change color */
  lp->col = PNTRED;

//  displayinfo("(Screen No.%d) Loop No.%d is selected.\n", screen->no+1, lp->no );
  screen->sellist_flag = SMD_ON;

  return sl;
}


SelList *list_selectlist(ScreenAtr * screen, Id id)
{
  SelList *sl;

  for (sl = screen->sel_first; sl != (SelList *) NULL; sl = sl->nxt) {
    if (sl->pid == id)
      return sl;
  }
  return (SelList *) NULL;
}

void FreeSelectList( ScreenAtr *screen )
{
  SelList *sl, *nsl;

  if (screen->sel_first == (SelList *) NULL)
    return;

  nsl = (SelList *) NULL;
  for (sl = screen->sel_first; sl != (SelList *) NULL; sl = nsl) {
    nsl = sl->nxt;
    free_sellist( sl, screen );
  }
  screen->sel_first = screen->sel_last = (SelList *) NULL;
  screen->sellist_flag = SMD_OFF;
  screen->n_sellist = 0;
  
  screen->areaflag  = SMD_OFF;
  screen->areaorg.x = 0.0;
  screen->areaorg.y = 0.0;
  screen->areaatv.x = 0.0;
  screen->areaatv.y = 0.0;
}
