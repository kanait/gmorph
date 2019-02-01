//
// harmonic.h
//
// Copyright (c) 1996-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _HARMONIC_H
#define _HARMONIC_H

#ifdef __cplusplus
extern "C" {
#endif

extern void hgfcharmonic_Eigen( HGfc *, Splp * );
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

#ifdef __cplusplus
}
#endif

#endif // _HARMONIC_H
