//
// ppdlist.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _PPDLIST_H
#define _PPDLIST_H

extern void write_ppd_file(char *, Sppd *);
extern Sppd *open_ppd(char *);
extern int gppd_ok(char *);
extern int ppd_ok(char *, int);
extern void printppd(Sppd *);

#endif // _PPDLIST_H
