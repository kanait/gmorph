/* Copyright (c) 1997-1998 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>
#include "smd.h"
#include "trisquare.h"
#include "veclib.h"

#define SMDZEROEPS2 1.0e-06

/* point square in-out check */

int vertex_square( Vec2d *v, QRange *qr )
{
	if ((v->x > qr->xmin) && (v->x < qr->xmax) &&
		(v->y > qr->ymin) && (v->y < qr->ymax))
		return INSIDE;
	if ((fabs(v->x - qr->xmin) < SMDZEROEPS) && (v->x < qr->xmax) &&
		(v->y > qr->ymin) && (v->y < qr->ymax))
		return INSIDE;
	if ((v->x > qr->xmin) && (fabs(v->x - qr->xmax) < SMDZEROEPS) &&
		(v->y > qr->ymin) && (v->y < qr->ymax))
		return INSIDE;
	if ((v->x > qr->xmin) && (v->x < qr->xmax) &&
		(fabs(v->y - qr->ymin) < SMDZEROEPS) && (v->y < qr->ymax))
		return INSIDE;
	if ((v->x > qr->xmin) && (v->x < qr->xmax) &&
		(v->y > qr->ymin) && (fabs(v->y - qr->ymax) < SMDZEROEPS))
		return INSIDE;
	return OUTSIDE;
}

/* Modified. 97/10/28 */

/*                    o (x2,y2)
|
TRUE     |     FALSE
|
o (x1,y1)
*/
BOOL isLeftSide( Vec2d *v1, Vec2d *v2, Vec2d *v )
{
	if ( ((v2->x - v1->x) * (v->y  - v1->y) -
		(v->x  - v1->x) * (v2->y - v1->y)) > 0.0 ) {
		return TRUE;
	} else return FALSE;
}

BOOL isLeftSidePivot( Vec2d *vi, Vec2d *vj, Vec2d *vk )
{
	double val1, val2, val3, val4;
	
	val1 = (vj->x - vi->x) * (vk->y  - vi->y) - (vk->x  - vi->x) * (vj->y - vi->y);
	if ( val1 != 0.0 ) {
		if ( val1 > 0.0 ) return TRUE; else return FALSE;
	}
//	display("taika! 退化! \n");
	val2 = vj->y - vk->y;
	if ( val2 != 0.0 ) {
		if ( val2 > 0.0 ) return TRUE; else return FALSE;
	}
	val3 = vk->y - vi->y;
	if ( val3 != 0.0 ) {
		if ( val3 > 0.0 ) return TRUE; else return FALSE;
	}
	val4 = vk->x - vj->x;
	if ( val4 != 0.0 ) {
		if ( val4 > 0.0 ) return TRUE; else return FALSE;
	}
	
	return FALSE;
}

void swap_sign( int *a, int *b )
{
	int tmp;
	tmp = *a; *a = *b; *b = tmp;
}

void swap_vec2d( Vec2d *vec1, Vec2d *vec2 )
{
	Vec2d tmp;
	
	tmp.x   = vec1->x; tmp.y   = vec1->y;
	vec1->x = vec2->x; vec1->y = vec2->y;
	vec2->x = tmp.x;   vec2->y = tmp.y;
	
}

BOOL isHGvtLeftSide( HGvt *vi, HGvt *vj, HGvt *vk )
{
	BOOL a;
	int cnt = 0, ni, nj, nk, swap = SMD_OFF;
	Vec2d uvwi, uvwj, uvwk;
	
	ni = vi->sign; nj = vj->sign; nk = vk->sign;
	uvwi.x = vi->uvw.x; uvwi.y = vi->uvw.y; 
	uvwj.x = vj->uvw.x; uvwj.y = vj->uvw.y; 
	uvwk.x = vk->uvw.x; uvwk.y = vk->uvw.y;
	
	if ( ni > nj ) {
		swap_sign( &ni, &nj );  swap_vec2d( &(uvwi), &(uvwj) );
		cnt++;
	}
	if ( ni > nk ) {
		swap_sign( &ni, &nk );  swap_vec2d( &(uvwi), &(uvwk) );
		cnt++;
	}
	if ( nj > nk ) {
		swap_sign( &nj, &nk );  swap_vec2d( &(uvwj), &(uvwk) );
		cnt++;
	}
	if ( !(cnt % 2) ) swap = SMD_OFF; else swap = SMD_ON;
	
	a = isLeftSidePivot( &(uvwi), &(uvwj), &(uvwk) );
	
	if ( a == TRUE ) {
		
		if ( swap ) return FALSE;
		else        return TRUE;
		
	} else {
		
		if ( swap ) return TRUE;
		else        return FALSE;
		
	}
}

double isLeftVal( Vec2d *v1, Vec2d *v2, Vec2d *v )
{
	return (v2->x - v1->x) * (v->y  - v1->y) -
		(v->x  - v1->x) * (v2->y - v1->y) ;
}

#define Bigger(x, y) ((x > y) ? x : y)
#define Smaller(x, y) ((x < y) ? x : y)
/*
* check the intersection of line segments
*/
BOOL isHGvtLineSegmentCrossing( HGvt *v1_s, HGvt *v1_e, HGvt *v2_s, HGvt *v2_e )
{
	BOOL s1, e1, s2, e2;
	
	s1 = isHGvtLeftSide( v2_s, v2_e, v1_s );
	e1 = isHGvtLeftSide( v2_s, v2_e, v1_e );
	/*   display("1: %d %d %g %g\n", s1, e1, */
	/* 	  isLeftVal( v2_s, v2_e, v1_s ), */
	/* 	  isLeftVal( v2_s, v2_e, v1_e ) */
	/* 	  ); */
	if ( s1 == e1 ) return FALSE;
	s2 = isHGvtLeftSide( v1_s, v1_e, v2_s );
	e2 = isHGvtLeftSide( v1_s, v1_e, v2_e );
	/*   display("2: %d %d\n", s2, e2 ); */
	if ( s2 == e2 ) return FALSE;
	
	return TRUE;
}

BOOL isLineSegmentCrossing( Vec2d *v1_s, Vec2d *v1_e, Vec2d *v2_s, Vec2d *v2_e )
{
	BOOL s1, e1, s2, e2;
	BOOL isLeftSide( Vec2d *, Vec2d *, Vec2d * );
	
	s1 = isLeftSide( v2_s, v2_e, v1_s );
	e1 = isLeftSide( v2_s, v2_e, v1_e );
	/*   display("1: %d %d %g %g\n", s1, e1, */
	/* 	  isLeftVal( v2_s, v2_e, v1_s ), */
	/* 	  isLeftVal( v2_s, v2_e, v1_e ) */
	/* 	  ); */
	if ( s1 == e1 ) return FALSE;
	s2 = isLeftSide( v1_s, v1_e, v2_s );
	e2 = isLeftSide( v1_s, v1_e, v2_e );
	/*   display("2: %d %d\n", s2, e2 ); */
	if ( s2 == e2 ) return FALSE;
	
	return TRUE;
}

void LineIntersectionPoint(
						   Vec2d *v1_s, Vec2d *v1_e,
						   Vec2d *v2_s, Vec2d *v2_e,
						   Vec2d *intsec 
						   )
{
	double den, a1, b1, c1, a2, b2, c2;
	
	a1 = v1_s->y - v1_e->y;
	b1 = v1_e->x - v1_s->x;
	c1 = v1_s->x * v1_e->y - v1_s->y * v1_e->x;
	a2 = v2_s->y - v2_e->y;
	b2 = v2_e->x - v2_s->x;
	c2 = v2_s->x * v2_e->y - v2_s->y * v2_e->x;
	
	den = a1 * b2 - b1 * a2;
	intsec->x = (c2 * b1 - c1 * b2 ) / den;
	intsec->y = (c1 * a2 - c2 * a1 ) / den;
	
}

int line_line( Vec2d *v1_s, Vec2d *v1_e, Vec2d *v2_s, Vec2d *v2_e )
{
	if ( FALSE == isLineSegmentCrossing( v1_s, v1_e, v2_s, v2_e ) ) {
		return OUTSIDE;
	}
	
	return INSIDE;
}

int line_line_param(Vec2d *v1_s, Vec2d *v1_e, Vec2d *v2_s, Vec2d *v2_e,
					double *t, double *s, unsigned short *online_flag)
{
	double a, b, c, d, x, y, den;
	
	if ( FALSE == isLineSegmentCrossing( v1_s, v1_e, v2_s, v2_e ) ) {
		return OUTSIDE;
	}
	
	*online_flag = 0;
	
	a = v1_e->x - v1_s->x;
	b = v1_e->y - v1_s->y;
	c = v2_s->x - v2_e->x;
	d = v2_s->y - v2_e->y;
	x = v2_s->x - v1_s->x;
	y = v2_s->y - v1_s->y;
	den = a * d - b * c;
	
	*t = (d * x - c * y) / den;
	*s = (-b * x + a * y) / den;
	
	return INSIDE;
}

BOOL isPointinHGsf( HGsf *sf, Vec2d *v )
{
	HGhe  *he;
	Vec2d *uvw0, *uvw1;
	
	he = sf->shghe;
	
	/*   display("\t(inhgsf) sf %d\n", sf->no ); */
	do {
		uvw0 = &(he->vt->uvw);
		uvw1 = &(he->nxt->vt->uvw);
		
		/*     display("\t(inhgsf) v1 %d v2 %d\n", he->vt->no, he->nxt->vt->no ); */
		if ( isLeftSide( uvw0, uvw1, v ) == FALSE ) return FALSE;
		
	} while ( (he = he->nxt) != sf->shghe );
	/*   display("\t(inhgsf) OK.\n"); */
	return TRUE;
}

BOOL isHGvtinHGsf( HGsf *sf, HGvt *v )
{
  HGhe  *he;
  Vec2d *uvw0, *uvw1;
	
  he = sf->shghe;
	
  /*   display("\t(inhgsf) sf %d\n", sf->no ); */
  do {
    uvw0 = &(he->vt->uvw);
    uvw1 = &(he->nxt->vt->uvw);
		
    /*     display("\t(inhgsf) v1 %d v2 %d\n", he->vt->no, he->nxt->vt->no ); */
    if ( isHGvtLeftSide( he->vt, he->nxt->vt, v ) == FALSE ) return FALSE;
		
  } while ( (he = he->nxt) != sf->shghe );
  /*   display("\t(inhgsf) OK.\n"); */
  return TRUE;
}

void VertexTriangleBarycentric( HGsf *sf, Vec2d *v, double *al, double *be, double *gm )
{
	Vec2d  uvw0, uvw1, uvw2;
	double a, b, c, d, x, y, den;
	
	uvw0.x = sf->shghe->vt->uvw.x;
	uvw0.y = sf->shghe->vt->uvw.y;
	uvw1.x = sf->shghe->nxt->vt->uvw.x;
	uvw1.y = sf->shghe->nxt->vt->uvw.y;
	uvw2.x = sf->shghe->nxt->nxt->vt->uvw.x;
	uvw2.y = sf->shghe->nxt->nxt->vt->uvw.y;
	
	a = uvw1.x - uvw0.x;
	b = uvw1.y - uvw0.y;
	c = uvw2.x - uvw0.x;
	d = uvw2.y - uvw0.y;
	x = v->x  - uvw0.x;
	y = v->y  - uvw0.y;
	
	den = a * d - b * c;
	
	*be = (d * x - c * y)  / den;
	*gm = (-b * x + a * y) / den;
	*al = 1.0 - *be - *gm;
	
}

int hg_vertex_triangle_param( HGsf *sf, Vec2d *v, double *al, double *be, double *gm )
{
	Vec2d  uvw0, uvw1, uvw2;
	double a, b, c, d, x, y, den;
	
	uvw0.x = sf->shghe->vt->uvw.x;
	uvw0.y = sf->shghe->vt->uvw.y;
	uvw1.x = sf->shghe->nxt->vt->uvw.x;
	uvw1.y = sf->shghe->nxt->vt->uvw.y;
	uvw2.x = sf->shghe->nxt->nxt->vt->uvw.x;
	uvw2.y = sf->shghe->nxt->nxt->vt->uvw.y;
	
	a = uvw1.x - uvw0.x;
	b = uvw1.y - uvw0.y;
	c = uvw2.x - uvw0.x;
	d = uvw2.y - uvw0.y;
	x = v->x  - uvw0.x;
	y = v->y  - uvw0.y;
	
	den = a * d - b * c;
	
	if (fabs(den) < SMDZEROEPS2) return OUTSIDE;
	
	*be = (d * x - c * y)  / den;
	*gm = (-b * x + a * y) / den;
	*al = 1.0 - *be - *gm;
	
	/* on vertex */
	if ((fabs(*al) < SMDZEROEPS2) && (fabs(*be) < SMDZEROEPS2) &&
		(fabs(*gm - 1.0) < SMDZEROEPS2)) {
		return INSIDE;
	}
	if ((fabs(*al) < SMDZEROEPS2) && (fabs(*be - 1.0) < SMDZEROEPS2) &&
		(fabs(*gm) < SMDZEROEPS2)) {
		return INSIDE;
	}
	if ((fabs(*al - 1.0) < SMDZEROEPS2) && (fabs(*be) < SMDZEROEPS2) &&
		(fabs(*gm) < SMDZEROEPS2)) {
		return INSIDE;
	}
	/* on edge */
	if ((fabs(*al) < SMDZEROEPS2) || (fabs(*al - 1.0) < SMDZEROEPS2)) {
		if ((*be > SMDZEROEPS2) && (*be < 1.0 - SMDZEROEPS2) &&
			(*gm > SMDZEROEPS2) && (*gm < 1.0 - SMDZEROEPS2))
			return INSIDE;
	}
	if ((fabs(*be) < SMDZEROEPS2) || (fabs(*be - 1.0) < SMDZEROEPS2)) {
		if ((*al > SMDZEROEPS2) && (*al < 1.0 - SMDZEROEPS2) &&
			(*gm > SMDZEROEPS2) && (*gm < 1.0 - SMDZEROEPS2))
			return INSIDE;
	}
	if ((fabs(*gm) < SMDZEROEPS2) || (fabs(*gm - 1.0) < SMDZEROEPS2)) {
		if ((*be > SMDZEROEPS2) && (*be < 1.0 - SMDZEROEPS2) &&
			(*al > SMDZEROEPS2) && (*al < 1.0 - SMDZEROEPS2))
			return INSIDE;
	}
	/* on face */
	if ((*al > SMDZEROEPS2) && (*al < 1.0 - SMDZEROEPS2) &&
		(*be > SMDZEROEPS2) && (*be < 1.0 - SMDZEROEPS2) &&
		(*gm > SMDZEROEPS2) && (*gm < 1.0 - SMDZEROEPS2))
		return INSIDE;
	
	return OUTSIDE;
}

double point_line_distance_param( Vec2d *v, Vec2d *v0, Vec2d *v1, double *t )
{
	double len;
	Vec2d  sub0, sub1, sub, sub0b;
	
	len = V2DistanceBetween2Points( v0, v1 );
	V2Sub( v0, v, &(sub0) );
	V2Sub( v1, v, &(sub1) );
	
	V2Sub( v, v0, &(sub0b) );
	V2Sub( v1, v0, &(sub) );
	
	*t = V2Dot( &(sub), &(sub0b) ) / V2Dot( &(sub), &(sub) );
	
	return fabs( (sub0.x * sub1.y) - (sub1.x * sub0.y) ) / len;
}

double point_line_distance( Vec2d *v, Vec2d *v0, Vec2d *v1 )
{
	double len;
	Vec2d  sub0, sub1;
	
	len = V2DistanceBetween2Points( v0, v1 );
	V2Sub(v0, v, &(sub0));
	V2Sub(v1, v, &(sub1));
	
	return fabs( sub0.x * sub1.y - sub1.x * sub0.y ) / len;
}

/* Triangular-Square Intersection Test */

int hg_triangle_square_intersection( HGsf *sf, QRange *qr )
{
	int   a, b, c;
	Vec2d uvw0, uvw1, uvw2;
	
	/* three points of face is inside a square ? */
	uvw0.x = sf->shghe->vt->uvw.x;
	uvw0.y = sf->shghe->vt->uvw.y;
	uvw1.x = sf->shghe->nxt->vt->uvw.x;
	uvw1.y = sf->shghe->nxt->vt->uvw.y;
	uvw2.x = sf->shghe->nxt->nxt->vt->uvw.x;
	uvw2.y = sf->shghe->nxt->nxt->vt->uvw.y;
	
	/*   display("%g %g %g %g %g %g\n", uvw0.x, uvw0.y, uvw1.x, uvw1.y, uvw2.x, uvw2.y); */
	a = vertex_square( &(uvw0), qr );
	b = vertex_square( &(uvw1), qr );
	c = vertex_square( &(uvw2), qr );
	if ((a == INSIDE) && (b == INSIDE) && (c == INSIDE)) {
		return INSIDE;
	}
	
	/* square is inside a triangle ?*/
	
	a = line_square_intersection( qr, &(uvw0), &(uvw1) );
	b = line_square_intersection( qr, &(uvw1), &(uvw2) );
	c = line_square_intersection( qr, &(uvw2), &(uvw0) );
	
	if ((a != OUTSIDE) || (b != OUTSIDE) || (c != OUTSIDE)) {
		return INTERSECTION;
	}
	
	return OUTSIDE;
	
}

/* Line-Square Intersection Test */

int line_square_intersection(QRange *qr, Vec2d *svec, Vec2d *evec)
{
	int    icnt, a, b, c;
	Vec2d  q1, q2;
	
	b = vertex_square(svec, qr);
	c = vertex_square(evec, qr);
	if ((b == INSIDE) && (c == INSIDE)) return INSIDE;
	
	icnt = 0;
	
	if ((svec->x - qr->xmin) * (evec->x - qr->xmin) < 0.0) {
		q1.x = qr->xmin;
		q1.y = qr->ymin;
		q2.x = qr->xmin;
		q2.y = qr->ymax;
		a = line_line(svec, evec, &(q1), &(q2));
		if (a != OUTSIDE) ++icnt;
	}
	if ((svec->x - qr->xmax) * (evec->x - qr->xmax) < 0.0) {
		q1.x = qr->xmax;
		q1.y = qr->ymin;
		q2.x = qr->xmax;
		q2.y = qr->ymax;
		a = line_line(svec, evec, &(q1), &(q2));
		if (a != OUTSIDE) ++icnt;
		
	}
	if ((svec->y - qr->ymin) * (evec->y - qr->ymin) < 0.0) {
		q1.x = qr->xmin;
		q1.y = qr->ymin;
		q2.x = qr->xmax;
		q2.y = qr->ymin;
		a = line_line(svec, evec, &(q1), &(q2));
		if (a != OUTSIDE) ++icnt;
	}
	if ((svec->y - qr->ymax) * (evec->y - qr->ymax) < 0.0) {
		q1.x = qr->xmin;
		q1.y = qr->ymax;
		q2.x = qr->xmax;
		q2.y = qr->ymax;
		a = line_line(svec, evec, &(q1), &(q2));
		if (a != OUTSIDE) ++icnt;
	}
	
	if (icnt == 0) return OUTSIDE;
	else if (icnt == 1) {
		if (b == INSIDE) return INTERSECTION;
		if (c == INSIDE) return INTERSECTION;
		return OUTSIDE;
	} else 
	return INTERSECTION;
}

int vertex_line(Vec2d *v, Vec2d *ev1, Vec2d *ev2)
{
	double t;
	double point_line_distance(Vec2d *, Vec2d *, Vec2d *);
	
	if (point_line_distance(v, ev1, ev2) < SMDZEROEPS) {
		t = (v->x - ev1->x) / (ev2->x - ev1->x);
		if ( ( t > 0.0 ) && ( t < 1.0) ) return INSIDE;
	}
	return OUTSIDE;
}
