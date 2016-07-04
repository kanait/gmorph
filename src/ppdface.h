/* ppdface.c */
extern Spfc *create_ppdface(Sppd *);
extern Spfc *create_ppdface_hedge(Sppd *, Spvt *, Spvt *, Spvt *, Sped *, Sped *, Sped *);
extern Spvt *other_vertices_face_left(Spfc *, Spvt *);
extern Spvt *other_vertices_face_right(Spfc *, Spvt *);
extern void free_ppdface(Spfc *, Sppd *);
extern void free_ppdface_withqtree(Spfc *, Sppd *);
extern Sphe *create_ppdhalfedge(Spfc *);
extern Sphe *free_ppdhalfedge(Sphe *, Spfc *);
extern void makenull_ppdhalfedge(Sped *, Spfc *);
extern Spfc *find_ppdface_ppdedge(Sped *, Spvt *, Spvt *);
extern Sphe *find_hedge_edge(Sped *, Spfc *);
extern void calc_fnorm(Spfc *);
extern void cancel_create_ppdface(void);
extern void cancel_delete_ppdface(void);
