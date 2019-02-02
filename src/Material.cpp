//
// Material.cpp
//
// Copyright (c) 1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "stdafx.h"
// #include "OpenGL.h"
#include "Material.h"

#include "smd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMaterial::CMaterial( void )
{
	ambient[0] = (float) 0.2;
    ambient[1] = (float) 0.2;
	ambient[2] = (float) 0.2;
	ambient[3] = (float) 1.0;
	diffuse[0] = (float) 0.8;
	diffuse[1] = (float) 0.8;
	diffuse[2] = (float) 0.8;
	diffuse[3] = (float) 1.0;
	emission[0] = (float) 0.0;
	emission[1] = (float) 0.0;
    emission[2] = (float) 0.0;
	emission[3] = (float) 1.0;
	specular[0] = (float) 0.0;
    specular[1] = (float) 0.0;
    specular[2] = (float) 0.0;
	specular[3] = (float) 1.0;
	shininess[0] = (float) 0.0;	
}

CMaterial::~CMaterial( void )
{
	return;
}

void CMaterial::Binding( void )
{
	::glMaterialfv( GL_FRONT, GL_AMBIENT, (GLfloat *) ambient );
	::glMaterialfv( GL_FRONT, GL_DIFFUSE, (GLfloat *) diffuse );
	::glMaterialfv( GL_FRONT, GL_SPECULAR, (GLfloat *) specular );
	::glMaterialfv( GL_FRONT, GL_EMISSION, (GLfloat *) emission );
	::glMaterialfv( GL_FRONT, GL_SHININESS, (GLfloat *) shininess );
}

void material_binding( Material *material )
{
  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialfv(GL_FRONT, GL_EMISSION, material->emission);
  glMaterialfv(GL_FRONT, GL_SHININESS, material->shininess);
}
