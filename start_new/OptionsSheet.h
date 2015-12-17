#if !defined(AFX_OPTIONSSHEET_H__CC140D77_20D7_11D3_B881_00000100B481__INCLUDED_)
#define AFX_OPTIONSSHEET_H__CC140D77_20D7_11D3_B881_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsSheet.h : header file
//
#include "optionpages.h"
#include "asteroids.h"
#include "soundpage.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsSheet

class COptionsSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(COptionsSheet)

// Construction
public:
	COptionsSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	COptionsSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	
	COptionPage1 p1;
	COptionPage2 p2;
	COptionPage3 p3;
	COptionPage4 p4;
	CAsteroids a;
	CSoundPage s;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsSheet)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COptionsSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(COptionsSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSSHEET_H__CC140D77_20D7_11D3_B881_00000100B481__INCLUDED_)
