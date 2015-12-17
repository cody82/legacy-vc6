// inieditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "iniedit.h"
#include "inieditDlg.h"
#include <int2str.h>
#include <profiles.h>

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
// CInieditDlg dialog

CInieditDlg::CInieditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInieditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInieditDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInieditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInieditDlg)
	DDX_Control(pDX, IDC_TREE1, m_tree1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInieditDlg, CDialog)
	//{{AFX_MSG_MAP(CInieditDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, OnEndlabeleditTree1)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_NOTIFY(TVN_KEYDOWN, IDC_TREE1, OnKeydownTree1)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, OnRclickTree1)
	ON_BN_CLICKED(IDC_RELOAD, OnReload)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_SORT, OnSort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInieditDlg message handlers

BOOL CInieditDlg::OnInitDialog()
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
	OnLoad();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInieditDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CInieditDlg::OnPaint() 
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
HCURSOR CInieditDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInieditDlg::LoadINIFile(char *filename)
{
	char sections[32768];
	char keys[32768];
	char tmpstr[64],tmpstr2[64];
	int i,i2;
	char *strptr;
	TV_INSERTSTRUCT insert;

	if(!FileExistCurDir(filename))return;

	insert.hParent=TVI_ROOT;
	insert.hInsertAfter=TVI_LAST;
	insert.item.mask=TVIF_TEXT;
	insert.item.pszText=filename;

	HTREEITEM item1=m_tree1.InsertItem(&insert);

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
	}
}

void SplitKey(char *line,char *key,char *value)
{
	int i;
	int i2;

	for(i=0;;++i)
	{
		if(line[i]=='=')break;
		key[i]=line[i];
	}
	key[i]='\0';
	++i;
	
	for(i2=i;;++i)
	{
		if(line[i]=='\0')break;
		value[i-i2]=line[i];
	}
	value[i-i2]='\0';
}

void CInieditDlg::SaveINIFile(HTREEITEM hti)
{
	char filename[64];
	char tmpstr[64],tmpstr2[64];
	char section[64];
	char key[64];
	DWORD dw;
	HANDLE h;
	HTREEITEM sectionitem,keyitem;

	strcpy(filename,m_tree1.GetItemText(hti).GetBuffer(64));
	dw=GetFileAttributes(filename);
	if(dw&FILE_ATTRIBUTE_READONLY)
		SetFileAttributes(filename,FILE_ATTRIBUTE_NORMAL);

	h=CreateFile(filename,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	CloseHandle(h);

	sectionitem=m_tree1.GetChildItem(hti);
	do
	{

		keyitem=m_tree1.GetChildItem(sectionitem);
		do
		{
			strcpy(section,m_tree1.GetItemText(sectionitem).GetBuffer(64));
			strcpy(key,m_tree1.GetItemText(keyitem).GetBuffer(64));
			SplitKey(key,tmpstr,tmpstr2);
			WritePrivateProfileStringCurrentDir(filename,section,tmpstr,tmpstr2);
		}while(keyitem=m_tree1.GetNextSiblingItem(keyitem));

	}while(sectionitem=m_tree1.GetNextSiblingItem(sectionitem));

}


void CInieditDlg::OnLoad() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	HANDLE h;
	char tmpstr[64];
	WIN32_FIND_DATA finddata;

	if(!(h=FindFirstFile("*.ini",&finddata)))return;
	
	strcpy(tmpstr,finddata.cFileName);

	m_tree1.DeleteAllItems();

	LoadINIFile(tmpstr);

	while(FindNextFile(h,&finddata))
	{
	strcpy(tmpstr,finddata.cFileName);

	LoadINIFile(tmpstr);
	}
	
	FindClose(h);
}


void CInieditDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CInieditDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CInieditDlg::OnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	char tmpstr[64];
	HTREEITEM hi;

	if(pTVDispInfo->item.pszText)
		strcpy(tmpstr,pTVDispInfo->item.pszText);
	else return;
	hi=pTVDispInfo->item.hItem;

	m_tree1.SetItemText(hi,tmpstr);

	*pResult = 0;
}

void CInieditDlg::OnSave() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM root;
	char tmpstr[64];

	root=m_tree1.GetRootItem();
	if(!root)return;
	do
	{
		strcpy(tmpstr,m_tree1.GetItemText(root).GetBuffer(64));
		SaveINIFile(root);
		root=m_tree1.GetNextSiblingItem(root);
	}while(root);
	
}


void CInieditDlg::OnNew() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hti;
	TVINSERTSTRUCT insert;

	hti=m_tree1.GetSelectedItem();
	if(!hti)
	{
		MessageBox("No item selected");
	}
	
	insert.hParent=hti;
	insert.hInsertAfter=TVI_LAST;
	insert.item.mask=TVIF_TEXT;
	insert.item.pszText="NEW ITEM";
		
	hti=m_tree1.InsertItem(&insert);

}



void CInieditDlg::OnKeydownTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	int vkc;
	vkc=pTVKeyDown->wVKey;

	switch(vkc)
	{
	case VK_DELETE:
		OnDelete();
		break;
	case VK_INSERT:
		OnNew();
		break;
	}

	*pResult = 0;
}

void CInieditDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hti;
		
	hti=m_tree1.GetSelectedItem();
	if(!hti)
	{
		MessageBox("No item selected");
	}

	m_tree1.DeleteItem(hti);
}

void CInieditDlg::OnEdit() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hti;
		
	hti=m_tree1.GetSelectedItem();
	if(!hti)
	{
		MessageBox("No item selected");
	}

	m_tree1.EditLabel(hti);

}

void CInieditDlg::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CInieditDlg::OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hti;
		
	hti=m_tree1.GetSelectedItem();
	m_tree1.EditLabel(hti);
	*pResult = 0;
}

void CInieditDlg::OnReload() 
{
	// TODO: Add your control notification handler code here
	OnLoad();
	
}

void CInieditDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	PostQuitMessage(0);
}

void CInieditDlg::OnSort() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM root,item1,item2;

	root=m_tree1.GetSelectedItem();
	if(!root)return;
	
	m_tree1.SortChildren(root);

	item1=m_tree1.GetChildItem(root);
	if(!item1)return;
	do
	{
		m_tree1.SortChildren(item1);
		item2=m_tree1.GetChildItem(item1);
		if(!item2)break;
		do
		{
			m_tree1.SortChildren(item2);
			
		}while(item2=m_tree1.GetNextSiblingItem(item2));

	}while(item1=m_tree1.GetNextSiblingItem(item1));
	
}
