// start_new.h : main header file for the START_NEW application
//

#if !defined(AFX_START_NEW_H__CC140D45_20D7_11D3_B881_00000100B481__INCLUDED_)
#define AFX_START_NEW_H__CC140D45_20D7_11D3_B881_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStart_newApp:
// See start_new.cpp for the implementation of this class
//

class CStart_newApp : public CWinApp
{
public:
	CStart_newApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStart_newApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStart_newApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_START_NEW_H__CC140D45_20D7_11D3_B881_00000100B481__INCLUDED_)
