// filearchivDlg.h : header file
//

#if !defined(AFX_FILEARCHIVDLG_H__94AEAD0D_58A5_11D3_B882_00000100B481__INCLUDED_)
#define AFX_FILEARCHIVDLG_H__94AEAD0D_58A5_11D3_B882_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFilearchivDlg dialog

class CFilearchivDlg : public CDialog
{
// Construction
public:
	CFilearchivDlg(CWnd* pParent = NULL);	// standard constructor
struct LOADSTRUCT
{
	char path[256];
	BOOL dir;
};
void CFilearchivDlg::AddFiles(CString path,CFile *f);
BOOL CFilearchivDlg::load(CFile *f,LOADSTRUCT *ls);

// Dialog Data
	//{{AFX_DATA(CFilearchivDlg)
	enum { IDD = IDD_FILEARCHIV_DIALOG };
	CListBox	m_list2;
	CListBox	m_list1;
	CString	m_edit1;
	int		m_count;
	CString	m_edit2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilearchivDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFilearchivDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnScan();
	afx_msg void OnLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEARCHIVDLG_H__94AEAD0D_58A5_11D3_B882_00000100B481__INCLUDED_)
