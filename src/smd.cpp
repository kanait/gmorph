//
// smd.cpp
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

#include "smd.h"
#include "ppd.h"

#ifndef _COLOR_H
#include "color.h"
#endif

// screen size per a window
#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 400
#define WOFFSET 17
#define HOFFSET 127

Swin *create_swin( void )
{
  Swin *swin;
  void  display3d_initialize( Disp3D * );
  void  screenatr_initialize( ScreenAtr *, int, int );
  Material *material_initialize( void );

  swin = (Swin *) malloc( sizeof(Swin) );

  swin->width  = SCREEN_WIDTH * 2 + WOFFSET;
  swin->height = SCREEN_HEIGHT + HOFFSET;

  display3d_initialize( &(swin->dis3d) );

  // left window (src)
  screenatr_initialize( &(swin->screenatr[SCREEN_SRC]), 
						SCREEN_WIDTH, SCREEN_HEIGHT );
  swin->screenatr[SCREEN_SRC].no  = SCREEN_SRC;

  // right window (dist)
  screenatr_initialize( &(swin->screenatr[SCREEN_DIST]), 
						SCREEN_WIDTH, SCREEN_HEIGHT );
  swin->screenatr[SCREEN_DIST].no = SCREEN_DIST;

  /* tile display */
  swin->tileno   = 0;

  /* material initialize */

  swin->material = material_initialize();

  // select type initialize 
  swin->select_type = SEL_CLEAR;
  swin->edit_type   = EDIT_NONE;
  
  // morph ppd 
  swin->morph_ppd = (Sppd *) NULL;

  // harmonic ppd 
  swin->hppd = (HPpd *) NULL;

  // divide number
  swin->mdiv = 50;

  // save harmonic map to ps 
  swin->savehmtops = SMD_OFF;

  return swin;
}

void display3d_initialize( Disp3D *disp )
{
  disp->vertex  = SMD_OFF;
  disp->wire    = SMD_OFF;
  disp->shading = SMD_ON;
  disp->cpoint  = SMD_OFF;
  disp->cmesh   = SMD_OFF;
  disp->loop    = SMD_OFF;
  disp->group   = SMD_OFF;
  disp->spath   = SMD_OFF;
  disp->hmap    = SMD_OFF;
  disp->coaxis  = SMD_OFF;
  disp->enhanced = SMD_OFF;
  disp->smooth  = SMD_OFF;
//  disp->gppd	= SMD_OFF;
  disp->interp	= SMD_OFF;
}

void screenatr_initialize( ScreenAtr *screen, int width, int height )
{
  void set_default_view(ScreenAtr *);
  
  screen->width  = width;
  screen->height = height;

  screen->xcenter = (double) screen->width  / 2.0;
  screen->ycenter = (double) screen->height / 2.0;
  
  /* resize or not */
  screen->resize = SMD_OFF;

  /* zoom parameter */
  screen->zoom_active = SMD_OFF;
  screen->zoom = 1.0;

  /* rotate parameter */
  screen->rotate_type   = ROTATE_XY;
  screen->rotate_active = SMD_OFF;
  screen->rotate_x = 0.0;
  screen->rotate_y = 0.0;
  screen->rotate_z = 0.0;

  /* background color */
/*   screen->bgrgb[0] = 0.0; */
/*   screen->bgrgb[1] = 0.0; */
/*   screen->bgrgb[2] = 0.0; */
/*   screen->bgrgb[0] = 0.0; */
/*   screen->bgrgb[1] = 0.0; */
/*   screen->bgrgb[2] = 0.5; */
/*   screen->bgrgb[0] = blackvec[0]; */
/*   screen->bgrgb[1] = blackvec[1]; */
/*   screen->bgrgb[2] = blackvec[2]; */
//  screen->bgrgb[0] = (float) whitevec[0]; 
//  screen->bgrgb[1] = (float) whitevec[1]; 
//  screen->bgrgb[2] = (float) whitevec[2]; 
  screen->bgrgb[0] = (float) bisquevec[0];
  screen->bgrgb[1] = (float) bisquevec[1];
  screen->bgrgb[2] = (float) bisquevec[2];

  /* set view initialize */

  set_default_view( screen );
  
  /* for select area */
  screen->areaflag  = SMD_OFF;
  screen->areaorg.x = 0.0;
  screen->areaorg.y = 0.0;
  screen->areaatv.x = 0.0;
  screen->areaatv.y = 0.0;

  /* select list */
  screen->sellist_flag = SMD_OFF;
  screen->n_sellist    = 0;
  screen->sel_first = screen->sel_last = (SelList *) NULL;

  /* for current_ppd */
  screen->current_ppd = (Sppd *) NULL;
  screen->view_ppd = (Sppd *) NULL;

  /* for shortest-path */
  screen->sg  = (SGraph *) NULL;
  screen->nsg = (SGraph *) NULL;
  screen->lp  = (SGlp *) NULL;

  screen->rad_sph = 0.015;
  screen->rad_cyl = 0.008;

}

Material *material_initialize( void )
{
  Material *matl;

  matl = (Material *) malloc(sizeof(Material));

  matl->ambient[0] = 0.2f;
  matl->ambient[1] = 0.2f;
  matl->ambient[2] = 0.2f;
  matl->ambient[3] = 1.0f;
  matl->diffuse[0] = 0.8f;
  matl->diffuse[1] = 0.8f;
  matl->diffuse[2] = 0.8f;
  matl->diffuse[3] = 1.0f;
  matl->emission[0] = 0.0f;
  matl->emission[1] = 0.0f;
  matl->emission[2] = 0.0f;
  matl->emission[3] = 1.0f;
  matl->specular[0] = 0.0f;
  matl->specular[1] = 0.0f;
  matl->specular[2] = 0.0f;
  matl->specular[3] = 1.0f;
  matl->shininess[0] = 0.0f;

  return matl;
}

void swin_free_ppd( Swin *swin )
{
	for ( int i = 0; i < 2; ++i ) {
		if ( swin->screenatr[i].current_ppd != (Sppd *) NULL ) 
			free_ppd( swin->screenatr[i].current_ppd );
	}
  if ( swin->morph_ppd != (Sppd *) NULL ) 
    free_ppd( swin->morph_ppd );
}

void swin_free_hppd( Swin *swin )
{
  void free_hppd( HPpd * );

  if ( swin->hppd == (HPpd *) NULL ) return;
  free_hppd( swin->hppd );

  swin->screenatr[SCREEN_SRC].current_ppd = (Sppd *) NULL;
  swin->screenatr[SCREEN_DIST].current_ppd = (Sppd *) NULL;
  swin->morph_ppd = (Sppd *) NULL;
}
  
void free_swin( Swin *swin )
{
  void swin_free_hppd( Swin * );
  void swin_free_ppd( Swin * );

  swin_free_hppd( swin );
  swin_free_ppd( swin );
  
  free( swin->material );
  free( swin );
}
