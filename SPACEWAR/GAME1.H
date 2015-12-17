#ifndef __GAME1_H
#define __GAME1_H

#include "include\include.h"

#include "control.h"
#include "gamedata.h"
#include "specials.h"
#include "events.h"
#include "onx.h"
#include "buttons.h"

void updateFrame();
//int random(int,int);
void ProcessKeyboardEx(Sprite2 *s,kbcontrol *kbc);
void ProcessControllersEx(Sprite2 *s,joystick *j);
void Scrolling(BOOL exponential);
void OnPreFlip();
void ProcessMouse(Sprite2 *s);

#define INGAMETITLE "EXTREME SPACEWAR v2.40"
#define BORGNUMBER 15
#define RESPAWNTIME 4000
#define BORGFRAGS 5
#define FRAGSHOWTIME 4000
//#define MAXLINES 5
//#define LINESTAYTIME 3000
#define CURSORNR 7


//Global Gamedata
extern LPDIRECTSOUNDBUFFER lpDirectSoundBuffer;
extern LPDIRECTSOUNDBUFFER lpDSBdeath;
extern LPDIRECTSOUNDBUFFER lpDSBCheat;

//main sprites
extern Sprite2 *PlayerSprites[4];

//Buttons
extern ButtonItem buttons[4];
//Window
extern WndItem window[4];

extern BitmapItem bitmap;

//Borg
extern Sprite2 *borgcube;
extern int borgarrivesound;

//game engine
extern Engine2 mainengine;

//Music
extern int music;

//Sounds
extern int death;
extern int shielddown;
extern int hullcritical;

//CD Player
extern CDPlayer *cdplayer;

//Prototypes:
extern Sprite2 PlayerPrototypes[4];

//Textdisplays
extern Text3 fragsdisplays[4];
extern Text3 hitpointdisplays[4];
extern Text3 shielddisplays[4];
extern Text3 namedisplays[4];
extern Text3 energydisplays[4];
extern energybar bars[4];

extern CmdLineItem cmdline;

//Events
extern Event *borg;
extern Event *asteroids;	

extern CGameData gamedata;



#endif