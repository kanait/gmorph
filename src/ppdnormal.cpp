//
// ppdnormal.cpp
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
  Normal
****************************************/

Spnm *create_ppdnormal(Sppd *ppd)
{
  Spnm *nm;

  nm = (Spnm *) malloc(sizeof(Spnm));

  nm->nxt = (Spnm *) NULL;
  if (ppd->spnm == (Spnm *) NULL) {
    nm->prv = (Spnm *) NULL;
    ppd->epnm = ppd->spnm = nm;
  } else {
    nm->prv   = ppd->epnm;
    ppd->epnm = ppd->epnm->nxt = nm;
  }

  /* id */
  nm->no   = ppd->nid;
  /* back solid */
  nm->bpso = (Spso *) NULL;
  /* save id */
  nm->sid  = SMDNULL;
  ++( ppd->nn );
  ++( ppd->nid );

  return nm;
}

void free_ppdnormal(Spnm *nm, Sppd *ppd)
{
  if (nm == (Spnm *) NULL) return;
  
  if (ppd->spnm == nm) {
    if ((ppd->spnm = nm->nxt) != (Spnm *) NULL)
      nm->nxt->prv = (Spnm *) NULL;
    else {
      ppd->epnm = (Spnm *) NULL;
    }
  } else if (ppd->epnm == nm) {
    nm->prv->nxt = (Spnm *) NULL;
    ppd->epnm = nm->prv;
  } else {
    nm->prv->nxt = nm->nxt;
    nm->nxt->prv = nm->prv;
  }

  free(nm);
  --( ppd->nn );
}

void ppdnorm( Sppd *ppd )
{
  int  cnt;
  Spfc *fc;
  Sphe *he;
  Spvt *vt;
  Spnm *nm, *normal, *nnormal;
  Vtnm *vtnm;
  Vec  newnorm;
  Vtnm *create_vtxnm( Spvt *, Spnm * );
  Vec  *V3Normalize( Vec * );
  Vtnm *find_ppdnormal( Spvt *, Vec *, Sppd * );
  void free_ppdvertexnormal( Spvt * );
  
  /* normal */
  for (normal = ppd->spnm; normal != (Spnm *) NULL; normal = nnormal) {
    nnormal = normal->nxt;
    free_ppdnormal(normal, ppd);
  }
  ppd->spnm = ppd->epnm = (Spnm *) NULL;
  ppd->nn = 0;
  ppd->nid = 0;
  
  for ( fc = ppd->spfc; fc != (Spfc *) NULL; fc = fc->nxt ) {
    
    he = fc->sphe;
    do {
      
      vt = he->vt;
      if ( (vtnm = find_ppdnormal( vt, &(fc->nrm), ppd)) == NULL ) {
	nm = create_ppdnormal( ppd );
	nm->bpso = ppd->spso;
	nm->vec.x = fc->nrm.x; nm->vec.y = fc->nrm.y; nm->vec.z = fc->nrm.z;
	(void) create_vtxnm( vt, nm );
	he->nm = nm;
	
      } else {
	
	/* update normal */
	he->nm = vtnm->nm;
	cnt = vtnm->cnt + 1;
	newnorm.x = ( (double) vtnm->cnt * he->nm->vec.x + fc->nrm.x ) / (double) cnt ;
	newnorm.y = ( (double) vtnm->cnt * he->nm->vec.y + fc->nrm.y ) / (double) cnt ;
	newnorm.z = ( (double) vtnm->cnt * he->nm->vec.z + fc->nrm.z ) / (double) cnt ;
	V3Normalize( &newnorm );
	he->nm->vec.x = newnorm.x;
	he->nm->vec.y = newnorm.y;
	he->nm->vec.z = newnorm.z;
	vtnm->cnt = cnt;
	
      }
    } while ( (he = he->nxt) != fc->sphe );
  }

  for ( vt = ppd->spvt; vt != (Spvt *) NULL; vt = vt->nxt ) {
    free_ppdvertexnormal( vt );
  }
}
