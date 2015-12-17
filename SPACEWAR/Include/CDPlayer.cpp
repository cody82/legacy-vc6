
#include "cdplayer.h"

CDPlayer::CDPlayer()
{
	MCIDeviceID=0;
	Initialize();
}

CDPlayer::~CDPlayer()
{
	Stop();
	mciSendCommand(MCIDeviceID, MCI_CLOSE, 0, NULL);
}

BOOL CDPlayer::Initialize()
{
	MCI_OPEN_PARMS mciOpenParms;
	
	// Open the CD audio device by specifying the device name.
	mciOpenParms.lpstrDeviceType = "cdaudio";
	if (mciSendCommand(NULL, MCI_OPEN,
		MCI_OPEN_TYPE, (DWORD)(LPVOID) &mciOpenParms))
	{
		// Failed to open device. Don't close it; just return error.
		return FALSE;
	}
	
	// The device opened successfully; get the device ID.
	MCIDeviceID = mciOpenParms.wDeviceID;
	return TRUE;
}

BOOL CDPlayer::Play(UINT Track,HWND notify)
{
	MCI_SET_PARMS mciSetParms;
	MCI_PLAY_PARMS mciPlayParms;
	
	hwnd=notify;
	// Set the time format to track/minute/second/frame (TMSF).
	mciSetParms.dwTimeFormat = MCI_FORMAT_TMSF;
	if (mciSendCommand(MCIDeviceID, MCI_SET, 
		MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &mciSetParms))
	{
		return FALSE;
	} 
	// Begin playback from the given track and play until the beginning 
	// of the next track. The window procedure function for the parent 
	// window will be notified with an MM_MCINOTIFY message when 
	// playback is complete. Unless the play command fails, the window 
	// procedure closes the device.
	mciPlayParms.dwFrom = 0L;
	mciPlayParms.dwTo = 0L;
	mciPlayParms.dwFrom = MCI_MAKE_TMSF(Track, 0, 0, 0);
	mciPlayParms.dwTo = MCI_MAKE_TMSF(Track + 1, 0, 0, 0);
	mciPlayParms.dwCallback = (DWORD) notify;
	if (mciSendCommand(MCIDeviceID, MCI_PLAY,
		MCI_FROM | MCI_TO | MCI_NOTIFY, (DWORD)(LPVOID) &mciPlayParms))
	{
		return FALSE;
	}
	track=Track;
	return TRUE;
}

BOOL CDPlayer::Stop()
{
	if(mciSendCommand(MCIDeviceID,MCI_STOP,MCI_WAIT,NULL))
	{
		return FALSE;
	}
	return TRUE;
}

void CDPlayer::OnWMNotify(WPARAM wparam,LPARAM lparam)
{
	Play(track,hwnd);
}
