// MPEGPlayer.h : main header file for the MPEGPLAYER application
//

#if !defined(AFX_MPEGPLAYER_H__0C09C694_3575_11D4_8168_F836E155409C__INCLUDED_)
#define AFX_MPEGPLAYER_H__0C09C694_3575_11D4_8168_F836E155409C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMPEGPlayerApp:
// See MPEGPlayer.cpp for the implementation of this class
//

class CMPEGPlayerApp : public CWinApp
{
public:
	CMPEGPlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMPEGPlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMPEGPlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MPEGPLAYER_H__0C09C694_3575_11D4_8168_F836E155409C__INCLUDED_)
