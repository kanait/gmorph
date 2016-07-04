/* Copyright (c) 1997 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"

/***************************************
  Open Ppd Functions
****************************************/

Oppd *create_oppd(void)
{
  Oppd *oppd;
  
  oppd = (Oppd *) malloc(sizeof(Oppd));

  oppd->oso = (Oso *) NULL;
  oppd->opt = (Opt *) NULL;
  oppd->onm = (Onm *) NULL;
  oppd->ovt = (Ovt *) NULL;
  oppd->ofc = (Ofc *) NULL;

  return oppd;
}
  
void free_oppd(Oppd *oppd)
{
  free(oppd->oso);
  free(oppd->opt);
  free(oppd->onm);
  free(oppd->ovt);
  free(oppd->ofc);
  free(oppd);
}
  
Oso *create_osolid(Oppd *oppd, int num)
{
  Oso *oso;
  
  oso = (Oso *) malloc(num * sizeof(Oso));
  
  return oso;
}

Opt *create_opart(Oppd *oppd, int num)
{
  Opt *opt;
  
  opt = (Opt *) malloc(num * sizeof(Opt));

  return opt;
}

Ofc *create_oface(Oppd *oppd, int num)
{
  Ofc *ofc;
  
  ofc = (Ofc *) malloc(num * sizeof(Ofc));

  return ofc;
}

Onm *create_onormal(Oppd *oppd, int num)
{
  Onm *onm;
  
  onm = (Onm *) malloc(num * sizeof(Onm));

  return onm;
}

Ovt *create_overtex(Oppd *oppd, int num)
{
  Ovt *ovt;
  
  ovt = (Ovt *) malloc(num * sizeof(Ovt));

  return ovt;
}

