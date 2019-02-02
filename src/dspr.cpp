//
// dspr.cpp
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
#include "sigproc.h"
#include "dspr.h"

SparseMatrix *init_sparsematrix( int num )
{
  SparseMatrix *sm;

  sm = (SparseMatrix *) malloc( sizeof(SparseMatrix) );
  sm->ncol = sm->nrow = num;

  return sm;
}

void free_sparsematrix( SparseMatrix *sm )
{
  free( sm->sa );
  free( sm->ija );
  free( sm );
}


