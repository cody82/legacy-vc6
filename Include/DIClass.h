#ifndef __DIRECTINPUTCLASSES
#define __DIRECTINPUTCLASSES
#include <dinput.h>
//link: dinput.lib, dxguid.lib

class DIKeyboard
{
public:
	LPDIRECTINPUTDEVICE  lpDIDevice;
	char buffer[256];

	DIKeyboard::DIKeyboard();
	DIKeyboard::~DIKeyboard();
	BOOL Initialize(LPDIRECTINPUT lpDI, HWND hwnd);
	BOOL UpdateKeyboard();
	BOOL GetKeyState(int dikey);
};

class DIMouse
{
public:
	LPDIRECTINPUTDEVICE lpDIDevice;
	DIMOUSESTATE ms;
	POINT offset;
	POINT screen;
	int speed;

	DIMouse::DIMouse();
	DIMouse::~DIMouse();
	BOOL Initialize(LPDIRECTINPUT lpDI, HWND hwnd);
	BOOL Update();
	POINT GetPos();
	BOOL ButtonPressed(UINT n);
};

#endif