//
// sgraph.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _SGRAPH_H
#define _SGRAPH_H

extern SGraph *create_sgraph(void);
extern void free_sgraph(SGraph *);
extern SGvt *create_sgvt(SGraph *);
extern SGvt *CreateSGvtfromSGvt(SGraph *, SGvt *);
extern void free_sgvt(SGvt *, SGraph *);
extern SGvt *another_sgvt(SGed *, SGvt *);
extern SGvt *find_sgvt_from_spvt(SGraph *, Spvt *);
extern SGvt *find_sgvt_from_spvt_number(SGraph *, int);
extern SGvt *find_sgvt_from_sgfc(SGfc *, SGvt *);
extern void FreeSGVertex(SGraph *);
extern SGvted *create_sgvted(SGvt *, SGed *);
extern void free_sgvted(SGvted *, SGvt *);
extern void FreeSGvted(SGvt *, SGed *);
extern void FreeSGVertexEdge(SGvt *);
extern SGed *create_sged(SGraph *);
extern SGed *CreateSGed(SGraph *, SGvt *, SGvt *, Sped *);
extern SGed *CreateSGedfromSGed(SGraph *, SGvt *, SGvt *, SGed *);
extern void free_sged(SGed *, SGraph *);
extern void FreeSGed(SGed *, SGraph *);
extern void FreeSGEdge(SGraph *);
extern SGed *find_sged(SGvt *, SGvt *);
extern SGfc *create_sgfc(SGraph *);
extern void free_sgfc(SGfc *, SGraph *);
extern void FreeSGFace(SGraph *);
extern SGfcvt *create_sgfcvt(SGfc *, SGvt *);
extern void free_sgfcvt(SGfcvt *, SGfc *);
extern void FreeSGFaceVertex(SGfc *);
extern SGlp *create_sglp(void);
extern void free_sglp(SGlp *);
extern SGlpvt *create_sglpvt(SGlp *, SGvt *);
extern void free_sglpvt(SGlpvt *, SGlp *);
extern void FreeSGLoopVertex(SGlp *);
extern SGlped *create_sglped(SGlp *, SGed *);
extern void free_sglped(SGlped *, SGlp *);
extern void FreeSGLoopEdge(SGlp *);
extern SGraph *initialize_sgraph(Sppd *);
extern void add_vertices_edges_sgraph(SGraph *);
extern BOOL isOnDifferentEdges(SGvt *, SGvt *);
extern SGlp *ShortestPath_Dijkstra_SGraph(SGraph *, SGvt *, SGvt *);
extern int sg_stepnumber_to_src(SGVtList *, SGvt *, SGvt *);
extern SGlp *sgvtlist_to_sglp(SGVtList *, SGvt *, SGvt *);
extern SGraph *sglp_to_sgraph(SGlp *, SGraph *);
extern void create_shortest_path(ScreenAtr *);
extern void free_splp_shortest_path(Splp *, Sppd *);
extern void delete_shortest_path(ScreenAtr *);
extern void manual_shortest_path(ScreenAtr *);
extern Splp *sellist_to_splp(ScreenAtr *);
extern void screen_initialize_sgraph(ScreenAtr *);
extern void screen_exit_sgraph(ScreenAtr *);

#endif // _SGRAPH_H
