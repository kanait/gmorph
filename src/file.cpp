/* Copyright (c) 1997-1998 Takashi Kanai; All rights reserved. */

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <sys/stat.h>
#include "smd.h"

void find_fileheader(char *filename, char *tname)
{
  unsigned int   i, j, a;
  char  name[BUFSIZ];

  for (i = strlen(filename) - 1; filename[i] != '/' && i; --i);

  if ( !i ) a = 0;
  else a = i+1;
  strcpy(tname, "\0");
  strcpy(name, "\0");
  for (j = a; j < strlen(filename); ++j) {
    sprintf(name, "%s%c", tname, filename[j]);
    strcpy(tname, name);
  }
}

void find_filename(char *filename, char *tname)
{
  unsigned int   i, j, a;
  char  name[BUFSIZ];

  for (i = strlen(filename) - 1; filename[i] != '\\' && i; --i);

  if ( !i ) a = 0;
  else a = i+1;
  strcpy(tname, "\0");
  strcpy(name, "\0");
  for (j = a; j < strlen(filename); ++j) {
    sprintf(name, "%s%c", tname, filename[j]);
    strcpy(tname, name);
  }
}

void filehead(char *filename, char *tname)
{
  int   i, j;
  char  name[BUFSIZ];

  for (i = strlen(filename) - 1; filename[i] != '.' && i; --i);

  strcpy(tname, "\0");
  strcpy(name, "\0");
  for (j = 0; j < i; ++j) {
    sprintf(name, "%s%c", tname, filename[j]);
    strcpy(tname, name);
  }
}

char *open_filename(char *str, char *name, char *dname)
{
  int   tidx;
  struct stat statbuf;
  char  com[BUFSIZ];

  if (stat(str, &statbuf) == -1) {
    if (str) {
      for (tidx = strlen(str) - 1;
	   str[tidx] != '/' &&
	   tidx; tidx--) {
      };

      sprintf(name, "%s", &str[tidx + 1]);
      strcpy(dname, str);
      return name;
    }
  }
  if (statbuf.st_mode & S_IFDIR) {
    sprintf(com, "dir %s\n", str);
  } else {
    for (tidx = strlen(str) - 1;
	 str[tidx] != '/' &&
	 tidx; tidx--) {
    };

    strcpy(dname, str);
    strcpy(name, &(str[tidx + 1]));
  }
  return name;
}

char *cut(char *sstr, char *res)
{
  int   search;
  char *str;

  str = sstr;
  search = 0;
  while (SMD_ON) {
    if (search == 0) {		/* before found */
      if (*str == ' ' || *str == '\t') {
	++str;
      } else if (*str == '\0' || *str == '\n') {
	str = NULL;
	break;
      } else {
	*res++ = *str++;
	search = 1;
      }
    } else if (search == 1) {	/* now searching */
      if (*str == ' ' || *str == '\t') {
	++str;
	search = 2;
      } else if (*str == '\0' || *str == '\n') {
	str = NULL;
	break;
      } else {
	*res++ = *str++;
      }
    } else {			/* after found */
      if (*str == ' ' || *str == '\t') {
	++str;
      } else if (*str == '\0' || *str == '\n') {
	str = NULL;
	break;
      } else {
	break;
      }
    }
  }
  *res = '\0';
  return str;
}
