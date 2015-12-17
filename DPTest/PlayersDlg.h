#if !defined(AFX_PLAYERSDLG_H__B4E8AF21_C467_11D3_8A48_00000100B481__INCLUDED_)
#define AFX_PLAYERSDLG_H__B4E8AF21_C467_11D3_8A48_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayersDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayersDlg dialog

class CPlayersDlg : public CDialog
{
// Construction
public:
	CPlayersDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlayersDlg)
	enum { IDD = IDD_PLAYERS };
	CListBox	m_list1;
	CString	m_chat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlayersDlg)
	afx_msg void OnCreate();
	afx_msg void OnUpdate();
	afx_msg void OnSend();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYERSDLG_H__B4E8AF21_C467_11D3_8A48_00000100B481__INCLUDED_)
