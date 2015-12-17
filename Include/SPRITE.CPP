#include "sprite.h"
/*
	void Text2::BlitText(LPDIRECTDRAWSURFACE lpDDS)
	{
		static HDC	hdc;
		if(!enabled)return;

		if(lpDDS->GetDC(&hdc)== DD_OK)
		{
			//SetBkColor( hdc, RGB( backcolor[0], backcolor[1], backcolor[2] ) );
			SetBkMode(hdc,TRANSPARENT);
			SetTextColor( hdc, RGB( textcolor[0], textcolor[1], textcolor[2] ) );
			DrawText(hdc,textptr,-1,&position,DT_CENTER);
			lpDDS->ReleaseDC(hdc);
		}
		position.left+=v.x;
		position.right+=v.x;
		position.top+=v.y;
		position.bottom+=v.y;

		if(position.bottom<0)
		{
			position.bottom=800+position.bottom-position.top;
			position.top=800;
		}
	}
*/
	energybar::energybar()
	{
		maxvalue=100;
		currentvalue=50;
		position.x=0;
		position.y=0;
		orientation=HORIZONTAL;
		forecolor[0]=255;
		forecolor[1]=255;
		forecolor[2]=255;
		backcolor[0]=128;
		backcolor[1]=128;
		backcolor[2]=128;
		inertia=FALSE;
		inertiavalue=0;
		enabled=TRUE;
		attach=NULL;
		intptr=NULL;
		floatptr=NULL;
	}

	void energybar::SetBackColor(byte r,byte g,byte b)
	{
		backcolor[0]=r;
		backcolor[1]=g;
		backcolor[2]=b;
	}
	
	void energybar::SetForeColor(byte r,byte g,byte b)
	{
		forecolor[0]=r;
		forecolor[1]=g;
		forecolor[2]=b;
	}
	
	energybar::~energybar()
	{
	}
		
	void energybar::Update(UINT dtime)
	{
		if(intptr!=NULL)
		{
			currentvalue=*intptr;
		}
		else if(floatptr!=NULL)
		{
			currentvalue=(int)*floatptr;
		}
		
		if(!inertia)inertiavalue=currentvalue;
		else 
		{
			if(inertiavalue<currentvalue)++inertiavalue;
			else if(inertiavalue>currentvalue)--inertiavalue;
		}

		if(attach)
		{
			if(enabled=attach->enabled)
			{
				position.x=attach->position.x+(float)attachpos.x;
				position.y=attach->position.y+(float)attachpos.y;
			}
		}
	}

	void energybar::Draw(LPDIRECTDRAWSURFACE lpDDS,int x,int y)
	{
		if(!enabled)return;
		RECT destrect;
		DDBLTFX ddbltfx;
		ddbltfx.dwSize=sizeof(ddbltfx);

		destrect.left=(int)position.x;
		destrect.right=(int)position.x+size.x;
		destrect.top=(int)position.y;
		destrect.bottom=(int)position.y+size.y;

		ddbltfx.dwFillColor=RGB(backcolor[0],backcolor[1],backcolor[2]);
		lpDDS->Blt(&destrect,NULL,NULL,DDBLT_COLORFILL,&ddbltfx);
		
		ddbltfx.dwFillColor=RGB(forecolor[0],forecolor[1],forecolor[2]);

		if(orientation==HORIZONTAL)
		{
			destrect.right=(int)(position.x + (float) ( ((float)inertiavalue/(float)maxvalue) * (float)size.x));
		}
		else if(orientation==VERTICAL)
		{
			destrect.top=(int)(position.y+size.y-(int) ( ((float)inertiavalue/(float)maxvalue) * (float)size.y ));
		}
		lpDDS->Blt(&destrect,NULL,NULL,DDBLT_COLORFILL,&ddbltfx);
	}
	
	void BaseItem::OnPress(int x,int y)
	{
	}

	void BaseItem::RestoreSurfaces()
	{
	}

	BaseItem::BaseItem()
	{
		//memset(this,0,sizeof(*this));
		noscroll=TRUE;
		position.x=0;
		position.y=0;
		size.x=0;
		size.y=0;
		enabled=FALSE;
		bfocused=FALSE;
		e=NULL;
	}
	BaseItem::~BaseItem()
	{
	}
	void BaseItem::Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y)
	{
		return;
	}
	void BaseItem::Update(UINT dtime)
	{
		return;
	}

	Text3::Text3()
	{
		//memset(this,0,sizeof(*this));
		attach=NULL;
		color[0]=255;
		color[1]=255;
		color[2]=255;
		enabled=TRUE;
		tpdelete=0;
		intptr=NULL;
		floatptr=NULL;
		strptr=NULL;
		position.x=0;
		position.y=0;
		truncatedecimals=TRUE;
		noscroll=TRUE;
	}

	void Text3::SetTxtColor(int r,int g,int b)
	{
		color[0]=r;
		color[1]=g;
		color[2]=b;
	}

	Text3::~Text3()
	{
	}

	void Text3::Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y)
	{
		if(!enabled)return;
		
		HDC	hdc;
		//char tmpstr[64];
		
		if(lpDDS->GetDC(&hdc)== DD_OK)
		{
			//SetBkColor( hdc, RGB( backcolor[0], backcolor[1], backcolor[2] ) );
			SetBkMode(hdc,TRANSPARENT);
			SetTextColor( hdc, RGB( color[0], color[1], color[2] ) );
			TextOut( hdc, x, y, buffer, lstrlen(buffer) );
			lpDDS->ReleaseDC(hdc);
		}
	}

	void Text3::Update(UINT dtime)
	{
		//char tmpstr[64];
		int i;
		if(tpdelete&&tpdelete<=e->tnow)
		{
			i=e->GetItemNumber(this);
			if(i>=0)
			{
				e->DeleteItem(i);
				return;
			}
		}
			if(intptr!=NULL)
			{
				sprintf(buffer,"%d",*intptr);
			}
			else if(floatptr!=NULL)
			{
				if(!truncatedecimals)
					sprintf(buffer,"%f",*floatptr);
				else
				{
					i=(int)*floatptr;
					sprintf(buffer,"%d",i);
				}
			}
			else if(strptr!=NULL)
			{
				strcpy(buffer,strptr);
			}

		if(attach)
		{
			if(enabled=attach->enabled)
			{
				position.x=attach->position.x+(float)attachpos.x;
				position.y=attach->position.y+(float)attachpos.y;
			}
		}
	}

Text4::Text4()
{
	speed.x=0;
	speed.y=0;
	position.x=0;
	position.y=0;
	color[0]=255;
	color[1]=255;
	color[2]=255;
	strptr=NULL;
	noscroll=TRUE;
}

Text4::~Text4()
{
}
	void Text4::SetTxtColor(int r,int g,int b)
	{
		color[0]=r;
		color[1]=g;
		color[2]=b;
	}

void Text4::Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y)
{
		HDC	hdc;
		RECT rect;
		//HFONT hf;
		if(!enabled)return;

		if(noscroll)
		{
			rect.left=(int)position.x;
			rect.right=(int)position.x+size.x;
			rect.top=(int)position.y;
			rect.bottom=(int)position.y+size.y;
		}
		else
		{
			rect.left=x;
			rect.right=x+size.x;
			rect.top=y;
			rect.bottom=y+size.y;
		}

		if(lpDDS->GetDC(&hdc)== DD_OK)
		{
			//SetBkColor( hdc, RGB( backcolor[0], backcolor[1], backcolor[2] ) );
			SetBkMode(hdc,TRANSPARENT);
			SetTextColor( hdc, RGB( color[0], color[1], color[2] ) );
			//hf=CreateFont(20,10,0,0,900,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"FuturaBlack BT");
			//SelectObject(hdc,hf);
			if(strptr)
				DrawText(hdc,strptr,-1,&rect,DT_CENTER);
			else
				DrawText(hdc,buffer,-1,&rect,DT_CENTER);
			lpDDS->ReleaseDC(hdc);
			//DeleteObject(hf);
		}
}

void Text4::Update(UINT dtime)
{
	if(!tplastupdate)tplastupdate=e->tnow;
	if(tplastupdate==e->tnow)return;

	position.x+=speed.x*(dtime)/1000;
	position.y+=speed.y*(dtime)/1000;
	tplastupdate=e->tnow;
}

Sprite2::Sprite2()
{
	memset(this,0,sizeof(*this));
/*	lpDSBSound=NULL;
	staticshield=NULL;
	weapon=NULL;
	defaultweapon=NULL;
	attacker=NULL;
	target=NULL;
	friendsprite=NULL;
	explosion=NULL;
	launchedfrom=NULL;
	debris=NULL;
	release=NULL;
	smoke=NULL;
*/	type=SPRITETYPE_NORMAL;
	maxspeed=1000;
	hitforce=1;
	hitforcemodifier=1;
	lr=1;
	nlaunch=2;
	homing=FALSE;
	animfps=25;
	gravdep=TRUE;
	currentswing=1;
	swingtime=1000;
	swingangle=90;
	swing=FALSE;
	swingacceleration=1000;
	soundnr=-1;
	tdisable=-1;
	tenablehitdetection=-1;
	tlastswingchange=-1;
	damagemultiplicator=1.0f;
	//angle=0;
	
}

Sprite2::~Sprite2()
{
	if(e)e->OnSpriteDelete(this);
//	if(lpDSBSound)lpDSBSound->Release();
}

BOOL Sprite2::Update(int dtime)
{
	if(dtime==0)
	{
		return FALSE;
	}

	switch(type)
	{
	case SPRITETYPE_NORMAL:
		UpdateNormal(dtime);
		break;
	case SPRITETYPE_EXPLOSION:
		UpdateExplosion(dtime);
		break;
	case SPRITETYPE_BONUS:
		//UpdateBonus(tnow);
		UpdateNormal(dtime);
		break;
	case SPRITETYPE_CPU:
		UpdateNormal(dtime);
		UpdateCpu(dtime);
		break;
	case SPRITETYPE_HUMAN:
		UpdateNormal(dtime);
		UpdateHuman(dtime);
		break;
	}
	return TRUE;
}
	
void Sprite2::Special()
{
	if(specialproc&&tlastspecial>=tspecialdelay&&enabled)
	{
		tlastspecial=0;
		specialproc(this);
	}
}

BOOL Sprite2::Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y)
{
	RECT destrect;
	RECT rect,clip;

	destrect.left=x;
	destrect.right=x+(int)size.x;
	destrect.top=y;
	destrect.bottom=y+(int)size.y;

	rect.left=0;
	rect.right=size.x;
	rect.top=0;
	rect.bottom=size.x;

	clip.left=0;
	clip.right=e->screenwidth;
	clip.top=0;
	clip.bottom=e->screenheight;

	if(lpDDSFrames[currentframe])
	{
		if(!additive)
			lpDDS->Blt(&destrect,lpDDSFrames[currentframe],NULL,DDBLT_KEYSRC |DDBLT_WAIT,NULL);
		else//AlphaBlending
		{
			//e->AdditiveBlt16(lpDDS,lpDDSFrames[currentframe],&destrect,&rect);
			DrawAlpha((LPDIRECTDRAWSURFACE)lpDDSFrames[currentframe],(LPDIRECTDRAWSURFACE)lpDDS,rect,destrect,x,y,false);
		}
	}
	//DrawMK2Collision(lpDDS,x,y);
	return TRUE;
}

void Sprite2::SetFrame(int dtime)
{
	if(nframes==0)return;

	if(frametype==FRAMETYPE_ANIMATION&& tframechange>=(UINT)(1000/animfps))
	{
		while(tframechange>=(UINT)(1000/animfps))
		{
			if(currentframe<nframes-1)++currentframe;
			else if(!disableanimcomplete)
				currentframe=0;
			else 
			{
				Disable();
				break;
			}
			tframechange-=(UINT)(1000/animfps);
		}

	}
	else if(frametype==FRAMETYPE_DIRECTION)
	{
		currentframe=int(angle/(360/nframes)+0.5);
		if(currentframe>=nframes)currentframe=0;
	}

}
	
BOOL Sprite2::InitWithSurfaceOfSprite(Sprite2 *s)
{
	int i;
	size.x=s->size.x;
	size.y=s->size.x;

	enabled=TRUE;
	nframes=s->nframes;

	for(i=0;i<100;++i)
	{
		lpDDSFrames[i]=s->lpDDSFrames[i];
	}
	return TRUE;
}
	
BOOL Sprite2::DrawMK2Collision(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y)
{
	RECT r;
	RECT destrect;
	if(!mk2collide)return FALSE;
	int i;
	int x0=x,y0=y;
	DDBLTFX ddbltfxtmp;
	ddbltfxtmp.dwSize=sizeof(ddbltfxtmp);
	ddbltfxtmp.dwFillColor=RGB(255,255,255);

	r.left=x;
	r.right=x+size.x;
	r.top=y;
	r.bottom=y+size.y;

	for(y=r.top;y<r.bottom;++y)
	{
		for(x=r.left;x<r.right;++x)
		{
			destrect.left=x;
			destrect.right=x+1;
			destrect.top=y;
			destrect.bottom=y+1;
			i=(y-y0)*size.x+(x-x0);
			if(collide[currentframe].GetBit(i))
			//if(collide2[currentframe][i])
			lpDDS->Blt(&destrect,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&ddbltfxtmp);		
		}
	}
	return TRUE;
}

void Sprite2::Disable()
{
	Sprite2 *tmp;
	int i;
	enabled=FALSE;
	tdisabled=0;
	tdisable=-1;
	age=0;

		if(explosion)//it´s a prototype
		{
			tmp=new Sprite2;
			e->DuplicateSprite(tmp,explosion);
			e->AddSpriteEx(tmp);
			tmp->position.x=(float)((position.x+size.x/2)-(tmp->size.x/2));
			tmp->position.y=(float)((position.y+size.y/2)-(tmp->size.y/2));
			tmp->enabled=TRUE;
			if(tmp->soundnr>=0)e->soundsys.Play(tmp->soundnr,FALSE);
		}

		if(release)
		{
			tmp=new Sprite2;
			e->DuplicateSprite(tmp,release);
			e->AddSpriteEx(tmp);
			tmp->position.x=(float)((position.x+size.x/2)-(tmp->size.x/2));
			tmp->position.y=(float)((position.y+size.y/2)-(tmp->size.y/2));
			tmp->enabled=TRUE;
			tmp->tdisable=RELEASESTAYTIME;
		}

		if(debris)
		{
			for(i=0;i<(int)ndebris;++i)
			{
				tmp=new Sprite2;
				e->DuplicateSprite(tmp,debris);
				e->AddSpriteEx(tmp);
				float a=(float)random(0,359);
				tmp->position.x=(float)(position.x+size.x/2-tmp->size.x/2+cos(a)*20);
				tmp->position.y=(float)(position.y+size.y/2-tmp->size.y/2+sin(a)*20);
				tmp->speed.x=(float)cos(a)*tmp->launchspeed+speed.x/DEBRISSPEEDDIVISOR;
				tmp->speed.y=(float)sin(a)*tmp->launchspeed+speed.y/DEBRISSPEEDDIVISOR;
				if(tmp->homing)
					tmp->target=e->GetNearestActor(tmp);
				if(launchedfrom)
					tmp->launchedfrom=launchedfrom;
				//else tmp->launchedfrom=this;
				if(tmp->canhit&&tmp->canbehit)
				{
					tmp->canhit=FALSE;
					tmp->canbehit=FALSE;
					tmp->tenablehitdetection=DEBRISTIME2HITDETECT;
				}
				tmp->enabled=TRUE;
				if(!tmp->homing)
				{
					tmp->currentframe=random(0,tmp->nframes);
					tmp->tdisable=DEBRISLIFETIME+random(0,DEBRISLIFETIMEFLUCTUATION)-DEBRISLIFETIMEFLUCTUATION/2;
					if(tmp->GetSpeed()<DEBRISMINSPEED)tmp->enabled=FALSE;
				}
			}
		}
//		if(lpDSBexplosionsound!=NULL)lpDSBexplosionsound->Play(0,0,0);
		e->OnSpriteDisable(this);
}
	
BOOL Sprite2::GetMK2Collision(int x,int y)
{
	if(!mk2collide)return FALSE;
	BOOL b;

	x-=(int)position.x;
	y-=(int)position.y;

	if(x<0||x>=size.x)exit(0);
	if(y<0||y>=size.y)exit(0);

	b=collide[currentframe].GetBit(y*size.x+x);
	//b=collide2[currentframe][y*size.x+x];
	return b;
}
	
BOOL Sprite2::InitMK2Collisions(LPSTR pbmfile,HBITMAP hbm)
{
	int i;
	char tmpstr[64];
	RECT rect;
	POINT s;
	int nframesx,nframesy;
	int w=size.x;
	int h=size.y;
	HDC hdc;
	//HBITMAP hbm;
	BITMAP bm;
	BOOL delhbm=FALSE;

	//if(FileExistCurDir(pbmfile))
/*	s=BitBool::GetPBMSize(pbmfile);
	if(s.x>0&&s.y>0)
	{
		nframesx=s.x/w;
		nframesy=s.y/h;
		for(i=0;i<(int)nframes;++i)
		{
			rect.left = w*(i%nframesx);
			rect.top = h*(int(i/nframesx));
			rect.right = w*(i%nframesx)+w;
			rect.bottom = h*(int(i/nframesx))+h;
			if(!collide[i].NewFromPBM_asciiRect(tmpstr,rect,FALSE))
			{
				return FALSE;
			}
			collide[i].Invert();
		}
	}*/
	if(hbm)goto LOADBMPRECT;

	for(i=0;i<(int)nframes;++i)
	{
		sprintf(tmpstr,"%s%0.3d.pbm",pbmfile,i+1);
		if(!collide[i].NewFromPBM_ascii(tmpstr,FALSE))
		{
			if(i>0)
				return FALSE;
			else goto LOADBMP;
		}
		collide[i].Invert();
	}
	goto OK;

LOADBMP:
	e->lpDDSPrimary->GetDC(&hdc);
	for(i=0;i<(int)nframes;++i)
	{
		sprintf(tmpstr,"%s%0.3d.bmp",pbmfile,i+1);
		if(!collide[i].NewFromBMP(tmpstr,hdc,FALSE))
		{
			e->lpDDSPrimary->ReleaseDC(hdc);
			if(i>0)
				return FALSE;
			else goto LOADBMPRECT;
		}
	}
	e->lpDDSPrimary->ReleaseDC(hdc);
	goto OK;

LOADBMPRECT:

	if(!hbm)
	{
		hbm=(HBITMAP)LoadImage(NULL,pbmfile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		delhbm=TRUE;
	}
	if(!hbm)return FALSE;

	GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap
	s.x=bm.bmWidth;
	s.y=bm.bmHeight;

	e->lpDDSPrimary->GetDC(&hdc);
		
	nframesx=s.x/w;
	nframesy=s.y/h;
	for(i=0;i<(int)nframes;++i)
	{
		rect.left = w*(i%nframesx);
		rect.top = h*(int(i/nframesx));
		rect.right = w*(i%nframesx)+w;
		rect.bottom = h*(int(i/nframesx))+h;
		if(!collide[i].NewFromBMPRect(hbm,hdc,rect,FALSE))
		{
			e->lpDDSPrimary->ReleaseDC(hdc);
			if(delhbm)DeleteObject(hbm);
			return FALSE;
		}
	}

	e->lpDDSPrimary->ReleaseDC(hdc);
	if(delhbm)DeleteObject(hbm);



OK:
	mk2collide=TRUE;

/*	HANDLE hf;
	PACK p;
	hf=CreateFile(e->cpf->packfile,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hf==INVALID_HANDLE_VALUE)return(FALSE);

	for(i=0;i<(int)nframes;++i)
	{
		sprintf(tmpstr,"%s%0.3d.pbm",pbmfile,i+1);
		if(!e->cpf->GetFileInfo(tmpstr,&p))
			return FALSE;
		if(!collide[i].NewFromPBM_asciiInFile(hf,p.Begin,p.End-p.Begin,FALSE))
		{
			return FALSE;
		}
		collide[i].Invert();
	}
	mk2collide=TRUE;
	
	CloseHandle(hf);*/
	
	return TRUE;

}

void Sprite2::Fire(UINT n)
{
	if(n==0)return;
	
	unsigned int i,i1=1;
	double stepx=0;
	Sprite2 *sn;
	int nlaunched=0;
	
	if(!weapon||!enabled)return;
	//if(tplastfire==0)tplastfire=timeGetTime();
	if(tlastfire<weapon->tfiredelay)return;
	tlastfire=0;

	if(ammo<1 && weapon->ammo>0)//Zur Default-Waffe wechseln
	{
		weapon=defaultweapon;
		nlaunch=defaultweapon->nlaunch;
		tlastfire=defaultweapon->tfiredelay;
	}
	if(energy<weapon->energy)return;
	if(energy<weapon->energy*n)
	{
		n=(int)(energy/weapon->energy);
	}
	//energy-=weapon->energy*n;

	if(n>ammo && weapon->ammo>0)
	{
		n=ammo;
	}
/*	if(weapon->ammo>0)
	{
		ammo-=n;
	}
*/
	if(n%2==1)
	{
		sn=new Sprite2;
		e->DuplicateSprite(sn,weapon);
		e->AddSpriteEx(sn);
		
		if(n>1)
		{
			if(centerfire&&sn->centerfire)
			{
				Launch(sn,sn->launchspeed,(int)0,(int)weapondist.y);
				++nlaunched;
			}
		}
		else
		{
			if(!(centerfire&&sn->centerfire))
			{
				Launch(sn,sn->launchspeed,(int)(lr*weapondist.x),(int)weapondist.y);
				++nlaunched;
				lr*=-1;
			}
			else
			{
				Launch(sn,sn->launchspeed,0,centerweapondisty);
				++nlaunched;
			}
		}
		--n;
	}
	
	for(i=0;i<n;i+=2)
	{
		
		do
		{	
			sn=new Sprite2;
			e->DuplicateSprite(sn,weapon);
			e->AddSpriteEx(sn);
			
			Launch(sn,sn->launchspeed,(int)(i1*(weapondist.x-(int)stepx)),(int)weapondist.y);
			++nlaunched;
			i1*=-1;
		}while(i1==-1);
		
		if(i>0)stepx+=stepx;
		if(i==0)stepx=2*weapondist.x/n;
	}
	
	energy-=weapon->energy*nlaunched;
	ammo-=nlaunched*weapon->ammo;

	if(e->fireproc)
		e->fireproc(this,nlaunched);

	
	if(sn->soundnr>=0 && e->soundsys.lpDS)
		e->soundsys.Play(sn->soundnr,FALSE);

}

void Sprite2::Launch(Sprite2 *s,float speed,int shiftx,int shifty)
{
		if(!s)return;
		if(e->pause)return;
		float angle3;
		float angle4;
		angle3=-angle+90;
		if(angle3<0)angle3+=360;
		angle4=angle3+90;
		if(angle4>=360)angle4-=360;
			s->position.x= (float)(cos(angle4/180*PI)*-shiftx + cos(angle3/180*PI) *shifty) + position.x + size.x/2 - s->size.x/2;
			s->position.y= (float)(-sin(angle4/180*PI)*-shiftx -sin(angle3/180*PI)*shifty) + position.y + size.y/2 - s->size.y/2;
			s->speed.x=(float)(cos(angle3/180*PI)*speed);
			s->speed.y=(float)(sin(angle3/180*PI)*speed*-1);
			s->enabled=TRUE;
			s->friendsprite=this;
			s->angle=angle;
			s->target=target;
			s->hitdamage*=damagemultiplicator;
			s->SetFrame(0);
			if(s->launchlifetime)s->tdisable=s->launchlifetime;
			if(!launchedfrom)s->launchedfrom=this;
			else s->launchedfrom=launchedfrom;
}

void Sprite2::OnCollision(Sprite2 *s)
{
	switch(type)
	{
	case SPRITETYPE_EXPLOSION:
		//UpdateExplosion(tnow);
		break;
	case SPRITETYPE_BONUS:
		OnCollisionBonus(s);
		break;
	default:
		OnCollisionNormal(s);
		break;
	}
}

BOOL Sprite2::Initialize(LPDIRECTDRAW lpDD,HBITMAP hbm,UINT w,UINT h,UINT numframes,BOOL autocolorkey)
{

		DDSURFACEDESC       ddsd;
		HRESULT             ddrval;
		BITMAP				bm;
		RECT rcRect;
		int i;
		int nframesx,nframesy;

		size.x=w;
		size.y=h;
//		numframesy=nframesy;
//		transparent=trans;

		GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap
		nframesx=bm.bmWidth/w;
		nframesy=bm.bmHeight/h;
		if(numframes==0)numframes=nframesx*nframesy;

		enabled=TRUE;

		if(nframesx==1&&nframesy==1&&numframes>1)//rotate
		{
			ddsd.dwSize = sizeof( ddsd );
			ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;

#ifdef LOAD_TO_SYSMEM
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
#else
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;//DDSCAPS_SYSTEMMEMORY;
#endif

			ddsd.dwHeight = h;
			ddsd.dwWidth = w;
			ddrval = lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSFrames[0], NULL );
		if(ddrval!=DD_OK)
		{
			strcpy(e->errormessage,"IDirectDraw::CreateSurface failed: ");
			e->PrintDDError(e->errormessage,ddrval);
			e->OnError();
			//return(FALSE);
		}

		//Interpolate
			if(!CreateRotatedSurfaces360((LPDIRECTDRAW)e->lpDD,(LPDIRECTDRAWSURFACE)lpDDSFrames[0],(LPDIRECTDRAWSURFACE*)&lpDDSFrames[1],numframes))
			{
				strcpy(e->errormessage,"IDirectDraw::CreateSurface failed: ");
				e->PrintDDError(e->errormessage,ddrval);
				e->OnError();
				return FALSE;
			}
			nframes=numframes;
			return TRUE;
		}

		for(i=0;i<(int)numframes;++i)
		{
			rcRect.left = w*(i%nframesx);
			rcRect.top = h*(int(i/nframesx));
			rcRect.right = w*(i%nframesx)+w;
			rcRect.bottom = h*(int(i/nframesx))+h;
		
			
			ddsd.dwSize = sizeof( ddsd );
			ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;

#ifdef LOAD_TO_SYSMEM
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
#else
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;//DDSCAPS_SYSTEMMEMORY;
#endif

			ddsd.dwHeight = h;
			ddsd.dwWidth = w;
			ddrval = lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSFrames[i], NULL );
		if(ddrval!=DD_OK)
		{
			strcpy(e->errormessage,"IDirectDraw::CreateSurface failed: ");
			e->PrintDDError(e->errormessage,ddrval);
			e->OnError();
			//return(FALSE);
		}

			DDCopyBitmap((LPDIRECTDRAWSURFACE)lpDDSFrames[i], hbm, rcRect.left, rcRect.top, w, h);
			//DDSetColorKey(lpDDSFrames[i], RGB(r,g,b));//CLR_INVALID
			if(autocolorkey)
			{
				DDSetColorKey((LPDIRECTDRAWSURFACE)lpDDSFrames[i], CLR_INVALID);//CLR_INVALID
			}
		}
		nframes=numframes;

if(i==0)
return FALSE;

	return TRUE;
}
	
BOOL Sprite2::Initialize2(LPDIRECTDRAW lpDD,char *bmfile,BOOL autocolorkey)
{
	HBITMAP hbm;
	BITMAP bm;
	char tmpstr[64],tmpstr2[64];
	int i;
	BOOL startatzero=TRUE;
	DDSURFACEDESC       ddsd;
	HRESULT             ddrval;
		
	//HANDLE hf;
	//hf=CreateFile(e->cpf->packfile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	//PACK p;

	for(i=0;;++i)
	{
		strcpy(tmpstr,bmfile);
		sprintf(tmpstr2,"%d",i);
		if(i<10)
		{
			strcat(tmpstr,"00");
		}
		else if(i<100)
		{
			strcat(tmpstr,"0");
		}
		strcat(tmpstr,tmpstr2);
		strcat(tmpstr,".bmp");
		
		hbm = (HBITMAP)LoadImage(NULL, tmpstr, 
			IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);

		//HANDLE hf;
		//hf=CreateFile(tmpstr,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		//hbm=LoadBmpInFile(hf,0,GetFileSize(hf,NULL));
		//CloseHandle(hf);
		//	if(e->cpf->GetFileInfo(tmpstr,&p))
		//		hbm=LoadBmpInFile(hf,p.Begin,p.End-p.Begin);
		//else hbm=NULL;

		if(!hbm&&i==0)
		{
			startatzero=FALSE;
			continue;
		}
		if(!hbm)break;
		if(i<=1)
		{
			GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap
			size.x=bm.bmWidth;
			size.y=bm.bmHeight;
		}
			
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;

#ifdef LOAD_TO_SYSMEM
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
#else
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;//DDSCAPS_SYSTEMMEMORY;
#endif

		ddsd.dwHeight = size.y;
		ddsd.dwWidth = size.x;
		ddrval = lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSFrames[i-!startatzero], NULL );
		if(ddrval!=DD_OK)
		{
			strcpy(e->errormessage,"IDirectDraw::CreateSurface in Sprite2::Initialize2 1st failed: ");
			e->PrintDDError(e->errormessage,ddrval);
			e->OnError();
			//return(FALSE);
		}
		DDCopyBitmap((LPDIRECTDRAWSURFACE)lpDDSFrames[i-!startatzero], hbm, 0, 0, size.x, size.y);
		DeleteObject(hbm);
		//DDSetColorKey(lpDDSFrames[i-!startatzero], RGB(r,g,b));
		if(autocolorkey)DDSetColorKey((LPDIRECTDRAWSURFACE)lpDDSFrames[i-!startatzero], CLR_INVALID);//CLR_INVALID

	}

	if(i<=1)
	{
		for(i=0;;++i)
		{
			strcpy(tmpstr,bmfile);
			sprintf(tmpstr2,"%d",i);
			if(i<10)
			{
				strcat(tmpstr,"000");
			}
			else if(i<100)
			{
				strcat(tmpstr,"00");
			}
			else if(i<1000)
			{
				strcat(tmpstr,"0");
			}
			strcat(tmpstr,tmpstr2);
			strcat(tmpstr,".bmp");
			
			hbm = (HBITMAP)LoadImage(NULL, tmpstr, 
				IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
			
		//HANDLE hf;
		//hf=CreateFile(tmpstr,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		//hbm=LoadBmpInFile(hf,0,GetFileSize(hf,NULL));
		//CloseHandle(hf);
		//	if(e->cpf->GetFileInfo(tmpstr,&p))
		//		hbm=LoadBmpInFile(hf,p.Begin,p.End-p.Begin);
		//else hbm=NULL;

		if(!hbm&&i==0)
			{
				startatzero=FALSE;
				continue;
			}
			if(!hbm)break;
			if(i<=1)
			{
				GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap
				size.x=bm.bmWidth;
				size.y=bm.bmHeight;
			}
			
			ddsd.dwSize = sizeof( ddsd );
			ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;

#ifdef LOAD_TO_SYSMEM
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
#else
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;//DDSCAPS_SYSTEMMEMORY;
#endif

			ddsd.dwHeight = size.y;
			ddsd.dwWidth = size.x;
			ddrval = lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSFrames[i-!startatzero], NULL );
			if(ddrval!=DD_OK)
			{
				strcpy(e->errormessage,"IDirectDraw::CreateSurface in Sprite2::Initialize2 2nd failed: ");
				e->PrintDDError(e->errormessage,ddrval);
				e->OnError();
				//return(FALSE);
			}
			
			DDCopyBitmap((LPDIRECTDRAWSURFACE)lpDDSFrames[i-!startatzero], hbm, 0, 0, size.x, size.y);
			DeleteObject(hbm);
			//DDSetColorKey(lpDDSFrames[i-!startatzero], RGB(r,g,b));
			if(autocolorkey)DDSetColorKey((LPDIRECTDRAWSURFACE)lpDDSFrames[i-!startatzero], CLR_INVALID);//CLR_INVALID
			
		}
	}
	//CloseHandle(hf);


	if(startatzero)
		nframes=i;
	else
		nframes=i-1;
	
	if(nframes==0)
		return FALSE;
	enabled=TRUE;

	return TRUE;
}

BOOL Sprite2::UpdateBonus(int dtime)
{

	return TRUE;
}

BOOL Sprite2::UpdateNormal(int dtime)
{
	float angle3;
	VECTOR v;

	if(!enabled)
	{
		age=0;
		if(staticshield)staticshield->enabled=FALSE;
		if(trespawn>0&&trespawn<tdisabled)
		{
			enabled=TRUE;
			tdisabled=0;//tnow;
			e->SpawnSprite(this);
			//else e->SpawnSprite(this,FALSE);
		}
		else
		{
			//if(dtime>=40)dtime-=40;
			//if(tdisabled==0)tpdisabled=e->tnow;
			tdisabled+=dtime;
			return FALSE;
		}
	}
	else 
	{
		age+=dtime;
		if(tdisable>=0)
		{
			tdisable-=dtime;
			if(tdisable<=0)
			{
				if(enabled)
					Disable();
				tdisable=-1;
			}
		}
	}
	tframechange+=dtime;
	tlastfire+=dtime;
	tlastsmoke+=dtime;
	tlastswingchange+=dtime;
	tlastspecial+=dtime;

	if(tenablehitdetection>=0)
	{
		tenablehitdetection-=(int)dtime;
		if(tenablehitdetection<=0)
		{
			canhit=TRUE;
			canbehit=TRUE;
			tenablehitdetection=-1;
		}
	}

	energy+=energyloadspeed*(float)dtime/1000;
	if(energy>=maxenergy)energy=maxenergy;
	if(shieldstrenght>0)
		shieldstrenght+=shieldloadspeed*(float)dtime/1000;
	if(shieldstrenght>=maxshieldstrenght)shieldstrenght=maxshieldstrenght;

	if(homing&&target&&target->enabled)
	{
		angle=(float)(90-(atan2(((target->position.y+target->size.y/2)-(position.y+size.y/2))*-1,(target->position.x+target->size.x/2)-(position.x+size.x/2))/PI*180));
		if(angle<0)angle+=360;
		if(angle>=360)angle-=360;
		currentacceleration=maxacceleration;
	}

	Turn(currentturnspeed*(float)dtime/1000);
	//Accelerate(currentacceleration*(tnow-tplastupdate)/25);
	angle3=-angle+90;
	if(angle3<0)angle3+=360.0;
	speed.x+=(float)(cos(angle3/180*PI)*currentacceleration*(float)dtime/1000);
	speed.y+=(float)(sin(angle3/180*PI)*currentacceleration*(float)dtime/1000*-1);

	if(maxspeed!=0&&sqrt(speed.x*speed.x+speed.y*speed.y)>maxspeed)
	{
		angle3=(float)atan2(speed.y,speed.x);
		speed.x=(float)cos(angle3)*maxspeed;
		speed.y=(float)sin(angle3)*maxspeed;
	}


	position.x+=speed.x*(float)dtime/1000;
	position.y+=speed.y*(float)dtime/1000;
	

	if(anglevdep)
	{
		angle=(float)(90-(atan2(speed.y*-1,speed.x)/PI*180));
		if(angle<0)angle+=360;
		if(angle>=360)angle-=360;
	}

	if(swing)//Schwingung
	{
		if(tlastswingchange==-1)tlastswingchange=swingtime/2;
		if(tlastswingchange>=swingtime)
		{
			currentswing*=-1;
			tlastswingchange=0;
		}
		angle3=angle+swingangle;
		if(angle3>=360)angle3-=360;
		angle3=(90-angle3)/180*PI;
		v.x=(float)cos(angle3)*swingacceleration*currentswing;
		v.y=(float)sin(angle3)*swingacceleration*-1*currentswing;
		speed.x+=v.x*(float)dtime/1000;
		speed.y+=v.y*(float)dtime/1000;
	}


	SetFrame(dtime);
	if(smoking&&smoke&&enabled)
	{
		if(tlastsmoke>=SMOKEDELAY)
		{
			Sprite2 *tmp=new Sprite2;
			e->DuplicateSprite(tmp,smoke);
			e->AddSpriteEx(tmp);
			tmp->enabled=TRUE;
			tmp->position.x=position.x+size.x/2-tmp->size.x/2-(float)sin(angle/180*PI)*collisionrange;
			tmp->position.y=position.y+size.y/2-tmp->size.y/2+(float)cos(angle/180*PI)*collisionrange;
			tlastsmoke=0;
		}
	}
	
	if(staticshield && staticshield->enabled)
	{

		staticshield->position.x=(position.x+(float)size.x/2)-((float)staticshield->size.x/2)+(float)(sin((staticshield->angle)*PI/180)*(float)collisionrange);
		staticshield->position.y=(position.y+(float)size.y/2)-((float)staticshield->size.y/2)+(float)(cos((staticshield->angle)*PI/180)*(float)collisionrange*-1);
		staticshield->speed.x=0;
		staticshield->speed.y=0;
	}


	if(launchedfrom&&launchedfrom==friendsprite)
	{
		if(e->GetSpriteDistance(launchedfrom,this)>50)
			friendsprite=NULL;
	}

	//Für QuadDamage yes!!!
	if(type!=SPRITETYPE_BONUS)
	{
		if(tdamagemulti>0)
		{
			if(tdamagemulti<=(UINT)dtime)
			{
				tdamagemulti=0;
				damagemultiplicator=1.0f;
			}
			else
			{
				tdamagemulti-=(UINT)dtime;
			}
		}
	}

	return TRUE;
}

BOOL Sprite2::UpdateExplosion(int dtime)
{
	tframechange+=dtime;
	if(tframechange>=(UINT)(1000/animfps)/*e->tnow-tplastframechange>=1000/animfps*/)
	{
		if(currentframe<nframes)++currentframe;
		//tplastframechange=e->tnow;
		tframechange=0;
	}
	if(currentframe==nframes)Disable();

	return TRUE;
}

BOOL Sprite2::UpdateCpu(int dtime)
{
	float tmp;
	float destangle;
	Sprite2 *tmpsprite;

	if(cpu.selfchangemode&&(int)cpu.tstayinmode<=cpu.tcurrentmode)
	{
		cpu.tstayinmode=0;
		tmpsprite=e->GetNearestActor(this);
			if(e->SpriteGetDistance(this,tmpsprite)<300)
			{
				if(cpu.lastaimode!=AI_MOVE)cpu.tcurrentmode=0;
				cpu.lastaimode=cpu.aimode;
				cpu.aimode=AI_MOVE;
				//if(!cpu.destvalid)
				{
					cpu.dest=e->GetGoodPosition(this);
					cpu.destradius=60;
					//cpu.destvalid=TRUE;
					//cpu.tstayinmode=1000;
				}
			}
			else if(e->SpriteGetDistance(this,(tmpsprite=e->GetNearestBonus(this)))<300)
			{
				if(cpu.lastaimode!=AI_MOVE)cpu.tcurrentmode=0;
				cpu.lastaimode=cpu.aimode;
				cpu.aimode=AI_MOVE;
				//if(!cpu.destvalid)
				{
					cpu.dest.x=(int)tmpsprite->position.x;
					cpu.dest.y=(int)tmpsprite->position.y;
					cpu.destradius=60;
					//cpu.destvalid=TRUE;
				cpu.tstayinmode=100;
				}
			}
			else if(!e->GetNearestActor(this))
			{
				if(tmpsprite=e->GetNearestBonus(this))
				{
				cpu.tcurrentmode=0;
				cpu.lastaimode=cpu.aimode;
				cpu.aimode=AI_MOVE;
				//if(!cpu.destvalid)
					cpu.dest.x=(int)tmpsprite->position.x;
					cpu.dest.y=(int)tmpsprite->position.y;
					cpu.destradius=60;
					//cpu.destvalid=TRUE;
				cpu.tstayinmode=3000;
				}
				else
				{
				cpu.tcurrentmode=0;
				//cpu.lastaimode=cpu.aimode;
				cpu.aimode=AI_MOVE;
					cpu.dest.x=e->screenwidth/2+(int)e->ScreenPos.x;
					cpu.dest.y=e->screenheight/2+(int)e->ScreenPos.y;
					cpu.destradius=60;
					//cpu.destvalid=TRUE;
				cpu.tstayinmode=1000;
				}
			}
			else
			{
				if(cpu.lastaimode!=AI_ATTACK)cpu.tcurrentmode=0;
				cpu.lastaimode=cpu.aimode;
				cpu.aimode=AI_ATTACK;
				cpu.destvalid=FALSE;
				cpu.cputarget=e->GetNearestActor(this);
				cpu.tstayinmode=200;
				if(cpu.cputarget&&cpu.cputarget->hitpoints<cpu.cputarget->maxhitpoints/4)
					cpu.tstayinmode=3000;
			}

			if(cpu.aimode==AI_MOVE&&cpu.tcurrentmode>3000)
			{
				if(cpu.lastaimode!=AI_ATTACK)cpu.tcurrentmode=0;
				cpu.lastaimode=cpu.aimode;
				cpu.aimode=AI_ATTACK;
				cpu.cputarget=e->GetNearestActor(this);
				cpu.tstayinmode=2000;
			}
	}

	if(cpu.aimode==AI_FIRE &&target&&target->enabled&&weapon&&e->SpriteInScreen(this))
	{
		tmp=angle;
		angle=(float)(90-(atan2(((target->position.y+target->size.y/2)-(position.y+size.y/2))*-1,(target->position.x+target->size.x/2)-(position.x+size.x/2))/PI*180));
		if(angle>=360)angle-=360;
		if(angle<0)angle+=360;
		Fire(weapon->nlaunch);
		angle=tmp;
	}
	else if(cpu.aimode==AI_SMARTFIRE &&target&&target->enabled&&weapon&&e->SpriteInScreen(this))
	{
		tmp=angle;
		//angle=(float)(90-(atan2(((target->position.y+target->size.y/2)-(position.y+size.y/2))*-1,(target->position.x+target->size.x/2)-(position.x+size.x/2))/PI*180));
		//if(angle>=360)angle-=360;
		//if(angle<0)angle+=360;
		angle=e->GetFireAngle(this,target);
		Fire(weapon->nlaunch);
		angle=tmp;
	}
	else if(cpu.aimode==AI_MOVE)
	{
		currentturnspeed=0;
		destangle=(float)(90-(atan2((cpu.dest.y-position.y)*-1,cpu.dest.x-position.x)/PI*180));
		if(destangle<0)
			destangle+=360;
		//tmp=destangle;
		if(angle<destangle)
		{
			if(destangle-angle<180)
				currentturnspeed=turnspeed;
			else if(destangle-angle>180)
				currentturnspeed=-turnspeed;
		}
		else if(angle>destangle)
		{
			if(angle-destangle<180)
				currentturnspeed=-turnspeed;
			else if(angle-destangle>180)
				currentturnspeed=turnspeed;
		}

		if(GetAngleDiff(angle,destangle)<50)
		{
			currentacceleration=maxacceleration;
			if(GetAngleDiff(angle,destangle)<5)
			{
				currentturnspeed=0;
			}
		}
		else if(GetAngleDiff(angle,destangle)>160)
			currentacceleration=-0.25f*maxacceleration;

		if(sqrt(fabs(position.x-cpu.dest.x)*fabs(position.x-cpu.dest.x)+fabs(position.y-cpu.dest.y)*fabs(position.y-cpu.dest.y))<cpu.destradius)
		{
			cpu.tstayinmode=0;
			//cpu.destvalid=FALSE;
		}
	}

	else if(cpu.aimode==AI_ATTACK)
	{
		if(cpu.cputarget)
		{
		currentturnspeed=0;
		currentacceleration=0;
		destangle=e->GetFireAngle(this,cpu.cputarget);

		if(angle<destangle)
		{
			if(destangle-angle<180)
				currentturnspeed=turnspeed;
			else if(destangle-angle>180)
				currentturnspeed=-turnspeed;
		}
		else if(angle>destangle)
		{
			if(angle-destangle<180)
				currentturnspeed=-turnspeed;
			else if(angle-destangle>180)
				currentturnspeed=turnspeed;
		}

	if(GetAngleDiff(angle,destangle)>10&&e->SpriteGetDistance(this,cpu.cputarget)>400||GetSpeed()<50||e->GetApproachSpeed(this,cpu.cputarget)<50)
		currentacceleration=maxacceleration;
	
	if(GetAngleDiff(angle,destangle)<30&&e->SpriteGetDistance(this,cpu.cputarget)<200&&e->GetApproachSpeed(this,cpu.cputarget)>0)
		currentacceleration=-0.25f*maxacceleration;

	if(GetAngleDiff(angle,destangle)<5)
		{
			currentturnspeed=0;
			//currentacceleration=maxacceleration;
			if(weapon)
				Fire(weapon->nlaunch);
		}
		}
		if(!cpu.cputarget||!cpu.cputarget->enabled)cpu.tstayinmode=0;
	}
	cpu.tcurrentmode+=dtime;
	return TRUE;
}

BOOL Sprite2::UpdateHuman(int dtime)
{
	return TRUE;
}

void Sprite2::Turn(float degs)
{
	if(angle>=360)angle-=360;
	else if(angle<0)angle+=360;
	
	
	angle+=degs;
	//angle=(angle<0) ? 
	if(angle<0)
	{
		angle+=360;
	}
	else if(angle>=360)
	{
		angle-=360;
	}
}

void Sprite2::Accelerate(float dir,int dtime)
{
	if(!enabled)return;
	float angle3;
	angle3=-angle+90;
	if(angle3<0)angle3+=360.0;
	speed.x=(float)(speed.x+cos(angle3/180*PI)*maxacceleration*(float)dtime/1000*dir);
	speed.y=(float)(speed.y+sin(angle3/180*PI)*maxacceleration*(float)dtime/1000*-1*dir);
}
	

void Sprite2::OnCollisionNormal(Sprite2 *s)
{

	if(!s->enabled)return;

	//if(!s->canbehit)return;
	if(!canhit || (!canbehit && !s->canbehit))return;
	if(s->type==SPRITETYPE_EXPLOSION||s->type==SPRITETYPE_BONUS)return;
	//if(s->friendsprite==this || friendsprite==s)return;

	if(launchedfrom)
		if(launchedfrom->launchedfrom)s->attacker=launchedfrom->launchedfrom;
		else s->attacker=launchedfrom;
	//else s->attacker=this;

	if(s->staticshield)
	{
		float a2=(float)atan2((s->position.y+s->size.y/2)-(position.y+size.y/2),(s->position.x+s->size.x/2)-(position.x+size.x/2));
		if(!anglevdep||type==SPRITETYPE_CPU||type==SPRITETYPE_HUMAN)
			s->staticshield->angle=a2/PI*180+180+90;
		else s->staticshield->angle=angle+180;
		if(s->staticshield->angle>=360)s->staticshield->angle-=360;
	}
	if(s->shieldstrenght>0&&shieldstrenght>0)
	{
		float a=(float)atan2((s->position.y+s->size.y/2)-(position.y+size.y/2),(s->position.x+s->size.x/2)-(position.x+size.x/2));
		if(s->hitforcemodifier>0)
		{
		s->speed.x=(float)cos(a)*100*100*hitforce*s->hitforcemodifier;
		s->speed.y=(float)sin(a)*100*100*hitforce*s->hitforcemodifier;
		}
		if(indestructible)
			s->ChangeHitpoints(-hitdamage);
		else
			s->ChangeHitpoints(-SHIELDDAMAGE);
	}
	else if((type==SPRITETYPE_CPU||type==SPRITETYPE_HUMAN)&&(s->shieldstrenght>0||shieldstrenght>0))
	{
		float a=(float)atan2((s->position.y+s->size.y/2)-(position.y+size.y/2),(s->position.x+s->size.x/2)-(position.x+size.x/2));
		if(s->hitforcemodifier>0)
		{
		s->speed.x=(float)cos(a)*100*100*hitforce*s->hitforcemodifier;
		s->speed.y=(float)sin(a)*100*100*hitforce*s->hitforcemodifier;
		}
		s->ChangeHitpoints(-SHIELDDAMAGE);
	}
	else
	{
		s->speed.x+=speed.x/100*100*hitforce*s->hitforcemodifier;
		s->speed.y+=speed.y/100*100*hitforce*s->hitforcemodifier;
		s->ChangeHitpoints(-hitdamage);
	}
}

void Sprite2::OnCollisionBonus(Sprite2 *s)
{
		if(!s->enabled)return;
		if(!s->canbehit)return;
		if(!s->receivebonus)return;

		if(tfiredelay!=0)s->tfiredelay=tfiredelay;
		s->ChangeHitpoints(-hitdamage);
		s->shieldstrenght+=shieldstrenght;

		//if(s->weapon==weaponsprite)++s->launchnumber;
		//else if(launchnumber!=0)s->launchnumber=launchnumber;

		if(weapon)
		{
			s->weapon=weapon;
			s->ammo=ammo;
			s->tlastfire=0;
		}
		if(soundnr>=0)e->soundsys.Play(soundnr,FALSE);

		if(damagemultiplicator!=1)
		{
			s->damagemultiplicator=damagemultiplicator;
			s->tdamagemulti=tdamagemulti;
		}

		Disable();
}

float Sprite2::GetVAngle()
{
	float a;
	a=(float)(90-(atan2(speed.y*-1,speed.x)/PI*180));
	if(a<0)angle+=360;
	if(a>=360)angle-=360;

	return(a);
}

float Sprite2::GetSpeed()
{
	return (float)sqrt(speed.x*speed.x+speed.y*speed.y);
}

void Sprite2::ChangeHitpoints(float d)
{
	float hp=hitpoints;

	if(d>0)
	{
		hitpoints+=d;
		if(hitpoints>maxhitpoints)hitpoints=maxhitpoints;
		if(hitpoints>maxhitpoints/SMOKEHITPOINTDIVISOR)smoking=FALSE;
		return;
	}
	if(shieldstrenght+hitpoints+d<=0 && indestructible==FALSE)
	{
		Disable();
		hitpoints=0;
		shieldstrenght=0;
	}
	else 
	{
		attacker=NULL;
		if(shieldstrenght>0 && staticshield && d<0)
		{
			if(staticshield->soundnr>=0)e->soundsys.Play(staticshield->soundnr,FALSE);
			staticshield->position.x=(position.x+size.x/2)-(staticshield->size.x/2);
			staticshield->position.y=(position.x+size.y/2)-(staticshield->size.y/2);
			staticshield->enabled=TRUE;
			staticshield->tdisable=SHIELDTIME;
		}
		if(indestructible==FALSE)
		{
			if(shieldstrenght>0)
			{
				shieldstrenght+=d;
				if(shieldstrenght<0)
				{
					hitpoints+=shieldstrenght;
					shieldstrenght=0;
					e->OnSpriteShieldDown(this);
				}
			}
			else
			{
				hitpoints+=d;
			}
		}
		if(hp>maxhitpoints/SMOKEHITPOINTDIVISOR&&hitpoints<maxhitpoints/SMOKEHITPOINTDIVISOR)
			e->OnSpriteHullCritical(this);

		if(smoke && hitpoints<maxhitpoints/SMOKEHITPOINTDIVISOR)
		{
			smoking=TRUE;
		}else smoking=FALSE;
	}
}