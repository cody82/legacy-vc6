#ifndef __JOYSTICK
#define __JOYSTICK
#include <windows.h>
#include <mmsystem.h>

class joystick
{
#define DEADZONE 10000
public:
	JOYINFO joyinf;
	UINT joyid;
	BOOL enabled;

	joystick::joystick();
	joystick::~joystick();
	BOOL Init(UINT jid);
	UINT GetXpos();
	UINT GetYpos();
	UINT GetZpos();
	BOOL UpdateJoystick();
	BOOL GetButtonState(int n);
};
#endif