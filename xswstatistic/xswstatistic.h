// xswstatistic.h : main header file for the XSWSTATISTIC application
//

#if !defined(AFX_XSWSTATISTIC_H__1E60060C_466F_11D3_B882_00000100B481__INCLUDED_)
#define AFX_XSWSTATISTIC_H__1E60060C_466F_11D3_B882_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXswstatisticApp:
// See xswstatistic.cpp for the implementation of this class
//

class CXswstatisticApp : public CWinApp
{
public:
	CXswstatisticApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXswstatisticApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXswstatisticApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSWSTATISTIC_H__1E60060C_466F_11D3_B882_00000100B481__INCLUDED_)
