// mfcddraw.h : Haupt-Header-Datei f�r die Anwendung MFCDDRAW
//

#if !defined(AFX_MFCDDRAW_H__8959E2B7_C456_4073_A133_0CCCD6C15356__INCLUDED_)
#define AFX_MFCDDRAW_H__8959E2B7_C456_4073_A133_0CCCD6C15356__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CMfcddrawApp:
// Siehe mfcddraw.cpp f�r die Implementierung dieser Klasse
//

class CMfcddrawApp : public CWinApp
{
public:
	CMfcddrawApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMfcddrawApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CMfcddrawApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_MFCDDRAW_H__8959E2B7_C456_4073_A133_0CCCD6C15356__INCLUDED_)
