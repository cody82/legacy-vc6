// xswstatisticDlg.h : header file
//

#if !defined(AFX_XSWSTATISTICDLG_H__1E60060E_466F_11D3_B882_00000100B481__INCLUDED_)
#define AFX_XSWSTATISTICDLG_H__1E60060E_466F_11D3_B882_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXswstatisticDlg dialog

class CXswstatisticDlg : public CDialog
{
// Construction
public:
	CXswstatisticDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXswstatisticDlg)
	enum { IDD = IDD_XSWSTATISTIC_DIALOG };
	CString	m_killed1;
	CString	m_killed2;
	CString	m_killed3;
	CString	m_killed4;
	CString	m_killer1;
	CString	m_killer2;
	CString	m_killer3;
	CString	m_killer4;
	int		m_kills11;
	int		m_kills12;
	int		m_kills13;
	int		m_kills14;
	int		m_kills21;
	int		m_kills22;
	int		m_kills23;
	int		m_kills24;
	int		m_kills31;
	int		m_kills32;
	int		m_kills33;
	int		m_kills34;
	int		m_kills41;
	int		m_kills42;
	int		m_kills43;
	int		m_kills44;
	int		m_totalkills1;
	int		m_totalkills2;
	int		m_totalkills3;
	int		m_totalkills4;
	CString	m_fire1;
	CString	m_fire2;
	CString	m_fire3;
	CString	m_fire4;
	int		m_hits1;
	int		m_hits2;
	int		m_hits3;
	int		m_hits4;
	int		m_shots1;
	int		m_shots2;
	int		m_shots3;
	int		m_shots4;
	float	m_accuracy1;
	float	m_accuracy2;
	float	m_accuracy3;
	float	m_accuracy4;
	int		m_deaths1;
	int		m_deaths2;
	int		m_deaths3;
	int		m_deaths4;
	int		m_frags1;
	int		m_frags2;
	int		m_frags4;
	int		m_frags3;
	int		m_suicides1;
	int		m_suicides2;
	int		m_suicides3;
	int		m_suicides4;
	int		m_totalkilled1;
	int		m_totalkilled2;
	int		m_totalkilled3;
	int		m_totalkilled4;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXswstatisticDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXswstatisticDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSWSTATISTICDLG_H__1E60060E_466F_11D3_B882_00000100B481__INCLUDED_)
