//
// oppd.cpp
//
// Copyright (c) 1997 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _OPPD_H
#define _OPPD_H

extern Oppd *create_oppd(void);
extern void free_oppd(Oppd *);
extern Oso *create_osolid(Oppd *, int);
extern Opt *create_opart(Oppd *, int);
extern Ofc *create_oface(Oppd *, int);
extern Onm *create_onormal(Oppd *, int);
extern Ovt *create_overtex(Oppd *, int);

#endif // _OPPD_H
