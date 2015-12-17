// keyboardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "keyboard.h"
#include "keyboardDlg.h"
#include <mmreg.h>
#include <dsound.h>
#include <dsutil3d.h>
#include <dinput.h>
#include <diclass.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//LPDIRECTSOUND lpDirectSound;
//LPDIRECTSOUNDBUFFER lpDirectSoundBuffer1;

//LPDIRECTSOUNDBUFFER lpDSB[26];

void CKeyboardDlg::DSPlay(int i,CString file)
{
	ds.PlayFile(file,FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg dialog

CKeyboardDlg::CKeyboardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyboardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyboardDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyboardDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKeyboardDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyboardDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_A, OnA)
	ON_BN_CLICKED(IDC_B, OnB)
	ON_BN_CLICKED(IDC_C, OnC)
	ON_BN_CLICKED(IDC_D, OnD)
	ON_BN_CLICKED(IDC_E, OnE)
	ON_BN_CLICKED(IDC_F, OnF)
	ON_BN_CLICKED(IDC_G, OnG)
	ON_BN_CLICKED(IDC_H, OnH)
	ON_BN_CLICKED(IDC_I, OnI)
	ON_BN_CLICKED(IDC_J, OnJ)
	ON_BN_CLICKED(IDC_K, OnK)
	ON_BN_CLICKED(IDC_L, OnL)
	ON_BN_CLICKED(IDC_M, OnM)
	ON_BN_CLICKED(IDC_N, OnN)
	ON_BN_CLICKED(IDC_O, OnO)
	ON_BN_CLICKED(IDC_P, OnP)
	ON_BN_CLICKED(IDC_Q, OnQ)
	ON_BN_CLICKED(IDC_R, OnR)
	ON_BN_CLICKED(IDC_S, OnS)
	ON_BN_CLICKED(IDC_T, OnT)
	ON_BN_CLICKED(IDC_U, OnU)
	ON_BN_CLICKED(IDC_V, OnV)
	ON_BN_CLICKED(IDC_W, OnW)
	ON_BN_CLICKED(IDC_X, OnX)
	ON_BN_CLICKED(IDC_Y, OnY)
	ON_BN_CLICKED(IDC_Z, OnZ)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg message handlers

BOOL CKeyboardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	ds.Initialize(m_hWnd);
	SetTimer(1,1000,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeyboardDlg::OnPaint() 
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
HCURSOR CKeyboardDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKeyboardDlg::OnA() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT1,tmpstr);
	DSPlay(1,tmpstr);
}

void CKeyboardDlg::OnB() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT2,tmpstr);
	DSPlay(2,tmpstr);
	
}

void CKeyboardDlg::OnC() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT3,tmpstr);
	DSPlay(3,tmpstr);

}

void CKeyboardDlg::OnD() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT4,tmpstr);
	DSPlay(4,tmpstr);
	
}

void CKeyboardDlg::OnE() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT5,tmpstr);
	DSPlay(5,tmpstr);
	
}

void CKeyboardDlg::OnF() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT6,tmpstr);
	DSPlay(6,tmpstr);
	
}

void CKeyboardDlg::OnG() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT7,tmpstr);
	DSPlay(7,tmpstr);
	
}

void CKeyboardDlg::OnH() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT8,tmpstr);
	DSPlay(8,tmpstr);
	
}

void CKeyboardDlg::OnI() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT9,tmpstr);
	DSPlay(9,tmpstr);
	
}

void CKeyboardDlg::OnJ() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT10,tmpstr);
	DSPlay(10,tmpstr);
	
}

void CKeyboardDlg::OnK() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT11,tmpstr);
	DSPlay(11,tmpstr);
	
}

void CKeyboardDlg::OnL() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT12,tmpstr);
	DSPlay(12,tmpstr);
	
}

void CKeyboardDlg::OnM() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT13,tmpstr);
	DSPlay(13,tmpstr);
	
}

void CKeyboardDlg::OnN() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT14,tmpstr);
	DSPlay(14,tmpstr);
	
}

void CKeyboardDlg::OnO() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT15,tmpstr);
	DSPlay(15,tmpstr);
	
}

void CKeyboardDlg::OnP() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT16,tmpstr);
	DSPlay(16,tmpstr);
	
}

void CKeyboardDlg::OnQ() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT17,tmpstr);
	DSPlay(17,tmpstr);
	
}

void CKeyboardDlg::OnR() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT18,tmpstr);
	DSPlay(18,tmpstr);
	
}

void CKeyboardDlg::OnS() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT19,tmpstr);
	DSPlay(19,tmpstr);
	
}

void CKeyboardDlg::OnT() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT20,tmpstr);
	DSPlay(20,tmpstr);
	
}

void CKeyboardDlg::OnU() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT21,tmpstr);
	DSPlay(21,tmpstr);
	
}

void CKeyboardDlg::OnV() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT22,tmpstr);
	DSPlay(22,tmpstr);
	
}

void CKeyboardDlg::OnW() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT23,tmpstr);
	DSPlay(23,tmpstr);
	
}

void CKeyboardDlg::OnX() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT24,tmpstr);
	DSPlay(24,tmpstr);
	
}

void CKeyboardDlg::OnY() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT25,tmpstr);
	DSPlay(25,tmpstr);
	
}

void CKeyboardDlg::OnZ() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	GetDlgItemText(IDC_EDIT26,tmpstr);
	DSPlay(26,tmpstr);
	
}

void CKeyboardDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/*	SHORT ret;
	ret=GetAsyncKeyState('A');
	if((ret&32768) &&(ret&1))
	{
		OnA();
	}
BOOL b;
	b=((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(!b);*/
	ds.ReleaseUnusedBuffers();
	CDialog::OnTimer(nIDEvent);
}
