/* sgpaths.c */
extern BOOL isokCalcShortestPath(HPpd *);
extern void SGShortestPathsCreate(HPpd *);
extern Splp *SGShortestPath(SGraph *, Sppd *, Spvt *, Spvt *);
extern Splp *CalcShortestPath(SGraph *, Sppd *);
extern Splp *sglp_to_splp(SGlp *, Sppd *);
