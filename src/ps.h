//
// ps.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _PS_H
#define _PS_H

extern void pstran(Vec2d *, Vec2d *);
extern void pstran_p(Vec2d *, Vec2d *);
extern void hppd_harmonicmap_to_ps(HPpd *);
extern void mhgfc_harmonicmap_to_ps(HPpd *);
extern void hgfc_harmonicmap_to_ps(char *, HGfc *);
extern void tmp_hgfc_harmonicmap_to_ps(char *, HGfc *, HGfc *, HGfc *);
extern void harmonicmap_to_ps(char *, Sppd *);
extern void psharmonicppdedge( FILE *, Sppd * );

#endif // _PS_H
