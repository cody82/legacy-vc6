#ifndef __AVIPLAYTESTH
#define __AVIPLAYTESTH
#include <windows.h>
#include <mmsystem.h>
#include <vfw.h>
#include "dibapi.h"
#include "dib.h"

//link: winmm.lib vfw32.lib

class CAVIPlayTest
{
public:
	DWORD CurrentTime;
	BOOL FileOpen;

  	PAVIFILE pfile;
	PAVISTREAM pstream;
	AVISTREAMINFO streaminfo;
	PGETFRAME pframe;
	BITMAPINFOHEADER bminfo;

	CAVIPlayTest();

	~CAVIPlayTest();

	BOOL Open(LPCSTR file);

	BOOL Paint(HDC hdc);

	void Close();

};
#endif