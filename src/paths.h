/* paths.c */
extern void makeshortestpathcb(Widget, XtPointer, XtPointer *);
extern void clearshortestpathcb(Widget, XtPointer, XtPointer *);
extern void make_shortest_path(HPpd *);
extern void initialize_shortestpath(Sppd *);
extern void exit_shortestpath(Sppd *);
extern Splp *ShortestPath_Dijkstra(Sppd *, Spvt *, Spvt *);
extern int stepnumber_to_src(VtList *, Spvt *, Spvt *);
extern Splp *vtlist_to_ppdloop(VtList *, Spvt *, Spvt *);
extern Splp *reverse_ppdloop(Splp *);
extern void cancel_create_shortestpath(ScreenAtr *);
extern void cancel_delete_shortestpath(ScreenAtr *);
extern void clear_paths(HPpd *);
extern void FreeHppdShortestPath(HPpd *);
extern void FreeHppdFaceLoop(HPpd *);
extern void make_subgraph(Sppd *);
extern int decide_steiner_number(double, double, int, double *);
extern void delete_subgraph(Sppd *);
extern Splp *ShortestPath_Boundary(Sppd *, Spvt *, Spvt *);
