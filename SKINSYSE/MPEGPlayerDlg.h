// MPEGPlayerDlg.h : header file
//

#if !defined(AFX_MPEGPLAYERDLG_H__0C09C696_3575_11D4_8168_F836E155409C__INCLUDED_)
#define AFX_MPEGPLAYERDLG_H__0C09C696_3575_11D4_8168_F836E155409C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMPEGPlayerDlg dialog

class CMPEGPlayerDlg : public CSkinDialog
{
// Construction
public:
	CMPEGPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMPEGPlayerDlg)
	enum { IDD = IDD_MPEGPLAYER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMPEGPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
//	virtual void ProgresChanged(CString m_Name);
	// Generated message map functions
	//{{AFX_MSG(CMPEGPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnLoadskin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetEQ(int Ch, int mVal);
	MPPlayer m_Player;
	BOOL m_PosScroll, m_VolScroll;
	real FrameCnt;

	void ProgresChanged(CString m_Name);
	void MouseMoved(CString m_ButtonName, int x, int y);
	void StopProc();
	void TrackChange(CString m_ButtonName, UINT nSBCode, UINT nPos);
	void OpenNew(CString m_FName);
	void ButtonPressed(CString m_ButtonName);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MPEGPLAYERDLG_H__0C09C696_3575_11D4_8168_F836E155409C__INCLUDED_)
