//
// ppdface.cpp
//
// Copyright (c) 1997 Takashi Kanai
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

/***************************************
  Face
****************************************/

/* face */
Spfc *create_ppdface(Sppd *ppd)
{
  Spfc *fc;

  fc = (Spfc *) malloc(sizeof(Spfc));
  
  fc->nxt = (Spfc *) NULL;

  if (ppd->spfc == (Spfc *) NULL) {
    fc->prv = (Spfc *) NULL;
    ppd->epfc = ppd->spfc = fc;
  } else {
    fc->prv   = ppd->epfc;
    ppd->epfc = ppd->epfc->nxt = fc;
  }

  /* half edge */
  fc->hen   = 0;
  fc->sphe  = (Sphe *) NULL;
  /* back part */
  fc->bppt  = (Sppt *) NULL;
  /* back solid */
  fc->bpso  = (Spso *) NULL;
  /* id */
  fc->no    = ppd->fid;
  fc->sid   = SMDNULL;
  /* face color */
  fc->col   = FACEBLUE;
  /* quadtree */
/*   fc->qf    = (QFace *) NULL; */

  /* for copy_ppd */
  fc->nfc   = (Spfc *) NULL;

  ++( ppd->fn );
  ++( ppd->fid );

  return fc;
}

Spfc *create_ppdface_hedge(Sppd *ppd, Spvt *v0, Spvt *v1, Spvt *v2,
			   Sped *e0, Sped *e1, Sped *e2)
{
  Spfc *fc;
  Sphe *he;
  Spfc *create_ppdface(Sppd *);
  Sphe *create_ppdhalfedge(Spfc *);
  void calc_fnorm(Spfc *);

  fc = create_ppdface(ppd);

  /* make halfedge */
  he = create_ppdhalfedge(fc);
  he->vt = v0;
  he->ed = e0;
  
  if (e0->lf == (Spfc *) NULL) {
    e0->lf = fc;
  } else {
    e0->rf = fc;
  }
  he = create_ppdhalfedge(fc);
  he->vt = v1;
  he->ed = e1;
  if (e1->lf == (Spfc *) NULL) {
    e1->lf = fc;
  } else {
    e1->rf = fc;
  }
  he = create_ppdhalfedge(fc);
  he->vt = v2;
  he->ed = e2;
  if (e2->lf == (Spfc *) NULL) {
    e2->lf = fc;
  } else {
    e2->rf = fc;
  }

  calc_fnorm(fc);
  
  return fc;
}

/* this function is valid for only triangle faces */
Spvt *other_vertices_face_left( Spfc *fc, Spvt *vt )
{
  Sphe *he;
  
  he = fc->sphe;

  do {
    if ( he->vt == vt ) {
      return he->nxt->vt;
    }
  } while ( (he = he->nxt) != fc->sphe );

  return NULL;
}

Spvt *other_vertices_face_right( Spfc *fc, Spvt *vt )
{
  Sphe *he;
  
  he = fc->sphe;

  do {
    if ( he->vt == vt ) {
      return he->prv->vt;
    }
  } while ( (he = he->nxt) != fc->sphe );
  return NULL;
}

void free_ppdface( Spfc *fc, Sppd *ppd )
{
  Sphe   *he;
  Sphe   *free_ppdhalfedge( Sphe *, Spfc * );
  
  if (fc == (Spfc *) NULL) return;
  
  /* free halfedge */
  he = fc->sphe;
  while (he != (Sphe *) NULL) {
    he = free_ppdhalfedge( he, fc );
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

void free_ppdface_withqtree(Spfc *fc, Sppd *ppd)
{
//  QFace *qf;
//  QTree *qt;
//  void  delete_qtree_face(QFace *, QTree *);
  void  free_ppdface(Spfc *, Sppd *);
  
/*   if (fc->qf != (QFace *) NULL) { */
/*     qf = fc->qf; */
/*     qt = qf->qt; */
/*     delete_qtree_face(qf, qt); */
/*   } */
  free_ppdface(fc, ppd);
}

/* halfedge */
Sphe *create_ppdhalfedge( Spfc *fc )
{
  Sphe *he;

  he = (Sphe *) malloc(sizeof(Sphe));
  
  if (fc->sphe == (Sphe *) NULL) {	/* first */
    fc->sphe = he;
    he->prv  = he;
    he->nxt  = he;
  } else {
    he->prv  = fc->sphe->prv;
    he->nxt  = fc->sphe;
    fc->sphe->prv->nxt = he;
    fc->sphe->prv = he;
  }
  /* id */
  he->no   = fc->hen;
  /* back face */
  he->bpfc = fc;
  /*he->mate = (Sphe *) NULL;*/
  /* edge */
  he->ed   = (Sped *) NULL;
  /* start vertex */
  he->vt  = (Spvt *) NULL;
  /* start normal */
  he->nm  = (Spnm *) NULL;
  ++( fc->hen );

  return he;
}

Sphe *free_ppdhalfedge( Sphe *he, Spfc *face )
{
  Sped *ed;
  Sphe *newhe;

  ed = he->ed;

  if ( ed != NULL ) {
    if ( ed->lf == face ) {
      ed->lf = (Spfc *) NULL;
      --(ed->fn);
      he->ed = NULL;
    } else if ( ed->rf == face ) {
      ed->rf = (Spfc *) NULL;
      --(ed->fn);
      he->ed = NULL;
    }
  }
  
  if ( he->nxt == he ) {
    free( he );
    --( face->hen );
    return (Sphe *) NULL;
  } else {
    newhe = he->nxt;
    he->prv->nxt = he->nxt;
    he->nxt->prv = he->prv;
    free(he);
    --(face->hen);
    return newhe;
  }
}

void makenull_ppdhalfedge(Sped *ed, Spfc *fc)
{
  Sphe *he;
  
  he = fc->sphe;
  do {
    if ( ed->lf == fc ) {
      ed->lf = (Spfc *) NULL;
      return;
    }
    if (ed->rf == fc) {
      ed->rf = (Spfc *) NULL;
      return;
    }
  } while ((he = he->nxt) != fc->sphe);
}

Spfc *find_ppdface_ppdedge( Sped *ed, Spvt *sv, Spvt *ev )
{
  if ( ed == NULL ) return NULL;

  if ( (ed->sv == sv) && (ed->ev == ev ) ) {
    return ed->lf;
  } else if ( (ed->sv == ev) && (ed->ev == sv ) ) {
    return ed->rf;
  }
  return NULL;
}

Sphe *find_hedge_edge(Sped *ed, Spfc *fc)
{
  Sphe *he;
  
  he = fc->sphe;
  do {
    if ( ed->lf == fc ) return he;
    if ( ed->rf == fc ) return he;
  } while ((he = he->nxt) != fc->sphe);
  return (Sphe *) NULL;
}

void calc_fnorm(Spfc *face)
{
  Sphe   *h;
  Spvt   *v1, *v2, *v3;
  Vec    vec1, vec2, vec3, vec4, vec5;
  Vec    *V3Sub(Vec *, Vec *, Vec *);
  Vec    *V3Cross(Vec *, Vec *, Vec *);
  Vec    *V3Normalize(Vec *);

  h = face->sphe;
  v1 = h->vt;
  v2 = h->nxt->vt;
  v3 = h->nxt->nxt->vt;
  vec1.x = v1->vec.x;
  vec1.y = v1->vec.y;
  vec1.z = v1->vec.z;
  vec2.x = v2->vec.x;
  vec2.y = v2->vec.y;
  vec2.z = v2->vec.z;
  vec3.x = v3->vec.x;
  vec3.y = v3->vec.y;
  vec3.z = v3->vec.z;
  V3Sub( &vec2, &vec1, &vec4 );
  V3Sub( &vec3, &vec1, &vec5 );
  V3Cross( &vec4, &vec5, &(face->nrm) );
  V3Normalize( &(face->nrm) );
}

/* "Cancel" functions */
/* 
void cancel_create_ppdface( void )
{
  ScreenAtr *screen1, *screen2;
  void    FreeSelectList(ScreenAtr *);

  screen1 = &(swin->screenatr);
  screen2 = &(swin->screenatr);

  FreeSelectList( screen1 );
  FreeSelectList( screen2 );
}

void cancel_delete_ppdface( void )
{
  ScreenAtr *screen1, *screen2;
  void    FreeSelectList(ScreenAtr *);

  screen1 = &(swin->screenatr);
  screen2 = &(swin->screenatr);

  FreeSelectList( screen1 );
  FreeSelectList( screen2 );
}
*/
