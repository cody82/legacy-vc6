// BMPList.cpp : implementation file
//

#include "stdafx.h"
#include "BMPList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBMPList dialog


CBMPList::CBMPList(CWnd* pParent /*=NULL*/)
	: CDialog(CBMPList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBMPList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBMPList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBMPList)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBMPList, CDialog)
	//{{AFX_MSG_MAP(CBMPList)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBMPList message handlers

BOOL CBMPList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	POINT bmpsize;
	POINT wndsize;
	bmpsize.x=128;
	bmpsize.y=128;
	int i;

	RECT rect;
	GetClientRect(&rect);
	wndsize.x=rect.right;
	wndsize.y=rect.bottom;

	rect.top=wndsize.y/4-bmpsize.y/2;
	rect.bottom=rect.top+bmpsize.y;
	for(i=0;i<4;++i)
	{
		rect.left=wndsize.x/8*(2*i+1)-bmpsize.x/2;
		rect.right=rect.left+bmpsize.x;
		bitmaps[i].Create(NULL,NULL,WS_CHILD|WS_BORDER,rect,this,i+10);
		bitmaps[i].ShowWindow(SW_SHOW);
		bitmaps[i].LoadBitmap("c:\\temp\\image1.bmp");
	}

	rect.top=wndsize.y/4*3-bmpsize.y/2;
	rect.bottom=rect.top+bmpsize.y;
	for(i=0;i<4;++i)
	{
		rect.left=wndsize.x/8*(2*i+1)-bmpsize.x/2;
		rect.right=rect.left+bmpsize.x;
		bitmaps[i+4].Create(NULL,NULL,WS_CHILD|WS_BORDER,rect,this,i+10);
		bitmaps[i+4].ShowWindow(SW_SHOW);
		bitmaps[i+4].LoadBitmap("c:\\temp\\image1.bmp");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBMPList::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	POINT bmpsize;
	POINT wndsize;
	bmpsize.x=128;
	bmpsize.y=128;
	int i;

	RECT rect;
	GetClientRect(&rect);
	wndsize.x=rect.right;
	wndsize.y=rect.bottom;

	rect.top=wndsize.y/4-bmpsize.y/2;
	rect.bottom=rect.top+bmpsize.y;
	for(i=0;i<4;++i)
	{
		rect.left=wndsize.x/8*(2*i+1)-bmpsize.x/2;
		rect.right=rect.left+bmpsize.x;
		if(bitmaps[i].m_hWnd)bitmaps[i].SetWindowPos(NULL,rect.left,rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);
	}

	rect.top=wndsize.y/4*3-bmpsize.y/2;
	rect.bottom=rect.top+bmpsize.y;
	for(i=0;i<4;++i)
	{
		rect.left=wndsize.x/8*(2*i+1)-bmpsize.x/2;
		rect.right=rect.left+bmpsize.x;
		if(bitmaps[i].m_hWnd)bitmaps[i+4].SetWindowPos(NULL,rect.left,rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);
	}

	
}

void CBMPList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd* wnd;

	wnd=ChildWindowFromPoint(point,CWP_SKIPDISABLED);
	if(wnd)wnd->DestroyWindow();
	
	CDialog::OnLButtonDown(nFlags, point);
}
