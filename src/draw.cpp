//
// draw.cpp
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

//#include "cinc.h"
#include <math.h>

#include "gl\gl.h"
#include "gl\glu.h"
//#include "gl\glaux.h"

#include "smd.h"

#ifndef _COLOR_H
#include "color.h"
#endif

int light_init( Light *light )
{
	::glEnable(GL_LIGHT0);
	::glLightfv(GL_LIGHT0, GL_AMBIENT, light->ambient);
	::glLightfv(GL_LIGHT0, GL_DIFFUSE, light->diffuse);
	::glLightfv(GL_LIGHT0, GL_SPECULAR, light->specular);
	::glLightfv(GL_LIGHT0, GL_POSITION, light->position);
	::glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light->lmodel_ambient);
	::glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, light->local_view);
	
	return 0;
}

/* int light_init(Light *light) */
/* { */
/*   glEnable(GL_LIGHT0); */
/*   glLightfv(GL_LIGHT0, GL_AMBIENT, light->ambient); */
/*   glLightfv(GL_LIGHT0, GL_DIFFUSE, light->diffuse); */
/*   glLightfv(GL_LIGHT0, GL_SPECULAR, light->specular); */
/*   light->position[0] = 0.0; */
/*   light->position[1] = 1.0; */
/*   light->position[2] = 0.0; */
/*   glLightfv(GL_LIGHT0, GL_POSITION, light->position); */

/*   glEnable(GL_LIGHT1); */
/*   glLightfv(GL_LIGHT1, GL_AMBIENT, light->ambient); */
/*   glLightfv(GL_LIGHT1, GL_DIFFUSE, light->diffuse); */
/*   glLightfv(GL_LIGHT1, GL_SPECULAR, light->specular); */
/*   light->position[0] = 0.0; */
/*   light->position[1] = 0.0; */
/*   light->position[2] = -1.0; */
/*   glLightfv(GL_LIGHT1, GL_POSITION, light->position); */

/*   glEnable(GL_LIGHT2); */
/*   glLightfv(GL_LIGHT2, GL_AMBIENT, light->ambient); */
/*   glLightfv(GL_LIGHT2, GL_DIFFUSE, light->diffuse); */
/*   glLightfv(GL_LIGHT2, GL_SPECULAR, light->specular); */
/*   light->position[0] = 0.0; */
/*   light->position[1] = 0.0; */
/*   light->position[2] = 1.0; */
/*   glLightfv(GL_LIGHT2, GL_POSITION, light->position); */

/*   glEnable(GL_LIGHT3); */
/*   glLightfv(GL_LIGHT3, GL_AMBIENT, light->ambient); */
/*   glLightfv(GL_LIGHT3, GL_DIFFUSE, light->diffuse); */
/*   glLightfv(GL_LIGHT3, GL_SPECULAR, light->specular); */
/*   light->position[0] = -1.0; */
/*   light->position[1] = 0.0; */
/*   light->position[2] = 0.0; */
/*   glLightfv(GL_LIGHT3, GL_POSITION, light->position); */

/*   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light->lmodel_ambient); */
/*   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, light->local_view); */

/*   return 0; */
/* } */

void clear_gl3d( ScreenAtr *screen )
{
	//  glXMakeCurrent(XtDisplay(screen->glw), XtWindow(screen->glw), screen->xc);
	::glClearColor((GLfloat) screen->bgrgb[0], (GLfloat) screen->bgrgb[1],
	       (GLfloat) screen->bgrgb[2], (GLfloat) 0.0);
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	::glPushMatrix();
}

/* default view setting */

void set_default_view( ScreenAtr *screen )
{
	double    rad;
	Vec       *V3Normalize(Vec *);
	Vec       *V3Cross(Vec *, Vec *, Vec *);
	void      calc_rotate_matrix(ScreenAtr *);
	
	screen->pers.ref.x = 0.0;
	screen->pers.ref.y = 0.0;
	screen->pers.ref.z = 0.0;
	screen->pers.up.x  = 0.0;
	screen->pers.up.y  = 1.0;
	screen->pers.up.z  = 0.0;
	screen->pers.angle = 45.0;
	screen->pers.znear_ratio = 0.1;
	screen->pers.zfar_ratio  = 10.0;
	/*  screen->pers.eye_dir.x = 1.0 / SQRT3;
	screen->pers.eye_dir.y = 1.0 / SQRT3;*/
	screen->pers.eye_dir.x = 0.0;
	screen->pers.eye_dir.y = 0.0;
	screen->pers.eye_dir.z = 1.0 / SQRT3;
	V3Normalize(&(screen->pers.eye_dir));
	
	/* default focal distance */
	rad = 1.0;
	screen->pers.fd = rad / tan(screen->pers.angle * SMDPI / 360.0);
	
	screen->zoom = 1.0;
	screen->rotate_x = 0.0;
	screen->rotate_y = 0.0;
	screen->rotate_z = 0.0;
	screen->zrot_rad = 0.0;
	
	calc_rotate_matrix( screen );
}

void calc_rotate_matrix(ScreenAtr *screen)
{
	Vec xvec, yvec, zvec;
	Vec *V3Normalize(Vec *);
	Vec *V3Cross(Vec *, Vec *, Vec *);
	
	/* calc rotate_axis vector */
	zvec.x = screen->pers.eye_dir.x;
	zvec.y = screen->pers.eye_dir.y;
	zvec.z = screen->pers.eye_dir.z;
	yvec.x = screen->pers.up.x;
	yvec.y = screen->pers.up.y;
	yvec.z = screen->pers.up.z;
	V3Normalize(&(yvec));
	V3Normalize(&(zvec));
	V3Cross(&(yvec), &(zvec), &(xvec));
	V3Cross(&(zvec), &(xvec), &(yvec));
	V3Normalize(&(xvec));
	V3Normalize(&(yvec));
	
	screen->rotate_xvec.x = xvec.x;
	screen->rotate_xvec.y = xvec.y;
	screen->rotate_xvec.z = xvec.z;
	screen->rotate_yvec.x = yvec.x;
	screen->rotate_yvec.y = yvec.y;
	screen->rotate_yvec.z = yvec.z;
	screen->rotate_zvec.x = zvec.x;
	screen->rotate_zvec.y = zvec.y;
	screen->rotate_zvec.z = zvec.z;
	
	screen->rmat[0]  = screen->rotate_xvec.x;
	screen->rmat[1]  = screen->rotate_yvec.x;
	screen->rmat[2]  = screen->rotate_zvec.x;
	screen->rmat[3]  = 0.0;
	screen->rmat[4]  = screen->rotate_xvec.y;
	screen->rmat[5]  = screen->rotate_yvec.y;
	screen->rmat[6]  = screen->rotate_zvec.y;
	screen->rmat[7]  = 0.0;
	screen->rmat[8]  = screen->rotate_xvec.z;
	screen->rmat[9]  = screen->rotate_yvec.z;
	screen->rmat[10] = screen->rotate_zvec.z;
	screen->rmat[11] = 0.0;
	screen->rmat[12] = 0.0;
	screen->rmat[13] = 0.0;
	screen->rmat[14] = 0.0;
	screen->rmat[15] = 1.0;
}

int view_init(ScreenAtr *screen)
{
	GLdouble rotx[16], roty[16], rotz[16];
	GLdouble rinvx[16], rinvy[16], rinvz[16];
	GLdouble m1[16];
	Vec      eye;
	void     MultMatrix4(double *, double *, double *);
	void     EqualMatrix4(double *, double *);
	void     MakeRotVec(double, Vec *, double *);
	void     MakeRotInvVec(double, Vec *, double *);
	void     MultMatrixVec(double *, Vec *);
	
	glViewport((GLint) 0, (GLint) 0,
		(GLsizei) screen->width, (GLsizei) screen->height);
	
	/* make rotate matrix */
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	screen->pers.scraspct = (double) screen->width / (double) screen->height;
	gluPerspective((GLdouble) screen->pers.angle,
		(GLdouble) screen->pers.scraspct,
		(GLdouble) screen->pers.fd
		* screen->pers.znear_ratio / screen->zoom,
		(GLdouble) screen->pers.fd
		* screen->pers.zfar_ratio / screen->zoom);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if (screen->rotate_type == ROTATE_XY) {
		
		/* Rotate X */
		MakeRotVec(screen->rotate_y, &(screen->rotate_xvec), (double *) rinvx);
		MakeRotInvVec(screen->rotate_y, &(screen->rotate_xvec), (double *) rotx);
		MultMatrix4((double *) screen->rmat, (double *) rotx, (double *) m1);
		MultMatrixVec((double *) rinvx,  &(screen->pers.eye_dir));
		MultMatrixVec((double *) rinvx,  &(screen->rotate_yvec));
		MultMatrixVec((double *) rinvx,  &(screen->rotate_zvec));
		/* Rotate Y */
		MakeRotVec(screen->rotate_x, &(screen->rotate_yvec), (double *) rinvy);
		MakeRotInvVec(screen->rotate_x, &(screen->rotate_yvec), (double *) roty);
		MultMatrix4((double *) m1, (double *) roty, (double *) screen->rmat);
		MultMatrixVec((double *) rinvy,  &(screen->pers.eye_dir));
		MultMatrixVec((double *) rinvy,  &(screen->rotate_zvec));
		MultMatrixVec((double *) rinvy,  &(screen->rotate_xvec));
		screen->rotate_x = 0.0;
		screen->rotate_y = 0.0;
		glMultMatrixd((GLdouble *) screen->rmat);
		
	} else if (screen->rotate_type == ROTATE_Z) {
		
		MakeRotVec(screen->rotate_z, &(screen->rotate_zvec), (double *) rinvz);
		MakeRotInvVec(screen->rotate_z, &(screen->rotate_zvec), (double *) rotz);
		MultMatrix4((double *) screen->rmat, (double *) rotz, (double *) m1);
		EqualMatrix4((double *) m1, (double *) screen->rmat);
		MultMatrixVec((double *) rinvz, &(screen->pers.eye_dir));
		MultMatrixVec((double *) rinvz, &(screen->rotate_xvec));
		MultMatrixVec((double *) rinvz, &(screen->rotate_yvec));
		screen->rotate_z = 0.0;
		glMultMatrixd((GLdouble *) screen->rmat);
		
	}
	
	/* current eye position */
	
	eye.x = screen->pers.eye_dir.x * screen->pers.fd / screen->zoom;
	eye.y = screen->pers.eye_dir.y * screen->pers.fd / screen->zoom;
	eye.z = screen->pers.eye_dir.z * screen->pers.fd / screen->zoom;
	eye.x += screen->pers.ref.x;
	eye.y += screen->pers.ref.y;
	eye.z += screen->pers.ref.z;
	
	glTranslated((GLdouble) -eye.x, (GLdouble) -eye.y, (GLdouble) -eye.z);
	
	return 0;
}
/*
GLuint *view_init_pick(ScreenAtr *screen, int x, int y)
{
GLuint   select_buf[BUFSIZ];
GLint    viewport[4];

 GLdouble rotx[16], roty[16], rotz[16];
 GLdouble rinvx[16], rinvy[16], rinvz[16];
 GLdouble rotxy[16], rinvxy[16], m1[16];
 Vec      eye;
 void     MultMatrix4(double *, double *, double *);
 void     EqualMatrix4(double *, double *);
 void     MakeRotVec(double, Vec *, double *);
 void     MakeRotInvVec(double, Vec *, double *);
 void     MultMatrixVec(double *, Vec *);
 
  glGetIntegerv(GL_VIEWPORT, viewport);
  glSelectBuffer(BUFSIZ, select_buf);
  glRenderMode(GL_SELECT);
  
   glInitNames();
   glPushName(-1);
   glPushMatrix();
   
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPickMatrix((GLdouble) x, (GLdouble)(viewport[3] - y),
	1.0, 1.0, viewport);
	screen->pers.scraspct = (double) screen->width / (double) screen->height;
	gluPerspective((GLdouble) screen->pers.angle,
	(GLdouble) screen->pers.scraspct,
	(GLdouble) screen->pers.fd
	* screen->pers.znear_ratio / screen->zoom,
	(GLdouble) screen->pers.fd
	* screen->pers.zfar_ratio / screen->zoom);
	
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
	 
	  if (screen->rotate_type == ROTATE_XY) {
	  
	   MakeRotVec(screen->rotate_y, &(screen->rotate_xvec), (double *) rinvx);
	   MakeRotInvVec(screen->rotate_y, &(screen->rotate_xvec), (double *) rotx);
	   MultMatrix4((double *) screen->rmat, (double *) rotx, (double *) m1);
	   MultMatrixVec((double *) rinvx,  &(screen->pers.eye_dir));
	   MultMatrixVec((double *) rinvx,  &(screen->rotate_yvec));
	   MultMatrixVec((double *) rinvx,  &(screen->rotate_zvec));
	   
		MakeRotVec(screen->rotate_x, &(screen->rotate_yvec), (double *) rinvy);
		MakeRotInvVec(screen->rotate_x, &(screen->rotate_yvec), (double *) roty);
		MultMatrix4((double *) m1, (double *) roty, (double *) screen->rmat);
		MultMatrixVec((double *) rinvy,  &(screen->pers.eye_dir));
		MultMatrixVec((double *) rinvy,  &(screen->rotate_zvec));
		MultMatrixVec((double *) rinvy,  &(screen->rotate_xvec));
		screen->rotate_x = 0.0;
		screen->rotate_y = 0.0;
		glMultMatrixd((GLdouble *) screen->rmat);
		
		 } else if (screen->rotate_type == ROTATE_Z) {
		 
		  MakeRotVec(screen->rotate_z, &(screen->rotate_zvec), (double *) rinvz);
		  MakeRotInvVec(screen->rotate_z, &(screen->rotate_zvec), (double *) rotz);
		  MultMatrix4((double *) screen->rmat, (double *) rotz, (double *) m1);
		  EqualMatrix4((double *) m1, (double *) screen->rmat);
		  MultMatrixVec((double *) rinvz, &(screen->pers.eye_dir));
		  MultMatrixVec((double *) rinvz, &(screen->rotate_xvec));
		  MultMatrixVec((double *) rinvz, &(screen->rotate_yvec));
		  screen->rotate_z = 0.0;
		  glMultMatrixd((GLdouble *) screen->rmat);
		  
		   }
		   
			eye.x = screen->pers.eye_dir.x * screen->pers.fd / screen->zoom;
			eye.y = screen->pers.eye_dir.y * screen->pers.fd / screen->zoom;
			eye.z = screen->pers.eye_dir.z * screen->pers.fd / screen->zoom;
			eye.x += screen->pers.ref.x;
			eye.y += screen->pers.ref.y;
			eye.z += screen->pers.ref.z;
			
			 glTranslated((GLdouble) -eye.x, (GLdouble) -eye.y, (GLdouble) -eye.z);
			 
			  return select_buf;
			  }
			  
			   GLuint *view_init_pick_area(ScreenAtr *screen)
			   {
			   GLuint   select_buf[BUFSIZ];
			   GLint    viewport[4];
			   GLdouble x, y, width, height;
			   GLdouble rotx[16], roty[16], rotz[16];
			   GLdouble rinvx[16], rinvy[16], rinvz[16];
			   GLdouble rotxy[16], rinvxy[16], m1[16];
			   Vec      eye;
			   void     MultMatrix4(double *, double *, double *);
			   void     EqualMatrix4(double *, double *);
			   void     MakeRotVec(double, Vec *, double *);
			   void     MakeRotInvVec(double, Vec *, double *);
			   void     MultMatrixVec(double *, Vec *);
			   
				glGetIntegerv(GL_VIEWPORT, viewport);
				glSelectBuffer(BUFSIZ, select_buf);
				glRenderMode(GL_SELECT);
				
				 glInitNames();
				 glPushName(-1);
				 glPushMatrix();
				 
				  x = (GLdouble) (screen->areaorg.x + screen->areaatv.x) / 2.0;
				  y = (GLdouble) (screen->areaorg.y + screen->areaatv.y) / 2.0;
				  width  = (GLdouble) fabs(screen->areaatv.x - screen->areaorg.x);
				  height = (GLdouble) fabs(screen->areaatv.y - screen->areaorg.y);
				  
				   glMatrixMode(GL_PROJECTION);
				   glLoadIdentity();
				   gluPickMatrix(x, y , width, height, viewport);
				   screen->pers.scraspct = (double) screen->width / (double) screen->height;
				   gluPerspective((GLdouble) screen->pers.angle,
				   (GLdouble) screen->pers.scraspct,
				   (GLdouble) screen->pers.fd
				   * screen->pers.znear_ratio / screen->zoom,
				   (GLdouble) screen->pers.fd
				   * screen->pers.zfar_ratio / screen->zoom);
				   
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					
					 if (screen->rotate_type == ROTATE_XY) {
					 
					  MakeRotVec(screen->rotate_y, &(screen->rotate_xvec), (double *) rinvx);
					  MakeRotInvVec(screen->rotate_y, &(screen->rotate_xvec), (double *) rotx);
					  MultMatrix4((double *) screen->rmat, (double *) rotx, (double *) m1);
					  MultMatrixVec((double *) rinvx,  &(screen->pers.eye_dir));
					  MultMatrixVec((double *) rinvx,  &(screen->rotate_yvec));
					  MultMatrixVec((double *) rinvx,  &(screen->rotate_zvec));
					  
					   MakeRotVec(screen->rotate_x, &(screen->rotate_yvec), (double *) rinvy);
					   MakeRotInvVec(screen->rotate_x, &(screen->rotate_yvec), (double *) roty);
					   MultMatrix4((double *) m1, (double *) roty, (double *) screen->rmat);
					   MultMatrixVec((double *) rinvy,  &(screen->pers.eye_dir));
					   MultMatrixVec((double *) rinvy,  &(screen->rotate_zvec));
					   MultMatrixVec((double *) rinvy,  &(screen->rotate_xvec));
					   screen->rotate_x = 0.0;
					   screen->rotate_y = 0.0;
					   glMultMatrixd((GLdouble *) screen->rmat);
					   
						} else if (screen->rotate_type == ROTATE_Z) {
						
						 MakeRotVec(screen->rotate_z, &(screen->rotate_zvec), (double *) rinvz);
						 MakeRotInvVec(screen->rotate_z, &(screen->rotate_zvec), (double *) rotz);
						 MultMatrix4((double *) screen->rmat, (double *) rotz, (double *) m1);
						 EqualMatrix4((double *) m1, (double *) screen->rmat);
						 MultMatrixVec((double *) rinvz, &(screen->pers.eye_dir));
						 MultMatrixVec((double *) rinvz, &(screen->rotate_xvec));
						 MultMatrixVec((double *) rinvz, &(screen->rotate_yvec));
						 screen->rotate_z = 0.0;
						 glMultMatrixd((GLdouble *) screen->rmat);
						 
						  }
						  
						   eye.x = screen->pers.eye_dir.x * screen->pers.fd / screen->zoom;
						   eye.y = screen->pers.eye_dir.y * screen->pers.fd / screen->zoom;
						   eye.z = screen->pers.eye_dir.z * screen->pers.fd / screen->zoom;
						   eye.x += screen->pers.ref.x;
						   eye.y += screen->pers.ref.y;
						   eye.z += screen->pers.ref.z;
						   
							glTranslated((GLdouble) -eye.x, (GLdouble) -eye.y, (GLdouble) -eye.z);
							
							 return select_buf;
}*/

void get_GL_attributes(ScreenAtr *screen)
{
	int view_init(ScreenAtr *screen);
	
	glPushMatrix();
	
	(void) view_init(screen);
	glGetDoublev(GL_MODELVIEW_MATRIX,  (GLdouble *) screen->mmat);
	glGetDoublev(GL_PROJECTION_MATRIX, (GLdouble *) screen->pmat);
	glGetIntegerv(GL_VIEWPORT, (GLint *) screen->viewport);
	
	glPopMatrix();
}

static void transform_point( double out[4], double m[16], double in[4] )
{
#define M(row,col)  m[col*4+row]
	out[0] = M(0,0) * in[0] + M(0,1) * in[1] + M(0,2) * in[2] + M(0,3) * in[3];
	out[1] = M(1,0) * in[0] + M(1,1) * in[1] + M(1,2) * in[2] + M(1,3) * in[3];
	out[2] = M(2,0) * in[0] + M(2,1) * in[1] + M(2,2) * in[2] + M(2,3) * in[3];
	out[3] = M(3,0) * in[0] + M(3,1) * in[1] + M(3,2) * in[2] + M(3,3) * in[3];
#undef M
}

void world_to_win(Vec *obj, Vec2d *win, double model[16], double proj[16],
                  int viewport[4])
{
	/* matrice de transformation */
	double in[4],out[4];
	
	/* initilise la matrice et le vecteur a transformer */
	in[0] = obj->x;
	in[1] = obj->y;
	in[2] = obj->z;
	in[3] = 1.0;
	transform_point(out,model,in);
	transform_point(in,proj,out);
	
	/* d'ou le resultat normalise entre -1 et 1*/
	in[0]/=in[3];
	in[1]/=in[3];
	in[2]/=in[3];
	
	/* en coordonnees ecran */
	win->x = viewport[0]+(1+in[0])*viewport[2]/2;
	win->y = viewport[1]+(1+in[1])*viewport[3]/2;
	/* entre 0 et 1 suivant z */
	/*   win->z = (1+in[2])/2; */
}

/********************
* drawing functions
********************/

/* draw 3D coordinate axis */

static void draw3dcoaxis(ScreenAtr *screen)
{
	//  int   printstring(ScreenAtr *, char *);
	double x, y, z, w;
	
	::glLineWidth((GLfloat) 1.0);
	::glColor3dv(magentavec);
	
	x = screen->pers.ref.x;
	y = screen->pers.ref.y;
	z = screen->pers.ref.z;
	w = 0.2 * screen->pers.fd / (screen->zoom * SQRT3);
	
	::glBegin(GL_LINE_STRIP);
	::glVertex3d((GLdouble) x, (GLdouble) y, (GLdouble) z);
	::glVertex3d((GLdouble) x + w, (GLdouble) y, (GLdouble) z);
	::glEnd();
	
	//  ::glRasterPos3d((GLdouble) x + w, (GLdouble) y, (GLdouble) z);
	//  (void) printstring(screen, "x");
	
	::glBegin(GL_LINE_STRIP);
	::glVertex3d((GLdouble) x, (GLdouble) y, (GLdouble) z);
	::glVertex3d((GLdouble) x, (GLdouble) y + w, (GLdouble) z);
	::glEnd();
	//  ::glRasterPos3d((GLdouble) x, (GLdouble) y + w, (GLdouble) z);
	//  (void) printstring(screen, "y");
	
	::glBegin(GL_LINE_STRIP);
	::glVertex3d((GLdouble) x, (GLdouble) y, (GLdouble) z);
	::glVertex3d((GLdouble) x, (GLdouble) y, (GLdouble) z + w);
	::glEnd();
	//  ::glRasterPos3d((GLdouble) x, (GLdouble) y, (GLdouble) z + w);
	//  (void) printstring(screen, "z");
}

/* draw 3D rotate axis */

static void draw3drotateaxis(ScreenAtr *screen)
{
	int    printstring(ScreenAtr *, char *);
	double x, y, z, w;
	Vec    vec;
	void   rot_x(double, Vec *);
	void   rot_y(double, Vec *);
	void   rot_z(double, Vec *);
	void   rot_inv_x(double, Vec *);
	void   rot_inv_y(double, Vec *);
	void   rot_inv_z(double, Vec *);
	void   rot_vec(double, Vec *, Vec *);
	Vec    *V3Cross(Vec *, Vec *, Vec *);
	Vec    *V3Normalize(Vec *);
	
	::glLineWidth((GLfloat) 1.0);
	::glColor3dv(yellowvec);
	
	x = screen->pers.ref.x;
	y = screen->pers.ref.y;
	z = screen->pers.ref.z;
	w = 0.2 * screen->pers.fd / (screen->zoom * SQRT3);
	
	vec.x = w * screen->rotate_xvec.x;
	vec.y = w * screen->rotate_xvec.y;
	vec.z = w * screen->rotate_xvec.z;
	
	::glBegin(GL_LINE_STRIP);
	::glVertex3d((GLdouble) x, (GLdouble) y, (GLdouble) z);
	::glVertex3d((GLdouble) (x + vec.x),
		(GLdouble) (y + vec.y),
		(GLdouble) (z + vec.z));
	::glEnd();
	//  ::glRasterPos3d((GLdouble) (x + vec.x),
	//		(GLdouble) (y + vec.y),
	//		(GLdouble) (z + vec.z));
	//  (void) printstring(screen, "Rx");
	
	vec.x = w * screen->rotate_yvec.x;
	vec.y = w * screen->rotate_yvec.y;
	vec.z = w * screen->rotate_yvec.z;
	
	::glBegin(GL_LINE_STRIP);
	::glVertex3d((GLdouble) x, (GLdouble) y, (GLdouble) z);
	::glVertex3d((GLdouble) (x + vec.x),
		(GLdouble) (y + vec.y),
		(GLdouble) (z + vec.z));
	::glEnd();
	//  glRasterPos3d((GLdouble) (x + vec.x),
	//		(GLdouble) (y + vec.y),
	//		(GLdouble) (z + vec.z));
	//  (void) printstring(screen, "Ry");
	
	vec.x = w * screen->rotate_zvec.x;
	vec.y = w * screen->rotate_zvec.y;
	vec.z = w * screen->rotate_zvec.z;
	
	::glBegin(GL_LINE_STRIP);
	::glVertex3d((GLdouble) x, (GLdouble) y, (GLdouble) z);
	::glVertex3d((GLdouble) (x + vec.x),
		(GLdouble) (y + vec.y),
		(GLdouble) (z + vec.z));
	::glEnd();
	//  glRasterPos3d((GLdouble) (x + vec.x),
	//		(GLdouble) (y + vec.y),
	//		(GLdouble) (z + vec.z));
	//  (void) printstring(screen, "Rz");
}

static void drawselectarea(ScreenAtr *screen)
{
	::glPushMatrix();
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluOrtho2D((GLdouble) 0.0, (GLdouble) screen->width,
		(GLdouble) 0.0, (GLdouble) screen->height);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	
	::glLineWidth((GLfloat) 1.0);
	::glColor3dv(redvec);
	::glBegin(GL_LINE_STRIP);
	::glVertex2d((GLdouble) screen->areaorg.x, (GLdouble) screen->areaorg.y);
	::glVertex2d((GLdouble) screen->areaorg.x, (GLdouble) screen->areaatv.y);
	::glEnd();
	::glBegin(GL_LINE_STRIP);
	::glVertex2d((GLdouble) screen->areaorg.x, (GLdouble) screen->areaorg.y);
	::glVertex2d((GLdouble) screen->areaatv.x, (GLdouble) screen->areaorg.y);
	::glEnd();
	::glBegin(GL_LINE_STRIP);
	::glVertex2d((GLdouble) screen->areaorg.x, (GLdouble) screen->areaatv.y);
	::glVertex2d((GLdouble) screen->areaatv.x, (GLdouble) screen->areaatv.y);
	::glEnd();
	::glBegin(GL_LINE_STRIP);
	::glVertex2d((GLdouble) screen->areaatv.x, (GLdouble) screen->areaorg.y);
	::glVertex2d((GLdouble) screen->areaatv.x, (GLdouble) screen->areaatv.y);
	::glEnd();
	
	::glPopMatrix();
}

static void drawppd( Sppd *ppd, ScreenAtr *screen )
{
	void  drawppd_vertex(Sppd *, ScreenAtr *);
	void  drawppd_edge(Sppd *, ScreenAtr *);
	void  drawppd_vertex_enhanced(Sppd *, ScreenAtr *);
	void  drawppd_edge_enhanced(Sppd *, ScreenAtr *);
	void  drawppd_shading(Sppd *, ScreenAtr *);
	void  drawppd_loop( Sppd *, ScreenAtr * );
	void  drawppd_loop_enhanced( Sppd *, ScreenAtr * );
	void  drawppd_sged( SGraph *, ScreenAtr *, GLdouble *, GLfloat );
	void  drawppd_hiddenline( Sppd *, ScreenAtr * );
	
	if ( swin->dis3d.vertex ) {
		drawppd_vertex( ppd, screen );
	}
	
	if ( (swin->dis3d.wire) && (swin->dis3d.shading) ) {

		drawppd_hiddenline( ppd, screen );

	} else if ( !(swin->dis3d.wire) && (swin->dis3d.shading) ) {
		
		drawppd_shading( ppd, screen );
		
	} else if ( (swin->dis3d.wire) && !(swin->dis3d.shading) ) {
		
		drawppd_edge( ppd, screen );
		
	}
	
	/*     if ( screen->sg != NULL ) { */
	/*       drawppd_sged( screen->sg, screen, (GLdouble *) gray60vec, 2.0 ); */
	/*     } else drawppd_edge( ppd, screen ); */
	
	if ( swin->dis3d.interp ) return;
	
	if ( swin->dis3d.loop ) {
		
		if ( swin->dis3d.enhanced == SMD_OFF ) {
			
			drawppd_loop( ppd, screen );
			
		} else {
			
			drawppd_loop_enhanced( ppd, screen );
			
		}
		
		
	}
	
}  

static void drawhppd( HPpd *hppd, ScreenAtr *screen )
{
	void drawhppd_cmesh( HPpd *, ScreenAtr * );
	void drawhppd_cmesh_enhanced( HPpd *, ScreenAtr * );
	void drawhppd_cpoint_enhanced( HPpd *, ScreenAtr * );
	void drawhppd_shortestpath( HPpd *, ScreenAtr * );
	void drawhppd_group( HPpd *, ScreenAtr *, int );
	void drawhppd_group_enhanced( HPpd *, ScreenAtr * );
	void drawhppd_hmap( HPpd *, ScreenAtr * );
	
	if ( hppd == (HPpd *) NULL ) return;
	
	if ( swin->dis3d.interp ) return;
	
	if ( swin->dis3d.cpoint ) {
		
		drawhppd_cpoint_enhanced( hppd, screen );
		
	}
	
	if ( swin->dis3d.cmesh ) {
		
		if ( swin->dis3d.enhanced == SMD_OFF ) {
			
			drawhppd_cmesh( hppd, screen );
			
		} else {
			
			drawhppd_cmesh_enhanced( hppd, screen );
			
		}
		
	}
	
	/* tile */
	if ( swin->dis3d.group ) {
		
		drawhppd_group( hppd, screen, swin->tileno ); 
		
	}
	
	if ( swin->dis3d.spath ) {
		
		drawhppd_shortestpath( hppd, screen );
		
	}
}

void draws3d( ScreenAtr *screen )
{
	void drawppd_sged( SGraph *, ScreenAtr *, GLdouble *, GLfloat );
	void draw_sglp( SGlp * );
	
	if ( swin->dis3d.coaxis ) {
		
		draw3dcoaxis( screen );
		
	}
	
	if ( screen->view_ppd != (Sppd *) NULL ) {
		drawppd( screen->view_ppd, screen );
	}
	
	if ( screen->lp != (SGlp *) NULL ) draw_sglp( screen->lp );
	
	//  if ( screen->nsg != (SGraph *) NULL ) {
	//    drawppd_sged( screen->nsg, screen, (GLdouble *) blackvec, 4.0 );
	//  }
	
	drawhppd( swin->hppd, screen );
	
	//  if (screen->areaflag) drawselectarea( screen );
	
}

