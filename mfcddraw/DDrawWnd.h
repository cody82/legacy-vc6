#if !defined(AFX_DDRAWWND_H__D1870BF7_AC31_4337_89ED_0A125CF3F77A__INCLUDED_)
#define AFX_DDRAWWND_H__D1870BF7_AC31_4337_89ED_0A125CF3F77A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ddraw.h>


class CDDrawWnd : public CWnd
{
// Konstruktion
public:
	CDDrawWnd();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	//{{AFX_VIRTUAL(CDDrawWnd)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual BOOL Create(int left,int top,int width,int height,CWnd *parent);
	virtual BOOL Flip();
	virtual VOID ReleaseDDrawDC();
	virtual CDC *GetDDrawDC();
	virtual BOOL Clear();
	virtual BOOL Restore();
	LPDIRECTDRAW lpDD;
	LPDIRECTDRAWCLIPPER lpDDClip;
	LPDIRECTDRAWSURFACE lpDDSPrimary;
	LPDIRECTDRAWSURFACE lpDDSBackBuffer;
	CDC DDrawDC;

	virtual ~CDDrawWnd();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	virtual VOID Shutdown();
	virtual BOOL InitDirectDraw();
	//{{AFX_MSG(CDDrawWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // AFX_DDRAWWND_H__D1870BF7_AC31_4337_89ED_0A125CF3F77A__INCLUDED_
