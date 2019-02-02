//
// gmorph.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _GMORPH_H
#define _GMORPH_H

extern Sppd *ppdgmorph_v2(HPpd *);
extern void initialize_gmorphv2(HPpd *);
extern void after_morphing(Sppd *);
extern void clear_gmorph(HPpd *);
extern void record_morphppd(char *, Sppd *);
extern void write_gmh_file(char *, HPpd *);
extern HPpd *open_gmh_file(char *);
extern Splp *create_shortestpath(char *, Sppd *);
extern int gmh_ok(char *);
extern void PrintGPpd( Sppd * );
extern void resetmorphppd( Sppd * );
extern void setinterpppd( Sppd *, double );

#endif // _GMORPH_H
