/* Copyright (c) 1997-1998 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>
#include "smd.h"
#include "linbcg.h"

int linbcg(Semat *emat, double *b, double *x, int itol, double tol,
	   int itmax, int *iter, double *err)
{
  int  n, j;
  double ak, akden, bk, bkden, bknum, bnrm, dxnrm, xnrm, zm1nrm, znrm;
  double *p, *pp, *r, *rr, *z, *zz;

  n = (int) emat->cnum;
  p = dvector(0, n - 1);
  pp = dvector(0, n - 1);
  r = dvector(0, n - 1);
  rr = dvector(0, n - 1);
  z = dvector(0, n - 1);
  zz = dvector(0, n - 1);

  *iter = 0;
  atimes(emat, n, x, r, 0);
  for (j = 0; j < n; ++j) {
    r[j] = b[j] - r[j];
    rr[j] = r[j];
  }
  atimes(emat, n, r, rr, 0);
  znrm = 1.0;
  if (itol == 1) {
    bnrm = snrm(n, b, itol);
    if (fabs(bnrm) < SMDEPS) {
      for (j = 0; j < n; ++j) x[j] = 0.0;
      free_dvector(p, 0, n - 1);
      free_dvector(pp, 0, n - 1);
      free_dvector(r, 0, n - 1);
      free_dvector(rr, 0, n - 1);
      free_dvector(z, 0, n - 1);
      free_dvector(zz, 0, n - 1);
      return SMD_ON;
    }
  } else if (itol == 2) {
    asolve(emat, n, b, z, 0);
    bnrm = snrm(n, z, itol);
  } else if (itol == 3 || itol == 4) {
    asolve(emat, n, b, z, 0);
    bnrm = snrm(n, z, itol);
    asolve(emat, n, r, z, 0);
    znrm = snrm(n, z, itol);
  } else {
    fprintf(stderr, "illegal itol in linbcg.");
    free_dvector(p, 0, n - 1);
    free_dvector(pp, 0, n - 1);
    free_dvector(r, 0, n - 1);
    free_dvector(rr, 0, n - 1);
    free_dvector(z, 0, n - 1);
    free_dvector(zz, 0, n - 1);
    return SMD_OFF;
  }
  asolve(emat, n, r, z, 0);
  while (*iter <= itmax) {
    ++(*iter);
    zm1nrm = znrm;

    asolve(emat, n, rr, zz, 1);
    for (bknum = 0.0, j = 0; j < n; ++j)
      bknum += z[j] * rr[j];

    if (*iter == 1) {
      for (j = 0; j < n; ++j) {
	p[j] = z[j];
	pp[j] = zz[j];
      }
    } else {
      bk = bknum / bkden;
      for (j = 0; j < n; ++j) {
	p[j] = bk * p[j] + z[j];
	pp[j] = bk * pp[j] + zz[j];
      }
    }
    bkden = bknum;
    atimes(emat, n, p, z, 0);
    for (akden = 0.0, j = 0; j < n; ++j)
      akden += z[j] * pp[j];
    ak = bknum / akden;
    atimes(emat, n, pp, zz, 1);
    for (j = 0; j < n; ++j) {
      x[j] += ak * p[j];
      r[j] -= ak * z[j];
      rr[j] -= ak * zz[j];
    }

    asolve(emat, n, r, z, 0);
    if (itol == 1 || itol == 2) {
      znrm = 1.0;
      *err = snrm(n, r, itol) / bnrm;
    } else if (itol == 3 || itol == 4) {
      znrm = snrm(n, z, itol);
      if (fabs(zm1nrm - znrm) > SMDEPS * znrm) {
	dxnrm = fabs(ak) * snrm(n, p, itol);
	*err = znrm / fabs(zm1nrm - znrm) * dxnrm;
      } else {
	*err = znrm / bnrm;
	continue;
      }
      xnrm = snrm(n, x, itol);
      if (*err <= 0.5 * xnrm)
	*err /= xnrm;
      else {
	*err = znrm / bnrm;
	continue;
      }
    }
/*     display("iter = %4d err = %10.6f\n", *iter, *err);  */
    if (*err <= tol)
      break;
  }
  free_dvector(p, 0, n - 1);
  free_dvector(pp, 0, n - 1);
  free_dvector(r, 0, n - 1);
  free_dvector(rr, 0, n - 1);
  free_dvector(z, 0, n - 1);
  free_dvector(zz, 0, n - 1);
  
  return SMD_ON;
}

double snrm(int n, double *sx, int itol)
{
  int  i, isamax;
  double   ans;

  if (itol <= 3) {
    ans = 0.0;
    for (i = 0; i < n; ++i)
      ans += sx[i] * sx[i];
    return sqrt(ans);
  } else {
    isamax = 0;
    for (i = 0; i < n; ++i) {
      if (fabs(sx[i]) > fabs(sx[isamax]))
	isamax = i;
    }
    return fabs(sx[isamax]);
  }
}

void atimes(Semat *emat, int n, double *x, double *r, int itrnsp)
{
  void  dsprsax(double *, int *, double *, double *, int);
  void  dsprstx(double *, int *, double *, double *, int);

  if (itrnsp) dsprstx(emat->sa, emat->ija, x, r, n);
  else        dsprsax(emat->sa, emat->ija, x, r, n);
}

void asolve(Semat *emat, int n, double *b, double *x, int itrnsp)
{
  int i;

  for (i = 0; i < n; ++i)
    x[i] = (emat->sa[i] != 0.0 ? b[i] / emat->sa[i] : b[i]);
}

void dsprsin( HGfc *hgfc, Semat *emat )
{
  int  j;
  HGvt *vt;
  HGvtvt *vv;

  emat->ija[0] = emat->cnum + 1;
  j = emat->cnum;
  
  for ( vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt ) {
    
    emat->sa[vt->sid] = vt->vval;
    for (vv = vt->shgvv; vv != (HGvtvt *) NULL; vv = vv->nxt) {
      ++j;
      emat->sa[j]  = vv->val;
      emat->ija[j] = vv->id;
/*       if (emat->num == j) printf("-------->\n"); */
    }
    emat->ija[vt->sid + 1] = j + 1;
/*     if (emat->num == vt->sid + 1) printf("-------->\n"); */
  }
}

void dsprsax(double *sa, int *ija, double *x, double *b, int n)
{
  int  i, k;

  if (ija[0] != n + 1) {
    fprintf(stderr, "dsprsax: mismatched vector and matrix.");
    return;
  }
  
  for (i = 0; i < n; ++i) {
    b[i] = sa[i] * x[i];
    for (k = ija[i]; k <= ija[i + 1] - 1; ++k) {
      b[i] += sa[k] * x[ija[k]];
    }
  }
  
}

void dsprstx(double *sa, int *ija, double *x, double *b, int n)
{
  int  i, j, k;

  if (ija[0] != n + 1) {
    fprintf(stderr, "dsprsax: mismatched vector and matrix.");
    return;
  }
  
  for (i = 0; i < n; ++i)
    b[i] = sa[i] * x[i];
  for (i = 0; i < n; ++i) {
    for (k = ija[i]; k <= ija[i + 1] - 1; ++k) {
      j = ija[k];
      b[j] += sa[k] * x[i];
    }
  }
}

#define NR_END 1
#define FREE_ARG char*

double *dvector(long nl, long nh)
/* allocate a double vector with subscript range v[nl..nh] */
{
  double *v;

  v = (double *) malloc((size_t) ((nh - nl + 1 + NR_END) * sizeof(double)));
  if (!v) fprintf(stderr, "allocation failure in dvector()\n");
  return v - nl + NR_END;
}

/*double *dvector(long n)
{
  double *v;

  v = (double *) malloc((n+1) * sizeof(double));
  return v;
}*/

void free_dvector(double *v, long nl, long nh)
/* free a double vector allocated with dvector() */
{
  free((FREE_ARG) (v + nl - NR_END));
}

/*void free_dvector(double *v)
{
  free(v);
}*/
