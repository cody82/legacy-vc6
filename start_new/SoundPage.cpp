// SoundPage.cpp : implementation file
//

#include "stdafx.h"
#include "start_new.h"
#include "SoundPage.h"
#include <profiles.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoundPage property page

IMPLEMENT_DYNCREATE(CSoundPage, CPropertyPage)

CSoundPage::CSoundPage() : CPropertyPage(CSoundPage::IDD)
{
	m_psp.dwFlags &=~PSP_HASHELP;
	//{{AFX_DATA_INIT(CSoundPage)
	//}}AFX_DATA_INIT
}

CSoundPage::~CSoundPage()
{
}

void CSoundPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoundPage)
	DDX_Control(pDX, IDC_MASTER, m_master);
	DDX_Control(pDX, IDC_SPEECH, m_speech);
	DDX_Control(pDX, IDC_SFX, m_sfx);
	DDX_Control(pDX, IDC_MUSIC, m_music);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSoundPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSoundPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundPage message handlers

void CSoundPage::OnOK() 
{
	// TODO: Add extra validation here
	int i;
	UpdateData(TRUE);

	i=m_music.GetPos();
	WritePrivateProfileIntCurrentDir("sounds.ini","typevolume","music",i);

	i=m_sfx.GetPos();
	WritePrivateProfileIntCurrentDir("sounds.ini","typevolume","fx",i);

	i=m_speech.GetPos();
	WritePrivateProfileIntCurrentDir("sounds.ini","typevolume","speech",i);

	i=m_master.GetPos();
	WritePrivateProfileIntCurrentDir("sounds.ini","mastervolume","volume",i);

	CPropertyPage::OnOK();
}

BOOL CSoundPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i;

	m_music.SetRange(0,100,TRUE);
	m_sfx.SetRange(0,100,TRUE);
	m_speech.SetRange(0,100,TRUE);
	m_master.SetRange(0,100,TRUE);

	i=GetPrivateProfileIntCurrentDir("sounds.ini","typevolume","fx",100);
	m_sfx.SetPos(i);
	i=GetPrivateProfileIntCurrentDir("sounds.ini","typevolume","music",100);
	m_music.SetPos(i);
	i=GetPrivateProfileIntCurrentDir("sounds.ini","typevolume","speech",100);
	m_speech.SetPos(i);
	i=GetPrivateProfileIntCurrentDir("sounds.ini","mastervolume","volume",100);
	m_master.SetPos(i);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
