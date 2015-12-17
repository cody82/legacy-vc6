#include "dd7videostream.h"

CDD7VideoStream::CDD7VideoStream()
{
	lpDDStream=NULL;
	lpMMStream=NULL;
	lpPrimaryVidStream=NULL;
	lpSample=NULL;
	lpDDS=NULL;
	pos_x=0;
	pos_y=0;
}

CDD7VideoStream::~CDD7VideoStream()
{
	Shutdown();
}

BOOL CDD7VideoStream::Initialize(LPDIRECTDRAW7 lpDD,LPCTSTR szFilename)
{
	HRESULT hr;
    IAMMultiMediaStream *pAMStream=NULL;
	IDirectDrawFactory *g_pDDF;

    WCHAR wFile[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, szFilename, -1, wFile,    
                                sizeof(wFile)/sizeof(wFile[0]));
    
//	hr = CoCreateInstance(CLSID_DirectDrawFactory, NULL, CLSCTX_INPROC_SERVER, 
//                            IID_IDirectDrawFactory, (void **)&g_pDDF);

    hr =CoCreateInstance(CLSID_AMMultiMediaStream, NULL, CLSCTX_INPROC_SERVER,
                                      IID_IAMMultiMediaStream, (void **)&pAMStream);
    if (FAILED(hr))
    {   //MessageBox(ghWnd, "Could not create a CLSID_MultiMediaStream object\n"
        //"Check you have run regsvr32 amstream.dll\n", "Error", MB_OK);
        //  return E_FAIL;
		return FALSE;
    }

    hr = pAMStream->Initialize(STREAMTYPE_READ, 0, NULL);
    if (FAILED(hr))
    {   //MessageBox(ghWnd, "Initialize failed.", "Error", MB_OK);
        //  return E_FAIL;
		pAMStream->Release();
		return FALSE;
    }
    hr = pAMStream->AddMediaStream(lpDD, &MSPID_PrimaryVideo, 0, NULL);
    if (FAILED(hr))
    {   //MessageBox(ghWnd, "AddMediaStream failed.", "Error", MB_OK);
        //  return E_FAIL;
		pAMStream->Release();
		return FALSE;

    }
    hr = pAMStream->AddMediaStream(NULL, &MSPID_PrimaryAudio, AMMSF_ADDDEFAULTRENDERER, NULL);
    if (FAILED(hr))
    {   //MessageBox(ghWnd, "AddMediaStream failed.", "Error", MB_OK);
        //  return E_FAIL;
		pAMStream->Release();
		return FALSE;
    }
    hr = pAMStream->OpenFile(wFile, 0); 
    if (FAILED(hr))
    {   //MessageBox(ghWnd, "File format not supported.", "Error", MB_OK);
        //  return E_FAIL;
		pAMStream->Release();
		return FALSE;
    }

    lpMMStream = pAMStream;    
    pAMStream->AddRef();

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
    DDSURFACEDESC    ddsd;
	DDSURFACEDESC2 ddsd2;
	RECT rect;
    
    hr = lpMMStream->GetMediaStream(MSPID_PrimaryVideo, &lpPrimaryVidStream);
    if (FAILED(hr))
    {   //goto Exit;
		pAMStream->Release();
		return FALSE;
    }

    hr = lpPrimaryVidStream->QueryInterface(IID_IDirectDrawMediaStream, (void **)&lpDDStream);
    if (FAILED(hr))
    {   //goto Exit;
		pAMStream->Release();
		lpDDStream->Release();
		return FALSE;
    }

    ddsd.dwSize = sizeof(ddsd);
    hr = lpDDStream->GetFormat(&ddsd, NULL, NULL, NULL);
    if (FAILED(hr))
    {   //goto Exit;
		pAMStream->Release();
		lpDDStream->Release();
		return FALSE;
    }

	pSize.x=ddsd.dwWidth;
	pSize.y=ddsd.dwHeight;

	rect.left=rect.top=0;
	rect.right=pSize.x;
	rect.bottom=pSize.y;

    ZeroMemory(&ddsd2, sizeof(ddsd2));
    ddsd2.dwSize = sizeof(ddsd2);    
    ddsd2.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd2.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd2.dwHeight = ddsd.dwHeight;    
    ddsd2.dwWidth  = ddsd.dwWidth;   
    ddsd2.ddpfPixelFormat = ddsd.ddpfPixelFormat; 

	hr=lpDD->CreateSurface(&ddsd2,&lpDDS,NULL);
	if(FAILED(hr))
    {   //goto Exit;
		pAMStream->Release();
		lpDDStream->Release();
		return FALSE;
    }

    hr = lpDDStream->CreateSample((LPDIRECTDRAWSURFACE)lpDDS, &rect, 0, &lpSample);
    if (FAILED(hr))
    {   //goto Exit;
		pAMStream->Release();
		lpDDStream->Release();
		return FALSE;
    }

    lpMMStream->SetState(STREAMSTATE_RUN);
    return TRUE;

}

void CDD7VideoStream::Shutdown()
{
	if(lpMMStream)lpMMStream->Release();
	if(lpDDS)lpDDS->Release();
}

BOOL CDD7VideoStream::Render(LPDIRECTDRAWSURFACE7 lpDDSDest)
{
    HRESULT        hr;
	RECT rect;

	rect.left=pos_x;
	rect.top=pos_y;
	rect.right=pos_x+pSize.x;
	rect.bottom=pos_y+pSize.y;

    if (lpSample->Update(0, NULL, NULL, 0) != S_OK) 
	{
        lpMMStream->SetState(STREAMSTATE_STOP);        
    }
    else
    { 
		hr = lpDDSDest->Blt(&rect, lpDDS, &rect, DDBLT_WAIT, NULL); 
	}

	return TRUE;
}