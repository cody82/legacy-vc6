/**************************************************************************************************

Title:  DDRAW RotoZoomer Code
From :  Dallas Nutsch ynb53@ttu.edu
Desc :

		Header File for Roto Zoomer Interface and Fixedpoint math


Notes:

Revisions:

	6-1-98 First Release

Limitations:

	-No Perspective Correction
	-No 24- or 32- bit support yet (it just needs new scanout functions similar to  ScanOutLine16)

Disclaimer:

	THIS SOFTWARE IS NOT SUPPORTED. THE AUTHOR IS NOT RESPONSIBLE OR LIABLE FOR ANY USE OF THIS CODE.
	THE AUTHOR IS NOT LIABLE FOR ANY DAMAGE, MISUSE, OR BAD STUFF THAT HAPPENS WHEN YOU USE THIS 
	CODE.


  Fixedpoint Parts (C) SciTech Software

*************************************************************************************************/
#ifndef __DDROTATE_H
#define __DDROTATE_H

//Macro to set up DDSD struct

#define setupDDSD(ddsd) ZeroMemory(&ddsd, sizeof(ddsd)); \
			            ddsd.dwSize = sizeof(ddsd);



//This stuff from the very cool SciTech company

typedef	long	FXFixed;			/* 16.16 format					*/
typedef long     real;	/* 16.16 format					*/

#define FXceil(f)	((FXFixed)(((f) + 0xFFFFL) & 0xFFFF0000L))
#define FXfloor(f)	((FXFixed)((f) & 0xFFFF0000L))
#define FXround(f)	((FXFixed)(((f) + 0x8000L) & 0xFFFF0000L))

/* Conversion operations. These can be done quickly inline. */

#define	FXintToReal(i)		((FXFixed)(i) << 16)
#define	FXintToZFixed(i)	((FXZFixed)(i) << 28)
#define	FXfixedToReal(f)	(f)
#define	FXzfixedToReal(f)	((f) >> 12)
#define	FXdblToReal(d)		((FXFixed)((d) * 65536.0 + 0.5))
#define	FXfltToReal(f)		((FXFixed)((f) * 65536.0 + 0.5))
#define	FXrealToInt(f)		((int)((f) >> 16))
#define	FXzfixedToInt(f)	((int)((f) >> 28))
#define	FXrndToInt(f)		((int)(((f) + 0x8000L) >> 16))
#define	FXrealToFixed(f)	(f)
#define	FXrealToFlt(f)		((float)((f) / 65536.0))
#define	FXrealToDbl(f)		((double)((f) / 65536.0))
#define	FXrealToZFixed(f)	((f) << 12)

FXFixed FXmul (FXFixed a, FXFixed b);
FXFixed FXdiv (FXFixed a, FXFixed b);

void DrawRotatedZoomed(LPDIRECTDRAWSURFACE src, LPDIRECTDRAWSURFACE dest,
					          RECT & srcrect, RECT & destclip,
					          int X, int Y, float Angle, float xzoom, float yzoom,
						      bool ReCenter=true);

#endif