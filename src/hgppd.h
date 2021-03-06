//
// hgppd.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _HGPPD_H
#define _HGPPD_H

extern HGppd *create_hgppd(void);
extern void free_hgppd(HGppd *);
extern HGfc *create_hgppdface(HGppd *);
extern HGfc *create_hgfc(void);
extern HGfc *find_hgfc(HGppd *, int);
extern void free_hgfc(HGfc *);
extern void free_hgppdface(HGfc *, HGppd *);
extern HGvt *create_hgppdvertex(HGfc *);
extern void free_hgppdvertex(HGvt *, HGfc *);
extern HGvted *create_hgvted(HGvt *, HGed *);
extern void insert_hgvted(HGvt *, HGed *);
extern HGvted *InsertHGvted(HGvt *, HGvted *, HGed *);
extern double hg_calc_angle(HGvt *, HGvt *, HGvt *);
extern HGvt *hg_another_vt(HGed *, HGvt *);
extern HGvt *HGedAnotherVertex(HGed *, HGvt *);
extern HGsf *HGedLeftFace(HGed *, HGvt *);
extern HGsf *HGedRightFace(HGed *, HGvt *);
extern void HGedAppendLeftFace(HGed *, HGvt *, HGsf *);
extern HGvted *find_hgvted(HGvt *, HGed *);
extern HGed *HGvtedNextCCWEdge(HGvt *, HGed *);
extern void free_hgppdvertexedge(HGvt *);
extern void free_hgvted(HGvted *, HGvt *);
extern HGvtvt *create_hgvtvt(HGvt *, Id);
extern HGvtvt *find_sort_hgvtvt(HGvt *, Id);
extern void FreeHGppdVertexVertex(HGfc *);
extern void free_hgppdvertexvertex(HGvt *);
extern void free_hgvtvt(HGvtvt *, HGvt *);
extern HGlp *create_hgppdloop(HGfc *);
extern void free_hgppdloop(HGlp *, HGfc *);
extern HGcv *create_hgppdctrlvertex(HGfc *);
extern void free_hgppdctrlvertex(HGcv *, HGfc *);
extern HGsf *create_hgppdsurface(HGfc *);
extern void free_hgppdsurface(HGsf *, HGfc *);
extern HGsf *create_hgppdsurface_edge(HGfc *, HGvt *, HGvt *, HGvt *, HGed *, HGed *, HGed *);
extern HGsf *another_hgsf(HGed *, HGsf *);
extern HGhe *create_hgppdhalfedge(HGsf *);
extern HGhe *free_hgppdhalfedge(HGhe *, HGsf *);
extern void CalcHGsfNorm(HGfc *);
extern void calc_hgsfnorm(HGsf *);
extern void FreeHGppd(HPpd *);
extern void FreeHGppdFace(HGppd *);
extern void FreeHGppdVertex(HGfc *);
extern void FreeHGppdEdge(HGfc *);
extern void FreeHGppdSurface(HGfc *);
extern void FreeHGppdLoop(HGfc *);
extern void FreeHGppdCtrlvertex(HGfc *);
extern HGlp *find_hgppdloop(Splp *, HGfc *);
extern HGcv *find_hgppdctrlvertex(Spvt *, HGfc *);
extern Sppd *hgfc_to_ppd(HGfc *);
extern void printhgfc(HGfc *, int);
extern void HGfcTriangulation(HGfc *);
extern void HGsfTriangulation(HGsf *, HGfc *);
extern void HGfcTriangulation_noEdge(HGfc *);
extern void HGsfTriangulation_noEdge(HGsf *, HGfc *);

#endif // _HGPPD_H
