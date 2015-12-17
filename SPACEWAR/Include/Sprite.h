#ifndef __SPRITE
#define __SPRITE
#include "ddutil.h"
#include <math.h>
#include "dsutil3d.h"
#include "ddraw.h"
#include "dsound.h"
#include "int2str.h"
//#include "definitions.h"
#include <stdio.h>
#include "engine.h"
#include "bitbool.h"
#include "bmputil.h"
//#include "ddalpha.h"

	typedef struct
	{
		float x;
		float y;
	}VECTOR;

class Engine2;

class BaseItem
{
public:
	Engine2 *e;
	VECTOR position;
	POINT size;
	BOOL enabled;
	BOOL noscroll;

	BOOL bfocused;
	POINT focpos;

	BaseItem::BaseItem();
	virtual BaseItem::~BaseItem();
	virtual void BaseItem::Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y);
	virtual void BaseItem::Update(UINT dtime);
	virtual void OnPress(int x,int y);
	virtual void RestoreSurfaces();

};
class Sprite2;

class energybar : public BaseItem
{
#define VERTICAL 1
#define HORIZONTAL 2
private:
	byte backcolor[3];
	byte forecolor[3];
public:
	int maxvalue;
	int currentvalue;
	int orientation;
	BOOL inertia;
	int inertiavalue;
	POINT size;
	Sprite2 *attach;
	POINT attachpos;
	int *intptr;
	float *floatptr;

	energybar::energybar();
	void energybar::SetBackColor(byte r,byte g,byte b);
	void energybar::SetForeColor(byte r,byte g,byte b);
	energybar::~energybar();
	virtual void Draw(LPDIRECTDRAWSURFACE lpDDS,int x,int y);
	virtual void Update(UINT dtime);
};

class Text3 : public BaseItem
{
public:
	int *intptr;
	float *floatptr;
	char *strptr;
	char buffer[64];
	int color[3];
	Sprite2 *attach;
	POINT attachpos;
	UINT tpdelete;
	BOOL truncatedecimals;

	Text3::Text3();
	virtual Text3::~Text3();
	virtual void Text3::Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y);
	virtual void Text3::Update(UINT dtime);
	void Text3::SetTxtColor(int r,int g,int b);

};

class Text4 : public BaseItem
{
public:
	Text4::Text4();
	virtual Text4::~Text4();
	virtual void Text4::Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y);
	virtual void Text4::Update(UINT dtime);
	void Text4::SetTxtColor(int r,int g,int b);

	byte color[3];
//	POINT size;
	VECTOR speed;
	char buffer[64*1024];
	char *strptr;
	UINT tplastupdate;

};

class Sprite2
{
#define SPRITETYPE_NORMAL 1
#define SPRITETYPE_BONUS 2
#define SPRITETYPE_EXPLOSION 3
#define SPRITETYPE_CPU 4
#define SPRITETYPE_HUMAN 5
//#define SPRITETYPE_HOMING 6

#define SHIELDDAMAGE 5
#define SHIELDTIME 500

#define FRAMETYPE_ANIMATION 1
#define FRAMETYPE_DIRECTION 2

//#define ANIMFRAMETIME 40
//#define EXPLOFRAMETIME 40

#define PI 3.141592653589793f

#define RELEASESTAYTIME 10000

#define DEBRISLIFETIME 5000
#define DEBRISTIME2HITDETECT 500
#define DEBRISSPEEDDIVISOR 3
#define DEBRISMINSPEED 80
#define DEBRISLIFETIMEFLUCTUATION 1000

#define SMOKEDELAY 120
#define SMOKEHITPOINTDIVISOR 2

#define AI_FIRE 1
#define AI_ATTACK 2
#define AI_MOVE 3
#define AI_SMARTFIRE 4

#define LOAD_TO_SYSMEM
	
//(*DESTROYPROC)(Sprite2*);
	typedef struct
	{
		UINT aimode;
		UINT lastaimode;
		POINT dest;
		int destradius;
		BOOL destvalid;
		int tcurrentmode;
		BOOL selfchangemode;
		Sprite2 *cputarget;
		UINT tstayinmode;
	}cpucontroldata;
friend Engine2;
public:
	LPDIRECTDRAWSURFACE3 lpDDSFrames[100];
	//LPDIRECTSOUNDBUFFER lpDSBSound;

	//Neue Kollisionserkennung (NYI)
	CBitBool collide[100];
	BOOL mk2collide;
	//byte collide2[100][64*64];

	int soundnr;

	POINT size;

	UINT type;

	VECTOR position;
	VECTOR speed;

	BOOL canbehit;
	BOOL canhit;
	BOOL enabled;
	BOOL deleteoutscreen;
	BOOL deletedisabled;
	BOOL deleteoutexscreen;
	BOOL disableoutexscreen;
	BOOL disableanimcomplete;
	BOOL bouncing;
	BOOL smoking;
	BOOL receivebonus;
	UINT ndebris;
	BOOL anglevdep;
	UINT frametype;
	UINT currentframe;
	UINT nframes;
	UINT ammo;
	BOOL homing;
	int launchlifetime;
//	float hitdamagedecreasespeed;
	BOOL centerfire;
	int centerweapondisty;
	BOOL additive;
	UINT animfps;
	BOOL gravdep;

	float damagemultiplicator;
	UINT tdamagemulti;

	float angle;
	float currentacceleration;
	float currentturnspeed;
	float maxspeed;

	float maxshieldstrenght;
	float shieldloadspeed;
	float shieldstrenght;
	float maxenergy;
	float energyloadspeed;
	float energy;
	float maxhitpoints;
	float hitpoints;
	float maxacceleration;
	float mass;
	float collisionrange;
	float hitdamage;
	float launchspeed;
	float turnspeed;
	float bouncestrenght;
	float hitforce;
	float hitforcemodifier;
	VECTOR weapondist;
	UINT nlaunch;
	BOOL indestructible;

	Sprite2 *staticshield;
	Sprite2 *explosion;
	Sprite2 *weapon;
	Sprite2 *defaultweapon;
	Sprite2 *smoke;
	Sprite2 *debris;

	Sprite2 *attacker;//should be killer
	Sprite2 *target;
	Sprite2 *launchedfrom;
	Sprite2 *friendsprite;
	Sprite2 *release;
	
	Sprite2 *special;
	UINT tlastspecial;//Zeit seit letztem Special-Einsatz in ms
	UINT tspecialdelay;
	void (*specialproc)(Sprite2*);
	UINT specialtype;

	UINT tdisabled;//Zeit seit Deactiviert in ms
	UINT tlastfire;//Zeit seit letztem Schuss in ms
//	UINT tplastupdate;
	UINT tlastsmoke;//Zeit seit letztes Smoke-Sprite gemacht worden ist in ms
	//UINT tplastframechange;
	UINT tframechange;//Zeit seit der letzte Frame gewechselt worden ist in ms
	UINT trespawn;//Konstante Respawnzeit in ms
	UINT tfiredelay;//Konstante Nachladezeit in ms
	int tdisable;//Zeit bis deactivieren in ms
	int tenablehitdetection;//Zeit bis Kollisionserkennung eingeschaltet wird in ms
	UINT tminlife;//Mindestalter, vorher wirds nicht einfach deativiert wenn auﬂerhald des Bildschirms ist [ms]
	UINT age;//Zeit seit aktivierung in ms, nicht ‰ndern

	cpucontroldata cpu;
	char bitmapfile[64];

	Engine2 *e;

	BOOL swing;//Schwingt: ja/nein
	float swingangle;//Schwingungswinkel relativ zum Normal-Winkel
	int swingtime;//Schwing-Periodenzeit in ms
	int tlastswingchange;//Zeit seit das letzte Mal die Schwingphase ge‰ndert worden ist
							//-1 wenns noch nicht Schwingt
	int currentswing;// 1/-1, Schwingphase
	float swingacceleration;//Beschleunigung der Schwingung

	Sprite2();
	~Sprite2();
	BOOL Initialize(LPDIRECTDRAW lpDD,HBITMAP hbm,UINT w,UINT h,UINT numframes,BOOL autocolorkey);
	BOOL InitWithSurfaceOfSprite(Sprite2 *s);
	BOOL Initialize2(LPDIRECTDRAW lpDD,char *bmfile,BOOL autocolorkey);
	BOOL Update(int dtime);
	BOOL Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y);
	void OnCollision(Sprite2 *s);
	void Disable();
	void Launch(Sprite2 *s,float speed,int shiftx,int shifty);
	void Fire(UINT n);
	void ChangeHitpoints(float d);
	void SetFrame(int dtime);
	float GetVAngle();
	float GetSpeed();
	void Special();
	BOOL InitMK2Collisions(LPSTR pbmfile,HBITMAP hbm=NULL);
	BOOL GetMK2Collision(int x,int y);
	BOOL DrawMK2Collision(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y);

private:
	BOOL UpdateExplosion(int dtime);
	BOOL UpdateNormal(int dtime);
	BOOL UpdateHuman(int dtime);
	BOOL UpdateCpu(int dtime);
	BOOL UpdateBonus(int dtime);
	void Turn(float degs);
	void Accelerate(float dir,int dtime);
	void OnCollisionNormal(Sprite2 *s);
	void OnCollisionBonus(Sprite2 *s);
	int lr;
	char spritename[64];
	char soundfile[64];

};

#endif