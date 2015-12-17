#ifndef __DIRECTINPUTCLASSES
#define __DIRECTINPUTCLASSES
//#define DIRECTINPUT_VERSION 0x0300
#include <dinput.h>
//link: dinput.lib, dxguid.lib

class DIKeyboard
{
public:
	IDirectInputDevice8*  lpDIDevice;
	char buffer[256];

	DIKeyboard::DIKeyboard();
	DIKeyboard::~DIKeyboard();
	BOOL Initialize(IDirectInput8 *lpDI, HWND hwnd);
	BOOL UpdateKeyboard();
	BOOL GetKeyState(int dikey);
};

class DIMouse
{
public:
	IDirectInputDevice8* lpDIDevice;
	DIMOUSESTATE ms;
	POINT offset;
	POINT screen;
	int speed;

	DIMouse::DIMouse();
	DIMouse::~DIMouse();
	BOOL Initialize(IDirectInput8 *lpDI, HWND hwnd);
	BOOL Update();
	POINT GetPos();
	BOOL ButtonPressed(UINT n);
};

#endif