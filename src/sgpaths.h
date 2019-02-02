//
// sgpaths.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _SGPATHS_H
#define _SGPATHS_H

extern BOOL isokCalcShortestPath(HPpd *);
extern void SGShortestPathsCreate(HPpd *);
extern Splp *SGShortestPath(SGraph *, Sppd *, Spvt *, Spvt *);
extern Splp *CalcShortestPath(SGraph *, Sppd *);
extern Splp *sglp_to_splp(SGlp *, Sppd *);

#endif // _SGPATHS_H
