// faDlg.h : header file
//

#if !defined(AFX_FADLG_H__AC79AEA2_E85B_11D3_BF26_00000100B481__INCLUDED_)
#define AFX_FADLG_H__AC79AEA2_E85B_11D3_BF26_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFaDlg dialog
#include "filearchive.h"

class CFaDlg : public CDialog
{
// Construction
public:
	CFaDlg(CWnd* pParent = NULL);	// standard constructor

	CFileArchive m_fa;
	VOID UpdateList();

// Dialog Data
	//{{AFX_DATA(CFaDlg)
	enum { IDD = IDD_FA_DIALOG };
	CListBox	m_list;
	CString	m_addname;
	CString	m_openname;
	BYTE	m_key;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnClose();
	afx_msg void OnAdd();
	afx_msg void OnExtract();
	afx_msg void OnChangeKey();
	afx_msg void OnAdddir();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FADLG_H__AC79AEA2_E85B_11D3_BF26_00000100B481__INCLUDED_)
