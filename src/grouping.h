//
// grouping.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _GROUPING_H
#define _GROUPING_H

extern void hppd_to_hgppd(HPpd *);
extern void subdivide_ppdedges(HPpd *);
extern void cmesh_group_hppd(HPpd *);
extern HGppd *ppdgroup(Sppd *, HPpd *, int);
extern HGfc *find_hgfc_grouping(Spvt *, Sppd *, HGppd *);
extern HGfc *find_hgfc_cvt(HGppd *, int, Spvt **);
extern int find_cvt_in_hgfc(int, Spvt **, HGfc *);
extern int find_vt_in_hgppdcntrlvertex(Spvt *, HGfc *);
extern void find_hgfc_vertex(Spvt *, int *, int *, int *, int *, Spvt **);
extern int find_cvt(Spvt *, int, Spvt **);
extern int check_gid(int, int, int *);
extern HGfc *hloop_to_hgfc(HFace *, HGppd *, int);
extern HGfc *find_ppdedge_in_hgppd(Sped *, HGppd *);
extern int find_ppdvertex_in_hgfc(Spvt *, HGfc *);
extern Sped *next_ungrouped_edge(Sped *);
extern void group_hgppd_vertex(Spvt *, HGfc *);
extern void hgppdface_to_hppdface(HGppd *, HPpd *, int);
extern void coincident_hface_hgface(HPpd *, HGfc *, int);
extern int coincidence_hface_hgfc(int, Spvt **, Spvt **);
extern void HGfcOrderBoundaryEdges(HPpd *, int);
extern void hgppd_make_edge_vertex_links(HPpd *, int);

#endif // _GROUPING_H
