// DPTestDlg.h : header file
//

#if !defined(AFX_DPTESTDLG_H__514183F0_BDFD_11D3_8185_00000100B481__INCLUDED_)
#define AFX_DPTESTDLG_H__514183F0_BDFD_11D3_8185_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDPTestDlg dialog

class CDPTestDlg : public CDialog
{
// Construction
public:
	CDPTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDPTestDlg)
	enum { IDD = IDD_DPTEST_DIALOG };
	CListBox	m_list1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDPTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDPTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DPTESTDLG_H__514183F0_BDFD_11D3_8185_00000100B481__INCLUDED_)
