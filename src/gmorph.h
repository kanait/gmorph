/* gmorph.c */
extern Sppd *ppdgmorph_v2(HPpd *);
extern void initialize_gmorphv2(HPpd *);
extern void after_morphing(Sppd *);
extern void clear_gmorph(HPpd *);
extern void record_morphppd(char *, Sppd *);
extern void write_gmh_file(char *, HPpd *);
extern HPpd *open_gmh_file(char *);
extern Splp *create_shortestpath(char *, Sppd *);
extern int gmh_ok(char *);
extern void PrintGPpd( Sppd * );
extern void resetmorphppd( Sppd * );
extern void setinterpppd( Sppd *, double );