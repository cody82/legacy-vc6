#ifndef __MCICDPLAYER
#define __MCICDPLAYER
#include <windows.h>
#include <mmsystem.h>
//link: winmm.lib
class CDPlayer
{
public:
	UINT MCIDeviceID;
	UINT track;
	HWND hwnd;
	CDPlayer::CDPlayer();	
	CDPlayer::~CDPlayer();
	BOOL CDPlayer::Initialize();
	BOOL CDPlayer::Play(UINT Track,HWND notify=NULL);
	BOOL CDPlayer::Stop();
	void CDPlayer::OnWMNotify(WPARAM wparam,LPARAM lparam);
};
#endif