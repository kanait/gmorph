/* oppd.c */
extern Oppd *create_oppd(void);
extern void free_oppd(Oppd *);
extern Oso *create_osolid(Oppd *, int);
extern Opt *create_opart(Oppd *, int);
extern Ofc *create_oface(Oppd *, int);
extern Onm *create_onormal(Oppd *, int);
extern Ovt *create_overtex(Oppd *, int);
