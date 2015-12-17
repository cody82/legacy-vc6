// xswstatisticDlg.cpp : implementation file
//

#include "stdafx.h"
#include "xswstatistic.h"
#include "xswstatisticDlg.h"
#include <profiles.h>
#include <dib.h>

typedef struct
	{
		int frags[4];	
		int kills[4][4];
		int deaths[4];
		int suicides[4];
		int shots[4];
		int hits[4];
	} STATS;

static HANDLE hdib;

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
// CXswstatisticDlg dialog

CXswstatisticDlg::CXswstatisticDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXswstatisticDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXswstatisticDlg)
	m_killed1 = _T("");
	m_killed2 = _T("");
	m_killed3 = _T("");
	m_killed4 = _T("");
	m_killer1 = _T("");
	m_killer2 = _T("");
	m_killer3 = _T("");
	m_killer4 = _T("");
	m_kills11 = 0;
	m_kills12 = 0;
	m_kills13 = 0;
	m_kills14 = 0;
	m_kills21 = 0;
	m_kills22 = 0;
	m_kills23 = 0;
	m_kills24 = 0;
	m_kills31 = 0;
	m_kills32 = 0;
	m_kills33 = 0;
	m_kills34 = 0;
	m_kills41 = 0;
	m_kills42 = 0;
	m_kills43 = 0;
	m_kills44 = 0;
	m_totalkills1 = 0;
	m_totalkills2 = 0;
	m_totalkills3 = 0;
	m_totalkills4 = 0;
	m_fire1 = _T("");
	m_fire2 = _T("");
	m_fire3 = _T("");
	m_fire4 = _T("");
	m_hits1 = 0;
	m_hits2 = 0;
	m_hits3 = 0;
	m_hits4 = 0;
	m_shots1 = 0;
	m_shots2 = 0;
	m_shots3 = 0;
	m_shots4 = 0;
	m_accuracy1 = 0.0f;
	m_accuracy2 = 0.0f;
	m_accuracy3 = 0.0f;
	m_accuracy4 = 0.0f;
	m_deaths1 = 0;
	m_deaths2 = 0;
	m_deaths3 = 0;
	m_deaths4 = 0;
	m_frags1 = 0;
	m_frags2 = 0;
	m_frags4 = 0;
	m_frags3 = 0;
	m_suicides1 = 0;
	m_suicides2 = 0;
	m_suicides3 = 0;
	m_suicides4 = 0;
	m_totalkilled1 = 0;
	m_totalkilled2 = 0;
	m_totalkilled3 = 0;
	m_totalkilled4 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXswstatisticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXswstatisticDlg)
	DDX_Text(pDX, IDC_KILLED1, m_killed1);
	DDX_Text(pDX, IDC_KILLED2, m_killed2);
	DDX_Text(pDX, IDC_KILLED3, m_killed3);
	DDX_Text(pDX, IDC_KILLED4, m_killed4);
	DDX_Text(pDX, IDC_KILLER1, m_killer1);
	DDX_Text(pDX, IDC_KILLER2, m_killer2);
	DDX_Text(pDX, IDC_KILLER3, m_killer3);
	DDX_Text(pDX, IDC_KILLER4, m_killer4);
	DDX_Text(pDX, IDC_KILL11, m_kills11);
	DDX_Text(pDX, IDC_KILL12, m_kills12);
	DDX_Text(pDX, IDC_KILL13, m_kills13);
	DDX_Text(pDX, IDC_KILL14, m_kills14);
	DDX_Text(pDX, IDC_KILL21, m_kills21);
	DDX_Text(pDX, IDC_KILL22, m_kills22);
	DDX_Text(pDX, IDC_KILL23, m_kills23);
	DDX_Text(pDX, IDC_KILL24, m_kills24);
	DDX_Text(pDX, IDC_KILL31, m_kills31);
	DDX_Text(pDX, IDC_KILL32, m_kills32);
	DDX_Text(pDX, IDC_KILL33, m_kills33);
	DDX_Text(pDX, IDC_KILL34, m_kills34);
	DDX_Text(pDX, IDC_KILL41, m_kills41);
	DDX_Text(pDX, IDC_KILL42, m_kills42);
	DDX_Text(pDX, IDC_KILL43, m_kills43);
	DDX_Text(pDX, IDC_KILL44, m_kills44);
	DDX_Text(pDX, IDC_TOTALKILLS1, m_totalkills1);
	DDX_Text(pDX, IDC_TOTALKILLS2, m_totalkills2);
	DDX_Text(pDX, IDC_TOTALKILLS3, m_totalkills3);
	DDX_Text(pDX, IDC_TOTALKILLS4, m_totalkills4);
	DDX_Text(pDX, IDC_FIRE1, m_fire1);
	DDX_Text(pDX, IDC_FIRE2, m_fire2);
	DDX_Text(pDX, IDC_FIRE3, m_fire3);
	DDX_Text(pDX, IDC_FIRE4, m_fire4);
	DDX_Text(pDX, IDC_HITS1, m_hits1);
	DDX_Text(pDX, IDC_HITS2, m_hits2);
	DDX_Text(pDX, IDC_HITS3, m_hits3);
	DDX_Text(pDX, IDC_HITS4, m_hits4);
	DDX_Text(pDX, IDC_SHOTS1, m_shots1);
	DDX_Text(pDX, IDC_SHOTS2, m_shots2);
	DDX_Text(pDX, IDC_SHOTS3, m_shots3);
	DDX_Text(pDX, IDC_SHOTS4, m_shots4);
	DDX_Text(pDX, IDC_ACCFIRE1, m_accuracy1);
	DDX_Text(pDX, IDC_ACCFIRE2, m_accuracy2);
	DDX_Text(pDX, IDC_ACCFIRE3, m_accuracy3);
	DDX_Text(pDX, IDC_ACCFIRE4, m_accuracy4);
	DDX_Text(pDX, IDC_DEATHS1, m_deaths1);
	DDX_Text(pDX, IDC_DEATHS2, m_deaths2);
	DDX_Text(pDX, IDC_DEATHS3, m_deaths3);
	DDX_Text(pDX, IDC_DEATHS4, m_deaths4);
	DDX_Text(pDX, IDC_FRAGS1, m_frags1);
	DDX_Text(pDX, IDC_FRAGS2, m_frags2);
	DDX_Text(pDX, IDC_FRAGS4, m_frags4);
	DDX_Text(pDX, IDC_FRAGS3, m_frags3);
	DDX_Text(pDX, IDC_SUICIDES1, m_suicides1);
	DDX_Text(pDX, IDC_SUICIDES2, m_suicides2);
	DDX_Text(pDX, IDC_SUICIDES3, m_suicides3);
	DDX_Text(pDX, IDC_SUICIDES4, m_suicides4);
	DDX_Text(pDX, IDC_TOTALKILLED1, m_totalkilled1);
	DDX_Text(pDX, IDC_TOTALKILLED2, m_totalkilled2);
	DDX_Text(pDX, IDC_TOTALKILLED3, m_totalkilled3);
	DDX_Text(pDX, IDC_TOTALKILLED4, m_totalkilled4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXswstatisticDlg, CDialog)
	//{{AFX_MSG_MAP(CXswstatisticDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXswstatisticDlg message handlers

BOOL CXswstatisticDlg::OnInitDialog()
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
	STATS stats;
	HANDLE h;
	int i;
	unsigned long nbytes;

	h=CreateFile("stats.bin",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(h)
	{
		ReadFile(h,&stats,sizeof(stats),&nbytes,NULL);
		CloseHandle(h);
	}

	hdib=OpenDIB("bg.bmp");

	m_kills11=stats.kills[0][0];
	m_kills12=stats.kills[0][1];
	m_kills13=stats.kills[0][2];
	m_kills14=stats.kills[0][3];

	m_kills21=stats.kills[1][0];
	m_kills22=stats.kills[1][1];
	m_kills23=stats.kills[1][2];
	m_kills24=stats.kills[1][3];

	m_kills31=stats.kills[2][0];
	m_kills32=stats.kills[2][1];
	m_kills33=stats.kills[2][2];
	m_kills34=stats.kills[2][3];
	
	m_kills41=stats.kills[3][0];
	m_kills42=stats.kills[3][1];
	m_kills43=stats.kills[3][2];
	m_kills44=stats.kills[3][3];

	m_totalkills1=stats.kills[0][1]+stats.kills[0][2]+stats.kills[0][3];
	m_totalkills2=stats.kills[1][0]+stats.kills[1][2]+stats.kills[1][3];
	m_totalkills3=stats.kills[2][0]+stats.kills[2][1]+stats.kills[2][3];
	m_totalkills4=stats.kills[3][0]+stats.kills[3][1]+stats.kills[3][2];

	i=GetPrivateProfileIntCurrentDir("config.ini","game1","players",0);
	if(i>=1)
	{
		GetPrivateProfileStringCurrentDir("config.ini","game1","player1name",m_killer1.GetBuffer(64),64);
		m_killed1=m_killer1;
		m_fire1=m_killer1;
	}
	if(i>=2)
	{
		GetPrivateProfileStringCurrentDir("config.ini","game1","player2name",m_killer2.GetBuffer(64),64);
		m_killed2=m_killer2;
		m_fire2=m_killer2;
	}
	if(i>=3)
	{
		GetPrivateProfileStringCurrentDir("config.ini","game1","player3name",m_killer3.GetBuffer(64),64);
		m_killed3=m_killer3;
		m_fire3=m_killer3;
	}
	if(i>=4)
	{
		GetPrivateProfileStringCurrentDir("config.ini","game1","player4name",m_killer4.GetBuffer(64),64);
		m_killed4=m_killer4;
		m_fire4=m_killer4;
	}



	m_shots1=stats.shots[0];
	m_shots2=stats.shots[1];
	m_shots3=stats.shots[2];
	m_shots4=stats.shots[3];

	m_hits1=stats.hits[0];
	m_hits2=stats.hits[1];
	m_hits3=stats.hits[2];
	m_hits4=stats.hits[3];

	if(stats.shots[0]>0)
		m_accuracy1=(float)stats.hits[0]/(float)stats.shots[0]*100;
	else m_accuracy1=0;

	if(stats.shots[1]>0)
		m_accuracy2=(float)stats.hits[1]/(float)stats.shots[1]*100;
	else m_accuracy2=0;

	if(stats.shots[2]>0)
		m_accuracy3=(float)stats.hits[2]/(float)stats.shots[2]*100;
	else m_accuracy3=0;

	if(stats.shots[3]>0)
		m_accuracy4=(float)stats.hits[3]/(float)stats.shots[3]*100;
	else m_accuracy4=0;


	m_frags1=stats.frags[0];
	m_frags2=stats.frags[1];
	m_frags3=stats.frags[2];
	m_frags4=stats.frags[3];

	m_deaths1=stats.deaths[0];
	m_deaths2=stats.deaths[1];
	m_deaths3=stats.deaths[2];
	m_deaths4=stats.deaths[3];

	m_suicides1=stats.suicides[0];
	m_suicides2=stats.suicides[1];
	m_suicides3=stats.suicides[2];
	m_suicides4=stats.suicides[3];

	m_totalkilled1=stats.kills[1][0]+stats.kills[2][0]+stats.kills[3][0];
	m_totalkilled2=stats.kills[0][1]+stats.kills[2][1]+stats.kills[3][1];
	m_totalkilled3=stats.kills[0][2]+stats.kills[1][2]+stats.kills[3][2];
	m_totalkilled4=stats.kills[0][3]+stats.kills[1][3]+stats.kills[2][3];

	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXswstatisticDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CXswstatisticDlg::OnPaint() 
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
		CDialog::OnPaint();
		DibBlt(dc.m_hDC,0,0,800,600,hdib,0,0,0);
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXswstatisticDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
