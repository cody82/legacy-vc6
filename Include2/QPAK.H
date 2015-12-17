#ifndef __QPAK_H
#define __QPAK_H

#include <stdio.h>
#include <string.h>

int qpak_ExtractFile (const char *pakFile, const char *lumpName, char *outFile);
int qpak_GetFilePos(const char *pakFile, const char *lumpName, int *pos,int *size);

#endif