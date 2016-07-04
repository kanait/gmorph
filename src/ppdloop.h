/* ppdloop.c */
extern Splp *create_splp(void);
extern Splp *create_ppdloop(Sppd *);
extern Splp *find_ppdloop(Sppd *, Spvt *);
extern void free_splp(Splp *);
extern void free_ppdloop(Splp *, Sppd *);
extern Splv *create_ppdloopvertex(Splp *);
extern Splv *find_ppdloopvertex(Splp *, Spvt *);
extern void free_ppdloopvertex(Splv *, Splp *);
extern Sple *create_ppdloopedge(Splp *);
extern void free_ppdloopedge(Sple *, Splp *);
extern Splp *reverse_ppdloop( Splp * );