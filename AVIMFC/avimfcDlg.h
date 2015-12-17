// avimfcDlg.h : header file
//

#if !defined(AFX_AVIMFCDLG_H__98E74488_6454_11D3_83D2_00000100B481__INCLUDED_)
#define AFX_AVIMFCDLG_H__98E74488_6454_11D3_83D2_00000100B481__INCLUDED_

#include "AviPlayMFC.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAvimfcDlg dialog

class CAvimfcDlg : public CDialog
{
// Construction
public:
	CAviPlayMFC avi;
	CAvimfcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAvimfcDlg)
	enum { IDD = IDD_AVIMFC_DIALOG };
	long	m_edit1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAvimfcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAvimfcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIMFCDLG_H__98E74488_6454_11D3_83D2_00000100B481__INCLUDED_)
