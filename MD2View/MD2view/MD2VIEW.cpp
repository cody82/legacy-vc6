
// MD2 View

// This file was originally part of the DX7 SDK
// and was altered by William Chin
// Developed in MSDEV C++ v6.0 using the DirectX 7.0a SDK
// Date : 16th May 2000
// File : md2view.cpp

// Website: http://members.aol.com/billybop7
// Email:  billybop7@aol.com 



#define STRICT
#define D3D_OVERLOADS
#include <stdio.h>
#include "D3DApp.h"
#include "D3DUtil.h"
#include "D3DMath.h"
#include "D3DTextr.h"
#include "ImportMD2.hpp"
#include "Debug.hpp"

#define WATER_COLOR 0x00006688 // used as the back ground color


MD2MODEL model; // structure to store 3ds model data



//-----------------------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: Main class to run this application. Most functionality is inherited
//       from the CD3DApplication base class.
//-----------------------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication, public CMD2
{

public:
    HRESULT OneTimeSceneInit();
    HRESULT InitDeviceObjects();
    HRESULT DeleteDeviceObjects();
    HRESULT Render();
    HRESULT FrameMove( FLOAT );
    HRESULT FinalCleanup();

    CMyD3DApplication();
};


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point to the program. Initializes everything, and goes into a
//       message-processing loop. Idle time is used to render the scene.
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    CMyD3DApplication d3dApp;

    if( FAILED( d3dApp.Create( hInst, strCmdLine ) ) )
        return 0;

    return d3dApp.Run();
}


//-----------------------------------------------------------------------------
// Name: CMyD3DApplication()
// Desc: Constructor
//-----------------------------------------------------------------------------
CMyD3DApplication::CMyD3DApplication()
                  :CD3DApplication()
{
    // Override base class members
    m_strWindowTitle  = TEXT("MD2 View v1.0");
    m_bAppUseZBuffer  = TRUE;
    m_bAppUseStereo   = TRUE;
    m_bShowStats      = TRUE;
    m_fnConfirmDevice = NULL;
}


//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::OneTimeSceneInit()
{
	PrintMessage("CMyD3DApplication::OneTimeSceneInit()", NULL);

	LoadMD2Model(&model, "malignus.md2" );	
    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove( FLOAT fTimeKey )
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Called once per frame, the call is the entry point for 3d
//       rendering. This function sets up render states, clears the
//       viewport, and renders the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                         WATER_COLOR, 1.0f, 0L );

	
    // Begin the scene 
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {	
		RenderMD2Model(m_pd3dDevice, 
					  0.0f, 0.0f, 0.0f, // place the model at world co-ordinate (x,y,z)
					  295.0f, // rotate model around y axis by this angle
					  &model); // pointer to 3ds model structure

        // End the scene.
        m_pd3dDevice->EndScene();
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
	PrintMessage("CMyD3DApplication::InitDeviceObjects()", NULL);

	// Create and set up the object material
    D3DMATERIAL7 mtrl;
    D3DUtil_InitMaterial( mtrl, 1.0f, 1.0f, 1.0f, 0.0f );
    mtrl.power = 40.0f;
    m_pd3dDevice->SetMaterial( &mtrl );
    m_pd3dDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0x00f0f0f0);


    // Set up the lighting states
    if( m_pDeviceInfo->ddDeviceDesc.dwVertexProcessingCaps &
                                                D3DVTXPCAPS_DIRECTIONALLIGHTS )
    {
        D3DLIGHT7 light;
        D3DUtil_InitLight( light, D3DLIGHT_DIRECTIONAL, 0.0f, -1.0f, 0.0f );
        m_pd3dDevice->SetLight( 0, &light );
        m_pd3dDevice->LightEnable( 0, TRUE );
        m_pd3dDevice->SetRenderState( D3DRENDERSTATE_LIGHTING, TRUE );
    }
    
	m_pd3dDevice->SetRenderState( D3DRENDERSTATE_LIGHTING, TRUE );
    // Set the transform matrices
    D3DVIEWPORT7 vp;
    m_pd3dDevice->GetViewport(&vp);

	// The Aspect ratio make sure all objects in the scene
	// always have the same proportions, and don't look
	// stretched when the window size is changed
    FLOAT fAspect = ((FLOAT)vp.dwHeight) / vp.dwWidth;

	// Position in the 3d scene where the camera is placed
	// AS the model is placed at x,y,z (0,0,0) we want
	// to place the camera behind this point at a resonable
	// distance away from it.
    D3DVECTOR vEyePt    = D3DVECTOR( 0.0f, 5.0f, -25.0f );

	// a point in the 3d scene that the camera is looking at
    D3DVECTOR vLookatPt = D3DVECTOR( 0.0f, 0.0f,   0.0f );

	// defines which Axis is up
    D3DVECTOR vUpVec    = D3DVECTOR( 0.0f, 1.0f,   0.0f );
    D3DMATRIX matWorld, matProj;

    D3DUtil_SetIdentityMatrix( matWorld );
    SetViewParams( &vEyePt, &vLookatPt, &vUpVec , 0.1f);
    D3DUtil_SetProjectionMatrix( matProj, g_PI/2, fAspect, 6.0f, 10000.0f );

    m_pd3dDevice->SetTransform( D3DTRANSFORMSTATE_WORLD,      &matWorld );
    m_pd3dDevice->SetTransform( D3DTRANSFORMSTATE_PROJECTION, &matProj );

    // Set up textures
    D3DTextr_RestoreAllTextures( m_pd3dDevice );
   

	// Set miscellaneous renderstates
    m_pd3dDevice->SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESS);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_NORMALIZENORMALS, TRUE); 

    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DTFN_LINEAR );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR );

    // Set default render states
    m_pd3dDevice->SetRenderState( D3DRENDERSTATE_DITHERENABLE,   TRUE );
    m_pd3dDevice->SetRenderState( D3DRENDERSTATE_SPECULARENABLE, FALSE );
    m_pd3dDevice->SetRenderState( D3DRENDERSTATE_ZENABLE,        TRUE );
    
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc: Called when the app is exitting, or the device is being changed,
//       this function deletes any device dependant objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::DeleteDeviceObjects()
{
	PrintMessage("CMyD3DApplication::DeleteDeviceObjects", NULL);
    D3DTextr_InvalidateAllTextures();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc: Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FinalCleanup()
{
  
    return S_OK;
}




