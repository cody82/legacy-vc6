// SessionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DPTest.h"
#include "SessionDlg.h"
#include "dp4engine.h"
#include "playersdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSessionDlg dialog


CSessionDlg::CSessionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSessionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSessionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSessionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSessionDlg)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSessionDlg, CDialog)
	//{{AFX_MSG_MAP(CSessionDlg)
	ON_BN_CLICKED(IDC_JOIN, OnJoin)
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSessionDlg message handlers

void CSessionDlg::OnJoin() 
{
	// TODO: Add your control notification handler code here
	CDP4Engine::JoinSession(m_list1.GetCurSel());
	CPlayersDlg dlg;
	dlg.DoModal();
}

void CSessionDlg::OnCreate() 
{
	// TODO: Add your control notification handler code here
	CDP4Engine::CreateSession("test",10);
	CPlayersDlg dlg;
	dlg.DoModal();
}

BOOL CSessionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	OnUpdate();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSessionDlg::OnUpdate() 
{
	// TODO: Add your control notification handler code here
	CDP4Engine::EnumSessions();

	m_list1.ResetContent();
	for(UINT i=0;i<CDP4Engine::GetNumSessions();++i)
	{
		m_list1.AddString(CDP4Engine::GetSessions()[i].lpszSessionNameA);
	}

}
