#if !defined(AFX_OPTIONPAGES_H__CC140D78_20D7_11D3_B881_00000100B481__INCLUDED_)
#define AFX_OPTIONPAGES_H__CC140D78_20D7_11D3_B881_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionPages.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionPage1 dialog

class COptionPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionPage1)

// Construction
public:
	COptionPage1();
	~COptionPage1();

// Dialog Data
	//{{AFX_DATA(COptionPage1)
	enum { IDD = IDD_OPTIONS1 };
	CString	m_name1;
	CString	m_name2;
	CString	m_name3;
	CString	m_name4;
	BOOL	m_borg;
	int		m_borgtime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionPage1)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionPage1)
	virtual BOOL OnInitDialog();
	afx_msg void OnBorg();
	afx_msg void OnEditchangePlayers();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// COptionPage2 dialog

class COptionPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionPage2)

// Construction
public:
	COptionPage2();
	~COptionPage2();

// Dialog Data
	//{{AFX_DATA(COptionPage2)
	enum { IDD = IDD_OPTIONS2 };
	BOOL	m_triplebuffering;
	BOOL	m_windowmode;
	UINT	m_resx;
	UINT	m_resy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionPage2)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionPage2)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
#endif
/////////////////////////////////////////////////////////////////////////////
// COptionPage3 dialog

class COptionPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionPage3)

// Construction
public:
	COptionPage3();
	~COptionPage3();

// Dialog Data
	//{{AFX_DATA(COptionPage3)
	enum { IDD = IDD_OPTIONS3 };
	CString	m_deathsound;
	BOOL	m_showinfo;
	CString	m_loadpicture;
	CString	m_backgroundsound;
	CString	m_backgroundimage;
	UINT	m_cdtrack;
	BOOL	m_cdplay;
	int		m_gamespeed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionPage3)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionPage3)
	virtual BOOL OnInitDialog();
	afx_msg void OnCdplay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// COptionPage4 dialog

class COptionPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionPage4)

// Construction
public:
	COptionPage4();
	~COptionPage4();

// Dialog Data
	//{{AFX_DATA(COptionPage4)
	enum { IDD = IDD_OPTIONS4 };
	CComboBox	m_special1;
	CComboBox	m_keyboard;
	CComboBox	m_up1;
	CComboBox	m_right1;
	CComboBox	m_left1;
	CComboBox	m_fire1;
	CComboBox	m_down1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionPage4)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionPage4)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeKeyboard();
	afx_msg void OnSelchangeKeyboard();
	afx_msg void OnSelchangeDown1();
	afx_msg void OnSelchangeFire1();
	afx_msg void OnSelchangeLeft1();
	afx_msg void OnSelchangeRight1();
	afx_msg void OnSelchangeUp1();
	afx_msg void OnSelchangeSpecial();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
