#if !defined(AFX_BMPLIST_H__80D9D775_49D8_11D3_B882_00000100B481__INCLUDED_)
#define AFX_BMPLIST_H__80D9D775_49D8_11D3_B882_00000100B481__INCLUDED_

#include "BitmapWnd.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BMPList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBMPList dialog

class CBMPList : public CDialog
{
// Construction
public:
	CBitmapWnd bitmaps[8];
	CBMPList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBMPList)
	enum { IDD = IDD_BMPLIST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBMPList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBMPList)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPLIST_H__80D9D775_49D8_11D3_B882_00000100B481__INCLUDED_)
