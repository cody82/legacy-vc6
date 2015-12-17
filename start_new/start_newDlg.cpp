// start_newDlg.cpp : implementation file
//

#include "stdafx.h"
#include "start_new.h"
#include "start_newDlg.h"
#include "playersdialog.h"
#include "optionssheet.h"
#include "optionpages.h"
#include "shipselectdlg.h"
#include <mmsystem.h>
#include <dib.h>
#include "asteroids.h"
#include <dibapi.h>
#include <bmputil.h>
#include <cpakfile.h>

//HANDLE hdib;
HBITMAP hbm;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStart_newDlg dialog

CStart_newDlg::CStart_newDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStart_newDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStart_newDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStart_newDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStart_newDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStart_newDlg, CDialog)
	//{{AFX_MSG_MAP(CStart_newDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_CREDITS, OnCredits)
	ON_BN_CLICKED(IDC_OPTIONS, OnOptions)
	ON_BN_CLICKED(IDC_STARTMULTI, OnStartmulti)
	ON_BN_CLICKED(IDC_EDITOR, OnEditor)
	ON_BN_CLICKED(IDC_STATS, OnStats)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStart_newDlg message handlers

BOOL CStart_newDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetFileAttributes("config.ini",FILE_ATTRIBUTE_NORMAL);
	sndPlaySound("sounds\\beep-01",0);
	hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"bitmaps\\tie1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	//hdib=ReadDIBFile("bitmaps\\tie1.bmp");
	//HANDLE hf;
	//hf=CreateFile("tie2.bmp",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	//hdib=(HANDLE)ReadDIBFileInFile(hf,265734,278075);

	//hbm=BitmapFromDib(hdib,NULL);
/*	pf.Open("test.pak");
	PACK p;
	pf.GetFileInfo("btn_exit001.bmp",&p);
	
	HANDLE hf;
	hf=CreateFile(pf.packfile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	hdib=(HANDLE)ReadDIBFileInFile(hf,p.Begin,p.End-p.Begin);

	hbm=BitmapFromDib(hdib,NULL);
*/
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStart_newDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStart_newDlg::OnPaint() 
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
		CPaintDC dc(this); // device context for painting

		DrawBitmap(dc.m_hDC,0,0,hbm,SRCCOPY);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStart_newDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CStart_newDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	sndPlaySound("sounds\\beep-01",0);
	CDialog::OnCancel();
}

void CStart_newDlg::OnCredits() 
{
	// TODO: Add your control notification handler code here
	//system("credits.exe");
	sndPlaySound("sounds\\beep-01",0);
	WinExec("credits.exe",SW_SHOW);
}

void CStart_newDlg::OnOptions() 
{
	// TODO: Add your control notification handler code here
	COptionsSheet os(IDS_OPTIONS);

	os.DoModal();
	sndPlaySound("sounds\\beep-01",0);
}

void CStart_newDlg::OnStartmulti() 
{
	// TODO: Add your control notification handler code here
	CShipSelectDlg dlg;
	sndPlaySound("sounds\\beep-01",0);
	if(dlg.DoModal()==IDOK)
		WinExec("game1.exe",SW_SHOW);
	//system("game1.exe");
}

void CStart_newDlg::OnEditor() 
{
	// TODO: Add your control notification handler code here
	
	sndPlaySound("sounds\\beep-01",0);
	WinExec("game1ed.exe",SW_SHOW);
	//system("game1ed.exe");
}

void CStart_newDlg::OnStats() 
{
	// TODO: Add your control notification handler code here
	sndPlaySound("sounds\\beep-01",0);
	WinExec("statistics.exe",SW_SHOW);

}
