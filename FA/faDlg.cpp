// faDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fa.h"
#include "faDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFaDlg dialog

CFaDlg::CFaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFaDlg)
	m_addname = _T("");
	m_openname = _T("");
	m_key = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFaDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Text(pDX, IDC_ADDNAME, m_addname);
	DDX_Text(pDX, IDC_OPENNAME, m_openname);
	DDX_Text(pDX, IDC_KEY, m_key);
	DDV_MinMaxByte(pDX, m_key, 0, 255);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFaDlg, CDialog)
	//{{AFX_MSG_MAP(CFaDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_EXTRACT, OnExtract)
	ON_EN_CHANGE(IDC_KEY, OnChangeKey)
	ON_BN_CLICKED(IDC_ADDDIR, OnAdddir)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaDlg message handlers

BOOL CFaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFaDlg::OnPaint() 
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
HCURSOR CFaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFaDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here

	UpdateData();

	if(!m_fa.Open(m_openname.GetBuffer(64)))
		m_fa.Create(m_openname.GetBuffer(64));

	UpdateList();
}

void CFaDlg::OnClose() 
{
	// TODO: Add your control notification handler code here
	m_fa.Close();
	m_addname="";
	m_openname="";

	m_list.ResetContent();
	UpdateData(FALSE);
}

void CFaDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_fa.AddFile(m_addname.GetBuffer(64));
	UpdateList();
}

void CFaDlg::OnExtract() 
{
	// TODO: Add your control notification handler code here
	if(m_list.GetCurSel()==CB_ERR)return;

	char tmpstr[64];
	m_list.GetText(m_list.GetCurSel(),tmpstr);
	m_fa.ExtractFile(tmpstr);
}

VOID CFaDlg::UpdateList()
{
	DWORD dw;

	m_list.ResetContent();

	for(dw=0;dw<m_fa.Header.FileCount;++dw)
	{
		m_list.AddString(m_fa.Files[dw].Name);
	}
}

void CFaDlg::OnChangeKey() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	m_fa.SetKey(m_key);
}

void CFaDlg::OnAdddir() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_fa.AddDir(m_addname.GetBuffer(64),FALSE);
	UpdateList();
}

void CFaDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	int i;
	char tmpstr[64];
	if((i=m_list.GetCurSel())==LB_ERR)return;

	m_list.GetText(i,tmpstr);
	m_fa.DeleteFile(tmpstr);

	UpdateList();
}
