// AviPlayMFC.cpp : implementation file
//

#include "AviPlayMFC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAviPlayMFC

CAviPlayMFC::CAviPlayMFC()
{
}

CAviPlayMFC::~CAviPlayMFC()
{
}


BEGIN_MESSAGE_MAP(CAviPlayMFC, CWnd)
	//{{AFX_MSG_MAP(CAviPlayMFC)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAviPlayMFC message handlers


BOOL CAviPlayMFC::Open(CString file)
{
	//SetTimer(1,40,NULL);
	//KillTimer(1);
	avi.Open(file);
	starttime=timeGetTime();
	return TRUE;
}

int CAviPlayMFC::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}

void CAviPlayMFC::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/*	CClientDC dc(this);
	if(!avi.Paint(dc.m_hDC))
	{
		if(Loop)
		{
			avi.CurrentTime=0;
			starttime=timeGetTime();
			avi.Paint(dc.m_hDC);
		}
	}
	avi.CurrentTime=timeGetTime()-starttime;
	sample=AVIStreamTimeToSample(avi.pstream,(LONG)avi.CurrentTime);*/
	CWnd::OnTimer(nIDEvent);
}

void StartThread()
{
	CAviPlayMFC::PaintThread(NULL);

}

BOOL CAviPlayMFC::Play(BOOL loop)
{
	//SetTimer(1,40,NULL);
	StartThread();
	return TRUE;
}

BOOL CAviPlayMFC::Stop()
{
	//KillTimer(1);
	return TRUE;

}

BOOL CAviPlayMFC::Pause()
{
	return TRUE;

}

DWORD CAviPlayMFC::PaintThread(void *p)
{

	return 0;
}

void CAviPlayMFC::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	avi.Paint(dc.m_hDC);
	
	// Do not call CWnd::OnPaint() for painting messages
}
