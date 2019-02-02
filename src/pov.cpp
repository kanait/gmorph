//
// pov.cpp
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
#include "pov.h"
#include "file.h"

void write_ppdpov_file( char *povname, char *incname, Sppd *ppd, ScreenAtr *screen )
{
	FILE *fp;

	if ( ppd == NULL ) return;
	if ((fp = fopen(povname, "w")) == NULL) return;

//	CString string;
//	string.Format("%s", incname );
//	AfxMessageBox( string );

	// header
	fprintf(fp, "// Persistence Of Vision raytracer version 3.0 sample file.\n");
	fprintf(fp, "// Demonstrates ppd. \n");
	fprintf(fp, "\n");
	fprintf(fp, "#version 3.0\n");
	fprintf(fp, "global_settings { assumed_gamma 2.2 }\n");
	fprintf(fp, "\n");
	fprintf(fp, "#include \"colors.inc\"\n");
	fprintf(fp, "#include \"shapes.inc\"\n");
	fprintf(fp, "#include \"textures.inc\"\n");
	fprintf(fp, "\n");
	
	// a material of ppd
	fprintf(fp, "#declare WHITE_BUNNY = texture {\n");
	fprintf(fp, "\tfinish { Shiny }\n");
	fprintf(fp, "\tpigment { White }\n");
	fprintf(fp, "}\n");
	fprintf(fp, "\n");
	
	// write ppd include file
	char fincname[BUFSIZ];
	find_filename( incname, fincname );
	fprintf(fp, "#include \"%s\"\n", fincname );
	fprintf(fp, "\n");

	// camera 
	Vec eye, look;
	eye.x = screen->pers.eye_dir.x * screen->pers.fd / screen->zoom;
	eye.y = screen->pers.eye_dir.y * screen->pers.fd / screen->zoom;
	eye.z = screen->pers.eye_dir.z * screen->pers.fd / screen->zoom;
	eye.x += screen->pers.ref.x;
	eye.y += screen->pers.ref.y;
	eye.z += screen->pers.ref.z;
	look.x = screen->pers.ref.x;
	look.y = screen->pers.ref.y;
	look.z = screen->pers.ref.z;
  
	fprintf(fp, "camera {\n");
	fprintf(fp, "\tlocation <%g, %g, %g>\n", eye.x, eye.y, eye.z );
	fprintf(fp, "\tright -x*1.333\n");
	fprintf(fp, "\tup y\n");
	fprintf(fp, "\tdirection z\n");
	fprintf(fp, "\tangle %g\n", screen->pers.angle);
	fprintf(fp, "\tlook_at <%g, %g, %g>\n", look.x, look.y, look.z );
	fprintf(fp, "}\n");
	fprintf(fp, "\n");

	// lights 
	fprintf(fp, "light_source { <20, 20, 20> color White }\n");
	fprintf(fp, "light_source { <-20, 20, 20> color White }\n");
	fprintf(fp, "\n");
	//  background color
	fprintf(fp, "sky_sphere { pigment { rgb <%g, %g, %g> } }\n",
		screen->bgrgb[0], screen->bgrgb[1], screen->bgrgb[2]);
	
	// write_ppd 
	write_ppdinc_file( incname, ppd );

	fclose (fp);

}

void write_ppdinc_file(char *fname, Sppd *ppd )
{
	FILE *fp;
	Spfc *fc;
	Sphe *he;
	Vec *vec, *nrm;
	
	if ( ppd == NULL ) return;
	if ((fp = fopen(fname, "w")) == NULL) return;

	fprintf(fp, "mesh {\n");
	for ( fc = ppd->spfc; fc != NULL; fc = fc->nxt ) {
		he = fc->sphe;
		fprintf(fp, "\tsmooth_triangle { ");
		do {
			if ( he != fc->sphe ) fprintf(fp, ", ");
			vec = &(he->vt->vec);
			nrm = ( he->nm != NULL ) ? &(he->nm->vec) : &(fc->nrm);
			fprintf(fp, "<%g, %g, %g>, <%g, %g, %g> ", 
				vec->x, vec->y, vec->z, nrm->x, nrm->y, nrm->z );

		} while ( (he = he->nxt) != fc->sphe );
		fprintf(fp, "}\n");
	}
	fprintf(fp, "\n");
	fprintf(fp, "\ttexture { WHITE_BUNNY }\n");
	fprintf(fp, "}\n");
	fclose (fp);
}
	
