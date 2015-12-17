// DirectShowWnd.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "mfcdirectshow.h"
#include "DirectShowWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirectShowWnd

CDirectShowWnd::CDirectShowWnd()
{
	pBA=NULL;
	pBV=NULL;
	pGB=NULL;
	pMC=NULL;
	pME=NULL;
	pMS=NULL;
	pVW=NULL;
}

CDirectShowWnd::~CDirectShowWnd()
{
}


BEGIN_MESSAGE_MAP(CDirectShowWnd, CWnd)
	//{{AFX_MSG_MAP(CDirectShowWnd)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_MOVE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDirectShowWnd 

BOOL CDirectShowWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	
	return CWnd::OnCommand(wParam, lParam);
}

void CDirectShowWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	Close();
}

void CDirectShowWnd::OnClose() 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	CWnd::OnClose();
}

void CDirectShowWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
	// Kein Aufruf von CWnd::OnPaint() für Zeichnungsnachrichten
}

void CDirectShowWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
    if(pVW)
	{
		LONG lHeight, lWidth;

	}
}

int CDirectShowWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Speziellen Erstellungscode hier einfügen
	
	return 0;
}

BOOL CDirectShowWnd::Open(LPCSTR file)
{
	strFile=file;

	Close();

    if (!Play())
        Close();

	//GoTo(10000);
	//GoToFrame(250);
	//SetSpeed(2);

	return TRUE;
}

VOID CDirectShowWnd::Close()
{
    HRESULT hr;
    
    // Relinquish ownership (IMPORTANT!) after hiding video window
    if(pVW)
    {
        hr = pVW->put_Visible(OAFALSE);
        hr = pVW->put_Owner(NULL);
    }

	if(pME)
	{
		pME->Release();
		pME=NULL;
	}
	if(pMS)
	{
		pMS->Release();
		pMS=NULL;
	}
	if(pMC)
	{
		pMC->Release();
		pMC=NULL;
	}
	if(pBA)
	{
		pBA->Release();
		pBA=NULL;
	}
	if(pBV)
	{
		pBV->Release();
		pBV=NULL;
	}
	if(pVW)
	{
		pVW->Release();
		pVW=NULL;
	}
	if(pGB)
	{
		pGB->Release();
		pGB=NULL;
	}	

}

BOOL CDirectShowWnd::Play()
{
    WCHAR wFile[MAX_PATH];
    HRESULT hr;

#ifndef UNICODE
    MultiByteToWideChar(CP_ACP, 0, strFile, -1, wFile, MAX_PATH);
#else
    lstrcpy(wFile, szFile);
#endif

    // Get the interface for DirectShow's GraphBuilder
    hr=CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGB);

    if(SUCCEEDED(hr))
    {
        // Have the graph construct its the appropriate graph automatically
        pGB->RenderFile(wFile, NULL);

        // QueryInterface for DirectShow interfaces
        pGB->QueryInterface(IID_IMediaControl, (void **)&pMC);
        pGB->QueryInterface(IID_IMediaEventEx, (void **)&pME);
        pGB->QueryInterface(IID_IMediaSeeking, (void **)&pMS);

        // Query for video interfaces, which may not be relevant for audio files
        pGB->QueryInterface(IID_IVideoWindow, (void **)&pVW);
        pGB->QueryInterface(IID_IBasicVideo, (void **)&pBV);

        // Query for audio interfaces, which may not be relevant for video-only files
        pGB->QueryInterface(IID_IBasicAudio, (void **)&pBA);

        // Have the graph signal event via window callbacks for performance
        pME->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);
        
		InitVideoWindow(1, 1);

        // Run the graph to play the media file
        pMC->Run();

    }

	return TRUE;
}

HRESULT CDirectShowWnd::InitVideoWindow(int nMultiplier, int nDivider)
{
    LONG lHeight, lWidth;
    HRESULT hr = S_OK;
    RECT rect,r2;

    if (!pBV)
        return S_OK;


    // Read the default video size
    pBV->GetVideoSize(&lWidth, &lHeight);

    // Account for requests of normal, half, or double size
    lWidth  = lWidth  * nMultiplier / nDivider;
    lHeight = lHeight * nMultiplier / nDivider;

    SetWindowPos(NULL, 0, 0, lWidth, lHeight, 
                 SWP_NOMOVE | SWP_NOOWNERZORDER);

 	pVW->put_WindowStyle(WS_VISIBLE|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	pVW->put_Owner((OAHWND)m_hWnd);
	pVW->put_WindowStyleEx(0);

    pVW->SetWindowPosition(0, 0, lWidth, lHeight);
	pVW->put_MessageDrain((OAHWND)m_hWnd);

	return hr;
}

LRESULT CDirectShowWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	switch(message)
	{
	case WM_GRAPHNOTIFY:
		HandleGraphEvent();
		break;
	}

	return CWnd::WindowProc(message, wParam, lParam);
}

HRESULT CDirectShowWnd::HandleGraphEvent(void)
{
    LONG evCode, evParam1, evParam2;
    HRESULT hr=S_OK;

    while(SUCCEEDED(pME->GetEvent(&evCode, &evParam1, &evParam2, 0)))
    {
        // Spin through the events
        hr = pME->FreeEventParams(evCode, evParam1, evParam2);

        if(EC_COMPLETE == evCode)
        {
            LONGLONG pos=0;

            // Reset to first frame of movie
            hr = pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                                   NULL, AM_SEEKING_NoPositioning);
            if (FAILED(hr))
            {
                // Some custom filters (like the Windows CE MIDI filter) 
                // may not implement seeking interfaces (IMediaSeeking)
                // to allow seeking to the start.  In that case, just stop 
                // and restart for the same effect.  This should not be
                // necessary in most cases.
                if (FAILED(hr = pMC->Stop()))
                {
                    //Msg(TEXT("Failed(0x%08lx) to stop media clip!\r\n"), hr);
                    break;
                }

                if (FAILED(hr = pMC->Run()))
                {
                    //Msg(TEXT("Failed(0x%08lx) to reset media clip!\r\n"), hr);
                    break;
                }
            }
        }
    }

    return hr;
}

BOOL CDirectShowWnd::Create(int x, int y, CWnd *parent)
{
	RECT r;

	r.left=x;
	r.right=x+320;
	r.top=y;
	r.bottom=y+240;

	return CWnd::Create(NULL,NULL,WS_VISIBLE|WS_BORDER,r,parent,0);

}

void CDirectShowWnd::OnMove(int x, int y) 
{
	CWnd::OnMove(x, y);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
}

BOOL CDirectShowWnd::ToggleFullscreen()
{
    LONG lMode;

    pVW->get_FullScreenMode(&lMode);
    if (lMode == OAFALSE)
		lMode=OATRUE;
	else
		lMode=OAFALSE;

    pVW->put_FullScreenMode(lMode);

	return TRUE;
}

void CDirectShowWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	LONG lMode;

    pVW->get_FullScreenMode(&lMode);
    if (lMode == OATRUE)
	{
		ToggleFullscreen();
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CDirectShowWnd::GoTo(LONG ms)
{
	HRESULT hr;

	LONGLONG ll;
	ll=ms*10000;

	hr=pMS->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);

	if(SUCCEEDED(hr))
	hr = pMS->SetPositions(&ll, AM_SEEKING_AbsolutePositioning ,
		NULL, AM_SEEKING_NoPositioning);

	return SUCCEEDED(hr);
}

BOOL CDirectShowWnd::GoToFrame(LONG frame)
{
	HRESULT hr;

	LONGLONG ll;
	ll=frame;

	hr=pMS->SetTimeFormat(&TIME_FORMAT_FRAME);

	if(SUCCEEDED(hr))
	hr = pMS->SetPositions(&ll, AM_SEEKING_AbsolutePositioning ,
		NULL, AM_SEEKING_NoPositioning);

	return SUCCEEDED(hr);

}

BOOL CDirectShowWnd::SetSpeed(FLOAT rate)
{
	HRESULT hr;

	hr=pMS->SetRate((double)rate);

	return SUCCEEDED(hr);
}

BOOL CDirectShowWnd::Pause()
{
	HRESULT hr;

	hr=pMC->Pause();

	return SUCCEEDED(hr);
}

BOOL CDirectShowWnd::Stop()
{
	HRESULT hr;

	hr=pMC->Stop();

	return SUCCEEDED(hr);
}
