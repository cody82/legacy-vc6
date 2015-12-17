#if !defined(AFX_SOUNDPAGE_H__BCDCE0A0_6F82_11D3_83D2_00000100B481__INCLUDED_)
#define AFX_SOUNDPAGE_H__BCDCE0A0_6F82_11D3_83D2_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SoundPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSoundPage dialog

class CSoundPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSoundPage)

// Construction
public:
	CSoundPage();
	~CSoundPage();

// Dialog Data
	//{{AFX_DATA(CSoundPage)
	enum { IDD = IDD_SOUND };
	CSliderCtrl	m_master;
	CSliderCtrl	m_speech;
	CSliderCtrl	m_sfx;
	CSliderCtrl	m_music;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSoundPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSoundPage)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDPAGE_H__BCDCE0A0_6F82_11D3_83D2_00000100B481__INCLUDED_)
