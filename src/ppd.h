/* ppd.c */
extern Sppd *create_ppd(void);
extern void free_ppd(Sppd *);
extern void reset_ppd(Sppd *);
extern Sppd *copy_ppd(Sppd *);
extern void clear_newppd_links(Sppd *);
extern void calc_ppd_boundary(Sppd *);
extern void normalize_ppd(Sppd *);
extern void unnormalize_ppd(Sppd *);
