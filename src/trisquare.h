//
// trisquare.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _TRISQUARE_H
#define _TRISQUARE_H

extern int vertex_square(Vec2d *, QRange *);
extern BOOL isLeftSide(Vec2d *, Vec2d *, Vec2d *);
extern BOOL isLeftSidePivot(Vec2d *, Vec2d *, Vec2d *);
extern void swap_sign(int *, int *);
extern void swap_vec2d(Vec2d *, Vec2d *);
extern BOOL isHGvtLeftSide(HGvt *, HGvt *, HGvt *);
extern double isLeftVal(Vec2d *, Vec2d *, Vec2d *);
extern BOOL isHGvtLineSegmentCrossing(HGvt *, HGvt *, HGvt *, HGvt *);
extern BOOL isLineSegmentCrossing(Vec2d *, Vec2d *, Vec2d *, Vec2d *);
extern void LineIntersectionPoint(Vec2d *, Vec2d *, Vec2d *, Vec2d *, Vec2d *);
extern int line_line(Vec2d *, Vec2d *, Vec2d *, Vec2d *);
extern int line_line_param(Vec2d *, Vec2d *, Vec2d *, Vec2d *, double *, double *, unsigned short *);
extern BOOL isPointinHGsf(HGsf *, Vec2d *);
extern BOOL isHGvtinHGsf(HGsf *, HGvt *);
extern void VertexTriangleBarycentric(HGsf *, Vec2d *, double *, double *, double *);
extern int hg_vertex_triangle_param(HGsf *, Vec2d *, double *, double *, double *);
extern double point_line_distance_param(Vec2d *, Vec2d *, Vec2d *, double *);
extern double point_line_distance(Vec2d *, Vec2d *, Vec2d *);
extern int hg_triangle_square_intersection(HGsf *, QRange *);
extern int line_square_intersection(QRange *, Vec2d *, Vec2d *);
extern int vertex_line(Vec2d *, Vec2d *, Vec2d *);

#endif // _TRISQUARE_H
