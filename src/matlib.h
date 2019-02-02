 //
// matlib.h
//
// Copyright (c); 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _MATLIB_H
#define _MATLIB_H

typedef double** Vmtx;

extern double InvertMatrix( Vmtx, int );
extern Vmtx NewMatrix( int, int );
extern void FreeMatrix( Vmtx, int );
extern void TransposeMatrix( Vmtx, Vmtx, int, int );
extern void MultMatrix( Vmtx, Vmtx, Vmtx, int, int, int );
extern void rot_x( double, Vec* );
extern void rot_y( double, Vec* );
extern void rot_z( double, Vec* );
extern void rot_inv_x( double, Vec* );
extern void rot_inv_y( double, Vec* );
extern void rot_inv_z( double, Vec* );
extern void rot_all( double, double, double, Vec* );
extern void rot_vec( double, Vec*, Vec* );
extern void MultMatrix4( double*, double*, double* );
extern void MakeRotX( double, double* );
extern void MakeRotY( double, double* );
extern void MakeRotZ( double, double* );
extern void MakeRotVec( double, Vec*, double* );
extern void MakeRotInvVec( double, Vec*, double* );
extern void MultMatrixVec( double*, Vec* );
extern void EqualMatrix4( double*, double* );

#endif // _MATLIB_H
