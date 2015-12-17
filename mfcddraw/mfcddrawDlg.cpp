// mfcddrawDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "mfcddraw.h"
#include "mfcddrawDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementierung
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
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcddrawDlg Dialogfeld

CMfcddrawDlg::CMfcddrawDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMfcddrawDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMfcddrawDlg)
	m_reflect = -1;
	m_amp = 0;
	m_speed = 0;
	m_hz = 0.0f;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcddrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMfcddrawDlg)
	DDX_Radio(pDX, IDC_NOREF, m_reflect);
	DDX_Text(pDX, IDC_AMP, m_amp);
	DDV_MinMaxInt(pDX, m_amp, 1, 1000);
	DDX_Text(pDX, IDC_SPEED, m_speed);
	DDV_MinMaxInt(pDX, m_speed, 10, 10000);
	DDX_Text(pDX, IDC_HZ, m_hz);
	DDV_MinMaxFloat(pDX, m_hz, 1.e-004f, 100.f);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMfcddrawDlg, CDialog)
	//{{AFX_MSG_MAP(CMfcddrawDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_NOREF, OnChange)
	ON_BN_CLICKED(IDC_OPENEND, OnChange)
	ON_BN_CLICKED(IDC_FIXEDEND, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CMfcddrawDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);


	ddraw.Create(140,10,640,480,this);

	SetTimer(1,25,NULL);

	m_reflect=0;
	m_hz=1;
	m_amp=100;
	m_speed=100;

	UpdateData(FALSE);
	
	CString str;
	str.Format("%f",m_hz);
	GetDlgItem(IDC_HZ)->SetWindowText(str);

	OnOK();


	return TRUE;
}

void CMfcddrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMfcddrawDlg::OnDestroy()
{
	KillTimer(1);
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

void CMfcddrawDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMfcddrawDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

VOID CMfcddrawDlg::Update()
{
	DWORD time=timeGetTime();
	static DWORD lasttime=timeGetTime();
	DWORD dTime=time-lasttime;


	ddraw.Update((float)dTime/1000);

	lasttime=time;
}

void CMfcddrawDlg::OnTimer(UINT nIDEvent) 
{	
	CDialog::OnTimer(nIDEvent);
	
	Update();
}

void CMfcddrawDlg::OnOK() 
{
	UpdateData();

	m_hz=fabs(m_hz);
	if(m_hz==0)m_hz=1;
	if(m_hz>100)m_hz=100;

	m_speed=fabs(m_speed);

	((CWaveGenerator*)ddraw.lpGenerator)->fFrequence=(float)m_hz;

	((CWaveGenerator*)ddraw.lpGenerator)->fAmp=(float)m_amp;

	ddraw.fSpeed=(float)m_speed;
	
	UpdateData(FALSE);

}

void CMfcddrawDlg::OnChange()
{
	UpdateData();
	
	switch(m_reflect)
	{
	case 0:
		ddraw.bReflect=FALSE;
		break;
	case 1:
		ddraw.bReflect=TRUE;
		ddraw.bFixedEnd=FALSE;
		break;
	case 2:
		ddraw.bReflect=TRUE;
		ddraw.bFixedEnd=TRUE;
		break;
	}
}
