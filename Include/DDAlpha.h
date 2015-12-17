#ifndef __DDALPHA_H
#define __DDALPHA_H
//Macro to set up DDSD struct

#define setupDDSD(ddsd) ZeroMemory(&ddsd, sizeof(ddsd)); \
			            ddsd.dwSize = sizeof(ddsd);
#define setupDDCAPS(ddcap) ZeroMemory(&ddcap, sizeof(ddcap)); \
			            ddcap.dwSize = sizeof(ddcap);




//These Globals in DDAlpha.CPP

int BuildAlphaTable (LPDIRECTDRAWSURFACE lpFront);

void DestroyAlphaTable (void);


int DrawAlpha( LPDIRECTDRAWSURFACE src, LPDIRECTDRAWSURFACE dest,
					   RECT & SrcRect, RECT & destclip, int X, int Y, bool ReCenter=TRUE);


//extern void GlobalError (char * str,...);
//extern HANDLE GError;

//extern void DDError(HRESULT hErr, void* hWnd);

//extern BYTE * g_RemapTable;


//These globals in DDUTIL.CPP

/*
#ifdef __cplusplus
extern "C" {            
#endif	

extern IDirectDrawPalette * DDLoadPalette(IDirectDraw2 *pdd, LPCSTR szBitmap);
extern IDirectDrawSurface * DDLoadBitmap(IDirectDraw2 *pdd, LPCSTR szBitmap, int dx, int dy);
extern HRESULT              DDReLoadBitmap(IDirectDrawSurface *pdds, LPCSTR szBitmap);
extern HRESULT              DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy);
extern DWORD                DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb);
extern HRESULT              DDSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb);

#ifdef __cplusplus
}
#endif	*/
#endif