// PlayersDialog.cpp : implementation file
//

#include "stdafx.h"
#include "start_new.h"
#include "PlayersDialog.h"
#include <profiles.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayersDialog dialog


CPlayersDialog::CPlayersDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayersDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayersDialog)
	//}}AFX_DATA_INIT
}


void CPlayersDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayersDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayersDialog, CDialog)
	//{{AFX_MSG_MAP(CPlayersDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayersDialog message handlers

BOOL CPlayersDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char tmpstr[64];
	int i;

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

//	((CComboBox*)GetDlgItem(IDC_CONTROL1))->SetDroppedWidth(10);
//	if(i==CB_ERR)exit(0);

//	UpdateData(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlayersDialog::OnOK() 
{
	// TODO: Add extra validation here
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

	CDialog::OnOK();
}
