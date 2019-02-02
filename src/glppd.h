//
// glppd.h
//
// Copyright (c) 1995-1997 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _GLPPD_H
#define _GLPPD_H

extern void drawppd_vertex(Sppd *, ScreenAtr *);
extern void drawppd_vertex_enhanced(Sppd *, ScreenAtr *);
extern void drawppd_edge(Sppd *, ScreenAtr *);
extern void drawppd_hiddenline(Sppd *, ScreenAtr *);
extern void drawppd_edge_enhanced(Sppd *, ScreenAtr *);
extern void drawppd_shading(Sppd *, ScreenAtr *);
extern void drawhppd_cmesh(HPpd *, ScreenAtr *);
extern void drawhppd_cmesh_enhanced(HPpd *, ScreenAtr *);
extern void drawhppd_cpoint_enhanced(HPpd *, ScreenAtr *);
extern void drawhppd_group(HPpd *, ScreenAtr *, int);
extern void drawhppd_group_enhanced(HPpd *, ScreenAtr *);
extern void drawhppd_hloop(HPpd *, ScreenAtr *);
extern void drawhppd_shortestpath(HPpd *, ScreenAtr *);
extern void drawppd_loop(Sppd *, ScreenAtr *);
extern void draw_loop(Splp *);
extern void draw_sglp(SGlp *);
extern void drawppd_loop_enhanced(Sppd *, ScreenAtr *);
extern void draw_loop_enhanced(Splp *, ScreenAtr * );
extern void drawhppd_hmap(HPpd *, ScreenAtr *);
/* from gldraw.c */
extern void glu_sphere(Vec *, double);
extern void glu_cylinder(Vec *, Vec *, double);
extern void material_binding(Material *);

#endif // _GLPPD_H
