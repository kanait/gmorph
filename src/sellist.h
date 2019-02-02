//
// sellist.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _SELLIST_H
#define _SELLIST_H

extern SelList *create_selectlist_vt(ScreenAtr *, Spvt *);
extern SelList *create_selectlist_hvt(ScreenAtr *, HVertex *);
extern SelList *create_selectlist_hface(ScreenAtr *, HFace *);
extern SelList *create_selectlist_ppdface(ScreenAtr *, Spfc *);
extern SelList *create_selectlist_lp(ScreenAtr *, Splp *);
extern SelList *list_selectlist(ScreenAtr *, Id);
extern void FreeSelectList(ScreenAtr *);

#endif // _SELLIST_H
