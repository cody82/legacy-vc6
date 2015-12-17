// ShipSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "start_new.h"
#include "ShipSelectDlg.h"
#include <profiles.h>
#include "optionssheet.h"
#include "optionpages.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int selectedspritefile[4];

/////////////////////////////////////////////////////////////////////////////
// CShipSelectDlg dialog


CShipSelectDlg::CShipSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShipSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShipSelectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShipSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShipSelectDlg)
	DDX_Control(pDX, IDC_SHIPS, m_shiplist);
	DDX_Control(pDX, IDC_PLAYERS, m_playerlist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShipSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CShipSelectDlg)
	ON_LBN_SELCHANGE(IDC_PLAYERS, OnSelchangePlayers)
	ON_LBN_SELCHANGE(IDC_SHIPS, OnSelchangeShips)
	ON_BN_CLICKED(IDC_OPTIONS, OnOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShipSelectDlg message handlers

BOOL CShipSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i,i2;
	char tmpstr[64];
	char tmpstr2[64],tmpstr3[64];

	((CAnimateCtrl*)GetDlgItem(IDC_ANIMATE1))->Open("videos\\select.avi");
	m_playerlist.ResetContent();
	m_shiplist.ResetContent();

	i=GetPrivateProfileIntCurrentDir("config.ini","game1","players",2);
	for(i2=1;i2<=i;++i2)
	{
		sprintf(tmpstr,"%d",i2);
		
		strcpy(tmpstr2,"player");
		strcat(tmpstr2,tmpstr);
		strcat(tmpstr2,"name");

		GetPrivateProfileStringCurrentDir("config.ini","game1",tmpstr2,tmpstr3,64);
		strcpy(tmpstr2," (");
		strcat(tmpstr2,tmpstr3);
		strcat(tmpstr2,")");
		strcat(tmpstr,tmpstr2);

		m_playerlist.AddString(tmpstr);

	}


	i2=GetPrivateProfileIntCurrentDir("config.ini","shipselect","numships",0);
	for(i=0;i<i2;++i)
	{
		strcpy(tmpstr,"ship");
		sprintf(tmpstr2,"%d",i);
		strcat(tmpstr,tmpstr2);
		strcat(tmpstr,"name");
		GetPrivateProfileStringCurrentDir("config.ini","shipselect",tmpstr,tmpstr2,64);
		m_shiplist.AddString(tmpstr2);
	}


	selectedspritefile[0]=GetPrivateProfileIntCurrentDir("config.ini","game1","player1ship",0);
	selectedspritefile[1]=GetPrivateProfileIntCurrentDir("config.ini","game1","player2ship",0);
	selectedspritefile[2]=GetPrivateProfileIntCurrentDir("config.ini","game1","player3ship",0);
	selectedspritefile[3]=GetPrivateProfileIntCurrentDir("config.ini","game1","player4ship",0);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShipSelectDlg::OnSelchangePlayers() 
{
	// TODO: Add your control notification handler code here
	char tmpstr3[64],tmpstr2[64],tmpstr[64];
	int i,i2,i3;
	
	m_playerlist.GetText(m_playerlist.GetCurSel(),tmpstr3);
	sndPlaySound("sounds\\beep-01",0);

	i2=tmpstr3[0]-48;

	for(i=0;i<GetPrivateProfileIntCurrentDir("config.ini","shipselect","numships",0);++i)
	{
		strcpy(tmpstr,"ship");
		sprintf(tmpstr2,"%d",i);
		strcat(tmpstr,tmpstr2);
		strcat(tmpstr,"file");
		i3=GetPrivateProfileIntCurrentDir("config.ini","shipselect",tmpstr,0);
		if(i3==selectedspritefile[i2-1])
		{
			m_shiplist.SetCurSel(i);
			CShipSelectDlg::OnSelchangeShips();
			break;
		}
	}
}

void CShipSelectDlg::OnSelchangeShips()
{
	// TODO: Add your control notification handler code here
	int i,i2;
	char tmpstr[64],tmpstr2[64],tmpstr3[64];
	sndPlaySound("sounds\\beep-01",0);
	
	if(m_playerlist.GetCurSel()==CB_ERR)
	{
		m_playerlist.SetCurSel(0);
	}
	
	i2=GetPrivateProfileIntCurrentDir("config.ini","shipselect","numships",0);
	
	m_shiplist.GetText(m_shiplist.GetCurSel(),tmpstr3);
	for(i=0;i<i2;++i)
	{
		strcpy(tmpstr,"ship");
		sprintf(tmpstr2,"%d",i);
		strcat(tmpstr,tmpstr2);
		strcat(tmpstr,"name");
		GetPrivateProfileStringCurrentDir("config.ini","shipselect",tmpstr,tmpstr2,64);
		if(strcmp(tmpstr2,tmpstr3)==0)
		{
			strcpy(tmpstr,"ship");
			sprintf(tmpstr2,"%d",i);
			strcat(tmpstr,tmpstr2);
			strcat(tmpstr,"avi");
			GetPrivateProfileStringCurrentDir("config.ini","shipselect",tmpstr,tmpstr2,64);
			((CAnimateCtrl*)GetDlgItem(IDC_ANIMATE1))->Open(tmpstr2);

			strcpy(tmpstr,"ship");
			sprintf(tmpstr2,"%d",i);
			strcat(tmpstr,tmpstr2);
			strcat(tmpstr,"file");
			i=GetPrivateProfileIntCurrentDir("config.ini","shipselect",tmpstr,0);
	
			m_playerlist.GetText(m_playerlist.GetCurSel(),tmpstr3);
			i2=tmpstr3[0]-48;
			selectedspritefile[i2-1]=i;
			break;
		}
	}
}

void CShipSelectDlg::OnOK() 
{
	// TODO: Add extra validation here
//	int i,i2;
//	i=GetPrivateProfileIntCurrentDir("config.ini","game1","players",2);

	WritePrivateProfileIntCurrentDir("config.ini","game1","player1ship",selectedspritefile[0]);
	WritePrivateProfileIntCurrentDir("config.ini","game1","player2ship",selectedspritefile[1]);
	WritePrivateProfileIntCurrentDir("config.ini","game1","player3ship",selectedspritefile[2]);
	WritePrivateProfileIntCurrentDir("config.ini","game1","player4ship",selectedspritefile[3]);

	CDialog::OnOK();
}


void CShipSelectDlg::OnOptions() 
{
	// TODO: Add your control notification handler code here
	COptionsSheet os(IDS_OPTIONS);

	if(os.DoModal()==IDOK)
	{
		CShipSelectDlg::OnInitDialog();
	}
	sndPlaySound("sounds\\beep-01",0);

}
