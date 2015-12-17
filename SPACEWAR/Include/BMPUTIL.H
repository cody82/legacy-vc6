#ifndef __BMPUTIL_H
#define __BMPUTIL_H
#include "dibapi.h"
#include "ddraw.h"
#include "dib.h"
#include "ddutil.h"

HDIB ReadDIBFileInFile(HANDLE hfile,DWORD begin,DWORD size);
LPDIRECTDRAWSURFACE LoadBmpInFile(IDirectDraw *pdd, HANDLE hfile,DWORD begin,DWORD size);
HBITMAP LoadBmpInFile(HANDLE hfile,DWORD begin,DWORD size);
BOOL LoadPBM_sw_asciiInFile(byte *b,HANDLE hfile,DWORD begin,DWORD size);

#endif