#ifndef __AVIITEMH
#define __AVIITEMH
#include <windows.h>
#include <mmsystem.h>
#include <vfw.h>
#include "dibapi.h"
#include "dib.h"
#include "engine.h"
#include "sprite.h"

//link: winmm.lib vfw32.lib

class AviItem : public BaseItem
{
public:
	DWORD CurrentTime;

	UINT tplastupdate;

	BOOL FileOpen;
	BOOL isPlaying;
	BOOL Loop;
	BOOL reverse;

	BaseItem *attach;
	POINT attachpos;

	//POINT size;
	VECTOR speed;

  	PAVIFILE pfile;
	PAVISTREAM pstream;
	AVISTREAMINFO streaminfo;
	PGETFRAME pframe;
	BITMAPINFOHEADER bminfo;
	LPVOID drawdata;

	AviItem();

	virtual ~AviItem();

	BOOL Open(LPCSTR file);

	virtual void Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y);

	virtual void Update(UINT dtime);

	void Close();

	void Play(BOOL loop);

	void Stop();

	void Pause();

	void Reverse();

	BOOL InScreen();
};
#endif