/* Copyright (c) 1997-1998 by Takashi Kanai; All rights researved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>
#include "smd.h"

/* "Vmtx"        : Holds the original and inverse and 
   "actual_size" : Actual size of matrix in use, (high_subscript+1) */

double InvertMatrix( Vmtx mat, int actual_size )
{
  int   i, j, k;
  /* Locations of pivot elements */
  int  *pvt_i, *pvt_j;
  double pvt_val;		/* Value of current pivot element */
  double hold;			/* Temporary storage */
  double determ;		/* Determinant */

  determ = 1.0;

  pvt_i = (int *) malloc(actual_size * sizeof(int));
  pvt_j = (int *) malloc(actual_size * sizeof(int));

  for (k = 0; k < actual_size; k++) {
    /* Locate k'th pivot element */
    pvt_val = mat[k][k];	/* Initialize for search */
    pvt_i[k] = k;
    pvt_j[k] = k;
    for (i = k; i < actual_size; i++)
      for (j = k; j < actual_size; j++)
	if (fabs(mat[i][j]) > fabs(pvt_val)) {
	  pvt_i[k] = i;
	  pvt_j[k] = j;
	  pvt_val = mat[i][j];
	}
    /* Product of pivots, gives determinant when finished */
    determ *= pvt_val;
    if (determ == 0.0) {
      free(pvt_i);
      free(pvt_j);
      return 0.0;
    }
    /* "Interchange" rows (with sign change stuff) */
    i = pvt_i[k];
    if (i != k)			/* If rows are different */
      for (j = 0; j < actual_size; j++) {
	hold = -mat[k][j];
	mat[k][j] = mat[i][j];
	mat[i][j] = hold;
      }
    /* "Interchange" columns */
    j = pvt_j[k];
    if (j != k)			/* If columns are different */
      for (i = 0; i < actual_size; i++) {
	hold = -mat[i][k];
	mat[i][k] = mat[i][j];
	mat[i][j] = hold;
      }
    /* Divide column by minus pivot value */
    for (i = 0; i < actual_size; i++)
      if (i != k)		/* Don't touch the pivot entry */
	mat[i][k] /= (-pvt_val);	/* (Tricky C syntax for division) */

    /* Reduce the matrix */
    for (i = 0; i < actual_size; i++) {
      hold = mat[i][k];
      for (j = 0; j < actual_size; j++)
	if (i != k && j != k)	/* Don't touch pivot. */
	  mat[i][j] += hold * mat[k][j];
    }

    /* Divide row by pivot */
    for (j = 0; j < actual_size; j++)
      if (j != k)		/* Don't touch the pivot! */
	mat[k][j] /= pvt_val;

    /* Replace pivot by reciprocal (at last we can touch it). */
    mat[k][k] = 1.0 / pvt_val;
  }

  /* That was most of the work, one final pass of row/column interchange */
  /* to finish */
  for (k = actual_size - 2; k >= 0; k--) {	/* Don't need to work with 1 by 1 */
    /* corner */
    i = pvt_j[k];		/* Rows to swap correspond to pivot COLUMN */
    if (i != k)			/* If rows are different */
      for (j = 0; j < actual_size; j++) {
	hold = mat[k][j];
	mat[k][j] = -mat[i][j];
	mat[i][j] = hold;
      }
    j = pvt_i[k];		/* Columns to swap correspond to pivot ROW */
    if (j != k)			/* If columns are different */
      for (i = 0; i < actual_size; i++) {
	hold = mat[i][k];
	mat[i][k] = -mat[i][j];
	mat[i][j] = hold;
      }
  }

  free(pvt_i);
  free(pvt_j);
  return determ;
}

Vmtx NewMatrix(int cols, int rows)
{
  int   i;
  Vmtx  newM;
  newM = (double **) malloc(rows * sizeof(double *));
  for (i = 0; i < rows; i++)
    newM[i] = (double *) malloc(cols * sizeof(double));
  return newM;
}

void FreeMatrix(Vmtx mat, int rows)
{
  int   i;
  for (i = 0; i < rows; i++)
    free(mat[i]);
  free(mat);
}

void TransposeMatrix(Vmtx inM, Vmtx outM, int cols, int rows)
{
  int   tempI, tempJ;
  for (tempI = 0; tempI < rows; tempI++)
    for (tempJ = 0; tempJ < cols; tempJ++)
      outM[tempI][tempJ] = inM[tempJ][tempI];
}

void MultMatrix(Vmtx firstM, Vmtx secondM, Vmtx outM, int firstrows,
	   int cols, int secondcols)
{
  int   i, j, k;
  double sum;

  for (i = 0; i < secondcols; i++)
    for (j = 0; j < firstrows; j++) {
      sum = 0.0;
      for (k = 0; k < cols; k++)
	sum += firstM[j][k] * secondM[k][i];
      outM[j][i] = sum;
    }
}

void InvertMatrix4(double *mat, double *inv)
{
  int    i, j;
  double d;
  int    *index, size;
  double *col;
  Vmtx   vmat, vinv;
  void   ludcmp(Vmtx, int, int *, double *);
  void   lubksb(Vmtx, int, int *, double *);

  size = 4;
  index = (int *) malloc(size * sizeof(int));
  col   = (double *) malloc(size * sizeof(double));

  /* convert */
  vmat  = (double **) malloc(size * sizeof(double *));
  vinv  = (double **) malloc(size * sizeof(double *));
  for (i = 0; i < size; ++i) {
    vmat[i] = (double *) malloc(size * sizeof(double));
    vinv[i] = (double *) malloc(size * sizeof(double));
    for (j = 0; j < size; ++j) {
      vmat[i][j] = mat[j * size + i];
    }
  }
  /* main routine */
  ludcmp(vmat, size, index, &d);
  for (j = 0; j < size; ++j) {
    for (i = 0; i < size; ++i) col[i] = 0.0;
    col[j] = 1.0;
    lubksb(vmat, size, index, col);
    for (i = 0; i < size; ++i) vinv[i][j] = col[i];
  }
  /* convert */
  for (i = 0; i < size; ++i) {
    for (j = 0; j < size; ++j) {
      inv[j * size + i] = vinv[i][j];
    }
  }
  /* free */
  for (i = 0; i < size; ++i) {
    free(vmat[i]);
    free(vinv[i]);
  }
  free(vmat);
  free(vinv);
  
  free(col);
  free(index);
}  

#define TINY 1.0e-20

void ludcmp(Vmtx a, int n, int *indx, double *d)
{
  int    i, imax, j, k;
  double big, dum, sum, temp;
  double *vv;

  vv = (double *) malloc(n * sizeof(double));
  *d = 1.0;
  for (i = 0; i < n; i++) {
    big = 0.0;
    for (j = 0; j < n; j++)
      if ((temp = fabs(a[i][j])) > big) big = temp;
    if (fabs(big - 0.0) < TINY) {
      fprintf(stderr, "Singular matrix in routine ludcmp\n");
    }
    vv[i] = 1.0 / big;
  }
  for (j = 0; j < n; j++) {
    for (i = 0; i < j; i++) {
      sum=a[i][j];
      for (k = 0; k < i; k++) sum -= a[i][k] * a[k][j];
      a[i][j] = sum;
    }
    big = 0.0;
    for (i = j; i < n; i++) {
      sum=a[i][j];
      for (k = 0; k < j; k++)
	sum -= a[i][k] * a[k][j];
      a[i][j] = sum;
      if ((dum = vv[i] * fabs(sum)) >= big) {
	big = dum;
	imax = i;
      }
    }
    if (j != imax) {
      for (k = 0; k < n; k++) {
	dum = a[imax][k];
	a[imax][k] = a[j][k];
	a[j][k] = dum;
      }
      *d = -(*d);
      vv[imax] = vv[j];
    }
    indx[j] = imax;
    if (fabs(a[j][j] - 0.0) < TINY) a[j][j] = TINY;
    if (j != n) {
      dum = 1.0 / (a[j][j]);
      for (i = j + 1; i < n; i++) a[i][j] *= dum;
    }
  }
  free(vv);
}

void lubksb(Vmtx a, int n, int *indx, double *b)
{
  int    i, ii = 0, ip, j;
  double sum;

  for (i = 0; i < n; i++) {
    ip = indx[i];
    sum = b[ip];
    b[ip] = b[i];
    if (ii) {
      for (j = ii; j <= i-1; j++) sum -= a[i][j] * b[j];
    } else if (sum) {
      ii = i;
    }
    b[i] = sum;
  }
  for (i = n - 1; i >= 0; i--) {
    sum = b[i];
    for (j = i+1; j < n; j++) sum -= a[i][j] * b[j];
    b[i] = sum / a[i][i];
  }
}

void rot_x(double val, Vec *vec)
{
  double v[2];
  double rd, co, si;
  
  v[0] = vec->y;
  v[1] = vec->z;

  rd = val * SMDPI / 180.0;
  co = cos(rd); si = sin(rd);
  vec->y =  co * v[0] + si * v[1];
  vec->z = -si * v[0] + co * v[1];
}

void rot_y(double val, Vec *vec)
{
  double v[2];
  double rd, co, si;
  
  v[0] = vec->z;
  v[1] = vec->x;

  rd = val * SMDPI / 180.0;
  co = cos(rd); si = sin(rd);
  vec->z =  co * v[0] + si * v[1];
  vec->x = -si * v[0] + co * v[1];
}

void rot_z(double val, Vec *vec)
{
  double v[2];
  double rd, co, si;
  
  v[0] = vec->x;
  v[1] = vec->y;

  rd = val * SMDPI / 180.0;
  co = cos(rd); si = sin(rd);
  vec->x =  co * v[0] + si * v[1];
  vec->y = -si * v[0] + co * v[1];
}

void rot_inv_x(double val, Vec *vec)
{
  double v[2];
  double rd, co, si;
  
  v[0] = vec->y;
  v[1] = vec->z;

  rd = val * SMDPI / 180.0;
  co = cos(rd); si = sin(rd);
  vec->y = co * v[0] - si * v[1];
  vec->z = si * v[0] + co * v[1];
}

void rot_inv_y(double val, Vec *vec)
{
  double v[2];
  double rd, co, si;
  
  v[0] = vec->z;
  v[1] = vec->x;

  rd = val * SMDPI / 180.0;
  co = cos(rd); si = sin(rd);
  vec->z = co * v[0] - si * v[1];
  vec->x = si * v[0] + co * v[1];
}

void rot_inv_z(double val, Vec *vec)
{
  double v[2];
  double rd, co, si;
  
  v[0] = vec->x;
  v[1] = vec->y;

  rd = val * SMDPI / 180.0;
  co = cos(rd); si = sin(rd);
  vec->x = co * v[0] - si * v[1];
  vec->y = si * v[0] + co * v[1];
}

void rot_all(double xval, double yval, double zval, Vec *vec)
{
  double v[3];
  double xrd, yrd, zrd;
  double cx, cy, cz, sx, sy, sz;
  v[0] = vec->x;
  v[1] = vec->y;
  v[2] = vec->z;

  xrd = xval * SMDPI / 180.0;
  yrd = yval * SMDPI / 180.0;
  zrd = zval * SMDPI / 180.0;
  cx = cos(xrd); sx = sin(xrd);
  cy = cos(yrd); sy = sin(yrd);
  cz = cos(zrd); sz = sin(zrd); 

  vec->x = cy * cz * v[0] - cy * sz * v[1] + sy * v[2];
  vec->y = (sx * sy * cz + cx * sz) * v[0] + (-1.0 * sx * sy * sz + cx * cz) * v[1]
    - sx * cy * v[2];
  vec->z = (-1.0 * cx * sy * cz + sx * sz) * v[0] + (cx * sy * sz + sx * cz) * v[1]
    + cx * cy * v[2];
}

void rot_vec(double angle, Vec *axis, Vec *vec)
{
  double v[3], m[9];
  double rd, co, si, mco;
  double ax2, ay2, az2, axay, axaz, ayaz;
  Vec    a;
  Vec    *V3Normalize(Vec *);
  
  v[0] = vec->x;
  v[1] = vec->y;
  v[2] = vec->z;

  rd = angle * SMDPI / 180.0;
  co = cos(rd); si = sin(rd); mco = 1.0 - co;
  a.x = axis->x; a.y = axis->y; a.z = axis->z;
  V3Normalize(&a);

  ax2 = a.x * a.x;
  ay2 = a.y * a.y;
  az2 = a.z * a.z;
  axay = a.x * a.y;
  axaz = a.x * a.z;
  ayaz = a.y * a.z;
  
  m[0] = ax2 + (1.0 - ax2) * co;
  m[1] = axay * mco + a.z * si;
  m[2] = axaz * mco - a.y * si;
  m[3] = axay * mco - a.z * si;
  m[4] = ay2 + (1.0 - ay2) * co;
  m[5] = ayaz * mco + a.x * si;
  m[6] = axaz * mco + a.y * si;
  m[7] = ayaz * mco - a.x * si;
  m[8] = az2 + (1.0 - az2) * co;
  
  vec->x = m[0] * v[0] + m[1] * v[1] + m[2] * v[2];
  vec->y = m[3] * v[0] + m[4] * v[1] + m[5] * v[2];
  vec->z = m[6] * v[0] + m[7] * v[1] + m[8] * v[2];
}

void MultMatrix4(double *m, double *mul, double *sum)
{
  int   i;
  
  for (i = 0; i < 4; i++) {
    sum[4*i]   = m[0] * mul[4*i] + m[4] * mul[4*i+1] + m[8]  * mul[4*i+2] + m[12] * mul[4*i+3];
    sum[4*i+1] = m[1] * mul[4*i] + m[5] * mul[4*i+1] + m[9]  * mul[4*i+2] + m[13] * mul[4*i+3];
    sum[4*i+2] = m[2] * mul[4*i] + m[6] * mul[4*i+1] + m[10] * mul[4*i+2] + m[14] * mul[4*i+3];
    sum[4*i+3] = m[3] * mul[4*i] + m[7] * mul[4*i+1] + m[11] * mul[4*i+2] + m[15] * mul[4*i+3];
  }
}

void MakeRotX(double val, double *m)
{
  double rd, co, si;
  
  rd = val * SMDPI / 180.0;
  co = cos(rd); si = sin(rd);
  m[0] = 1.0; m[4] = 0.0; m[8]  = 0.0; m[12] = 0.0;
  m[1] = 0.0; m[5] = co;  m[9]  = -si; m[13] = 0.0;
  m[2] = 0.0; m[6] = si;  m[10] =  co; m[14] = 0.0;
  m[3] = 0.0; m[7] = 0.0; m[11] = 0.0; m[15] = 1.0;
}

void MakeRotY(double val, double *m)
{
  double rd, co, si;
  
  rd = val * SMDPI / 180.0;
  co = cos(rd); si = sin(rd);
  m[0] = co ; m[4] = 0.0; m[8]  = si;  m[12] = 0.0;
  m[1] = 0.0; m[5] = 1.0; m[9]  = 0.0; m[13] = 0.0;
  m[2] = -si; m[6] = 0.0; m[10] =  co; m[14] = 0.0;
  m[3] = 0.0; m[7] = 0.0; m[11] = 0.0; m[15] = 1.0;
}

void MakeRotZ(double val, double *m)
{
  double rd, co, si;
  
  rd = val * SMDPI / 180.0;
  co = cos(rd); si = sin(rd);
  m[0] = co;  m[4] = -si; m[8]  = 0.0; m[12] = 0.0;
  m[1] = si;  m[5] =  co; m[9]  = 0.0; m[13] = 0.0;
  m[2] = 0.0; m[6] = 0.0; m[10] = 1.0; m[14] = 0.0;
  m[3] = 0.0; m[7] = 0.0; m[11] = 0.0; m[15] = 1.0;
}

void MakeRotVec(double angle, Vec *axis, double *m)
{
  double rd, co, si, mco;
  double ax2, ay2, az2, axay, axaz, ayaz;
  Vec    a;
  Vec    *V3Normalize(Vec *);
  
  rd = angle * SMDPI / 180.0;
  co = cos(rd); si = sin(rd); mco = 1.0 - co;
  a.x = axis->x; a.y = axis->y; a.z = axis->z;
  V3Normalize(&a);

  ax2  = a.x * a.x;
  ay2  = a.y * a.y;
  az2  = a.z * a.z;
  axay = a.x * a.y;
  axaz = a.x * a.z;
  ayaz = a.y * a.z;
  
  m[0]  = ax2 + (1.0 - ax2) * co;
  m[1]  = axay * mco - a.z * si;
  m[2]  = axaz * mco + a.y * si;
  m[3]  = 0.0;
  m[4]  = axay * mco + a.z * si;
  m[5]  = ay2 + (1.0 - ay2) * co;
  m[6]  = ayaz * mco - a.x * si;
  m[7]  = 0.0;
  m[8]  = axaz * mco - a.y * si;
  m[9]  = ayaz * mco + a.x * si;
  m[10] = az2 + (1.0 - az2) * co;
  m[11] = 0.0;
  m[12] = 0.0;
  m[13] = 0.0;
  m[14] = 0.0;
  m[15] = 1.0;
}

void MakeRotInvVec(double angle, Vec *axis, double *m)
{
  double rd, co, si, mco;
  double ax2, ay2, az2, axay, axaz, ayaz;
  Vec    a;
  Vec    *V3Normalize(Vec *);
  
  rd = angle * SMDPI / 180.0;
  co = cos(rd); si = sin(rd); mco = 1.0 - co;
  a.x = axis->x; a.y = axis->y; a.z = axis->z;
  V3Normalize(&a);

  ax2  = a.x * a.x;
  ay2  = a.y * a.y;
  az2  = a.z * a.z;
  axay = a.x * a.y;
  axaz = a.x * a.z;
  ayaz = a.y * a.z;
  
  m[0]  = ax2 + (1.0 - ax2) * co; 
  m[1]  = axay * mco + a.z * si;
  m[2]  = axaz * mco - a.y * si;
  m[3]  = 0.0;
  m[4]  = axay * mco - a.z * si;  
  m[5]  = ay2 + (1.0 - ay2) * co; 
  m[6]  = ayaz * mco + a.x * si;
  m[7]  = 0.0;
  m[8]  = axaz * mco + a.y * si;
  m[9]  = ayaz * mco - a.x * si;
  m[10] = az2 + (1.0 - az2) * co;
  m[11] = 0.0;
  m[12] = 0.0;
  m[13] = 0.0;
  m[14] = 0.0;
  m[15] = 1.0;
}

void MultMatrixVec(double *mat, Vec* vec)
{
  int   i;
  double a[4], b[4];

  a[0] = vec->x; a[1] = vec->y; a[2] = vec->z; a[3] = 1.0;
  for (i = 0; i < 4; ++i) 
    b[i] = (mat[i] * a[0] + mat[4 + i] * a[1] +  mat[8 + i] * a[2] + mat[12 + i] * a[3]);
  vec->x = b[0];
  vec->y = b[1];
  vec->z = b[2];
}

void EqualMatrix4(double *mat, double* mat1)
{
  int  i;

  for (i = 0; i < 16; ++i) mat1[i] = mat[i];
}

#undef TINY      










