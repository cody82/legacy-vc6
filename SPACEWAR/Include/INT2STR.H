#ifndef __INT2STR
#define __INT2STR
#include <string.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "ddraw.h"
#include "dibapi.h"
#include "dib.h"

char* int2str(int x);
void int2str(int x,char *buffer);
int str2int(char *string);
double str2double(char* string);
int random(int min,int max);
unsigned short ColorCode(int r,int g,int b);//565 16bit
float GetDistance(float x1,float y1,float x2,float y2);
float GetAngleDiff(float a1,float a2);
//BOOL AdditiveBlt16(LPDIRECTDRAWSURFACE3 destsurface,LPDIRECTDRAWSURFACE3 srcsurface,RECT *destrect,RECT *srcrect);
BOOL DrawAdditiveRect(LPDIRECTDRAWSURFACE3 lpDDS,RECT rect,int rn,int gn,int bn);
BOOL FileOpenDlg(HWND hWnd,char *buffer,int size);
BOOL FileExist(char *filename);
BOOL FileExistCurDir(char *filename);
BOOL code(char *string,unsigned char key);
char *maketextstring(char *filename);
HBITMAP LoadBMP(char *szFile);
//BOOL DeleteBitmap(HBITMAP hbm);
BOOL DDAlphaBlend(LPDIRECTDRAWSURFACE3 lpDDS1,LPDIRECTDRAWSURFACE3 lpDDS2,LPRECT rect1,LPRECT rect2);
BOOL SaveDC2File(HDC hdc,char *file);
//LPDIRECTDRAWSURFACE3 DDLoadBitmap3(LPDIRECTDRAW dd,LPSTR file);
BOOL PointInRect(POINT p,RECT rect);
void DrawLine(LPDIRECTDRAWSURFACE3 lpDDS,int x1,int y1,int x2,int y2,COLORREF c,int width);
void DDPolyLine(LPDIRECTDRAWSURFACE3 lpDDS,POINT *points,int npoints,COLORREF c,int width);
void DDPolyBezier(LPDIRECTDRAWSURFACE3 lpDDS,POINT *points,int npoints,COLORREF c,int width);
void DDSimpleBezier(LPDIRECTDRAWSURFACE3 lpDDS,POINT *points,int npoints,COLORREF c,int width);
DWORD MakeSurfaceRGB( LPDIRECTDRAWSURFACE lpDDS, float r, float g, float b );
BOOL CreateRotatedSurfaces360(LPDIRECTDRAW lpDD,LPDIRECTDRAWSURFACE source,LPDIRECTDRAWSURFACE *dest,int totalframes);

#endif