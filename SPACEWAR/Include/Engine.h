#ifndef __ENGINE
#define __ENGINE
#include <windowsx.h>
#include <windows.h>
//#include "definitions.h"
#include <mmsystem.h>
#include <dsound.h>
#include <ddraw.h>
#include "sprite.h"
#include <math.h>
#include <stdio.h>
#include "ddutil.h"
#include "profiles.h"
#include "int2str.h"
#include "dsutil3d.h"
#include <fstream>
//#define DIRECTINPUT_VERSION 0x0300
#include <dinput.h>
#include "diclass.h"
#include "dsplayer.h"
#include "event.h"
#include "cpakfile.h"

//link:ddraw.lib, dsound.lib, dinput.lib
class energybar;

class BaseItem;
class Sprite2;
struct MAPFILESTRUCT
{
	char bitmapfile[64];
	BOOL passable;
};

typedef void (*DESTROYPROC)(Sprite2*);
//typedef void (*WMPROC)(UINT message,WPARAM wparam,LPARAM lparam);
typedef void (*VOIDPROC)();
typedef void (*COLLISIONPROC)(Sprite2*,Sprite2*);
typedef void (*FIREPROC)(Sprite2*,int);
typedef void (*ITEMPROC)(BaseItem*);
class Engine2
#define MAXSPRITES 400
#define MAXPROTOTYPES 100
#define WNDCLASSNAME "engine"
#define WNDTITLE "Engine"
#define MAXITEMS 50
#define EXTENDEDSCREENRANGE 500
#define MAPSIZE 64
#define FIELDSIZE 64

#define E_SFX_VOLUME -2500
#define E_SFX_MINVOLUME -2500

#define MAXEVENTS 10
{
friend Sprite2;
public:
	BOOL MakeScreenShot();
	BOOL LoadMap(char *file);
	BOOL RenderMap(LPDIRECTDRAWSURFACE3 lpDDS);

struct FIELD
{
	LPDIRECTDRAWSURFACE3 lpDDS;
	BOOL passable;
	char bitmapfile[64];
} Map[MAPSIZE][MAPSIZE];
	typedef struct
	{
		float x;
		float y;
	}VECTOR;

	CPackFile *cpf;

	VECTOR ScreenPos;
	VECTOR ScrollSpeed;

	BOOL drawcollisionmaps;

	HWND                hwnd;
	DESTROYPROC destroyproc;
	VOIDPROC updateproc;
	VOIDPROC preflipproc;

	DESTROYPROC shielddownproc;
	DESTROYPROC hullcriticalproc;
	DESTROYPROC respawnproc;
	COLLISIONPROC collisionproc;
	FIREPROC fireproc;
	ITEMPROC itemclickproc;
//	WMPROC wmproc;
	UINT frametime;
	
	Sprite2 *prototypes[MAXPROTOTYPES];
	Sprite2 *sprites[MAXSPRITES];
	Sprite2 *cursor;
	//int SpriteStack[MAXSPRITES];
	//int SpriteStackPointer;
	BaseItem *items[MAXITEMS];
	Event *events[MAXEVENTS];

	
	//LPDIRECTSOUND lpDirectSound;
	IDirectInput8 *lpDirectInput;

	DSPlayer soundsys;

	LPDIRECTDRAW lpDD;
	//LPDIRECTDRAW lpDD2;
	LPDIRECTDRAWSURFACE3 lpDDSBackGround;
	LPDIRECTDRAWSURFACE3 lpDDSBackBuffer;
	LPDIRECTDRAWSURFACE3 lpDDSPrimary;
	LPDIRECTDRAWCLIPPER lpDDClip;
	
	BOOL fullscreen;
	BOOL pause;
	BOOL initialized;
//	BOOL prototypesloaded;
//	BOOL hitdetection;
	BOOL bActive;
	BOOL showinfo;
	UINT screenheight;
	UINT screenwidth;
	UINT framenumber;
	int currentnumsprites;
	int currentnumitems;
	int currentnumevents;
	int fps;
	UINT tplastupdate;
	UINT tnow;
	UINT totalpausetime;
	UINT starttime;
	BOOL deleteproc;
	UINT tppauseon;
	float gravity;
	float gamespeed;


	char errormessage[64];

	DIKeyboard keyboard;
	DIMouse mouse;

	int Start();
	Engine2();
	~Engine2();
	BOOL Initialize(HINSTANCE hInstance,int sw,
		int sh,int bpp,BOOL fs,int backbuffers,WNDPROC wndproc,BOOL use2ndDisplaydevice=FALSE);
	void DetectHits();
	void DeleteSprite(int n);
	void Update();
	BOOL SpriteInScreen(Sprite2 *s);
	BOOL SpriteInExtendedScreen(Sprite2 *s);
	BOOL SpriteFullInScreen(Sprite2 *s);
	BOOL LoadPrototypes(char *filename);
	BOOL DuplicateSprite(Sprite2 *sn,Sprite2 *s);
	BOOL SpriteDetectHit(Sprite2 *s1,Sprite2 *s2);
	BOOL LoadSprite(Sprite2 *s,char *filename,char *spritename);
	void OnWM(UINT message,WPARAM wp,LPARAM lp);
	void SpawnSprite(Sprite2 *s);
	void SpawnSpriteInCircle(Sprite2 *s,float mx,float my,float r);
	void DrawAll();
	BOOL SetBackGround(char *filename);
	BOOL AddSprite(Sprite2 *s);
	void Engine2::Defrag();
	int Engine2::FindLastSprite();

#define ADD_NORMAL 0
#define ADD_LAST 1
#define ADD_FIRST 2
	BOOL AddSpriteEx(Sprite2 *s,UINT pos=0);
	BOOL AddItem(BaseItem *i);
	void OnSpriteDelete(Sprite2 *s);
	void OnSpriteDisable(Sprite2 *s);
	void OnSpriteShieldDown(Sprite2 *s);
	void OnSpriteHullCritical(Sprite2 *s);
	float SpriteGetDistance(Sprite2 *s1,Sprite2 *s2);
	float GetSpriteDistance(Sprite2 *s1,Sprite2 *s2);
	Sprite2 *GetNearestSprite(Sprite2 *s);
	Sprite2 *GetNearestActor(Sprite2 *s);
	Sprite2 *GetNearestBonus(Sprite2 *s);
	void Write2Surface(LPDIRECTDRAWSURFACE3 lpDDS,char *text,int x,int y);
	void ClearSurface(LPDIRECTDRAWSURFACE3 lpDDS);
	void PrintDDError(char *buffer,HRESULT ddrval);
	void PrintDSError(char *buffer,HRESULT ddrval);
	void PrintDIError(char *buffer,HRESULT ddrval);
	void OnError();
	BOOL CopyBitmap2Surface(LPDIRECTDRAWSURFACE3 lpDDS,char *file);
	int GetSpriteNumber(Sprite2* s);
	void DeleteItem(int n);
	int GetItemNumber(BaseItem *i);
	BOOL RestoreSurfaces();
	POINT GetGoodPosition(Sprite2 *s);
	float GetFireAngle(Sprite2 *attacker,Sprite2 *target);
	float GetApproachSpeed(Sprite2 *s1,Sprite2 *s2);
	float GetAngle(Sprite2 *source,Sprite2 *dest);
	void Pause(LPCSTR text=NULL);
	void BackupPrimarySurface(BOOL restore,BOOL release);
	void FullBlt(LPDIRECTDRAWSURFACE3 to,LPDIRECTDRAWSURFACE3 from);
	BOOL AdditiveBlt16(LPDIRECTDRAWSURFACE3 destsurface,LPDIRECTDRAWSURFACE3 srcsurface,RECT *destrect,RECT *srcrect);
	void OnItemClick(BaseItem *i);
	BOOL ScreenPointHitsItem(POINT p,BaseItem *bi,POINT *pwhere=NULL);
	POINT GetCenterPos(BaseItem *bi);
	BOOL MK2DetectHit(Sprite2 *s1,Sprite2 *s2);
	BOOL SpriteRectDetectHit(Sprite2 *s1,Sprite2 *s2);
	Event *CreateEvent(void(*eventproc)(),UINT interval,BOOL repeat,UINT t2raise);
	BOOL AddEvent(Event *event);
	void DeleteEvent(int i);
	BOOL ChangeDisplayMode(int x,int y,int bpp);

private:
	 char backgroundimagefile[64];
	 char pausetext[64];
};

extern GUID FAR *lpDisplayDevice;

#endif