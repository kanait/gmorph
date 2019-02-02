//
// screen.cpp
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


/* rotate 3D */

void start_screen3d_rotate( ScreenAtr *screen )
{
  screen->rotate_active = SMD_ON;
}

void update_screen3d_rotate(ScreenAtr *screen, int dx, int dy)
{
  screen->rotate_active = SMD_ON;
  screen->rotate_type   = ROTATE_XY;
  screen->rotate_x = (double) dx;
  screen->rotate_y = (double) dy;
}

void update_screen3d_rotate_z(ScreenAtr *screen, double dz)
{
  screen->rotate_active = SMD_ON;
  screen->rotate_type   = ROTATE_Z;
  screen->rotate_z      = dz;
  screen->zrot_rad      += (dz * SMDPI / 180.0);
}

void finish_screen3d_rotate(ScreenAtr *screen)
{
  screen->rotate_active = SMD_OFF;
}

/* zoom 3D */

void start_screen3d_zoom(ScreenAtr *screen)
{
  screen->zoom_active = SMD_ON;
}

void update_screen3d_zoom(ScreenAtr *screen, int dx, int dy)
{
  screen->zoom_active = SMD_ON;
  screen->zoom += ((float) 5.0e-03 * (dx - dy));
  if (screen->zoom < 1.0e-04) screen->zoom = (float) 1.0e-04;
  
}

void finish_screen3d_zoom(ScreenAtr *screen)
{
  screen->zoom_active = SMD_OFF;
}

