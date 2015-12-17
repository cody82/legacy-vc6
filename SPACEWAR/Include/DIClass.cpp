#include "diclass.h"

BOOL DIKeyboard::Initialize(IDirectInput8 *lpDI, HWND hwnd)
{
	HRESULT hr;
    
	hr = lpDI->CreateDevice(GUID_SysKeyboard, &lpDIDevice, NULL); 
    if FAILED(hr)
	{
		return FALSE;
	}
	
    hr = lpDIDevice->SetDataFormat(&c_dfDIKeyboard);     
	if FAILED(hr)     
	{
		return FALSE;
	}

    hr = lpDIDevice->SetCooperativeLevel(hwnd,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
    if FAILED(hr)
	{
		return FALSE; 
	}
	
	hr = lpDIDevice->Acquire(); 
    if FAILED(hr)     
	{
		return FALSE;
	}

	return TRUE;
}

BOOL DIKeyboard::UpdateKeyboard()
{
	if(!lpDIDevice)return(FALSE);
	HRESULT hr;
	
	hr = lpDIDevice->GetDeviceState(sizeof(buffer),(LPVOID)&buffer); 
    if FAILED(hr)     
	{
		hr = lpDIDevice->Acquire();
		if(FAILED(hr))
		{
			return FALSE;
		}
		hr = lpDIDevice->GetDeviceState(sizeof(buffer),(LPVOID)&buffer);
		if(FAILED(hr))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL DIKeyboard::GetKeyState(int dikey)
{
//#define KEYDOWN(name,key) (name[key] & 0x80)
	
	return (buffer[dikey] & 0x80);
}

DIKeyboard::DIKeyboard()
{
}

DIKeyboard::~DIKeyboard()
{
}

DIMouse::DIMouse()
{
	memset(&ms,0,sizeof(ms));
	lpDIDevice=NULL;
	offset.x=0;
	offset.y=0;
}

DIMouse::~DIMouse()
{
}

BOOL DIMouse::Initialize(IDirectInput8 *lpDI,HWND hwnd)
{
	HRESULT hr;
	DIPROPDWORD pdw;

	hr = lpDI->CreateDevice(GUID_SysMouse, &lpDIDevice, NULL);
	if (FAILED(hr)) 
	{
		return FALSE;
	}

	hr = lpDIDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) 
	{
		return FALSE;
	}

	hr = lpDIDevice->SetCooperativeLevel(hwnd,DISCL_NONEXCLUSIVE | DISCL_FOREGROUND); 
	if (FAILED(hr)) 
	{
		return FALSE;
	}

	memset(&pdw,0,sizeof(pdw));
	pdw.diph.dwSize=sizeof(pdw);
	pdw.diph.dwHeaderSize=sizeof(pdw.diph);
	pdw.dwData=DIPROPAXISMODE_ABS;
	pdw.diph.dwHow=DIPH_DEVICE;

	hr=lpDIDevice->SetProperty(DIPROP_AXISMODE,&pdw.diph);
	if(FAILED(hr))
	{
		return FALSE;
	}

		hr=lpDIDevice->Acquire();
		if(FAILED(hr))
		{
			//return FALSE;
		}
		hr=lpDIDevice->GetDeviceState(sizeof(ms),&ms);
		if(FAILED(hr))
		{
			return FALSE;
		}

	offset.x=ms.lX;
	offset.y=ms.lY;

	screen.x=GetSystemMetrics(SM_CXSCREEN);
	screen.y=GetSystemMetrics(SM_CYSCREEN);

	speed=2;

	return TRUE;
}

POINT DIMouse::GetPos()
{
	POINT p;

	if(ms.lX<offset.x)
	{
		offset.x=ms.lX;
	}
	else if(ms.lX>offset.x+screen.x/speed)
	{
		offset.x=ms.lX-screen.x/speed;
	}
	
	if(ms.lY<offset.y)
	{
		offset.y=ms.lY;
	}
	else if(ms.lY>offset.y+screen.y/speed)
	{
		offset.y=ms.lY-screen.y/speed;
	}

	p.x=speed*(ms.lX-offset.x);
	p.y=speed*(ms.lY-offset.y);

/*	if(p.x<0)
	{
		offset.x=-p.x-1;
		p.x=0;
	}
	else if(p.y>screen.x)
	{
		
	}*/
	return p;
}

BOOL DIMouse::ButtonPressed(UINT n)
{
	if(n>4)return FALSE;

	return ms.rgbButtons[n]!=0;
}

BOOL DIMouse::Update()
{
	HRESULT hr;

	hr=lpDIDevice->GetDeviceState(sizeof(ms),&ms);
	if(FAILED(hr))
	{
		hr=lpDIDevice->Acquire();
		if(FAILED(hr))
		{
			return FALSE;
		}
		hr=lpDIDevice->GetDeviceState(sizeof(ms),&ms);
		if(FAILED(hr))
		{
			return FALSE;
		}
	}

	return TRUE;
}

