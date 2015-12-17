#include "specials.h"

void SpecialRandomTeleport(Sprite2 *s)
{
	Sprite2 *ns=new Sprite2;
	int i=0;

	mainengine.DuplicateSprite(ns,s->special);
	mainengine.AddSpriteEx(ns);
	ns->enabled=TRUE;
	ns->position.x=s->position.x+s->size.x/2-ns->size.x/2;
	ns->position.y=s->position.y+s->size.y/2-ns->size.y/2;
	if(ns->soundnr>=0)mainengine.soundsys.Play(ns->soundnr,FALSE);

	do{
		s->position.x=(float)random((int)mainengine.ScreenPos.x,(int)(mainengine.ScreenPos.x+mainengine.screenwidth-s->size.x));
		s->position.y=(float)random((int)mainengine.ScreenPos.y,(int)(mainengine.ScreenPos.y+mainengine.screenheight-s->size.y));
		s->angle=(float)random(0,359);
		++i;
	}while(mainengine.GetSpriteDistance(s,mainengine.GetNearestSprite(s))<100 && i<100);

	ns=new Sprite2;
	mainengine.DuplicateSprite(ns,s->special);
	mainengine.AddSpriteEx(ns);
	ns->enabled=TRUE;
	ns->position.x=s->position.x+s->size.x/2-ns->size.x/2;
	ns->position.y=s->position.y+s->size.y/2-ns->size.y/2;

}

void SpecialTurret(Sprite2 *s)
{
	float f;
	Sprite2 *ns;
	if(!s->target||!s->special)return;

	if(s->energy<s->special->energy)return;
	s->energy-=s->special->energy;

	f=s->angle;
	s->angle=(float)(90-(atan2(((s->target->position.y+s->target->size.y/2)-(s->position.y+s->size.y/2))*-1,(s->target->position.x+s->target->size.x/2)-(s->position.x+s->size.x/2))/PI*180));
	if(s->angle>=360)s->angle-=360;
	if(s->angle<0)s->angle+=360;

	ns=new Sprite2;
	mainengine.DuplicateSprite(ns,s->special);
	mainengine.AddSprite(ns);
	s->Launch(ns,ns->launchspeed,0,(int)s->special->collisionrange);
	if(ns->soundnr>=0)mainengine.soundsys.Play(ns->soundnr,FALSE);

	s->angle=f;

}

void SpecialRearFire(Sprite2 *s)
{
	float f;

	f=s->angle;
	s->angle+=180;
	if(s->angle>=360)s->angle-=360;

	s->Fire(s->weapon->nlaunch);

	s->angle=f;
}

void SpecialSelfDestruct(Sprite2 *s)
{
	int i;
	s->tdisable=3000;
	for(i=0;i<gamedata.players;++i)
	{
		if(s==PlayerSprites[i])
		{
			++gamedata.stats.frags[i];
			break;
		}
	}
}

void SpecialSystemOverload(Sprite2 *s)
{
	s->tdisable=6000;
	s->energy=s->maxenergy;
	s->shieldstrenght=s->maxshieldstrenght;
}

void SpecialSuckEnergy(Sprite2 *s)
{
	Sprite2 *s2;
	float f1,f2;
	s2=mainengine.GetNearestActor(s);
	if(mainengine.GetSpriteDistance(s,s2)<200)
	{
		f1=s2->energy;
		f2=s2->shieldstrenght;
		s2->energy-=s->maxenergy-s->energy;
		s2->shieldstrenght-=s->maxshieldstrenght-s->shieldstrenght;

		s->energy=s->maxenergy;
		s->shieldstrenght=s->maxshieldstrenght;
	}
}

void SpecialMine(Sprite2 *s)
{
	Sprite2 *ns;
	if(!s->special)return;

	ns=new Sprite2;
	mainengine.DuplicateSprite(ns,s->special);
	mainengine.AddSpriteEx(ns);
	if(ns->soundnr>=0)mainengine.soundsys.Play(ns->soundnr,FALSE);
	s->Launch(ns,0,0,-(int)s->collisionrange);
}
