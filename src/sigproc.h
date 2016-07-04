/* sigproc.c */

/* matrix structure for linbcg */
typedef struct _sparsematrix {
  int nrow;	/* matrix row */
  int ncol;	/* matrix column */
  int narray; /* number of array */
  int *ija;
  double *sa;
} SparseMatrix;

extern void ppd_signal_processing(Sppd *, double, double, int);
extern SparseMatrix *create_spmatrix_dspr(Sppd *, double);
extern void edge_weight(Sppd *);
