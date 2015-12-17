#include "joystick.h"

	joystick::joystick()
	{
		enabled=FALSE;
	}

	joystick::~joystick()
	{
	}

	BOOL joystick::Init(UINT jid)
	{
		if (!joyGetNumDevs())
		{
			return FALSE;
		}
		joyid=jid;
		if(joyGetPos(joyid,&joyinf)!=JOYERR_NOERROR)return(FALSE);
		enabled=TRUE;
		return(TRUE);
	}

	UINT joystick::GetXpos()
	{
		return(joyinf.wXpos);
	}

	UINT joystick::GetYpos()
	{
		return(joyinf.wYpos);
	}
	
	UINT joystick::GetZpos()
	{
		return(joyinf.wZpos);
	}

	BOOL joystick::UpdateJoystick()
	{
		if(joyGetPos(joyid,&joyinf)!=JOYERR_NOERROR)return(FALSE);
		return(TRUE);
	}

	BOOL joystick::GetButtonState(int n)
	{
		if(n==1 && (joyinf.wButtons & JOY_BUTTON1))return(TRUE);
		if(n==2 && (joyinf.wButtons & JOY_BUTTON2))return(TRUE);
		if(n==3 && (joyinf.wButtons & JOY_BUTTON3))return(TRUE);
		if(n==4 && (joyinf.wButtons & JOY_BUTTON4))return(TRUE);
		return(FALSE);
	}
