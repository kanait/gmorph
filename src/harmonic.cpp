//
// harmonic.cpp
//
// Copyright (c) 1996-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "StdAfx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>
#include "smd.h"
#include "harmonic.h"
#include "ppdedge.h"
#include "hgppd.h"
#include "linbcg.h"

#define KAPPA 1.0

#include <vector>
#include <Eigen/Sparse>
#include <Eigen/OrderingMethods>

/*******************************************************************************
  STEP 2: harmonic maps (Related functions are in "harmonic.c".)
*******************************************************************************/

void harmonic_initialize_vector_2( HGfc *hgfc, Splp *lp,
                                   Eigen::VectorXd& bx, Eigen::VectorXd& by )
{
  int    i;
  HGvt   *vt;
  Vec2d  *uvbprm;
  Sple   *le, *tle, *sle;
  Splv   *lv, *tlv, *slv, *elv;
  double sum, esum, val;
  Vec2d  sub;

  /* initialize vector */
  for ( vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt )
    {
      bx[vt->sid] = 0.0;
      by[vt->sid] = 0.0;
    //   emat->bx[vt->sid] = emat->xx[vt->sid] = 0.0;
    // emat->by[vt->sid] = emat->yy[vt->sid] = 0.0;
    }

  uvbprm = calc_uvbprm( hgfc->hgcn );

  /* calculate boundary values */

  lv = lp->splv;
  le = lp->sple;

  i = 0;
  while ( i < hgfc->hgcn ) {

    slv = lv;
    sle = le;
    sum = 0.0;

    while ( 1 ) {
      sum += le->ed->length;
      lv = lv->nxt;
      le = le->nxt;
      if ( lv == (Splv *) NULL ) {
        elv = lp->splv;
        break;
      }
      if ( lv->vt->sp_type == SP_VERTEX_HVERTEX ) {
        elv = lv;
        break;
      }
    }

    esum = 0.0;
    tlv = slv;
    tle = sle;
    sub.x = uvbprm[i+1].x - uvbprm[i].x;
    sub.y = uvbprm[i+1].y - uvbprm[i].y;
    while ( 1 ) {

      val = esum / sum;
      bx[ tlv->hgvt->sid ] = uvbprm[i].x + sub.x * val;
      by[ tlv->hgvt->sid ] = uvbprm[i].y + sub.y * val;
      // emat->bx[ tlv->hgvt->sid ] = uvbprm[i].x + sub.x * val;
      // emat->by[ tlv->hgvt->sid ] = uvbprm[i].y + sub.y * val;

      esum += tle->ed->length;

      tlv = tlv->nxt;
      tle = tle->nxt;

      if ( (tlv == elv) || (tlv == (Splv *) NULL) ) break;
    }

    ++i;
  }

  free(uvbprm);
}

// harmonic mapping functions with Eigen

void hgfcharmonic_Eigen( HGfc *hgfc, Splp *lp )
{
  int vn = initialize_hgfc( hgfc );

  // alternates harmonic_calc_kappa function
  double* kappa = (double*) malloc( hgfc->hgen * sizeof(double) );
  for ( HGed* ed = hgfc->shged; ed != (HGed*) NULL; ed = ed->nxt )
    {
      kappa[ed->sid] = 1.0;
    }

  // vt->vval initialization
  for ( HGvt* vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt )
    {
      vt->vval = 0.0;
    }
  
  // setup val and vval
  for ( HGvt* vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt ) {
    for ( HGvted* ve = vt->shgve; ve != (HGvted *) NULL; ve = ve->nxt )
      {
        HGed* ed = ve->ed;
        // sv
        int id = ed->sv->sid;
        if (vt->sid != id)
          {
            HGvtvt* vv = find_sort_hgvtvt( vt, id );
            vv->val -= kappa[ed->sid];
          }
        else
          {
            vt->vval += kappa[ed->sid];
          }
        // ev
        id = ed->ev->sid;
        if (vt->sid != id)
          {
            HGvtvt* vv = find_sort_hgvtvt( vt, id );
            vv->val -= kappa[ed->sid];
          }
        else
          {
            vt->vval += kappa[ed->sid];
          }
      }
  }
      
  free(kappa);

  // boundary points are fixed
  for ( HGvt* vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt )
    {
      if ( vt->vt->sp_type != SP_VERTEX_NORMAL )
        {
          vt->vval = 1.0;
          free_hgppdvertexvertex( vt );
        }
    }

  // setup matrix A
  // build up sparse matrix A

  int n_vt = hgfc->hgvn;
  Eigen::SparseMatrix<double> spmat( n_vt, n_vt );
  
  for ( HGvt* vt = hgfc->shgvt; vt != (HGvt*) NULL; vt = vt->nxt )
    {
      int i = vt->sid;
      spmat.insert( i, i ) = vt->vval;
      if ( vt->vt->sp_type == SP_VERTEX_NORMAL )
        {
          for ( HGvtvt* vv = vt->shgvv; vv != (HGvtvt*) NULL; vv = vv->nxt )
            {
              int j = vv->id;
              spmat.insert( i, j ) = vv->val;
            }
        }
    }
  spmat.makeCompressed();

  // setup vector b
  Eigen::VectorXd bx(n_vt), by(n_vt);
  harmonic_initialize_vector_2( hgfc, lp, bx, by );

  // solve x and y
  Eigen::VectorXd xx(n_vt), xy(n_vt);
  Eigen::BiCGSTAB<Eigen::SparseMatrix<double> > solver(spmat);
  xx = solver.solve(bx);
  xy = solver.solve(by);

  // store x to uvw
  for ( HGvt* vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt )
    {
      vt->uvw.x = xx[vt->sid];
      vt->uvw.y = xy[vt->sid];
    }

  exit_hgfc( hgfc );
}

void hppdharmonic( HPpd *hppd )
{
  HFace *hf;

  /* calc edge length */
  edge_length( hppd->ppd1 );
  edge_length( hppd->ppd2 );
  for ( hf = hppd->shfc; hf != (HFace *) NULL; hf = hf->nxt )
    {
      hgfcharmonic_Eigen( hf->hgfc1, hf->hloop->lp1 );
      hgfcharmonic_Eigen( hf->hgfc2, hf->hloop->lp2 );
      // hgfcharmonic( hf->hgfc1, hf->hloop->lp1 );
      // hgfcharmonic( hf->hgfc2, hf->hloop->lp2 );
    }
}

/* harmonic mapping functions */
void hgfcharmonic( HGfc *hgfc, Splp *lp )
{
  int    iter;
  int    vn;
  double rsq;
  Semat  *emat;

  vn = initialize_hgfc( hgfc );
  emat = create_harmonic_emat( hgfc );
  harmonic_initialize_vector( hgfc, lp, emat );

  linbcg( emat, emat->bx, emat->xx, 1, SMDZEROEPS, 1000, &iter, &rsq );
  linbcg( emat, emat->by, emat->yy, 1, SMDZEROEPS, 1000, &iter, &rsq );
  solvec_hgfc( hgfc, emat );

  free_emat( emat );
  exit_hgfc( hgfc );
}

int initialize_hgfc( HGfc *hgfc )
{
  int  i;
  int  cnt = 0;
  HGvt *hv;
  HGed *he;

  /* id */

  for (i = 0, hv = hgfc->shgvt; hv != (HGvt *) NULL; hv = hv->nxt, ++i) {
    hv->sid  = i;
    if ( hv->vt->sp_type == SP_VERTEX_NORMAL ) {
      ++cnt;
    }
  }
  /* , and create hgvt->hged links */
  for (i = 0, he = hgfc->shged; he != (HGed *) NULL; he = he->nxt, ++i) {
    he->sid  = i;
    create_hgvted( he->sv, he );
    create_hgvted( he->ev, he );
  }
  return cnt;
}

Semat *create_harmonic_emat( HGfc *hgfc )
{
  int    i, vn;
  int    id;
  double *kappa;
  Semat  *emat;
  HGvt   *vt;
  HGed   *ed;
  HGvted *ve;
  HGvtvt *vv;

  emat = init_emat( hgfc->hgvn );

  kappa = harmonic_calc_kappa( hgfc );

  for ( vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt ) {
    vt->vval = 0.0;
  }

  for ( vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt ) {
    for ( ve = vt->shgve; ve != (HGvted *) NULL; ve = ve->nxt ) {

      ed = ve->ed;
      /* sv */
      id = ed->sv->sid;
      if (vt->sid != id) {
        vv = find_sort_hgvtvt( vt, id );
        vv->val -= kappa[ed->sid];
      } else {
        vt->vval += kappa[ed->sid];
      }
      /* ev */
      id = ed->ev->sid;
      if (vt->sid != id) {
        vv = find_sort_hgvtvt( vt, id );
        vv->val -= kappa[ed->sid];
      } else {
        vt->vval += kappa[ed->sid];
      }
    }
  }

  /* Boundary Points are fixed. */
  for ( vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt ) {

    if ( vt->vt->sp_type != SP_VERTEX_NORMAL ) {
      vt->vval = 1.0;
      free_hgppdvertexvertex( vt );
    }

  }

  vn = 0;
  for ( vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt ) {
    vn += vt->hgvvn;
  }

  emat->num = vn + hgfc->hgvn + 1;
  emat->sa  = (double *) malloc(emat->num * sizeof(double));
  for (i = 0; i < emat->num; ++i) emat->sa[i] = 0.0;
  emat->ija = (int *) malloc(emat->num * sizeof(int));

  dsprsin( hgfc, emat );
  
  free(kappa);

  FreeHGppdVertexVertex( hgfc );

  return emat;
}

double *harmonic_calc_kappa( HGfc *hgfc )
{
  double *kappa;
  HGed   *ed;

  /* initialize length, area, kappa */
  kappa   = (double *) malloc( hgfc->hgen * sizeof(double));

  for ( ed = hgfc->shged; ed != (HGed *) NULL; ed = ed->nxt ) {
    kappa[ed->sid] = 1.0;
  }
  return kappa;
}

void harmonic_initialize_vector( HGfc *hgfc, Splp *lp, Semat *emat )
{
  int    i;
  HGvt   *vt;
  Vec2d  *uvbprm;
  Sple   *le, *tle, *sle;
  Splv   *lv, *tlv, *slv, *elv;
  double sum, esum, val;
  Vec2d  sub;

  /* initialize vector */
  for ( vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt ) {

    emat->bx[vt->sid] = emat->xx[vt->sid] = 0.0;
    emat->by[vt->sid] = emat->yy[vt->sid] = 0.0;

  }

  uvbprm = calc_uvbprm( hgfc->hgcn );

  /* calculate boundary values */

  lv = lp->splv;
  le = lp->sple;

  i = 0;
  while ( i < hgfc->hgcn ) {

    slv = lv;
    sle = le;
    sum = 0.0;

    while ( 1 ) {
      sum += le->ed->length;
      lv = lv->nxt;
      le = le->nxt;
      if ( lv == (Splv *) NULL ) {
        elv = lp->splv;
        break;
      }
      if ( lv->vt->sp_type == SP_VERTEX_HVERTEX ) {
        elv = lv;
        break;
      }
    }

    esum = 0.0;
    tlv = slv;
    tle = sle;
    sub.x = uvbprm[i+1].x - uvbprm[i].x;
    sub.y = uvbprm[i+1].y - uvbprm[i].y;
    while ( 1 ) {

      val = esum / sum;
      emat->bx[ tlv->hgvt->sid ] = uvbprm[i].x + sub.x * val;
      emat->by[ tlv->hgvt->sid ] = uvbprm[i].y + sub.y * val;

      esum += tle->ed->length;

      tlv = tlv->nxt;
      tle = tle->nxt;

      if ( (tlv == elv) || (tlv == (Splv *) NULL) ) break;
    }

    ++i;
  }

  free(uvbprm);
}

Vec2d *calc_uvbprm( int cn )
{
  int i;
  double angle;
  Vec2d *uvbprm;

  uvbprm = (Vec2d *) malloc( (cn+1) * sizeof(Vec2d) );

  for ( i = 0; i <= cn; ++i ) {
    angle = 2 * (double) i * SMDPI / (double) cn;
    uvbprm[i].x = cos( angle );
    uvbprm[i].y = sin( angle );
/*     display("uvbprm %g %g\n", uvbprm[i].x, uvbprm[i].y); */
  }
  return uvbprm;
}

void solvec_hgfc( HGfc *hgfc, Semat *emat )
{
  HGvt *vt;

  for ( vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt ) {
    vt->uvw.x = emat->xx[vt->sid];
    vt->uvw.y = emat->yy[vt->sid];
  }
}

void exit_hgfc( HGfc *hgfc )
{
  HGvt *hv;
  HGed *he;

  for ( hv = hgfc->shgvt; hv != (HGvt *) NULL; hv = hv->nxt ) {
    hv->sid  = SMDNULL;
    hv->vval = 0.0;
    free_hgppdvertexedge( hv );
  }

  /* create hgfc surface */

  for ( he = hgfc->shged; he != (HGed *) NULL; he = he->nxt ) {
    he->sid  = SMDNULL;
  }

}

/* Semat functions */
Semat *init_emat( int num )
{
  Semat *emat;

  emat = (Semat *) malloc(sizeof(Semat));
  emat->rnum = num;
  emat->cnum = num;
  /* constant vectors initialize */
  emat->bx = (double *) malloc(num * sizeof(double));
  emat->by = (double *) malloc(num * sizeof(double));
  /* solution vectors initialize */
  emat->xx = (double *) malloc(num * sizeof(double));
  emat->yy = (double *) malloc(num * sizeof(double));

  return emat;
}

void free_emat(Semat *emat)
{
  free(emat->sa);
  free(emat->ija);
  free(emat->bx);
  free(emat->by);
  free(emat->xx);
  free(emat->yy);
  free(emat);
}

/*
void printemat(Semat *emat)
{
  int i;

  for (i = 0; i < emat->cnum; ++i) {
    display("%d (b) %f %f\n", i, emat->bx[i], emat->by[i]);
    display("%d (x) %f %f\n", i, emat->xx[i], emat->yy[i]);
  }
  for (i = 0; i < emat->num; ++i) 
    display("(%d) (sa) %f (ija) %d\n", i, emat->sa[i], emat->ija[i]);
}
*/

