/* sellist.c */
extern SelList *create_selectlist_vt(ScreenAtr *, Spvt *);
extern SelList *create_selectlist_hvt(ScreenAtr *, HVertex *);
extern SelList *create_selectlist_hface(ScreenAtr *, HFace *);
extern SelList *create_selectlist_ppdface(ScreenAtr *, Spfc *);
extern SelList *create_selectlist_lp(ScreenAtr *, Splp *);
extern SelList *list_selectlist(ScreenAtr *, Id);
extern void FreeSelectList(ScreenAtr *);
