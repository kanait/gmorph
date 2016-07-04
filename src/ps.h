/* ps.c */
extern void pstran(Vec2d *, Vec2d *);
extern void pstran_p(Vec2d *, Vec2d *);
extern void hppd_harmonicmap_to_ps(HPpd *);
extern void mhgfc_harmonicmap_to_ps(HPpd *);
extern void hgfc_harmonicmap_to_ps(char *, HGfc *);
extern void tmp_hgfc_harmonicmap_to_ps(char *, HGfc *, HGfc *, HGfc *);
extern void harmonicmap_to_ps(char *, Sppd *);
extern void psharmonicppdedge( FILE *, Sppd * );
