// fa.h : main header file for the FA application
//

#if !defined(AFX_FA_H__AC79AEA0_E85B_11D3_BF26_00000100B481__INCLUDED_)
#define AFX_FA_H__AC79AEA0_E85B_11D3_BF26_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFaApp:
// See fa.cpp for the implementation of this class
//

class CFaApp : public CWinApp
{
public:
	CFaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFaApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FA_H__AC79AEA0_E85B_11D3_BF26_00000100B481__INCLUDED_)
