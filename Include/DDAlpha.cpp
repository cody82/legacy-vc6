#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#define DIRECTDRAW_VERSION 0x0100
#include <DDRAW.H>
#include "DDAlpha.H"


BYTE * g_RemapTable = NULL;
void Clip(int *DestX, int *DestY, RECT *SrcRect, RECT *DestRect);


/************************************************************************
Function: BuildAlphaTable
Description:

  Builds an 8-bit alpha LUT

  This brute force technique takes a wile.  There are faster ways to find 
  the closes color, but I'm not gonna go into that.

************************************************************************/

int BuildAlphaTable (LPDIRECTDRAWSURFACE lpFront)
{

	DDSURFACEDESC ddsd;
	IDirectDrawPalette * pal;
	PALETTEENTRY palentries [256];
	HRESULT rval;

	if (lpFront == NULL) return 0;

	setupDDSD (ddsd);

	rval = lpFront -> GetSurfaceDesc (&ddsd);
	if (rval != DD_OK) 
	{
		return 0;
	}

	if (ddsd.ddpfPixelFormat.dwRGBBitCount != 8)
	{
		//Not an 8-bit front buffer so just return
		return 0;
	}

	rval = lpFront -> GetPalette (&pal);
	if (rval != DD_OK) 
	{
		return 0;
	}
	rval = pal -> GetEntries (0,0,256,palentries);
	if (rval != DD_OK) 
	{
		return 0;
	}

	g_RemapTable = new BYTE [256*256];

	int xloop, yloop, cloop;
	double error;
	double cerror;
	int cindex;
	int r,g,b;
	for (xloop=0;xloop<256;xloop++)
	for (yloop=xloop;yloop<256;yloop++)
	{
		r = ((int)palentries [xloop] . peRed + (int)palentries [yloop] . peRed)>>1;
		g = ((int)palentries [xloop] . peGreen + (int)palentries [yloop] . peGreen)>>1;
		b = ((int)palentries [xloop] . peBlue + (int)palentries [yloop] . peBlue)>>1;

		cindex = 0;//DDColorMatch (lpFront,RGB (r,g,b));
		
		error = 65536*3;
		for (cloop = 0;cloop < 256;cloop++)
		{
		//	cerror =  (double)log(1+fabs(r-(int)palentries [cloop] . peRed))+
		//		      (double)log(1+fabs(g-(int)palentries [cloop] . peGreen))+
		//			  (double)log(1+fabs(b-(int)palentries [cloop] . peBlue));
			cerror =  (double)fabs(r-(int)palentries [cloop] . peRed)+
				      (double)fabs(g-(int)palentries [cloop] . peGreen)+
					  (double)fabs(b-(int)palentries [cloop] . peBlue);


			if (cerror < error)
			{
				error = cerror;
				cindex = cloop;
			}
		}
		
		g_RemapTable [xloop*256+yloop] = cindex;
		g_RemapTable [yloop*256+xloop] = cindex;

	}
	return -1;
}

void DestroyAlphaTable (void)
{
	if (g_RemapTable != NULL) delete [] g_RemapTable;
}



/************************************************************************
Function: DrawAlpha
Description:

  8,16,24,32 bit Alpha Blener

  For 8-bit Be sure to call BuildAlphaTable(); first


************************************************************************/
int DrawAlpha( LPDIRECTDRAWSURFACE src, LPDIRECTDRAWSURFACE dest,
					   RECT & SrcRect, RECT & destclip, int X, int Y, bool ReCenter)

{
 DDSURFACEDESC ddsd;

 HRESULT rval;
 RECT ModSrc,ModDest;

 BYTE * SrcData;
 BYTE * DestData;
 int SrcPitch,DestPitch, xloop,yloop;

 MoveMemory (&ModSrc, &SrcRect, sizeof (RECT));

	if (dest==NULL)
	{
//		GlobalError ("DrawAlpha - dest = NULL\n");
		return 0;
	}
	if (src==NULL)
	{
//		GlobalError ("DrawAlpha - lsrc = NULL\n");
		return 0;
	}

	//This function clips the modsrc rectangel and changes the x,y coords directly on the stack to fit in destrect

	Clip(&X, &Y, &ModSrc, &destclip);

	//See if bitmap was fully cliped

	if (ModSrc . right - ModSrc . left <= 0) return 0;
	if (ModSrc . bottom - ModSrc . top <= 0) return 0;

	ModDest . left = ModSrc. left + X;
	ModDest . top = ModSrc. top + Y;
	ModDest . right = ModSrc. right + X;
	ModDest . bottom = ModSrc. bottom + Y;

	//Lock src and dest surfaces

	setupDDSD (ddsd);
	rval = src -> Lock (NULL,&ddsd,DDLOCK_WAIT,0);
	SrcData = (BYTE *) ddsd . lpSurface;
	SrcPitch = ddsd . lPitch;

	setupDDSD (ddsd);
	rval = dest -> Lock (NULL,&ddsd,DDLOCK_WAIT,0);
	DestData =  (BYTE *) ddsd . lpSurface;
	DestPitch = ddsd . lPitch;


	setupDDSD (ddsd);
    rval = dest->GetSurfaceDesc (&ddsd);

	if (ddsd.ddpfPixelFormat.dwRGBBitCount==8)
	{
		//8-bit Alpha Blend
		if (g_RemapTable == NULL)// return 0; //return if table hasn't been created
			BuildAlphaTable(dest);

		//Initialize pointers

		SrcData += ModSrc . top * SrcPitch + ModSrc . left;
		DestData += ModDest . top * DestPitch + ModDest . left;

		for (yloop = 0; yloop < ModDest . bottom - ModDest . top; yloop++)
		{
			for (xloop = 0; xloop < ModSrc . right - ModSrc . left; xloop++)
			{
				*(DestData+xloop) = g_RemapTable[(((int)*(SrcData+xloop)) <<8)+ (int)*(DestData+xloop)];
			}
			DestData += DestPitch;
			SrcData  += SrcPitch;
		}
		
	}
	else if (ddsd.ddpfPixelFormat.dwRGBBitCount==16)
	{
		//Initialize pointers

		SrcData += ModSrc . top * SrcPitch + ModSrc . left*2;
		DestData += ModDest . top * DestPitch + ModDest . left*2;

			if (ddsd .ddpfPixelFormat . dwGBitMask ==  0x07E0) //If 16-bit (5,6,5)
			  {

				//Loop through source pixels

				for (yloop = 0; yloop < ModDest . bottom - ModDest . top; yloop++)
				{
					for (xloop = 0; xloop < 2*(ModSrc . right - ModSrc . left); xloop+=2)
					{
						__asm
						{
							push esi                           // save for c++
							push edi                           // save for c++
 
							mov esi,  SrcData                  // Get pointer to source pixel
							add esi, xloop                     // add the index

							mov edi,  DestData                 // Get pointer to dest pixel
							add edi, xloop                     // add the index

							movzx eax, WORD PTR [esi]          // Get source pixel
							movzx ebx, WORD PTR [edi]          // Get dest pixel

							push eax                           //Copy both pixels twice
							push ebx
							push eax 
							push ebx

							and eax, 0x1f;                     //Mask out unwanted bits
							and ebx, 0x1f
				
							add eax, ebx                       //Add components together
							shr eax, 1                         //divide by two to average
							mov edx, eax                       //store component in edx

							pop ebx                            //Restore pixels and start next component
							pop eax

							shr eax, 5
							shr ebx, 5
							and eax, 0x3f
							and ebx, 0x3f

							add eax, ebx
							shr eax, 1
							shl eax, 5
							or edx, eax                       //Or this component (green) with the blue one

							pop ebx                           //Now restore colors for red component
							pop eax

							shr eax, 11
							shr ebx, 11	
							and eax, 0x1f
							and ebx, 0x1f

							add eax, ebx
							shr eax, 1
							shl eax, 11
							or edx, eax

							mov WORD PTR [edi], dx

							pop edi
							pop esi
						}
					}
					DestData += DestPitch;
					SrcData  += SrcPitch;
				}
			}
			else //15-bit (5,5,5)
			{
				for (yloop = 0; yloop < ModDest . bottom - ModDest . top; yloop++)
				{
					for (xloop = 0; xloop < 2*(ModSrc . right - ModSrc . left); xloop+=2)
					{
						__asm
						{
							push esi
							push edi 

							mov esi,  SrcData
							add esi, xloop

							mov edi,  DestData
							add edi, xloop

							movzx eax, WORD PTR [esi]
							movzx ebx, WORD PTR [edi]

							push eax
							push ebx
							push eax 
							push ebx

							and eax, 0x1f;
							and ebx, 0x1f
				
							add eax, ebx
							shr eax, 1
							mov edx, eax

							pop ebx
							pop eax

							shr eax, 5
							shr ebx, 5
							and eax, 0x1f
							and ebx, 0x1f

							add eax, ebx
							shr eax, 1
							shl eax, 5
							or edx, eax

							pop ebx
							pop eax

							shr eax, 10
							shr ebx, 10	
							and eax, 0x1f
							and ebx, 0x1f

							add eax, ebx
							shr eax, 1
							shl eax, 10
							or edx, eax

							mov WORD PTR [edi], dx

							pop edi
							pop esi
						}
					}
					DestData += DestPitch;
					SrcData  += SrcPitch;
				}
			}

	}
	else if (ddsd.ddpfPixelFormat.dwRGBBitCount==24)
	{
		//Initialize pointers

		SrcData += ModSrc . top * SrcPitch + ModSrc . left*4;
		DestData += ModDest . top * DestPitch + ModDest . left*4;

		for (yloop = 0; yloop < ModDest . bottom - ModDest . top; yloop++)
		{
			for (xloop = 0; xloop < 3*(ModSrc . right - ModSrc . left); xloop+=3)
			{
				__asm
				{
					push esi
					push edi

					mov esi,  SrcData
					add esi, xloop

					mov edi,  DestData
					add edi, xloop


					movsx al,  [esi]
					movsx bl,  [edi]

					add eax, ebx
					shr eax, 1
					mov [edi], al

					inc esi
					inc edi

					movsx al,  [esi]
					movsx bl,  [edi]

					add eax, ebx
					shr eax, 1
					mov [edi], al

					inc esi
					inc edi

					movsx al,  [esi]
					movsx bl,  [edi]

					add eax, ebx
					shr eax, 1
					mov [edi], al

					inc esi
					inc edi



					pop edi
					pop esi

				}
			}
			DestData += DestPitch;
			SrcData  += SrcPitch;
		}

	}
	else if (ddsd.ddpfPixelFormat.dwRGBBitCount==32)
	{
		//Initialize pointers

		SrcData += ModSrc . top * SrcPitch + ModSrc . left*4;
		DestData += ModDest . top * DestPitch + ModDest . left*4;

		for (yloop = 0; yloop < ModDest . bottom - ModDest . top; yloop++)
		{
			for (xloop = 0; xloop < 4*(ModSrc . right - ModSrc . left); xloop+=4)
			{
				__asm
				{
					push esi
					push edi

					mov esi,  SrcData
					add esi, xloop

					mov edi,  DestData
					add edi, xloop

					mov eax,  [esi]
					mov ebx,  [edi]


					push eax
					push ebx
					push eax 
					push ebx

					and eax, 0xff
					and ebx, 0xff
		
					add eax, ebx
					shr eax, 1
					mov edx, eax

					pop ebx
					pop eax

					shr eax, 8
					shr ebx, 8
					and eax, 0xff
					and ebx, 0xff

					add eax, ebx
					shr eax, 1
					shl eax, 8
					or edx, eax

					pop ebx
					pop eax

					shr eax, 16
					shr ebx, 16	
					and eax, 0xff
					and ebx, 0xff

					add eax, ebx
					shr eax, 1
					shl eax, 16
					or edx, eax

					mov [edi], edx

					pop edi
					pop esi

				}
			}
			DestData += DestPitch;
			SrcData  += SrcPitch;
		}

	}


	rval = dest -> Unlock(NULL);
	rval = src -> Unlock(NULL);


	return -1;
}

/************************************************************************
Function: Clip
Description:


  Clips a source rectange and coords to a dest rectangle and coords
  Thanks to Danny Farley aka CDX

************************************************************************/
void Clip(int *DestX, int *DestY, RECT *SrcRect, RECT *DestRect)
{
	// If it's partly off the right side of the screen
	if(*DestX + (SrcRect->right - SrcRect->left) > DestRect->right)
		SrcRect->right -= *DestX + (SrcRect->right-SrcRect->left) - DestRect->right;

	// Partly off the left side of the screen
	if(*DestX < DestRect->left)
	{
		SrcRect->left += DestRect->left - *DestX;
		*DestX = DestRect->left;
	}

	// Partly off the top of the screen
	if(*DestY < DestRect->top)
	{
		SrcRect->top += DestRect->top - *DestY;
		*DestY = DestRect->top;
	}

	// If it's partly off the bottom side of the screen
	if(*DestY + (SrcRect->bottom - SrcRect->top) > DestRect->bottom)
	SrcRect->bottom -= ((SrcRect->bottom-SrcRect->top)+*DestY) - DestRect->bottom;

	return;
}



/*
DirectDraw is a trademark of Microsoft Corp.
*/