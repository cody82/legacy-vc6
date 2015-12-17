#if !defined(AFX_BITMAPWND_H__80D9D765_49D8_11D3_B882_00000100B481__INCLUDED_)
#define AFX_BITMAPWND_H__80D9D765_49D8_11D3_B882_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitmapWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitmapWnd window

class CBitmapWnd : public CWnd
{
// Construction
public:
	CBitmapWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_Stretch;
	HBITMAP m_Bitmap;
	BOOL LoadBitmap(LPCSTR file);
	virtual ~CBitmapWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBitmapWnd)
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPWND_H__80D9D765_49D8_11D3_B882_00000100B481__INCLUDED_)
