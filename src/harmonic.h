/* harmonic.c */
extern void hppdharmonic(HPpd *);
extern void hgfcharmonic(HGfc *, Splp *);
extern int initialize_hgfc(HGfc *);
extern Semat *create_harmonic_emat(HGfc *);
extern double *harmonic_calc_kappa(HGfc *);
extern void harmonic_initialize_vector(HGfc *, Splp *, Semat *);
extern Vec2d *calc_uvbprm(int);
extern void solvec_hgfc(HGfc *, Semat *);
extern void exit_hgfc(HGfc *);
extern Semat *init_emat(int);
extern void free_emat(Semat *);
extern void printemat(Semat *);
