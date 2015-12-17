#ifndef __C3DENGINE_H
#define __C3DENGINE_H

#define D3DE_WNDTITLE "3DEngine"
#define D3DE_WNDCLASS "3DEngine"

#include <windows.h>
#include <ddraw.h>
#include <mmsystem.h>
#include <stdio.h>

#include "matrix.h"
#include "texture.h"
#include "vertex.h"

struct VECTOR3D
{
	float x;
	float y;
	float z;
};
class C3DEngine;

#include "3dobject.h"

class C3DEngine
{
public:
	C3DEngine();
	~C3DEngine();
	BOOL Initialize(int res_x,int res_y,int nBuffers,int bpp,WNDPROC wndproc,HINSTANCE hInst,BOOL fullscreen);
	void Update();
	void Shutdown();
	void Start();
	void OnWM(UINT message, WPARAM wParam, LPARAM lParam);

	HWND hWnd;
	BOOL bActive;
	float FPS;
	BOOL bShowStats;

	C3DObject *pFirstObject;

	DWORD tNow;
	
	LPDIRECTDRAW DirectDraw;
	LPDIRECTDRAWSURFACE FrontBuffer;
	LPDIRECTDRAWSURFACE BackBuffer;
	LPDIRECTDRAWSURFACE ZBuffer;
	
	LPDIRECT3D2 Direct3D;
	LPDIRECT3DDEVICE2 Device;
	LPDIRECT3DVIEWPORT2 Viewport;
	
	MATRIX World;
	MATRIX View;
	MATRIX Projection;
	TEXTURE tex;

};
#endif