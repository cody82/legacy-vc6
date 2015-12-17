// DDrawWnd.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "mfcddraw.h"
#include "DDrawWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDDrawWnd::CDDrawWnd()
{
	lpDD=NULL;
	lpDDSPrimary=NULL;
	lpDDSBackBuffer=NULL;
	lpDDClip=NULL;
}

CDDrawWnd::~CDDrawWnd()
{
}


BEGIN_MESSAGE_MAP(CDDrawWnd, CWnd)
	//{{AFX_MSG_MAP(CDDrawWnd)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDDrawWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	InitDirectDraw();
}

BOOL CDDrawWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle|WS_VISIBLE|WS_BORDER, rect, pParentWnd, nID, pContext);
}

BOOL CDDrawWnd::InitDirectDraw()
{
	HRESULT hRet;
	DDSURFACEDESC ddsd;
	RECT rect;
	
	GetWindowRect(&rect);
	
	Shutdown();
	
	hRet = DirectDrawCreate(NULL, &lpDD, NULL);
	if(hRet == DD_OK) 
	{ 
	} 
	else 
	{ 
		return FALSE;
	}
	
	hRet = lpDD->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL);
	if (hRet != DD_OK)
	{ 
		lpDD->Release();
		lpDD=NULL;
		return FALSE;
	} 
	else 
	{ 
	}
	
	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	hRet = lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
	if( hRet != DD_OK )
	{
		return FALSE;
	}
	
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;	
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	
	ddsd.dwWidth = rect.right-rect.left;
	ddsd.dwHeight = rect.bottom-rect.top;
	
	hRet = lpDD->CreateSurface(&ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSBackBuffer,NULL);
	if( hRet != DD_OK )
	{
		return(FALSE);
	}
	
	
	hRet = lpDD->CreateClipper(0,&lpDDClip,NULL);
	if( hRet != DD_OK )
	{
		return FALSE;
	}
	
	lpDDClip->SetHWnd(0,m_hWnd);
	lpDDSPrimary->SetClipper(lpDDClip);
	
	Clear();
	
	return TRUE;
}

BOOL CDDrawWnd::Clear()
{
	DDBLTFX ddbltfxtmp;
	HRESULT hr;

	ddbltfxtmp.dwSize=sizeof(ddbltfxtmp);
	ddbltfxtmp.dwFillColor=0;

	hr=lpDDSBackBuffer->Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&ddbltfxtmp);
	if(FAILED(hr))
	{
		Restore();
		hr=lpDDSBackBuffer->Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&ddbltfxtmp);
		if(FAILED(hr))
		{
			return FALSE;
		}
	}

	return TRUE;
}

VOID CDDrawWnd::Shutdown()
{
	if(lpDDClip)
	{
		lpDDClip->Release();
		lpDDClip=NULL;
	}
	if(lpDDSPrimary)
	{
		lpDDSPrimary->Release();
		lpDDSPrimary=NULL;
	}
	if(lpDDSBackBuffer)
	{
		lpDDSBackBuffer->Release();
		lpDDSBackBuffer=NULL;
	}
	if(lpDD)
	{
		lpDD->Release();
		lpDD=NULL;
	}

}

void CDDrawWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	
	Shutdown();
}

void CDDrawWnd::OnPaint() 
{
	CPaintDC dc(this);

	Flip();
}

CDC *CDDrawWnd::GetDDrawDC()
{
	HRESULT hr;
	HDC dc;

	hr=lpDDSBackBuffer->GetDC(&dc);
	if(FAILED(hr))
	{
		Restore();
		hr=lpDDSBackBuffer->GetDC(&dc);
		if(FAILED(hr))
		{
			return NULL;
		}
	}

	DDrawDC.Attach(dc);

	return &DDrawDC;
}

BOOL CDDrawWnd::Restore()
{
	HRESULT hr;

	hr=lpDDSBackBuffer->Restore();

	hr=lpDDSPrimary->Restore();

	return TRUE;
}

VOID CDDrawWnd::ReleaseDDrawDC()
{
	HRESULT hr;

	hr=lpDDSBackBuffer->ReleaseDC(DDrawDC.m_hDC);

	DDrawDC.Detach();
}

BOOL CDDrawWnd::Flip()
{
	RECT r;
	HRESULT hr;

	GetWindowRect(&r);
	hr=lpDDSPrimary->Blt(&r,lpDDSBackBuffer,NULL,DDBLT_WAIT,NULL);
	if(FAILED(hr))
	{
		Restore();
		hr=lpDDSPrimary->Blt(&r,lpDDSBackBuffer,NULL,DDBLT_WAIT,NULL);
		if(FAILED(hr))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CDDrawWnd::Create(int left,int top,int width,int height,CWnd *parent)
{
	RECT r;

	r.left=left;
	r.right=left+width;
	r.top=top;
	r.bottom=top+height;

	return Create(NULL,NULL,0,r,parent,0);
}
