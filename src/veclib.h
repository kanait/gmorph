//
// veclib.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _VECLIB_H
#define _VECLIB_H

extern double V2SquaredLength(Vec2d *);
extern double V2Length(Vec2d *);
extern Vec2d *V2Negate(Vec2d *);
extern Vec2d *V2Normalize(Vec2d *);
extern Vec2d *V2Scale(Vec2d *, double);
extern Vec2d *V2Add(Vec2d *, Vec2d *, Vec2d *);
extern Vec2d *V2Sub(Vec2d *, Vec2d *, Vec2d *);
extern double V2Dot(Vec2d *, Vec2d *);
extern Vec2d *V2Combine(Vec2d *, Vec2d *, Vec2d *, double, double);
extern Vec2d *V2Mul(Vec2d *, Vec2d *, Vec2d *);
extern double V2DistanceBetween2Points(Vec2d *, Vec2d *);
extern Vec2d *V2MakePerpendicular(Vec2d *, Vec2d *);
extern Vec2d *V2MulPointByProjMatrix(Vec2d *, Mat3 *, Vec2d *);
extern Mat3 *V2MatMul(Mat3 *, Mat3 *, Mat3 *);
extern Mat3 *TransposeMatrix3(Mat3 *, Mat3 *);
extern double V2Cosign(Vec2d *, Vec2d *);
extern double V2Sign(Vec2d *, Vec2d *);
extern int V2Signi(Vec2d *, Vec2d *);
extern double V3SquaredLength(Vec *);
extern double V3Length(Vec *);
extern Vec *V3Negate(Vec *);
extern Vec *V3Equal(Vec *, Vec *);
extern Vec *V3Normalize(Vec *);
extern Vec *V3Scale(Vec *, double);
extern Vec *V3Scr(double, Vec *, Vec *);
extern Vec *V3Add(Vec *, Vec *, Vec *);
extern Vec *OV3Sub(Vec *, Vec *, Vec *);
extern Vec *V3Sub(Vec *, Vec *, Vec *);
extern double V3Dot(Vec *, Vec *);
extern double OV3Dot(Vec *, Vec *);
extern Vec *V3Combine(Vec *, Vec *, Vec *, double, double);
extern Vec *V3Mul(Vec *, Vec *, Vec *);
extern double V3DistanceBetween2Points(Vec *, Vec *);
extern double OV3DistanceBetween2Points(Vec *, Vec *);
extern Vec *V3Cross(Vec *, Vec *, Vec *);
extern double V3Triple(Vec *, Vec *, Vec *);
extern double V3Cosign(Vec *, Vec *);
extern double V3SquaredDistanceBetween2Points(Vec *, Vec *);
extern Vec *V3MulPointByMatrix(Vec *, Mat3 *, Vec *);
extern Vec *V3MulPointByProjMatrix(Vec *, Mat4 *, Vec *);
extern Mat4 *V3MatMul(Mat4 *, Mat4 *, Mat4 *);

#endif // _VECLIB_H
