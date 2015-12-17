#ifndef __WNDITEM_H
#define __WNDITEM_H

#include "engine.h"

#define WNDMAXITEMS 40

class WndItem : public BaseItem
{
public:

	DWORD color;
	BOOL transparent;
	BaseItem *items[WNDMAXITEMS];

	WndItem();
	~WndItem();
	virtual void Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y);
	virtual void Update(UINT tnow);
	virtual void RestoreSurfaces();
	virtual void OnPress(int x,int y);
	BOOL AddItem(BaseItem *bi);
	POINT GetCenterPos(BaseItem *bi);
};

#endif