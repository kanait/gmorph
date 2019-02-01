/* Copyright (c) 1997-1998 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>
#include "smd.h"
#include "sigproc.h"
#include "dspr.h"
//#include "linbcg.h"
#include "ppdvertex.h"
#include "veclib.h"

#if 0
void ppd_signal_processing( Sppd *ppd, 
			    double lambda,
			    double mu,
			    int nrepeat )
{
  int    i, j;
  double *vecx, *vecy, *vecz, *dvecx, *dvecy, *dvecz;
  Spvt *vt, *avt;
  Vted *ve;
  SparseMatrix *sml, *smm;

  /* ed->ewt */
  edge_weight( ppd );

  for ( vt = ppd->spvt; vt != NULL; vt = vt->nxt ) {

	  vt->tven = 0;
	  if ( vt->isConst == SMD_OFF ) {
		  for ( ve = vt->svted; ve != NULL; ve = ve->nxt ) {
			  avt = another_vt( ve->ed, vt );
			  if ( avt->isConst == SMD_OFF ) {
				  ++( vt->tven );
			  }
		  }
	  }
    
  }
  
//   create matrix I - lK... 
  sml = create_spmatrix_dspr( ppd, lambda );
//   create matrix I - mK...
  smm = create_spmatrix_dspr( ppd, mu );
  
  vecx  = (double *) malloc( ppd->vn * sizeof(double) );
  vecy  = (double *) malloc( ppd->vn * sizeof(double) );
  vecz  = (double *) malloc( ppd->vn * sizeof(double) );
  dvecx = (double *) malloc( ppd->vn * sizeof(double) );
  dvecy = (double *) malloc( ppd->vn * sizeof(double) );
  dvecz = (double *) malloc( ppd->vn * sizeof(double) );
  
  for ( j = 0, vt = ppd->spvt; j < ppd->vn; ++j, vt = vt->nxt ) {
    vecx[j] = vt->vec.x; vecy[j] = vt->vec.y; vecz[j] = vt->vec.z;
  }
  
  for ( i = 0; i < nrepeat; ++i ) {
    dsprsax( smm->sa, smm->ija, vecx, dvecx, smm->ncol );
    dsprsax( smm->sa, smm->ija, vecy, dvecy, smm->ncol );
    dsprsax( smm->sa, smm->ija, vecz, dvecz, smm->ncol );
    dsprsax( sml->sa, sml->ija, dvecx, vecx, sml->ncol );
    dsprsax( sml->sa, sml->ija, dvecy, vecy, sml->ncol );
    dsprsax( sml->sa, sml->ija, dvecz, vecz, sml->ncol );
  }
  
  for ( j = 0, vt = ppd->spvt; j < ppd->vn; ++j, vt = vt->nxt ) {
    vt->vec.x = dvecx[j]; vt->vec.y = dvecy[j]; vt->vec.z = dvecz[j];
  }

  free( vecx ); free( vecy ); free( vecz ); 
  free( dvecx ); free( dvecy ); free( dvecz );
  free_sparsematrix( sml );
  free_sparsematrix( smm );

}
#endif

SparseMatrix *create_spmatrix_dspr( Sppd *ppd, double coefs )
{
  int i, j, k;
  Spvt *vt, *avt;
  Vted *vted;
  double sum_wt, *vtwt;
  SparseMatrix *sm;

  sm = init_sparsematrix( ppd->vn );
  
  /* decide number of array */
  sm->narray = ppd->vn + 1; 
  for ( vt = ppd->spvt; vt != NULL; vt = vt->nxt ) {
    
    sm->narray += vt->tven;
    
  }

  sm->sa  = (double *) malloc( sm->narray * sizeof(double) );
  for ( i = 0; i < sm->narray; ++i ) sm->sa[i] = 0.0;
  sm->ija = (int *) malloc( sm->narray * sizeof(int) );

  /* store values */
  sm->ija[0] = sm->ncol + 1;
  j = sm->ncol;

  for ( i = 0, vt = ppd->spvt; vt != NULL; vt = vt->nxt, ++i ) {

    if ( vt->isConst == SMD_OFF ) {
      
      sm->sa[i] = 1.0 - coefs;
      
      vtwt = (double *) malloc( vt->tven * sizeof(double) );
      /* sum weights */
      sum_wt = 0.0;
      k = 0;
      for ( vted = vt->svted; vted != NULL; vted = vted->nxt ) {
	avt = another_vt( vted->ed, vt );
	if ( avt->isConst == SMD_OFF ) {
	  vtwt[k] = vted->ed->ewt;
	  sum_wt += vtwt[k];
	  ++k;
	}
      }

      /* normalize weights and store into matrix */
      k = 0;
      for ( vted = vt->svted; vted != NULL; vted = vted->nxt ) {
	avt = another_vt( vted->ed, vt );
	if ( avt->isConst == SMD_OFF ) {
	  vtwt[k] /= sum_wt;
	  ++j;
	  sm->ija[j] = avt->no;
	  sm->sa[j]  = coefs * vtwt[k];
	  ++k;
	}
      }
      
      free( vtwt );

    } else { /* constraint vertex */
      
      sm->sa[i] = 1.0;
      
    }

    sm->ija[i+1] = j+1;

  }

  return sm;
}

void edge_weight( Sppd *ppd )
{
  Sped *ed;
  double len;
  
  for ( ed = ppd->sped; ed != NULL; ed = ed->nxt ) {
    len = V3DistanceBetween2Points( &(ed->sv->vec), &(ed->ev->vec) );
    if ( fabs(len) > SMDZEROEPS ) {
      ed->ewt = 1.0 / len;
    } else {
      ed->ewt = 0;
    }
  }
}
    

