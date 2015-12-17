#if !defined(AFX_SHIPSELECTDLG_H__B38F01C1_21B4_11D3_B881_00000100B481__INCLUDED_)
#define AFX_SHIPSELECTDLG_H__B38F01C1_21B4_11D3_B881_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShipSelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShipSelectDlg dialog

class CShipSelectDlg : public CDialog
{
// Construction
public:
	CShipSelectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShipSelectDlg)
	enum { IDD = IDD_SHIPSELECT };
	CListBox	m_shiplist;
	CListBox	m_playerlist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShipSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShipSelectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangePlayers();
	afx_msg void OnSelchangeShips();
	virtual void OnOK();
	afx_msg void OnOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHIPSELECTDLG_H__B38F01C1_21B4_11D3_B881_00000100B481__INCLUDED_)
