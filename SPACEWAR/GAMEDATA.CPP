#include "gamedata.h"

	CGameData::CGameData()
	{
		int i;
		char tmpstr[64];
		char tmpstr2[64];

		for(i=0;i<4;++i)stats.frags[i]=0;
		//borgarrivetime=GetPrivateProfileIntCurrentDir("config.ini","game1","borgtime",-1);
		//if(borgarrivetime!=-1)nextborgarrivetime=(int)timeGetTime()+borgarrivetime;
		joystick1.Init(JOYSTICKID1);
		joystick2.Init(JOYSTICKID2);
		loadkbcontrol(&p1control,"keyboard.ini","p1control");	
		loadkbcontrol(&p2control,"keyboard.ini","p2control");	
		loadkbcontrol(&p3control,"keyboard.ini","p3control");	
		loadkbcontrol(&p4control,"keyboard.ini","p4control");	
		GetPrivateProfileStringCurrentDir("config.ini","game1","player1name",names[0],64);
		GetPrivateProfileStringCurrentDir("config.ini","game1","player2name",names[1],64);
		GetPrivateProfileStringCurrentDir("config.ini","game1","player3name",names[2],64);
		GetPrivateProfileStringCurrentDir("config.ini","game1","player4name",names[3],64);
		quitonY=FALSE;
		tpexit=0;
		loaddeathmessages();
		memset(commandline,0,64);
		players=GetPrivateProfileIntCurrentDir("config.ini","game1","players",2);
		showfrags=FRAGSHOWTIME;
		infonships=TRUE;
		borgstate=BORGSTATE_ARRIVE;

		//Scrolling
		scrollacceleration=(float)GetPrivateProfileIntCurrentDir("config.ini","game1","scrollacceleration",500)/1000.0f;
		exponentialscrolling=GetPrivateProfileIntCurrentDir("config.ini","game1","exponentialscroll",0);
		if(exponentialscrolling)
			scrollspeed=(float)GetPrivateProfileIntCurrentDir("config.ini","game1","scrollspeed",1000)/1000.0f;
		else
			scrollspeed=(float)GetPrivateProfileIntCurrentDir("config.ini","game1","scrollspeed",40000)/1000.0f;

		//Controls
		for(i=0;i<4;++i)
		{
			sprintf(tmpstr2,"player%dcontrol",i+1);
			GetPrivateProfileStringCurrentDir("config.ini","game1",tmpstr2,tmpstr,64);
			
			if(stricmp(tmpstr,"keyboard1")==0)
			{
				playercontrols[i]=KEYBOARD1;
			}
			else if(stricmp(tmpstr,"keyboard2")==0)
			{
				playercontrols[i]=KEYBOARD2;
			}
			else if(stricmp(tmpstr,"keyboard3")==0)
			{
				playercontrols[i]=KEYBOARD3;
			}
			else if(stricmp(tmpstr,"keyboard4")==0)
			{
				playercontrols[i]=KEYBOARD4;
			}
			else if(stricmp(tmpstr,"joystick1")==0)
			{
				playercontrols[i]=JOYSTICK1;
			}
			else if(stricmp(tmpstr,"joystick2")==0)
			{
				playercontrols[i]=JOYSTICK2;
			}
			else if(stricmp(tmpstr,"cpu")==0)
			{
				playercontrols[i]=CPU;
			}
			else if(stricmp(tmpstr,"mouse&keyboard1")==0)
			{
				playercontrols[i]=MOUSEKB1;
			}
			else if(stricmp(tmpstr,"mouse&keyboard2")==0)
			{
				playercontrols[i]=MOUSEKB2;
			}
			else if(stricmp(tmpstr,"mouse&keyboard3")==0)
			{
				playercontrols[i]=MOUSEKB3;
			}
			else if(stricmp(tmpstr,"mouse&keyboard4")==0)
			{
				playercontrols[i]=MOUSEKB4;
			}
		}

		//asteroidinterval=GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidinterval",0);
		asteroidspawndistance=GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidspawndistance",1000);
		asteroidspawnradius=GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidspawnradius",500);
		asteroidcount=GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidcount",10);
		asteroidspeed=GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidspeed",100);
		asteroidminlifetime=GetPrivateProfileIntCurrentDir("config.ini","game1","asteroidminlifetime",10000);
		//time2asteroid=asteroidinterval;

		//antaraninterval=GetPrivateProfileIntCurrentDir("config.ini","game1","antaraninterval",0);
		//time2antaran=antaraninterval;
	}

	BOOL CGameData::SaveStats(char *filename)
	{
		HANDLE h;
		unsigned long nbytes;
		SetFileAttributes(filename,FILE_ATTRIBUTE_NORMAL);
		h=CreateFile(filename,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		WriteFile(h,&stats,sizeof(stats),&nbytes,NULL);
		CloseHandle(h);
		return TRUE;
	}

	BOOL CGameData::loaddeathmessages()
	{
		int i,i2;
		char tmpstr[64],tmpstr2[64],istr[16];
		
		i=GetPrivateProfileIntCurrentDir("config.ini","game1","numcomments",0);
		numcomments=i;

		deathmessages1=new char*[i];
		deathmessages2=new char*[i];
		
		for(i2=0;i2<i;++i2)
		{
			strcpy(tmpstr,"comment1-");
			sprintf(istr,"%d",i2);
			strcat(tmpstr,istr);
			GetPrivateProfileStringCurrentDir("config.ini","game1",tmpstr,tmpstr2,64);
			deathmessages1[i2]=new char[strlen(tmpstr2)+1];
			strcpy(deathmessages1[i2],tmpstr2);
		}
		
		for(i2=0;i2<i;++i2)
		{
			strcpy(tmpstr,"comment2-");
			sprintf(istr,"%d",i2);
			strcat(tmpstr,istr);
			GetPrivateProfileStringCurrentDir("config.ini","game1",tmpstr,tmpstr2,64);
			deathmessages2[i2]=new char[strlen(tmpstr2)+1];
			strcpy(deathmessages2[i2],tmpstr2);
		}
		
		return(TRUE);
	}
	
	int CGameData::GetNumHumanPlayers()
	{
		int i;
		int n=players;

		for(i=0;i<players;++i)
		{
			if(playercontrols[i]==CPU)
				--n;
		}
		return n;
	}
	
	int CGameData::GetNumControllers()
	{
		int n=2;
		if(joystick1.enabled)++n;
		if(joystick2.enabled)++n;
		return n;
	}

	CGameData::~CGameData()
	{
		SaveStats("stats.bin");
	}
	
