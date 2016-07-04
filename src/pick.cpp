/* Copyright (c) 1997-1998 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>
#include "smd.h"
#include "ppdvertex.h"
#include "draw.h"
#include "pick.h"
#include "sellist.h"
#include "trisquare.h"
#include "veclib.h"

BOOL edit_pick( int x, int y, int edit_mode, ScreenAtr *screen )
{
	Spvt *vt = NULL;
	Splp *lp = NULL;
	Spfc *fc = NULL;
	HVertex *hvt = NULL;
	HFace *hfc = NULL;
	Sppd *ppd = screen->current_ppd;
	Sppd *gppd = swin->morph_ppd;
	HPpd *hppd = swin->hppd;
	
	if ( ppd == NULL ) return FALSE;
	
	switch ( edit_mode ) {
		
	case EDIT_CREATE_PPDLOOP:

		if ( (vt = pick_ppdvertex_screen( x, y, screen, ppd )) == NULL ) {
			return FALSE;
		}
		if ( vt->col == PNTRED ) return FALSE;
		
		FreeSelectList( screen );
		
		vt->col = PNTRED;
		create_selectlist_vt( screen, vt );

		return TRUE;
		
	case EDIT_DELETE_PPDLOOP:
		
		if ( (lp = pick_ppdloop_screen( x, y, screen, ppd )) == NULL ) {
			return FALSE;
		}
		if ( lp->col == LOOPRED ) return FALSE;
		
		FreeSelectList( screen );
		
		lp->col = LOOPRED;
		create_selectlist_lp( screen, lp );

		return TRUE;
		
	case EDIT_CREATE_PPDFACE:

		if ( (vt = pick_ppdvertex_screen( x, y, screen, ppd )) == NULL ) {
			return FALSE;
		}
		if ( vt->col == PNTRED ) return FALSE;
		
		vt->col = PNTRED;
		create_selectlist_vt( screen, vt );
		
		return TRUE;
		
	case EDIT_DELETE_PPDFACE:

		if ( (fc = pick_ppdface_screen( x, y, screen, ppd )) == NULL ) {
			return FALSE;
		}
		if ( fc->col == FACERED ) return FALSE;
		
		FreeSelectList( screen );
		
		fc->col = FACERED;
		create_selectlist_ppdface( screen, fc );
		
		return TRUE;

	case EDIT_CREATE_CV:

		if ( (vt = pick_ppdvertex_screen( x, y, screen, ppd )) == NULL ) {
			return FALSE;
		}
		if ( vt->col == PNTRED ) return FALSE;
		
		FreeSelectList( screen );
		
		vt->col = PNTRED;
		create_selectlist_vt( screen, vt );
		
		return TRUE;
		
	case EDIT_MOVE_CV:
		return FALSE;
		
	case EDIT_DELETE_CV:
		return FALSE;
		
	case EDIT_CREATE_CMESH:
		
		if ( (hvt = pick_hvertex_screen( x, y, screen, hppd )) == NULL ) {
			return FALSE;
		}

		if ( hvt->col != PNTGREEN ) return FALSE;

		hvt->col = PNTRED;
		create_selectlist_hvt(screen, hvt);
		return TRUE;
		
	case EDIT_DELETE_CMESH:

		if ( (hfc = pick_hface_screen( x, y, screen, hppd )) == NULL ) {
			return FALSE;
		}

		if ( hfc->col == FACERED ) return FALSE;

		hfc->col = FACERED;
		create_selectlist_hface(screen, hfc);

		return TRUE;
		
	case EDIT_CREATE_SPATH:

		if ( screen->n_sellist == 2 ) return FALSE;
		
		if ( (vt = pick_ppdvertex_screen( x, y, screen, ppd )) == NULL ) {
			return FALSE;
		}
		if ( vt->col == PNTRED ) return FALSE;

		vt->col = PNTRED;
		create_selectlist_vt( screen, vt );

		return TRUE;
		
	case EDIT_DELETE_SPATH:

		if ( (lp = pick_splp_screen( x, y, screen, hppd )) == NULL ) {
			return FALSE;
		}

		if ( lp->col == LOOPRED ) return FALSE;

		FreeSelectList( screen );

		lp->col = PNTRED;
		create_selectlist_lp( screen, lp );

		return TRUE;
		
	case EDIT_CREATE_SPATH_MANU:

		if ( gppd == NULL ) return FALSE;
		if ( (vt = pick_ppdvertex_screen( x, y, screen, gppd )) == NULL ) {
			return FALSE;
		}

		if ( vt->col == PNTRED ) return FALSE;

		vt->isConst = SMD_ON;
		vt->col = PNTRED;
		create_selectlist_vt( screen, vt );

		return TRUE;
	}
	return FALSE;
}

BOOL edit_pick_area( int bx, int by, int ex, int ey,
					int edit_mode, ScreenAtr *screen )
{
	Spvt *vt = NULL;
	Sppd *ppd = screen->current_ppd;
	
	if ( ppd == NULL ) return FALSE;
	
	switch ( edit_mode ) {
		
	case EDIT_CREATE_PPDLOOP:
		if ( (vt = pick_ppdvertex_screen_area( bx, by, ex, ey, screen, ppd )) == NULL ) {
			return FALSE;
		}
		if ( vt->col == PNTRED ) return FALSE;
		
		FreeSelectList( screen );
		
		vt->col = PNTRED;
		create_selectlist_vt( screen, vt );
		return TRUE;
		
	case EDIT_CREATE_PPDFACE:
		if ( (vt = pick_ppdvertex_screen_area( bx, by, ex, ey, screen, ppd )) == NULL ) {
			return FALSE;
		}
		if ( vt->col == PNTRED ) return FALSE;
		
		FreeSelectList( screen );
		
		vt->col = PNTRED;
		create_selectlist_vt( screen, vt );
		return TRUE;
		
	case EDIT_CREATE_CV:
		if ( (vt = pick_ppdvertex_screen_area( bx, by, ex, ey, screen, ppd )) == NULL ) {
			return FALSE;
		}
		if ( vt->col == PNTRED ) return FALSE;
		
		FreeSelectList( screen );
		
		vt->col = PNTRED;
		create_selectlist_vt( screen, vt );
		return TRUE;
		
	case EDIT_MOVE_CV:
		return FALSE;
		
	case EDIT_DELETE_CV:
		return FALSE;
		
	case EDIT_CREATE_CMESH:
		return FALSE;
		
	case EDIT_CREATE_SPATH:
		if ( (vt = pick_ppdvertex_screen_area( bx, by, ex, ey, screen, ppd )) == NULL ) {
			return FALSE;
		}
		if ( vt->col == PNTRED ) return FALSE;
		
		FreeSelectList( screen );
		
		vt->col = PNTRED;
		create_selectlist_vt( screen, vt );
		return TRUE;
		
	case EDIT_CREATE_SPATH_MANU:
		if ( (vt = pick_ppdvertex_screen_area( bx, by, ex, ey, screen, ppd )) == NULL ) {
			return FALSE;
		}
		if ( vt->col == PNTRED ) {
			AfxMessageBox("This vertex has been already selected.");
			return FALSE;		
		}
		
		vt->col = PNTRED;
		create_selectlist_vt( screen, vt );
		return TRUE;
		
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// pick hface functions
//////////////////////////////////////////////////////////////////////

#define PICKPOINTSIZE 5

static BOOL pick_on_point( double x, double y, double ix, double iy, double *dis )
{
	
	double subx, suby;
	
	subx = x - ix; suby = y - iy;
	
	if ( (fabs( subx ) < PICKPOINTSIZE) &&
		(fabs( suby ) < PICKPOINTSIZE) ) {
		*dis = sqrt(subx*subx+suby*suby);
		return TRUE;
	}
	return FALSE;
}

Spvt *pick_ppdvertex_screen( int x, int y, ScreenAtr *screen, Sppd *ppd )
{
	int    cnt;
	Spvt   *v, *pvt;
	double ix, iy;
	Vec2d  win2;
	double dis,dis0;
	
	if ( ppd == (Sppd *) NULL ) return (Spvt *) NULL;
	
	get_GL_attributes(screen);
	
	ix = (double) x;
	iy = (double) screen->viewport[3] - (double) y;
	
	cnt = 0;
	pvt = (Spvt *) NULL;
	for ( v = ppd->spvt; v != (Spvt *) NULL; v = v->nxt ) {
		world_to_win( &(v->vec), &(win2), screen->mmat, screen->pmat,
			screen->viewport );
		// pick.
		if ( pick_on_point( win2.x, win2.y, ix, iy, &dis ) == TRUE) {
			
			if ( cnt ) {
				if ( dis < dis0 ) {
					dis0 = dis;
					pvt  = v;
					++cnt;
				}
			} else {
				dis0 = dis;
				pvt  = v;
				++cnt;
			}
			
		}
	}
	
	return pvt;
}

Spvt *pick_ppdvertex_spath_screen( int x, int y, ScreenAtr *screen, Sppd *ppd )
{
	int    cnt;
	Spvt   *v, *pvt, *org_vt;
	Vted   *ve;
	double ix, iy;
	Vec2d  win2;
	double dis, dis0;
	
	if ( ppd == (Sppd *) NULL ) return (Spvt *) NULL;
	
	if ( screen->n_sellist ) {
		
		get_GL_attributes( screen );
		
		ix = (double) x;
		iy = (double) screen->viewport[3] - (double) y;
		
		cnt = 0;
		pvt = (Spvt *) NULL;
		
		org_vt = screen->sel_last->vt;
		
		for ( ve = org_vt->svted; ve != (Vted *) NULL; ve = ve->nxt ) {
			
			v = another_vt( ve->ed, org_vt );
			world_to_win( &(v->vec), &(win2), screen->mmat, screen->pmat,
				screen->viewport );

			// pick.
			if ( pick_on_point( win2.x, win2.y, ix, iy, &dis ) == TRUE ) {
				
				if ( cnt ) {
					if ( dis < dis0 ) {
						dis0 = dis;
						pvt  = v;
						++cnt;
					}
				} else {
					dis0 = dis;
					pvt  = v;
					++cnt;
				}
				
			}
		}
		
		return pvt;
		
	} else {
		return pick_ppdvertex_screen( x, y, screen, ppd );
	}
    
}

static int sc_in_area(Vec2d * vec, Vec2d * org, Vec2d * atv)
{
	if ((vec->x >= org->x) && (vec->x <= atv->x) &&
		(vec->y <= org->y) && (vec->y >= atv->y))
		return SMD_ON;
	
	return SMD_OFF;
}

Spvt *pick_ppdvertex_screen_area(int bx, int by, int ex, int ey, ScreenAtr *screen, Sppd *ppd)
{
	Vec2d  win2, vb, ve;
	
	if ( ppd == (Sppd *) NULL ) return (Spvt *) NULL;
	
	get_GL_attributes(screen);
	
	vb.x = (double) bx;
	vb.y = (double) screen->viewport[3] - (double) by;
	
	ve.x = (double) ex;
	ve.y = (double) screen->viewport[3] - (double) ey;
	
	for ( Spvt *v = ppd->spvt; v != (Spvt *) NULL; v = v->nxt ) {
		world_to_win( &(v->vec), &(win2), screen->mmat, screen->pmat,
			screen->viewport );
		if ( sc_in_area(&(win2), &(vb), &(ve)) ) {
			return v;
		}
	}
	
	return (Spvt *) NULL;
}

HVertex *pick_hvertex_screen(int x, int y, ScreenAtr *screen, HPpd *hppd)
{
	HVertex *hvt, *pvt;
	Spvt   *vt;
	double ix, iy;
	int    cnt;
	double dis, dis0;
	Vec2d  win2;
	
	if ( hppd == (HPpd *) NULL ) return (HVertex *) NULL;
	
	get_GL_attributes(screen);
	
	ix = (double) x;
	iy = (double) screen->viewport[3] - (double) y;
	
	pvt = (HVertex *) NULL;
	cnt = 0;
	for ( hvt = hppd->shvt; hvt != (HVertex *) NULL; hvt = hvt->nxt ) {
		
		if ( screen->no == SCREEN_SRC ) vt = hvt->vt1;
		else vt = hvt->vt2;
		
		world_to_win( &(vt->vec), &(win2), screen->mmat, screen->pmat,
			screen->viewport );

		// pick.
		if ( pick_on_point( win2.x, win2.y, ix, iy, &dis) == TRUE ) {
			
			if ( cnt ) {
				if ( dis < dis0 ) {
					dis0 = dis;
					pvt  = hvt;
					++cnt;
				}
			} else {
				dis0 = dis;
				pvt  = hvt;
				++cnt;
			}
			
		}
	}
	
	return (HVertex *) pvt;
}

HVertex *pick_hvertex_screen_area(int x, int y, ScreenAtr *screen, HPpd *hppd)
{
	HVertex *hvt;
	Spvt   *v;
	double ix, iy;
	Vec2d  win2;
	
	if ( hppd == (HPpd *) NULL ) return (HVertex *) NULL;
	
	get_GL_attributes( screen );
	
	ix = (double) x;
	iy = (double) screen->viewport[3] - (double) y + PICKPOINTSIZE;
	
	for ( hvt = hppd->shvt; hvt != (HVertex *) NULL; hvt = hvt->nxt ) {
		
		if ( screen->no == SCREEN_SRC ) v = hvt->vt1;
		else v = hvt->vt2;
		
		world_to_win( &(v->vec), &(win2), screen->mmat, screen->pmat,
			screen->viewport );
		if ( sc_in_area(&(win2), &(screen->areaorg), &(screen->areaatv)) ) {
			return hvt;
		}
	}
	
	return (HVertex *) NULL;
}

//////////////////////////////////////////////////////////////////////
// pick hface functions
//////////////////////////////////////////////////////////////////////

/* left or right ? */
static BOOL V2LR(Vec2d *a, Vec2d *b)
{
	double fg;
	
	fg =a->x * b->y - b->x * a->y;
	
	if ( fg >= 0.0 ) return TRUE;
	else return FALSE;
}

static BOOL point_in_hface( HFace *fc, double x, double y, ScreenAtr *screen )
{
	HHalfedge *he1, *he2;
	Spvt   *vt1, *vt2;
	Vec2d  v1, v2, sub1, sub0;
	BOOL first_sign, sign;
	
	he1 = fc->shhe;
	he2 = he1->nxt;
	
	vt1 = ( !screen->no ) ? he1->vt->vt1 : he1->vt->vt2;
	vt2 = ( !screen->no ) ? he2->vt->vt1 : he2->vt->vt2;
	
	/* first edge */ 
	world_to_win( &(vt1->vec), &(v1), screen->mmat, screen->pmat,
		screen->viewport );
	world_to_win( &(vt2->vec), &(v2), screen->mmat, screen->pmat,
		screen->viewport );
	
	V2Sub( &(v2), &(v1), &sub0 );
	sub1.x = x - v1.x;
	sub1.y = y - v1.y;
	first_sign = V2LR( &(sub0), &(sub1) );
	
	he1 = he2;
	he2 = he2->nxt;
	
	do {
		vt1 = ( !screen->no ) ? he1->vt->vt1 : he1->vt->vt2;
		vt2 = ( !screen->no ) ? he2->vt->vt1 : he2->vt->vt2;
		world_to_win( &(vt1->vec), &(v1), screen->mmat, screen->pmat,
			screen->viewport );
		world_to_win( &(vt2->vec), &(v2), screen->mmat, screen->pmat,
			screen->viewport );
		
		V2Sub( &(v2), &(v1), &sub0 );
		sub1.x = x - v1.x;
		sub1.y = y - v1.y;
		sign = V2LR( &(sub0), &(sub1) );
		
		if ( sign != first_sign ) {
			return FALSE;
		}
		
		he1 = he2;
		he2 = he2->nxt;
		
	} while ( he1 != fc->shhe );
	
	return TRUE;
}    

HFace *pick_hface_screen( int x, int y, ScreenAtr *screen, HPpd *hppd )
{
	HFace  *hfc;
	double ix, iy;
	
	if ( hppd == (HPpd *) NULL ) return (HFace *) NULL;
	
	get_GL_attributes( screen );
	
	ix = (double) x;
	iy = (double) screen->viewport[3] - (double) y;
	
	for ( hfc = hppd->shfc; hfc != (HFace *) NULL; hfc = hfc->nxt ) {

		// pick.
		if( point_in_hface( hfc, ix, iy, screen ) == TRUE ) {
			return hfc;
		}
		
	}
	return (HFace *) NULL;
}

static BOOL point_on_line( Vec2d *v, Vec2d *ev1, Vec2d *ev2, double *dis )
{
	double t;
	
	*dis = point_line_distance_param( v, ev1, ev2, &t );
	
	if ( (*dis < 5) && ( t > 0.0 ) && ( t < 1.0) ) {
		return TRUE;
	} else {
		return FALSE;
	}

}

Splp *pick_ppdloop_screen( int x, int y, ScreenAtr *screen, Sppd *ppd )
{
	int    cnt;
	Splp   *lp, *rlp;
	double dis0, dis;
	Splv   *lv, *nlv;
	Vec2d  ivec, vec1, vec2;
	
	if ( ppd == (Sppd *) NULL ) return (Splp *) NULL;
	
	get_GL_attributes( screen );
	
	ivec.x = (double) x;
	ivec.y = (double) screen->viewport[3] - (double) y;
	
	cnt = 0;
	rlp = (Splp *) NULL;
	for ( lp = ppd->splp; lp != (Splp *) NULL; lp = lp->nxt ) {
		
		nlv = lp->splv;
		lv = nlv->nxt;
		
		world_to_win( &(nlv->vt->vec), &(vec1), screen->mmat, screen->pmat,
			screen->viewport );
		
		while ( lv != (Splv *) NULL ) {
			
			world_to_win( &(lv->vt->vec), &(vec2), screen->mmat, screen->pmat,
				screen->viewport );
			
			// pick.
			if ( point_on_line( &(ivec), &(vec1), &vec2, &dis) == TRUE ) {
				if ( cnt ) {
					if ( dis < dis0 ) {
						dis0 = dis;
						rlp = lp;
						++cnt;
					}
				} else {
					++cnt;
					dis0 = dis;
					rlp = lp;
				}
			}
			
			nlv = lv;
			lv = lv->nxt;
			vec1.x = vec2.x;
			vec1.y = vec2.y;
			
		}
		
	}
	
	return rlp;
}

Splp *pick_splp_screen( int x, int y, ScreenAtr *screen, HPpd *hppd )
{
	int    cnt;
	HEdge  *hed;
	Splp   *lp, *rlp;
	double dis0, dis;
	Splv   *lv, *nlv;
	Vec2d  ivec, vec1, vec2;
	
	if ( hppd == (HPpd *) NULL ) return (Splp *) NULL;
	
	get_GL_attributes( screen );
	
	ivec.x = (double) x;
	ivec.y = (double) screen->viewport[3] - (double) y;
	
	cnt = 0;
	rlp = (Splp *) NULL;
	for ( hed = hppd->shed; hed != (HEdge *) NULL; hed = hed->nxt ) {
		
		lp = (!screen->no) ? hed->lp1 : hed->lp2;
		
		if ( lp != (Splp *) NULL ) {
			
			nlv = lp->splv;
			lv = nlv->nxt;
			
			world_to_win( &(nlv->vt->vec), &(vec1), screen->mmat, screen->pmat,
				screen->viewport );
			
			while ( lv != (Splv *) NULL ) {
				
				world_to_win( &(lv->vt->vec), &(vec2), screen->mmat, screen->pmat,
					screen->viewport );

				// pick.
				if ( point_on_line( &(ivec), &(vec1), &vec2, &dis) == TRUE ) {
					if ( cnt ) {
						if ( dis < dis0 ) {
							dis0 = dis;
							rlp = lp;
							++cnt;
						}
					} else {
						++cnt;
						dis0 = dis;
						rlp = lp;
					}
				}
				
				nlv = lv;
				lv = lv->nxt;
				vec1.x = vec2.x;
				vec1.y = vec2.y;
				
			}
			
		}
	}
	
	return rlp;
}

//////////////////////////////////////////////////////////////////////
// pick ppdface functions
//////////////////////////////////////////////////////////////////////

static BOOL point_in_ppdface( Spfc *fc, double x, double y, ScreenAtr *screen )
{
  Sphe *he1, *he2;
  Spvt   *vt1, *vt2;
  Vec2d  v1, v2, sub1, sub0;
  BOOL first_sign, sign;

  he1 = fc->sphe;
  he2 = he1->nxt;

  vt1 = he1->vt; vt2 = he2->vt;
  
  /* first edge */ 
  world_to_win( &(vt1->vec), &(v1), screen->mmat, screen->pmat, screen->viewport );
  world_to_win( &(vt2->vec), &(v2), screen->mmat, screen->pmat,	screen->viewport );
  
  V2Sub( &(v2), &(v1), &sub0 );
  sub1.x = x - v1.x;
  sub1.y = y - v1.y;
  first_sign = V2LR( &(sub0), &(sub1) );

  he1 = he2;
  he2 = he2->nxt;

  do {
    vt1 = he1->vt;
    vt2 = he2->vt;
    world_to_win( &(vt1->vec), &(v1), screen->mmat, screen->pmat,
		  screen->viewport );
    world_to_win( &(vt2->vec), &(v2), screen->mmat, screen->pmat,
		  screen->viewport );
  
    V2Sub( &(v2), &(v1), &sub0 );
    sub1.x = x - v1.x;
    sub1.y = y - v1.y;
    sign = V2LR( &(sub0), &(sub1) );

    if ( sign != first_sign ) {
      return FALSE;
    }

    he1 = he2;
    he2 = he2->nxt;
    
  } while ( he1 != fc->sphe );

  return TRUE;
}    

Spfc *pick_ppdface_screen( int x, int y, ScreenAtr *screen, Sppd *ppd )
{
	Spfc  *fc;
	double ix, iy;
	
	if ( ppd == (Sppd *) NULL ) return (Spfc *) NULL;
	
	get_GL_attributes( screen );
	
	ix = (double) x;
	iy = (double) screen->viewport[3] - (double) y;
	
	for ( fc = ppd->spfc; fc != (Spfc *) NULL; fc = fc->nxt ) {
		
		// ñ@ê¸ï˚å¸Ç‡ï]âøÇ…Ç¢ÇÍÇÈÇÊÇ§Ç…Ç∑ÇÈ
		if( point_in_ppdface( fc, ix, iy, screen ) == TRUE ) {
			return fc;
		}
		
	}
	return (Spfc *) NULL;
}


