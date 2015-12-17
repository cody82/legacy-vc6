#if !defined(AFX_PLAYERSDIALOG_H__CC140D4F_20D7_11D3_B881_00000100B481__INCLUDED_)
#define AFX_PLAYERSDIALOG_H__CC140D4F_20D7_11D3_B881_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayersDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayersDialog dialog

class CPlayersDialog : public CDialog
{
// Construction
public:
	CPlayersDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlayersDialog)
	enum { IDD = IDD_PLAYERS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayersDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlayersDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYERSDIALOG_H__CC140D4F_20D7_11D3_B881_00000100B481__INCLUDED_)
