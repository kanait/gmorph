//
// hged.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _HGED_H
#define _HGED_H

extern HGed *create_hgppdedge(HGfc *);
extern void free_hgppdedge(HGed *, HGfc *);
extern HGed *find_hgppdedge(HGvt *, HGvt *);
extern HGedList *create_hgedlist(void);
extern void free_hgedlist(HGedList *);
extern HGedNode *create_hgednode(HGed *, HGedList *);
extern void free_hgednode(HGedNode *, HGedList *);
extern void free_start_hgednode(HGedList *);
extern HGedvt *create_hgedvt(HGvt *, HGed *);
extern void free_hgppdedgevertex(HGed *);
extern void free_hgedvt(HGedvt *, HGed *);
extern HGedvtList *create_hgedvtlist(void);
extern void free_hgedvtlist(HGedvtList *);
extern HGedvtNode *create_hgedvtnode(HGedvtList *);
extern HGedvtNode *create_start_hgedvtnode(HGedvtList *);
extern HGedvtNode *create_end_hgedvtnode(HGedvtList *);
extern void free_hgedvtnode(HGedvtNode *, HGedvtList *);
extern void free_start_hgedvtnode(HGedvtList *);
extern HGeded *create_hgeded(HGed *);
extern void free_hgppdedgeedge(HGed *);
extern void free_hgeded(HGeded *, HGed *);

#endif // _HGED_H
