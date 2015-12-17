#ifndef __BITMAPITEMH
#define __BITMAPITEMH

#define DIRECTDRAW_VERSION 0x0100
#include <ddraw.h>
#include "sprite.h"
#include "engine.h"
#include "int2str.h"

//link: ddraw.lib

class BitmapItem : public BaseItem
{
public:
	LPDIRECTDRAWSURFACE3 lpDDSBitmap;
	
	UINT tplastupdate;
	BOOL colorkey;

	BaseItem *attach;
	POINT attachpos;
	char bmpfile[64];

//	POINT size;
	VECTOR speed;

	BitmapItem();

	virtual ~BitmapItem();

	BOOL Load(LPSTR file,BOOL autocolorkey,LPDIRECTDRAW dd=NULL);

	virtual void Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y);

	virtual void Update(UINT dtime);

	BOOL InScreen();

	void SetColorkey(int r,int g,int b);

	virtual void RestoreSurfaces();
};
#endif