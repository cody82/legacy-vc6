// mfcdirectshow.h : Haupt-Header-Datei f�r die Anwendung MFCDIRECTSHOW
//

#if !defined(AFX_MFCDIRECTSHOW_H__032BADCB_7CEA_48CB_9EE3_097F339DEE26__INCLUDED_)
#define AFX_MFCDIRECTSHOW_H__032BADCB_7CEA_48CB_9EE3_097F339DEE26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CMfcdirectshowApp:
// Siehe mfcdirectshow.cpp f�r die Implementierung dieser Klasse
//

class CMfcdirectshowApp : public CWinApp
{
public:
	CMfcdirectshowApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMfcdirectshowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CMfcdirectshowApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_MFCDIRECTSHOW_H__032BADCB_7CEA_48CB_9EE3_097F339DEE26__INCLUDED_)
