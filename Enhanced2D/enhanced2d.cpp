//-----------------------------------------------------------------------------
//
// File: Enhanced2D.cpp		Date: 03/08/1999	for DirectX 6.0 / 6.1
//
// Copyright (C) 1999 by Tobias M. Lensing - All rights reserved
//
// Note: This is free software. Permission to copy, modify and distribute this
//       code freely for non-commercial and commercial purposes is hereby
//       granted as long as the above copyright note is included with the
//       product. Reselling this source code is strictly forbidden!
//
//       This application may be used under the terms of the GNU Library
//       General Public License which is included to the project package.
//
// This software shows how to combine DirectDraw Blitting with Direct3D
// Immediate Mode rendering to attain special effects like alphablending or
// interpolated lighting (with Gouraud Shading). The sample code is based on
// an image which is blitted in DirectDraw. Using Direct3D the sample draws
// a sprite with alphablending and lighting over the image.
//
// Please note that this code is based on the Direct3D Immediate Mode helper
// library from Microsoft (d3dframe.lib) which is linked with the LIB-Directory
// of this project. The d3dframe.lib should have come with your DirectX SDK and
// should be available in the samples D3DIM\LIB\-Directory. If you want to use
// your version of the d3dframe.lib please link it instead of my one (I have
// included the original one which might not be perfect for all purposes).
//
// This sample does also use the ddutil.h file which should also be available
// within your SDK's DirectDraw sample's include directory. If it is not,
// please tell me and I will help you (this should normally be not the case).
//
// BUGS: I have written this very quickly, because there were much people who
// were interested in my idea and wanted to see my source. Here it is, but
// I'm not sure that it is free of bugs. If you find anyone, please e-mail me.
// If you have any questions or comments, please don't hesitate to message me.
// Thanks. Hope that this sample will help you with all your wonderful 2D
// (and even 3D) games!
//
// Tobias M. Lensing					The Cyclon3D Project Web Site:
// e-mail: tobias.lensing@okay.net		http://members.tripod.de/~Cyclon
// ICQ: 22102329
//
//-----------------------------------------------------------------------------

#define D3D_OVERLOADS
#define STRICT
#include <math.h>
#include <stdio.h>
#include "D3DFrame.h"
#include "D3DTextr.h"
#include "D3DUtil.h"
#include "ddraw.h"
#include "ddutil.h"
#include "ccklib.h"
#include "Sprite3D.h"


//-----------------------------------------------------------------------------
// Declare the application globals for use in WinMain.cpp
//-----------------------------------------------------------------------------
TCHAR* g_strAppTitle       = TEXT( "Enhanced2D: Mixing DirectDraw and D3DIM" );
BOOL   g_bAppUseZBuffer    = TRUE;
BOOL   g_bAppUseBackBuffer = TRUE;

extern void AppOutputText( LPDIRECT3DDEVICE3 pd3dDevice, DWORD x, DWORD y, CHAR* str );
extern CD3DFramework* g_pFramework;


//-----------------------------------------------------------------------------
// Function prototypes and global (or static) variables
//-----------------------------------------------------------------------------
VOID    AppPause( BOOL );
HRESULT App_InitDeviceObjects( LPDIRECT3DDEVICE3, LPDIRECT3DVIEWPORT3 );
VOID    App_DeleteDeviceObjects( LPDIRECT3DDEVICE3, LPDIRECT3DVIEWPORT3 );
void    UpdateDDFrame( LPDIRECT3DDEVICE3 pd3dDevice );
HRESULT CreateBitmapSurface( LPDIRECTDRAWSURFACE4* pDDS, char* bmpFilename );
HRESULT RenderSurface( LPDIRECTDRAWSURFACE4 g_pDDS, UINT rLeft, UINT rTop,
		               UINT rRight, UINT rBottom );
BOOL    RestoreAll();


// Class for color management in this sample
class TRGBA {
public:
	TRGBA() {}
	TRGBA( float _r, float _g, float _b, float _a )
	{ r = _r; g = _g; b = _b; a = _a; }
	TRGBA( DWORD dwColor )
	{ SplitColors(dwColor); }
	void SplitColors( DWORD dwColor ) {
		r = RGBA_GETRED(dwColor) / 255;
		g = RGBA_GETGREEN(dwColor) / 255;
		b = RGBA_GETBLUE(dwColor) / 255;
		a = RGBA_GETALPHA(dwColor) / 255;
	}
	BOOL equals( TRGBA t ) {
		if( t.r == r && t.g == g && t.b == b && t.a == a ) return TRUE;
		else return FALSE;
	}
	BOOL IsSimilarTo( TRGBA t ) {
		if( t.r >= r-0.1 && t.r <= r+0.1 &&
			t.g >= g-0.1 && t.g <= g+0.1 &&
			t.b >= b-0.1 && t.b <= b+0.1 &&
			t.a >= a-0.1 && t.a <= a+0.1 ) return TRUE;
		else return FALSE;
	}
	D3DCOLOR GetColor() { return D3DRGBA(r,g,b,a); }
	float r,g,b,a;
};

BOOL g_bCanDoAlphaBlend = FALSE;				// Is the device able to do alphablending?
BOOL g_bCanDoAlphaTest  = FALSE;				// Is the device able to do alphatesting?

LPDIRECT3DMATERIAL3	 g_pmtrlRenderMtrl = NULL;	// The Render Material
LPDIRECTDRAWSURFACE4 g_pddsBitmap      = NULL;	// The Bitmap's Surface

char* g_bmpFilename		  = "enh2d.bmp";		// The Bitmap's Filename
Sprite3D* g_pSprite		  = NULL;				// Our 3D Sprite
Timer* g_pTimer			  = NULL;				// The sample's timing management (CCKLib)
Timer* g_pModeTimer       = NULL;				// Timer for sample modes
Randomizer* g_pRandomizer = NULL;				// The CCKLib class for making random numbers easier

float g_fFadeFactor = 0.01;						// Fading factor per event in Fading Mode
float g_fFade = 0;								// Fading color for the whole sprite

BOOL VertexInit[4];								// Must vertix colors be initalized?
BOOL g_bUseAlphablending = TRUE;				// Do we currently use Alphablending?
BOOL g_bUseAlphatesting = FALSE;				// Do we currently use Alphatesting?
BOOL g_bUseSpecular = TRUE;						// Are we using specular colors?
TRGBA cVertex[4], cVertexTarget[4], cStep[4];	// Vertex colors (using TRGB class)

float g_mR = 0.5, g_mG = 0.5, g_mB = 0.5;		// Global light settings for material
int g_nEventCount = 0;							// Event counter for different lighting modes

char* g_strMode = "Fading";						// String for global mode

// Just some modes for the sample movement of the sprite
enum MoveMode { MOVE_RIGHT=1, MOVE_DOWN=2, MOVE_LEFT=3, MOVE_UP=4 } g_nMoveMode = MOVE_RIGHT;
enum SampleMode { SM_FADE=1, SM_LIGHT=2 } g_nSampleMode = SM_FADE;


//-----------------------------------------------------------------------------
// Name: App_OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT App_OneTimeSceneInit( HWND hWnd )
{
	// Seed the random number generator
	g_pRandomizer->SeedRand();

	// Initializing stuff
	for( int i=0; i<4; i++ ) VertexInit[i] = TRUE;

	// Create a texture for our D3D IM sprite
	D3DTextr_CreateTexture( "tex1.bmp",  0, D3DTEXTR_TRANSPARENTBLACK );
	D3DTextr_CreateTexture( "tree0.bmp", 0, D3DTEXTR_TRANSPARENTBLACK );

	// TODO: Add the textures you'll need for your sprites here.

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: App_FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT App_FrameMove( LPDIRECT3DDEVICE3 pd3dDevice, FLOAT fTimeKey )
{
	// The following code depends on this sample and is not necessary
	// for your applications
	if( g_pTimer->GetEvent() )
	{
		// Get the viewport's width and height
		LPDIRECT3DVIEWPORT3 pvViewport;
		pd3dDevice->GetCurrentViewport( &pvViewport );
		D3DVIEWPORT2 vp;
		vp.dwSize = sizeof(D3DVIEWPORT2);
		pvViewport->GetViewport2( &vp );
		DWORD vpWidth = vp.dwWidth;
		DWORD vpHeight = vp.dwHeight;

		// Code to move our sprite around on the surface - this is done
		// in any sample mode
		int nLeft, nTop, nRight, nBottom;
		g_pSprite->GetCoordinates( nLeft, nTop, nRight, nBottom );
		if( nRight < (int)vpWidth - 10 && g_nMoveMode == MOVE_RIGHT )
			g_pSprite->Move( 1, 0 );
		else if( nRight == (int)vpWidth - 10 && g_nMoveMode == MOVE_RIGHT )
			g_nMoveMode = MOVE_DOWN;
		else if( nBottom < (int)vpHeight - 10 && g_nMoveMode == MOVE_DOWN )
			g_pSprite->Move( 0, 1 );
		else if( nBottom == (int)vpHeight - 10 && g_nMoveMode == MOVE_DOWN )
			g_nMoveMode = MOVE_LEFT;
		else if( nLeft > 10 && g_nMoveMode == MOVE_LEFT )
			g_pSprite->Move( -1, 0 );
		else if( nLeft == 10 && g_nMoveMode == MOVE_LEFT )
			g_nMoveMode = MOVE_UP;
		else if( nTop > 10 && g_nMoveMode == MOVE_UP )
			g_pSprite->Move( 0, -1 );
		else if( nTop == 10 && g_nMoveMode == MOVE_UP )
			g_nMoveMode = MOVE_RIGHT;

		// Sample Mode specific code. The following code samples do only show
		// how you could attain certain effects with the Sprite3D class.
		switch( g_nSampleMode )
		{
		case SM_FADE:
			g_strMode = "Fading";
			if( g_fFade < 1 ) g_fFade += g_fFadeFactor;
			if( g_fFade >= 1 ) {
				g_fFade = 1.0f;
				g_nSampleMode = SM_LIGHT;
				g_pModeTimer = new Timer(5000);
				g_strMode = "Alphablending + Surface Light";
			}
			g_pSprite->SetColors( D3DRGBA( g_fFade, g_fFade, g_fFade, g_fFade ),
						  	      D3DRGBA( g_fFade, g_fFade, g_fFade, g_fFade ) );
			break;

		case SM_LIGHT:
			if( g_pModeTimer->GetEvent() ) {
				if( g_nEventCount == 0 ) {
					g_pSprite->SetColors( D3DRGBA( 1, 1, 1, 1 ),
		            			  	      D3DRGBA( 0.5, 0.5, 0.5, 0.5 ) );
					g_bUseAlphablending = FALSE;
					g_pModeTimer->SetWaitTime(5000);
					++g_nEventCount;
					g_strMode = "Opaque + Surface Light";
				} else if( g_nEventCount == 1 ) {
					if(g_bCanDoAlphaTest) g_bUseAlphatesting = TRUE;
					g_bUseAlphablending = FALSE;
					g_pSprite->SetTexFilename( "tree0.bmp" );
					++g_nEventCount;
					g_strMode = "Alphatesting + Surface Light";
				} else if( g_nEventCount == 2 ) {
					if(g_bCanDoAlphaBlend) g_bUseAlphablending = TRUE;
					g_bUseAlphatesting = FALSE;
					g_pSprite->SetTexFilename( "tex1.bmp" );
					g_nEventCount = 0;
					g_strMode = "Alphablending + Surface Light";
					if( g_bUseSpecular ) g_bUseSpecular = FALSE;
					else g_bUseSpecular = TRUE;
				}

			}

			float fStepFactor = 10;

			// Calculate and set the surface lighting parameters
			for( int i=0; i<4; i++ )
			{
				if( VertexInit[i] == TRUE )	{
					VertexInit[i] = FALSE;
					cVertex[i] = TRGBA( g_pSprite->GetColor() );
					cVertexTarget[i] = TRGBA( g_pRandomizer->GetRandNum(1),
						                      g_pRandomizer->GetRandNum(1), 
											  g_pRandomizer->GetRandNum(1),
											  g_pRandomizer->GetRandNum(1) );
					cStep[i].r = (cVertexTarget[i].r - cVertex[i].r) / fStepFactor;
					cStep[i].g = (cVertexTarget[i].g - cVertex[i].g) / fStepFactor;
					cStep[i].b = (cVertexTarget[i].b - cVertex[i].b) / fStepFactor;
					cStep[i].a = (cVertexTarget[i].a - cVertex[i].a) / fStepFactor;
				}

				if( cVertex[i].IsSimilarTo(cVertexTarget[i]) )
				{
					cVertexTarget[i] = TRGBA( g_pRandomizer->GetRandNum(1),
						                      g_pRandomizer->GetRandNum(1), 
											  g_pRandomizer->GetRandNum(1),
											  g_pRandomizer->GetRandNum(1) );
					cStep[i].r = (cVertexTarget[i].r - cVertex[i].r) / fStepFactor;
					cStep[i].g = (cVertexTarget[i].g - cVertex[i].g) / fStepFactor;
					cStep[i].b = (cVertexTarget[i].b - cVertex[i].b) / fStepFactor;
					cStep[i].a = (cVertexTarget[i].a - cVertex[i].a) / fStepFactor;
				}

				// Recalculate and refresh the colors
				cVertex[i].r += cStep[i].r;
				cVertex[i].g += cStep[i].g;
				cVertex[i].b += cStep[i].b;
				cVertex[i].a += cStep[i].a;
				g_pSprite->SetVertexColor( i, cVertex[i].GetColor(), cVertex[i].GetColor() );
			}
			break;
		}
	}
	
	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: App_Render()
// Desc: Called once per frame, the call is the entry point for 3d
//       rendering. This function sets up render states, clears the
//       viewport, and renders the scene.
//-----------------------------------------------------------------------------
HRESULT App_Render( LPDIRECT3DDEVICE3 pd3dDevice, 
				    LPDIRECT3DVIEWPORT3 pvViewport, D3DRECT* prcViewportRect )
{
    //Clear the viewport
    pvViewport->Clear2( 1UL, prcViewportRect, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0x20202020, 
		                1.0f, 0L );

	// Begin the scene
	if( SUCCEEDED( pd3dDevice->BeginScene() ) )
	{
		// Render the DirectDraw background image
		UpdateDDFrame(pd3dDevice);
	
		if( g_bUseSpecular )
			pd3dDevice->SetRenderState( D3DRENDERSTATE_SPECULARENABLE, TRUE );
		else
			pd3dDevice->SetRenderState( D3DRENDERSTATE_SPECULARENABLE, FALSE );

		if( g_bUseAlphablending )
		{
			pd3dDevice->SetRenderState( D3DRENDERSTATE_SRCBLEND,  D3DBLEND_ONE);
			pd3dDevice->SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
			pd3dDevice->SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
		}

		if( g_bUseAlphatesting )
		{
			pd3dDevice->SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, TRUE );
		    pd3dDevice->SetRenderState( D3DRENDERSTATE_ALPHAREF, 0x08 );
	        pd3dDevice->SetRenderState( D3DRENDERSTATE_ALPHAFUNC, D3DCMP_GREATEREQUAL );
		}

		// Render the sample sprite
		g_pSprite->RenderSprite( pd3dDevice );

		pd3dDevice->SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
		pd3dDevice->SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, FALSE );

		// Display the sample mode string
		AppOutputText( pd3dDevice, 5, 15, g_strMode );

		// End the scene.
		pd3dDevice->EndScene();
	}

	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////
//
// The following functions are based on DirectDraw and are only for 2D blitting
//

void UpdateDDFrame( LPDIRECT3DDEVICE3 pd3dDevice )
{
	HRESULT hRet;

    while (TRUE)
    {
		// Render the prepared bitmap surface
		//if(g_pddsBitmap==NULL)exit(0);
		hRet = RenderSurface( g_pddsBitmap, 0, 0, 256, 256 );
        if (hRet == DD_OK)
            break;

        if (hRet == DDERR_SURFACELOST)
        {
            if (!RestoreAll())
                return;
        }
        if (hRet != DDERR_WASSTILLDRAWING)
            return;
	}

}


//-----------------------------------------------------------------------------
// Name: RestoreAll()
// Desc: Restore all lost objects
//-----------------------------------------------------------------------------
BOOL RestoreAll(void)
{
	if( g_pddsBitmap->Restore() && DDReLoadBitmap((LPDIRECTDRAWSURFACE)g_pddsBitmap, g_bmpFilename) )
		return TRUE;
	else
		return FALSE;
}


//-----------------------------------------------------------------------------
// Name: CreateBitmapSurface()
// Desc: This function creates a surface for an existing bitmap.
//-----------------------------------------------------------------------------
HRESULT CreateBitmapSurface( LPDIRECTDRAWSURFACE4* pddsDest, char* bmpFilename )
{
	LPDIRECTDRAW4 pDD;

	LPDIRECTDRAWSURFACE4 pddsSurface = g_pFramework->GetRenderSurface();
    if( FAILED( pddsSurface->GetDDInterface( (VOID**)&pDD ) ) )
        return E_FAIL;
    pDD->Release();

	*pddsDest = (LPDIRECTDRAWSURFACE4)DDLoadBitmap((LPDIRECTDRAW)pDD, bmpFilename, 0, 0);
    if (pddsDest == NULL)
        return E_FAIL;

	return DD_OK;
}


//-----------------------------------------------------------------------------
// Name: RenderSurface()
// Desc: This function renders a DirectDrawSurface to the Render Surface.
//-----------------------------------------------------------------------------
HRESULT RenderSurface( LPDIRECTDRAWSURFACE4 g_pDDS, UINT rLeft, UINT rTop,
		               UINT rRight, UINT rBottom )
{
	RECT cyRect;
	HRESULT hRet;

	// Get the BackBuffer's DirectDraw Surface into memory
	LPDIRECTDRAWSURFACE4 g_pDDSBack;
	g_pDDSBack = g_pFramework->GetRenderSurface();

	// Create the rectangle which is cut from the DirectDrawSurface
	cyRect.left   = rLeft;
	cyRect.top    = rTop;
	cyRect.right  = rRight;
	cyRect.bottom = rBottom;
	
    hRet = g_pDDSBack->Blt(NULL, g_pDDS, &cyRect, 0, NULL);

	return hRet;
}


//
// End of the 2D section in this file. The 3D sprite stuff can be found in the
// Sprite3D module of the project. Note: Sprite3D is a special class to make
// sprite-rendering easier.
//
///////////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------------------
// Name: App_InitDeviceObjects()
// Desc: Initialize scene objects
//-----------------------------------------------------------------------------
HRESULT App_InitDeviceObjects( LPDIRECT3DDEVICE3 pd3dDevice,
							   LPDIRECT3DVIEWPORT3 pvViewport )
{
	// Check parameters
	if( NULL==pd3dDevice || NULL==pvViewport )
        return E_INVALIDARG;

	D3DTextr_RestoreAllTextures( pd3dDevice );

	// Get a ptr to the ID3D object to create materials and/or lights. Note:
	// the Release() call just serves to decrease the ref count.
	LPDIRECT3D3 pD3D;
	if( FAILED( pd3dDevice->GetDirect3D( &pD3D ) ) )
		return E_FAIL;
	pD3D->Release();

	//Create the render material
    if( FAILED( pD3D->CreateMaterial( &g_pmtrlRenderMtrl, NULL) ) )
		return E_FAIL;

	D3DMATERIAL       mtrl;
	D3DMATERIALHANDLE hmtrl;
	D3DUtil_InitMaterial( mtrl, g_mR, g_mG, g_mB );
	mtrl.power = 40;
    g_pmtrlRenderMtrl->SetMaterial( &mtrl );
	g_pmtrlRenderMtrl->GetHandle( pd3dDevice, &hmtrl );
	pd3dDevice->SetLightState( D3DLIGHTSTATE_MATERIAL, hmtrl );

	// Set the transform matrices
	D3DVECTOR vEyePt    = D3DVECTOR( 0.0f, 0.0f, -20.0f );
	D3DVECTOR vLookatPt = D3DVECTOR( 0.0f, 0.0f,   0.0f );
	D3DVECTOR vUpVec    = D3DVECTOR( 0.0f, 0.0f,   1.0f );
	D3DMATRIX matView, matProj;

	D3DUtil_SetViewMatrix( matView, vEyePt, vLookatPt, vUpVec );
	D3DUtil_SetProjectionMatrix( matProj, 1.57f, 1.0f, 1.0f, 100.0f );
	pd3dDevice->SetTransform( D3DTRANSFORMSTATE_VIEW,       &matView );
	pd3dDevice->SetTransform( D3DTRANSFORMSTATE_PROJECTION, &matProj );

	// Set any appropiate state
    pd3dDevice->SetLightState(  D3DLIGHTSTATE_AMBIENT,     0xffffffff );
	pd3dDevice->SetRenderState( D3DRENDERSTATE_SRCBLEND,   D3DBLEND_ONE );
	pd3dDevice->SetRenderState( D3DRENDERSTATE_DESTBLEND,  D3DBLEND_ONE );
	pd3dDevice->SetRenderState( D3DRENDERSTATE_DITHERENABLE, FALSE );
	pd3dDevice->SetRenderState( D3DRENDERSTATE_SPECULARENABLE, TRUE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DTFN_LINEAR );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR );

	// Check the hardware capabilities to check wether device can do
	// alphablending and alphatesting
	D3DDEVICEDESC ddHELDesc, ddHALDesc;
    ddHELDesc.dwSize = sizeof(D3DDEVICEDESC);
    ddHALDesc.dwSize = sizeof(D3DDEVICEDESC);
    pd3dDevice->GetCaps( &ddHALDesc, &ddHELDesc );
    D3DDEVICEDESC* pDesc = (ddHALDesc.dwFlags) ? &ddHALDesc : &ddHELDesc;
    if( pDesc->dpcTriCaps.dwDestBlendCaps & D3DPBLENDCAPS_INVSRCALPHA )
        if( pDesc->dpcTriCaps.dwSrcBlendCaps & D3DPBLENDCAPS_SRCALPHA )
                g_bCanDoAlphaBlend = TRUE;

    if( pDesc->dpcTriCaps.dwAlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL )
        g_bCanDoAlphaTest = TRUE;

	// If alphablending is supported activate it, otherwise warn the user
	if( g_bCanDoAlphaBlend ) g_bUseAlphablending = TRUE;
	else {
		char* strMsg = "The graphic board of this system doesn't support alphablending.\nNote that this feature will not be displayed correctly in Direct3D HAL device.";
		MessageBox( NULL, strMsg, g_strAppTitle, MB_ICONWARNING|MB_OK );
	}

	// If alphatesting is not supported warn the user
	if( !g_bCanDoAlphaTest ) {
		char* strMsg = "The graphic board of this system doesn't support alphatesting.\nNote that this feature will not be displayed correctly in Direct3D HAL.";
		MessageBox( NULL, strMsg, g_strAppTitle, MB_ICONWARNING|MB_OK );
	}

	// Create a surface for the bitmap and load it in...
	HRESULT hr = CreateBitmapSurface( &g_pddsBitmap, g_bmpFilename );
	//if(g_pddsBitmap==NULL)exit(0);
	// Create a sprite using the Sprite3D class
	g_pSprite = new Sprite3D();
	g_pSprite->CreateSprite( "tex1.bmp", 0x00000000, 0x00000000,
		                    10, 10, 200, 200, 0, 0, 1, 1 );

	// Create a new timer for the sample's timing management (the Timer
	// class is a special class developed by me for game timing - it can
	// be found in the ccklib.h file included to this project)
	// Note: The 20 means that the timer returns an event every 20 milliseconds
	g_pTimer = new Timer(20);

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: App_FinalCleanup()
// Desc: Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT App_FinalCleanup( LPDIRECT3DDEVICE3 pd3dDevice, 
						  LPDIRECT3DVIEWPORT3 pvViewport )
{
	App_DeleteDeviceObjects( pd3dDevice, pvViewport );
	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: App_DeleteDeviceObjects()
// Desc: Called when the app is exitting, or the device is being changed,
//       this function deletes any device dependant objects.
//-----------------------------------------------------------------------------
VOID App_DeleteDeviceObjects( LPDIRECT3DDEVICE3 pd3dDevice,
				              LPDIRECT3DVIEWPORT3 pvViewport )
{
    D3DTextr_InvalidateAllTextures();
	SAFE_RELEASE( g_pmtrlRenderMtrl );

	if(g_pddsBitmap)g_pddsBitmap->Release();		// destroy the bitmap's surface
	delete g_pSprite;				// delete the sample sprite
	delete g_pTimer;				// delete the program timer

	// If necessary, delete the Mode Timer.
	if( g_nSampleMode > 1 )	delete g_pModeTimer;

	// Set the modes to default for app reinitialization
	g_nMoveMode = MOVE_RIGHT;
	g_nSampleMode = SM_FADE;
}




//-----------------------------------------------------------------------------
// Name: App_RestoreSurfaces
// Desc: Restores any previously lost surfaces. Must do this for all surfaces
//       (including textures) that the app created.
//-----------------------------------------------------------------------------
HRESULT App_RestoreSurfaces()
{
	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: App_ConfirmDevice()
// Desc: Called during device intialization, this code checks the device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT App_ConfirmDevice( DDCAPS* pddDriverCaps,
						   D3DDEVICEDESC* pd3dDeviceDesc )
{
	// Get triangle caps (Hardware or software) and check for alpha blending
	LPD3DPRIMCAPS pdpc = &pd3dDeviceDesc->dpcTriCaps;

	if( 0 == ( pdpc->dwSrcBlendCaps & pdpc->dwDestBlendCaps & D3DBLEND_ONE ) )
		return E_FAIL;

	return S_OK;
}






