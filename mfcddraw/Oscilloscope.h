// Oscilloscope.h: Schnittstelle für die Klasse COscilloscope.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OSCILLOSCOPE_H__29505536_E67D_4EF9_80B3_00356A8CA6C0__INCLUDED_)
#define AFX_OSCILLOSCOPE_H__29505536_E67D_4EF9_80B3_00356A8CA6C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DDrawWnd.h"
#include "generator.h"

class COscilloscope : public CDDrawWnd  
{
public:
	COscilloscope();
	virtual ~COscilloscope();

	virtual VOID Shift();
	virtual VOID Update(float dTime);
	virtual VOID Draw(CGenerator *gen,float from,float to);
	virtual VOID DrawCoords();

	float *fCoords;
	float *fReflectCoords;
	DWORD dwCoordCount;
	BOOL bFixedEnd;
	BOOL bReflect;
	float fSpeed;
	CGenerator *lpGenerator;

protected:
	virtual VOID CreateCoords(DWORD count);

	//{{AFX_MSG(COscilloscope)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_OSCILLOSCOPE_H__29505536_E67D_4EF9_80B3_00356A8CA6C0__INCLUDED_)
