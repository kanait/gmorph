//
// morphvec.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _MORPHVEC_H
#define _MORPHVEC_H

extern void calc_morph_vector(HPpd *, Sppd *);
extern void initialize_ppd_morph_vector(Sppd *);
extern void hvertex_calc_morph_vector(HPpd *, Sppd *);
extern void hedge_calc_morph_vector(HPpd *, Sppd *);
extern void hface_calc_morph_vector(HPpd *, Sppd *);
extern void hgfc_calc_morph_vector(HGfc *, HGfc *, HGfc *, Sppd *, int);

#endif // _MORPHVEC_H
