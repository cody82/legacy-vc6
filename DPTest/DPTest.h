// DPTest.h : main header file for the DPTEST application
//

#if !defined(AFX_DPTEST_H__514183EE_BDFD_11D3_8185_00000100B481__INCLUDED_)
#define AFX_DPTEST_H__514183EE_BDFD_11D3_8185_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDPTestApp:
// See DPTest.cpp for the implementation of this class
//

class CDPTestApp : public CWinApp
{
public:
	CDPTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDPTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDPTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DPTEST_H__514183EE_BDFD_11D3_8185_00000100B481__INCLUDED_)
