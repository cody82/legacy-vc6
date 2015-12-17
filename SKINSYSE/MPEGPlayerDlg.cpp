// MPEGPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MPEGPlayer.h"
#include "MPEGPlayerDlg.h"
#include "Decoder/Stream.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	LOWER_LIMIT_DB	-20
#define	UPPER_LIMIT_DB	20
#define	LIMIT_DB_RATIO	3
#define	LOWER_LIMIT		LOWER_LIMIT_DB*LIMIT_DB_RATIO
#define	UPPER_LIMIT		UPPER_LIMIT_DB*LIMIT_DB_RATIO
#define	TOTAL_LIMIT		(UPPER_LIMIT-(LOWER_LIMIT))

#define EQMAXLIMIT     20
#define EQMINLIMIT    -20

UINT StringToID(CString m_ID)
{
	struct ID
	{
		UINT m_ID;
		char* m_Name;
	} IDS[] = { BUTTON_PLAY, "BUTTON_PLAY",
				BUTTON_EJECT, "BUTTON_EJECT",
				BUTTON_STOP, "BUTTON_STOP",
				BUTTON_NEXT, "BUTTON_NEXT",
				BUTTON_PREV, "BUTTON_PREV",
				BUTTON_PAUSE, "BUTTON_PAUSE",
				BUTTON_EXIT, "BUTTON_EXIT",
				BUTTON_MINIMIZE, "BUTTON_MINIMIZE",
				BUTTON_PLAYLIST, "BUTTON_PLAYLIST",
				BUTTON_NEXTTRACK, "BUTTON_NEXTTRACK",
				BUTTON_PREVTRACK, "BUTTON_PREVTRACK",
				TEXT_SONG, "TEXT_SONG",
				TEXT_LEN, "TEXT_LEN",
				TEXT_POS, "TEXT_POS",
				TEXT_HINT, "TEXT_HINT",
				TRACKBAR_VOLUME, "TRACKBAR_VOLUME",
				TRACKBAR_POS, "TRACKBAR_POS" };

	for(int i = 0; i < sizeof(IDS) / sizeof(ID); i++)
	{
		if(m_ID == IDS[i].m_Name)
			return IDS[i].m_ID;
	}
	return 0;
}

CString msToStr(UINT m_Pos)
{
	CString m_Time;
	m_Time.Format("%02d:%02d", m_Pos / (60 * 1000),
		            (m_Pos / 1000) % 60);
	return m_Time;
}
/////////////////////////////////////////////////////////////////////////////
// CMPEGPlayerDlg dialog

CMPEGPlayerDlg::CMPEGPlayerDlg(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CMPEGPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMPEGPlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMPEGPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMPEGPlayerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMPEGPlayerDlg, CSkinDialog)
	//{{AFX_MSG_MAP(CMPEGPlayerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_COMMAND(ID_LOADSKIN, OnLoadskin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMPEGPlayerDlg message handlers

BOOL CMPEGPlayerDlg::OnInitDialog()
{
	char m_skin[512];

	sprintf(m_skin, "Sample/Skin.ini");
	SetMenuID(IDR_MAINMENU);
	SetWindowText("MPEG Player");
	SetSkinFile(m_skin);
	CSkinDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	StopProc();

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMPEGPlayerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CSkinDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMPEGPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMPEGPlayerDlg::ButtonPressed(CString m_ButtonName)
{
	if(m_ButtonName == "BUTTON_EXIT")
		EndDialog(IDOK);
	if(m_ButtonName == "BUTTON_USEEQ")
	{
		Args->UseEqualizer = !Args->UseEqualizer;
		SetButtonCheck("BUTTON_USEEQ", Args->UseEqualizer);
	}
	else if(m_ButtonName == "BUTTON_EJECT")
	{
		CString m_FName = GetFileName(GetSafeHwnd(), "MP3 files\0*.MP3\0\0");
		if(!m_FName.IsEmpty()) OpenNew(m_FName);
	}
	else if(m_ButtonName == "BUTTON_PLAY")
	{
		if(m_Player.PlayerMode() == pmReady) 
			m_Player.Play();
		else if(m_Player.PlayerMode() == pmPaused)//if(GetButtonCheck("BUTTON_PLAY")
			m_Player.Resume();
		SetButtonCheck("BUTTON_PLAY", true);
		SetButtonCheck("BUTTON_PAUSE", false);
		KillTimer(1);
		SetTimer(1, 1000, NULL);
	}
	else if(m_ButtonName == "BUTTON_PAUSE")
	{
		if(m_Player.PlayerMode() == pmPlaying || m_Player.PlayerMode() == pmReady)
		{
			m_Player.Pause();
			KillTimer(1);
			SetButtonCheck("BUTTON_PAUSE", true);
			SetButtonCheck("BUTTON_PLAY", false);
		}
	}
	else if(m_ButtonName == "BUTTON_STOP")
	{
		StopProc();
	}
	else if(m_ButtonName == "BUTTON_MINIMIZE")
	{
		ShowWindow(SW_SHOWMINIMIZED);
	}
}

void CMPEGPlayerDlg::OpenNew(CString m_FName)
{
	m_Player.SetWindow(GetSafeHwnd());
	if(m_Player.PlayerMode() != pmClosed)
	{
		StopProc();
	}
	m_Player.SetInName(m_FName);
	m_Player.Open();
	if(!m_Player.InitStream()) return;

	FrameCnt = Totalms(); 

	SetText("TEXT_LEN", msToStr((UINT) FrameCnt));
	CString mPath = getPath(m_FName), MFName(m_FName);
	MFName.Delete(0, mPath.GetLength());

	SetText("TEXT_SONG", MFName);
	SetText("TEXT_POS", "00:00");
	SetButtonEnable("BUTTON_PLAY", TRUE);
	SetButtonEnable("BUTTON_PAUSE", TRUE);
	SetButtonEnable("BUTTON_STOP", TRUE);

}

void CMPEGPlayerDlg::TrackChange(CString m_ButtonName, UINT nSBCode, UINT nPos)
{
	if(m_ButtonName == "TRACKBAR_VOLUME")
	{
		m_VolScroll = true;
		int Vol = GetTrackBarPos("TRACKBAR_VOLUME");
		CString m_Hint;
		m_Hint.Format("Ses: %%%d", Vol);
		SetText("TEXT_HINT", m_Hint);

		if(nSBCode == SB_ENDSCROLL)
		{
			Vol *= (65535 / 100);
			Vol = Vol << 16 | Vol;
			m_Player.SetVolume(Vol);
			SetText("TEXT_HINT", "Ses Ayarlandý");
			m_VolScroll = false;
		}
	}
	else if(m_ButtonName == "TRACKBAR_BALANCE")
	{
		unsigned long m_Vol, m_N;
		int m_Pos = GetTrackBarPos("TRACKBAR_BALANCE"),
			m_L, m_R;

		m_Player.GetVolume(&m_Vol);
		m_L = LOWORD(m_Vol);
		m_R = HIWORD(m_Vol);
		if(m_Pos > 50)
			m_R = ((0xffff * (100 - m_Pos) * 2) / 100);
		else if (m_Pos < 50)
			m_L = ((0xffff * m_Pos * 2) / 100);
		m_N = m_L << 16 | m_R;
		CString m_Hint;
		if(m_Pos < 50)
			m_Hint.Format("Hoparlör: %%%d Sol", m_Pos * 2);
		else if(m_Pos > 50)
			m_Hint.Format("Hoparlör: %%%d Sað", (100 - m_Pos) * 2);
		else
			m_Hint = "Hoparlör: Orta";
		SetText("TEXT_HINT", m_Hint);
		if(nSBCode == SB_ENDSCROLL)
			m_Player.SetVolume(m_N == 0 ? m_Vol : m_N);
	}
	else if(m_ButtonName == "TRACKBAR_POS")
	{
		int m_Pos = GetTrackBarPos("TRACKBAR_POS");
		UINT m_Cur = (UINT) (FrameCnt * m_Pos) / 100;
		CString m_Hint;
		m_Hint.Format("Pozisyon: %%%d, %s/%s", m_Pos, 
			msToStr(m_Cur), msToStr((UINT) FrameCnt));
		SetText("TEXT_HINT", m_Hint);
		SetProgressPos("PROGRESS_POS", (UINT) (FrameCnt * m_Pos) / 100);
		if(nSBCode == SB_ENDSCROLL)
		{
			m_Player.SetPos((UINT) (FrameCnt * m_Pos) / 100);
			m_PosScroll = false;
		}
		else
			m_PosScroll = true;
	}
	else if(m_ButtonName.Find("TRACKBAR_EQ") > -1)
	{
		CString m_EQ = m_ButtonName;
		m_EQ.Delete(0, 11);
		int mVal = GetTrackBarPos(m_ButtonName);
		SetProgressPos("PROGRESS_EQ" + m_EQ, mVal);
		if(nSBCode == SB_ENDSCROLL)
			SetEQ(atoi(m_EQ), mVal);
	}
}

void CMPEGPlayerDlg::SetEQ(int Ch, int mVal)
{
	if(mVal < 50)
		mVal = ((((50 - mVal) * 100) / 50) * EQMINLIMIT) / 100;
	else
		mVal = ((((mVal - 50) * 100) / 50) * EQMAXLIMIT) / 100;
	if(mVal == 0) mVal = 1;
	else mVal *= -1 ;

	double eq[32];
	double  Value = (double) mVal * 0.15;
	for(int i = 0; i < 32; i++)
		eq[i] = equalizer[0][i];
	switch(Ch) 
   {
	case 1:
		eq[0] = Value;
		break;
	case 2:
		eq[1] = Value;
		break;
	case 3:
		eq[2] = Value;
		break;
	case 4:
		eq[3] = Value;
		eq[4] = Value;
		eq[5] = Value;
	case 5:
		eq[6] = Value;
		eq[7] = Value;
		break;
	case 6:
		eq[8] = Value;
		eq[9] = Value;
		eq[10] = Value;
		eq[11] = Value;
		break;
	case 7:
		eq[12] = Value;
		eq[13] = Value;
		eq[14] = Value;
		eq[15] = Value;
		eq[16] = Value;
		eq[17] = Value;
		eq[18] = Value;
		eq[19] = Value;
		break;
	case 8:
		eq[20] = Value;
		eq[21] = Value;
		eq[22] = Value;
		eq[23] = Value;
		eq[24] = Value;
		eq[25] = Value;
		eq[26] = Value;
		eq[27] = Value;
		eq[28] = Value;
		eq[29] = Value;
		eq[30] = Value;
		eq[31] = Value;
		break;
	default:
      return;
	}

/*	switch(Ch) 
   {
	case 1:
		eq[0] = Value;
		break;
	case 2:
		eq[1] = Value;
		break;
	case 3:
		eq[2] = Value;
		break;
	case 4:
		eq[3] = Value;
		eq[4] = Value;
		eq[5] = Value;
	case 5:
		eq[6] = Value;
		eq[7] = eq[6];
		break;
	case 6:
		eq[8] = Value;
		eq[9] = eq[8];
		eq[10] = eq[8];
		eq[11] = eq[8];
		break;
	case 7:
		eq[12] = Value;
		eq[13] = eq[12];
		eq[14] = eq[12];
		eq[15] = eq[12];
		eq[16] = eq[12];
		eq[17] = eq[12];
		eq[18] = eq[12];
		eq[19] = eq[12];
		break;
	case 8:
		eq[20] = Value;
		eq[21] = eq[20];
		eq[22] = eq[20];
		eq[23] = eq[20];
		eq[24] = eq[20];
		eq[25] = eq[20];
		eq[26] = eq[20];
		eq[27] = eq[20];
		eq[28] = eq[20];
		eq[29] = eq[20];
		eq[30] = eq[20];
		eq[31] = eq[20];
		break;
	default:
      return;
	}
*/
	for(i = 0; i < 32; i++)
	{
		equalizer[0][i] = eq[i];
		equalizer[1][i] = eq[i];
	}
}

void CMPEGPlayerDlg::ProgresChanged(CString m_Name)
{
	if(m_Name == "PROGRESS_POS")
	{
		int m_Pos = GetProgressPos("PROGRESS_POS");
		m_Player.SetPos((UINT) (FrameCnt * m_Pos) / 100);
		SetTrackBarPos("TRACKBAR_POS", (UINT) (FrameCnt * m_Pos) / 100);
	}
	else if(m_Name == "PROGRESS_VOL")
	{
		int Vol = GetProgressPos("PROGRESS_VOL");
		SetTrackBarPos("TRACKBAR_VOLUME", Vol);
		Vol *= (65535 / 100);
		Vol = Vol << 16 | Vol;
		m_Player.SetVolume(Vol);
	}
}

void CMPEGPlayerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1)
	{
		switch(m_Player.PlayerMode())
		{
			case pmReady:
			case pmPlaying:
				{
					SetText("TEXT_POS", msToStr(Currentms()));
					if(!m_PosScroll)
						SetTrackBarPos("TRACKBAR_POS", (UINT) ((100 * Currentms()) / FrameCnt));
					SetProgressPos("PROGRESS_POS", (UINT) ((100 * Currentms()) / FrameCnt));
				}
				break;

			case pmStopped:
				StopProc();
				break;
		}
	}
	else CSkinDialog::OnTimer(nIDEvent);
}

void CMPEGPlayerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CSkinDialog::OnClose();
}

void CMPEGPlayerDlg::StopProc()
{
	if(m_Player.PlayerMode() != pmClosed)
	{
		if(m_Player.PlayerMode() == pmPlaying)
			m_Player.Stop();
		m_Player.Close();
	}
	SetButtonCheck("BUTTON_PAUSE", false);
	SetButtonCheck("BUTTON_PLAY", false);
	SetTrackBarPos("TRACKBAR_POS", 0);
	SetProgressPos("PROGRESS_POS", 0);
	SetText("TEXT_SONG", "");
	SetText("TEXT_POS", "");
	SetText("TEXT_LEN", "");
	m_PosScroll = FALSE;
	m_VolScroll = FALSE;
	SetTrackBarPos("TRACKBAR_POS", 0);
	SetTrackBarPos("TRACKBAR_VOLUME", 100);
	SetText("TEXT_SONG", "Þarkýyý Seçin");
	SetButtonEnable("BUTTON_PLAY", FALSE);
	SetButtonEnable("BUTTON_PAUSE", FALSE);
	SetButtonEnable("BUTTON_STOP", FALSE);

	KillTimer(1);
}

void CMPEGPlayerDlg::MouseMoved(CString m_ButtonName, int x, int y)
{
	if(m_PosScroll || m_VolScroll) return;
	CString m_Hint = "";
	if(!m_ButtonName.IsEmpty())
	{
		UINT m_ID = StringToID(m_ButtonName);
		if(m_ID > 0)
			m_Hint.LoadString(m_ID);
	}
	SetText("TEXT_HINT", m_Hint);
}

void CMPEGPlayerDlg::OnLoadskin() 
{
	// TODO: Add your command handler code here
	CString m_SknName= GetFileName(GetSafeHwnd(), "Skin Dosyalarý\0*.ini\0\0");
	if(!m_SknName.IsEmpty())//(m_newSkin[0] != 0) 	
	{
		char m_newSkin[512];
		sprintf(m_newSkin, "%s", m_SknName);
		SetSkinFile(m_newSkin);
		LoadSkins();
	}
}
