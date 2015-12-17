// mfcddrawDlg.h : Header-Datei
//

#if !defined(AFX_MFCDDRAWDLG_H__2FF55F9D_196C_4950_8CF0_174D22F133BE__INCLUDED_)
#define AFX_MFCDDRAWDLG_H__2FF55F9D_196C_4950_8CF0_174D22F133BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMfcddrawDlg Dialogfeld
#include "oscilloscope.h"

class CMfcddrawDlg : public CDialog
{
// Konstruktion
public:
	virtual VOID Update();
	CMfcddrawDlg(CWnd* pParent = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CMfcddrawDlg)
	enum { IDD = IDD_MFCDDRAW_DIALOG };
	int		m_reflect;
	int		m_amp;
	int		m_speed;
	float	m_hz;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CMfcddrawDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void OnChange();
	HICON m_hIcon;
	COscilloscope ddraw;
	CWaveGenerator gen;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CMfcddrawDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_MFCDDRAWDLG_H__2FF55F9D_196C_4950_8CF0_174D22F133BE__INCLUDED_)
