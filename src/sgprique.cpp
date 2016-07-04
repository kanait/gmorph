/* Copyright (c) 1997-1998 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "smd.h"
#include "sgprique.h"

SGPQHeap *create_sgpqheap( int size )
{
  int    i;
  SGPQHeap *pqh;

  pqh = (SGPQHeap *) malloc(sizeof(SGPQHeap));

  pqh->pqcont = (SGPQCont *) malloc( size * sizeof(SGPQCont) );
  
  pqh->size     = size;
  for ( i = 0; i < size; ++i ) pqh->pqcont[i].id = i;
  pqh->size     = size;
  pqh->last     = 0;

  return pqh;
}

void swap_sgpqcont( SGPQCont *a, SGPQCont *b )
{
  double temp_dis;
  SGvt   *temp_vt;

  temp_dis    = a->distance;
  a->distance = b->distance;
  b->distance = temp_dis;

  temp_vt   = a->tgt_vt;
  a->tgt_vt = b->tgt_vt;
  b->tgt_vt = temp_vt;
  
  a->tgt_vt->pqc = a;
  b->tgt_vt->pqc = b;
  
  temp_vt   = a->prv_vt;
  a->prv_vt = b->prv_vt;
  b->prv_vt = temp_vt;
  
}  

void insert_sgpqcont( double dis, SGPQHeap *pqh, SGvt *tgt, SGvt *prv )
{
  if ( pqh->last >= (pqh->size - 1) ) {
    return;
  }

  pqh->pqcont[pqh->last].distance = dis;
  pqh->pqcont[pqh->last].tgt_vt = tgt;
  pqh->pqcont[pqh->last].prv_vt = prv;
  tgt->pqc = &(pqh->pqcont[pqh->last]);
  tgt->pq_type = EXIST;
  
  sg_adjust_to_parent( pqh->last, pqh );

  ++(pqh->last);

}

static int parent_num( int child )
{
  return (int) (child - 1) / 2;
}

/* parent direction process */
void sg_adjust_to_parent( int id, SGPQHeap *pqh )
{
  int  p, c;

  c = id;

  while ( c > 0 ) {
    p = parent_num( c );
    if ( pqh->pqcont[p].distance > pqh->pqcont[c].distance ) {
      swap_sgpqcont( &(pqh->pqcont[c]), &(pqh->pqcont[p]) );
      c = p;
    } else return;
  }
}

/* child direction process */
void sg_adjust_to_child( int id, SGPQHeap *pqh )
{
  int  p, c, i2l, i2r;

  if ( pqh->last <= 1 ) return;

  p = id;

  while ( p <= parent_num(pqh->last-1) ) {

    /* child: i2l, i2r */
    i2l = 2*p+1; i2r = i2l+1;
    if ( i2r == pqh->last ) { /* pqh->last does not exist. */
      c = i2l;
    } else if ( pqh->pqcont[i2l].distance < pqh->pqcont[i2r].distance ) {
      c = i2l;
    } else {
      c = i2r;
    }
    
    if ( pqh->pqcont[p].distance > pqh->pqcont[c].distance ) {
      swap_sgpqcont( &(pqh->pqcont[p]), &(pqh->pqcont[c]) );
    } else return;
    
    p = c;
    
  }
}

void adjust_sgpqheap( Id id, SGPQHeap *pqh )
{
  sg_adjust_to_parent( id, pqh );
}

void deletemin_sgpqcont( SGPQHeap *pqh )
{
  int  i, a;
  
  /* empty */
  if ( pqh->last == 0 ) {
    return;
  }
  

  /* delete mininum (root) */
  pqh->pqcont[0].tgt_vt->pq_type = DELETED;
  pqh->pqcont[0].tgt_vt->pqc     = (SGPQCont *) NULL;

  a = pqh->pqcont[0].tgt_vt->no;
  pqh->pqcont[0].distance = pqh->pqcont[pqh->last-1].distance;
  pqh->pqcont[0].tgt_vt   = pqh->pqcont[pqh->last-1].tgt_vt;
  pqh->pqcont[0].prv_vt   = pqh->pqcont[pqh->last-1].prv_vt;

  pqh->pqcont[0].tgt_vt->pqc = &(pqh->pqcont[0]);

  --(pqh->last);

  i = 0;
  sg_adjust_to_child( i, pqh );
}

void free_sgpqheap( SGPQHeap *pqh )
{
  free( pqh->pqcont );
  free( pqh );
}


