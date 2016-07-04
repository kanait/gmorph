/* Copyright (c) 1995-1997 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>
#include "gl\gl.h"
#include "gl\glu.h"

#include "smd.h"
#include "glppd.h"

#ifndef _COLOR_H
#include "color.h"
#endif

#ifndef _MTL_H
#include "mtl.h"
#endif

/* #define screen->rad_sph  0.1 */
//#define screen->rad_sph  0.01
//#define SMALL_SPHERE_RADIUS  0.008
/* #define SMALL_SPHERE_RADIUS  0.05 */
/* #define screen->rad_cyl    0.05 */
//#define screen->rad_cyl    0.005
#define NUM_GROUP_EDGE 5

static Material line_mat[] = {
	0.187004f, 0.138930f, 0.138930f, 1.0f,
		0.748016f, 0.75721f,  0.155721f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.836364f, 0.836364f, 0.836364f, 1.0f,
		77.575806f
};

static Material pointred_mat[] = {
	0.187004f, 0.0f, 0.0f, 1.0f,
		0.748016f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.672727f, 0.672727f, 0.672727f, 1.0f,
		29.478785f
};

static Material point_mat[] = {
	0.005183f, 0.084911f, 0.084911f, 1.0f,
		0.020732f, 0.339645f, 0.339645f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.903030f, 0.903030f, 0.903030f, 1.0f,
		118.690941f
};

static Material vertex_mat[] = {
	0.0f, 0.187004f, 0.187004f, 1.0f, 
		0.0f, 0.748016f, 0.748016f, 1.0f, 
		0.0f, 0.0f, 0.0f, 1.0f, 
		0.981818f, 0.981818f, 0.981818f, 1.0f, 
		92.315140f
};

static Material edge_mat[] = {
	0.038095f, 0.036285f, 0.036285f, 1.0f, 
		0.152381f, 0.145141f, 0.145141f, 1.0f, 
		0.0f, 0.0f, 0.0f, 1.0f, 
		0.745455f, 0.745455f, 0.745455f, 1.0f, 
		122.569725f
};

void drawppd_vertex( Sppd *ppd, ScreenAtr *screen )
{
	Spvt *v;
	Vec  *vec;
	
	if ( ppd == NULL ) return;
	
	glPointSize(4.0);
	
	for ( v = ppd->spvt; v != (Spvt *) NULL; v = v->nxt ) {
		glColor3dv( greenvec );
		if ( v->col == PNTRED ) glColor3dv( redvec );
		// temporary
		if ( v->isConst != SMD_ON ) {
			glBegin(GL_POINTS);
			vec = &(v->vec);
			glVertex3d( (GLdouble) vec->x, (GLdouble) vec->y, (GLdouble) vec->z );
			glEnd();
		}
		
	}

	glEnable(GL_LIGHTING);
	material_binding( pointred_mat );
	for ( v = ppd->spvt; v != (Spvt *) NULL; v = v->nxt ) {
		if ( v->isConst == SMD_ON ) glu_sphere( &(v->vec), screen->rad_sph );
	}
	glDisable(GL_LIGHTING);
}

void drawppd_vertex_enhanced( Sppd *ppd, ScreenAtr *screen )
{
	Spvt *v;
	
	if ( ppd == NULL ) return;
	
	glEnable(GL_LIGHTING);
	
	for ( v = ppd->spvt; v != (Spvt *) NULL; v = v->nxt ) {
		
		if ( v->type == VERTEX_ORIGINAL ) {
			
			switch ( v->sp_type ) {
			case SP_VERTEX_HVERTEX:
				material_binding( tropical20 );
				break;
			default:
				material_binding( point_mat );
				break;
			}
			if ( v->col == PNTRED ) material_binding( pointred_mat );
			
			glu_sphere( &(v->vec), screen->rad_sph );
			
		}
		
	}
	
	glDisable(GL_LIGHTING);
}

void drawppd_edge( Sppd *ppd, ScreenAtr *screen )
{
	Sped *e;
	Vec  *svec, *evec;
	
	if ( ppd == NULL ) return;
	
	glLineWidth((GLfloat) 1.0);
	
	/* edge */
	for (e = ppd->sped; e != (Sped *) NULL; e = e->nxt) {
		
		if ( e->type == EDGE_ORIGINAL ) {
			
			glColor3dv( gray40vec );
			if ( e->fn == 1 ) {
				if ( e->used_loop == SMD_OFF ) {
					glColor3dv( bluevec );
				}
			}
			if ( e->fn > 2 ) {
				glColor3dv( redvec );
			}
			
			svec = &(e->sv->vec);
			evec = &(e->ev->vec);
			glBegin(GL_LINE_STRIP);
			glVertex3d( (GLdouble) svec->x, (GLdouble) svec->y, (GLdouble) svec->z );
			glVertex3d( (GLdouble) evec->x, (GLdouble) evec->y, (GLdouble) evec->z );
			glEnd();
		}
		
	}
}

void drawppd_hiddenline( Sppd *ppd, ScreenAtr *screen )
{
	Spfc  *f;
	Sphe  *he;
	Vec   *vec, *nrm;
	
	glLineWidth( (GLfloat) 1.0 );
	glColor3dv( gray40vec );
//	glColor3dv( blackvec );
	
	glEnable(GL_STENCIL_TEST);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 0, 1);
	glStencilOp(GL_INVERT, GL_INVERT, GL_INVERT);
	
	for ( f = ppd->spfc; f != NULL; f = f->nxt ) {
		
		he = f->sphe;
		glBegin(GL_LINE_LOOP);
		do {
			vec = &(he->vt->vec);
			glVertex3d((GLdouble) vec->x, (GLdouble) vec->y, (GLdouble) vec->z);
		} while ((he = he->nxt) != f->sphe);
		glEnd();
		
		/*** polygon shading (by material or background color) ***/
		if (swin->dis3d.shading) { 
			
			material_binding(swin->material);
			glEnable(GL_LIGHTING);
			glStencilFunc(GL_EQUAL, 0, 1);
			glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
			
			glBegin( GL_POLYGON );
			he = f->sphe;
			nrm = &(f->nrm);
			do {
				glNormal3d((GLdouble) nrm->x, (GLdouble) nrm->y, (GLdouble) nrm->z);
				vec = &(he->vt->vec);
				glVertex3d((GLdouble) vec->x, (GLdouble) vec->y, (GLdouble) vec->z);
			} while ((he = he->nxt) != f->sphe);
			glEnd();
			
			glDisable(GL_LIGHTING);
			
			/*     } else { */
			/*       glColor3f( screen->bgrgb[0], screen->bgrgb[1], screen->bgrgb[2] ); */
			
			/*       glShadeModel(GL_FLAT); */
			/*       glStencilFunc(GL_EQUAL, 0, 1); */
			/*       glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); */
			/*       glBegin(GL_POLYGON); */
			/*       do { */
			/* 	vec = &(he->vt->vec); */
			/* 	glVertex3d((GLdouble) vec->x, (GLdouble) vec->y, (GLdouble) vec->z); */
			/*       } while ((he = he->nxt) != f->sphe); */
			/*       glEnd(); */
			/*     } */
			
			/*** edge drawing (2nd stencil) ***/      
			glStencilFunc(GL_ALWAYS, 0, 1);
			glStencilOp(GL_INVERT, GL_INVERT, GL_INVERT);
			
			he = f->sphe;
			glBegin(GL_LINE_LOOP);
			do {
				vec = &(he->vt->vec);
				glVertex3d((GLdouble) vec->x, (GLdouble) vec->y, (GLdouble) vec->z);
			} while ((he = he->nxt) != f->sphe);
			glEnd();
			
		}
	}
}
	
	
void drawppd_sged( SGraph *sg, ScreenAtr *screen, GLdouble *color, GLfloat width )
{
	SGed *e;
	Vec  *svec, *evec;
	
	if ( sg == NULL ) return;
	
	/*   glPointSize(7.0); */
	/*   for ( v = sg->sgvt; v != (SGvt *) NULL; v = v->nxt ) { */
	/*     svec = &(v->vec); */
	
	/*     glBegin( GL_POINTS ); */
	/*     glColor3dv( lightbluevec ); */
	/*     glVertex3d( (GLdouble) svec->x, (GLdouble) svec->y, (GLdouble) svec->z ); */
	/*     glEnd(); */
	
	/*     glColor3dv( redvec ); */
	/*     glRasterPos3d( (GLdouble) svec->x, (GLdouble) svec->y, (GLdouble) svec->z ); */
	/*     sprintf(buf, "%d", v->no ); */
	/*     (void) printstring( screen, buf ); */
	
	/*   } */
	
	glLineWidth((GLfloat) width );
	
	/* edge */
	for ( e = sg->sged; e != (SGed *) NULL; e = e->nxt ) {
		
		glColor3dv( color );
		svec = &(e->sv->vec);
		evec = &(e->ev->vec);
		glBegin( GL_LINE_STRIP );
		glVertex3d( (GLdouble) svec->x, (GLdouble) svec->y, (GLdouble) svec->z );
		glVertex3d( (GLdouble) evec->x, (GLdouble) evec->y, (GLdouble) evec->z );
		glEnd();
		
		/*     glColor3dv( redvec ); */
		/*     glRasterPos3d( (GLdouble) (svec->x+evec->x) /2.0, */
		/* 		   (GLdouble) (svec->y+evec->y) /2.0, */
		/* 		   (GLdouble) (svec->z+evec->z) /2.0 ); */
		/*     sprintf(buf, "%d", e->no ); */
		/*     (void) printstring( screen, buf ); */
		
	}
}

void drawppd_edge_enhanced(Sppd *ppd, ScreenAtr *screen)
{
	Sped *e;
	
	if ( ppd == NULL ) return;
	
	glEnable(GL_LIGHTING);
	material_binding( edge_mat );
	
	/* edge */
	
	for (e = ppd->sped; e != (Sped *) NULL; e = e->nxt) {
		
		if ( e->type == EDGE_ORIGINAL ) {
			glu_cylinder( &(e->sv->vec), &(e->ev->vec) , screen->rad_cyl );
		}
		
	}
	
	glDisable(GL_LIGHTING);
	
}

void drawppd_shading( Sppd *ppd, ScreenAtr *screen )
{
	Spfc  *f;
	Sphe  *he;
	Vec   *vec;
	
	if ( ppd == NULL ) return;
	
	material_binding( swin->material );
	
	for (f = ppd->spfc; f != (Spfc *) NULL;f = f->nxt) {
		
		if (f->col == FACEBLUE) {
			
			glEnable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			he = f->sphe;
			do {
				if ( (he->nm != (Spnm *) NULL) && (swin->dis3d.smooth == SMD_ON) ) {
					vec = &(he->nm->vec);
					glNormal3d((GLdouble) vec->x, (GLdouble) vec->y, (GLdouble) vec->z );
				} else {
					glNormal3d((GLdouble) f->nrm.x, (GLdouble) f->nrm.y, (GLdouble) f->nrm.z);
				}
				
				vec = &(he->vt->vec);
				glVertex3d( (GLdouble) vec->x, (GLdouble) vec->y, (GLdouble) vec->z );
				
			} while ((he = he->nxt) != f->sphe);
			glEnd();
			glDisable(GL_LIGHTING);
			
		} else if (f->col == FACERED) {
			
			glColor3dv( redvec );
			glBegin(GL_POLYGON);
			he = f->sphe;
			do {
				vec = &(he->vt->vec);
				glVertex3d( (GLdouble) vec->x, (GLdouble) vec->y, (GLdouble) vec->z );
			} while ((he = he->nxt) != f->sphe);
			glEnd();
			
		} else if (f->col == FACEGREEN) {
			
			glColor3dv(greenvec);
			glBegin(GL_POLYGON);
			he = f->sphe;
			do {
				vec = &(he->vt->vec);
				glVertex3d( (GLdouble) vec->x, (GLdouble) vec->y, (GLdouble) vec->z );
			} while ((he = he->nxt) != f->sphe);
			glEnd();
			
		}
	}
}

void drawhppd_cmesh(HPpd *hppd, ScreenAtr *screen)
{
	HEdge     *hed;
	HVertex   *hvt, *shvt, *ehvt;
	HFace     *hfc;
	HHalfedge *he;
	Vec  *nrm;
	Spvt      *vt, *sv, *ev;
	
	glPointSize(4.0);
	glLineWidth((GLfloat) 2.0);
	
	/* hvertices */
	glBegin( GL_POINTS );
	for ( hvt = hppd->shvt; hvt != (HVertex *) NULL; hvt = hvt->nxt ) {
		
		vt = ( !screen->no ) ? hvt->vt1 : hvt->vt2;
		
		if ( hvt->atr == VTXINTERNAL ) glColor3dv( darkorange4vec );
		else glColor3dv( magenta4vec );
		
		if ( hvt->col != PNTGREEN ) glColor3dv( redvec );
		
		glVertex3d((GLdouble) vt->vec.x, (GLdouble) vt->vec.y, (GLdouble) vt->vec.z);
		
	}
	glEnd();
	
	/* hedges */
	
	for ( hed = hppd->shed; hed != (HEdge *) NULL; hed = hed->nxt ) {
		
		shvt = hed->sv;
		ehvt = hed->ev;
		sv = ( !screen->no ) ? shvt->vt1 : shvt->vt2;
		ev = ( !screen->no ) ? ehvt->vt1 : ehvt->vt2;
		
		if ( hed->atr == EDGEINTERNAL ) glColor3dv( darkorange4vec );
		else glColor3dv( magenta4vec );
		
		glBegin(GL_LINE_STRIP);
		glVertex3d((GLdouble) sv->vec.x, (GLdouble) sv->vec.y, (GLdouble) sv->vec.z);
		glVertex3d((GLdouble) ev->vec.x, (GLdouble) ev->vec.y, (GLdouble) ev->vec.z);
		glEnd();
		
	}
	
	/* faces */
	for ( hfc = hppd->shfc; hfc != (HFace *) NULL; hfc = hfc->nxt ) {
		
		if ( hfc->col != FACERED ) {
			
			glEnable( GL_LIGHTING );
			material_binding( swin->material );
			
			glBegin(GL_POLYGON);
			he = hfc->shhe;
			nrm = ( !screen->no ) ? &(hfc->nrm1) : &(hfc->nrm2);
			do {
				shvt = he->vt;
				sv = ( !screen->no ) ? shvt->vt1 : shvt->vt2;
				glNormal3d((GLdouble) nrm->x, (GLdouble) nrm->y, (GLdouble) nrm->z);
				glVertex3d((GLdouble) sv->vec.x, (GLdouble) sv->vec.y, (GLdouble) sv->vec.z);
				
			} while ((he = he->nxt) != hfc->shhe);
			glEnd();
			
			glDisable( GL_LIGHTING );
			
		} else {
			
			glColor3dv( redvec );
			glBegin( GL_POLYGON );
			he = hfc->shhe;
			do {
				shvt = he->vt;
				sv = ( !screen->no ) ? shvt->vt1 : shvt->vt2;
				glVertex3d( (GLdouble) sv->vec.x, (GLdouble) sv->vec.y, (GLdouble) sv->vec.z );
				
			} while ((he = he->nxt) != hfc->shhe);
			
			glEnd();
			
			
		}      
		
	}
	
}

void drawhppd_cmesh_enhanced(HPpd *hppd, ScreenAtr *screen)
{
	HEdge     *hed;
	HVertex   *hvt, *shvt, *ehvt;
	Spvt      *vt, *sv, *ev;
	HFace     *hfc;
	HHalfedge *he;
	Vec   *nrm;
	
	/* hvertices */
	glEnable(GL_LIGHTING);
	
	for ( hvt = hppd->shvt; hvt != (HVertex *) NULL; hvt = hvt->nxt ) {
		
		if ( screen->no == SCREEN_SRC ) vt = hvt->vt1;
		else                         vt = hvt->vt2;
		
		if ( hvt->col == PNTGREEN ) material_binding( point_mat );
		else material_binding( pointred_mat );
		
		glu_sphere( &(vt->vec), screen->rad_sph );
	}
	
	/* hedges */
	
	glLineWidth((GLfloat) 2.0);
	for ( hed = hppd->shed; hed != (HEdge *) NULL; hed = hed->nxt ) {
		
		shvt = hed->sv;
		ehvt = hed->ev;
		if ( screen->no == SCREEN_SRC ) {
			sv = shvt->vt1;
			ev = ehvt->vt1;
		} else {
			sv = shvt->vt2;
			ev = ehvt->vt2;
		}
		
		material_binding( line_mat );
		
		glu_cylinder( &(sv->vec), &(ev->vec) , screen->rad_cyl );
		
	}
	
	/* faces */
	material_binding( swin->material );
	
	for ( hfc = hppd->shfc; hfc != (HFace *) NULL; hfc = hfc->nxt ) {
		
		glBegin( GL_POLYGON );
		
		nrm = ( !screen->no ) ? &(hfc->nrm1) : &(hfc->nrm2);
		he = hfc->shhe;
		do {
			shvt = he->vt;
			sv = ( !screen->no ) ? shvt->vt1 : shvt->vt2;
			glNormal3d((GLdouble) nrm->x, (GLdouble) nrm->y, (GLdouble) nrm->z);
			glVertex3d((GLdouble) sv->vec.x, (GLdouble) sv->vec.y, (GLdouble) sv->vec.z);
			
		} while ((he = he->nxt) != hfc->shhe);
		
		glEnd();
	}
	
	glDisable( GL_LIGHTING );
}

void drawhppd_cpoint_enhanced(HPpd *hppd, ScreenAtr *screen)
{
	HVertex   *hvt;
	Spvt      *vt;
	
	/* hvertices */
	glEnable(GL_LIGHTING);
	
	for ( hvt = hppd->shvt; hvt != (HVertex *) NULL; hvt = hvt->nxt ) {
		
		if ( screen->no == SCREEN_SRC ) vt = hvt->vt1;
		else                         vt = hvt->vt2;
		
		if ( hvt->col == PNTGREEN ) material_binding( point_mat );
		else material_binding( pointred_mat );
		
		glu_sphere( &(vt->vec), screen->rad_sph );
	}
	
	glDisable( GL_LIGHTING );
}

/* grouping */
void drawhppd_group(HPpd *hppd, ScreenAtr *screen, int tileno)
{
	HFace *hfc;
	HGfc  *hgfc;
	HGsf  *sf;
	Spvt  *sv, *ev;
	HGhe  *hghe;
	
	if ( hppd == (HPpd *) NULL ) return;
	if ( hppd->shfc == (HFace *) NULL ) return;
	
	glPointSize(4.0);
	glLineWidth((GLfloat) 3.0);
	glColor3dv( blackvec );
	
	for ( hfc = hppd->shfc; hfc != (HFace *) NULL; hfc = hfc->nxt ) {
		
		if (hfc->no != tileno) continue;
		
		if ( !screen->no ) hgfc = hfc->hgfc1; else hgfc = hfc->hgfc2;
		if ( hgfc == (HGfc *) NULL ) continue;
		
		for ( sf = hgfc->shgsf; sf != (HGsf *) NULL; sf = sf->nxt ) {
			
			hghe = sf->shghe;
			
			do {
				sv = hghe->vt->vt;
				ev = hghe->nxt->vt->vt;
				glBegin(GL_LINE_STRIP);
				glVertex3d((GLdouble) sv->vec.x, (GLdouble) sv->vec.y, (GLdouble) sv->vec.z);
				glVertex3d((GLdouble) ev->vec.x, (GLdouble) ev->vec.y, (GLdouble) ev->vec.z);
				glEnd();
			} while ( (hghe = hghe->nxt) != sf->shghe );
			
		}
		
	}
	
}

void drawhppd_group_enhanced(HPpd *hppd, ScreenAtr *screen)
{
	HFace *hfc;
	HGfc  *hgfc;
	HGvt  *hv;
	HGed  *he;
	
	if ( hppd == (HPpd *) NULL ) return;
	if ( hppd->shfc == (HFace *) NULL ) return;
	
	glEnable(GL_LIGHTING);
	
	for ( hfc = hppd->shfc; hfc != (HFace *) NULL; hfc = hfc->nxt ) {
		
		switch ( hfc->no %  NUM_GROUP_EDGE ) {
		case 0:
			material_binding( tropical0 );
			break;
		case 1:
			material_binding( tropical13 );
			break;
		case 2:
			material_binding( tropical6 );
			break;
		case 3:
			material_binding( tropical24 );
			break;
		case 4:
			material_binding( tropical29 );
			break;
		}
		
		if ( !screen->no ) hgfc = hfc->hgfc1; else hgfc = hfc->hgfc2;
		
		if ( hgfc != (HGfc *) NULL ) {
			
			/* vertices */
			for ( hv = hgfc->shgvt; hv != (HGvt *) NULL; hv = hv->nxt ) {
				glu_sphere( &(hv->vt->vec), screen->rad_sph );
			}
			
			/* edges */
			for ( he = hgfc->shged; he != (HGed *) NULL; he = he->nxt ) {
				glu_cylinder( &(he->ed->sv->vec), &(he->ed->ev->vec) , screen->rad_cyl );
			}
			
		}
	}
	
	glDisable(GL_LIGHTING);
}

/* hloop */
void drawhppd_hloop(HPpd *hppd, ScreenAtr *screen)
{
	HFace *hfc;
	Splp    *lp;
	Splv    *lv;
	
	glPointSize(4.0);
	glLineWidth((GLfloat) 2.0);
	
	for ( hfc = hppd->shfc; hfc != (HFace *) NULL; hfc = hfc->nxt ) {
		
		if ( hfc->hloop != (HLoop *) NULL ) {
			
			if ( !screen->no ) lp = hfc->hloop->lp1; else lp = hfc->hloop->lp2;
			
			glColor3dv( redvec );
			
			glBegin(GL_LINE_LOOP);
			for (lv = lp->splv; lv != (Splv *) NULL; lv = lv->nxt) {
				glVertex3d((GLdouble) lv->vt->vec.x,
					(GLdouble) lv->vt->vec.y,
					(GLdouble) lv->vt->vec.z);
			}
			glEnd();
			
			for (lv = lp->splv; lv != (Splv *) NULL; lv = lv->nxt) {
				
				if ( lv->vt->col != PNTRED ) glColor3dv( orangevec );
				else glColor3dv( redvec );
				
				glBegin(GL_POINTS);
				glVertex3d((GLdouble) lv->vt->vec.x,
					(GLdouble) lv->vt->vec.y,
					(GLdouble) lv->vt->vec.z);
				glEnd();
			}
		}
	}
}

void drawhppd_shortestpath(HPpd *hppd, ScreenAtr *screen)
{
	HEdge   *hed;
	Splp    *lp;
	Splv    *lv;
	
	glLineWidth((GLfloat) 4.0);
	
	for ( hed = hppd->shed; hed != (HEdge *) NULL; hed = hed->nxt ) {
		
		if ( screen->no == SCREEN_SRC ) lp = hed->lp1;
		else lp = hed->lp2;
		
		if ( lp != (Splp *) NULL ) {

// for GI fig			
			glColor3dv( redvec );
//			if ( lp->col != LOOPRED ) glColor3dv( indianred4vec );
//			else glColor3dv( redvec );
			
			glBegin(GL_LINE_STRIP);
			for (lv = lp->splv; lv != (Splv *) NULL; lv = lv->nxt) {
				glVertex3d( (GLdouble) lv->vt->vec.x,
					(GLdouble) lv->vt->vec.y,
					(GLdouble) lv->vt->vec.z );
			}
			glEnd();

/*			
			glPointSize( 7.0 );
			glBegin( GL_POINTS );
			for (lv = lp->splv; lv != (Splv *) NULL; lv = lv->nxt) {
				
				vt = lv->vt;
				
				if ( vt->sp_type == SP_VERTEX_HVERTEX ) continue;
				
				glColor3dv( orangevec );
				glVertex3d((GLdouble) lv->vt->vec.x, (GLdouble) lv->vt->vec.y,
					(GLdouble) lv->vt->vec.z);
			}
			glEnd();
*/
		}
		
	}
	
}

void drawppd_loop( Sppd *ppd, ScreenAtr *screen )
{
	Splp *lp;
	
	for ( lp = ppd->splp; lp != (Splp *) NULL; lp = lp->nxt ) {
		
		draw_loop( lp );
		
	}
}

void draw_loop( Splp *lp )
{
	Splv *lv;
	Spvt *vt;
	Vec  *vec;
	
	if ( lp == NULL ) return;
	/* loops */
	
	glLineWidth((GLfloat) 2.0);
	
	switch ( lp->type ) {
	case SHORTESTPATH:
		glColor3dv( red3vec );
		break;
	default:
		glColor3dv( bluevec );
	}

	// selected
	if ( lp->col == LOOPRED ) glColor3dv( redvec );
	
	switch ( lp->type ) {
	case CLOSEDLOOP:
		glBegin( GL_LINE_LOOP );
		break;
	default:
		glBegin( GL_LINE_STRIP );
		break;
	}
	
	for ( lv = lp->splv; lv != (Splv *) NULL; lv = lv->nxt ) {
		vec = &(lv->vt->vec);
		glVertex3d( (GLdouble) vec->x, (GLdouble) vec->y, (GLdouble) vec->z );
	}
	glEnd();
	
	glPointSize(7.0);
	
	for ( lv = lp->splv; lv != (Splv *) NULL; lv = lv->nxt ) {
		
		vt = lv->vt;
		
		if ( vt->col != PNTRED ) glColor3dv( orangevec );
		else glColor3dv( redvec );
		
		if ( (vt->sp_type != SP_VERTEX_HVERTEX) && (vt->spn > 1 ) ) {
			glColor3dv( bluevec );
		}
		
		glBegin(GL_POINTS);
		glVertex3d( (GLdouble) vt->vec.x, (GLdouble) vt->vec.y, (GLdouble) vt->vec.z );
		glEnd();
	}
	
}

void draw_sglp( SGlp *lp )
{
	SGlpvt *lv;
	Vec  *vec;
	
	if ( lp == NULL ) return;
	/* loops */
	
	glLineWidth( (GLfloat) 4.0 );
	glColor3dv( bluevec );
	
	glBegin( GL_LINE_STRIP );
	for ( lv = lp->slpvt; lv != (SGlpvt *) NULL; lv = lv->nxt ) {
		vec = &( lv->vt->vec );
		glVertex3d( (GLdouble) vec->x, (GLdouble) vec->y, (GLdouble) vec->z );
	}
	glEnd();
	
	glPointSize( 8.0 );
	glColor3dv( orangevec );
	
	glBegin( GL_POINTS );
	for ( lv = lp->slpvt; lv != (SGlpvt *) NULL; lv = lv->nxt ) {
		vec = &( lv->vt->vec );
		glVertex3d( (GLdouble) vec->x, (GLdouble) vec->y, (GLdouble) vec->z );
	}
	glEnd();
}

void drawppd_loop_enhanced( Sppd *ppd, ScreenAtr *screen )
{
	Splp *lp;
	
	for ( lp = ppd->splp; lp != (Splp *) NULL; lp = lp->nxt ) {
		
		draw_loop_enhanced( lp, screen );
		
	}
}

void draw_loop_enhanced( Splp *lp, ScreenAtr *screen )
{
	Splv *lv;
	Spvt *vt;
	
	if ( lp == NULL ) return;
	/* loops */
	
	glLineWidth((GLfloat) 2.0);
	
	
	switch ( lp->type ) {
	case SHORTESTPATH:
		glColor3dv( red3vec );
		break;
	default:
		glColor3dv( bluevec );
	}
	
	switch ( lp->type ) {
	case CLOSEDLOOP:
		glBegin( GL_LINE_LOOP );
		break;
	default:
		glBegin( GL_LINE_STRIP );
		break;
	}
	
	for (lv = lp->splv; lv != (Splv *) NULL; lv = lv->nxt) {
		glVertex3d( (GLdouble) lv->vt->vec.x,
			(GLdouble) lv->vt->vec.y,
			(GLdouble) lv->vt->vec.z );
	}
	glEnd();
	
	glEnable( GL_LIGHTING );
	for ( lv = lp->splv; lv != (Splv *) NULL; lv = lv->nxt ) {
		vt = lv->vt;
		switch ( vt->sp_type ) {
		case SP_VERTEX_HVERTEX:
			if ( vt->col != PNTRED ) material_binding( point_mat );
			else material_binding( pointred_mat );
			glu_sphere( &(vt->vec), screen->rad_sph );
			break;
		default:
			if ( vt->col != PNTRED ) material_binding( vertex_mat );
			else material_binding( pointred_mat );
			glu_sphere( &(vt->vec), screen->rad_sph );
			break;
		}
	}
	glDisable( GL_LIGHTING );
}

void drawhppd_hmap( HPpd *hppd, ScreenAtr *screen )
{
	HGfc  *hgfc;
	HFace *hf;
	HGed  *he;
	HGvt  *hv;
	HGsf  *hs;
	HGhe  *hghe;
	Vec   *vec;
	
	glLineWidth((GLfloat) 2.0);
	glPointSize(4.0);
	glColor3dv( blackvec );
	
	if ( hppd == NULL ) return;
	
	for ( hf = hppd->shfc; hf != (HFace *) NULL; hf = hf->nxt ) {
		
		hgfc = ( !screen->no ) ? hf->hgfc1->mhgfc : hf->hgfc2->mhgfc;
		
		/* edge */
		for ( he = hgfc->shged; he != (HGed *) NULL; he = he->nxt ) {
			
			if ( (he->rf == NULL) || ( he->rf == NULL) ) {
				glColor3dv( redvec );
			} else {
				glColor3dv( blackvec );
			}
			
			glBegin(GL_LINE_STRIP);
			vec = &(he->sv->vec);
			glVertex3d((GLdouble) vec->x, (GLdouble) vec->y,
				(GLdouble) vec->z);
			vec = &(he->ev->vec);
			glVertex3d((GLdouble) vec->x, (GLdouble) vec->y,
				(GLdouble) vec->z);
			glEnd();
		}
		
		/* vertex */
		glBegin( GL_POINTS );
		glColor3dv( blackvec );
		for ( hv = hgfc->shgvt; hv != (HGvt *) NULL; hv = hv->nxt ) {
			glVertex3d( (GLdouble) hv->vec.x,
				(GLdouble) hv->vec.y,
				(GLdouble) hv->vec.z );
		}
		glEnd();
		
		/* surface */
		glEnable( GL_LIGHTING );
		material_binding( tropical10 );
		
		for ( hs = hgfc->shgsf; hs != (HGsf *) NULL; hs = hs->nxt ) {
			
			glBegin( GL_POLYGON );
			
			hghe = hs->shghe;
			
			do { 
				
				glNormal3d( (GLdouble) hs->nrm.x,
					(GLdouble) hs->nrm.y,
					(GLdouble) hs->nrm.z );
				
				vec = &(hghe->vt->vec);
				glVertex3d( (GLdouble) vec->x,
					(GLdouble) vec->y,
					(GLdouble) vec->z );
				
			} while ( ( hghe = hghe->nxt ) != hs->shghe );
			
			glEnd();
			
		}
		
		glDisable(GL_LIGHTING);
		
	}
}

// draw primitives 
void glu_sphere( Vec *pos, double radius )
{
	GLUquadricObj   *qobj;
	GLint           slices = 20,staks = 10;
	
	if ((qobj = gluNewQuadric()) != NULL) {
		glPushMatrix();
		glTranslated( (GLdouble) pos->x, (GLdouble) pos->y, (GLdouble) pos->z );
		gluSphere(qobj, (GLdouble) radius, slices, staks);
		glPopMatrix();
		gluDeleteQuadric(qobj);
	}
}

void glu_cylinder( Vec *sv, Vec *ev, double rad )
{
	GLUquadricObj   *cyl;
	GLint           slices = 20,staks = 10;
	Vec sub;
	double height;
	double rx, ry;
	double V3Length( Vec * );
	
	if ((cyl = gluNewQuadric()) != NULL) {
		glPushMatrix();
		sub.x  = ev->x - sv->x;
		sub.y  = ev->y - sv->y;
		sub.z  = ev->z - sv->z;
		height = V3Length( &sub );
		sub.x /= height; sub.y /= height; sub.z /= height;
		
		ry = asin( sub.x );
		rx = acos( sub.z / cos(ry) );
		
		if ( fabs ( sub.y + sin(rx) * cos(ry) > SMDZEROEPS) ) {
			rx = 2 * SMDPI - rx;
		}
		
		glTranslated ( sv->x, sv->y, sv->z );
		glRotated( rx * 180.0 / SMDPI, 1.0, 0.0, 0.0 );
		glRotated( ry * 180.0 / SMDPI, 0.0, 1.0, 0.0 );
		gluCylinder(cyl, rad, rad, height, slices, staks);
		glPopMatrix();
		gluDeleteQuadric(cyl);
	}
}
