//
// quadtree.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _QUADTREE_H
#define _QUADTREE_H

extern QTree *create_qtreechild(QTree *, int, int, double, double, double, double);
extern QTree *create_qtreechild_qr(QTree *, int, int, QRange *);
extern QVertex *insert_qtree_vertex(Spvt *, QTree *);
extern QEdge *insert_qtree_edge(Sped *, QTree *);
extern QFace *insert_qtree_face(HGsf *, QTree *);
extern void free_ppdqtree(Sppd *);
extern void free_ppdqtree_child(QTree *, Sppd *);
extern int free_noinfo_ppdqtree_child(QTree *, Sppd *);
extern void free_qedge(QTree *);
extern void delete_qtree_edge(QEdge *, QTree *);
extern void free_qvertex(QTree *);
extern void delete_qtree_vertex(QVertex *, QTree *);
extern void free_qface(QTree *);
extern void delete_qtree_face(QFace *, QTree *);
extern int decide_qrange_child_number(Vec2d *, QRange *, QRange *);
extern int decide_qrange_child_num(Vec2d *, QRange *);
extern void subdivide_qrange(QRange *, int, QRange *);
extern QTree *init_qtree(Sppd *);
extern void ppdvertex_to_ppdqtree(Sppd *);
extern void decide_qvertex_child(QTree *, Spvt *, Sppd *);
extern void ppdedge_to_ppdqtree(Sppd *);
extern void decide_qedge_child(QTree *, Sped *, Sppd *);
extern QTree *init_hgppdqtree(HGfc *);
extern void hged_to_hgppdqtree(HGfc *);
extern void decide_hgqedge_child(QTree *, Sped *, HGfc *);
extern void free_hgppdqtree(HGfc *);
extern void free_hgppdqtree_child(QTree *, HGfc *);
extern void hgppdsurface_to_hgppdqtree(HGfc *);
extern void decide_qface_child(QTree *, HGsf *, HGfc *);
extern void printqface(QTree *);

#endif // _QUADTREE_H
