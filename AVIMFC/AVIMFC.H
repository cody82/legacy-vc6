// avimfc.h : main header file for the AVIMFC application
//

#if !defined(AFX_AVIMFC_H__98E74486_6454_11D3_83D2_00000100B481__INCLUDED_)
#define AFX_AVIMFC_H__98E74486_6454_11D3_83D2_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAvimfcApp:
// See avimfc.cpp for the implementation of this class
//

class CAvimfcApp : public CWinApp
{
public:
	CAvimfcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAvimfcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAvimfcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIMFC_H__98E74486_6454_11D3_83D2_00000100B481__INCLUDED_)
