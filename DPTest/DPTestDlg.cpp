// DPTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DPTest.h"
#include "DPTestDlg.h"
#include "dp4engine.h"
#include "sessiondlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDPTestDlg dialog

CDPTestDlg::CDPTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDPTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDPTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDPTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDPTestDlg)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDPTestDlg, CDialog)
	//{{AFX_MSG_MAP(CDPTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDPTestDlg message handlers

BOOL CDPTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CDP4Engine::Initialize();
	CDP4Engine::EnumConnections();

	for(UINT i=0;i<CDP4Engine::GetNumConnections();++i)
	{
		m_list1.AddString(CDP4Engine::GetConnections()[i].pShortName);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDPTestDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDPTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDPTestDlg::OnSelect() 
{
	CSessionDlg dlg;
	// TODO: Add your control notification handler code here
	CDP4Engine::InitializeConnection(m_list1.GetCurSel());

	dlg.DoModal();
}
