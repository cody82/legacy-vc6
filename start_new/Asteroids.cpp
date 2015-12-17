// Asteroids.cpp : implementation file
//

#include "stdafx.h"
#include "start_new.h"
#include "Asteroids.h"
#include <profiles.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAsteroids property page

IMPLEMENT_DYNCREATE(CAsteroids, CPropertyPage)

CAsteroids::CAsteroids() : CPropertyPage(CAsteroids::IDD)
{
	m_psp.dwFlags &=~PSP_HASHELP;
	//{{AFX_DATA_INIT(CAsteroids)
	m_asteroids = FALSE;
	m_count = 0;
	m_distance = 0;
	m_interval = 0;
	m_radius = 0;
	m_speed = 0;
	//}}AFX_DATA_INIT
}

CAsteroids::~CAsteroids()
{
}

void CAsteroids::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAsteroids)
	DDX_Check(pDX, IDC_ASTEROIDS, m_asteroids);
	DDX_Text(pDX, IDC_COUNT, m_count);
	DDX_Text(pDX, IDC_DISTANCE, m_distance);
	DDX_Text(pDX, IDC_INTERVAL, m_interval);
	DDX_Text(pDX, IDC_RADIUS, m_radius);
	DDX_Text(pDX, IDC_SPEED, m_speed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAsteroids, CPropertyPage)
	//{{AFX_MSG_MAP(CAsteroids)
	ON_BN_CLICKED(IDC_ASTEROIDS, OnAsteroids)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAsteroids message handlers

void CAsteroids::OnAsteroids() 
{
	UpdateData();

	GetDlgItem(IDC_INTERVAL)->EnableWindow(m_asteroids);
	GetDlgItem(IDC_SPEED)->EnableWindow(m_asteroids);
	GetDlgItem(IDC_COUNT)->EnableWindow(m_asteroids);
	GetDlgItem(IDC_RADIUS)->EnableWindow(m_asteroids);
	GetDlgItem(IDC_DISTANCE)->EnableWindow(m_asteroids);

	// TODO: Add your control notification handler code here
	
}

BOOL CAsteroids::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i;
	
	i=GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidinterval",-1);
	if(i>0)
	{
		m_asteroids=TRUE;
		m_interval=i;
	}
	else
	{
		m_asteroids=FALSE;
		m_interval=60000;
	}

	m_count=GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidcount",0);

	m_distance=GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidspawndistance",0);

	m_radius=GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidspawnradius",0);

	m_speed=GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidspeed",0);

	UpdateData(FALSE);
	
	OnAsteroids();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAsteroids::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData();

	if(m_asteroids)	
		WritePrivateProfileIntCurrentDir("config.ini","game1","asteroidinterval",m_interval);
	else
		WritePrivateProfileIntCurrentDir("config.ini","game1","asteroidinterval",-1);
	
	WritePrivateProfileIntCurrentDir("config.ini","game1","asteroidcount",m_count);

	WritePrivateProfileIntCurrentDir("config.ini","game1","asteroidspawndistance",m_distance);

	WritePrivateProfileIntCurrentDir("config.ini","game1","asteroidspawnradius",m_radius);

	WritePrivateProfileIntCurrentDir("config.ini","game1","asteroidspeed",m_speed);

	CPropertyPage::OnOK();
}
