// avimfcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "avimfc.h"
#include "avimfcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAvimfcDlg dialog

CAvimfcDlg::CAvimfcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAvimfcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAvimfcDlg)
	m_edit1 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAvimfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAvimfcDlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAvimfcDlg, CDialog)
	//{{AFX_MSG_MAP(CAvimfcDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAvimfcDlg message handlers

BOOL CAvimfcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	RECT rect;
	rect.left=0;
	rect.right=320;
	rect.top=0;
	rect.bottom=240;
	avi.Create(NULL,NULL,WS_BORDER|WS_VISIBLE,rect,this,120);
	SetTimer(2,20,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAvimfcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAvimfcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAvimfcDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	avi.Open("alien2.avi");
	avi.Play(TRUE);
}

void CAvimfcDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_edit1=avi.sample;
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}
