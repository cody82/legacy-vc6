#ifndef __GAMEDATA_H
#define __GAMEDATA_H

class CGameData;

#include "game1.h"
#include "control.h"

typedef struct
	{
		int frags[4];	
		int kills[4][4];
		int deaths[4];
		int suicides[4];
		int shots[4];
		int hits[4];
	} STATS;

class CGameData
{
public:
	char names[4][64];
	STATS stats;

#define BORGSTATE_ARRIVE 0
#define BORGSTATE_GOWARP 1
	UINT borgstate;
	int asteroidspawndistance;
	int asteroidspawnradius;
	int asteroidcount;
	int asteroidspeed;
	int asteroidminlifetime;

	UINT tpexit;

	char **deathmessages1;
	char **deathmessages2;
	int numcomments;
	BOOL usejoysticks;
	BOOL quitonY;
	char commandline[64];
	int players;
	int showfrags;
	BOOL infonships;
	UINT playercontrols[4];
		#define KEYBOARD1 1
		#define KEYBOARD2 2
		#define JOYSTICK1 4
		#define JOYSTICK2 8
		#define CPU 16
		#define MOUSEKB1 32
		#define MOUSEKB2 64
		#define KEYBOARD3 128
		#define KEYBOARD4 256
		#define MOUSEKB3 1024
		#define MOUSEKB4 2048

	BOOL exponentialscrolling;
	float scrollspeed;
	float scrollacceleration;
	int startcountdown;
	kbcontrol p1control,p2control,p3control,p4control;
	joystick joystick1,joystick2;

	CGameData();
	BOOL SaveStats(char *filename);
	BOOL loaddeathmessages();
	int GetNumHumanPlayers();
	int GetNumControllers();
	~CGameData();
	
};



#endif