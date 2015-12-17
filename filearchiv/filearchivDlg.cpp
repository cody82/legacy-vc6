// filearchivDlg.cpp : implementation file
//

#include "stdafx.h"
#include "filearchiv.h"
#include "filearchivDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilearchivDlg dialog

CFilearchivDlg::CFilearchivDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFilearchivDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilearchivDlg)
	m_edit1 = _T("");
	m_count = 0;
	m_edit2 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFilearchivDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilearchivDlg)
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_COUNT, m_count);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFilearchivDlg, CDialog)
	//{{AFX_MSG_MAP(CFilearchivDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SCAN, OnScan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilearchivDlg message handlers

BOOL CFilearchivDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFilearchivDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFilearchivDlg::OnPaint() 
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
HCURSOR CFilearchivDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFilearchivDlg::AddFiles(CString path,CFile *f)
{
	CFileFind ff;
	CString cstr;
//	CFile f;
	BOOL b;
	BOOL bdir;

	if(!ff.FindFile(path,0))return;
	
	while(TRUE)
	{
		b=ff.FindNextFile();
		if(!ff.IsDots())
		{
			if(bdir=ff.IsDirectory())
			{
				cstr=ff.GetFilePath();
				f->Write(cstr,cstr.GetLength()+1);
				f->Write(&bdir,sizeof(BOOL));
				m_list1.AddString(cstr);
				cstr+="\\*.*";
				AddFiles(cstr,f);

			}
			else
			{
				cstr=ff.GetFilePath();
				f->Write(cstr,cstr.GetLength()+1);
				f->Write(&bdir,sizeof(BOOL));
				m_list1.AddString(cstr);
			}
		}
		if(!b)break;
	};
}


BOOL CFilearchivDlg::load(CFile *f,LOADSTRUCT *ls)
{
	int i=0;
	
	for(i=0;;++i)
	{
		if(!f->Read(&ls->path[i],1))return FALSE;
		if(ls->path[i]=='\0')break;
	};
		
	if(!f->Read(&ls->dir,sizeof(BOOL)))return FALSE;


	return TRUE;
}

void CFilearchivDlg::OnScan() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFile f;
	
	if(!f.Open(m_edit2,CFile::modeCreate | CFile::modeWrite))return;
	
	m_list1.ResetContent;
	AddFiles(m_edit1,&f);
	
	m_count=m_list1.GetCount();

	f.Flush();
	f.Close();
	
	UpdateData(FALSE);
}

void TruncLastPath(CString path)
{
	int i=-1;
	int i2;
	
	while((i=path.Find('\\',i+1))!=-1)
	{
		i2=i;
	}
	path.Delete(i2,path.GetLength()-i2);
	return;
}


void CFilearchivDlg::OnLoad() 
{
	// TODO: Add your control notification handler code here
/*	CFile f;
	CString cstr;
	LOADSTRUCT ls;
	TV_INSERTSTRUCT insert;
	HTREEITEM item1;
	insert.hParent=TVI_ROOT;
	insert.hInsertAfter=TVI_LAST;
	insert.item.mask=TVIF_TEXT;

	if(!f.Open("struct.txt",CFile::modeReadWrite|CFile::shareExclusive))return;

	//=m_tree1.InsertItem(&insert);


	f.Close();
	
	if(!GetProfileSectionNamesCurDir(filename,sections,32768))return;

	insert.hParent=item1;
	strptr=sections;
	while(1)
	{
		if(*strptr==0)break;
		strcpy(tmpstr,strptr);
		i2=strlen(strptr)+1;
		for(i=0;i<i2;++i)++strptr;
		insert.item.pszText=tmpstr;
		m_tree1.InsertItem(&insert);
	}

	HTREEITEM item2=m_tree1.GetChildItem(item1);
	strcpy(tmpstr,m_tree1.GetItemText(item2).GetBuffer(64));
	strcpy(tmpstr2,m_tree1.GetItemText(item1).GetBuffer(64));
	if(!GetProfileSectionCurDir(tmpstr2,tmpstr,keys,32767))return;
	
	insert.hParent=item2;
	strptr=keys;
	while(1)
	{
		if(*strptr==0)break;
		strcpy(tmpstr,strptr);
		i2=strlen(strptr)+1;
		for(i=0;i<i2;++i)++strptr;
		insert.item.pszText=tmpstr;
		m_tree1.InsertItem(&insert);
	}

	while(item2=m_tree1.GetNextSiblingItem(item2))
	{
	strcpy(tmpstr,m_tree1.GetItemText(item2).GetBuffer(64));
	strcpy(tmpstr2,m_tree1.GetItemText(item1).GetBuffer(64));
	if(!GetProfileSectionCurDir(tmpstr2,tmpstr,keys,32767))return;
	
	insert.hParent=item2;
	strptr=keys;
	while(1)
	{
		if(*strptr==0)break;
		strcpy(tmpstr,strptr);
		i2=strlen(strptr)+1;
		for(i=0;i<i2;++i)++strptr;
		insert.item.pszText=tmpstr;
		m_tree1.InsertItem(&insert);
	}
	}*/








}
