// keyboardDlg.h : header file
//

#if !defined(AFX_KEYBOARDDLG_H__C1C0DA07_1D10_11D3_B881_00000100B481__INCLUDED_)
#define AFX_KEYBOARDDLG_H__C1C0DA07_1D10_11D3_B881_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dsplayer.h>
/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg dialog

class CKeyboardDlg : public CDialog
{
// Construction
public:
	DSPlayer ds;
	CKeyboardDlg(CWnd* pParent = NULL);	// standard constructor
	void DSPlay(int i,CString file);

// Dialog Data
	//{{AFX_DATA(CKeyboardDlg)
	enum { IDD = IDD_KEYBOARD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyboardDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKeyboardDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnA();
	afx_msg void OnB();
	afx_msg void OnC();
	afx_msg void OnD();
	afx_msg void OnE();
	afx_msg void OnF();
	afx_msg void OnG();
	afx_msg void OnH();
	afx_msg void OnI();
	afx_msg void OnJ();
	afx_msg void OnK();
	afx_msg void OnL();
	afx_msg void OnM();
	afx_msg void OnN();
	afx_msg void OnO();
	afx_msg void OnP();
	afx_msg void OnQ();
	afx_msg void OnR();
	afx_msg void OnS();
	afx_msg void OnT();
	afx_msg void OnU();
	afx_msg void OnV();
	afx_msg void OnW();
	afx_msg void OnX();
	afx_msg void OnY();
	afx_msg void OnZ();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYBOARDDLG_H__C1C0DA07_1D10_11D3_B881_00000100B481__INCLUDED_)
