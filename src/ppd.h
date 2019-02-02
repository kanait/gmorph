//
// ppd.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _PPD_H
#define _PPD_H

extern Sppd *create_ppd(void);
extern void free_ppd(Sppd *);
extern void reset_ppd(Sppd *);
extern Sppd *copy_ppd(Sppd *);
extern void clear_newppd_links(Sppd *);
extern void calc_ppd_boundary(Sppd *);
extern void normalize_ppd(Sppd *);
extern void unnormalize_ppd(Sppd *);

#endif // _PPD_H
