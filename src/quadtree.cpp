//
// quadtree.cpp
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>
#include "smd.h"
#include "quadtree.h"
#include "trisquare.h"

/* create quadtree functions */

QTree *create_qtreechild(QTree *parent, int level, int id, 
						 double xmin, double xmax,
						 double ymin, double ymax)
{
	QTree *qtree;
	
	qtree = (QTree *) malloc(sizeof(QTree));
	
	qtree->parent   = parent;
	qtree->level    = level;
	qtree->id       = id;
	qtree->child[0] = (QTree *) NULL;
	qtree->child[1] = (QTree *) NULL;
	qtree->child[2] = (QTree *) NULL;
	qtree->child[3] = (QTree *) NULL;
	qtree->qr.xmin  = xmin;
	qtree->qr.xmax  = xmax;
	qtree->qr.ymin  = ymin;
	qtree->qr.ymax  = ymax;
	qtree->qen      = 0;
	qtree->sqe      = (QEdge *) NULL;
	qtree->eqe      = (QEdge *) NULL;
	qtree->qfn      = 0;
	qtree->sqf      = (QFace *) NULL;
	qtree->eqf      = (QFace *) NULL;
	qtree->qvn      = 0;
	qtree->sqv      = (QVertex *) NULL;
	qtree->eqv      = (QVertex *) NULL;
	
	return qtree;
}  

QTree *create_qtreechild_qr(QTree *parent, int level, int id,
							QRange *qr)
{
	QTree *qtree;
	
	qtree = (QTree *) malloc(sizeof(QTree));
	
	qtree->parent   = parent;
	qtree->level    = level;
	qtree->id       = id;
	qtree->child[0] = (QTree *) NULL;
	qtree->child[1] = (QTree *) NULL;
	qtree->child[2] = (QTree *) NULL;
	qtree->child[3] = (QTree *) NULL;
	qtree->qr.xmin  = qr->xmin;
	qtree->qr.xmax  = qr->xmax;
	qtree->qr.ymin  = qr->ymin;
	qtree->qr.ymax  = qr->ymax;
	qtree->qen      = 0;
	qtree->sqe      = (QEdge *) NULL;
	qtree->eqe      = (QEdge *) NULL;
	qtree->qfn      = 0;
	qtree->sqf      = (QFace *) NULL;
	qtree->eqf      = (QFace *) NULL;
	qtree->qvn      = 0;
	qtree->sqv      = (QVertex *) NULL;
	qtree->eqv      = (QVertex *) NULL;
	
	return qtree;
}  

/* Vertex */
QVertex *insert_qtree_vertex(Spvt *vt, QTree *qtree)
{
	QVertex *qv;
	
	qv = (QVertex *) malloc(sizeof(QVertex));
	qv->vt  = vt;
	qv->qt  = qtree;
	/*   vt->qv  = qv; */
	
	qv->nxt = (QVertex *) NULL;
	if (qtree->sqv == (QVertex *) NULL) {
		qv->prv = (QVertex *) NULL;
		qtree->eqv = qtree->sqv = qv;
	} else {
		qv->prv    = qtree->eqv;
		qtree->eqv = qtree->eqv->nxt = qv;
	}
	
	++(qtree->qvn);
	
	return qv;
}

/* Edge */
QEdge *insert_qtree_edge(Sped *ed, QTree *qtree)
{
	QEdge *qe;
	
	qe = (QEdge *) malloc(sizeof(QEdge));
	qe->ed  = ed;
	qe->qt  = qtree;
	/*   ed->qe  = qe; */
	
	qe->nxt = (QEdge *) NULL;
	if (qtree->sqe == (QEdge *) NULL) {
		qe->prv = (QEdge *) NULL;
		qtree->eqe = qtree->sqe = qe;
	} else {
		qe->prv    = qtree->eqe;
		qtree->eqe = qtree->eqe->nxt = qe;
	}
	
	++(qtree->qen);
	
	return qe;
}

/* Face */
QFace *insert_qtree_face( HGsf *sf, QTree *qtree )
{
	QFace *qf;
	
	qf = (QFace *) malloc(sizeof(QFace));
	qf->sf  = sf;
	qf->qt  = qtree;
	sf->qf  = qf;
	
	qf->nxt = (QFace *) NULL;
	if (qtree->sqf == (QFace *) NULL) {
		qf->prv = (QFace *) NULL;
		qtree->eqf = qtree->sqf = qf;
	} else {
		qf->prv    = qtree->eqf;
		qtree->eqf = qtree->eqf->nxt = qf;
	}
	
	++(qtree->qfn);
	
	return qf;
}

/* free quadtree functions */

void free_ppdqtree(Sppd *ppd)
{
	free_ppdqtree_child( ppd->qt, ppd );
	ppd->qt = (QTree *) NULL;
}

void free_ppdqtree_child(QTree *qtree, Sppd *ppd)
{
	int  i;
	
	if (qtree == (QTree *) NULL) return;
	
	for (i = 0; i < 4; ++i) {
		if (qtree->child[i] != (QTree *) NULL) {
			free_ppdqtree_child(qtree->child[i], ppd);
		}
	}
	free_qedge(qtree);
	free_qface(qtree);
	free_qvertex(qtree);
	free(qtree);
	qtree = (QTree *) NULL;
	--(ppd->qn);
}

int free_noinfo_ppdqtree_child(QTree *qtree, Sppd *ppd)
{
	int  i, flag;
	
	if (qtree == (QTree *) NULL) return SUCCEED;
	else {
		if (qtree->qfn || qtree->qen) return FAIL;
		flag = SUCCEED;
		for (i = 0; i < 4; ++i) {
			if (free_noinfo_ppdqtree_child(qtree->child[i], ppd) == FAIL)
				flag = FAIL;
		}
		if (flag == SUCCEED) {
			free(qtree);
			qtree = (QTree *) NULL;
			--(ppd->qn);
			return SUCCEED;
		} else {
			return FAIL;
		}
	}
}

/* Edge */
void free_qedge(QTree *qtree)
{
	QEdge *qe, *nqe;
	
	for (qe = qtree->sqe; qe != (QEdge *) NULL; qe = qe->nxt) {
		nqe = qe->nxt;
		delete_qtree_edge(qe, qtree);
	}
	qtree->sqe = (QEdge *) NULL;
	qtree->eqe = (QEdge *) NULL;
}

void delete_qtree_edge(QEdge *qe, QTree *qtree)
{
	if (qe == (QEdge *) NULL) return;
	/*   if (qe->ed != (Sped *) NULL) qe->ed->qe = (QEdge *) NULL; */
	
	if (qtree->sqe == qe) {
		if ((qtree->sqe = qe->nxt) != (QEdge *) NULL)
			qe->nxt->prv = (QEdge *) NULL;
		else {
			qtree->eqe = (QEdge *) NULL;
		}
	} else if (qtree->eqe == qe) {
		qe->prv->nxt = (QEdge *) NULL;
		qtree->eqe = qe->prv;
		
	} else {
		qe->prv->nxt = qe->nxt;
		qe->nxt->prv = qe->prv;
	}
	--(qtree->qen);
	free(qe);
}

/* Vertex */
void free_qvertex( QTree *qtree )
{
	QVertex *qv, *nqv;
	
	for (qv = qtree->sqv; qv != (QVertex *) NULL; qv = qv->nxt) {
		nqv = qv->nxt;
		delete_qtree_vertex(qv, qtree);
	}
	qtree->sqv = (QVertex *) NULL;
	qtree->eqv = (QVertex *) NULL;
}

void delete_qtree_vertex(QVertex *qv, QTree *qtree)
{
	if (qv == (QVertex *) NULL) return;
	/*   if (qv->vt != (Spvt *) NULL) { */
	/*     qv->vt->qv = (QVertex *) NULL; */
	/*   } */
	
	if (qtree->sqv == qv) {
		if ((qtree->sqv = qv->nxt) != (QVertex *) NULL)
			qv->nxt->prv = (QVertex *) NULL;
		else {
			qtree->eqv = (QVertex *) NULL;
		}
	} else if (qtree->eqv == qv) {
		qv->prv->nxt = (QVertex *) NULL;
		qtree->eqv = qv->prv;
	} else {
		qv->prv->nxt = qv->nxt;
		qv->nxt->prv = qv->prv;
	}
	--(qtree->qvn);
	free(qv);
}

/* Face */
void free_qface(QTree *qtree)
{
	QFace *qf, *nqf;
	
	for (qf = qtree->sqf; qf != (QFace *) NULL; qf = qf->nxt) {
		nqf = qf->nxt;
		delete_qtree_face(qf, qtree);
	}
	qtree->sqf = (QFace *) NULL;
	qtree->eqf = (QFace *) NULL;
}

void delete_qtree_face(QFace *qf, QTree *qtree)
{
	if (qf == (QFace *) NULL) return;
	if (qf->sf != (HGsf *) NULL) qf->sf->qf = (QFace *) NULL;
	
	if (qtree->sqf == qf) {
		if ((qtree->sqf = qf->nxt) != (QFace *) NULL)
			qf->nxt->prv = (QFace *) NULL;
		else {
			qtree->eqf = (QFace *) NULL;
		}
	} else if (qtree->eqf == qf) {
		qf->prv->nxt = (QFace *) NULL;
		qtree->eqf = qf->prv;
		
	} else {
		qf->prv->nxt = qf->nxt;
		qf->nxt->prv = qf->prv;
	}
	--(qtree->qfn);
	free(qf);
}

int decide_qrange_child_number(Vec2d *vec, QRange *qr, QRange *qrnew)
{
	double hx, hy;
	
	hx = (qr->xmin + qr->xmax) / 2.0;
	hy = (qr->ymin + qr->ymax) / 2.0;
	
	/*printf("(parent qr) %f %f %f %f\n", 
	qr->xmin, qr->xmax, 
	qr->ymin, qr->ymax);
	printf("(vec) %f %f %f\n", vec->x, vec->y, vec->z);*/
	
	if ((vec->x > qr->xmin) && 
		((vec->x < hx) || (fabs(vec->x - hx) < SMDZEROEPS)) &&
		(vec->y > qr->ymin) && 
		((vec->y < hy) || (fabs(vec->y - hy) < SMDZEROEPS))) {
		qrnew->xmin = qr->xmin;
		qrnew->xmax = hx;
		qrnew->ymin = qr->ymin;
		qrnew->ymax = hy;
		return 0;
	} else if ((vec->x > hx) && 
		((vec->x < qr->xmax) || (fabs(vec->x - qr->xmax) < SMDZEROEPS)) &&
		(vec->y > qr->ymin) && 
		((vec->y < hy) || (fabs(vec->y - hy) < SMDZEROEPS))) {
		qrnew->xmin = hx;
		qrnew->xmax = qr->xmax;
		qrnew->ymin = qr->ymin;
		qrnew->ymax = hy;
		return 1;
	} else if ((vec->x > qr->xmin) && 
		((vec->x < hx) || (fabs(vec->x - hx) < SMDZEROEPS)) &&
		(vec->y > hy) && 
		((vec->y < qr->ymax) || (fabs(vec->y - qr->ymax) < SMDZEROEPS))) {
		qrnew->xmin = qr->xmin;
		qrnew->xmax = hx;
		qrnew->ymin = hy;
		qrnew->ymax = qr->ymax;
		return 2;
	} else {
//	} else if ((vec->x > hx) && 
//		((vec->x < qr->xmax) || (fabs(vec->x - qr->xmax) < SMDZEROEPS)) &&
//		(vec->y > hy) && 
//		((vec->y < qr->ymax) || (fabs(vec->y - qr->ymax) < SMDZEROEPS))) {
		qrnew->xmin = hx;
		qrnew->xmax = qr->xmax;
		qrnew->ymin = hy;
		qrnew->ymax = qr->ymax;
		return 3;
	}
}

int decide_qrange_child_num(Vec2d *vec, QRange *qr)
{
	double hx, hy;
	
	hx = (qr->xmin + qr->xmax) / 2.0;
	hy = (qr->ymin + qr->ymax) / 2.0;
	
	if ((vec->x > qr->xmin) && 
		((vec->x < hx) || (fabs(vec->x - hx) < SMDZEROEPS)) &&
		(vec->y > qr->ymin) && 
		((vec->y < hy) || (fabs(vec->y - hy) < SMDZEROEPS))) {
		return 0;
	} else if ((vec->x > hx) && 
		((vec->x < qr->xmax) || (fabs(vec->x - qr->xmax) < SMDZEROEPS)) &&
		(vec->y > qr->ymin) && 
		((vec->y < hy) || (fabs(vec->y - hy) < SMDZEROEPS))) {
		return 1;
	} else if ((vec->x > qr->xmin) && 
		((vec->x < hx) || (fabs(vec->x - hx) < SMDZEROEPS)) &&
		(vec->y > hy) && 
		((vec->y < qr->ymax) || (fabs(vec->y - qr->ymax) < SMDZEROEPS))) {
		return 2;
	} else {
//	} else if ((vec->x > hx) && 
//		((vec->x < qr->xmax) || (fabs(vec->x - qr->xmax) < SMDZEROEPS)) &&
//		(vec->y > hy) && 
//		((vec->y < qr->ymax) || (fabs(vec->y - qr->ymax) < SMDZEROEPS))) {
		return 3;
	}
}

void subdivide_qrange(QRange *qr, int i, QRange *qrnew)
{
	double hx, hy;
	
	hx = (qr->xmin + qr->xmax) / 2.0;
	hy = (qr->ymin + qr->ymax) / 2.0;
	
	if (i == 0) {
		qrnew->xmin = qr->xmin;
		qrnew->xmax = hx;
		qrnew->ymin = qr->ymin;
		qrnew->ymax = hy;
	} else if (i == 1) {
		qrnew->xmin = hx;
		qrnew->xmax = qr->xmax;
		qrnew->ymin = qr->ymin;
		qrnew->ymax = hy;
	} else if (i == 2) {
		qrnew->xmin = qr->xmin;
		qrnew->xmax = hx;
		qrnew->ymin = hy;
		qrnew->ymax = qr->ymax;
	} else if (i == 3) {
		qrnew->xmin = hx;
		qrnew->xmax = qr->xmax;
		qrnew->ymin = hy;
		qrnew->ymax = qr->ymax;
	}
}

/*********************************************************************
for ppd 
*********************************************************************/

QTree *init_qtree(Sppd *ppd)
{
	int    i;
	QTree  *head;
	int    level;
	double xsub, ysub;
	Spvt   *v;
	
	for (i = 0, v = ppd->spvt; v != (Spvt *) NULL; ++i, v = v->nxt) {
		if (i) {
			if (ppd->xmax < v->uvw.x) ppd->xmax = v->uvw.x;
			if (ppd->xmin > v->uvw.x) ppd->xmin = v->uvw.x;
			if (ppd->ymax < v->uvw.y) ppd->ymax = v->uvw.y;
			if (ppd->ymin > v->uvw.y) ppd->ymin = v->uvw.y;
		} else {
			ppd->xmax = v->uvw.x;
			ppd->xmin = v->uvw.x;
			ppd->ymax = v->uvw.y;
			ppd->ymin = v->uvw.y;
		}
	}
	
	level = 0;
	xsub  = 0.01 * (ppd->xmax - ppd->xmin);
	ysub  = 0.01 * (ppd->ymax - ppd->ymin);
	head  = create_qtreechild(NULL, level, ppd->qn++, 
		ppd->xmin - xsub,
		ppd->xmax + xsub + SMDZEROEPS,
		ppd->ymin - ysub,
		ppd->ymax + ysub + SMDZEROEPS);
	ppd->maxqtlevel = 4;
	return head;
}

/* Vertex */
void ppdvertex_to_ppdqtree(Sppd *ppd)
{
	Spvt *vt;
	
	for (vt = ppd->spvt; vt != (Spvt *) NULL; vt = vt->nxt) {
		decide_qvertex_child(ppd->qt, vt, ppd);
	}
}

void decide_qvertex_child(QTree *qt, Spvt *vt, Sppd *ppd)
{
	int     i;
	QRange  newqr;
	
	if (qt->level == ppd->maxqtlevel) {
		(void) insert_qtree_vertex(vt, qt);
		return;
	}
	
	for (i = 0; i < 4; ++i) {
		subdivide_qrange(&(qt->qr), i, &(newqr));
		if (vertex_square( &(vt->uvw), &(newqr))  == INSIDE) {
			if (qt->child[i] == (QTree *) NULL) {
				qt->child[i] = create_qtreechild_qr(qt, qt->level + 1, 
					ppd->qn++, &(newqr));
			}
			decide_qvertex_child(qt->child[i], vt, ppd);
		}
	}
}

/* Edge */

void ppdedge_to_ppdqtree(Sppd *ppd)
{
	for (Sped *ed = ppd->sped; ed != (Sped *) NULL; ed = ed->nxt) 
		decide_qedge_child(ppd->qt, ed, ppd);
}

void decide_qedge_child(QTree *qt, Sped *ed, Sppd *ppd)
{
	int    i, a;
	QEdge  *qe;
	QRange newqr;
	
	if (qt->level == ppd->maxqtlevel) {
		qe = insert_qtree_edge(ed, qt);
		return;
	}
	
	for (i = 0; i < 4; ++i) {
		subdivide_qrange(&(qt->qr), i, &(newqr));
		a = line_square_intersection( &(newqr), &(ed->sv->uvw), &(ed->ev->uvw) );
		if (a == INSIDE) {
			if (qt->child[i] == (QTree *) NULL) {
				qt->child[i] = create_qtreechild_qr(qt, qt->level + 1, 
					ppd->qn++, &(newqr));
			}
			decide_qedge_child(qt->child[i], ed, ppd);
			return;
		} else if (a == INTERSECTION) {
			/*       display("(insert0) ed = %d, qt = %d\n", ed->no, qt->level); */
			/*       display("(range) (x) %f %f (y) %f %f\n", */
			/*       qt->qr.xmin, qt->qr.xmax, qt->qr.ymin, qt->qr.ymax); */
			qe = insert_qtree_edge(ed, qt);
			return;
		}
	}
}

/*********************************************************************
for PGppd functions
*********************************************************************/

#define SUB 0.01

QTree *init_hgppdqtree( HGfc *hgfc )
{
	QTree  *head;
	int    level;
	
	level = 0;
	head  = create_qtreechild( NULL, level, hgfc->qn++, -(1.0+SUB), 1.0+SUB, -(1.0+SUB), 1.0+SUB );
	hgfc->maxqtlevel = 4;
	return head;
}

void hged_to_hgppdqtree( HGfc *hgfc )
{
	HGed *hged;
	
	for ( hged = hgfc->shged; hged != (HGed *) NULL; hged = hged->nxt ) {
		if ( hged->ed->sp_type == SP_EDGE_NORMAL ) {
			
			hged->ed->sv->uvw.x = hged->sv->uvw.x;
			hged->ed->sv->uvw.y = hged->sv->uvw.y;
			hged->ed->ev->uvw.x = hged->ev->uvw.x;
			hged->ed->ev->uvw.y = hged->ev->uvw.y;
			
			/*       display("hged uvw (sv) %g %g (ev) %g %g\n", */
			/* 	      hged->ed->sv->uvw.x,  hged->ed->sv->uvw.y, */
			/* 	      hged->ed->ev->uvw.x,  hged->ed->ev->uvw.y); */
			
			decide_hgqedge_child( hgfc->qt, hged->ed, hgfc );
		}
	}
}

void decide_hgqedge_child( QTree *qt, Sped *ed, HGfc *hgfc )
{
	int    i, a;
	QEdge  *qe;
	QRange newqr;
	
	if ( qt->level == hgfc->maxqtlevel ) {
		qe = insert_qtree_edge( ed, qt );
		return;
	}
	
	for (i = 0; i < 4; ++i) {
		subdivide_qrange( &(qt->qr), i, &(newqr) );
		a = line_square_intersection( &(newqr), &(ed->sv->uvw), &(ed->ev->uvw) );
		if (a == INSIDE) {
			if (qt->child[i] == (QTree *) NULL) {
				qt->child[i] = create_qtreechild_qr( qt, qt->level + 1, 
					hgfc->qn++, &(newqr) );
			}
			decide_hgqedge_child( qt->child[i], ed, hgfc );
			return;
		} else if (a == INTERSECTION) {
			/*       display("(insert0) ed = %d, qt = %d\n", ed->no, qt->level); */
			/*       display("(range) (x) %f %f (y) %f %f\n", */
			/*       qt->qr.xmin, qt->qr.xmax, qt->qr.ymin, qt->qr.ymax); */
			qe = insert_qtree_edge( ed, qt );
			return;
		}
	}
}

void free_hgppdqtree( HGfc *hgfc )
{
	free_hgppdqtree_child( hgfc->qt, hgfc );
	hgfc->qt = (QTree *) NULL;
}

void free_hgppdqtree_child( QTree *qtree, HGfc *hgfc )
{
	int  i;
	
	if (qtree == (QTree *) NULL) return;
	
	for (i = 0; i < 4; ++i) {
		if (qtree->child[i] != (QTree *) NULL) {
			free_hgppdqtree_child( qtree->child[i], hgfc );
		}
	}
	free_qedge( qtree );
	free_qface( qtree );
	free_qvertex( qtree );
	free( qtree );
	qtree = (QTree *) NULL;
	--(hgfc->qn);
}

/* Face */
void hgppdsurface_to_hgppdqtree( HGfc *hgfc )
{
	for ( HGsf *sf = hgfc->shgsf; sf != (HGsf *) NULL; sf = sf->nxt ) 
		decide_qface_child( hgfc->qt, sf, hgfc );
}

void decide_qface_child( QTree *qt, HGsf *sf, HGfc *hgfc )
{
	int    i, a;
	QFace  *qf;
	QRange newqr;
	
	if (qt->level == hgfc->maxqtlevel) {
		qf = insert_qtree_face( sf, qt );
		return;
	}
	
	for (i = 0; i < 4; ++i) {
		subdivide_qrange(&(qt->qr), i, &(newqr));
		a = hg_triangle_square_intersection( sf, &(newqr) );
		if (a  == INSIDE) {
			if (qt->child[i] == (QTree *) NULL) {
				qt->child[i] = create_qtreechild_qr(qt, qt->level + 1, 
					hgfc->qn++, &(newqr));
			}
			decide_qface_child( qt->child[i], sf, hgfc );
			return;
		} else if (a == INTERSECTION) {
			qf = insert_qtree_face( sf, qt );
			return;
		}
	}
}

/*
void printqface( QTree *qt )
{
int   i;
QFace *qf;
void  printqface( QTree * );

 display("(level) %d\n", qt->level);
 for (qf = qt->sqf; qf != (QFace *) NULL; qf = qf->nxt) {
 display("face id:\t%d\n", qf->sf->no );
 }
 
  for (i = 0; i < 4; ++i) {
  if (qt->child[i] != (QTree *) NULL) {
  printqface( qt->child[i] );
  }
  }
  }
*/
