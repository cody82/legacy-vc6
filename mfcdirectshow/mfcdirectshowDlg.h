// mfcdirectshowDlg.h : Header-Datei
//

#if !defined(AFX_MFCDIRECTSHOWDLG_H__10C4DA80_8B46_46DF_86EC_2233D8E3793C__INCLUDED_)
#define AFX_MFCDIRECTSHOWDLG_H__10C4DA80_8B46_46DF_86EC_2233D8E3793C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "directshowwnd.h"

/////////////////////////////////////////////////////////////////////////////
// CMfcdirectshowDlg Dialogfeld

class CMfcdirectshowDlg : public CDialog
{
// Konstruktion
public:
	CMfcdirectshowDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CMfcdirectshowDlg)
	enum { IDD = IDD_MFCDIRECTSHOW_DIALOG };
	CString	m_file;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMfcdirectshowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;
	CDirectShowWnd dshow;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CMfcdirectshowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFullscreen();
	afx_msg void OnPlay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MFCDIRECTSHOWDLG_H__10C4DA80_8B46_46DF_86EC_2233D8E3793C__INCLUDED_)
