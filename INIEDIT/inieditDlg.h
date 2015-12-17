// inieditDlg.h : header file
//

#if !defined(AFX_INIEDITDLG_H__AB12D447_4504_11D3_B882_00000100B481__INCLUDED_)
#define AFX_INIEDITDLG_H__AB12D447_4504_11D3_B882_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInieditDlg dialog

class CInieditDlg : public CDialog
{
// Construction
public:
	CInieditDlg(CWnd* pParent = NULL);	// standard constructor
	void CInieditDlg::LoadINIFile(char *filename);
	void CInieditDlg::SaveINIFile(HTREEITEM hti);

// Dialog Data
	//{{AFX_DATA(CInieditDlg)
	enum { IDD = IDD_INIEDIT_DIALOG };
	CTreeCtrl	m_tree1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInieditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInieditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLoad();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSave();
	afx_msg void OnNew();
	afx_msg void OnKeydownTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnButton3();
	afx_msg void OnEdit();
	afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReload();
	afx_msg void OnExit();
	afx_msg void OnSort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INIEDITDLG_H__AB12D447_4504_11D3_B882_00000100B481__INCLUDED_)
