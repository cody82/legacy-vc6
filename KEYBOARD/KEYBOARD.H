// keyboard.h : main header file for the KEYBOARD application
//

#if !defined(AFX_KEYBOARD_H__C1C0DA05_1D10_11D3_B881_00000100B481__INCLUDED_)
#define AFX_KEYBOARD_H__C1C0DA05_1D10_11D3_B881_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKeyboardApp:
// See keyboard.cpp for the implementation of this class
//

class CKeyboardApp : public CWinApp
{
public:
	CKeyboardApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyboardApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKeyboardApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYBOARD_H__C1C0DA05_1D10_11D3_B881_00000100B481__INCLUDED_)
