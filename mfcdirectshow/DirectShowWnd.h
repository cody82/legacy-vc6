#if !defined(AFX_DIRECTSHOWWND_H__60EC0DB1_0C4D_491E_8B46_72023706FAF5__INCLUDED_)
#define AFX_DIRECTSHOWWND_H__60EC0DB1_0C4D_491E_8B46_72023706FAF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirectShowWnd.h : Header-Datei
//

#include <dshow.h>
#include <tchar.h>

#define WM_GRAPHNOTIFY  WM_USER+13

/////////////////////////////////////////////////////////////////////////////
// Fenster CDirectShowWnd 

class CDirectShowWnd : public CWnd
{
// Konstruktion
public:
	CDirectShowWnd();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDirectShowWnd)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual BOOL Stop();
	virtual BOOL Pause();
	virtual BOOL SetSpeed(FLOAT rate);
	virtual BOOL GoToFrame(LONG frame);
	virtual BOOL GoTo(LONG ms);
	virtual BOOL ToggleFullscreen();
	virtual BOOL Create(int x,int y,CWnd *parent);
	virtual BOOL Play();
	virtual VOID Close();
	virtual BOOL Open(LPCSTR file);
	virtual HRESULT InitVideoWindow(int nMultiplier, int nDivider);
	virtual ~CDirectShowWnd();

	// DirectShow interfaces
	IGraphBuilder *pGB;
	IMediaControl *pMC;
	IMediaEventEx *pME;
	IVideoWindow  *pVW;
	IBasicAudio   *pBA;
	IBasicVideo   *pBV;
	IMediaSeeking *pMS;

	CString strFile;

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	virtual HRESULT HandleGraphEvent(void);
	//{{AFX_MSG(CDirectShowWnd)
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIRECTSHOWWND_H__60EC0DB1_0C4D_491E_8B46_72023706FAF5__INCLUDED_
