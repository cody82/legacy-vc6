//#define WIN32_LEAN_AND_MEAN
#include "game1.h"

//Global Gamedata
LPDIRECTSOUNDBUFFER lpDirectSoundBuffer;
LPDIRECTSOUNDBUFFER lpDSBdeath;
LPDIRECTSOUNDBUFFER lpDSBCheat;

//main sprites
Sprite2 *PlayerSprites[4]={NULL,NULL,NULL,NULL};

//Buttons
ButtonItem buttons[4];
//Window
WndItem window[4];

BitmapItem bitmap;

//Borg
Sprite2 *borgcube=new Sprite2;
int borgarrivesound;

//game engine
Engine2 mainengine;

//Music
int music;

//Sounds
int death;
int shielddown;
int hullcritical;

//CD Player
CDPlayer *cdplayer=NULL;

//Prototypes:
Sprite2 PlayerPrototypes[4];

//Textdisplays
Text3 fragsdisplays[4];
Text3 hitpointdisplays[4];
Text3 shielddisplays[4];
Text3 namedisplays[4];
Text3 energydisplays[4];
energybar bars[4];

CmdLineItem cmdline;

//Events
Event *borg;
Event *asteroids;	

CGameData gamedata;



long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
//	int i;
	mainengine.OnWM(message,wParam,lParam);

    switch( message )
    {
    case WM_ACTIVATEAPP:
    case WM_ACTIVATE:
		break;
    case WM_TIMER:
		break;
	case WM_CHAR:
		break;
	case MM_MCINOTIFY:
		if(cdplayer)cdplayer->OnWMNotify(wParam,lParam);
		break;
    case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_ESCAPE:
			mainengine.Pause("");
			window[0].enabled=mainengine.pause;
			break;
		case VK_F1:
			gamedata.showfrags=FRAGSHOWTIME;
			break;
		case VK_F2:
			gamedata.infonships=!gamedata.infonships;
			break;
		case VK_F3:
			mainengine.MakeScreenShot();
			break;
		case VK_F4:
			//mainengine.ChangeDisplayMode(1024,768,32);
			//mainengine.RestoreSurfaces();
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		break;
    case WM_PAINT:
		break;
    case WM_DESTROY:
		if(cdplayer)delete cdplayer;
		break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
} /* WindowProc */

void makemapfile(char *file)
{
	MAPFILESTRUCT map;
	HANDLE hfile;
	strcpy(map.bitmapfile,"maptest.bmp");
	map.passable=TRUE;
	unsigned long ul;
	
	int i;
	hfile=CreateFile(file,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if(!hfile)return;

	for(i=0;i<MAPSIZE*MAPSIZE;++i)
	{
		WriteFile(hfile,(LPVOID)&map,sizeof(map),&ul,NULL);
	}
	CloseHandle(hfile);
}



/*
 * WinMain - initialization, message loop
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow)
{
	char tmpstr[64];
	int i,i2;
	Text3 *t;

	i=GetPrivateProfileIntCurrentDir("config.ini","game1","xres",640);
	i2=GetPrivateProfileIntCurrentDir("config.ini","game1","yres",480);

/*	BitBool bb;
	RECT rect;
	rect.left=0;
	rect.right=96;
	rect.top=0;
	rect.bottom=96;
	bb.NewFromPBM_asciiRect("alien\\alien001.pbm",rect,TRUE);*/
	if(!mainengine.Initialize(hInstance,i,i2,
		GetPrivateProfileIntCurrentDir("config.ini","game1","colordepth",16),
		!GetPrivateProfileIntCurrentDir("config.ini","game1","window",1),
		GetPrivateProfileIntCurrentDir("config.ini","game1","backbuffers",1),
		WindowProc,
		GetPrivateProfileIntCurrentDir("config.ini","game1","2nddisplaydevice",0)
		))
	{
		strcpy(mainengine.errormessage,"Engine could not be correctly initialized");
		mainengine.OnError();
	}

	//if(!mainengine.lpDD)mainengine.lpDD2=mainengine.lpDD;

	mainengine.soundsys.LoadSounds("sounds.ini");

	if(GetPrivateProfileStringCurrentDir("config.ini","game1","loadpicture",tmpstr,64))
	{
		if(stricmp(tmpstr,"NULL")!=0)
		{
			mainengine.CopyBitmap2Surface(mainengine.lpDDSPrimary,tmpstr);
		}
	}

	if(GetPrivateProfileStringCurrentDir("config.ini","game1","shielddownsound",tmpstr,64))
	{
		if(stricmp(tmpstr,"NULL")!=0&&mainengine.soundsys.lpDS)
		{
			shielddown=mainengine.soundsys.GetSoundNr(tmpstr);
//			mainengine.soundsys.soundtype[shielddown]=SOUNDTYPE_SPEECH;
		}
	}
	if(GetPrivateProfileStringCurrentDir("config.ini","game1","hullcriticalsound",tmpstr,64))
	{
		if(stricmp(tmpstr,"NULL")!=0&&mainengine.soundsys.lpDS)
		{
			hullcritical=mainengine.soundsys.GetSoundNr(tmpstr);		
//			mainengine.soundsys.soundtype[hullcritical]=SOUNDTYPE_SPEECH;
		}
	}

	if(GetPrivateProfileStringCurrentDir("config.ini","game1","backgroundimage",tmpstr,64))
	{
		if(stricmp(tmpstr,"NULL")!=0)
		{
			mainengine.SetBackGround(tmpstr);
		}
	}

	//collisionmaps
	if(GetPrivateProfileIntCurrentDir("config.ini","game1","drawcollisionmaps",0))
	{
		mainengine.drawcollisionmaps=TRUE;
	}

	mainengine.LoadPrototypes("prototypes.ini");
	
	//GameSpeed
	mainengine.gamespeed=(float)abs(GetPrivateProfileIntCurrentDir("config.ini","game1","gamespeed",100))/100;

	//Load music
	GetPrivateProfileStringCurrentDir("config.ini","game1","backgroundsound",tmpstr,64);
	if(stricmp(tmpstr,"NULL")!=0&&mainengine.soundsys.lpDS)
	{
		mainengine.FullBlt(mainengine.lpDDSBackBuffer,mainengine.lpDDSPrimary);
		mainengine.Write2Surface(mainengine.lpDDSPrimary,"Loading Music...",5,5);
		music=mainengine.soundsys.GetSoundNr(tmpstr);
		mainengine.soundsys.Play(music);
		mainengine.FullBlt(mainengine.lpDDSPrimary,mainengine.lpDDSBackBuffer);

	}
	//MP3!!!
/*	if(GetPrivateProfileStringCurrentDir("config.ini","game1","mp3",tmpstr,64))
	{
		if(stricmp(tmpstr,"NULL")!=0&&mainengine.soundsys.lpDS)
		{
			mainengine.soundsys.PlayMP3(tmpstr);
		}
	}
*/
	GetPrivateProfileStringCurrentDir("config.ini","game1","deathsound",tmpstr,64);
	if(stricmp(tmpstr,"NULL")!=0&&mainengine.soundsys.lpDS)
	{
		death=mainengine.soundsys.GetSoundNr(tmpstr);
	}

	//Initialize Players
	PlayerSprites[0]=new Sprite2;
	i=GetPrivateProfileIntCurrentDir("config.ini","game1","player1ship",-1);
	if(i>=0)
	{
		mainengine.DuplicateSprite(PlayerSprites[0],mainengine.prototypes[i]);
		mainengine.AddSpriteEx(PlayerSprites[0]);
	}
	if(gamedata.players>1)
	{
		PlayerSprites[1]=new Sprite2;
		i=GetPrivateProfileIntCurrentDir("config.ini","game1","player2ship",-1);
		if(i>=0)
		{
			mainengine.DuplicateSprite(PlayerSprites[1],mainengine.prototypes[i]);
			mainengine.AddSpriteEx(PlayerSprites[1]);
		}
		if(gamedata.players>2)
		{
			PlayerSprites[2]=new Sprite2;
			i=GetPrivateProfileIntCurrentDir("config.ini","game1","player3ship",-1);
			if(i>=0)
			{
				mainengine.DuplicateSprite(PlayerSprites[2],mainengine.prototypes[i]);
				mainengine.AddSpriteEx(PlayerSprites[2]);
			}
			if(gamedata.players>3)
			{
				PlayerSprites[3]=new Sprite2;
				i=GetPrivateProfileIntCurrentDir("config.ini","game1","player4ship",-1);
				if(i>=0)
				{
					mainengine.DuplicateSprite(PlayerSprites[3],mainengine.prototypes[i]);
					mainengine.AddSpriteEx(PlayerSprites[3]);
				}
			}
		}
	}
	
	//Specials
	for(i=0;i<gamedata.players;++i)
	{
		if(PlayerSprites[i]->specialtype>0)
			switch(PlayerSprites[i]->specialtype)
			{
				case SPECIAL_TELEPORT:
					PlayerSprites[i]->specialproc=SpecialRandomTeleport;
					break;
				case SPECIAL_TURRET:
					PlayerSprites[i]->specialproc=SpecialTurret;
					break;
				case SPECIAL_REARFIRE:
					PlayerSprites[i]->specialproc=SpecialRearFire;
					break;
				case SPECIAL_SELFDESTRUCT:
					PlayerSprites[i]->specialproc=SpecialSelfDestruct;
					break;
				case SPECIAL_SYSTEMOVERLOAD:
					PlayerSprites[i]->specialproc=SpecialSystemOverload;
					break;
				case SPECIAL_SUCKENERGY:
					PlayerSprites[i]->specialproc=SpecialSuckEnergy;
					break;
				case SPECIAL_MINE:
					PlayerSprites[i]->specialproc=SpecialMine;
					break;

			}
	}

	for(i=0;i<gamedata.players;++i)
	{
		//PlayerSprites[i]->ailevel=0;
		PlayerSprites[i]->trespawn=RESPAWNTIME;
		if(gamedata.playercontrols[i]==CPU)
		{
			PlayerSprites[i]->type=SPRITETYPE_CPU;
			PlayerSprites[i]->cpu.selfchangemode=TRUE;
		}
		else
			PlayerSprites[i]->type=SPRITETYPE_HUMAN;
		//PlayerSprites[i]->bouncerectrespawn=TRUE;
	}
	for(i=0;i<gamedata.players;++i)
	{
		memcpy(&PlayerPrototypes[i],PlayerSprites[i],sizeof(*PlayerSprites[i]));
	}
	for(i=0;i<gamedata.players;++i)
	{
		mainengine.SpawnSprite(PlayerSprites[i]);
	}
	
	//Add Bonus
	Sprite2 *tmp;
		for(i2=0;i2<MAXPROTOTYPES;++i2)
		{
			if(mainengine.prototypes[i2]&&mainengine.prototypes[i2]->type==SPRITETYPE_BONUS)
			{
				tmp=new Sprite2;
				mainengine.DuplicateSprite(tmp,mainengine.prototypes[i2]);
				mainengine.AddSpriteEx(tmp);
				tmp->position.x=(float)random(0,mainengine.screenwidth-(int)(tmp->size.x));
				tmp->position.y=(float)random(0,mainengine.screenheight-(int)(tmp->size.y));
				tmp->enabled=FALSE;
				tmp->tdisabled=0;
			}
		}

	//Displays
	fragsdisplays[0].position.x=150;
	fragsdisplays[0].position.y=50;
	fragsdisplays[1].position.x=150;
	fragsdisplays[1].position.y=80;
	fragsdisplays[2].position.x=150;
	fragsdisplays[2].position.y=110;
	fragsdisplays[3].position.x=150;
	fragsdisplays[3].position.y=140;

	for(i=0;i<gamedata.players;++i)mainengine.AddItem(&fragsdisplays[i]);

	for(i=0;i<gamedata.players;++i)
	{
		mainengine.AddItem(&hitpointdisplays[i]);
		hitpointdisplays[i].floatptr=&PlayerSprites[i]->hitpoints;
		hitpointdisplays[i].enabled=TRUE;
		hitpointdisplays[i].SetTxtColor(0,255,0);
	}
	for(i=0;i<gamedata.players;++i)
	{
		mainengine.AddItem(&shielddisplays[i]);
		shielddisplays[i].floatptr=&PlayerSprites[i]->shieldstrenght;
		shielddisplays[i].enabled=TRUE;
		shielddisplays[i].SetTxtColor(0,0,255);
	}
	for(i=0;i<gamedata.players;++i)
	{
		mainengine.AddItem(&energydisplays[i]);
		energydisplays[i].floatptr=&PlayerSprites[i]->energy;
		energydisplays[i].enabled=TRUE;
		energydisplays[i].SetTxtColor(255,255,0);
	}

	mainengine.AddItem(&namedisplays[0]);
	namedisplays[0].strptr=gamedata.names[0];
	namedisplays[0].position.x=10;
	namedisplays[0].position.y=50;
	
	if(gamedata.players>1)
	{
		mainengine.AddItem(&namedisplays[1]);
		namedisplays[1].strptr=gamedata.names[1];
		namedisplays[1].position.x=10;
		namedisplays[1].position.y=80;
	}
	
	if(gamedata.players>2)
	{
		mainengine.AddItem(&namedisplays[2]);
		namedisplays[2].strptr=gamedata.names[2];
		namedisplays[2].position.x=10;
		namedisplays[2].position.y=110;
	}
	
	if(gamedata.players>3)
	{
		mainengine.AddItem(&namedisplays[3]);
		namedisplays[3].strptr=gamedata.names[3];
		namedisplays[3].position.x=10;
		namedisplays[3].position.y=140;
	}

	for(i=0;i<4;++i)fragsdisplays[i].intptr=&gamedata.stats.frags[i];

	//Attach displays to Sprites
	for(i=0;i<gamedata.players;++i)
	{
		hitpointdisplays[i].attach=PlayerSprites[i];
		hitpointdisplays[i].attachpos.x=PlayerSprites[i]->size.x;
		shielddisplays[i].attach=PlayerSprites[i];
		shielddisplays[i].attachpos.x=PlayerSprites[i]->size.x;
		shielddisplays[i].attachpos.y=20;
		energydisplays[i].attach=PlayerSprites[i];
		energydisplays[i].attachpos.x=PlayerSprites[i]->size.x;
		energydisplays[i].attachpos.y=40;
		
		hitpointdisplays[i].noscroll=FALSE;
		shielddisplays[i].noscroll=FALSE;
		energydisplays[i].noscroll=FALSE;
	}
	
	//Borg part
	
	if(GetPrivateProfileIntCurrentDir("config.ini","game1","borgtime",-1)>0)
	{
		mainengine.DuplicateSprite(borgcube,mainengine.prototypes[BORGNUMBER]);
		mainengine.AddSpriteEx(borgcube);
		borgcube->deletedisabled=FALSE;
		borgcube->deleteoutscreen=FALSE;
		borgcube->enabled=FALSE;
		borgcube->cpu.aimode=AI_SMARTFIRE;
		borgcube->type=SPRITETYPE_CPU;
		if(mainengine.soundsys.lpDS)borgarrivesound=mainengine.soundsys.GetSoundNr("borg.wav");
		borg=mainengine.CreateEvent(BorgArrive,(UINT)GetPrivateProfileIntCurrentDir("config.ini","game1","borgtime",0),TRUE,(UINT)GetPrivateProfileIntCurrentDir("config.ini","game1","borgtime",0));
	}
	
	//Asteroids
	if(GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidinterval",-1)>0)
	{
		asteroids=mainengine.CreateEvent(AsteroidShower,GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidinterval",-1),TRUE,GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidinterval",-1));
	}

	//Check Controls
	if(gamedata.GetNumHumanPlayers()>gamedata.GetNumControllers())
	{
		strcpy(mainengine.errormessage,"Not enough controllers");
		mainengine.OnError();
	}

	//CD-Player
	i=GetPrivateProfileIntCurrentDir("config.ini","game1","playcdtrack",0);
	if(i>0)
	{
		cdplayer=new CDPlayer;
		cdplayer->Play(i,mainengine.hwnd);
	}

	mainengine.destroyproc=OnSpriteDestroy;

	//Message display
	mainengine.AddItem(&cmdline);
	cmdline.size.x=500;
	cmdline.size.y=100;
	cmdline.position.x=(float)mainengine.screenwidth/2-(float)cmdline.size.x/2;
	cmdline.position.y=0;
	cmdline.enabled=TRUE;
	cmdline.color[0]=255;
	cmdline.color[1]=0;
	cmdline.color[2]=0;
	cmdline.tlinedeleteinterval=3000;

	//Title
	t=new Text3;
	strcpy(t->buffer,INGAMETITLE);
	mainengine.AddItem(t);
	t->enabled=TRUE;
	t->position.y=0;
	t->position.x=0;

	mainengine.showinfo=GetPrivateProfileIntCurrentDir("config.ini","game1","showinformation",0);
	mainengine.updateproc=updateFrame;
	mainengine.shielddownproc=OnSpriteShieldDown;
	mainengine.hullcriticalproc=OnSpriteHullCritical;
	mainengine.respawnproc=OnSpriteRespawn;
	mainengine.collisionproc=OnSpriteCollision;
	mainengine.fireproc=OnSpriteFire;
	mainengine.preflipproc=OnPreFlip;
	mainengine.itemclickproc=OnItemClick;

	//Cursor
	if(GetPrivateProfileIntCurrentDir("config.ini","game1","cursor",0))
	{
		mainengine.cursor=new Sprite2;
		mainengine.DuplicateSprite(mainengine.cursor,mainengine.prototypes[CURSORNR]);
		mainengine.cursor->enabled=TRUE;
	}
	
	//Window&Buttons
	POINT p;
	mainengine.AddItem(&window[0]);
	window[0].size.x=300;
	window[0].size.y=400;
	p=mainengine.GetCenterPos(&window[0]);
	window[0].position.x=(float)p.x;
	window[0].position.y=(float)p.y;
	window[0].enabled=FALSE;

	window[0].AddItem(&buttons[0]);
	buttons[0].Load("bitmaps\\btn_resume001.bmp","bitmaps\\btn_resume003.bmp","bitmaps\\btn_resume002.bmp",NULL,FALSE);
	p=window[0].GetCenterPos(&buttons[0]);
	buttons[0].position.x=(float)p.x;
	buttons[0].position.y=100;
	buttons[0].pressproc=OnButtonResumeClick;
	buttons[0].LoadSound("sounds\\set_off2.wav","sounds\\beep-01.wav");

	window[0].AddItem(&buttons[1]);
	buttons[1].Load("bitmaps\\btn_restart001.bmp","bitmaps\\btn_restart003.bmp","bitmaps\\btn_restart002.bmp",NULL,FALSE);
	buttons[1].position.x=(float)p.x;
	buttons[1].position.y=100+32;
	buttons[1].pressproc=OnButtonRestartClick;
	buttons[1].LoadSound("sounds\\set_off2.wav","sounds\\beep-01.wav");

	window[0].AddItem(&buttons[2]);
	buttons[2].Load("bitmaps\\btn_options001.bmp","bitmaps\\btn_options003.bmp","bitmaps\\btn_options002.bmp",NULL,FALSE);
	buttons[2].position.x=(float)p.x;
	buttons[2].position.y=100+64;
	buttons[2].pressproc=OnButtonOptionsClick;
	buttons[2].LoadSound("sounds\\set_off2.wav","sounds\\beep-01.wav");

	window[0].AddItem(&buttons[3]);
	buttons[3].Load("bitmaps\\btn_exit001.bmp","bitmaps\\btn_exit003.bmp","bitmaps\\btn_exit002.bmp",NULL,FALSE);
	buttons[3].position.x=(float)p.x;
	buttons[3].position.y=100+96;
	buttons[3].pressproc=OnButtonExitClick;
	buttons[3].LoadSound("sounds\\set_off2.wav","sounds\\beep-01.wav");

	window[0].AddItem(&bitmap);
	p=window[0].GetCenterPos(&window[0]);
	bitmap.Load("bitmaps\\logo1.bmp",TRUE);
	bitmap.position.x=(float)p.x;
	bitmap.position.y=0;

	return(mainengine.Start());

} /* WinMain */

void updateFrame()
{
	int i,i2;
	int maxfrags,minfrags;
	int r,g,b;
	static int dist;

	//exit
	if(gamedata.tpexit&&timeGetTime()>=gamedata.tpexit)
	{
		gamedata.tpexit=0;
		PostQuitMessage(0);
	}

	if(mainengine.pause)return;

	//Fragdisplays
	gamedata.showfrags-=(mainengine.tnow-mainengine.tplastupdate);
	for(i=0;i<gamedata.players;++i)
	{
		fragsdisplays[i].enabled=gamedata.showfrags>0;
		namedisplays[i].enabled=gamedata.showfrags>0;
	}
	
	Scrolling(gamedata.exponentialscrolling);

	for(i=0;i<gamedata.players;++i)
	{
		if(hitpointdisplays[i].attach->enabled)
		{
			hitpointdisplays[i].enabled=gamedata.infonships;
			shielddisplays[i].enabled=gamedata.infonships;
			energydisplays[i].enabled=gamedata.infonships;
		}
	}


	if(gamedata.borgstate==BORGSTATE_ARRIVE)
	{
		borgcube->angle=(float)(90-(atan2(((mainengine.ScreenPos.y+mainengine.screenheight/2)-(borgcube->position.y+borgcube->size.y/2))*-1,(mainengine.ScreenPos.x+mainengine.screenwidth/2)-(borgcube->position.x+borgcube->size.x/2))/PI*180));
		if(borgcube->angle>=360)borgcube->angle-=360;
		if(borgcube->angle<0)borgcube->angle+=360;
		borgcube->currentacceleration=borgcube->maxacceleration;
	}
	else if(gamedata.borgstate==BORGSTATE_GOWARP)
	{
		borgcube->angle=(float)(90-(atan2(((mainengine.ScreenPos.y+mainengine.screenheight/2)-(borgcube->position.y+borgcube->size.y/2))*-1,(mainengine.ScreenPos.x+mainengine.screenwidth/2)-(borgcube->position.x+borgcube->size.x/2))/PI*180)+180);
		if(borgcube->angle>=360)borgcube->angle-=360;
		if(borgcube->angle<0)borgcube->angle+=360;
		borgcube->currentacceleration=borgcube->maxacceleration;

	}
	if(GetDistance(borgcube->position.x+borgcube->size.x/2,borgcube->position.y+borgcube->size.y/2,mainengine.ScreenPos.x+mainengine.screenwidth/2,mainengine.ScreenPos.y+mainengine.screenheight/2)<20||borgcube->hitpoints<borgcube->maxhitpoints*0.75)
	{
		gamedata.borgstate=BORGSTATE_GOWARP;
	}
	
	//Controllers
	for(i=0;i<gamedata.players;++i)
	{
		switch(gamedata.playercontrols[i])
		{
		case KEYBOARD1:
			ProcessKeyboardEx(PlayerSprites[i],&gamedata.p1control);
			break;
		case KEYBOARD2:
			ProcessKeyboardEx(PlayerSprites[i],&gamedata.p2control);
			break;
		case KEYBOARD3:
			ProcessKeyboardEx(PlayerSprites[i],&gamedata.p3control);
			break;
		case KEYBOARD4:
			ProcessKeyboardEx(PlayerSprites[i],&gamedata.p4control);
			break;
		case JOYSTICK1:
			ProcessControllersEx(PlayerSprites[i],&gamedata.joystick1);
			break;
		case JOYSTICK2:
			ProcessControllersEx(PlayerSprites[i],&gamedata.joystick2);
			break;
		case MOUSEKB1:
			ProcessKeyboardEx(PlayerSprites[i],&gamedata.p1control);
			ProcessMouse(PlayerSprites[i]);
			break;
		case MOUSEKB2:
			ProcessKeyboardEx(PlayerSprites[i],&gamedata.p2control);
			ProcessMouse(PlayerSprites[i]);
			break;
		case MOUSEKB3:
			ProcessKeyboardEx(PlayerSprites[i],&gamedata.p3control);
			ProcessMouse(PlayerSprites[i]);
			break;
		case MOUSEKB4:
			ProcessKeyboardEx(PlayerSprites[i],&gamedata.p4control);
			ProcessMouse(PlayerSprites[i]);
			break;
		}
	}
		
	//Targeting
	for(i2=0;i2<MAXSPRITES;++i2)
	{
		if(mainengine.sprites[i2])
		{
			if(mainengine.sprites[i2]->enabled )
			{
				if(mainengine.sprites[i2]->type==SPRITETYPE_CPU||mainengine.sprites[i2]->type==SPRITETYPE_HUMAN)
				{
					mainengine.sprites[i2]->target=mainengine.GetNearestActor(mainengine.sprites[i2]);
				}
				else if(mainengine.sprites[i2]->target&&!mainengine.sprites[i2]->target->enabled)
				{
					mainengine.sprites[i2]->target=mainengine.GetNearestActor(mainengine.sprites[i2]);
				}
			}
		}
	}

	//Messages
/*	if(tpdelete&&tpdelete<timeGetTime())
	{
		tpdelete=0;
		strcpy(messagedisplay.buffer,"");
		nlines=0;
	}*/
	
		
	//calculate the right color
	maxfrags=-99999999;
	minfrags=99999999;
	for(i=0;i<gamedata.players;++i)//calculate minfrags
	{
		if(maxfrags<gamedata.stats.frags[i])maxfrags=gamedata.stats.frags[i];
	}
	for(i=0;i<gamedata.players;++i)//calculate maxfrags
	{
		if(minfrags>gamedata.stats.frags[i])minfrags=gamedata.stats.frags[i];
	}
	
	for(i=0;i<gamedata.players;++i)
	{
		fragsdisplays[i].SetTxtColor(255,255,0);
		namedisplays[i].SetTxtColor(255,255,0);
	}
	if(!(maxfrags==minfrags))
	{
		for(i=0;i<gamedata.players;++i)
		{
			if(gamedata.stats.frags[i]==maxfrags)
			{
				fragsdisplays[i].SetTxtColor(0,255,0);
				namedisplays[i].SetTxtColor(0,255,0);
			}
			else if(gamedata.stats.frags[i]==minfrags)
			{
				fragsdisplays[i].SetTxtColor(255,0,0);
				namedisplays[i].SetTxtColor(255,0,0);
			}
		}		
	}
	
	//ammo and energydisplays
	for(i=0;i<gamedata.players;++i)
	{
		if(PlayerSprites[i]&&PlayerSprites[i]->weapon)
		if(PlayerSprites[i]->weapon->ammo>0)
		{
			energydisplays[i].intptr=(int*)&PlayerSprites[i]->ammo;
			energydisplays[i].floatptr=NULL;
		}
		else
		{
			energydisplays[i].floatptr=&PlayerSprites[i]->energy;
			energydisplays[i].intptr=NULL;
		}
	}
	
	//Displaycolors
	for(i=0;i<gamedata.players;++i)
	{
		g=(int)((float)PlayerSprites[i]->hitpoints/(float)PlayerSprites[i]->maxhitpoints*255);
		r=255-g;
		hitpointdisplays[i].SetTxtColor(r,g,0);
		
		b=(int)((float)PlayerSprites[i]->shieldstrenght/(float)PlayerSprites[i]->maxshieldstrenght*255);
		r=255-b;
		shielddisplays[i].SetTxtColor(r,0,b);
	}


} /* updateFrame */

void Scrolling(BOOL exponential)
{
	float x,y,dx,dy;
	VECTOR destspeed;
	int i,i2;

	x=0;
	y=0;
	dx=0;
	dy=0;
	i2=0;
	for(i=0;i<gamedata.players;++i)
	{
		if(PlayerSprites[i]->enabled)
		{
			if(!exponential)
			{
			x+=PlayerSprites[i]->position.x+PlayerSprites[i]->size.x/2;
			y+=PlayerSprites[i]->position.y+PlayerSprites[i]->size.y/2;
			}
			else
			{
				x=(PlayerSprites[i]->position.x+PlayerSprites[i]->size.x/2)-(mainengine.ScreenPos.x+mainengine.screenwidth/2);
				y=(PlayerSprites[i]->position.y+PlayerSprites[i]->size.y/2)-(mainengine.ScreenPos.y+mainengine.screenheight/2);
				x*=(float)fabs(x);
				y*=(float)fabs(y);
				dx+=x;
				dy+=y;
			}
			++i2;
		}
	}
	if(exponential)
	{
		dx/=i2;
		dy/=i2;
	}
	else
	{
		x/=i2;
		y/=i2;
		dx=x-(mainengine.ScreenPos.x+mainengine.screenwidth/2);
		dy=y-(mainengine.ScreenPos.y+mainengine.screenheight/2);
	}
	if(i2==0)
	{
		mainengine.ScrollSpeed.x/=(float)(mainengine.tnow-mainengine.tplastupdate);
		mainengine.ScrollSpeed.y/=(float)(mainengine.tnow-mainengine.tplastupdate);
		return;
	}

	if(fabs(dx)>0)
		destspeed.x=gamedata.scrollspeed*(float)(mainengine.tnow-mainengine.tplastupdate)/1000*dx;
	
	if(fabs(dy)>0)
		destspeed.y=gamedata.scrollspeed*(float)(mainengine.tnow-mainengine.tplastupdate)/1000*dy;

		
	if(mainengine.ScrollSpeed.x<destspeed.x)
	{
		mainengine.ScrollSpeed.x+=(float)(mainengine.tnow-mainengine.tplastupdate)*gamedata.scrollacceleration;
		if(mainengine.ScrollSpeed.x>destspeed.x)mainengine.ScrollSpeed.x=destspeed.x;
	}
	else if(mainengine.ScrollSpeed.x>destspeed.x)
	{
		mainengine.ScrollSpeed.x-=(float)(mainengine.tnow-mainengine.tplastupdate)*gamedata.scrollacceleration;
		if(mainengine.ScrollSpeed.x<destspeed.x)mainengine.ScrollSpeed.x=destspeed.x;
	}

	if(mainengine.ScrollSpeed.y<destspeed.y)
	{
		mainengine.ScrollSpeed.y+=(float)(mainengine.tnow-mainengine.tplastupdate)*gamedata.scrollacceleration;
		if(mainengine.ScrollSpeed.y>destspeed.y)mainengine.ScrollSpeed.y=destspeed.y;
	}
	else if(mainengine.ScrollSpeed.y>destspeed.y)
	{
		mainengine.ScrollSpeed.y-=(float)(mainengine.tnow-mainengine.tplastupdate)*gamedata.scrollacceleration;
		if(mainengine.ScrollSpeed.y<destspeed.y)mainengine.ScrollSpeed.y=destspeed.y;
	}
}
