// PlayersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DPTest.h"
#include "PlayersDlg.h"
#include "dp4engine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPlayersDlg *dlg;
/////////////////////////////////////////////////////////////////////////////
// CPlayersDlg dialog


CPlayersDlg::CPlayersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayersDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayersDlg)
	m_chat = _T("");
	//}}AFX_DATA_INIT
}


void CPlayersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayersDlg)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Text(pDX, IDC_CHAT, m_chat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayersDlg, CDialog)
	//{{AFX_MSG_MAP(CPlayersDlg)
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayersDlg message handlers

void CPlayersDlg::OnCreate() 
{
	// TODO: Add your control notification handler code here
	CDP4Engine::CreatePlayer("testplayer");
}

void CPlayersDlg::OnUpdate() 
{
	// TODO: Add your control notification handler code here
	CDP4Engine::EnumPlayers();
	m_list1.ResetContent();
	
	for(UINT i=0;i<CDP4Engine::GetNumPlayers();++i)
	{
		m_list1.AddString(CDP4Engine::GetPlayers()[i].name);
	}
}

void CPlayersDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDP4Engine::SendChatMessage(&CDP4Engine::GetPlayers()[m_list1.GetCurSel()],m_chat.GetBuffer(5));
	m_chat.ReleaseBuffer();
}

VOID ChatProc(LPSTR lpszText,DPID idFrom, DPID idToPlayer,DPID idToGroup)
{
	dlg->MessageBox(lpszText);
}

BOOL CPlayersDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetTimer(1,1000,NULL);
	CDP4Engine::SetChatProc(ChatProc);
	dlg=this;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlayersDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CDP4Engine::ReceiveMessages();
	CDialog::OnTimer(nIDEvent);
}
