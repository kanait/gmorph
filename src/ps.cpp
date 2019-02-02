//
// ps.cpp
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

/* function for Adobe Postsrcipt file */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "ps.h"

#define WINDOWCENTERX 250.0
#define WINDOWCENTERY 400.0
#define PARA_WINDOWCENTERX 100
#define PARA_WINDOWCENTERY 450

#define RADIUS 100.0

/* open Postscript file */

FILE *open_ps( char *fname )
{
    FILE *fp;
	
    if ((fp = fopen(fname, "w")) == NULL) {
		return (FILE *) NULL;
    }
    fprintf(fp, "%%!\n");
    fprintf(fp, "/l {moveto lineto [] 0 setdash linecolor setrgbcolor stroke} def\n");
    fprintf(fp, "/sprint {moveto /NewCenturySchlbk-Italic findfont 3 scalefont setfont show} def\n");
    fprintf(fp, "/sprintbold {moveto /NewCenturySchlbk-BoldItalic findfont 25 scalefont setfont show} def\n");
    fprintf(fp, "/sprint2 {moveto /Courier findfont 15 scalefont setfont show} def\n");
    fprintf(fp, "/printZip {0 0 moveto /Helvetica-BoldOblique findfont 30 scalefont setfont show} def\n");
    fprintf(fp, "/d {moveto lineto [4 2] 0 setdash linecolor setrgbcolor stroke} def\n");
    fprintf(fp, "/d2 {moveto lineto [2 2] 0 setdash linecolor setrgbcolor stroke} def\n");
    fprintf(fp, "%%/star {moveto lineto [] 0 setdash starcolor setrgbcolor stroke} def\n");
    fprintf(fp, "/star {\n");
    fprintf(fp, " /factor 0.5 def\n");
    fprintf(fp, " /y1 exch def /x1 exch def /y0 exch def /x0 exch def\n");
    fprintf(fp, " /ym y0 y1 add 2 div def /xm x0 x1 add 2 div def\n");
    fprintf(fp, " /yd y0 y1 sub 2 div factor mul def\n");
    fprintf(fp, " /xd x0 x1 sub 2 div factor mul def\n");
    fprintf(fp, " xm xd add ym yd add moveto\n");
    fprintf(fp, " xm xd sub ym yd sub lineto\n");
    fprintf(fp, "[] 0 setdash starcolor setrgbcolor stroke\n");
    fprintf(fp, "} def\n");
	
    fprintf(fp, "/linecolor {0 0 0} def\n");
    fprintf(fp, "/markcolor {0 0 0} def\n");
    fprintf(fp, "/starcolor {0 0 0} def\n");
    fprintf(fp, "/offset 3 def\n");
    fprintf(fp, "/f {2 copy 4 copy\n");
    fprintf(fp, "  offset sub exch offset sub exch moveto\n");
    fprintf(fp, "  offset add exch offset sub exch lineto\n");
    fprintf(fp, "  offset add exch offset add exch lineto\n");
    fprintf(fp, "  offset sub exch offset add exch lineto\n");
    fprintf(fp, "  closepath\n");
    /*    fprintf(fp, "  0 setgray\n"); */
    fprintf(fp, "  markcolor setrgbcolor\n");
    fprintf(fp, "  fill\n");
    fprintf(fp, "} def\n");
    fprintf(fp, "newpath\n");
    fprintf(fp, "%f setlinewidth\n", 0.001);
    fprintf(fp, "\n");
	
    return fp;
}

/* close post-script file */
void close_ps(FILE * fp)
{
    fprintf(fp, "\n");
    fprintf(fp, "showpage");
    fclose(fp);
}

/* transformation from 2D point to PS point */
void pstran(Vec2d * p1, Vec2d * p2)
{
/*p2->x = WINDOWCENTERX + p1->x * swin->psws;
	p2->y = WINDOWCENTERY + p1->y * swin->psws; */
}

/* transformation from 2D point to PS point in parameter space */
void pstran_p(Vec2d * p1, Vec2d * p2)
{
/*p2->x = PARA_WINDOWCENTERX + p1->x * swin->pswsp;
	p2->y = PARA_WINDOWCENTERY + p1->y * swin->pswsp; */
}

/* set line-width */
void pslinewidth(FILE * fp, double width)
{
    fprintf(fp, "%.4f setlinewidth\n", width);
}

/* eps offset-width */
void psoffsetwidth(FILE * fp, double d)
{
    fprintf(fp, "/offset %.4f def\n", d);
}

/* eps line color */

void pscolor(FILE * fp, double r, double g, double b)
{
	fprintf(fp, "%.3f %.3f %.3f setrgbcolor\n", r, g, b);
}

/* eps mark color */

/*void 
psmarkcolor (ChrP color)
{
double rgb[3];

 psrgbcolor(color, rgb);
 fprintf(fp, "/markcolor {%.4f %.4f %.4f} def\n", 
 rgb[0], rgb[1], rgb[2]);
   } */

/* eps star color */

/*void 
psstarcolor (ChrP color)
{
double rgb[3];

 psrgbcolor(color, rgb);
 fprintf(fp, "/starcolor {%.4f %.4f %.4f} def\n", 
 rgb[0], rgb[1], rgb[2]);
   } */

/********************************* 2D *********************************/

/* print line */
void psline(FILE * fp, Vec2d * p1, Vec2d * p2)
{
    fprintf(fp, "%f %f %f %f l\n", p1->x, p1->y, p2->x, p2->y);
}

void psline_4values(FILE * fp, double x1, double y1, double x2, double y2)
{
    fprintf(fp, "%f %f %f %f l\n", x1, y1, x2, y2);
}

/* print dashline */
void psdashline(FILE * fp, Vec2d * p1, Vec2d * p2)
{
    Vec2d c1, c2;
	
    pstran(p1, &c1);
    pstran(p2, &c2);
    fprintf(fp, "%.6f %.6f %.6f %.6f d\n", c1.x, c1.y, c2.x, c2.y);
}

/* print dashline 2 */
void psdashline2(FILE * fp, Vec2d * p1, Vec2d * p2)
{
    Vec2d c1, c2;
	
    pstran(p1, &c1);
    pstran(p2, &c2);
    fprintf(fp, "%.6f %.6f %.6f %.6f d2\n", c1.x, c1.y, c2.x, c2.y);
}

/* print star */

void psstar(FILE * fp, Vec2d * p)
{
    Vec2d c;
    Vec2d c1, c2;
	
    pstran(p, &c);
    c1.x = c.x - 5.0;
    c2.x = c.x + 5.0;
    c1.y = c.y - 5.0;
    c2.y = c.y + 5.0;
    fprintf(fp, "%.6f %.6f %.6f %.6f star\n", c1.x, c1.y, c2.x, c2.y);
    c1.x = c.x - 5.0;
    c2.x = c.x + 5.0;
    c1.y = c.y + 5.0;
    c2.y = c.y - 5.0;
    fprintf(fp, "%.6f %.6f %.6f %.6f star\n", c1.x, c1.y, c2.x, c2.y);
}

/* print rectangle */

void psrectangle( FILE * fp, Vec2d * p, double len )
{
    Vec2d c1, c2;
	
    c1.x = p->x - len;
    c2.x = p->x - len;
    c1.y = p->y - len;
    c2.y = p->y + len;
    fprintf(fp, "%.6f %.6f %.6f %.6f l\n", c1.x, c1.y, c2.x, c2.y);
    c1.x = p->x - len;
    c2.x = p->x + len;
    c1.y = p->y - len;
    c2.y = p->y - len;
    fprintf(fp, "%.6f %.6f %.6f %.6f l\n", c1.x, c1.y, c2.x, c2.y);
    c1.x = p->x - len;
    c2.x = p->x + len;
    c1.y = p->y + len;
    c2.y = p->y + len;
    fprintf(fp, "%.6f %.6f %.6f %.6f l\n", c1.x, c1.y, c2.x, c2.y);
    c1.x = p->x + len;
    c2.x = p->x + len;
    c1.y = p->y - len;
    c2.y = p->y + len;
    fprintf(fp, "%.6f %.6f %.6f %.6f l\n", c1.x, c1.y, c2.x, c2.y);
}

void psfillrectangle(FILE * fp, Vec2d * p)
{
    Vec2d c;
	
    pstran(p, &c);
    fprintf(fp, "%.6f %.6f f\n", c.x, c.y);
}

/* print star with adaptive sacale */
void psstar_d(FILE * fp, Vec2d * p, double d)
{
    Vec2d c;
    Vec2d c1, c2;
	
    pstran(p, &c);
    c1.x = c.x - 5.0 * d;
    c2.x = c.x + 5.0 * d;
    c1.y = c.y - 5.0 * d;
    c2.y = c.y + 5.0 * d;
    fprintf(fp, "%.6f %.6f %.6f %.6f star\n", c1.x, c1.y, c2.x, c2.y);
    c1.x = c.x - 5.0 * d;
    c2.x = c.x + 5.0 * d;
    c1.y = c.y + 5.0 * d;
    c2.y = c.y - 5.0 * d;
    fprintf(fp, "%.6f %.6f %.6f %.6f star\n", c1.x, c1.y, c2.x, c2.y);
}

/* print mark */
void psmark(FILE * fp, Vec2d * p)
{
    Vec2d c;
	
    pstran(p, &c);
    fprintf(fp, "%.6f %.6f f\n", c.x, c.y);
}

/* print text */
void pstext(FILE * fp, Vec2d * p, char *text)
{
    fprintf(fp, "(%s) %.6f %.6f sprint\n", text, p->x, p->y);
}

/* print text */
void
pstextbold(FILE * fp, Vec2d * p, char *text)
{
    Vec2d c;
	
    pstran(p, &c);
    c.x += 2.0;
    c.y += 2.0;
    fprintf(fp, "(%s) %.6f %.6f sprintbold\n", text, c.x, c.y);
}

void psprintzip(FILE * fp, Vec2d * p, char *text)
{
    Vec2d c;
	
    pstran(p, &c);
    c.x += 2.0;
    c.y += 2.0;
    fprintf(fp, "%.0f %.0f translate\n", c.x, c.y);
    fprintf(fp, ".95 -.05 0\n");
    fprintf(fp, "{setgray (%s) printZip -0.2 .2 translate} for\n",
		text);
    fprintf(fp, "gsave 1 setgray printZip grestore\n");
    fprintf(fp, "\n");
	
}

/********************* in parameter space ************************/
/* print line in parameter space */
void psline_p(FILE * fp, Vec2d * p1, Vec2d * p2)
{
    Vec2d c1, c2;
	
    pstran_p(p1, &c1);
    pstran_p(p2, &c2);
    fprintf(fp, "%.6f %.6f %.6f %.6f l\n", c1.x, c1.y, c2.x, c2.y);
}

/* print dashline in parameter space */
void psdashline_p(FILE * fp, Vec2d * p1, Vec2d * p2)
{
    Vec2d c1, c2;
	
    pstran_p(p1, &c1);
    pstran_p(p2, &c2);
    fprintf(fp, "%.6f %.6f %.6f %.6f d\n", c1.x, c1.y, c2.x, c2.y);
}

/* print dashline 2 in parameter space */
void psdashline2_p(FILE * fp, Vec2d * p1, Vec2d * p2)
{
    Vec2d c1, c2;
	
    pstran_p(p1, &c1);
    pstran_p(p2, &c2);
    fprintf(fp, "%.6f %.6f %.6f %.6f d2\n",
		c1.x, c1.y, c2.x, c2.y);
}

/* print star in parameter space */
void psstar_p(FILE * fp, Vec2d * p)
{
    Vec2d c1, c2;
	
    c1.x = p->x - 0.01;
    c2.x = p->x + 0.01;
    c1.y = p->y - 0.01;
    c2.y = p->y + 0.01;
    pstran_p(&c1, &c1);
    pstran_p(&c2, &c2);
    fprintf(fp, "%.6f %.6f %.6f %.6f star\n", c1.x, c1.y, c2.x, c2.y);
    c1.x = p->x - 0.01;
    c2.x = p->x + 0.01;
    c1.y = p->y + 0.01;
    c2.y = p->y - 0.01;
    pstran_p(&c1, &c1);
    pstran_p(&c2, &c2);
    fprintf(fp, "%.6f %.6f %.6f %.6f star\n", c1.x, c1.y, c2.x, c2.y);
}

/* print star with adaptive sacale in parameter space */
void psstar_d_p(FILE * fp, Vec2d * p, double d)
{
    Vec2d c;
    Vec2d c1, c2;
	
    c1.x = p->x - 0.01 * d * 1.0;
    c2.x = p->x + 0.01 * d * 1.0;
    c1.y = p->y - 0.01 * d * 1.0;
    c2.y = p->y + 0.01 * d * 1.0;
    pstran_p(&c1, &c1);
    pstran_p(&c2, &c2);
    pstran_p(p, &c);
    fprintf(fp, "%.6f %.6f %.6f %.6f star\n", c1.x, c1.y, c2.x, c2.y);
    c1.x = p->x - 0.01 * d * 1.0;
    c2.x = p->x + 0.01 * d * 1.0;
    c1.y = p->y + 0.01 * d * 1.0;
    c2.y = p->y - 0.01 * d * 1.0;
    pstran_p(&c1, &c1);
    pstran_p(&c2, &c2);
    fprintf(fp, "%.6f %.6f %.6f %.6f star\n", c1.x, c1.y, c2.x, c2.y);
}

/* print mark in parameter space */
void psmarp(FILE * fp, Vec2d * p)
{
    Vec2d c;
	
    pstran_p(p, &c);
    fprintf(fp, "%.6f %.6f f\n", c.x, c.y);
}

/* print text in parameter space */
void pstext_p(FILE * fp, Vec2d * p, char *text)
{
    Vec2d c;
	
    pstran_p(p, &c);
    c.x += 2.0;
    c.y += 2.0;
    fprintf(fp, "(%s) %.6f %.6f sprint\n", text, c.x, c.y);
}

void hppd_harmonicmap_to_ps( HPpd *hppd )
{
	HFace *hfc;
	HGfc  *hgfc;
	char str[BUFSIZ];
	
	for ( hfc = hppd->shfc; hfc != (HFace *) NULL; hfc = hfc->nxt ) {
		hgfc = hfc->hgfc1;
		sprintf( str, "ps/ppd%dhrm%d.ps", 1, hfc->no );
		hgfc_harmonicmap_to_ps( str, hgfc );
		hgfc = hfc->hgfc2;
		sprintf( str, "ps/ppd%dhrm%d.ps", 2, hfc->no );
		hgfc_harmonicmap_to_ps( str, hgfc );
	}
}

void mhgfc_harmonicmap_to_ps( HPpd *hppd )
{
	HFace *hfc;
	HGfc  *hgfc;
	char str[BUFSIZ];
	void hgfc_harmonicmap_to_ps( char *, HGfc * );
	
	for ( hfc = hppd->shfc; hfc != (HFace *) NULL; hfc = hfc->nxt ) {
		hgfc = hfc->mhgfc;
		sprintf( str, "gppdhrm%d.ps", hfc->no );
		hgfc_harmonicmap_to_ps( str, hgfc );
	}
}

void hgfc_harmonicmap_to_ps( char *file, HGfc *hgfc )
{
	FILE *fp;
	Vec2d uvw1, uvw2;
	HGed *hged;
	
	if ((fp = open_ps( file )) == (FILE *) NULL ) return;
	
	pslinewidth( fp, 0.01 );
	for ( hged = hgfc->shged; hged != (HGed *) NULL; hged = hged->nxt ) {
		uvw1.x = WINDOWCENTERX + RADIUS * hged->sv->uvw.x;
		uvw1.y = WINDOWCENTERY + RADIUS * hged->sv->uvw.y;
		uvw2.x = WINDOWCENTERX + RADIUS * hged->ev->uvw.x;
		uvw2.y = WINDOWCENTERY + RADIUS * hged->ev->uvw.y;
		psline( fp, &(uvw1), &(uvw2) );
	}
	close_ps(fp);
}


void tmp_hgfc_harmonicmap_to_ps( char *file, HGfc *hgfc1, HGfc *hgfc2, HGfc *mhgfc )
{
	FILE *fp;
	Vec2d uvw1, uvw2, v;
	HGed *hged;
	HGvt *hgvt;
	char vname[BUFSIZ];
	
	if ((fp = open_ps( file )) == (FILE *) NULL ) return;
	
	for ( hgvt = mhgfc->shgvt; hgvt != (HGvt *) NULL; hgvt = hgvt->nxt ) {
		v.x = WINDOWCENTERX + RADIUS * hgvt->uvw.x;
		v.y = WINDOWCENTERY + RADIUS * hgvt->uvw.y;
		switch( hgvt->sp_type ) {
		case SP_VERTEX_NORMAL:
			psrectangle( fp, &v, 1.0 );
			break;
		case SP_VERTEX_BOUNDARY:
			psrectangle( fp, &v, 1.0 );
			break;
		case SP_VERTEX_HVERTEX:
			psrectangle( fp, &v, 5.0 );
			break;
		}
		sprintf( vname, "V%d_%d", hgvt->from, hgvt->no );
		pstext( fp, &v, (char *) vname );
	}
	
	pslinewidth( fp, 0.01 );
	for ( hged = hgfc1->shged; hged != (HGed *) NULL; hged = hged->nxt ) {
		uvw1.x = WINDOWCENTERX + RADIUS * hged->sv->uvw.x;
		uvw1.y = WINDOWCENTERY + RADIUS * hged->sv->uvw.y;
		uvw2.x = WINDOWCENTERX + RADIUS * hged->ev->uvw.x;
		uvw2.y = WINDOWCENTERY + RADIUS * hged->ev->uvw.y;
		psline( fp, &(uvw1), &(uvw2) );
	}
	
	for ( hged = hgfc2->shged; hged != (HGed *) NULL; hged = hged->nxt ) {
		uvw1.x = WINDOWCENTERX + RADIUS * hged->sv->uvw.x;
		uvw1.y = WINDOWCENTERY + RADIUS * hged->sv->uvw.y;
		uvw2.x = WINDOWCENTERX + RADIUS * hged->ev->uvw.x;
		uvw2.y = WINDOWCENTERY + RADIUS * hged->ev->uvw.y;
		pslinewidth( fp, 0.01 );
		psline(fp, &(uvw1), &(uvw2));
		
		if ( hged->no == 76 ) {
			sprintf( vname, "e2_%d", hged->no );
			v.x = (uvw1.x + uvw2.x) / 2.0;
			v.y = (uvw1.y + uvw2.y) / 2.0;
			pstext( fp, &v, (char *) vname );
			
			sprintf( vname, "sv_%d", hged->sv->no );
			pstext( fp, &(uvw1), (char *) vname );
			sprintf( vname, "ev_%d", hged->ev->no );
			pstext( fp, &(uvw2), (char *) vname );
		}
	}
	close_ps(fp);
}


void harmonicmap_to_ps(char *file, Sppd * ppd)
{
	FILE *fp;
	FILE *open_ps( char * );
	
	if ((fp = open_ps(file)) == (FILE *) NULL)  return;
	
	psharmonicppdedge(fp, ppd);
	
	close_ps(fp);
}

void psharmonicppdedge(FILE * fp, Sppd *ppd)
{
    Sped *ed;
    Vec2d uvw1, uvw2;
	
	pslinewidth( fp, 0.01 );
    for (ed = ppd->sped; ed != (Sped *) NULL; ed = ed->nxt) {
		uvw1.x = WINDOWCENTERX + RADIUS * ed->sv->uvw.x;
		uvw1.y = WINDOWCENTERY + RADIUS * ed->sv->uvw.y;
		uvw2.x = WINDOWCENTERX + RADIUS * ed->ev->uvw.x;
		uvw2.y = WINDOWCENTERY + RADIUS * ed->ev->uvw.y;
		psline(fp, &(uvw1), &(uvw2));
    }
}

/* end of file */
