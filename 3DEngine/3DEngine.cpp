#include "3dengine.h"


/////////////////////////////////////////////////////////////////////////////////////
// EnumDD - enumerates DD drivers, chooses hardware if available
/////////////////////////////////////////////////////////////////////////////////////
BOOL FAR PASCAL EnumDD(GUID FAR* lpGUID, LPSTR lpDriverDesc, LPSTR lpDriverName, LPVOID lpContext)
{
	LPDIRECTDRAW lpDD;
	DDCAPS HALCaps, HELCaps;

	// Make sure the guid is valid
	if(lpGUID)
	{
		// Try to create a DirectDraw object
		DirectDrawCreate(lpGUID, &lpDD, NULL);

		// Get the DirectDraw capabilities
		memset(&HALCaps, 0, sizeof(DDCAPS));
		HALCaps.dwSize = sizeof(DDCAPS);

		memset(&HELCaps, 0, sizeof(DDCAPS));
		HELCaps.dwSize = sizeof(DDCAPS);

		lpDD->GetCaps(&HALCaps, &HELCaps);

		// Does this driver have 3D hardware capabilites?
		if(HALCaps.dwCaps & DDCAPS_3D)
		{
			*(LPDIRECTDRAW*)lpContext = lpDD;
			return DDENUMRET_CANCEL;
		}

		*(LPDIRECTDRAW*)lpContext = NULL;
		lpDD->Release();
	}
	return DDENUMRET_OK;
}

C3DEngine::C3DEngine()
{
	bActive=TRUE;
	pFirstObject=NULL;
}

C3DEngine::~C3DEngine()
{
	Shutdown();
}

BOOL C3DEngine::Initialize(int res_x,int res_y,int nBuffers,int bpp,WNDPROC wndproc,HINSTANCE hInst,BOOL fullscreen)
{
	HRESULT rval;
	WNDCLASS WndClass;
	//BOOL sw=FALSE;

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = wndproc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInst;
	WndClass.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = NULL;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = D3DE_WNDCLASS;
	RegisterClass(&WndClass);

	hWnd = CreateWindowEx(
		WS_EX_TOPMOST,
		D3DE_WNDCLASS,
		D3DE_WNDTITLE,
		WS_POPUP,
		0,0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		NULL,
		NULL,
		hInst,
		NULL);

	if(!hWnd) return FALSE;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	DirectDrawEnumerate(EnumDD, &DirectDraw);

	// Create the DirectDraw instance
	if(!DirectDraw)	rval = DirectDrawCreate(NULL, &DirectDraw, NULL);

	DirectDraw->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE);
	DirectDraw->SetDisplayMode(res_x, res_y, bpp);

	DDSURFACEDESC ddsd;
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
												DDSCAPS_FLIP |
	                      DDSCAPS_COMPLEX |
												DDSCAPS_3DDEVICE |
												DDSCAPS_VIDEOMEMORY;
	ddsd.dwBackBufferCount = nBuffers;

	// Create the FrontBuffer
	DirectDraw->CreateSurface(&ddsd, &FrontBuffer, NULL);

	DDSCAPS ddscaps;
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;

	// Create the BackBuffer
	FrontBuffer->GetAttachedSurface(&ddscaps, &BackBuffer);

	//Create Z-Buffer
    //memset(&ddsd, 0 ,sizeof(DDSURFACEDESC));
    //ddsd.dwSize = sizeof( ddsd );
/*    ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS |DDSD_ZBUFFERBITDEPTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER|DDSCAPS_VIDEOMEMORY;
    ddsd.dwHeight = res_y;
    ddsd.dwWidth = res_x;
	ddsd.dwZBufferBitDepth = 16;
    if(DirectDraw->CreateSurface(&ddsd,&ZBuffer,NULL)!=DD_OK)exit(0);*/

	
	
	// Create the Direct3D instance
	DirectDraw->QueryInterface(IID_IDirect3D2, (LPVOID*)&Direct3D);

	D3DFINDDEVICESEARCH search;
	D3DFINDDEVICERESULT result;

	search.dwSize = sizeof(search);
	search.dwFlags = D3DFDS_HARDWARE;
	search.bHardware = TRUE;
	result.dwSize = sizeof(result);

	// Create the hardware Device
	Direct3D->FindDevice(&search, &result);
	Direct3D->CreateDevice(result.guid, BackBuffer, &Device);

	if(Device == NULL)
	{
		search.dwSize = sizeof(search);
		search.dwFlags = D3DFDS_HARDWARE;
		search.bHardware = FALSE;
		result.dwSize = sizeof(result);

		// Create the software Device
		Direct3D->FindDevice(&search, &result);
		Direct3D->CreateDevice(result.guid, BackBuffer, &Device);
		//sw=TRUE;
	}


	D3DVIEWPORT2 viewport;
	memset(&viewport, 0, sizeof(D3DVIEWPORT2));
	viewport.dwSize = sizeof(D3DVIEWPORT2);
	viewport.dwX = 0;
	viewport.dwY = 0;
	viewport.dwWidth  = res_x;
	viewport.dwHeight = res_y;
	viewport.dvClipX = -1.0f;
	viewport.dvClipY = (float)res_x/(float)res_y/2.0f;
	viewport.dvClipWidth = 2.0f;
	viewport.dvClipHeight = 1.2f * (float)res_x/(float)res_y;
	viewport.dvMinZ = 0.0f;
	viewport.dvMaxZ = 1.0f;

	// Create the Viewport
	Direct3D->CreateViewport(&Viewport, NULL);
	Device->AddViewport(Viewport);
	Viewport->SetViewport2(&viewport);
	Device->SetCurrentViewport(Viewport);

	World.Identity();//0,0,-50  001,010
	View.SetView(D3DVECTOR(0,0,-50), D3DVECTOR(0,0,1), D3DVECTOR(0,1,0), 0);
	Projection.SetProjection(0.01f, 2000000.0f, (float)(60*PI/180));

	//Device->SetTransform(D3DTRANSFORMSTATE_WORLD, &World);
	Device->SetTransform(D3DTRANSFORMSTATE_VIEW, &View);
	Device->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &Projection);

	// Set the render states
	Device->SetRenderState(D3DRENDERSTATE_ZENABLE,FALSE);
	Device->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,FALSE);
	//Device->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE,TRUE);

	//Device->SetRenderState(D3DRENDERSTATE_FILLMODE,D3DFILL_SOLID );
	//Device->SetRenderState(D3DRENDERSTATE_SHADEMODE ,D3DSHADE_GOURAUD);
	//Device->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND ,D3DTBLEND_ADD);
	//Device->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
	//Device->SetRenderState(D3DRENDERSTATE_SRCBLEND ,TRUE);
  
	tex.Load(Device,"texture.bmp");
	//tex.LoadAlpha(Device);
	Sleep(1000);
	return TRUE;
}

void C3DEngine::Update()
{
	//Ganz am Anfang, nicht ändern
	static DWORD dtime=0;
	DWORD tupdatestart=timeGetTime();
	//////////////////////////////

	//Updating
	C3DObject *node;
	node=pFirstObject;
	while(node)
	{
		node->Update(dtime);
		node=node->pNext;
	}

	//Rendering
	DDBLTFX ddbltfx;
	ddbltfx.dwSize = sizeof(DDBLTFX);
	ddbltfx.dwFillColor = 0;
	BackBuffer->Blt(NULL, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx);

	
	//D3DMATERIALHANDLE hmat;
	//pFirstObject->Material->GetHandle(Device,&hmat);
	//Device->SetLightState(D3DLIGHTSTATE_MATERIAL,hmat);

//Device->GetTransform(D3DTRANSFORMSTATE_WORLD,&World);

/*	Device->BeginScene();

	node=pFirstObject;
	while(node)
	{
		node->Draw(Device);
		node=node->pNext;
	}

	//TEST

	Device->EndScene();*/
	//Device->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, tex.GetHandle());

	//Device->Begin(D3DPT_TRIANGLESTRIP,D3DVT_TLVERTEX,D3DDP_WAIT);
	D3DTLVERTEX v[4];
	memset(v,0,sizeof(D3DTLVERTEX)*4);
	v[0].sx=100;
	v[0].sy=100;
	v[0].color=D3DRGB(1.0f,0.0f,0.0f);
	v[0].specular=D3DRGB(0.0f,0.0f,0.0f);
	//v[0].dvTU=1;
	//v[0].dvTV=1;
	v[1].sx=500;
	v[1].sy=100;
	v[1].color=D3DRGB(0.0f,0.0f,0.0f);
	v[1].specular=D3DRGB(0.0f,0.0f,0.0f);
	//v[1].dvTU=1;
	//v[1].dvTV=0;
	v[2].sx=100;
	v[2].sy=500;
	v[2].color=D3DRGB(0.0f,0.0f,0.0f);
	v[2].specular=D3DRGB(0.0f,0.0f,0.0f);
	//v[2].dvTU=0;
	//v[2].dvTV=1;
	v[3].sx=500;
	v[3].sy=500;
	v[3].color=D3DRGB(0.0f,0.0f,0.0f);
	v[3].specular=D3DRGB(0.0f,0.0f,0.0f);
	//v[3].dvTU=0;
	//v[3].dvTV=0;

	//Device->Vertex(&v[0]);
	//Device->Vertex(&v[1]);
	//Device->Vertex(&v[2]);
	//Device->Vertex(&v[3]);	
	
	//Device->End(0);
	
	Device->BeginScene();
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,D3DVT_TLVERTEX,v,4,D3DDP_WAIT);
	Device->EndScene();
//Device->SetTransform(D3DTRANSFORMSTATE_WORLD,&World);


	HDC hdc;
	char tmpstr[64];
	BackBuffer->GetDC(&hdc);
	sprintf(tmpstr,"%f",FPS);
	SetBkMode(hdc,TRANSPARENT);
	SetTextColor(hdc,RGB(255,255,255));
	TextOut(hdc,0,0,tmpstr,strlen(tmpstr));
	BackBuffer->ReleaseDC(hdc);
	FrontBuffer->Flip(NULL, 0/*DDFLIP_WAIT*/);


	//Am Ende, nicht ändern
	dtime=timeGetTime()-tupdatestart;
	tNow+=dtime;
	FPS=1000/(float)dtime;
	///////////////////////


}

void C3DEngine::Shutdown()
{
	if(Device)
	{
		Device->Release();
		Device=NULL;
	}
	if(Direct3D)
	{
		Direct3D->Release();
		Direct3D=NULL;
	}
	if(BackBuffer)
	{
		BackBuffer->Release();
		BackBuffer=NULL;
	}
	if(FrontBuffer)
	{
		FrontBuffer->Release();
		FrontBuffer=NULL;
	}
	if(ZBuffer)
	{
		ZBuffer->Release();
		ZBuffer=NULL;
	}
	if(DirectDraw)
	{
		DirectDraw->Release();
		DirectDraw=NULL;
	}

}

void C3DEngine::Start()
{
	MSG msg;
	tNow=0;
	
	while( 1 )	//message loop
    {
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
			if( !GetMessage( &msg, NULL, 0, 0 ) )
			{
				return;
			}
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else if(bActive)
		{
			Update();
		}
        else
        {
            // make sure we go to sleep if we have nothing else to do
            WaitMessage();
        }
    }

}

void C3DEngine::OnWM(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_ACTIVATEAPP:
			bActive = wParam;
			break;

		case WM_CREATE:
			break;

		case WM_SETCURSOR:
			SetCursor(NULL);
			return;

		case WM_KEYDOWN:
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

}
