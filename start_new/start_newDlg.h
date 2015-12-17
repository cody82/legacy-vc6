// start_newDlg.h : header file
//

#if !defined(AFX_START_NEWDLG_H__CC140D47_20D7_11D3_B881_00000100B481__INCLUDED_)
#define AFX_START_NEWDLG_H__CC140D47_20D7_11D3_B881_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CStart_newDlg dialog

class CStart_newDlg : public CDialog
{
// Construction
public:
	CStart_newDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStart_newDlg)
	enum { IDD = IDD_START_NEW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStart_newDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStart_newDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExit();
	afx_msg void OnCredits();
	afx_msg void OnOptions();
	afx_msg void OnStartmulti();
	afx_msg void OnEditor();
	afx_msg void OnStats();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_START_NEWDLG_H__CC140D47_20D7_11D3_B881_00000100B481__INCLUDED_)
