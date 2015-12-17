#include "buttonitem.h"

ButtonItem::ButtonItem()
{
	position.x=0;
	position.y=0;
	noscroll=TRUE;
	tpbuttonpressed=0;
	pressproc=NULL;
	state=NORMAL;
	focusedlastupdate=FALSE;
	soundpress=-1;
	soundgetfocus=-1;
}

ButtonItem::~ButtonItem()
{
}

void ButtonItem::OnGetFocus()
{
	//if(lpDSBGetFocus)lpDSBGetFocus->Play(0,0,0);
	if(soundgetfocus>=0)e->soundsys.Play(soundgetfocus,FALSE);
}
	
void ButtonItem::RestoreSurfaces()
{
	normal.RestoreSurfaces();
	pressed.RestoreSurfaces();
	focused.RestoreSurfaces();
	deactivated.RestoreSurfaces();
}

void ButtonItem::OnPress(int x,int y)
{
	state=PRESSED;
	if(soundpress>=0)e->soundsys.Play(soundpress,FALSE);
	tpbuttonpressed=e->tnow+e->totalpausetime;
	if(pressproc)pressproc();
}
	
BOOL ButtonItem::LoadSound(LPSTR fpress,LPSTR fgetfocus)
{
	//if(lpDSBGetFocus)lpDSBGetFocus->Release();
	//lpDSBGetFocus=DSLoadSoundBuffer(e->soundsys.lpDS,fgetfocus);
	
	//if(lpDSBPress)lpDSBPress->Release();
	//lpDSBPress=DSLoadSoundBuffer(e->soundsys.lpDS,fpress);
	
	//if(!(lpDSBGetFocus&&lpDSBPress))return TRUE;

	soundpress=e->soundsys.GetSoundNr(fpress);
	soundgetfocus=e->soundsys.GetSoundNr(fgetfocus);

	return TRUE;
}

void ButtonItem::Update(UINT dtime)
{
	if(tpbuttonpressed&&(e->tnow+e->totalpausetime)-tpbuttonpressed>BUTTONPRESSTIME)
	{
		tpbuttonpressed=0;
		if(bfocused)
		{
			state=FOCUSED;
			focusedlastupdate=TRUE;
		}
		else
			state=NORMAL;
	}
	if(bfocused&&state==NORMAL)state=FOCUSED;
	if(!bfocused&&state==FOCUSED)state=NORMAL;
	if(state==FOCUSED&&!focusedlastupdate)
		OnGetFocus();
	focusedlastupdate=(state==FOCUSED);
}

BOOL ButtonItem::Load(LPSTR fnormal,
					  LPSTR fpressed,
					  LPSTR ffocused,
					  LPSTR fdeactivated,
					  BOOL autocolorkey,
					  LPDIRECTDRAW lpDD/*=NULL*/)
{
	BOOL b;

	normal.e=e;
	pressed.e=e;
	focused.e=e;
	deactivated.e=e;

	b=normal.Load(fnormal,autocolorkey,lpDD);
	if(!b)return FALSE;
	normal.enabled=TRUE;

	if(fpressed)
	{
		b=pressed.Load(fpressed,autocolorkey,lpDD);
		if(!b)return FALSE;
		pressed.enabled=TRUE;
	}

	if(ffocused)
	{
		b=focused.Load(ffocused,autocolorkey,lpDD);
		if(!b)return FALSE;
		focused.enabled=TRUE;
	}

	if(fdeactivated)
	{
		b=deactivated.Load(fdeactivated,autocolorkey,lpDD);
		if(!b)return FALSE;
		deactivated.enabled=TRUE;
	}

	size=normal.size;

	enabled=TRUE;

	return TRUE;
}

void ButtonItem::Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y)
{
	switch(state)
	{
	case NORMAL:
		normal.Draw(lpDDS,x,y);
		break;
	case PRESSED:
		pressed.Draw(lpDDS,x,y);
		break;
	case FOCUSED:
		focused.Draw(lpDDS,x,y);
		break;
	case DEACTIVATED:
		deactivated.Draw(lpDDS,x,y);
		break;
	}
}
