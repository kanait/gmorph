/* Copyright (c) 1997-1998 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>
#include "smd.h"
#include "ppd.h"
#include "ppdsolid.h"
#include "ppdpart.h"
#include "ppdvertex.h"
#include "ppdface.h"
#include "hgppd.h"
#include "quadtree.h"
#include "veclib.h"

//******************************************************************
//                       HGppd functions 
//******************************************************************

/* hgppd */
HGppd *create_hgppd(void)
{
	HGppd *hgppd;
	
	if ((hgppd = (HGppd *) malloc(sizeof(HGppd))) == (HGppd *) NULL) {
		return (HGppd *) NULL;
	}
	
	/* faces */
	hgppd->nhgfc = 0;
	hgppd->shgfc = hgppd->ehgfc = (HGfc *) NULL;
    
	return hgppd;
}

void free_hgppd( HGppd *ppd )
{
	if ( ppd == (HGppd *) NULL ) return;
	
	FreeHGppdFace( ppd );
	free( ppd );
}

/* face */
HGfc *create_hgppdface( HGppd *ppd )
{
	HGfc *fc;
	
	fc = (HGfc *) malloc(sizeof(HGfc));
	
	fc->nxt = (HGfc *) NULL;
	
	if (ppd->shgfc == (HGfc *) NULL) {
		fc->prv = (HGfc *) NULL;
		ppd->ehgfc = ppd->shgfc = fc;
	} else {
		fc->prv   = ppd->ehgfc;
		ppd->ehgfc = ppd->ehgfc->nxt = fc;
	}
	
	/* vertex */
	fc->hgvn  = 0;
	fc->shgvt = fc->ehgvt = (HGvt *) NULL;
	
	/* edges */
	fc->hgen  = 0;
	fc->shged = fc->ehged = (HGed *) NULL;
	
	/* loops */
	fc->hgln  = 0;
	fc->shglp = fc->ehglp = (HGlp *) NULL;
	
	/* control vertices */
	fc->hgcn  = 0;
	fc->shgcv = fc->ehgcv = (HGcv *) NULL;
	
	/* surfaces */
	fc->hgsn  = 0;
	fc->shgsf = fc->ehgsf = (HGsf *) NULL;
	
	/*   fc->cvn = 0; */
	
	/*   fc->cvt[0] = fc->cvt[1] = fc->cvt[2] = (Spvt *) NULL; */
	
	fc->hf = (HFace *) NULL;
	
	fc->mhgfc = (HGfc *) NULL;
	
	/* for Quadtree */
	fc->qn    = 0;
	fc->qt    = (QTree *) NULL;
	fc->maxqtlevel = 0;
	
	++( ppd->nhgfc );
	
	return fc;
}

HGfc *create_hgfc( void )
{
	HGfc *fc;
	
	fc = (HGfc *) malloc( sizeof(HGfc) );
	
	/* vertex */
	fc->hgvn  = 0;
	fc->shgvt = fc->ehgvt = (HGvt *) NULL;
	
	/* edges */
	fc->hgen  = 0;
	fc->shged = fc->ehged = (HGed *) NULL;
	
	/* surfaces */
	fc->hgsn  = 0;
	fc->shgsf = fc->ehgsf = (HGsf *) NULL;
	
	/*   fc->cvt[0] = fc->cvt[1] = fc->cvt[2] = (Spvt *) NULL; */
	
	/* for Quadtree */
	fc->qn    = 0;
	fc->qt    = (QTree *) NULL;
	fc->maxqtlevel = 0;
	
	return fc;
}

HGfc *find_hgfc( HGppd *hgppd, int id )
{
	HGfc *hgfc;
	
	for ( hgfc = hgppd->shgfc; hgfc != (HGfc *) NULL; hgfc = hgfc->nxt ) {
		if ( hgfc->id == id ) return hgfc;
	}
	return NULL;
}

void free_hgfc( HGfc *fc )
{
	if (fc == (HGfc *) NULL) return;
	
	/* for QTree */
	free_hgppdqtree( fc );
	
	/* free vertices, edges, loops */
	FreeHGppdVertex( fc );
	FreeHGppdEdge( fc );
	FreeHGppdSurface( fc );
	
	free(fc);
	
}

void free_hgppdface( HGfc *fc, HGppd *ppd )
{
	if (fc == (HGfc *) NULL) return;
	
	/* for QTree */
	free_hgppdqtree( fc );
	
	/* free vertices, edges, loops */
	FreeHGppdVertex( fc );
	FreeHGppdEdge( fc );
	FreeHGppdSurface( fc );
	FreeHGppdLoop( fc );
	FreeHGppdCtrlvertex( fc );
	
	if (ppd->shgfc == fc) {
		if ((ppd->shgfc = fc->nxt) != (HGfc *) NULL)
			fc->nxt->prv = (HGfc *) NULL;
		else {
			ppd->ehgfc = (HGfc *) NULL;
		}
	} else if (ppd->ehgfc == fc) {
		fc->prv->nxt = (HGfc *) NULL;
		ppd->ehgfc = fc->prv;
		
	} else {
		fc->prv->nxt = fc->nxt;
		fc->nxt->prv = fc->prv;
	}
	
	free(fc);
	--( ppd->nhgfc );
}

/* vertex */
HGvt *create_hgppdvertex( HGfc *fc )
{
	HGvt *vt;
	
	vt = (HGvt *) malloc(sizeof(HGvt));
	
	vt->nxt = (HGvt *) NULL;
	if (fc->shgvt == (HGvt *) NULL) {
		vt->prv   = (HGvt *) NULL;
		fc->ehgvt = fc->shgvt = vt;
	} else {
		vt->prv   = fc->ehgvt;
		fc->ehgvt = fc->ehgvt->nxt = vt;
	}
	
	vt->vt = (Spvt *) NULL;
	
	/* for harmonic map */
	vt->sid  = SMDNULL;
	vt->vval = 0.0;
	
	/* links to HGvtvt */
	vt->hgvvn = 0;
	vt->shgvv = (HGvtvt *) NULL;
	vt->ehgvv = (HGvtvt *) NULL;
	
	/* links to HGvted */
	vt->hgven = 0;
	vt->shgve = (HGvted *) NULL;
	vt->ehgve = (HGvted *) NULL;
	
	vt->vec.x = 0.0;
	vt->vec.y = 0.0;
	vt->vec.z = 0.0;
	
	/* used in "isHGvtLeftSide" */
	vt->sign  = SMDNULL;
	
	vt->no      = fc->hgvn;
	vt->sp_type = SP_VERTEX_NORMAL;
	
	/* for merging used in "hedge_to_gppd" */
	vt->from    = SMDNULL;
	
	/* Boundary Inclusion Information  used only if vt->sp_type is SP_VERTEX_BOUNDARY  */
	/* use in "edge_edge_intersection" */
	vt->inc_ed  = (HGed *) NULL;
	
	/* Normal Inclusion Information ( used only if vt->sp_type is SP_VERTEX_NORMAL ) */
	/* use in "edge_edge_intersection" */
	vt->inc_sf  = (HGsf *) NULL;
	
	/* used in hgfc1, hgfc2 */
	vt->mhgvt = (HGvt *) NULL;
	
	++( fc->hgvn );
	
	return vt;
}

void free_hgppdvertex( HGvt *vt, HGfc *fc )
{
	if (vt == (HGvt *) NULL) return;
	
	free_hgppdvertexvertex( vt );
	free_hgppdvertexedge( vt );
	
	vt->vt = (Spvt *) NULL;
	
	if ( fc->shgvt == vt ) {
		if ((fc->shgvt = vt->nxt) != (HGvt *) NULL)
			vt->nxt->prv = (HGvt *) NULL;
		else {
			fc->ehgvt = (HGvt *) NULL;
		}
	} else if (fc->ehgvt == vt) {
		vt->prv->nxt = (HGvt *) NULL;
		fc->ehgvt = vt->prv;
	} else {
		vt->prv->nxt = vt->nxt;
		vt->nxt->prv = vt->prv;
	}
	
	free(vt);
	--( fc->hgvn );
}

/* HG vertex -> edge */
HGvted *create_hgvted(HGvt *hgvt, HGed *ed)
{
	HGvted *ve;
	
	if (ed == (HGed *) NULL) return (HGvted *) NULL;
	
	ve = (HGvted *) malloc(sizeof(HGvted));
	
	ve->nxt = (HGvted *) NULL;
	if (hgvt->shgve == (HGvted *) NULL) {
		ve->prv       = (HGvted *) NULL;
		hgvt->ehgve = hgvt->shgve = ve;
	} else {
		ve->prv       = hgvt->ehgve;
		hgvt->ehgve = hgvt->ehgve->nxt = ve;
	}
	
	/* edge */
	ve->ed = ed;
	
	++(hgvt->hgven);
	
	return ve;
}

/* for make hgppdface to ppdface */
void insert_hgvted( HGvt *vt, HGed *ed )
{
	HGvted *ve, *nve;
	double angle;
	
	/* first */
	if (vt->shgve == (HGvted *) NULL) {
		ve = create_hgvted( vt, ed );
		ve->angle = 0.0;
		return;
	}
	
	/* calc angle */
	ve    = vt->shgve;
	angle = hg_calc_angle( vt, hg_another_vt(ve->ed, vt), hg_another_vt(ed, vt) );
	
	while ( (ve != (HGvted *) NULL) && (angle > ve->angle) ) {
		ve = ve->nxt;
	}
	
	/* last */
	if (ve == (HGvted *) NULL) {
		ve = create_hgvted( vt, ed );
		ve->angle = angle;
		return;
	} 
	
	nve = (HGvted *) malloc( sizeof(HGvted) );
	
	nve->prv = ve->prv;
	nve->nxt = ve;
	if (ve->prv != (HGvted *) NULL) 
		ve->prv->nxt = nve;
	ve->prv = nve;
	if (vt->shgve == ve) vt->shgve = nve;
	
	nve->ed = ed;
	nve->angle = angle;
	
	++( vt->hgven );
	
	return;
}

/* for make hgppdface to ppdface */
HGvted *InsertHGvted( HGvt *vt, HGvted *ve, HGed *ed )
{
	HGvted *nve;
	
	nve = (HGvted *) malloc( sizeof(HGvted) );
	
	nve->prv = ve->prv;
	nve->nxt = ve;
	if (ve->prv != (HGvted *) NULL) 
		ve->prv->nxt = nve;
	ve->prv = nve;
	if (vt->shgve == ve) vt->shgve = nve;
	
	nve->ed = ed;
	
	++( vt->hgven );
	
	return nve;
}

double hg_calc_angle( HGvt *v1, HGvt *v2, HGvt *v3 )
{
	double cs, cs_angle;
	int    i;
	double  d1, d2, d3;
	Vec2d  sub1, sub2;
	
	sub1.x = v2->uvw.x - v1->uvw.x;
	sub1.y = v2->uvw.y - v1->uvw.y;
	sub2.x = v3->uvw.x - v1->uvw.x;
	sub2.y = v3->uvw.y - v1->uvw.y;
	
	d1 = V2Length( &sub1 );
	d2 = V2Length( &sub2 );
	d3 = V2Dot( &sub1, &sub2 );
	
	if ( (d1 < SMDZEROEPS) || (d2 < SMDZEROEPS) ) {
		cs = 0.0;
	} else {
		cs = d3 / ( d1 * d2 );
	}
	
	if ( fabs(cs + 1.0) < SMDZEROEPS ) {
		return 180.0;
	}
	
	cs_angle = RTOD * acos(cs);
	i = V2Signi(&(sub1), &(sub2));
	
	if ( fabs(cs) < SMDZEROEPS ) {
		if ( i == SMD_ON ) {    /* plus */
			return 90.0;
		} else { /* minus */
			return 270.0;
		}
	}
	
	if ( fabs(cs - 1.0) < SMDZEROEPS ) {
		return 0.0;
	}
	
	if (!i) {
		cs_angle = ( 360.0 - cs_angle );
	}
	
	return cs_angle;
}

HGvt *hg_another_vt( HGed *ed, HGvt *vt )
{
	if ( ed == (HGed *) NULL ) return (HGvt *) NULL;
	
	if (ed->sv == vt) return ed->ev;
	else return ed->sv;
}

HGvt *HGedAnotherVertex( HGed *ed, HGvt *vt )
{
	if ( ed == (HGed *) NULL ) return (HGvt *) NULL;
	
	if (ed->sv == vt) return ed->ev;
	else return ed->sv;
}

HGsf *HGedLeftFace( HGed *ed, HGvt *start )
{
	if ( ed->sv == start ) {
		/*     display("sf %d\n", ed->lf); */
		return ed->lf;
	} else return ed->rf;
}

HGsf *HGedRightFace( HGed *ed, HGvt *start )
{
	if ( ed->sv == start ) return ed->rf;
	else return ed->lf;
}

void HGedAppendLeftFace( HGed *ed, HGvt *vt, HGsf *sf )
{
	if ( ed->sv == vt ) {
		ed->lf = sf;
	} else {
		ed->rf = sf;
	}
}

HGvted *find_hgvted( HGvt *vt, HGed *ed )
{
	HGvted *vted;
	
	for ( vted = vt->shgve; vted != (HGvted *) NULL; vted = vted->nxt ) {
		if ( vted->ed == ed ) return vted;
	}
	return (HGvted *) NULL;
}

HGed *HGvtedNextCCWEdge( HGvt *vt, HGed *ed )
{
	HGvted *vted;
	
	for ( vted = vt->shgve; vted != (HGvted *) NULL; vted = vted->nxt ) {
		
		if ( vted->ed == ed ) {
			
			if ( vted != vt->shgve ) {
				return vted->prv->ed;
			} else {
				return vt->ehgve->ed;
			}
			
		}
		
	}
	return (HGed *) NULL;
}

void free_hgppdvertexedge( HGvt *vt )
{
	HGvted *ve, *venxt;
	
	for (ve = vt->shgve; ve != (HGvted *) NULL; ve = venxt) {
		venxt = ve->nxt;
		free_hgvted(ve, vt);
	}
	vt->hgven = 0;
	vt->shgve = vt->ehgve = (HGvted *) NULL;
}

void free_hgvted(HGvted *ve, HGvt *vt)
{
	if (ve == (HGvted *) NULL) return;
	
	ve->ed = (HGed *) NULL;
	
	if (vt->shgve == ve) {
		if ((vt->shgve = ve->nxt) != (HGvted *) NULL)
			ve->nxt->prv = (HGvted *) NULL;
		else {
			vt->ehgve = (HGvted *) NULL;
		}
	} else if (vt->ehgve == ve) {
		ve->prv->nxt = (HGvted *) NULL;
		vt->ehgve = ve->prv;
	} else {
		ve->prv->nxt = ve->nxt;
		ve->nxt->prv = ve->prv;
	}
	free(ve);
	--( vt->hgven );
}

/* HG vertex -> other vertex link */

HGvtvt *create_hgvtvt(HGvt *hgvt, Id id)
{
	HGvtvt *vv;
	
	if (id == SMDNULL) return (HGvtvt *) NULL;
	
	vv = (HGvtvt *) malloc(sizeof(HGvtvt));
	
	vv->nxt = (HGvtvt *) NULL;
	if (hgvt->shgvv == (HGvtvt *) NULL) {
		vv->prv       = (HGvtvt *) NULL;
		hgvt->ehgvv = hgvt->shgvv = vv;
	} else {
		vv->prv       = hgvt->ehgvv;
		hgvt->ehgvv = hgvt->ehgvv->nxt = vv;
	}
	
	/* other vertex id ( used in sid ) */
	vv->id  = id;
	
	vv->val = 0.0;
	
	++(hgvt->hgvvn);
	
	return vv;
}

HGvtvt *find_sort_hgvtvt(HGvt *vt, Id id)
{
	HGvtvt *vv, *nvv;
	
	vv = vt->shgvv;
	
	if (vt->shgvv == (HGvtvt *) NULL) {
		nvv = create_hgvtvt(vt, id);
		return nvv;
	} 
	
	do {
		if (vv->id == id) return vv;
		if (vv->id > id) break;
	} while ((vv = vv->nxt) != (HGvtvt *) NULL);
	
	if (vv == (HGvtvt *) NULL) {
		nvv = create_hgvtvt(vt, id);
		return nvv;
	}
	
	nvv = (HGvtvt *) malloc(sizeof(HGvtvt));
	
	nvv->prv = vv->prv;
	nvv->nxt = vv;
	if (vv->prv != (HGvtvt *) NULL)
		vv->prv->nxt = nvv;
	vv->prv = nvv;
	if (vt->shgvv == vv) vt->shgvv = nvv;
	
	nvv->id  = id;
	
	nvv->val = 0.0;
	
	++( vt->hgvvn );
	
	return nvv;
}

void FreeHGppdVertexVertex( HGfc *hgfc )
{
	HGvt *vt;
	
	for ( vt = hgfc->shgvt; vt != (HGvt *) NULL; vt = vt->nxt ) {
		free_hgppdvertexvertex( vt );
	}
	
}

void free_hgppdvertexvertex( HGvt *vt )
{
	HGvtvt *vv, *vvnxt;
	void free_hgvtvt(HGvtvt *, HGvt *);
	
	for (vv = vt->shgvv; vv != (HGvtvt *) NULL; vv = vvnxt) {
		vvnxt = vv->nxt;
		free_hgvtvt(vv, vt);
	}
	vt->hgvvn = 0;
	vt->shgvv = vt->ehgvv = (HGvtvt *) NULL;
}

void free_hgvtvt(HGvtvt *vv, HGvt *vt)
{
	if (vv == (HGvtvt *) NULL) return;
	
	if (vt->shgvv == vv) {
		if ((vt->shgvv = vv->nxt) != (HGvtvt *) NULL)
			vv->nxt->prv = (HGvtvt *) NULL;
		else {
			vt->ehgvv = (HGvtvt *) NULL;
		}
	} else if (vt->ehgvv == vv) {
		vv->prv->nxt = (HGvtvt *) NULL;
		vt->ehgvv = vv->prv;
	} else {
		vv->prv->nxt = vv->nxt;
		vv->nxt->prv = vv->prv;
	}
	free(vv);
	
	--( vt->hgvvn );
}

/* loop */
HGlp *create_hgppdloop(HGfc *fc)
{
	HGlp *lp;
	
	lp = (HGlp *) malloc(sizeof(HGlp));
	
	lp->nxt = (HGlp *) NULL;
	if (fc->shglp == (HGlp *) NULL) {
		lp->prv   = (HGlp *) NULL;
		fc->ehglp = fc->shglp = lp;
	} else {
		lp->prv   = fc->ehglp;
		fc->ehglp = fc->ehglp->nxt = lp;
	}
	
	lp->lp = (Splp *) NULL;
    
	++( fc->hgln );
	
	return lp;
}

void free_hgppdloop(HGlp *lp, HGfc *fc)
{
	
	if (lp == (HGlp *) NULL) return;
	
	lp->lp = (Splp *) NULL;
	
	if (fc->shglp == lp) {
		if ((fc->shglp = lp->nxt) != (HGlp *) NULL)
			lp->nxt->prv = (HGlp *) NULL;
		else {
			fc->ehglp = (HGlp *) NULL;
		}
	} else if (fc->ehglp == lp) {
		lp->prv->nxt = (HGlp *) NULL;
		fc->ehglp = lp->prv;
	} else {
		lp->prv->nxt = lp->nxt;
		lp->nxt->prv = lp->prv;
	}
	
	free(lp);
	--( fc->hgln );
}

/* control vertex  */
HGcv *create_hgppdctrlvertex(HGfc *fc)
{
	HGcv *cv;
	
	cv = (HGcv *) malloc(sizeof(HGcv));
	
	cv->nxt = (HGcv *) NULL;
	if (fc->shgcv == (HGcv *) NULL) {
		cv->prv   = (HGcv *) NULL;
		fc->ehgcv = fc->shgcv = cv;
	} else {
		cv->prv   = fc->ehgcv;
		fc->ehgcv = fc->ehgcv->nxt = cv;
	}
	
	cv->vt = (Spvt *) NULL;
    
	++( fc->hgcn );
	
	return cv;
}

void free_hgppdctrlvertex(HGcv *cv, HGfc *fc)
{
	
	if (cv == (HGcv *) NULL) return;
	
	cv->vt = (Spvt *) NULL;
	
	if (fc->shgcv == cv) {
		if ((fc->shgcv = cv->nxt) != (HGcv *) NULL)
			cv->nxt->prv = (HGcv *) NULL;
		else {
			fc->ehgcv = (HGcv *) NULL;
		}
	} else if (fc->ehgcv == cv) {
		cv->prv->nxt = (HGcv *) NULL;
		fc->ehgcv = cv->prv;
	} else {
		cv->prv->nxt = cv->nxt;
		cv->nxt->prv = cv->prv;
	}
	
	free(cv);
	--( fc->hgcn );
}

HGsf *create_hgppdsurface( HGfc *fc )
{
	HGsf *sf;
	
	sf = (HGsf *) malloc(sizeof(HGsf));
	
	sf->nxt = (HGsf *) NULL;
	if ( fc->shgsf == (HGsf *) NULL ) {
		sf->prv   = (HGsf *) NULL;
		fc->ehgsf = fc->shgsf = sf;
	} else {
		sf->prv   = fc->ehgsf;
		fc->ehgsf = fc->ehgsf->nxt = sf;
	}
	
	/* half edge */
	sf->hen   = 0;
	sf->shghe = (HGhe *) NULL;
	
	sf->no = fc->hgsn;
	sf->qf = (QFace *) NULL;
	
	++( fc->hgsn );
	
	return sf;
}

void free_hgppdsurface( HGsf *sf, HGfc *fc )
{
	HGhe *he;
	
	if (sf == (HGsf *) NULL) return;
	
	/* free halfedge */
	he = sf->shghe;
	while ( he != (HGhe *) NULL ) {
		he = free_hgppdhalfedge( he, sf );
	}
	
	if ( fc->shgsf == sf ) {
		if ( (fc->shgsf = sf->nxt) != (HGsf *) NULL )
			sf->nxt->prv = (HGsf *) NULL;
		else {
			fc->ehgsf = (HGsf *) NULL;
		}
	} else if (fc->ehgsf == sf) {
		sf->prv->nxt = (HGsf *) NULL;
		fc->ehgsf = sf->prv;
	} else {
		sf->prv->nxt = sf->nxt;
		sf->nxt->prv = sf->prv;
	}
	
	free( sf );
	--( fc->hgsn );
}

/* if surface is triangle */
HGsf *create_hgppdsurface_edge( HGfc *hgfc, HGvt *v0, HGvt *v1, HGvt *v2,
							   HGed *e0, HGed *e1, HGed *e2 )
{
	HGsf *sf;
	HGhe *he;
	
	sf = create_hgppdsurface( hgfc );
	he = create_hgppdhalfedge( sf );
	he->vt = v0; he->ed = e0;
	he = create_hgppdhalfedge( sf );
	he->vt = v1; he->ed = e1;
	he = create_hgppdhalfedge( sf );
	he->vt = v2; he->ed = e2;
	
	/*   sf->vt[0] = v0; */
	/*   sf->ed[0] = e0; */
	/*   sf->vt[1] = v1; */
	/*   sf->ed[1] = e1; */
	/*   sf->vt[2] = v2; */
	/*   sf->ed[2] = e2; */
	
	if ( (e0->sv == v1) && (e0->ev == v0) ) {
		e0->rf = sf;
	} else {
		e0->lf = sf;
	}
	if ( (e1->sv == v2) && (e1->ev == v1) ) {
		e1->rf = sf;
	} else {
		e1->lf = sf;
	}
	if ( (e2->sv == v0) && (e2->ev == v2) ) {
		e2->rf = sf;
	} else {
		e2->lf = sf;
	}
	
	/*   calc_hgsfnorm( sf ); */
	
	return sf;
}

HGsf *another_hgsf( HGed *ed, HGsf *sf )
{
	//  if ( (ed->rf != sf) && (ed->lf != sf ) ) {
	//    display("Warning: Topology is incorrected.\n");
	//  }
	if ( ed->rf == sf ) return ed->lf;
	else                return ed->rf;
}

/* halfedge */
HGhe *create_hgppdhalfedge( HGsf *sf )
{
	HGhe *he;
	
	he = (HGhe *) malloc( sizeof(HGhe) );
	
	if (sf->shghe == (HGhe *) NULL) {	/* first */
		sf->shghe = he;
		he->prv  = he;
		he->nxt  = he;
	} else {
		he->prv  = sf->shghe->prv;
		he->nxt  = sf->shghe;
		sf->shghe->prv->nxt = he;
		sf->shghe->prv = he;
	}
	/* id */
	he->no   = sf->hen;
	/* back face */
	he->bhgsf = sf;
	/* edge */
	he->ed   = (HGed *) NULL;
	/* vertex */
	he->vt  = (HGvt *) NULL;
	
	++( sf->hen );
	
	return he;
}

HGhe *free_hgppdhalfedge(HGhe *he, HGsf *face)
{
	HGhe *newhe;
	
	if (he->nxt == he) {
		free( he );
		--(face->hen);
		return (HGhe *) NULL;
	} else {
		newhe = he->nxt;
		he->prv->nxt = he->nxt;
		he->nxt->prv = he->prv;
		free(he);
		--(face->hen);
		return newhe;
	}
}

void CalcHGsfNorm( HGfc *hgfc )
{
	HGsf *sf;
	void calc_hgsfnorm( HGsf * );
	
	for ( sf = hgfc->shgsf; sf != (HGsf *) NULL; sf = sf->nxt ) {
		calc_hgsfnorm( sf );
	}
}

void calc_hgsfnorm( HGsf *sf )
{
	HGvt   *v1, *v2, *v3;
	Vec    vec1, vec2, vec3, vec4, vec5;
	
	/*   v1 = sf->vt[0]; */
	/*   v2 = sf->vt[1]; */
	/*   v3 = sf->vt[2]; */
	v1 = sf->shghe->vt;
	v2 = sf->shghe->nxt->vt;
	v3 = sf->shghe->nxt->nxt->vt;
	vec1.x = v1->vec.x;
	vec1.y = v1->vec.y;
	vec1.z = v1->vec.z;
	vec2.x = v2->vec.x;
	vec2.y = v2->vec.y;
	vec2.z = v2->vec.z;
	vec3.x = v3->vec.x;
	vec3.y = v3->vec.y;
	vec3.z = v3->vec.z;
	V3Sub( &vec2, &vec1, &vec4 );
	V3Sub( &vec3, &vec1, &vec5 );
	V3Cross( &vec4, &vec5, &(sf->nrm) );
	V3Normalize( &(sf->nrm) );
}

/* free functions */

void FreeHGppd( HPpd *ppd )
{
	free_hgppd( ppd->hgppd1 ); ppd->hgppd1 = (HGppd *) NULL;
	free_hgppd( ppd->hgppd2 ); ppd->hgppd2 = (HGppd *) NULL;
}

void FreeHGppdFace( HGppd *ppd )
{
	HGfc *face, *nface;
	
	for (face = ppd->shgfc; face != (HGfc *) NULL; face = nface) {
		nface = face->nxt;
		free_hgppdface( face, ppd );
	}
	ppd->shgfc = ppd->ehgfc = (HGfc *) NULL;
	ppd->nhgfc = 0;
	
}

void FreeHGppdVertex( HGfc *fc )
{
	HGvt *vertex, *nvertex;
	
	for (vertex = fc->shgvt; vertex != (HGvt *) NULL; vertex = nvertex) {
		nvertex = vertex->nxt;
		free_hgppdvertex( vertex, fc );
	}
	fc->shgvt = fc->ehgvt = (HGvt *) NULL;
	fc->hgvn = 0;
	
}

void FreeHGppdEdge( HGfc *fc )
{
	HGed *edge, *nedge;
	void free_hgppdedge( HGed *, HGfc * );
	
	for (edge = fc->shged; edge != (HGed *) NULL; edge = nedge) {
		nedge = edge->nxt;
		free_hgppdedge( edge, fc );
	}
	fc->shged = fc->ehged = (HGed *) NULL;
	fc->hgen = 0;
	
}

void FreeHGppdSurface( HGfc *fc )
{
	HGsf *surface, *nsurface;
	
	for ( surface = fc->shgsf; surface != (HGsf *) NULL; surface = nsurface ) {
		nsurface = surface->nxt;
		free_hgppdsurface( surface, fc );
	}
	fc->shgsf = fc->ehgsf = (HGsf *) NULL;
	fc->hgsn = 0;
	
}

void FreeHGppdLoop( HGfc *fc )
{
	HGlp *loop, *nloop;
	
	for (loop = fc->shglp; loop != (HGlp *) NULL; loop = nloop) {
		nloop = loop->nxt;
		free_hgppdloop( loop, fc );
	}
	fc->shglp = fc->ehglp = (HGlp *) NULL;
	fc->hgln = 0;
	
}

void FreeHGppdCtrlvertex( HGfc *fc )
{
	HGcv *cv, *ncv;
	
	for (cv = fc->shgcv; cv != (HGcv *) NULL; cv = ncv) {
		ncv = cv->nxt;
		free_hgppdctrlvertex( cv, fc );
	}
	fc->shgcv = fc->ehgcv = (HGcv *) NULL;
	fc->hgcn = 0;
	
}

/* "find" functions */
HGlp *find_hgppdloop( Splp *lp, HGfc *hgfc )
{
	HGlp *hglp;
	
	if ( lp == (Splp *) NULL ) return NULL;
	
	for ( hglp = hgfc->shglp; hglp != (HGlp *) NULL; hglp = hglp->nxt ) {
		if ( lp == hglp->lp ) return hglp;
	}
	return (HGlp *) NULL;
}

HGcv *find_hgppdctrlvertex( Spvt *vt, HGfc *hgfc )
{
	HGcv *hgcv;
	
	if ( vt == (Spvt *) NULL ) return NULL;
	
	for ( hgcv = hgfc->shgcv; hgcv != (HGcv *) NULL; hgcv = hgcv->nxt ) {
		if ( vt == hgcv->vt ) return hgcv;
	}
	return (HGcv *) NULL;
}

/* for harmonicmap save */
Sppd *hgfc_to_ppd( HGfc *hgfc )
{
	Sppd *ppd;
	Spvt *pvt;
	Spfc *pfc;
	Sphe *phe;
	HGvt *hgvt;
	HGsf *hgsf;
	HGhe *hghe;
	
	ppd = create_ppd();
	
	ppd->spso = create_ppdsolid( ppd );
	ppd->sppt = create_ppdpart( ppd );
	ppd->sppt->bpso = ppd->spso;
	
	for ( hgvt = hgfc->shgvt; hgvt != (HGvt *) NULL; hgvt = hgvt->nxt ) {
		pvt = create_ppdvertex( ppd );
		pvt->vec.x = hgvt->uvw.x;
		pvt->vec.y = hgvt->uvw.y;
		pvt->vec.z = 0.0;
		pvt->bpso  = ppd->spso;
		hgvt->tmp_vt = pvt;
	}
	for ( hgsf = hgfc->shgsf; hgsf != (HGsf *) NULL; hgsf = hgsf->nxt ) {
		pfc = create_ppdface( ppd );
		pfc->bpso = ppd->spso;
		pfc->bppt = ppd->sppt;
		
		hghe = hgsf->shghe;
		
		/*     for ( i = 0;i < TRIANGLE; ++i ) { */
		do { 
			
			phe = create_ppdhalfedge( pfc );
			phe->vt = hghe->vt->tmp_vt;
			
		} while ( ( hghe = hghe->nxt ) != hgsf->shghe );
		
	}
	
	return ppd;
}

/*
void printhgfc( HGfc *hgfc, int from )
{
int i;
HGvt *hgvt;
HGed *hged;
HGsf *hgsf;
HGhe *he;

 display("------------- hgfc%d %d ------------\n", from, hgfc->id );
 
  for ( hgvt = hgfc->shgvt; hgvt != (HGvt *) NULL; hgvt = hgvt->nxt ) {
  display("\thgvt %d vt %d\n",
  hgvt->no,
  ( hgvt->vt != NULL ) ? hgvt->vt->no : SMDNULL );
  }
  
   for ( hged = hgfc->shged; hged != (HGed *) NULL; hged = hged->nxt ) {
   display("\thged %d sv %d ev %d\n", hged->no, hged->sv->no, hged->ev->no );
   }
   
	for ( hgsf = hgfc->shgsf; hgsf != (HGsf *) NULL; hgsf = hgsf->nxt ) {
    display("\thsf %d\n", hgsf->no);
    for ( i = 0, he = hgsf->shghe; i < hgsf->hen; ++i, he = he->nxt ) {
	display("\tvt %d type %d ed %d type %d\n",
	he->vt->no,
	he->vt->sp_type,
	he->ed->no,
	he->ed->sp_type);
    }
	}
	}
*/

void HGfcTriangulation( HGfc *hgfc )
{
	int i, n;
	HGsf *sf, *nsf;
	
	i = 0;
	n = hgfc->hgsn;
	sf = hgfc->shgsf;
	
	while ( i < n ) {
		
		if ( sf->hen == TRIANGLE ) {
			sf = sf->nxt; i++;
			continue;
		}
		nsf = sf->nxt;
		HGsfTriangulation( sf, hgfc );
		free_hgppdsurface( sf, hgfc );
		sf = nsf; ++i;
	}
}

void HGsfTriangulation( HGsf *sf, HGfc *hgfc )
{
	int i, n;
	HGed **edarray, **newedarray;
	HGvt **vtarray, **newvtarray;
	HGsf **sfarray;
	HGhe *he, *he0, *he1, *he2;
	HGhe *create_hgppdhalfedge( HGsf * );
	HGed   *create_hgppdedge( HGfc * );
	HGsf *create_hgppdsurface( HGfc * );
	void insert_hgvted( HGvt *, HGed * );
	
	n = sf->hen;
	
	he = sf->shghe;
	i = 0;
	while ( i < sf->hen ) {
		
		/*     display("hgfc %d (Tri) vt %d type %d\n", hgfc->id, he->vt->no, he->vt->sp_type ); */
		if ( he->vt->sp_type != SP_VERTEX_BOUNDARY ) {
			sf->shghe = he;
			break;
		}
		he = he->nxt; ++i;
	}
    
	edarray = (HGed **) malloc( n * sizeof( HGed * ) );
	vtarray = (HGvt **) malloc( n * sizeof( HGvt * ) );
	
	for( i = 0, he = sf->shghe; i < n; ++i, he = he->nxt ) {
		vtarray[i] = he->vt;
		edarray[i] = he->ed;
	}
	
	/* create new surface */
	sfarray = (HGsf **) malloc( (n - 2) * sizeof( HGsf * ) );
	for ( i = 0; i < n - 2; ++i ) {
		sfarray[i] = create_hgppdsurface( hgfc );
	}
	newvtarray = (HGvt **) malloc( (n - 1) * sizeof( HGvt * ) );
	for ( i = 0; i < n - 1; ++i ) {
		newvtarray[i] = vtarray[i+1];
	}
	newedarray = (HGed **) malloc( (n - 1) * sizeof( HGed * ) );
	newedarray[0] = sf->shghe->ed;
	newedarray[ n - 2 ] = sf->shghe->prv->ed;
	
	for ( i = 1; i < n - 2; ++i ) {
		newedarray[i] = create_hgppdedge( hgfc );
		newedarray[i]->sv = vtarray[0];
		newedarray[i]->ev = newvtarray[i];
		newedarray[i]->rf = sfarray[i-1];
		newedarray[i]->lf = sfarray[i];
		insert_hgvted( newedarray[i]->sv, newedarray[i] );
		insert_hgvted( newedarray[i]->ev, newedarray[i] );
	}
	
	for ( i = 0; i < n - 2; ++i ) {
		
		he0 = create_hgppdhalfedge( sfarray[i] );
		he0->vt = vtarray[0];
		he0->ed = newedarray[i];
		he1 = create_hgppdhalfedge( sfarray[i] );
		he1->vt = newvtarray[i];
		he1->ed = edarray[i+1];
		he2 = create_hgppdhalfedge( sfarray[i] );
		he2->vt = newvtarray[i+1];
		he2->ed = newedarray[i+1];
		
		if ( he1->ed->rf == sf ) he1->ed->rf = sfarray[i];
		if ( he1->ed->lf == sf ) he1->ed->lf = sfarray[i];
	}
	if ( edarray[0]->rf == sf ) edarray[0]->rf = sfarray[0];
	if ( edarray[0]->lf == sf ) edarray[0]->lf = sfarray[0];
	if ( edarray[n-1]->rf == sf ) edarray[n-1]->rf = sfarray[n-3];
	if ( edarray[n-1]->lf == sf ) edarray[n-1]->lf = sfarray[n-3];
	
	free(edarray); free(newedarray);
	free(vtarray); free(newvtarray);
	free(sfarray); 
	
}  

void HGfcTriangulation_noEdge( HGfc *hgfc )
{
	int i, n;
	HGsf *sf, *nsf;
	
	i = 0;
	n = hgfc->hgsn;
	sf = hgfc->shgsf;
	
	while ( i < n ) {
		
		if ( sf->hen == TRIANGLE ) {
			sf = sf->nxt; i++;
			continue;
		}
		nsf = sf->nxt;
		HGsfTriangulation_noEdge( sf, hgfc );
		free_hgppdsurface( sf, hgfc );
		sf = nsf; ++i;
	}
}

void HGsfTriangulation_noEdge( HGsf *sf, HGfc *hgfc )
{
	int i, n;
	HGvt **vtarray, **newvtarray;
	HGsf **sfarray;
	HGhe *he, *he0, *he1, *he2;
	
	n = sf->hen;
	
	he = sf->shghe;
	i = 0;
	while ( i < sf->hen ) {
		
		if ( he->vt->sp_type != SP_VERTEX_BOUNDARY ) {
			sf->shghe = he;
			break;
		}
		he = he->nxt; ++i;
	}
    
	vtarray = (HGvt **) malloc( n * sizeof( HGvt * ) );
	
	for( i = 0, he = sf->shghe; i < n; ++i, he = he->nxt ) {
		vtarray[i] = he->vt;
	}
	
	/* create new surface */
	sfarray = (HGsf **) malloc( (n - 2) * sizeof( HGsf * ) );
	for ( i = 0; i < n - 2; ++i ) {
		sfarray[i] = create_hgppdsurface( hgfc );
	}
	newvtarray = (HGvt **) malloc( (n - 1) * sizeof( HGvt * ) );
	for ( i = 0; i < n - 1; ++i ) {
		newvtarray[i] = vtarray[i+1];
	}
	for ( i = 0; i < n - 2; ++i ) {
		
		he0 = create_hgppdhalfedge( sfarray[i] );
		he0->vt = vtarray[0];
		he1 = create_hgppdhalfedge( sfarray[i] );
		he1->vt = newvtarray[i];
		he2 = create_hgppdhalfedge( sfarray[i] );
		he2->vt = newvtarray[i+1];
		
	}
	
	free(vtarray); free(newvtarray);
	free(sfarray);
	
}  
