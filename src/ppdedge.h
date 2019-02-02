//
// ppdedge.h
//
// Copyright (c) 1997 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _PPDEDGE_H
#define _PPDEDGE_H

extern Sped *create_ppdedge(Sppd *);
extern void free_ppdedge(Sped *, Sppd *);
extern void free_ppdedge_withqtree(Sped *, Sppd *);
extern void FreeSped(Sped *, Sppd *);
extern Edvt *create_edvtx(Sped *, Spvt *);
extern void insert_edvtx(Sped *, Spvt *, Sped *, double);
extern void free_ppdedgevertex(Sped *);
extern void free_edvtx(Edvt *, Sped *);
extern void edge_length(Sppd *);
extern Sped *find_ppdedge(Spvt *, Spvt *);

#endif // _PPDEDGE_H
