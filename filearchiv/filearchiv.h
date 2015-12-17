// filearchiv.h : main header file for the FILEARCHIV application
//

#if !defined(AFX_FILEARCHIV_H__94AEAD0B_58A5_11D3_B882_00000100B481__INCLUDED_)
#define AFX_FILEARCHIV_H__94AEAD0B_58A5_11D3_B882_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFilearchivApp:
// See filearchiv.cpp for the implementation of this class
//

class CFilearchivApp : public CWinApp
{
public:
	CFilearchivApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilearchivApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFilearchivApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEARCHIV_H__94AEAD0B_58A5_11D3_B882_00000100B481__INCLUDED_)
