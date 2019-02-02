//
// ppdvertex.h
//
// Copyright (c) 1997 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _PPDVERTEX_H
#define _PPDVERTEX_H

extern Spvt *create_ppdvertex(Sppd *);
extern Spvt *list_ppdvertex(Sppd *, Id);
extern void free_ppdvertex(Spvt *, Sppd *);
extern Vted *create_vtxed(Spvt *, Sped *);
extern Spvt *another_vt(Sped *, Spvt *);
extern Vted *find_vtxed(Spvt *, Sped *);
extern double calc_angle(Spvt *, Spvt *, Spvt *);
extern Vted *next_vted(Vted *);
extern Vted *previous_vted(Vted *);
extern void insert_vtxed(Spvt *, Sped *);
extern void make_vtxedlink(Sppd *);
extern void FreeVted(Spvt *, Sped *);
extern void free_ppdvertexedge(Spvt *);
extern void free_vertexedge(Spvt *, Sped *);
extern void free_vtxed(Vted *, Spvt *);
extern void printvtxed(Spvt *);
extern Vtnm *create_vtxnm(Spvt *, Spnm *);
extern void free_ppdvertexnormal(Spvt *);
extern void free_vtxnm(Vtnm *, Spvt *);
extern Vtnm *find_ppdnormal(Spvt *, Vec *, Sppd *);
extern void free_ppdvertex_noedge(Sppd *);
extern void ppdvertex_noedge_check(Sppd *);

#endif // _PPDVERTEX_H
