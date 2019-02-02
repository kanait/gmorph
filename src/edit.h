//
// edit.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _EDIT_H
#define _EDIT_H

extern BOOL create_boundaryloop( ScreenAtr * );
extern BOOL create_face( ScreenAtr * );
extern BOOL delete_face( ScreenAtr * );
extern BOOL create_hvertex( void );
extern BOOL delete_hvertex( void );
extern BOOL create_hface( void );
extern BOOL delete_hface( void );
extern BOOL sg_create_spath( ScreenAtr * );
extern BOOL delete_spath( ScreenAtr * );
extern BOOL manual_spath( ScreenAtr * );

#endif // _EDIT_H
