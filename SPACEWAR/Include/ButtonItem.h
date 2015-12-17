#ifndef __BUTTONITEM_H
#define __BUTTONITEM_H
#include "engine.h"
#include "bitmapitem.h"
#include "dsutil3d.h"

#define BUTTONPRESSTIME 500

class ButtonItem;
//typedef void(*BTNPROC)(ButtonItem *b);

class ButtonItem : public BaseItem
{
public:

	typedef enum STATE
	{
		NORMAL,PRESSED,FOCUSED,DEACTIVATED
	};
	STATE state;
	UINT tpbuttonpressed;//realtime
	VOIDPROC pressproc;
	BOOL focusedlastupdate;
	//LPDIRECTSOUNDBUFFER lpDSBGetFocus;
	//LPDIRECTSOUNDBUFFER lpDSBPress;
	int soundgetfocus;
	int soundpress;

	ButtonItem();
	~ButtonItem();
	BOOL Load(LPSTR fnormal,LPSTR fpressed,LPSTR ffocused,LPSTR fdeactivated,BOOL autocolorkey,LPDIRECTDRAW lpDD=NULL);
	virtual void Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y);
	virtual void Update(UINT dtime);
	virtual void OnPress(int x,int y);
	BOOL LoadSound(LPSTR fpress,LPSTR fgetfocus);
	virtual void RestoreSurfaces();

private:
	void OnGetFocus();
	BitmapItem normal;
	BitmapItem focused;
	BitmapItem pressed;
	BitmapItem deactivated;
};

#endif