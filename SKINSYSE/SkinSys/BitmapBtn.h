///////////////////////////////////////////////////////////////
//
// Dosya Ad�: BitmapBtn.h
// Yazan    : C�neyt EL�BOL
// A��klama : Resim butonlar� i�in kod
// 
// Detayl� Bilgi i�in 
//       
//    www.celibol.freeservers.com  adresini ziyaret edin
//            veya
//    celibol@hotmail.com adresine mesaj at�n.
//
// Dikkat:
//    Bu program kodlar�n� kullan�rken Aciklama.txt dosyas�ndaki
//  gerekleri yerine getirmeniz gerekir.
//
///////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPBTN_H__5B9A5F8E_2016_11D4_8166_C1E4D6E4D62B__INCLUDED_)
#define AFX_BITMAPBTN_H__5B9A5F8E_2016_11D4_8166_C1E4D6E4D62B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitmapBtn.h : header file
//
#include <afxwin.h>
#include <afxcmn.h>

/////////////////////////////////////////////////////////////////////////////
// CBitmapBtn window

class CBitmapBtn : public CButton
{
	void InitToolTip();
	CToolTipCtrl m_ToolTip;
// Construction
public:
	BOOL m_Check, m_CheckedButton;
	CBitmapBtn();
	void SetTooltipText(CString* spText, BOOL bActivate = TRUE);
	void ActivateTooltip(BOOL bEnable = TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapBtn)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetCheck(BOOL m_NewValue);
	void SetBitmap(CBitmap& mNrml, CBitmap& mOvr, CBitmap& mDwn, CBitmap& mDsbl);
	virtual ~CBitmapBtn();

	// Generated message map functions
protected:
	BOOL m_MouseOnButton;
	CBitmap m_Normal, m_Over, m_Down, m_Disabled;
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//{{AFX_MSG(CBitmapBtn)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPBTN_H__5B9A5F8E_2016_11D4_8166_C1E4D6E4D62B__INCLUDED_)
