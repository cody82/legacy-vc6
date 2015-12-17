#if !defined(AFX_ASTEROIDS_H__96A9AE80_6A10_11D3_83D2_00000100B481__INCLUDED_)
#define AFX_ASTEROIDS_H__96A9AE80_6A10_11D3_83D2_00000100B481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Asteroids.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAsteroids dialog

class CAsteroids : public CPropertyPage
{
	DECLARE_DYNCREATE(CAsteroids)

// Construction
public:
	CAsteroids();
	~CAsteroids();

// Dialog Data
	//{{AFX_DATA(CAsteroids)
	enum { IDD = IDD_ASTEROIDS };
	BOOL	m_asteroids;
	int		m_count;
	int		m_distance;
	int		m_interval;
	int		m_radius;
	int		m_speed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAsteroids)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAsteroids)
	afx_msg void OnAsteroids();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASTEROIDS_H__96A9AE80_6A10_11D3_83D2_00000100B481__INCLUDED_)
