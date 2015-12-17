#include "onx.h"

void OnSpriteDestroy(Sprite2 *s)
{
	int i,ndestroyed=-1,nkiller=-1;
	char tmpstr[1024];


	for(i=0;i<gamedata.players;++i)
	{
		if(s==PlayerSprites[i])
		{
			gamedata.showfrags=FRAGSHOWTIME;
			if(death>=0)mainengine.soundsys.Play(death,FALSE);
			ndestroyed=i;
			++gamedata.stats.deaths[i];
			for(i=0;i<gamedata.players;++i)
			{
				if(s->attacker==PlayerSprites[i])
				{
					nkiller=i;
					if(nkiller!=ndestroyed)
					{
						++gamedata.stats.frags[i];
					}
					else
					{
						++gamedata.stats.suicides[ndestroyed];
						--gamedata.stats.frags[ndestroyed];
					}
				}
			}
			if(nkiller>=0)
			{
			/*	strcat(messagedisplay.buffer,gamedata.names[ndestroyed]);
				strcat(messagedisplay.buffer," ");
				strcat(messagedisplay.buffer,gamedata.deathmessages2[random(0,gamedata.numcomments-1)]);
				strcat(messagedisplay.buffer," ");
				strcat(messagedisplay.buffer,gamedata.names[nkiller]);
				strcat(messagedisplay.buffer,"\n");*/
				strcpy(tmpstr,gamedata.names[ndestroyed]);
				strcat(tmpstr," ");
				strcat(tmpstr,gamedata.deathmessages2[random(0,gamedata.numcomments-1)]);
				strcat(tmpstr," ");
				strcat(tmpstr,gamedata.names[nkiller]);
				strcat(tmpstr,"\n");
				strcat(cmdline.text,tmpstr);

				++gamedata.stats.kills[nkiller][ndestroyed];
			}
			else if(s->attacker==borgcube)
			{
				/*strcat(messagedisplay.buffer,gamedata.names[ndestroyed]);
				strcat(messagedisplay.buffer," ");
				strcat(messagedisplay.buffer,gamedata.deathmessages2[random(0,gamedata.numcomments-1)]);
				strcat(messagedisplay.buffer," the Borg");
				strcat(messagedisplay.buffer,"\n");*/
				strcat(cmdline.text,gamedata.names[ndestroyed]);
				strcat(cmdline.text," ");
				strcat(cmdline.text,gamedata.deathmessages2[random(0,gamedata.numcomments-1)]);
				strcat(cmdline.text," the Borg");
				strcat(cmdline.text,"\n");

				--gamedata.stats.frags[ndestroyed];
				++gamedata.stats.suicides[ndestroyed];
			}
			else
			{
				strcat(cmdline.text,gamedata.names[ndestroyed]);
				strcat(cmdline.text," ");
				strcat(cmdline.text,gamedata.deathmessages1[random(0,gamedata.numcomments-1)]);
				strcat(cmdline.text,"\n");
				--gamedata.stats.frags[ndestroyed];
				++gamedata.stats.suicides[ndestroyed];
			}
			//++nlines;
		/*	if(nlines>=MAXLINES)
			{
				tmp=strstr(messagedisplay.buffer,"\n");
				++tmp;
				strcpy(messagedisplay.buffer,tmp);
				--nlines;
			}
			tpdelete=timeGetTime()+LINESTAYTIME;*/
			//t->position.y=25;
			//t->enabled=TRUE;
			//tpdeleteline=timeGetTime()+2000;
			break;
		}
		else if(s==borgcube)
		{
			nkiller=-1;
			for(i=0;i<gamedata.players;++i)
			{
				if(s->attacker==PlayerSprites[i])
				{
					nkiller=i;
				}
			}
			if(nkiller>=0)
			{
				strcat(cmdline.text,"The borgcube ");
				strcat(cmdline.text," ");
				strcat(cmdline.text,gamedata.deathmessages2[random(0,gamedata.numcomments-1)]);
				strcat(cmdline.text," ");
				strcat(cmdline.text,gamedata.names[nkiller]);
				strcat(cmdline.text,"\n");
				gamedata.stats.frags[nkiller]+=BORGFRAGS;
			}
			else
			{
				strcat(cmdline.text,"The borgcube ");
				strcat(cmdline.text,gamedata.deathmessages1[random(0,gamedata.numcomments-1)]);
				strcat(cmdline.text,"\n");
			}
/*			++nlines;
			if(nlines>=3)
			{
				tmp=strstr(messagedisplay.buffer,"\n");
				++tmp;
				strcpy(messagedisplay.buffer,tmp);
				--nlines;
			}
			tpdelete=timeGetTime()+2000;*/

			break;
		}
	}
}

void OnSpriteShieldDown(Sprite2 *s)
{
	int i;
	
	for(i=0;i<gamedata.players;++i)
	{
		if(s==PlayerSprites[i])
		{
			if(shielddown>=0)mainengine.soundsys.Play(shielddown,FALSE);	
		}
	}

}

void OnSpriteRespawn(Sprite2 *s)
{
	Sprite2 *ns=new Sprite2;
	mainengine.DuplicateSprite(ns,mainengine.prototypes[RESPAWNSPRITENUMBER]);
	mainengine.AddSpriteEx(ns);
	ns->enabled=TRUE;
	ns->position.x=s->position.x+s->size.x/2-ns->size.x/2;
	ns->position.y=s->position.y+s->size.y/2-ns->size.y/2;
	if(ns->soundnr>=0)mainengine.soundsys.Play(ns->soundnr,FALSE);
}

void OnItemClick(BaseItem *i)
{
}

void OnSpriteHullCritical(Sprite2 *s)
{
	int i;
	
	for(i=0;i<gamedata.players;++i)
	{
		if(s==PlayerSprites[i])
		{
			if(hullcritical>=0)mainengine.soundsys.Play(hullcritical,FALSE);
			break;
		}
	}
}

void OnSpriteCollision(Sprite2 *s1,Sprite2 *s2)
{
	int i;

	if(!(s1->launchedfrom||s2->launchedfrom))return;

	if(s1->launchedfrom&&!s2->launchedfrom)
	{
		for(i=0;i<gamedata.players;++i)
		{
			if(s1->launchedfrom==PlayerSprites[i])
			{
				++gamedata.stats.hits[i];
				break;
			}
		}
	}
	else if(s2->launchedfrom&&!s1->launchedfrom)
	{
		for(i=0;i<gamedata.players;++i)
		{
			if(s2->launchedfrom==PlayerSprites[i])
			{
				++gamedata.stats.hits[i];
				break;
			}
		}
	}
	else if(s2->launchedfrom&&s1->launchedfrom)
	{
		for(i=0;i<gamedata.players;++i)
		{
			if(s2->launchedfrom==PlayerSprites[i])
			{
				++gamedata.stats.hits[i];
				break;
			}
		}
		for(i=0;i<gamedata.players;++i)
		{
			if(s1->launchedfrom==PlayerSprites[i])
			{
				++gamedata.stats.hits[i];
				break;
			}
		}
	}

}

void OnPreFlip()
{
	//POINT points[4]={{0,0},{100,400},{200,000},{300,300}};


	//DDPolyLine(mainengine.lpDDSBackBuffer,points,4,RGB(255,255,255),1);

	//DDPolyBezier(mainengine.lpDDSBackBuffer,points,4,RGB(255,255,255),1);
	//DDSimpleBezier(mainengine.lpDDSBackBuffer,points,4,RGB(255,255,255),1);

}

void OnSpriteFire(Sprite2 *s,int n)
{
	int i;
	
	for(i=0;i<gamedata.players;++i)
	{
		if(s==PlayerSprites[i])
		{
			gamedata.stats.shots[i]+=n;
			break;
		}
	}
}
