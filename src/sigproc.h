//
// sigproc.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _SIGPROC_H
#define _SIGPROC_H

/* matrix structure for linbcg */
typedef struct _sparsematrix {
  int nrow;   /* matrix row */
  int ncol;   /* matrix column */
  int narray; /* number of array */
  int *ija;
  double *sa;
} SparseMatrix;

extern void ppd_signal_processing(Sppd *, double, double, int);
extern SparseMatrix *create_spmatrix_dspr(Sppd *, double);
extern void edge_weight(Sppd *);

#endif // _SIGPROC_H
