#ifndef __DSPLAYER
#define __DSPLAYER

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <dsutil3d.h>
#include <stdio.h>
#include <stdlib.h>
#include "profiles.h"
#include "int2str.h"
//#include "gaudio.h"

#define MAXSOUNDS 100
#define MAXORGINALSOUNDS 100
#define SOUNDMINVOLUME -3000

#define SOUNDTYPE_FX 1
#define SOUNDTYPE_MUSIC 2
#define SOUNDTYPE_SPEECH 3

class DSPlayer
{
public:
	LPDIRECTSOUND lpDS;

	LPDIRECTSOUNDBUFFER lpDSB[MAXSOUNDS];

	LPDIRECTSOUNDBUFFER lpDSBOrg[MAXORGINALSOUNDS];

	//GAUDIO_MP3STREAM mp3;

	char filenames[MAXORGINALSOUNDS][MAX_PATH];
	char soundtype[MAXORGINALSOUNDS][64];
	BOOL loop[MAXORGINALSOUNDS];
	int minvolume;

	DSPlayer();
	~DSPlayer();
	BOOL Initialize(HWND hwnd,DWORD dsprio=DSSCL_NORMAL);
	int LoadSound(LPCSTR file);
	int Play(int n,BOOL loop);
	int Play(int n);
	int PlayFile(LPCSTR file,BOOL loop);
	void ReleaseUnusedBuffers();
	BOOL ReleaseOrginalBuffer(int n);
	BOOL ReleaseOrginalBufferFile(LPCSTR file);
	void SetVolume(int percent);
	void SetVolume(int n,int percent);
	void SetVolume2(LPSTR type,int percent);
	void SetType(int n,LPSTR type2);
	BOOL LoadSounds(LPSTR inifile);
	BOOL LoadSound(LPSTR file,int i);
	int GetSoundNr(LPSTR file);

	//BOOL PlayMP3(LPSTR file);
};
#endif