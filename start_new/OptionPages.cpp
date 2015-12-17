// OptionPages.cpp : implementation file
//

#include "stdafx.h"
#include "start_new.h"
#include "OptionPages.h"
#include <profiles.h>
#include <int2str.h>
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//OptionPage4 variables
int up[4],down[4],left[4],right[4],fire[4],special[4];


/////////////////////////////////////////////////////////////////////////////
// COptionPage1 property page

IMPLEMENT_DYNCREATE(COptionPage1, CPropertyPage)

COptionPage1::COptionPage1() : CPropertyPage(COptionPage1::IDD)
{
	//{{AFX_DATA_INIT(COptionPage1)
	m_name1 = _T("");
	m_name2 = _T("");
	m_name3 = _T("");
	m_name4 = _T("");
	m_borg = FALSE;
	m_borgtime = 0;
	//}}AFX_DATA_INIT
	//m_psp.dwFlags |= PSH_NOAPPLYNOW;
	m_psp.dwFlags &=~PSP_HASHELP;
}

COptionPage1::~COptionPage1()
{

}

void COptionPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionPage1)
	DDX_Text(pDX, IDC_NAME1, m_name1);
	DDX_Text(pDX, IDC_NAME2, m_name2);
	DDX_Text(pDX, IDC_NAME3, m_name3);
	DDX_Text(pDX, IDC_NAME4, m_name4);
	DDX_Check(pDX, IDC_BORG, m_borg);
	DDX_Text(pDX, IDC_BORGTIME, m_borgtime);
	DDV_MinMaxInt(pDX, m_borgtime, -1, 1000000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionPage1, CPropertyPage)
	//{{AFX_MSG_MAP(COptionPage1)
	ON_BN_CLICKED(IDC_BORG, OnBorg)
	ON_CBN_EDITCHANGE(IDC_PLAYERS, OnEditchangePlayers)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionPage1 message handlers
/////////////////////////////////////////////////////////////////////////////
// COptionPage2 property page

IMPLEMENT_DYNCREATE(COptionPage2, CPropertyPage)

COptionPage2::COptionPage2() : CPropertyPage(COptionPage2::IDD)
{
	m_psp.dwFlags &=~PSP_HASHELP;
	//{{AFX_DATA_INIT(COptionPage2)
	m_triplebuffering = FALSE;
	m_windowmode = FALSE;
	m_resx = 0;
	m_resy = 0;
	//}}AFX_DATA_INIT
}

COptionPage2::~COptionPage2()
{
}

void COptionPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionPage2)
	DDX_Check(pDX, IDC_TRIPLEBUFFERING, m_triplebuffering);
	DDX_Check(pDX, IDC_WINDOWMODE, m_windowmode);
	DDX_Text(pDX, IDC_RESX, m_resx);
	DDV_MinMaxUInt(pDX, m_resx, 640, 1600);
	DDX_Text(pDX, IDC_RESY, m_resy);
	DDV_MinMaxUInt(pDX, m_resy, 400, 1200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionPage2, CPropertyPage)
	//{{AFX_MSG_MAP(COptionPage2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionPage2 message handlers
/////////////////////////////////////////////////////////////////////////////
// COptionPage3 property page

IMPLEMENT_DYNCREATE(COptionPage3, CPropertyPage)

COptionPage3::COptionPage3() : CPropertyPage(COptionPage3::IDD)
{
	m_psp.dwFlags &=~PSP_HASHELP;
	//{{AFX_DATA_INIT(COptionPage3)
	m_deathsound = _T("");
	m_showinfo = FALSE;
	m_loadpicture = _T("");
	m_backgroundsound = _T("");
	m_backgroundimage = _T("");
	m_cdtrack = 0;
	m_cdplay = FALSE;
	m_gamespeed = 0;
	//}}AFX_DATA_INIT
}

COptionPage3::~COptionPage3()
{
}

void COptionPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionPage3)
	DDX_Text(pDX, IDC_DEATHSOUND, m_deathsound);
	DDX_Check(pDX, IDC_INFO, m_showinfo);
	DDX_Text(pDX, IDC_LOADPICTURE, m_loadpicture);
	DDX_Text(pDX, IDC_SOUND, m_backgroundsound);
	DDX_Text(pDX, IDC_IMAGE, m_backgroundimage);
	DDX_Text(pDX, IDC_CDTRACK, m_cdtrack);
	DDX_Check(pDX, IDC_CDPLAY, m_cdplay);
	DDX_Text(pDX, IDC_GAMESPEED, m_gamespeed);
	DDV_MinMaxInt(pDX, m_gamespeed, 1, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionPage3, CPropertyPage)
	//{{AFX_MSG_MAP(COptionPage3)
	ON_BN_CLICKED(IDC_CDPLAY, OnCdplay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionPage3 message handlers

void COptionPage1::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	CString string;

	GetDlgItemText(IDC_PLAYERS,string);
	WritePrivateProfileStringCurrentDir("config.ini","game1","players",string.GetBuffer(64));

	GetDlgItemText(IDC_CONTROL1,string);
	WritePrivateProfileStringCurrentDir("config.ini","game1","player1control",string.GetBuffer(64));

	GetDlgItemText(IDC_CONTROL2,string);
	WritePrivateProfileStringCurrentDir("config.ini","game1","player2control",string.GetBuffer(64));

	GetDlgItemText(IDC_CONTROL3,string);
	WritePrivateProfileStringCurrentDir("config.ini","game1","player3control",string.GetBuffer(64));

	GetDlgItemText(IDC_CONTROL4,string);
	WritePrivateProfileStringCurrentDir("config.ini","game1","player4control",string.GetBuffer(64));

	//Names
	WritePrivateProfileStringCurrentDir("config.ini","game1","player1name",m_name1.GetBuffer(64));
	WritePrivateProfileStringCurrentDir("config.ini","game1","player2name",m_name2.GetBuffer(64));
	WritePrivateProfileStringCurrentDir("config.ini","game1","player3name",m_name3.GetBuffer(64));
	WritePrivateProfileStringCurrentDir("config.ini","game1","player4name",m_name4.GetBuffer(64));
	
	if(m_borg)
	{
		WritePrivateProfileIntCurrentDir("config.ini","game1","borgtime",m_borgtime);
	}
	else WritePrivateProfileIntCurrentDir("config.ini","game1","borgtime",-1);

	CPropertyPage::OnOK();
}

void COptionPage2::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	char tmpstr[64];

	WritePrivateProfileIntCurrentDir("config.ini","game1","backbuffers",m_triplebuffering+1);
	WritePrivateProfileIntCurrentDir("config.ini","game1","window",m_windowmode);
	
	GetDlgItemText(IDC_COLORDEPTH,tmpstr,64);
	WritePrivateProfileStringCurrentDir("config.ini","game1","colordepth",tmpstr);

	WritePrivateProfileIntCurrentDir("config.ini","game1","xres",m_resx);
	WritePrivateProfileIntCurrentDir("config.ini","game1","yres",m_resy);

	CPropertyPage::OnOK();
}

void COptionPage3::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);

	WritePrivateProfileStringCurrentDir("config.ini","game1","backgroundimage",m_backgroundimage.GetBuffer(64));

	WritePrivateProfileStringCurrentDir("config.ini","game1","backgroundsound",m_backgroundsound.GetBuffer(64));

	WritePrivateProfileStringCurrentDir("config.ini","game1","deathsound",m_deathsound.GetBuffer(64));
	
	WritePrivateProfileStringCurrentDir("config.ini","game1","loadpicture",m_loadpicture.GetBuffer(64));

	WritePrivateProfileIntCurrentDir("config.ini","game1","showinformation",m_showinfo);
	if(m_cdplay)
		WritePrivateProfileIntCurrentDir("config.ini","game1","playcdtrack",m_cdtrack);
	else WritePrivateProfileIntCurrentDir("config.ini","game1","playcdtrack",0);
	
	WritePrivateProfileIntCurrentDir("config.ini","game1","gamespeed",m_gamespeed);

	CPropertyPage::OnOK();
}

BOOL COptionPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	char tmpstr[64];
	int i;
	
	//Controls and Players
	GetPrivateProfileStringCurrentDir("config.ini","game1","players",tmpstr,64);
	i=((CComboBox*)GetDlgItem(IDC_PLAYERS))->FindStringExact(0,tmpstr);
	((CComboBox*)GetDlgItem(IDC_PLAYERS))->SetCurSel(i);

	GetPrivateProfileStringCurrentDir("config.ini","game1","player1control",tmpstr,64);
	i=((CComboBox*)GetDlgItem(IDC_CONTROL1))->FindStringExact(0,tmpstr);
	((CComboBox*)GetDlgItem(IDC_CONTROL1))->SetCurSel(i);

	GetPrivateProfileStringCurrentDir("config.ini","game1","player2control",tmpstr,64);
	i=((CComboBox*)GetDlgItem(IDC_CONTROL2))->FindStringExact(0,tmpstr);
	((CComboBox*)GetDlgItem(IDC_CONTROL2))->SetCurSel(i);

	GetPrivateProfileStringCurrentDir("config.ini","game1","player3control",tmpstr,64);
	i=((CComboBox*)GetDlgItem(IDC_CONTROL3))->FindStringExact(0,tmpstr);
	((CComboBox*)GetDlgItem(IDC_CONTROL3))->SetCurSel(i);

	GetPrivateProfileStringCurrentDir("config.ini","game1","player4control",tmpstr,64);
	i=((CComboBox*)GetDlgItem(IDC_CONTROL4))->FindStringExact(0,tmpstr);
	((CComboBox*)GetDlgItem(IDC_CONTROL4))->SetCurSel(i);

	//Names
	GetPrivateProfileStringCurrentDir("config.ini","game1","player1name",tmpstr,64);
	m_name1=tmpstr;
	GetPrivateProfileStringCurrentDir("config.ini","game1","player2name",tmpstr,64);
	m_name2=tmpstr;
	GetPrivateProfileStringCurrentDir("config.ini","game1","player3name",tmpstr,64);
	m_name3=tmpstr;
	GetPrivateProfileStringCurrentDir("config.ini","game1","player4name",tmpstr,64);
	m_name4=tmpstr;

	i=GetPrivateProfileIntCurrentDir("config.ini","game1","borgtime",-1);
	if(i>-1)
	{
		m_borg=TRUE;
		m_borgtime=i;
	}
	else m_borg=FALSE;

	UpdateData(FALSE);
	OnBorg();
	OnEditchangePlayers();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL COptionPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	char tmpstr[64];
	int i;

	m_windowmode=GetPrivateProfileIntCurrentDir("config.ini","game1","window",0);
	m_triplebuffering=GetPrivateProfileIntCurrentDir("config.ini","game1","backbuffers",0)-1;
	
	GetPrivateProfileStringCurrentDir("config.ini","game1","colordepth",tmpstr,64);
	i=((CComboBox*)GetDlgItem(IDC_COLORDEPTH))->FindStringExact(0,tmpstr);
	((CComboBox*)GetDlgItem(IDC_COLORDEPTH))->SetCurSel(i);

	m_resx=GetPrivateProfileIntCurrentDir("config.ini","game1","xres",0);
	m_resy=GetPrivateProfileIntCurrentDir("config.ini","game1","yres",0);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL COptionPage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i;

	GetPrivateProfileStringCurrentDir("config.ini","game1","backgroundimage",m_backgroundimage.GetBuffer(64),64);
	GetPrivateProfileStringCurrentDir("config.ini","game1","backgroundsound",m_backgroundsound.GetBuffer(64),64);
	GetPrivateProfileStringCurrentDir("config.ini","game1","deathsound",m_deathsound.GetBuffer(64),64);
	GetPrivateProfileStringCurrentDir("config.ini","game1","loadpicture",m_loadpicture.GetBuffer(64),64);
	m_showinfo=GetPrivateProfileIntCurrentDir("config.ini","game1","showinformation",0);
		
	i=GetPrivateProfileIntCurrentDir("config.ini","game1","playcdtrack",0);
	if(i>0)
	{
		m_cdplay=TRUE;
		m_cdtrack=i;
	}
	else m_cdplay=FALSE;

	m_gamespeed=GetPrivateProfileIntCurrentDir("config.ini","game1","gamespeed",100);
	
	UpdateData(FALSE);
	COptionPage3::OnCdplay();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionPage1::OnBorg()
{
	// TODO: Add your control notification handler code here
	BOOL b;

	b=((CButton*)GetDlgItem(IDC_BORG))->GetCheck();
	((CWnd*)GetDlgItem(IDC_BORGTIME))->EnableWindow(b);
	UpdateData();
	if(m_borgtime<=0)
		m_borgtime=60000;
	UpdateData(FALSE);
}

void COptionPage1::OnEditchangePlayers() 
{
	// TODO: Add your control notification handler code here
/*	char tmpstr[64];
	int i;
	//((CComboBox*)GetDlgItem(IDC_PLAYERS))->GetText(((CComboBox*)GetDlgItem(IDC_PLAYERS))->GetCurSel(),tmpstr);
	GetDlgItemText(IDC_PLAYERS,tmpstr,64);
	i=tmpstr[0]-48;

	switch(i)
	{
	case 1:
		((CComboBox*)GetDlgItem(IDC_NAME1))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_NAME2))->EnableWindow(FALSE);
		((CWnd*)GetDlgItem(IDC_NAME3))->EnableWindow(FALSE);
		((CWnd*)GetDlgItem(IDC_NAME4))->EnableWindow(FALSE);
		
		((CWnd*)GetDlgItem(IDC_CONTROL1))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_CONTROL2))->EnableWindow(FALSE);
		((CWnd*)GetDlgItem(IDC_CONTROL3))->EnableWindow(FALSE);
		((CWnd*)GetDlgItem(IDC_CONTROL4))->EnableWindow(FALSE);
		break;
	case 2:
		((CWnd*)GetDlgItem(IDC_NAME1))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_NAME2))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_NAME3))->EnableWindow(FALSE);
		((CWnd*)GetDlgItem(IDC_NAME4))->EnableWindow(FALSE);
		
		((CWnd*)GetDlgItem(IDC_CONTROL1))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_CONTROL2))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_CONTROL3))->EnableWindow(FALSE);
		((CWnd*)GetDlgItem(IDC_CONTROL4))->EnableWindow(FALSE);
		break;
	case 3:
		((CWnd*)GetDlgItem(IDC_NAME1))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_NAME2))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_NAME3))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_NAME4))->EnableWindow(FALSE);
		
		((CWnd*)GetDlgItem(IDC_CONTROL1))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_CONTROL2))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_CONTROL3))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_CONTROL4))->EnableWindow(FALSE);
		break;
	case 4:
		((CWnd*)GetDlgItem(IDC_NAME1))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_NAME2))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_NAME3))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_NAME4))->EnableWindow();
		
		((CWnd*)GetDlgItem(IDC_CONTROL1))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_CONTROL2))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_CONTROL3))->EnableWindow();
		((CWnd*)GetDlgItem(IDC_CONTROL4))->EnableWindow();
		break;
	}
*/
}
/////////////////////////////////////////////////////////////////////////////
// COptionPage4 property page

IMPLEMENT_DYNCREATE(COptionPage4, CPropertyPage)

COptionPage4::COptionPage4() : CPropertyPage(COptionPage4::IDD)
{
	m_psp.dwFlags &=~PSP_HASHELP;
	//{{AFX_DATA_INIT(COptionPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COptionPage4::~COptionPage4()
{
}

void COptionPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionPage4)
	DDX_Control(pDX, IDC_SPECIAL, m_special1);
	DDX_Control(pDX, IDC_KEYBOARD, m_keyboard);
	DDX_Control(pDX, IDC_UP1, m_up1);
	DDX_Control(pDX, IDC_RIGHT1, m_right1);
	DDX_Control(pDX, IDC_LEFT1, m_left1);
	DDX_Control(pDX, IDC_FIRE1, m_fire1);
	DDX_Control(pDX, IDC_DOWN1, m_down1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionPage4, CPropertyPage)
	//{{AFX_MSG_MAP(COptionPage4)
	ON_CBN_EDITCHANGE(IDC_KEYBOARD, OnEditchangeKeyboard)
	ON_CBN_SELCHANGE(IDC_KEYBOARD, OnSelchangeKeyboard)
	ON_CBN_SELCHANGE(IDC_DOWN1, OnSelchangeDown1)
	ON_CBN_SELCHANGE(IDC_FIRE1, OnSelchangeFire1)
	ON_CBN_SELCHANGE(IDC_LEFT1, OnSelchangeLeft1)
	ON_CBN_SELCHANGE(IDC_RIGHT1, OnSelchangeRight1)
	ON_CBN_SELCHANGE(IDC_UP1, OnSelchangeUp1)
	ON_CBN_SELCHANGE(IDC_SPECIAL, OnSelchangeSpecial)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionPage4 message handlers

BOOL COptionPage4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i;
	char tmpstr[64];
	for(i=0;i<4;++i)
	{
		sprintf(tmpstr,"p%dcontrol",i+1);
		up[i]=GetPrivateProfileIntCurrentDir("keyboard.ini",tmpstr,"up",-1);
		down[i]=GetPrivateProfileIntCurrentDir("keyboard.ini",tmpstr,"down",-1);
		left[i]=GetPrivateProfileIntCurrentDir("keyboard.ini",tmpstr,"left",-1);
		right[i]=GetPrivateProfileIntCurrentDir("keyboard.ini",tmpstr,"right",-1);
		fire[i]=GetPrivateProfileIntCurrentDir("keyboard.ini",tmpstr,"fire",-1);
		special[i]=GetPrivateProfileIntCurrentDir("keyboard.ini",tmpstr,"special",-1);
	}
/*
	up[0]=GetPrivateProfileIntCurrentDir("keyboard.ini","p1control","up",-1);
	down[0]=GetPrivateProfileIntCurrentDir("keyboard.ini","p1control","down",-1);
	left[0]=GetPrivateProfileIntCurrentDir("keyboard.ini","p1control","left",-1);
	right[0]=GetPrivateProfileIntCurrentDir("keyboard.ini","p1control","right",-1);
	fire[0]=GetPrivateProfileIntCurrentDir("keyboard.ini","p1control","fire",-1);
	special[0]=GetPrivateProfileIntCurrentDir("keyboard.ini","p1control","special",-1);

	up[1]=GetPrivateProfileIntCurrentDir("keyboard.ini","p2control","up",-1);
	down[1]=GetPrivateProfileIntCurrentDir("keyboard.ini","p2control","down",-1);
	left[1]=GetPrivateProfileIntCurrentDir("keyboard.ini","p2control","left",-1);
	right[1]=GetPrivateProfileIntCurrentDir("keyboard.ini","p2control","right",-1);
	fire[1]=GetPrivateProfileIntCurrentDir("keyboard.ini","p2control","fire",-1);
	special[1]=GetPrivateProfileIntCurrentDir("keyboard.ini","p2control","special",-1);
*/
	m_keyboard.SetCurSel(0);
	COptionPage4::OnSelchangeKeyboard();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionPage4::OnEditchangeKeyboard() 
{
	// TODO: Add your control notification handler code here
}

void COptionPage4::OnSelchangeKeyboard() 
{
	// TODO: Add your control notification handler code here
	char tmpstr[64];
	int i2,i;

	i2=m_keyboard.GetCurSel();

	if(up[i2]==-1)m_up1.SetCurSel(0);
	else
	{
	sprintf(tmpstr,"%d",up[i2]);
	GetPrivateProfileStringCurrentDir("dikmap.ini","int2dik",tmpstr,tmpstr,64);
	i=m_up1.FindStringExact(0,tmpstr);
	m_up1.SetCurSel(i);
	}

	if(down[i2]==-1)m_down1.SetCurSel(0);
	else
	{
		sprintf(tmpstr,"%d",down[i2]);
		GetPrivateProfileStringCurrentDir("dikmap.ini","int2dik",tmpstr,tmpstr,64);
		i=m_down1.FindStringExact(0,tmpstr);
		m_down1.SetCurSel(i);
	}

	if(left[i2]==-1)m_left1.SetCurSel(0);
	else
	{
	sprintf(tmpstr,"%d",left[i2]);
	GetPrivateProfileStringCurrentDir("dikmap.ini","int2dik",tmpstr,tmpstr,64);
	i=m_left1.FindStringExact(0,tmpstr);
	m_left1.SetCurSel(i);
	}

	if(right[i2]==-1)m_right1.SetCurSel(0);
	else
	{
	sprintf(tmpstr,"%d",right[i2]);
	GetPrivateProfileStringCurrentDir("dikmap.ini","int2dik",tmpstr,tmpstr,64);
	i=m_right1.FindStringExact(0,tmpstr);
	m_right1.SetCurSel(i);
	}

	if(fire[i2]==-1)m_fire1.SetCurSel(0);
	else
	{
	sprintf(tmpstr,"%d",fire[i2]);
	GetPrivateProfileStringCurrentDir("dikmap.ini","int2dik",tmpstr,tmpstr,64);
	i=m_fire1.FindStringExact(0,tmpstr);
	m_fire1.SetCurSel(i);
	}

	if(special[i2]==-1)m_special1.SetCurSel(0);
	else
	{
	sprintf(tmpstr,"%d",special[i2]);
	GetPrivateProfileStringCurrentDir("dikmap.ini","int2dik",tmpstr,tmpstr,64);
	i=m_special1.FindStringExact(0,tmpstr);
	m_special1.SetCurSel(i);
	}
}

void COptionPage4::OnSelchangeDown1() 
{
	// TODO: Add your control notification handler code here
	char tmpstr[64];
	int i2;

	i2=m_keyboard.GetCurSel();
	
	m_down1.GetLBText(m_down1.GetCurSel(),tmpstr);	
	down[i2]=GetPrivateProfileIntCurrentDir("dikmap.ini","dik2int",tmpstr,-1);

}

void COptionPage4::OnSelchangeFire1() 
{
	// TODO: Add your control notification handler code here
	char tmpstr[64];
	int i2;

	i2=m_keyboard.GetCurSel();
	
	m_fire1.GetLBText(m_fire1.GetCurSel(),tmpstr);	
	fire[i2]=GetPrivateProfileIntCurrentDir("dikmap.ini","dik2int",tmpstr,-1);

	
}

void COptionPage4::OnSelchangeLeft1() 
{
	// TODO: Add your control notification handler code here
	char tmpstr[64];
	int i2;

	i2=m_keyboard.GetCurSel();
	
	m_left1.GetLBText(m_left1.GetCurSel(),tmpstr);	
	left[i2]=GetPrivateProfileIntCurrentDir("dikmap.ini","dik2int",tmpstr,-1);

	
}

void COptionPage4::OnSelchangeRight1() 
{
	// TODO: Add your control notification handler code here
	char tmpstr[64];
	int i2;

	i2=m_keyboard.GetCurSel();
	
	m_right1.GetLBText(m_right1.GetCurSel(),tmpstr);	
	right[i2]=GetPrivateProfileIntCurrentDir("dikmap.ini","dik2int",tmpstr,-1);

	
}

void COptionPage4::OnSelchangeUp1() 
{
	// TODO: Add your control notification handler code here
	char tmpstr[64];
	int i2;

	i2=m_keyboard.GetCurSel();
	
	m_up1.GetLBText(m_up1.GetCurSel(),tmpstr);	
	up[i2]=GetPrivateProfileIntCurrentDir("dikmap.ini","dik2int",tmpstr,-1);

	
}

void COptionPage4::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	int i;
	char tmpstr[64];

	for(i=0;i<4;++i)
	{
		sprintf(tmpstr,"p%dcontrol",i+1);
	WritePrivateProfileIntCurrentDir("keyboard.ini",tmpstr,"up",up[i]);
	WritePrivateProfileIntCurrentDir("keyboard.ini",tmpstr,"down",down[i]);
	WritePrivateProfileIntCurrentDir("keyboard.ini",tmpstr,"left",left[i]);
	WritePrivateProfileIntCurrentDir("keyboard.ini",tmpstr,"right",right[i]);
	WritePrivateProfileIntCurrentDir("keyboard.ini",tmpstr,"fire",fire[i]);
	WritePrivateProfileIntCurrentDir("keyboard.ini",tmpstr,"special",special[i]);
	}
/*
	WritePrivateProfileIntCurrentDir("keyboard.ini","p1control","up",up[0]);
	WritePrivateProfileIntCurrentDir("keyboard.ini","p1control","down",down[0]);
	WritePrivateProfileIntCurrentDir("keyboard.ini","p1control","left",left[0]);
	WritePrivateProfileIntCurrentDir("keyboard.ini","p1control","right",right[0]);
	WritePrivateProfileIntCurrentDir("keyboard.ini","p1control","fire",fire[0]);
	WritePrivateProfileIntCurrentDir("keyboard.ini","p1control","special",special[0]);

	WritePrivateProfileIntCurrentDir("keyboard.ini","p2control","up",up[1]);
	WritePrivateProfileIntCurrentDir("keyboard.ini","p2control","down",down[1]);
	WritePrivateProfileIntCurrentDir("keyboard.ini","p2control","left",left[1]);
	WritePrivateProfileIntCurrentDir("keyboard.ini","p2control","right",right[1]);
	WritePrivateProfileIntCurrentDir("keyboard.ini","p2control","fire",fire[1]);
	WritePrivateProfileIntCurrentDir("keyboard.ini","p2control","special",special[1]);
*/
	CPropertyPage::OnOK();
}

void COptionPage3::OnCdplay() 
{
	// TODO: Add your control notification handler code here
	BOOL b;

	b=((CButton*)GetDlgItem(IDC_CDPLAY))->GetCheck();
	((CWnd*)GetDlgItem(IDC_CDTRACK))->EnableWindow(b);
	
}

BOOL COptionPage1::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	sndPlaySound("sounds\\beep-01",0);

	return CPropertyPage::OnSetActive();
}

BOOL COptionPage2::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	sndPlaySound("sounds\\beep-01",0);

	return CPropertyPage::OnSetActive();
}

BOOL COptionPage3::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	sndPlaySound("sounds\\beep-01",0);

	return CPropertyPage::OnSetActive();
}

BOOL COptionPage4::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	sndPlaySound("sounds\\beep-01",0);

	return CPropertyPage::OnSetActive();
}

void COptionPage4::OnSelchangeSpecial() 
{
	// TODO: Add your control notification handler code here
	char tmpstr[64];
	int i2;

	i2=m_keyboard.GetCurSel();
	
	m_special1.GetLBText(m_special1.GetCurSel(),tmpstr);	
	special[i2]=GetPrivateProfileIntCurrentDir("dikmap.ini","dik2int",tmpstr,-1);

}
