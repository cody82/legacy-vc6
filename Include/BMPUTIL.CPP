#include "bmputil.h"

HDIB ReadDIBFileInFile(HANDLE hfile,DWORD begin,DWORD size)
{
	BITMAPFILEHEADER bmfHeader;
	//DWORD dwBitsSize;
	HDIB hDIB;
	LPSTR pDIB;
	//HANDLE hFile;
	DWORD nBytesRead;
	DWORD dw;

	if(size==0)
		size=GetFileSize(hfile,NULL)-begin;

	//dwBitsSize = GetFileSize(hFile,NULL);
	SetFilePointer(hfile,(LONG)begin,NULL,FILE_BEGIN);

	/*
	 * Go read the DIB file header and check if it's valid.
	 */
	// attempt an asynchronous read operation

	if(! ReadFile(hfile, (LPSTR)&bmfHeader, sizeof(bmfHeader), &nBytesRead,
		 NULL))
	{
		dw=GetLastError();
		return NULL;
	}

	if (bmfHeader.bfType != DIB_HEADER_MARKER)
		return NULL;

	/*
	 * Allocate memory for DIB
	 */
	hDIB = (HDIB) ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size);
	if (hDIB == 0)
	{
		return NULL;
	}
	pDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);

	/*
	 * Go read the bits.
	 */
	if(!ReadFile(hfile, (LPSTR)pDIB, size - sizeof(BITMAPFILEHEADER), &nBytesRead, NULL))
	{
		::GlobalUnlock((HGLOBAL) hDIB);
		::GlobalFree((HGLOBAL) hDIB);
		return NULL;
	}
	::GlobalUnlock((HGLOBAL) hDIB);
	//CloseHandle(hfile);
	return hDIB;
}

LPDIRECTDRAWSURFACE LoadBmpInFile(IDirectDraw *pdd, HANDLE hfile,DWORD begin,DWORD size)
{
    HBITMAP             hbm;
    BITMAP              bm;
    DDSURFACEDESC       ddsd;
	HDIB hdib;
    IDirectDrawSurface *pdds;

    //
    //  try to load the bitmap as a resource, if that fails, try it as a file
    //

	hdib=ReadDIBFileInFile(hfile,begin,size);
	hbm=BitmapFromDib((HANDLE)hdib,NULL);
	delete hdib;

    if (hbm == NULL)
	return NULL;

    //
    // get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap

    //
    // create a DirectDrawSurface for this bitmap
    //
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth = bm.bmWidth;
    ddsd.dwHeight = bm.bmHeight;

    if (pdd->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
	return NULL;

    DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);

    DeleteObject(hbm);

    return pdds;


}

HBITMAP LoadBmpInFile(HANDLE hfile,DWORD begin,DWORD size)
{
	HBITMAP hbm;
	HDIB hdib;

	hdib=ReadDIBFileInFile(hfile,begin,size);
	if(hdib==NULL)return NULL;
	hbm=BitmapFromDib((HANDLE)hdib,NULL);

	//delete hdib;
	//GlobalUnlock((HGLOBAL)hdib);
	GlobalFree((HGLOBAL) hdib);

	return hbm;

}

