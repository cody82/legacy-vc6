#include "events.h"

void BorgArrive()
{
	int i2;
	//if((int)mainengine.tnow>=gamedata.nextborgarrivetime&&gamedata.borgarrivetime!=-1&&!mainengine.SpriteInScreen(borgcube))
	//{
		//gamedata.nextborgarrivetime=(int)mainengine.tnow+gamedata.borgarrivetime;
		if(borgarrivesound>=0)mainengine.soundsys.Play(borgarrivesound,FALSE);
		gamedata.borgstate=BORGSTATE_ARRIVE;
		i2=random(0,359);
		borgcube->position.x=mainengine.ScreenPos.x+mainengine.screenwidth/2+(float)cos((double)((double)i2/180*PI))*(mainengine.screenwidth+mainengine.screenheight)/2;
		borgcube->position.y=mainengine.ScreenPos.y+mainengine.screenheight/2+(float)sin((double)((double)i2/180*PI))*(mainengine.screenwidth+mainengine.screenheight)/2;
		borgcube->enabled=TRUE;
		borgcube->hitpoints=borgcube->maxhitpoints;
		borgcube->shieldstrenght=borgcube->maxshieldstrenght;
		borgcube->smoking=FALSE;
	//}

}

void AsteroidShower()
{
	int i;
	float angle=(float)random(0,359);

	Sprite2 *s;
	VECTOR pos;
	pos.x=mainengine.ScreenPos.x+mainengine.screenwidth/2+(float)cos((double)((double)angle/180*PI))*gamedata.asteroidspawndistance;
	pos.y=mainengine.ScreenPos.y+mainengine.screenheight/2+(float)sin((double)((double)angle/180*PI))*gamedata.asteroidspawndistance;

	for(i=0;i<gamedata.asteroidcount;++i)
	{
		s=new Sprite2;
		mainengine.DuplicateSprite(s,mainengine.prototypes[ASTEROIDSPRITENR]);
		mainengine.AddSpriteEx(s);
		mainengine.SpawnSpriteInCircle(s,pos.x,pos.y,(float)gamedata.asteroidspawnradius);
		s->speed.x=-(float)(cos(angle/180*PI)*gamedata.asteroidspeed);
		s->speed.y=-(float)(sin(angle/180*PI)*gamedata.asteroidspeed);
		//s->tpdisable=mainengine.tnow+ASTEROIDLIFETIME;
		s->tminlife=(int)gamedata.asteroidminlifetime;
		s->currentframe=random(0,s->nframes);
	}

}
