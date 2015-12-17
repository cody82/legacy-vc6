#if !defined(AFX_SESSIONDLG_H__514183F8_BDFD_11D3_8185_00000100B481__INCLUDED_)
#define AFX_SESSIONDLG_H__514183F8_BDFD_11D3_8185_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SessionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSessionDlg dialog

class CSessionDlg : public CDialog
{
// Construction
public:
	CSessionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSessionDlg)
	enum { IDD = IDD_SESSIONS };
	CListBox	m_list1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSessionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSessionDlg)
	afx_msg void OnJoin();
	afx_msg void OnCreate();
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SESSIONDLG_H__514183F8_BDFD_11D3_8185_00000100B481__INCLUDED_)
