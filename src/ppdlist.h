/* ppdlist.c */
extern void write_ppd_file(char *, Sppd *);
extern Sppd *open_ppd(char *);
extern int gppd_ok(char *);
extern int ppd_ok(char *, int);
extern void printppd(Sppd *);
