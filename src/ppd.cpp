//
// ppd.cpp
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

#include <math.h>
#include "smd.h"

/***************************************
  Ppd functions
****************************************/

Sppd *create_ppd(void)
{
  double angle;
  Sppd *ppd;
  
  if ((ppd = (Sppd *) malloc(sizeof(Sppd))) == (Sppd *) NULL) {
    return (Sppd *) NULL;
  }
  
  /* solid */
  ppd->sn   = 0;
  ppd->sid  = 0;
  ppd->spso = (Spso *) NULL;
  ppd->epso = (Spso *) NULL;
  
  /* part */
  ppd->pn   = 0;
  ppd->pid  = 0;
  ppd->sppt = (Sppt *) NULL;
  ppd->eppt = (Sppt *) NULL;
  
  /* face */
  ppd->fn   = 0;
  ppd->fid  = 0;
  ppd->spfc = (Spfc *) NULL;
  ppd->epfc = (Spfc *) NULL;
  
  /* normal */
  ppd->nn   = 0;
  ppd->nid  = 0;
  ppd->spnm = (Spnm *) NULL;
  ppd->epnm = (Spnm *) NULL;
  
  /* vertex */
  ppd->vn   = 0;
  ppd->vid  = 0;
  ppd->spvt = (Spvt *) NULL;
  ppd->epvt = (Spvt *) NULL;
  
  /* edge */
  ppd->en   = 0;
  ppd->eid  = 0;
  ppd->sped = (Sped *) NULL;
  ppd->eped = (Sped *) NULL;
  
  /* loop */
  ppd->ln    = 0;
  ppd->lid   = 0;
  ppd->splp  = (Splp *) NULL;
  ppd->eplp  = (Splp *) NULL;
  
  /* qtree */
  ppd->qn    = 0;
  ppd->qt    = (QTree *) NULL;
  ppd->maxqtlevel = 0;

  /* scale, center */
  ppd->scale = 0.0;
  ppd->center.x = 0.0;
  ppd->center.y = 0.0;
  ppd->center.z = 0.0;

  /* for morphing */
  ppd->mvec1 = (Vec *) NULL;
  ppd->mvec2 = (Vec *) NULL;
  ppd->mcalc1 = (unsigned short *) NULL;
  ppd->mcalc2 = (unsigned short *) NULL;
  
  angle = 40.0;
  ppd->smooth_angle = cos( angle * SMDPI / 180.0 );
  return ppd;
}

void free_ppd(Sppd *ppd)
{
  Spso *solid, *nsolid;
  Sppt *part, *npart;
  Spfc *face, *nface;
  Spnm *normal, *nnormal;
  Spvt *vertex, *nvertex;
  Sped *edge, *nedge;
  Splp *loop, *nloop;
  void free_ppdedge(Sped *, Sppd *);
  void free_ppdface(Spfc *, Sppd *);
  void free_ppdloop(Splp *, Sppd *);
  void free_ppdnormal(Spnm *, Sppd *);
  void free_ppdvertex(Spvt *, Sppd *);
  void free_ppdpart(Sppt *, Sppd *);
  void free_ppdsolid(Spso *, Sppd *);
//  void free_ppdqtree(Sppd *);

  if ( ppd == (Sppd *) NULL ) return;

  if ( ppd->mvec1 != (Vec *) NULL ) free(ppd->mvec1);
  if ( ppd->mvec2 != (Vec *) NULL ) free(ppd->mvec2);
  if ( ppd->mcalc1 != (unsigned short *) NULL ) free(ppd->mcalc1);
  if ( ppd->mcalc2 != (unsigned short *) NULL ) free(ppd->mcalc2);

  /* quadcree */
//  if (ppd->qt != (QTree *) NULL) {
//    free_ppdqtree(ppd);
//  }
  
  /* edge */
  for (edge = ppd->sped; edge != (Sped *) NULL; edge = nedge) {
    nedge = edge->nxt;
    free_ppdedge(edge, ppd);
  }
  /* face */
  for (face = ppd->spfc; face != (Spfc *) NULL; face = nface) {
    nface = face->nxt;
    free_ppdface(face, ppd);
  }
  /* loop */
  for (loop = ppd->splp; loop != (Splp *) NULL; loop = nloop) {
    nloop = loop->nxt;
    free_ppdloop(loop, ppd);
  }
  /* normal */
  for (normal = ppd->spnm; normal != (Spnm *) NULL; normal = nnormal) {
    nnormal = normal->nxt;
    free_ppdnormal(normal, ppd);
  }
  /* vertex */
  for (vertex = ppd->spvt; vertex != (Spvt *) NULL; vertex = nvertex) {
    nvertex = vertex->nxt;
    free_ppdvertex(vertex, ppd);
  }
  /* part */
  for (part = ppd->sppt; part != (Sppt *) NULL; part = npart) {
    npart = part->nxt;
    free_ppdpart(part, ppd);
  }
  /* solid */
  for (solid = ppd->spso; solid != (Spso *) NULL; solid = nsolid) {
    nsolid = solid->nxt;
    free_ppdsolid(solid, ppd);
  }

  /* ppd */
  free(ppd);
}

void reset_ppd(Sppd *ppd)
{
  Spvt *vt;
  Sped *ed;
  void free_ppdedgevertex(Sped *);
  
  for ( vt = ppd->spvt; vt != (Spvt *) NULL; vt = vt->nxt ) {
    vt->mvt = (Spvt *) NULL;
  }

  for ( ed = ppd->sped; ed != (Sped *) NULL; ed = ed->nxt ) {
    free_ppdedgevertex(ed);
    
  }
}

Sppd *copy_ppd( Sppd *ppd )
{
  Sppd  *nppd;
  Spvt  *vt, *nvt;
  Sped  *ed, *ned;
  Spfc  *fc, *nfc;
  Sphe  *he, *nhe;
//  Vted  *ved;
  void  clear_newppd_links( Sppd * );
  Sppd  *create_ppd( void );
  Spfc  *create_ppdface( Sppd * );
  Spvt  *create_ppdvertex( Sppd * );
  Sped  *create_ppdedge( Sppd * );
  Sphe  *create_ppdhalfedge( Spfc * );
  Vted  *create_vtxed( Spvt *, Sped * );

  if ( ppd == (Sppd *) NULL ) return (Sppd *) NULL;
  
  clear_newppd_links( ppd );
  /* initialize new ppd */
  nppd = create_ppd();

  /* vertex */
  for ( vt = ppd->spvt; vt != (Spvt *) NULL; vt = vt->nxt ) {
    
    if ( (vt->sp_type != SP_VERTEX_STEINER) && (vt->sp_type != SP_VERTEX_BOUNDARY) ) {
      nvt = create_ppdvertex( nppd );
      nvt->sp_type = vt->sp_type;
      nvt->vec.x = vt->vec.x;
      nvt->vec.y = vt->vec.y;
      nvt->vec.z = vt->vec.z;
      nvt->atr   = vt->atr;
      vt->nvt = nvt;
      if ( vt->sp_type == SP_VERTEX_HVERTEX ) {
	nvt->hvt = vt->hvt;
      }
    }
    
  }
  
  /* edge */
  for ( ed = ppd->sped; ed != (Sped *) NULL; ed = ed->nxt ) {
    
    if ( (ed->sp_type != SP_EDGE_STEINER) ) {
      ned = create_ppdedge( nppd );
      ned->sp_type = ed->sp_type;
      ned->atr     = ed->atr;
      ed->ned = ned;
    }
    
  }
      
  /* face */
  for ( fc = ppd->spfc; fc != (Spfc *) NULL; fc = fc->nxt ) {

    nfc = create_ppdface( nppd );
    fc->nfc = nfc;
    /* create halfedges */
    he = fc->sphe;
    do {
      nhe = create_ppdhalfedge( nfc );
      /* links */
      nhe->vt = he->vt->nvt;
      nhe->ed = he->ed->ned;
    } while ( (he = he->nxt) != fc->sphe );

  }

  /* create vertex, edge, links */
  
  /* edge */
  for ( ed = ppd->sped; ed != (Sped *) NULL; ed = ed->nxt ) {

    if ( (ed->sp_type != SP_EDGE_STEINER) ) {
      ned = ed->ned;
      ned->sv = ed->sv->nvt;
      ned->ev = ed->ev->nvt;
      create_vtxed( ned->sv, ned );
      create_vtxed( ned->ev, ned );
      ned->rf = ( ed->rf != (Spfc *) NULL ) ? ed->rf->nfc : (Spfc *) NULL;
      ned->lf = ( ed->lf != (Spfc *) NULL ) ? ed->lf->nfc : (Spfc *) NULL;
    }
    
  }
  
  clear_newppd_links( ppd );
      
  return nppd;
}

void clear_newppd_links( Sppd *ppd )
{
  Spvt *vt;
  Spfc *fc;
  Sped *ed;

  if ( ppd == (Sppd *) NULL ) return;
  
  for ( vt = ppd->spvt; vt != (Spvt *) NULL; vt = vt->nxt ) {
    vt->nvt = (Spvt *) NULL;
  }
  for ( ed = ppd->sped; ed != (Sped *) NULL; ed = ed->nxt ) {
    ed->ned = (Sped *) NULL;
  }
  for ( fc = ppd->spfc; fc != (Spfc *) NULL; fc = fc->nxt ) {
    fc->nfc = (Spfc *) NULL;
  }
}
    
void calc_ppd_boundary( Sppd *ppd )
{
  Sped  *e;
//  Spvt  *sv, *ev;
  
  for ( e = ppd->sped; e != (Sped *) NULL; e = e->nxt ) {

    if ( (e->lf == (Spfc *) NULL) || (e->rf == (Spfc *) NULL) ) {
      e->atr     = EDGEBOUNDARY;
      e->sv->atr = VTXEXTERNAL;
      e->ev->atr = VTXEXTERNAL;
    } else {
      e->atr = EDGEINTERNAL;
    }
    
  }
}

void normalize_ppd( Sppd *ppd )
{
  int  i;
  Spvt *v;
  double maxlength;
  double xlength, ylength, zlength;
  double maxx, minx, maxy, miny, maxz, minz;
  
  for (i = 0, v = ppd->spvt; v != (Spvt *) NULL; ++i, v = v->nxt) {
    if (i) {
      if (v->vec.x > maxx) maxx = v->vec.x;
      if (v->vec.x < minx) minx = v->vec.x;
      if (v->vec.y > maxy) maxy = v->vec.y;
      if (v->vec.y < miny) miny = v->vec.y;
      if (v->vec.z > maxz) maxz = v->vec.z;
      if (v->vec.z < minz) minz = v->vec.z;
    }	else {
      maxx = minx = v->vec.x;
      maxy = miny = v->vec.y;
      maxz = minz = v->vec.z;
    }
  }

  xlength = maxx - minx;
  ylength = maxy - miny;
  zlength = maxz - minz;

  if (xlength > ylength)   maxlength = xlength;
  else                     maxlength = ylength;
  if (zlength > maxlength) maxlength = zlength;

  ppd->scale = 1.5 / maxlength;
  ppd->center.x = (maxx + minx) / 2.0;
  ppd->center.y = (maxy + miny) / 2.0;
  ppd->center.z = (maxz + minz) / 2.0;

  for (i = 0, v = ppd->spvt; v != (Spvt *) NULL; ++i, v = v->nxt) {
    v->vec.x = (v->vec.x - ppd->center.x) * ppd->scale;
    v->vec.y = (v->vec.y - ppd->center.y) * ppd->scale;
    v->vec.z = (v->vec.z - ppd->center.z) * ppd->scale;
  }
}

void unnormalize_ppd( Sppd *ppd )
{
  Spvt *v;
  
  for ( v = ppd->spvt; v != (Spvt *) NULL; v = v->nxt ) {
    v->vec.x = v->vec.x / ppd->scale +  ppd->center.x;
    v->vec.y = v->vec.y / ppd->scale +  ppd->center.y;
    v->vec.z = v->vec.z / ppd->scale +  ppd->center.z;
  }
  
}



