/* Copyright (c) 1997-1998 by Takashi Kanai; All rights reserved. */

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

extern int light_init(Light *);
extern void clear_gl3d(ScreenAtr *);
extern void set_default_view(ScreenAtr *);
extern void calc_rotate_matrix(ScreenAtr *);
extern int view_init(ScreenAtr *);
extern void get_GL_attributes(ScreenAtr *);
extern void world_to_win(Vec *, Vec2d *, double [16], double [16], int [4]);
extern void draws3d( ScreenAtr * );
extern void drawwindow(int);
