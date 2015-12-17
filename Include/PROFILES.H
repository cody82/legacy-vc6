#ifndef __PROFILES
#define __PROFILES

#ifndef __AFX_H__
#include <windows.h>
#include <stdio.h>
#endif

int GetPrivateProfileIntCurrentDir(char *file,char *section,char *key,int defaultint);
BOOL GetPrivateProfileStringCurrentDir(char *file,char *section,char *key,char *retbuffer,int size);
BOOL WritePrivateProfileStringCurrentDir(char *file,char *section,char *key,char *string);
BOOL WritePrivateProfileIntCurrentDir(char *file,char *section,char *key,int i);
BOOL GetProfileSectionNamesCurDir(char *file,char *buffer,int size);
BOOL GetProfileSectionCurDir(char *file,char *section,char *buffer,int size);

#endif