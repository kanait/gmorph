//
// hppd.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _HPPD_H
#define _HPPD_H

extern HPpd *create_hppd(void);
extern void FreeHppdEdge(HPpd *);
extern void FreeHppdFace(HPpd *);
extern void free_hppd(HPpd *);
extern void calc_hppdfnorm(HFace *);
extern HVertex *create_hppdvertex(HPpd *);
extern HVertex *list_hppdvertex(HPpd *, Id);
extern void free_hppdvertex(HVertex *, HPpd *);
extern HEdge *create_hppdedge(HPpd *);
extern HEdge *find_hppdedge(HVertex *, HVertex *, HPpd *);
extern HEdge *find_hppdedge_from_spvt(Spvt *, Spvt *, ScreenAtr *, HPpd *);
extern void free_hppdedge(HEdge *, HPpd *);
extern Hedvt *create_hedvt(HEdge *, Spvt *);
extern Hedvt *insert_hedvt(HEdge *, Spvt *, double);
extern void free_hppdedgevertex(HEdge *);
extern void free_hedvt(Hedvt *, HEdge *);
extern HFace *create_hppdface(HPpd *);
extern HFace *another_hface(HEdge *, HFace *);
extern HFace *list_hppdface(HPpd *, Id);
extern int find_hppdface_edge_links(HFace *, HEdge *);
extern void free_hppdface(HFace *, HPpd *);
extern HHalfedge *create_hppdhalfedge(HFace *);
extern HHalfedge *free_hppdhalfedge(HHalfedge *, HFace *);
extern void calc_hppd_boundary(HPpd *);
extern void create_hloop(HFace *, HPpd *);
extern int lp_start_end(Splp *, Spvt *);

#endif // _HPPD_H
