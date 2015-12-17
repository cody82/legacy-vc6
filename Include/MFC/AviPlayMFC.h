#if !defined(AFX_AVIPLAYMFC_H__98E74480_6454_11D3_83D2_00000100B481__INCLUDED_)
#define AFX_AVIPLAYMFC_H__98E74480_6454_11D3_83D2_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AviPlayMFC.h : header file
//
//#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
//#include <afxext.h>         // MFC extensions
//#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
//#ifndef _AFX_NO_AFXCMN_SUPPORT
//#include <afxcmn.h>			// MFC support for Windows Common Controls
//#endif // _AFX_NO_AFXCMN_SUPPORT

#include "caviplaytest.h"

/////////////////////////////////////////////////////////////////////////////
// CAviPlayMFC window

class CAviPlayMFC : public CWnd
{
// Construction
public:
	CAviPlayMFC();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAviPlayMFC)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	CWinThread thread;
	HANDLE htread;
	LONG sample;
	BOOL Loop;
	DWORD starttime;
	CAVIPlayTest avi;
	BOOL Pause();
	BOOL Stop();
	BOOL Play(BOOL loop);
	BOOL Open(CString file);
	virtual ~CAviPlayMFC();
	static DWORD PaintThread(void *p);

	// Generated message map functions
protected:
	//{{AFX_MSG(CAviPlayMFC)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIPLAYMFC_H__98E74480_6454_11D3_83D2_00000100B481__INCLUDED_)
