// BitmapWnd.cpp : implementation file
//

#include "stdafx.h"
#include "BitmapWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapWnd

CBitmapWnd::CBitmapWnd()
{
	m_Stretch=FALSE;
	m_Bitmap=NULL;
}

CBitmapWnd::~CBitmapWnd()
{
	if(m_Bitmap)DeleteObject(m_Bitmap);
}


BEGIN_MESSAGE_MAP(CBitmapWnd, CWnd)
	//{{AFX_MSG_MAP(CBitmapWnd)
	ON_WM_PAINT()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBitmapWnd message handlers

BOOL CBitmapWnd::LoadBitmap(LPCSTR file)
{
	if(m_Bitmap)DeleteObject(m_Bitmap);
	m_Bitmap = (HBITMAP)LoadImage(NULL,file, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	if(m_Bitmap)return TRUE;
	return FALSE;
}

void CBitmapWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	HDC       hdcBits;
    BITMAP    bm;
	RECT rect;
	
	// TODO: Add your message handler code here
	if(!m_Bitmap)return;

    hdcBits = CreateCompatibleDC(dc.m_hDC);
    GetObject(m_Bitmap,sizeof(BITMAP),(LPSTR)&bm);
    SelectObject(hdcBits,m_Bitmap);

	GetClientRect(&rect);

	if(m_Stretch)
		StretchBlt(dc.m_hDC,0,0,rect.right,rect.bottom,hdcBits,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	else
		BitBlt(dc.m_hDC,0,0,rect.right,rect.bottom,hdcBits,0,0,SRCCOPY);

    DeleteDC(hdcBits);

	// Do not call CWnd::OnPaint() for painting messages
}

void CBitmapWnd::OnMove(int x, int y) 
{
	CWnd::OnMove(x, y);
	
	CClientDC dc(this);
	// TODO: Add your message handler code here
	HDC       hdcBits;
    BITMAP    bm;
	RECT rect;
	
	// TODO: Add your message handler code here
	if(!m_Bitmap)return;

    hdcBits = CreateCompatibleDC(dc.m_hDC);
    GetObject(m_Bitmap,sizeof(BITMAP),(LPSTR)&bm);
    SelectObject(hdcBits,m_Bitmap);

	GetClientRect(&rect);

	if(m_Stretch)
		StretchBlt(dc.m_hDC,0,0,rect.right,rect.bottom,hdcBits,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	else
		BitBlt(dc.m_hDC,0,0,rect.right,rect.bottom,hdcBits,0,0,SRCCOPY);

    DeleteDC(hdcBits);

}
