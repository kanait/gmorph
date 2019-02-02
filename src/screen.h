//
// screen.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _SCREEN_H
#define _SCREEN_H

extern void start_screen3d_rotate(ScreenAtr *);
extern void update_screen3d_rotate(ScreenAtr *, int, int);
extern void update_screen3d_rotate_z(ScreenAtr *, double);
extern void finish_screen3d_rotate(ScreenAtr *);
extern void start_screen3d_zoom(ScreenAtr *);
extern void update_screen3d_zoom(ScreenAtr *, int, int);
extern void finish_screen3d_zoom(ScreenAtr *);

#endif // _SCREEN_H
