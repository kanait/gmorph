/* Copyright (c) 1997-1998 by Takashi Kanai; All rights researved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>
#include "smd.h"

/******************/
/*   2d Library   */
/******************/

/* returns squared length of input vector */
double V2SquaredLength(Vec2d *a)
{
  return (a->x * a->x) + (a->y * a->y);
}

/* returns length of input vector */
double V2Length(Vec2d *a)
{
  return sqrt(V2SquaredLength(a));
}

/* negates the input vector and returns it */
Vec2d *V2Negate(Vec2d *v)
{
  v->x = -v->x;
  v->y = -v->y;
  return v;
}

/* normalizes the input vector and returns it */
Vec2d *V2Normalize(Vec2d *v)
{
  double   len = V2Length(v);
  if (len != 0.0) {
    v->x /= len;
    v->y /= len;
  }
  return v;
}


/* scales the input vector to the new length and returns it */
Vec2d *V2Scale(Vec2d *v, double newlen)
{
  double   len = V2Length(v);
  if (len != 0.0) {
    v->x *= newlen / len;
    v->y *= newlen / len;
  }
  return v;
}

/* return vector sum c = a+b */
Vec2d *V2Add(Vec2d *a, Vec2d *b, Vec2d *c)
{
  c->x = a->x + b->x;
  c->y = a->y + b->y;
  return c;
}

/* return vector difference c = a-b */
Vec2d *V2Sub(Vec2d *a, Vec2d *b, Vec2d *c)
{
  c->x = a->x - b->x;
  c->y = a->y - b->y;
  return c;
}

/* return the dot product of vectors a and b */
double V2Dot(Vec2d *a, Vec2d *b)
{
  return (a->x * b->x) + (a->y * b->y);
}

/* make a linear combination of two vectors and return the result. */
/* result = (a * ascl) + (b * bscl) */
Vec2d *V2Combine(Vec2d *a, Vec2d *b, Vec2d *result, double ascl, double bscl)
{
  result->x = (ascl * a->x) + (bscl * b->x);
  result->y = (ascl * a->y) + (bscl * b->y);
  return result;
}

/* multiply two vectors together component-wise */
Vec2d *V2Mul(Vec2d *a, Vec2d *b, Vec2d *result)
{
  result->x = a->x * b->x;
  result->y = a->y * b->y;
  return result;
}

/* return the distance between two points */
double V2DistanceBetween2Points(Vec2d *a, Vec2d *b)
{
  double   dx = a->x - b->x;
  double   dy = a->y - b->y;
  return sqrt((dx * dx) + (dy * dy));
}

/* return the vector perpendicular to the input vector a */
Vec2d *V2MakePerpendicular(Vec2d *a, Vec2d *ap)
{
  ap->x = -a->y;
  ap->y = a->x;
  return ap;
}

/* multiply a point by a projective matrix and return the transformed point */
Vec2d *V2MulPointByProjMatrix(Vec2d *pin, Mat3 *m, Vec2d *pout)
{
  double   w;
  pout->x = (pin->x * m->elm[0][0]) + (pin->y * m->elm[1][0]) + m->elm[2][0];
  pout->y = (pin->x * m->elm[0][1]) + (pin->y * m->elm[1][1]) + m->elm[2][1];
  w = (pin->x * m->elm[0][2]) + (pin->y * m->elm[1][2]) + m->elm[2][2];
  if (w != 0.0) {
    pout->x /= w;
    pout->y /= w;
  }
  return pout;
}

/* multiply together matrices c = ab */
/* note that c must not point to either of the input matrices */
Mat3 *V2MatMul(Mat3 * a, Mat3 * b, Mat3 * c)
{
  int   i, j, k;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      c->elm[i][j] = 0;
      for (k = 0; k < 3; k++)
	c->elm[i][j] += a->elm[i][k] * b->elm[k][j];
    }
  }
  return c;
}

/* transpose rotation portion of matrix a, return b */
Mat3 *TransposeMatrix3(Mat3 * a, Mat3 * b)
{
  int   i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++)
      b->elm[i][j] = a->elm[j][i];
  }
  return b;
}

double V2Cosign(Vec2d *vec1, Vec2d *vec2)
{
  double  d1, d2, d3;
  double  V2Length(Vec2d *);
  double  V2Dot(Vec2d *, Vec2d *);
  
  d1 = V2Length(vec1);
  d2 = V2Length(vec2);
  d3 = V2Dot(vec1, vec2);
  return d3 / (d1 * d2);
}

double V2Sign(Vec2d *vec1, Vec2d *vec2)
{
  return vec1->x * vec2->y - vec1->y * vec2->x;
}

int V2Signi(Vec2d *vec1, Vec2d *vec2)
{
  double val;
  
  val = 1000.0 * (vec1->x * vec2->y - vec1->y * vec2->x);
  if ( val > SMDZEROEPS ) return SMD_ON;
  return SMD_OFF;
}

/******************/
/*   3d Library   */
/******************/

/* returns squared length of input vector */
double V3SquaredLength(Vec *a)
{
  return (a->x * a->x) + (a->y * a->y) + (a->z * a->z);
}

/* returns length of input vector */
double V3Length(Vec *a)
{
  return sqrt(V3SquaredLength(a));
}

/* negates the input vector and returns it */
Vec *V3Negate(Vec *v)
{
  v->x = -v->x;
  v->y = -v->y;
  v->z = -v->z;
  return v;
}

/* equals the input vector and returns it */
Vec *V3Equal(Vec *v, Vec *a)
{
  v->x = a->x;
  v->y = a->y;
  v->z = a->z;
  return v;
}

/* normalizes the input vector and returns it */
Vec *V3Normalize(Vec *v)
{
  double   V3Length(Vec *);

  double   len = V3Length(v);
  if (len != 0.0) {
    v->x /= len;
    v->y /= len;
    v->z /= len;
  }
  return v;
}

/* scales the input vector to the new length and returns it */
Vec *V3Scale(Vec *v, double newlen)
{
  double   len = V3Length(v);
  if (len != 0.0) {
    v->x *= newlen / len;
    v->y *= newlen / len;
    v->z *= newlen / len;
  }
  return v;
}

/* scalar multiplication of vector and returns it */
Vec *V3Scr(double k, Vec *p1, Vec *p)
{
  p->x = p1->x * k;
  p->y = p1->y * k;
  p->z = p1->z * k;

  return p;
}


/* return vector sum c = a+b */
Vec *V3Add(Vec *a, Vec *b, Vec *c)
{
  c->x = a->x + b->x;
  c->y = a->y + b->y;
  c->z = a->z + b->z;
  return c;
}

/* return vector difference c = a-b */
Vec *OV3Sub(Vec *a, Vec *b, Vec *c)
{
  c->x = a->x - b->x;
  c->y = a->y - b->y;
  c->z = a->z - b->z;
  return c;
}

/* return vector difference c = a-b */
Vec *V3Sub(Vec *a, Vec *b, Vec *c)
{
  c->x = a->x - b->x;
  c->y = a->y - b->y;
  c->z = a->z - b->z;
  return c;
}

/* return the dot product of vectors a and b */
double V3Dot(Vec *a, Vec *b)
{
  return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

/* return the dot product of vectors a and b */
double OV3Dot(Vec *a, Vec *b)
{
  return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

/* make a linear combination of two vectors and return the result. */
/* result = (a * ascl) + (b * bscl) */
Vec *V3Combine(Vec *a, Vec *b, Vec *result, double ascl, double bscl)
{
  result->x = (ascl * a->x) + (bscl * b->x);
  result->y = (ascl * a->y) + (bscl * b->y);
  result->z = (ascl * a->z) + (bscl * b->z);
  return result;
}


/* multiply two vectors together component-wise and return the result */
Vec *V3Mul(Vec *a, Vec *b, Vec *result)
{
  result->x = a->x * b->x;
  result->y = a->y * b->y;
  result->z = a->z * b->z;
  return result;
}

/* return the distance between two points */
double V3DistanceBetween2Points(Vec *a, Vec *b)
{
  double   dx = a->x - b->x;
  double   dy = a->y - b->y;
  double   dz = a->z - b->z;
  return sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

/* return the distance between two points */
double OV3DistanceBetween2Points(Vec *a, Vec *b)
{
  double   dx = a->x - b->x;
  double   dy = a->y - b->y;
  double   dz = a->z - b->z;
  return sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

/* return the cross product c = a cross b */
Vec *V3Cross(Vec *a, Vec *b, Vec *c)
{
  c->x = (a->y * b->z) - (a->z * b->y);
  c->y = (a->z * b->x) - (a->x * b->z);
  c->z = (a->x * b->y) - (a->y * b->x);
  return c;
}

/* tri_product of 3 vectors (by kami) */

double V3Triple(Vec *p1, Vec *p2, Vec *p3)
{
  double   r;

  r = (p1->x * p2->y * p3->z
       + p1->y * p2->z * p3->x
       + p1->z * p2->x * p3->y
       - p1->z * p2->y * p3->x
       - p1->x * p2->z * p3->y
       - p1->y * p2->x * p3->z);
  return (r);
}

double V3Cosign(Vec *vec1, Vec *vec2)
{
  double  d1, d2, d3;
  double  V3Length(Vec *);
  double  V3Dot(Vec *, Vec *);
  
  d1 = V3Length(vec1);
  d2 = V3Length(vec2);
  d3 = V3Dot(vec1, vec2);
  /* display("len %g %g dot %g\n", d1, d2, d3); */
  return d3 / (d1 * d2);
}

/* return the distance between two points */

double V3SquaredDistanceBetween2Points(Vec *a, Vec *b)
{
  double   dx = a->x - b->x;
  double   dy = a->y - b->y;
  double   dz = a->z - b->z;
  return (dx * dx) + (dy * dy) + (dz * dz);
}

/* multiply a point by a matrix and return the transformed point */
Vec *V3MulPointByMatrix(Vec *pin, Mat3 *m, Vec *pout)
{
  pout->x = (pin->x * m->elm[0][0]) + (pin->y * m->elm[1][0]) +
    (pin->z * m->elm[2][0]);
  pout->y = (pin->x * m->elm[0][1]) + (pin->y * m->elm[1][1]) +
    (pin->z * m->elm[2][1]);
  pout->z = (pin->x * m->elm[0][2]) + (pin->y * m->elm[1][2]) +
    (pin->z * m->elm[2][2]);
  return pout;
}

/* multiply a point by a projective matrix and return the transformed point */
Vec *V3MulPointByProjMatrix(Vec *pin, Mat4 *m, Vec *pout)
{
  double   w;
  pout->x = (pin->x * m->elm[0][0]) + (pin->y * m->elm[1][0]) +
    (pin->z * m->elm[2][0]) + m->elm[3][0];
  pout->y = (pin->x * m->elm[0][1]) + (pin->y * m->elm[1][1]) +
    (pin->z * m->elm[2][1]) + m->elm[3][1];
  pout->z = (pin->x * m->elm[0][2]) + (pin->y * m->elm[1][2]) +
    (pin->z * m->elm[2][2]) + m->elm[3][2];
  w = (pin->x * m->elm[0][3]) + (pin->y * m->elm[1][3]) +
    (pin->z * m->elm[2][3]) + m->elm[3][3];
  if (w != 0.0) {
    pout->x /= w;
    pout->y /= w;
    pout->z /= w;
  }
  return pout;
}

/* multiply together matrices c = ab */
/* note that c must not point to either of the input matrices */
Mat4 *V3MatMul(Mat4 * a, Mat4 * b, Mat4 * c)
{
  int   i, j, k;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      c->elm[i][j] = 0;
      for (k = 0; k < 4; k++)
	c->elm[i][j] += a->elm[i][k] * b->elm[k][j];
    }
  }
  return c;
}



