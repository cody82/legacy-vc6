/////////////////////////////////////////////////////////////////////////////////////
// TEXTURE class
/////////////////////////////////////////////////////////////////////////////////////
#define D3D_OVERLOADS

#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include <d3d.h>
#include "texture.h"

/////////////////////////////////////////////////////////////////////////////////////
// DEBUG junk
/////////////////////////////////////////////////////////////////////////////////////
#if defined(DEBUG) || defined(_DEBUG)
static void DPF(char *fmt, ...)
{
    char ach[128];
    va_list va;
    va_start( va, fmt );
    wvsprintf( ach, fmt, va );
    va_end( va );
    OutputDebugString("TEXTURE: ");
    OutputDebugString(ach);
    OutputDebugString("\r\n");
}
#else
#define DPF if (0) 
#endif

typedef struct tagPixelConvertInfo
{
	BYTE * lpStartPos;		// Start of raw pixels
	BYTE * lpCurrLine;		// Current line start pos
	BYTE * lpCurrPos;		// Current pixel pos 

	DWORD x;			// current x position
	DWORD y;			// current y position
	DWORD w;			// Width
	DWORD h;			// Height
	long  pitch;		// Actual width in video memory
	
	// Red channel Info
	DWORD rMask;		// bit mask
	DWORD rBits;		// # of bits in mask
	DWORD rShift;		// # of bits to shift down to canonical position

	// Green channel info
	DWORD gMask;		// bit mask
	DWORD gBits;		// # of bits in mask
	DWORD gShift;		// # of bits to shift down to canonical position

	// Blue channel Info
	DWORD bMask;		// bit mask
	DWORD bBits;		// # of bits in mask
	DWORD bShift;		// # of bits to shift down to canonical position

	// Alpha channel info
	DWORD aMask;		// bit mask
	DWORD aBits;		// # of bits in mask
	DWORD aShift;		// # of bits to shift down to canonical position

} PixelConvertInfo;
typedef PixelConvertInfo * LPPixelConvertInfo;

typedef void (FAR PASCAL * LPWRITECALLBACK)(LPPixelConvertInfo ppci, DWORD toWrite);

void FAR PASCAL Write8 (LPPixelConvertInfo ppci, DWORD dwColor);
void FAR PASCAL Write16 (LPPixelConvertInfo ppci, DWORD dwColor);
void FAR PASCAL Write24 (LPPixelConvertInfo ppci, DWORD dwColor);
void FAR PASCAL Write32 (LPPixelConvertInfo ppci, DWORD dwColor);

BOOL  InitMaskInfo (LPDDSURFACEDESC pddsd, LPPixelConvertInfo ppci);
DWORD ConvertColor (LPPixelConvertInfo ppci, DWORD color);

/////////////////////////////////////////////////////////////////////////////////////
// ChooseTextureFormat
/////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	DWORD bpp;
	DDPIXELFORMAT ddpf;
} FindTextureData;

HRESULT CALLBACK FindTextureCallback (DDSURFACEDESC *DeviceFmt, LPVOID lParam)
{
    FindTextureData * FindData = (FindTextureData *)lParam;
    DDPIXELFORMAT ddpf = DeviceFmt->ddpfPixelFormat;

    DPF("FindTexture: %d %s%s%s %08X %08X %08X %08X", 
	ddpf.dwRGBBitCount, 
        (ddpf.dwFlags & (DDPF_ALPHA|DDPF_ALPHAPIXELS)) ? "ALPHA " : "", 
        (ddpf.dwFlags &	(DDPF_RGB)) ? "RGB " : "", 
        (ddpf.dwFlags &	(DDPF_PALETTEINDEXED8 | DDPF_PALETTEINDEXED4)) ? "PAL " : "", 
	ddpf.dwRBitMask,
	ddpf.dwGBitMask,
	ddpf.dwBBitMask,
	ddpf.dwRGBAlphaBitMask);

    //
    // we use GetDC/BitBlt to init textures so we only
    // want to use formats that GetDC will support.
    //
    if (ddpf.dwFlags & (DDPF_ALPHA|DDPF_ALPHAPIXELS))
        return DDENUMRET_OK;

    if (ddpf.dwRGBBitCount <= 8 &&
        !(ddpf.dwFlags & (DDPF_PALETTEINDEXED8 | DDPF_PALETTEINDEXED4)))
        return DDENUMRET_OK;

    if (ddpf.dwRGBBitCount > 8 && !(ddpf.dwFlags & DDPF_RGB))
        return DDENUMRET_OK;

    //
    // BUGBUG GetDC does not work for 1 or 4bpp YET!
    //
    if (ddpf.dwRGBBitCount < 8)
        return DDENUMRET_OK;

    //
    // keep the texture format that is nearest to the bitmap we have
    //
    if (FindData->ddpf.dwRGBBitCount == 0 ||
       (ddpf.dwRGBBitCount >= FindData->bpp &&
       (UINT)(ddpf.dwRGBBitCount - FindData->bpp) < (UINT)(FindData->ddpf.dwRGBBitCount - FindData->bpp)))
    {
        FindData->ddpf = ddpf;
    }

    return DDENUMRET_OK;
}


HRESULT CALLBACK FindAlphaTextureCallback (DDSURFACEDESC *DeviceFmt, LPVOID lParam)
{
    FindTextureData * FindData = (FindTextureData *)lParam;
    DDPIXELFORMAT ddpf = DeviceFmt->ddpfPixelFormat;

    DPF("FindTexture: %d %s%s%s %08X %08X %08X %08X", 
	ddpf.dwRGBBitCount, 
        (ddpf.dwFlags & (DDPF_ALPHA|DDPF_ALPHAPIXELS)) ? "ALPHA " : "", 
        (ddpf.dwFlags &	(DDPF_RGB)) ? "RGB " : "", 
        (ddpf.dwFlags &	(DDPF_PALETTEINDEXED8 | DDPF_PALETTEINDEXED4)) ? "PAL " : "", 
	ddpf.dwRBitMask,
	ddpf.dwGBitMask,
	ddpf.dwBBitMask,
	ddpf.dwRGBAlphaBitMask);

	// No Alpha Only formats
	// No ZBuffer only formats
	// No YUV formats
	// No RGBZ formats
	// No FourCC formats
	if (ddpf.dwFlags & (DDPF_ALPHA | DDPF_ZBUFFER |
		                DDPF_YUV | DDPF_ZPIXELS | DDPF_FOURCC))
        return DDENUMRET_OK;

	// We only want RGB formats for now !!!
    if (! (ddpf.dwFlags & DDPF_RGB))
        return DDENUMRET_OK;

	// We only want texture formats with an alpha channel
    if (! (ddpf.dwFlags & DDPF_ALPHAPIXELS))
        return DDENUMRET_OK;

	// We don't want palettized textures
    if (ddpf.dwFlags & (DDPF_PALETTEINDEXED8 | DDPF_PALETTEINDEXED4 | 
		                DDPF_PALETTEINDEXED2 | DDPF_PALETTEINDEXED1))
        return DDENUMRET_OK;

	// We don't support less than 8 bits per pixel
	if (ddpf.dwRGBBitCount < 8)
		return DDENUMRET_OK;

    //
    // keep the alpha texture format with the largest
	// alpha channel
    //
    if ((FindData->ddpf.dwAlphaBitDepth == 0) ||
	    (ddpf.dwAlphaBitDepth > FindData->ddpf.dwAlphaBitDepth))
    {
        FindData->ddpf = ddpf;
    }

    return DDENUMRET_OK;
}

void ChooseTextureFormat(IDirect3DDevice2 *Device, DWORD bpp, DDPIXELFORMAT *pddpf)
{
    FindTextureData FindData;
    ZeroMemory(&FindData, sizeof(FindData));
    FindData.bpp = bpp;
    Device->EnumTextureFormats(FindTextureCallback, (LPVOID)&FindData);
    *pddpf = FindData.ddpf;

    DPF("ChooseTexture: %d %s%s%s %08X %08X %08X %08X", 
	pddpf->dwRGBBitCount, 
        (pddpf->dwFlags & (DDPF_ALPHA|DDPF_ALPHAPIXELS)) ? "ALPHA " : "", 
        (pddpf->dwFlags &	(DDPF_RGB)) ? "RGB " : "", 
        (pddpf->dwFlags &	(DDPF_PALETTEINDEXED8 | DDPF_PALETTEINDEXED4)) ? "PAL " : "", 
	pddpf->dwRBitMask,
	pddpf->dwGBitMask,
	pddpf->dwBBitMask,
	pddpf->dwRGBAlphaBitMask);
}

BOOL ChooseAlphaTextureFormat(IDirect3DDevice2 *Device, DDPIXELFORMAT *pddpf)
{
    FindTextureData FindData;
    ZeroMemory(&FindData, sizeof(FindData));

    Device->EnumTextureFormats (FindAlphaTextureCallback, (LPVOID)&FindData);
    *pddpf = FindData.ddpf;

	if (FindData.ddpf.dwAlphaBitDepth == 0)
		return FALSE;

    DPF("ChooseAlphaTexture: %d %s%s%s %08X %08X %08X %08X", 
	pddpf->dwRGBBitCount, 
        (pddpf->dwFlags &   (DDPF_ALPHAPIXELS)) ? "ALPHA " : "", 
        (pddpf->dwFlags &	(DDPF_RGB)) ? "RGB " : "", 
        (pddpf->dwFlags &	(DDPF_PALETTEINDEXED8 | DDPF_PALETTEINDEXED4)) ? "PAL " : "", 
	pddpf->dwRBitMask,
	pddpf->dwGBitMask,
	pddpf->dwBBitMask,
	pddpf->dwRGBAlphaBitMask);

	return TRUE;
}


/**************************************************************************
 PaletteFromBitmap
 **************************************************************************/

static IDirectDrawPalette * PaletteFromBitmap(IDirectDraw *DirectDraw, HBITMAP Bitmap)
{
    IDirectDrawPalette *    Palette = NULL;
    HDC                     BitmapDC;
    DWORD                   adw[256];
    int                     colors, i;

    //
    // get the color table from the DIBSection
    //
    BitmapDC = CreateCompatibleDC(NULL);
    SelectObject(BitmapDC, Bitmap);
    colors = GetDIBColorTable(BitmapDC, 0, 256, (RGBQUAD *)adw);
    DeleteDC(BitmapDC);

    if (colors != 0)
    {
        //
        // convert BGR to RGB (stupid IBM!)
        //
        for (i=0; i<colors; i++)
            adw[i] = RGB(GetBValue(adw[i]),GetGValue(adw[i]),GetRValue(adw[i]));

        //
        // create a DirectDraw palette for the texture.
        //
        DirectDraw->CreatePalette(colors <= 16 ? DDPCAPS_4BIT : DDPCAPS_8BIT,
            (PALETTEENTRY *)adw, &Palette, NULL);
    }

    return Palette;
}

/**************************************************************************
 GetDD

 get the IDirectDraw from a IDirect3DDevice, we need the DD
 to create surfaces.

 this function does not do a AddRef on the DirectDraw object
 (ie you dont need to Release)

 NOTE if your app has this around as a global you can use
 the global instead of this code.

 **************************************************************************/
static IDirectDraw * GetDD(IDirect3DDevice2 *Device)
{
    IDirectDraw *       DirectDraw;
    IDirectDrawSurface *Target;
    IDirectDrawSurface2*Target2;

    //
    // get the render target (we need it to get the IDirectDraw)
    //
    if (Device==NULL || Device->GetRenderTarget(&Target) != DD_OK)
        return NULL;

    //
    // get the DirectDraw object, but first we need a IDirectDrawSurface2
    //
    if (Target->QueryInterface(IID_IDirectDrawSurface2, (void**)&Target2) != DD_OK)
        return NULL;
    Target->Release();
    Target2->GetDDInterface((void**)&DirectDraw);
    Target2->Release();
    DirectDraw->Release();  // dont up ref count

    return DirectDraw;
}

/**************************************************************************
 TEXTURE::Load

 load a bitmap from the resource, or bmp file and create a
 D3D texture map

 **************************************************************************/

BOOL TEXTURE::Load(IDirect3DDevice2 *Device, char *BitmapName)
{
    BITMAP              bm;
    DDSURFACEDESC       ddsd;
    HBITMAP             Bitmap;
    IDirectDraw *       DirectDraw;

    DPF("TEXTURE::Load(%s)", BitmapName);

    //
    // we need a IDirectDraw so we can create a surface.
    //
    if ((DirectDraw = GetDD(Device)) == NULL)
        return FALSE;

    //
    // load the bitmap from a resource or file.
    //
    Bitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), BitmapName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    if (Bitmap == NULL)
        Bitmap = (HBITMAP)LoadImage(NULL, BitmapName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

    if (Bitmap == NULL)
        return FALSE;

    // free any existing texture.
    Release();

    GetObject(Bitmap, sizeof(bm), &bm);      // get size of bitmap

    //
    // find the best texture format to use.
    //
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ChooseTextureFormat(Device, bm.bmBitsPixel, &ddsd.ddpfPixelFormat);
    ddsd.dwFlags |= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.dwWidth = bm.bmWidth;
    ddsd.dwHeight = bm.bmHeight;

    //
    // create a video memory texture
    //
    // if we are dealing with a HAL create in video memory, else
    // create in system memory.
    //
    D3DDEVICEDESC hal, hel;
    ZeroMemory(&hal, sizeof(hal));
    hal.dwSize = sizeof(hal);
    ZeroMemory(&hel, sizeof(hel));
    hel.dwSize = sizeof(hel);
    Device->GetCaps(&hal, &hel);

    // BUGBUG should we check for texture caps?
    if (hal.dcmColorModel)
        ddsd.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD;
    else
        ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY| DDSCAPS_TEXTURE;

    if (DirectDraw->CreateSurface(&ddsd, &DeviceSurface, NULL) != DD_OK)
        goto error;

    //
    // create a system memory surface for the texture.
    //
    // we use this system memory surface for the ::Load call
    // and this surface does not get lost.
    //
    if (hal.dcmColorModel)
    {
        ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;

        if (DirectDraw->CreateSurface(&ddsd, &MemorySurface, NULL) != DD_OK)
            goto error;
    }
    else
    {
        //
        // when dealing with a SW rasterizer we dont need to make two
        // surfaces.
        //
        MemorySurface = DeviceSurface;
        DeviceSurface->AddRef();
    }

    //
    // create a palette for the texture
    //
    if (ddsd.ddpfPixelFormat.dwRGBBitCount <= 8)
    {
        Palette = PaletteFromBitmap(DirectDraw, Bitmap);

        //
        // now we have a palette, attach the palette to the Surface
        // and the texture
        //
        MemorySurface->SetPalette(Palette);
        DeviceSurface->SetPalette(Palette);
    }

    //
    // copy the bitmap to our surface
    //
    if (!Copy(Bitmap))
        goto error;

    //
    // get the texture handle
    //
    IDirect3DTexture2 *	Texture;
    DeviceSurface->QueryInterface(IID_IDirect3DTexture2, (void**)&Texture);
    Texture->GetHandle(Device, &Handle);
    Texture->Release();

    //
    // we are done, delete the bitmap (we made a copy) and return.
    //
    DeleteObject(Bitmap);
    return TRUE;

error:
    if (Bitmap)
        DeleteObject(Bitmap);
    Release();
    return FALSE;
}

/**************************************************************************
 TEXTURE::Copy

 init the system memory surface from a GDI Bitmap

 **************************************************************************/

BOOL TEXTURE::Copy(HBITMAP Bitmap)
{
    BITMAP  bm;
    HDC     BitmapDC;
    HDC     SurfaceDC;
    BOOL    result = FALSE;

    DPF("TEXTURE::Copy");

    GetObject(Bitmap, sizeof(bm), &bm);    // get size of bitmap

    BitmapDC = CreateCompatibleDC(NULL);
    SelectObject(BitmapDC, Bitmap);

    if (MemorySurface->GetDC(&SurfaceDC) == DD_OK)
    {
        BitBlt(SurfaceDC, 0, 0, bm.bmWidth, bm.bmHeight, BitmapDC, 0, 0, SRCCOPY);
        MemorySurface->ReleaseDC(SurfaceDC);
        result = Restore();
    }
    DeleteDC(BitmapDC);
    return result;
}


/**************************************************************************
 TEXTURE::Restore

 restore the texture image

 **************************************************************************/

BOOL TEXTURE::Restore()
{
    HRESULT             err;
    IDirect3DTexture2  *MemoryTexture;
    IDirect3DTexture2  *DeviceTexture;

    DPF("TEXTURE::Restore");

    if (DeviceSurface == NULL || MemorySurface == NULL)
        return FALSE;

    //
    // we dont need to do this step for system memory surfaces.
    //
    if (DeviceSurface == MemorySurface)
        return TRUE;

    //
    // restore the video memory texture.
    //
    if (DeviceSurface->Restore() != DD_OK)
        return FALSE;

    //
    // call IDirect3DTexture::Load() to copy the texture to the device.
    //
    DeviceSurface->QueryInterface(IID_IDirect3DTexture2, (void**)&DeviceTexture);
    MemorySurface->QueryInterface(IID_IDirect3DTexture2, (void**)&MemoryTexture);

    err = DeviceTexture->Load (MemoryTexture);

    DeviceTexture->Release();
    MemoryTexture->Release();

    return err == DD_OK;
}

/**************************************************************************
 TEXTURE::Release

 free the texture, free all objects associated with this texture

 NOTE we cant do this in the destructor because DirectDraw
 will clean up all the surfaces when the main direct draw object
 is destroyed, before a static destructor will be called.

 **************************************************************************/

void TEXTURE::Release()
{
    DPF("TEXTURE::Release");

    if (MemorySurface)
       MemorySurface->Release();
    MemorySurface = 0;

    if (DeviceSurface)
       DeviceSurface->Release();
    DeviceSurface = 0;

    if (Palette)
       Palette->Release();
    Palette = 0;

    Handle = 0;
}


/*
**-----------------------------------------------------------------------------
** Alpha Texture Methods 
**-----------------------------------------------------------------------------
*/


/**************************************************************************
  TEXTURE::LoadAlpha

  Create a simple Alpha Gradient Texture
 
 **************************************************************************/

BOOL TEXTURE::LoadAlpha (IDirect3DDevice2 *Device)
{
    DDSURFACEDESC       ddsd;
    IDirectDraw *       DirectDraw;

    DPF("TEXTURE::LoadAlpha");

    //
    // we need a IDirectDraw so we can create a surface.
    //
    if ((DirectDraw = GetDD(Device)) == NULL)
        return FALSE;

    // free any existing texture.
    Release();

    //
    // find the best Alpha texture format to use.
    //
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    if (! ChooseAlphaTextureFormat (Device, &ddsd.ddpfPixelFormat))
	{
		// Unable to find valid Alpha Texture Format
		return FALSE;
	}
    ddsd.dwFlags |= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.dwWidth  = 128;
    ddsd.dwHeight = 128;

    //
    // create a video memory texture
    //
    // if we are dealing with a HAL create in video memory, else
    // create in system memory.
    //
    D3DDEVICEDESC hal, hel;
    ZeroMemory(&hal, sizeof(hal));
    hal.dwSize = sizeof(hal);
    ZeroMemory(&hel, sizeof(hel));
    hel.dwSize = sizeof(hel);
    Device->GetCaps(&hal, &hel);

    // BUGBUG should we check for texture caps?
    if (hal.dcmColorModel)
        ddsd.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD;
    else
        ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY| DDSCAPS_TEXTURE;

    if (DirectDraw->CreateSurface(&ddsd, &DeviceSurface, NULL) != DD_OK)
        goto error;

    //
    // create a system memory surface for the texture.
    //
    // we use this system memory surface for the ::Load call
    // and this surface does not get lost.
    //
    if (hal.dcmColorModel)
    {
        ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_TEXTURE;

        if (DirectDraw->CreateSurface(&ddsd, &MemorySurface, NULL) != DD_OK)
            goto error;
    }
    else
    {
        //
        // when dealing with a SW rasterizer we dont need to make two
        // surfaces.
        //
        MemorySurface = DeviceSurface;
        DeviceSurface->AddRef();
    }

	// No need for a palette
	Palette = NULL;

    //
    // Create Default Alpha Gradient Texture
    //
    if (! CreateDefaultAlpha ())
        goto error;

	//
	// Copy System Memory Surface to Video Memory Surface
	//
	Restore ();


    //
    // get the texture handle
    //
    IDirect3DTexture2 *	Texture;
    DeviceSurface->QueryInterface (IID_IDirect3DTexture2, (void**)&Texture);
    Texture->GetHandle (Device, &Handle);
    Texture->Release ();

	// Success
    return TRUE;

error:
	// Cleanup
    Release();
    return FALSE;
}



/**************************************************************************
 TEXTURE::CreateDefaultAlpha

  Creates a simple Default Alpha Texture

 **************************************************************************/

BOOL TEXTURE::CreateDefaultAlpha()
{
	BOOL					fResult = FALSE;
	HRESULT					hResult;
//	LPDIRECTDRAWSURFACE3	lpdds3 = NULL;
	DDSURFACEDESC			ddsd;
	PixelConvertInfo		pci;
	DWORD					dwColor;
	LPWRITECALLBACK			writeFunc = NULL;
	DWORD					r,g,b,a;
	int						yGrad, xGrad;

    DPF("TEXTURE::CreateDefaultAlpha");

	// Create Simple Gradient surface

	// Step 1.  Get Pixel Format
	if (! MemorySurface)
		return FALSE;

	// Get DirectDrawSurface3 Interface
//	hResult = MemorySurface->QueryInterface (IID_IDirectDrawSurface3, 
//											 (LPVOID)&lpdds3);

	// Get Pointer to surface
	ZeroMemory (&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof (ddsd);
	hResult = MemorySurface->Lock (NULL, 
								   &ddsd, 
								   DDLOCK_WAIT, 
								   NULL);
	if (FAILED (hResult))
		return FALSE;

	if ((! (ddsd.ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS)) ||
		(ddsd.ddpfPixelFormat.dwAlphaBitDepth == 0))
		goto lblFAILURE;

	// Step 2.  Init Conversion Masks
	if (! InitMaskInfo (&ddsd, &pci))
		goto lblFAILURE;

	// Step 3.  Choose Conversion functions based on bitdepth
	switch (ddsd.ddpfPixelFormat.dwRGBBitCount)
	{	
	case 4:
		// Note: We don't support this yet!!!
		goto lblFAILURE;
	
	case 8:
		writeFunc   = Write8;
		break;
	
	case 16:
		writeFunc   = Write16;
		break;
	
	case 24:
		writeFunc   = Write24;
		break;

	case 32:
		writeFunc   = Write32;
		break;
	
	default:
		// Unknown Bit Depth
		goto lblFAILURE;
	}

	pci.lpStartPos = (BYTE *)(void *)ddsd.lpSurface;
//	pci.lpCurrLine = ddsd.lpSurface;
//	pci.lpCurrPos  = ddsd.lpSurface;

//	pci.x	  = 0;
//	pci.y	  = 0;
	pci.w     = ddsd.dwWidth;
	pci.h	  = ddsd.dwHeight;
	pci.pitch = ddsd.lPitch;


	// Step 5.  Make default Gradient bitmap
	pci.y = 0;
	pci.lpCurrLine = pci.lpStartPos;
	while (pci.y < pci.h)
	{
		yGrad = (int)(((float)pci.y/(float)pci.h) * 255.0f);
		pci.x = 0;
		pci.lpCurrPos = pci.lpCurrLine;
		while (pci.x < pci.w)
		{			
			// Get Gradient color
			xGrad = (int)(((float)pci.x/(float)pci.w) * 255.0f);

			r = (DWORD)(xGrad + yGrad)/2 & 0xFF;
			g = (DWORD)((255 - xGrad) + yGrad)/2 & 0xFF;
			b = (DWORD)(xGrad + (255 - yGrad)) & 0xFF;
			a = (DWORD)(xGrad + yGrad)/2 & 0xFF;

			dwColor = ((a << 24) | (r << 16) | (g << 8) | b);

			// Convert color to current pixel format
			dwColor = ConvertColor (&pci, dwColor);

			// Write Pixel
			(*writeFunc)(&pci, dwColor);
			pci.x++;
		}

		// Move to next line
		pci.lpCurrLine += pci.pitch;
		pci.y++;
	}

	// Success
	fResult = TRUE;

lblFAILURE:
	// Cleanup
	hResult = MemorySurface->Unlock (ddsd.lpSurface);
	if (FAILED (hResult))
	{
		// Error, do nothing
	}

	return fResult;
}



BOOL InitMaskInfo (LPDDSURFACEDESC pddsd, LPPixelConvertInfo ppci)
{
	DWORD dwMask;
	DWORD dwBitMask;
	DWORD dwShift;
	DWORD dwBits;

	// Check Parameters
	if ((! pddsd) || (! ppci))
		return FALSE;

	// Get Red Mask info
	dwMask = pddsd->ddpfPixelFormat.dwRBitMask;
	if (0L == dwMask)
	{
		dwBits  = 0;
		dwShift = 0;
	}
	else
	{
		// Count number of bits til first bit in mask
		dwBitMask = 1;
		dwShift = 0;
		while (! (dwMask & dwBitMask))
		{
			dwBitMask <<= 1;
			dwShift++;
		}

		// Count number of bits in mask
		dwBits = 0;
		while (dwMask & dwBitMask)
		{
			dwBitMask <<= 1;
			dwBits++;
		}

		if (dwBits > 8)
			return FALSE;
	}

	ppci->rMask  = dwMask;
	ppci->rBits  = dwBits;
	ppci->rShift = dwShift;
	

	// Get Green Mask info
	dwMask = pddsd->ddpfPixelFormat.dwGBitMask;
	if (0L == dwMask)
	{
		dwBits  = 0;
		dwShift = 0;
	}
	else
	{
		// Count number of bits til first bit in mask
		dwBitMask = 1;
		dwShift = 0;
		while (! (dwMask & dwBitMask))
		{
			dwBitMask <<= 1;
			dwShift++;
		}

		// Count number of bits in mask
		dwBits = 0;
		while (dwMask & dwBitMask)
		{
			dwBitMask <<= 1;
			dwBits++;
		}

		if (dwBits > 8)
			return FALSE;
	}

	ppci->gMask  = dwMask;
	ppci->gBits  = dwBits;
	ppci->gShift = dwShift;


	// Get Blue Mask info
	dwMask = pddsd->ddpfPixelFormat.dwBBitMask;
	if (0L == dwMask)
	{
		dwBits  = 0;
		dwShift = 0;
	}
	else
	{
		// Count number of bits til first bit in mask
		dwBitMask = 1;
		dwShift = 0;
		while (! (dwMask & dwBitMask))
		{
			dwBitMask <<= 1;
			dwShift++;
		}

		// Count number of bits in mask
		dwBits = 0;
		while (dwMask & dwBitMask)
		{
			dwBitMask <<= 1;
			dwBits++;
		}

		if (dwBits > 8)
			return FALSE;
	}

	ppci->bMask  = dwMask;
	ppci->bBits  = dwBits;
	ppci->bShift = dwShift;


	// Get Alpha Mask info
	dwMask = pddsd->ddpfPixelFormat.dwRGBAlphaBitMask;
	if (0L == dwMask)
	{
		dwBits  = 0;
		dwShift = 0;
	}
	else
	{
		// Count number of bits til first bit in mask
		dwBitMask = 1;
		dwShift = 0;
		while (! (dwMask & dwBitMask))
		{
			dwBitMask <<= 1;
			dwShift++;
		}

		// Count number of bits in mask
		dwBits = 0;
		while (dwMask & dwBitMask)
		{
			dwBitMask <<= 1;
			dwBits++;
		}

		if (dwBits > 8)
			return FALSE;
	}

	ppci->aMask  = dwMask;
	ppci->aBits  = dwBits;
	ppci->aShift = dwShift;

	// Success
	return TRUE;
} // End InitConvertInfo


DWORD ConvertColor (LPPixelConvertInfo ppci, DWORD dwColor)
{
	DWORD r, g, b, a;

	// Convert Red component
	r = (dwColor >> 16) & 0xFF;			// Convert to Byte
	r >>= (DWORD)(8 - ppci->rBits);		// throw away low precision bits
	r <<= ppci->rShift;					// move to new position

	// Convert Green component
	g = (dwColor >> 8) & 0xFF;
	g >>= (DWORD)(8 - ppci->gBits);
	g <<= ppci->gShift;

	// Convert Blue component
	b = dwColor & 0xFF;
	b >>= (DWORD)(8 - ppci->bBits);
	b <<= ppci->bShift;

	// Convert Alpha component
	a = (dwColor >> 24) & 0xFF;
	a >>= (DWORD)(8 - ppci->aBits);
	a <<= ppci->aShift;

	// Return converted color
	return (r | g | b | a);
} // End ConvertColor


void FAR PASCAL Write8 (LPPixelConvertInfo ppci, DWORD dwColor)
{
	dwColor &= 0xFF;
	*(ppci->lpCurrPos) = (BYTE)dwColor;
	ppci->lpCurrPos++;
}

void FAR PASCAL Write16 (LPPixelConvertInfo ppci, DWORD dwColor)
{
	dwColor &= 0xFFFF;
	*((WORD *)ppci->lpCurrPos) = (WORD)dwColor;
	ppci->lpCurrPos += 2;
}

void FAR PASCAL Write24 (LPPixelConvertInfo ppci, DWORD dwColor)
{
	BYTE * lpColor = (BYTE *)&dwColor;

	dwColor &= 0xFFFFFF;
	*(ppci->lpCurrPos++) = *lpColor++;
	*(ppci->lpCurrPos++) = *lpColor++;
	*(ppci->lpCurrPos++) = *lpColor++;
}

void FAR PASCAL Write32 (LPPixelConvertInfo ppci, DWORD dwColor)
{
	*((DWORD *)ppci->lpCurrPos) = (WORD)dwColor;
	ppci->lpCurrPos += 4;
}


