//
// file.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _FILE_H
#define _FILE_H

extern void find_fileheader(char *, char *);
extern void find_filename(char *, char *);
extern void filehead(char *, char *);
extern char *open_filename(char *, char *, char *);
extern char *cut(char *, char *);

#endif // _FILE_H
