#include "engine.h"

void Engine2::PrintDDError(char *buffer,HRESULT ddrval)
{
	switch (ddrval)
	{
	case DD_OK:
		strcat(buffer,"DD_OK");
		break;
	case DDERR_ALREADYINITIALIZED:
		strcat(buffer,"DDERR_ALREADYINITIALIZED");
		break;
	case DDERR_BLTFASTCANTCLIP:
		strcat(buffer,"DDERR_BLTFASTCANTCLIP");
		break;
	case DDERR_CANNOTATTACHSURFACE:
		strcat(buffer,"DDERR_CANNOTATTACHSURFACE");
		break;
	case DDERR_CANNOTDETACHSURFACE:
		strcat(buffer,"DDERR_CANNOTDETACHSURFACE");
		break;
	case DDERR_CANTCREATEDC:
		strcat(buffer,"DDERR_CANTCREATEDC");
		break;
	case DDERR_CANTDUPLICATE:
		strcat(buffer,"DDERR_CANTDUPLICATE");
		break;
	case DDERR_CANTLOCKSURFACE:
		strcat(buffer,"DDERR_CANTLOCKSURFACE");
		break;
	case DDERR_CANTPAGELOCK:
		strcat(buffer,"DDERR_CANTPAGELOCK");
		break;
	case DDERR_CANTPAGEUNLOCK:
		strcat(buffer,"DDERR_CANTPAGEUNLOCK");
		break;
	case DDERR_CLIPPERISUSINGHWND:
		strcat(buffer,"DDERR_CLIPPERISUSINGHWND");
		break;
	case DDERR_COLORKEYNOTSET:
		strcat(buffer,"DDERR_COLORKEYNOTSET");
		break;
	case DDERR_CURRENTLYNOTAVAIL:
		strcat(buffer,"DDERR_CURRENTLYNOTAVAIL");
		break;
	case DDERR_DCALREADYCREATED:
		strcat(buffer,"DDERR_DCALREADYCREATED");
		break;
	case DDERR_DEVICEDOESNTOWNSURFACE:
		strcat(buffer,"DDERR_DEVICEDOESNTOWNSURFACE");
		break;
	case DDERR_DIRECTDRAWALREADYCREATED:
		strcat(buffer,"DDERR_DIRECTDRAWALREADYCREATED");
		break;
	case DDERR_EXCEPTION:
		strcat(buffer,"DDERR_EXCEPTION");
		break;
	case DDERR_EXCLUSIVEMODEALREADYSET:
		strcat(buffer,"DDERR_EXCLUSIVEMODEALREADYSET");
		break;
	case DDERR_GENERIC:
		strcat(buffer,"DDERR_GENERIC");
		break;
	case DDERR_HEIGHTALIGN:
		strcat(buffer,"DDERR_HEIGHTALIGN");
		break;
	case DDERR_HWNDALREADYSET:
		strcat(buffer,"DDERR_HWNDALREADYSET");
		break;
	case DDERR_HWNDSUBCLASSED:
		strcat(buffer,"DDERR_HWNDSUBCLASSED");
		break;
	case DDERR_IMPLICITLYCREATED:
		strcat(buffer,"DDERR_IMPLICITLYCREATED");
		break;
	case DDERR_INCOMPATIBLEPRIMARY:
		strcat(buffer,"DDERR_INCOMPATIBLEPRIMARY");
		break;
	case DDERR_INVALIDCAPS:
		strcat(buffer,"DDERR_INVALIDCAPS");
		break;
	case DDERR_INVALIDCLIPLIST:
		strcat(buffer,"DDERR_INVALIDCLIPLIST");
		break;
	case DDERR_INVALIDDIRECTDRAWGUID:
		strcat(buffer,"DDERR_INVALIDDIRECTDRAWGUID");
		break;
	case DDERR_INVALIDMODE:
		strcat(buffer,"DDERR_INVALIDMODE");
		break;
	case DDERR_INVALIDOBJECT:
		strcat(buffer,"DDERR_INVALIDOBJECT");
		break;
	case DDERR_INVALIDPARAMS:
		strcat(buffer,"DDERR_INVALIDPARAMS");
		break;
	case DDERR_INVALIDPIXELFORMAT:
		strcat(buffer,"DDERR_INVALIDPIXELFORMAT");
		break;
	case DDERR_INVALIDPOSITION:
		strcat(buffer,"DDERR_INVALIDPOSITION");
		break;
	case DDERR_INVALIDRECT:
		strcat(buffer,"DDERR_INVALIDRECT");
		break;
	case DDERR_INVALIDSURFACETYPE:
		strcat(buffer,"DDERR_INVALIDSURFACETYPE");
		break;
	case DDERR_LOCKEDSURFACES:
		strcat(buffer,"DDERR_LOCKEDSURFACES");
		break;
	case DDERR_MOREDATA:
		strcat(buffer,"DDERR_MOREDATA");
		break;
	case DDERR_NO3D:
		strcat(buffer,"DDERR_NO3D");
		break;
	case DDERR_NOALPHAHW:
		strcat(buffer,"DDERR_NOALPHAHW");
		break;
	case DDERR_NOBLTHW:
		strcat(buffer,"DDERR_NOBLTHW");
		break;
	case DDERR_NOCLIPLIST:
		strcat(buffer,"DDERR_NOCLIPLIST");
		break;
	case DDERR_NOCLIPPERATTACHED:
		strcat(buffer,"DDERR_NOCLIPPERATTACHED");
		break;
	case DDERR_NOCOLORCONVHW:
		strcat(buffer,"DDERR_NOCOLORCONVHW");
		break;
	case DDERR_NOCOLORKEY:
		strcat(buffer,"DDERR_NOCOLORKEY");
		break;
	case DDERR_NOCOLORKEYHW:
		strcat(buffer,"DDERR_NOCOLORKEYHW");
		break;
	case DDERR_NOCOOPERATIVELEVELSET:
		strcat(buffer,"DDERR_NOCOOPERATIVELEVELSET");
		break;
	case DDERR_NODC:
		strcat(buffer,"DDERR_NODC");
		break;
	case DDERR_NODDROPSHW:
		strcat(buffer,"DDERR_NODDROPSHW");
		break;
	case DDERR_NODIRECTDRAWHW:
		strcat(buffer,"DDERR_NODIRECTDRAWHW");
		break;
	case DDERR_NODIRECTDRAWSUPPORT:
		strcat(buffer,"DDERR_NODIRECTDRAWSUPPORT");
		break;
	case DDERR_NOEMULATION:
		strcat(buffer,"DDERR_NOEMULATION");
		break;
	case DDERR_NOEXCLUSIVEMODE:
		strcat(buffer,"DDERR_NOEXCLUSIVEMODE");
		break;
	case DDERR_NOFLIPHW:
		strcat(buffer,"DDERR_NOFLIPHW");
		break;
	case DDERR_NOFOCUSWINDOW:
		strcat(buffer,"DDERR_NOFOCUSWINDOW");
		break;
	case DDERR_NOGDI:
		strcat(buffer,"DDERR_NOGDI");
		break;
	case DDERR_NOHWND:
		strcat(buffer,"DDERR_NOHWND");
		break;
	case DDERR_NOMIPMAPHW:
		strcat(buffer,"DDERR_NOMIPMAPHW");
		break;
	case DDERR_NOMIRRORHW:
		strcat(buffer,"DDERR_NOMIRRORHW");
		break;
	case DDERR_NONONLOCALVIDMEM:
		strcat(buffer,"DDERR_NONONLOCALVIDMEM");
		break;
	case DDERR_NOOPTIMIZEHW:
		strcat(buffer,"DDERR_NOOPTIMIZEHW");
		break;
	case DDERR_NOOVERLAYDEST:
		strcat(buffer,"DDERR_NOOVERLAYDEST");
		break;
	case DDERR_NOOVERLAYHW:
		strcat(buffer,"DDERR_NOOVERLAYHW");
		break;
	case DDERR_NOPALETTEATTACHED:
		strcat(buffer,"DDERR_NOPALETTEATTACHED");
		break;
	case DDERR_NOPALETTEHW:
		strcat(buffer,"DDERR_NOPALETTEHW");
		break;
	case DDERR_NORASTEROPHW:
		strcat(buffer,"DDERR_NORASTEROPHW");
		break;
	case DDERR_NOROTATIONHW:
		strcat(buffer,"DDERR_NOROTATIONHW");
		break;
	case DDERR_NOSTRETCHHW:
		strcat(buffer,"DDERR_NOSTRETCHHW");
		break;
	case DDERR_NOT4BITCOLOR:
		strcat(buffer,"DDERR_NOT4BITCOLOR");
		break;
	case DDERR_NOT4BITCOLORINDEX:
		strcat(buffer,"DDERR_NOT4BITCOLORINDEX");
		break;
	case DDERR_NOT8BITCOLOR:
		strcat(buffer,"DDERR_NOT8BITCOLOR");
		break;
	case DDERR_NOTAOVERLAYSURFACE:
		strcat(buffer,"DDERR_NOTAOVERLAYSURFACE");
		break;
	case DDERR_NOTEXTUREHW:
		strcat(buffer,"DDERR_NOTEXTUREHW");
		break;
	case DDERR_NOTFLIPPABLE:
		strcat(buffer,"DDERR_NOTFLIPPABLE");
		break;
	case DDERR_NOTFOUND:
		strcat(buffer,"DDERR_NOTFOUND");
		break;
	case DDERR_NOTINITIALIZED:
		strcat(buffer,"DDERR_NOTINITIALIZED");
		break;
	case DDERR_NOTLOADED:
		strcat(buffer,"DDERR_NOTLOADED");
		break;
	case DDERR_NOTLOCKED:
		strcat(buffer,"DDERR_NOTLOCKED");
		break;
	case DDERR_NOTPAGELOCKED:
		strcat(buffer,"DDERR_NOTPAGELOCKED");
		break;
	case DDERR_NOTPALETTIZED:
		strcat(buffer,"DDERR_NOTPALETTIZED");
		break;
	case DDERR_NOVSYNCHW:
		strcat(buffer,"DDERR_NOVSYNCHW");
		break;
	case DDERR_NOZBUFFERHW:
		strcat(buffer,"DDERR_NOZBUFFERHW");
		break;
	case DDERR_NOZOVERLAYHW:
		strcat(buffer,"DDERR_NOZOVERLAYHW");
		break;
	case DDERR_OUTOFCAPS:
		strcat(buffer,"DDERR_OUTOFCAPS");
		break;
	case DDERR_OUTOFMEMORY:
		strcat(buffer,"DDERR_OUTOFMEMORY");
		break;
	case DDERR_OUTOFVIDEOMEMORY:
		strcat(buffer,"DDERR_OUTOFVIDEOMEMORY");
		break;
	case DDERR_OVERLAYCANTCLIP:
		strcat(buffer,"DDERR_OVERLAYCANTCLIP");
		break;
	case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
		strcat(buffer,"DDERR_OVERLAYCOLORKEYONLYONEACTIVE");
		break;
	case DDERR_OVERLAYNOTVISIBLE:
		strcat(buffer,"DDERR_OVERLAYNOTVISIBLE");
		break;
	case DDERR_PALETTEBUSY:
		strcat(buffer,"DDERR_PALETTEBUSY");
		break;
	case DDERR_PRIMARYSURFACEALREADYEXISTS:
		strcat(buffer,"DDERR_PRIMARYSURFACEALREADYEXISTS");
		break;
	case DDERR_REGIONTOOSMALL:
		strcat(buffer,"DDERR_REGIONTOOSMALL");
		break;
	case DDERR_SURFACEALREADYATTACHED:
		strcat(buffer,"DDERR_SURFACEALREADYATTACHED");
		break;
	case DDERR_SURFACEALREADYDEPENDENT:
		strcat(buffer,"DDERR_SURFACEALREADYDEPENDENT");
		break;
	case DDERR_SURFACEBUSY:
		strcat(buffer,"DDERR_SURFACEBUSY");
		break;
	case DDERR_SURFACEISOBSCURED:
		strcat(buffer,"DDERR_SURFACEISOBSCURED");
		break;
	case DDERR_SURFACELOST:
		strcat(buffer,"DDERR_SURFACELOST");
		break;
	case DDERR_SURFACENOTATTACHED:
		strcat(buffer,"DDERR_SURFACENOTATTACHED");
		break;
	case DDERR_TOOBIGHEIGHT:
		strcat(buffer,"DDERR_TOOBIGHEIGHT");
		break;
	case DDERR_TOOBIGSIZE:
		strcat(buffer,"DDERR_TOOBIGSIZE");
		break;
	case DDERR_TOOBIGWIDTH:
		strcat(buffer,"DDERR_TOOBIGWIDTH");
		break;
	case DDERR_UNSUPPORTED:
		strcat(buffer,"DDERR_UNSUPPORTED");
		break;
	case DDERR_UNSUPPORTEDFORMAT:
		strcat(buffer,"DDERR_UNSUPPORTEDFORMAT");
		break;
	case DDERR_UNSUPPORTEDMASK:
		strcat(buffer,"DDERR_UNSUPPORTEDMASK");
		break;
	case DDERR_UNSUPPORTEDMODE:
		strcat(buffer,"DDERR_UNSUPPORTEDMODE");
		break;
	case DDERR_VERTICALBLANKINPROGRESS:
		strcat(buffer,"DDERR_VERTICALBLANKINPROGRESS");
		break;
	case DDERR_VIDEONOTACTIVE:
		strcat(buffer,"DDERR_VIDEONOTACTIVE");
		break;
	case DDERR_WASSTILLDRAWING:
		strcat(buffer,"DDERR_WASSTILLDRAWING");
		break;
	case DDERR_WRONGMODE:
		strcat(buffer,"DDERR_WRONGMODE");
		break;
	case DDERR_XALIGN:
		strcat(buffer,"DDERR_XALIGN");
		break;
	default:
		strcat(buffer,"Unknown Error");
		break;
	}
}

void Engine2::PrintDSError(char *buffer,HRESULT ddrval)
{
	switch(ddrval)
	{
	case DS_OK:
		strcat(buffer,"DS_OK");
		break;
	case DSERR_ALLOCATED:
		strcat(buffer,"DSERR_ALLOCATED");
		break;
	case DSERR_ALREADYINITIALIZED:
		strcat(buffer,"DSERR_ALREADYINITIALIZED");
		break;
	case DSERR_BADFORMAT:
		strcat(buffer,"DSERR_BADFORMAT");
		break;
	case DSERR_BUFFERLOST:
		strcat(buffer,"DSERR_BUFFERLOST");
		break;
	case DSERR_CONTROLUNAVAIL:
		strcat(buffer,"DSERR_CONTROLUNAVAIL");
		break;
	case DSERR_GENERIC:
		strcat(buffer,"DSERR_GENERIC");
		break;
	case DSERR_INVALIDCALL:
		strcat(buffer,"DSERR_INVALIDCALL");
		break;
	case DSERR_INVALIDPARAM:
		strcat(buffer,"DSERR_INVALIDPARAM");
		break;
	case DSERR_NOAGGREGATION:
		strcat(buffer,"DSERR_NOAGGREGATION");
		break;
	case DSERR_NODRIVER:
		strcat(buffer,"DSERR_NODRIVER");
		break;
	case DSERR_NOINTERFACE:
		strcat(buffer,"DSERR_NOINTERFACE");
		break;
	case DSERR_OTHERAPPHASPRIO:
		strcat(buffer,"DSERR_OTHERAPPHASPRIO");
		break;
	case DSERR_OUTOFMEMORY:
		strcat(buffer,"DSERR_OUTOFMEMORY");
		break;
	case DSERR_PRIOLEVELNEEDED:
		strcat(buffer,"DSERR_PRIOLEVELNEEDED");
		break;
	case DSERR_UNINITIALIZED:
		strcat(buffer,"DSERR_UNINITIALIZED");
		break;
	case DSERR_UNSUPPORTED:
		strcat(buffer,"DSERR_UNSUPPORTED");
		break;
	default:
		strcat(buffer,"Unknown Error");
		break;
	}
}

void Engine2::PrintDIError(char *buffer,HRESULT ddrval)
{
	switch(ddrval)
	{
	case DI_BUFFEROVERFLOW:
		strcat(buffer,"DI_BUFFEROVERFLOW");
		break;
	case DI_DOWNLOADSKIPPED:
		strcat(buffer,"DI_DOWNLOADSKIPPED");
		break;
	case DI_EFFECTRESTARTED:
		strcat(buffer,"DI_EFFECTRESTARTED");
		break;
	case DI_OK:
		strcat(buffer,"DI_OK");
		break;
	case DI_POLLEDDEVICE:
		strcat(buffer,"DI_POLLEDDEVICE");
		break;
	case DI_TRUNCATED:
		strcat(buffer,"DI_TRUNCATED");
		break;
	case DI_TRUNCATEDANDRESTARTED:
		strcat(buffer,"DI_TRUNCATEDANDRESTARTED");
		break;
	case DIERR_ACQUIRED:
		strcat(buffer,"DIERR_ACQUIRED");
		break;
	case DIERR_ALREADYINITIALIZED:
		strcat(buffer,"DIERR_ALREADYINITIALIZED");
		break;
	case DIERR_BADDRIVERVER:
		strcat(buffer,"DIERR_BADDRIVERVER");
		break;
	case DIERR_BETADIRECTINPUTVERSION:
		strcat(buffer,"DIERR_BETADIRECTINPUTVERSION");
		break;
	case DIERR_DEVICEFULL:
		strcat(buffer,"DIERR_DEVICEFULL");
		break;
	case DIERR_HASEFFECTS:
		strcat(buffer,"DIERR_HASEFFECTS");
		break;
	case DIERR_GENERIC:
		strcat(buffer,"DIERR_GENERIC");
		break;
	case DIERR_HANDLEEXISTS:
		strcat(buffer,"DIERR_HANDLEEXISTS");
		break;
	case DIERR_INCOMPLETEEFFECT:
		strcat(buffer,"DIERR_INCOMPLETEEFFECT");
		break;
	case DIERR_INPUTLOST:
		strcat(buffer,"DIERR_INPUTLOST");
		break;
	case DIERR_INVALIDPARAM:
		strcat(buffer,"DIERR_INVALIDPARAM");
		break;
	case DIERR_MOREDATA:
		strcat(buffer,"DIERR_MOREDATA");
		break;
	case DIERR_NOAGGREGATION:
		strcat(buffer,"DIERR_NOAGGREGATION");
		break;
	case DIERR_NOINTERFACE:
		strcat(buffer,"DIERR_NOINTERFACE");
		break;
	case DIERR_NOTACQUIRED:
		strcat(buffer,"DIERR_NOTACQUIRED");
		break;
	case DIERR_NOTBUFFERED:
		strcat(buffer,"DIERR_NOTBUFFERED");
		break;
	case DIERR_NOTDOWNLOADED:
		strcat(buffer,"DIERR_NOTDOWNLOADED");
		break;
	case DIERR_NOTEXCLUSIVEACQUIRED:
		strcat(buffer,"DIERR_NOTEXCLUSIVEACQUIRED");
		break;
	case DIERR_NOTFOUND:
		strcat(buffer,"DIERR_NOTFOUND");
		break;
	case DIERR_NOTINITIALIZED:
		strcat(buffer,"DIERR_NOTINITIALIZED");
		break;
	case DIERR_OLDDIRECTINPUTVERSION:
		strcat(buffer,"DIERR_OLDDIRECTINPUTVERSION");
		break;
	case DIERR_OUTOFMEMORY:
		strcat(buffer,"DIERR_OUTOFMEMORY");
		break;
	case DIERR_REPORTFULL:
		strcat(buffer,"DIERR_REPORTFULL");
		break;
	case DIERR_UNPLUGGED:
		strcat(buffer,"DIERR_UNPLUGGED");
		break;
	case DIERR_UNSUPPORTED:
		strcat(buffer,"DIERR_UNSUPPORTED");
		break;
	case E_PENDING:
		strcat(buffer,"E_PENDING");
		break;
	default:
		strcat(buffer,"Unknown Error");
		break;
	}
}

BOOL Engine2::LoadPrototypes(char *filename)
{
	if(!initialized)return(FALSE);
	int i,totalsprites;
	char tmpstr[64],tmpstr2[64];
	char istr[16];

	//RECT rect;
	//rect.right=screenwidth;
	//rect.left=0;
	//rect.top=0;
	//rect.bottom=screenheight;

	totalsprites=GetPrivateProfileIntCurrentDir(filename,"sprites","numsprites",0);
	
	for(i=0;i<MAXPROTOTYPES;++i)prototypes[i]=new Sprite2;

	//if(fullscreen)
		FullBlt(lpDDSBackBuffer,lpDDSPrimary);
	//else
	//{
	//	GetWindowRect(hwnd,&rect);
	//	lpDDSBackBuffer->Blt(NULL,lpDDSPrimary,&rect,DDBLT_WAIT,NULL);
	//}

	for(i=0;i<totalsprites;++i)
	{
		
	//if(fullscreen)
		FullBlt(lpDDSPrimary,lpDDSBackBuffer);
	//else
	//{
	//	GetWindowRect(hwnd,&rect);
	//	lpDDSPrimary->Blt(&rect,lpDDSBackBuffer,NULL,DDBLT_WAIT,NULL);
	//}

		strcpy(tmpstr,"Loading Sprite#");
		sprintf(tmpstr2,"%d",i);
		strcat(tmpstr,tmpstr2);
		strcat(tmpstr," of ");
		sprintf(tmpstr2,"%d",totalsprites);
		strcat(tmpstr,tmpstr2);
		Write2Surface(lpDDSPrimary,tmpstr,5,5);

		strcpy(tmpstr,"sprite");
		sprintf(istr,"%d",i);
		strcat(tmpstr,istr);
		GetPrivateProfileStringCurrentDir(filename,"sprites",tmpstr,tmpstr2,64);

		if(stricmp(tmpstr2,"none")!=0)
		{
		if(!LoadSprite(prototypes[i],"sprites.ini",tmpstr2))
		{
			strcpy(errormessage,"Error while loading Sprite");
			OnError();
			delete prototypes[i];
			prototypes[i]=NULL;
		}
		}
		
		
	}

	for(i=0;i<MAXPROTOTYPES;++i)
	{
		if(i>=GetPrivateProfileIntCurrentDir(filename,"sprites","numsprites",0))
		{
			delete prototypes[i];
			prototypes[i]=NULL;
		}
	}
	
	deleteproc=TRUE;
	return(TRUE);

}
	
BOOL Engine2::SetBackGround(char *filename)
{
	if(!initialized)return FALSE;
	
	DDSURFACEDESC       ddsd;
	HRESULT ddrval;
	HBITMAP hbm;
	BITMAP bm;
	LPDIRECTDRAWSURFACE3 lpDDSTmp;
	//RECT destrect,srcrect;
	
	hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	
	if(!hbm)
	{
		return FALSE;
	}
	strcpy(backgroundimagefile,filename);
	if(lpDDSBackGround)
	{
		lpDDSBackGround->Release();
		lpDDSBackGround=NULL;
	}

	GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap
	
	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
	ddsd.dwHeight = bm.bmHeight;
	ddsd.dwWidth = bm.bmWidth;
	ddrval=lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSTmp, NULL );

	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;//|DDSCAPS_SYSTEMMEMORY;
	ddsd.dwHeight = screenheight;
	ddsd.dwWidth = screenwidth;
	ddrval=lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSBackGround, NULL );

	DDCopyBitmap((LPDIRECTDRAWSURFACE)lpDDSTmp, hbm, 0, 0,bm.bmWidth,bm.bmHeight);

	lpDDSBackGround->Blt(NULL,lpDDSTmp,NULL,DDBLT_WAIT,NULL);
	lpDDSTmp->Release();
	//strcpy(backgroundfile,filename);
	return TRUE;

}
	
POINT Engine2::GetCenterPos(BaseItem *bi)
{
	POINT p;
	p.x=0;
	p.y=0;
	if(!bi)return p;
	if(bi->noscroll)
	{
		p.x=screenwidth/2-bi->size.x/2;
		p.y=screenheight/2-bi->size.y/2;
	}
	else
	{
		p.x=screenwidth/2-bi->size.x/2-(int)ScreenPos.x;
		p.y=screenheight/2-bi->size.y/2-(int)ScreenPos.y;
	}
	return p;

}

BOOL Engine2::AddSprite(Sprite2 *s)
{
	int i=0;
	if(currentnumsprites>=MAXSPRITES)
	{
		strcpy(errormessage,"Error in Engine2::AddSprite: too many Sprites");
		OnError();
		return FALSE;
	}
	while(sprites[i]!=NULL)++i;
	sprites[i]=s;
	sprites[i]->e=this;
	return(TRUE);
}
	
void Engine2::FullBlt(LPDIRECTDRAWSURFACE3 to,LPDIRECTDRAWSURFACE3 from)
{
	RECT rect;
	if(to==lpDDSPrimary&&!fullscreen)
	{
		GetWindowRect(hwnd,&rect);
		to->Blt(&rect,from, NULL, DDBLTFAST_NOCOLORKEY |DDBLT_WAIT ,NULL);

	}
	else if(from==lpDDSPrimary&&!fullscreen)
	{
		GetWindowRect(hwnd,&rect);
		to->Blt(NULL,from, &rect, DDBLTFAST_NOCOLORKEY |DDBLT_WAIT ,NULL);
	}
	else
		to->Blt(NULL,from, NULL, DDBLTFAST_NOCOLORKEY |DDBLT_WAIT ,NULL);
}

BOOL Engine2::AddItem(BaseItem *i)
{
	int n=0;
	if(currentnumitems>=MAXITEMS)
	{
		strcpy(errormessage,"Error in Engine2::AddItem: too many Items");
		OnError();
		return FALSE;
	}
	while(items[n]!=NULL)++n;
	items[n]=i;
	items[n]->e=this;
	return(TRUE);
}
		

POINT Engine2::GetGoodPosition(Sprite2 *s)
{
	int i=0;
	POINT p;
	float dx,dy;
	Sprite2 *nearestsprite;
//	float a;
	
	nearestsprite=GetNearestActor(s);
//	a=(float)atan2(s->position.y-nearestsprite->position.y,s->position.x-nearestsprite->position.x);
	//if(a<0)
	//	a+=360;

	dx=s->position.x-nearestsprite->position.x;
	dy=s->position.y-nearestsprite->position.y;

//	dx=(float)cos(a)*400;
//	dy=(float)sin(a)*400;
	
	p.x=(int)(s->position.x+dx);
	p.y=(int)(s->position.y+dy);
	
	if(p.x<0)
	{
		//p.x=s->position.x-dx;
		//p.x=screenwidth+p.x-s->size.x/2;
		p.x=screenwidth/2;
	}
	if(p.x+s->size.x>(int)screenwidth)
	{
		//p.x=s->position.x-dx;
		//p.x-=screenwidth;
		p.x=screenwidth/2;
	}
	if(p.y<0)
	{
		//p.y=s->position.y-dy;
		//p.y=screenheight+p.y-s->size.y/2;
		p.y=screenheight/2;
	}
	if(p.y+s->size.y>(int)screenheight)
	{
		//p.y=s->position.y-dy;
		//p.y-=screenheight;
		p.y=screenheight/2;
	}

/*	do{
		p.x=random(0,(int)(screenwidth-s->size.x));
		p.y=random(0,(int)(screenheight-s->size.y));
		++i;
	}while(GetDistance(p.x,p.y,)<300 && i<100);*/
	
	return(p);
}

int Engine2::Start()
{
	MSG msg;
	memset(&msg,0,sizeof(msg));
	tnow=timeGetTime();
	tplastupdate=tnow;
	starttime=tnow;
	
	while( 1 )	//message loop
    {	
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
			if( !GetMessage( &msg, NULL, 0, 0 ) )
			{
				return msg.wParam;
			}
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else if(bActive)
		{
			Update();
		}
        else
        {
            // make sure we go to sleep if we have nothing else to do
            WaitMessage();
        }
    }
    return msg.wParam;

}

Event *Engine2::CreateEvent(void(*eventproc)(),UINT interval,BOOL repeat,UINT t2raise)
{
	Event *e;
	e=new Event;
	e->event=eventproc;
	e->tinterval=interval;
	e->t2raise=t2raise;
	e->repeat=repeat;

	AddEvent(e);
	return e;
}

BOOL Engine2::AddEvent(Event *event)
{
	int i;
	for(i=0;i<MAXEVENTS;++i)
	{
		if(!events[i])
		{
			events[i]=event;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL Engine2::ChangeDisplayMode(int x,int y,int bpp)
{
	HRESULT hres;
	while((hres=lpDD->SetDisplayMode((DWORD)x,(DWORD)y,(DWORD)bpp))==DDERR_WASSTILLDRAWING);
	if(hres!=DD_OK)
	{
		return FALSE;
	}

	screenwidth=x;
	screenheight=y;

	return TRUE;
}

void Engine2::DeleteEvent(int i)
{
	if(events[i])
	{
		delete events[i];
		events[i]=NULL;
	}
}

BOOL Engine2::AddSpriteEx(Sprite2 *s,UINT pos)
{
	if(pos==ADD_NORMAL)
	{
		AddSprite(s);
		if(s->staticshield)
			AddSprite(s->staticshield);
	}
	else if(pos==ADD_FIRST)
	{
	}
	else if(pos==ADD_LAST)
	{

	}
	
	return TRUE;
}

int Engine2::FindLastSprite()
{
	int i,i2=0;
	for(i=0;i<MAXSPRITES;++i)
	{
		if(sprites[i])i2=i;
	}
	return i2;
}

void Engine2::Defrag()
{
	int i,i2;
	for(i=0;i<MAXSPRITES-1;++i)
	{
		i2=FindLastSprite();
		if(i>i2)return;
		if(sprites[i]==NULL)
		{
			if(i>=i2)return;
			sprites[i]=sprites[i2];
			sprites[i2]=NULL;
		}
	}
}

void Engine2::DeleteSprite(int n)
{
	if(sprites[n]->staticshield)
	{
		sprites[n]->staticshield->deletedisabled=TRUE;
	}
	delete sprites[n];
	sprites[n]=NULL;
	--currentnumsprites;
}
	
void Engine2::OnSpriteShieldDown(Sprite2 *s)
{
	if(shielddownproc)shielddownproc(s);
}
	
void Engine2::OnSpriteHullCritical(Sprite2 *s)
{
	if(hullcriticalproc)hullcriticalproc(s);
}

Sprite2 *Engine2::GetNearestSprite(Sprite2 *s)
{
	if(s==NULL)return(NULL);

	int i;
	Sprite2 *tmpsprite=NULL;
	float lastdistance,tmpfloat;
	tmpfloat=0;
	lastdistance=9999999;

	for(i=0;i<MAXSPRITES;++i)
	{
		if(sprites[i]!=NULL)
		{
			tmpfloat=SpriteGetDistance(s,sprites[i]);
			if(tmpfloat<lastdistance && s!=sprites[i] && sprites[i]->enabled && sprites[i]->canhit&&SpriteInScreen(sprites[i]))
			{
				tmpsprite=sprites[i];
				lastdistance=tmpfloat;
			}
		}
	}

	return(tmpsprite);

}

Sprite2 *Engine2::GetNearestActor(Sprite2 *s)
{
	if(s==NULL)return(NULL);

	int i;
	Sprite2 *tmpsprite=NULL;
	float lastdistance,tmpfloat;
	tmpfloat=0;
	lastdistance=9999999;

	for(i=0;i<MAXSPRITES;++i)
	{
		if(sprites[i])
		{
			tmpfloat=SpriteGetDistance(s,sprites[i]);
			if(tmpfloat<lastdistance && s!=sprites[i] && sprites[i]->enabled && sprites[i]->canhit && (sprites[i]->type==SPRITETYPE_HUMAN||sprites[i]->type==SPRITETYPE_CPU)&&SpriteInScreen(sprites[i]))
			{
				tmpsprite=sprites[i];
				lastdistance=tmpfloat;
			}
		}
	}

	return(tmpsprite);
}

Sprite2 *Engine2::GetNearestBonus(Sprite2 *s)
{
	if(s==NULL)return(NULL);

	int i;
	Sprite2 *tmpsprite=NULL;
	float lastdistance,tmpfloat;
	tmpfloat=0;
	lastdistance=9999999;

	for(i=0;i<MAXSPRITES;++i)
	{
		if(sprites[i])
		{
			tmpfloat=SpriteGetDistance(s,sprites[i]);
			if(tmpfloat<lastdistance && s!=sprites[i] && sprites[i]->enabled && sprites[i]->type==SPRITETYPE_BONUS &&SpriteInScreen(sprites[i]))
			{
				tmpsprite=sprites[i];
				lastdistance=tmpfloat;
			}
		}
	}

	return(tmpsprite);
}
	
float Engine2::GetSpriteDistance(Sprite2 *s1,Sprite2 *s2)
{
	float x1,x2,y1,y2,dx,dy;
	float dist;
	
	if(s1==NULL||s2==NULL)return(1000000000);

	x1=s1->position.x+s1->size.x/2;
	y1=s1->position.y+s1->size.y/2;
	x2=s2->position.x+s2->size.x/2;
	y2=s2->position.y+s2->size.y/2;
	dx=(float)fabs(x1-x2);
	dy=(float)fabs(y1-y2);
	dist=(float)sqrt(dx*dx+dy*dy)-s1->collisionrange-s2->collisionrange;
	
	return(dist);
}

float Engine2::SpriteGetDistance(Sprite2 *s1,Sprite2 *s2)
{
	float x1,x2,y1,y2,dx,dy;
	float dist;
	
	if(s1==NULL||s2==NULL)return(1000000000);

	x1=s1->position.x+s1->size.x/2;
	y1=s1->position.y+s1->size.y/2;
	x2=s2->position.x+s2->size.x/2;
	y2=s2->position.y+s2->size.y/2;
	dx=(float)fabs(x1-x2);
	dy=(float)fabs(y1-y2);
	dist=(float)sqrt(dx*dx+dy*dy);
	
	return(dist);

}

void Engine2::OnSpriteDelete(Sprite2 *s)
{
	int i;
	//if(!deleteproc)return;

	if(s->staticshield)
	{
		s->staticshield->deletedisabled=TRUE;
		s->staticshield->enabled=FALSE;
	}

	for(i=0;i<MAXSPRITES;++i)
	{
		if(sprites[i]==s)
		{
			sprites[i]=NULL;
		}
	}
	for(i=0;i<MAXSPRITES;++i)
	{
		if(sprites[i])
		{
			if(sprites[i]->attacker==s)sprites[i]->attacker=NULL;
			if(sprites[i]->friendsprite==s)sprites[i]->friendsprite=NULL;
			if(sprites[i]->launchedfrom==s)sprites[i]->launchedfrom=NULL;
			if(sprites[i]->staticshield==s)sprites[i]->staticshield=NULL;
			if(sprites[i]->target==s)sprites[i]->target=NULL;
		}
	}

	//Defrag();
}

void Engine2::OnSpriteDisable(Sprite2 *s)
{
	if(destroyproc)destroyproc(s);
}
	
BOOL Engine2::MK2DetectHit(Sprite2 *s1,Sprite2 *s2)
{
	if(!SpriteRectDetectHit(s1,s2))return FALSE;

	RECT r,r1,r2;
	int x,y;
	BOOL b;

	r1.left=(int)s1->position.x;
	r1.right=(int)s1->position.x+s1->size.x;
	r1.top=(int)s1->position.y;
	r1.bottom=(int)s1->position.y+s1->size.y;

	r2.left=(int)s2->position.x;
	r2.right=(int)s2->position.x+s2->size.x;
	r2.top=(int)s2->position.y;
	r2.bottom=(int)s2->position.y+s2->size.y;

	if(r1.left<r2.left)
		r.left=r2.left;
	else r.left=r1.left;

	if(r1.right<r2.right)
		r.right=r1.right;
	else r.right=r2.right;

	if(r1.top<r2.top)
		r.top=r2.top;
	else r.top=r1.top;

	if(r1.bottom<r2.bottom)
		r.bottom=r1.bottom;
	else r.bottom=r2.bottom;

	for(y=r.top;y<r.bottom;++y)
	{
		for(x=r.left;x<r.right;++x)
		{
			b=s1->GetMK2Collision(x,y);
			if(b)
			{
				b=s2->GetMK2Collision(x,y);
				if(b)return TRUE;
			}

		}
	}

	return FALSE;
}

void Engine2::DetectHits()
{
	int i1;
	int i2;

	for(i2=0;i2<MAXSPRITES;++i2)
	{
		if(sprites[i2])
		{
			for(i1=i2+1;i1<MAXSPRITES;++i1)
			{
				if(sprites[i1] && sprites[i1]->enabled && sprites[i2]->enabled)
				{
					if(	(sprites[i1]->canhit || sprites[i2]->canhit)&& 
						(sprites[i1]->canbehit || sprites[i2]->canbehit) &&
						SpriteDetectHit(sprites[i1],sprites[i2])&&
						!(sprites[i1]->friendsprite==sprites[i2] || sprites[i2]->friendsprite==sprites[i1])&&
						(sprites[i1]->friendsprite!=sprites[i2]->friendsprite ||!(sprites[i1]->friendsprite||sprites[i1]->friendsprite))&&
						(sprites[i1]->launchedfrom!=sprites[i2]->launchedfrom||(!sprites[i1]->launchedfrom))&&
						SpriteInScreen(sprites[i1]) && SpriteInScreen(sprites[i2])
						)
					{
						if((sprites[i1]->canhit||sprites[i1]->canbehit)&&(sprites[i2]->canhit||sprites[i2]->canbehit))
						{
							if(collisionproc)
								collisionproc(sprites[i1],sprites[i2]);
							sprites[i1]->OnCollision(sprites[i2]);
							sprites[i2]->OnCollision(sprites[i1]);
						}
					}
				}
			}
		}
	}
}

void Engine2::DrawAll()
{
	int i,i2,i3;
	char tmpstr[64];
	RECT destrect;
	RECT srcrect;
	VECTOR c;
	if(!initialized)return;

	if(lpDDSBackGround)
	{

		//DDAlphaBlend(lpDDSBackBuffer,lpDDSBackGround,&destrect,&srcrect);

		//lpDDSBackBuffer->Blt(NULL,lpDDSBackGround,NULL,DDBLT_WAIT,NULL);

		c.x=-ScreenPos.x;
		c.y=-ScreenPos.y;
		while(c.x<0)c.x+=(float)screenwidth;
		while(c.y<0)c.y+=(float)screenheight;
		while(c.x>screenwidth)c.x-=(float)screenwidth;
		while(c.y>screenheight)c.y-=(float)screenheight;

		destrect.left=0;
		destrect.right=(int)c.x;
		destrect.top=0;
		destrect.bottom=(int)c.y;
		srcrect.left=screenwidth-(int)c.x;
		srcrect.right=screenwidth;
		srcrect.top=screenheight-(int)c.y;
		srcrect.bottom=screenheight;
		lpDDSBackBuffer->Blt(&destrect,lpDDSBackGround,&srcrect,DDBLT_WAIT,NULL);

		destrect.left=(int)c.x;
		destrect.right=screenwidth;
		destrect.top=0;
		destrect.bottom=(int)c.y;
		srcrect.left=0;
		srcrect.right=screenwidth-(int)c.x;
		srcrect.top=screenheight-(int)c.y;
		srcrect.bottom=screenheight;
		lpDDSBackBuffer->Blt(&destrect,lpDDSBackGround,&srcrect,DDBLT_WAIT,NULL);

		destrect.left=0;
		destrect.right=(int)c.x;
		destrect.top=(int)c.y;
		destrect.bottom=screenheight;
		srcrect.left=screenwidth-(int)c.x;
		srcrect.right=screenwidth;
		srcrect.top=0;
		srcrect.bottom=screenheight-(int)c.y;
		lpDDSBackBuffer->Blt(&destrect,lpDDSBackGround,&srcrect,DDBLT_WAIT,NULL);

		destrect.left=(int)c.x;
		destrect.right=screenwidth;
		destrect.top=(int)c.y;
		destrect.bottom=screenheight;
		srcrect.left=0;
		srcrect.right=screenwidth-(int)c.x;
		srcrect.top=0;
		srcrect.bottom=screenheight-(int)c.y;
		lpDDSBackBuffer->Blt(&destrect,lpDDSBackGround,&srcrect,DDBLT_WAIT,NULL);


	}
	else
	{
		ClearSurface(lpDDSBackBuffer);
	}
	//RenderMap(lpDDSBackBuffer);

	for(i=0;i<MAXSPRITES;++i)
	{
		if(sprites[i]&&sprites[i]->enabled)
		{
			sprites[i]->Draw(lpDDSBackBuffer,(int)(sprites[i]->position.x-ScreenPos.x),(int)(sprites[i]->position.y-ScreenPos.y));
			if(drawcollisionmaps)
				sprites[i]->DrawMK2Collision(lpDDSBackBuffer,(int)(sprites[i]->position.x-ScreenPos.x),(int)(sprites[i]->position.y-ScreenPos.y));
		}
	}

	for(i=0;i<MAXITEMS;++i)
	{
		if(items[i]&&items[i]->enabled)
		{
			if(!items[i]->noscroll)
				items[i]->Draw(lpDDSBackBuffer,(int)(items[i]->position.x-ScreenPos.x),(int)(items[i]->position.y-ScreenPos.y));
			else
				items[i]->Draw(lpDDSBackBuffer,(int)(items[i]->position.x),(int)(items[i]->position.y));
		}
	}

	if(showinfo)
	{
		sprintf(tmpstr,"%d",currentnumsprites);
		Write2Surface(lpDDSBackBuffer,tmpstr,700,10);
		
		sprintf(tmpstr,"%d",fps);
		Write2Surface(lpDDSBackBuffer,tmpstr,600,10);
		
		sprintf(tmpstr,"%d",currentnumitems);
		Write2Surface(lpDDSBackBuffer,tmpstr,500,10);
		
		sprintf(tmpstr,"%d",(int)(tnow-starttime));
		Write2Surface(lpDDSBackBuffer,tmpstr,400,10);
		
		sprintf(tmpstr,"%d",(int)(totalpausetime));
		Write2Surface(lpDDSBackBuffer,tmpstr,300,10);
		
		sprintf(tmpstr,"%d",(int)(currentnumevents));
		Write2Surface(lpDDSBackBuffer,tmpstr,500,50);

		//mouse
		POINT p;
		p=mouse.GetPos();

		sprintf(tmpstr,"%d",(int)(p.x));
		Write2Surface(lpDDSBackBuffer,tmpstr,20,300);
		
		sprintf(tmpstr,"%d",(int)(p.y));
		Write2Surface(lpDDSBackBuffer,tmpstr,20,350);

		//Sound
		i2=0;
		i3=0;
		for(i=0;i<MAXSOUNDS;++i)
		{
			if(soundsys.lpDSB[i])++i2;
		}
		for(i=0;i<MAXORGINALSOUNDS;++i)
		{
			if(soundsys.lpDSBOrg[i])++i3;
		}
		sprintf(tmpstr,"%d",(int)(i2));
		Write2Surface(lpDDSBackBuffer,tmpstr,200,50);

		sprintf(tmpstr,"%d",(int)(i3));
		Write2Surface(lpDDSBackBuffer,tmpstr,250,50);
	}
		
	if(pause)
		Write2Surface(lpDDSBackBuffer,pausetext,screenwidth/2-50,screenheight/2-10);

	//DrawLine(lpDDSBackBuffer,0,0,500,500,RGB(255,255,255),1);

	//Cursor
	if(cursor&&cursor->enabled)
	{
		cursor->Draw(lpDDSBackBuffer,(int)cursor->position.x,(int)cursor->position.y);
	}

	if(preflipproc)preflipproc();

	if(fullscreen)lpDDSPrimary->Flip(NULL,0);
	else
	{
		GetWindowRect(hwnd,&destrect);
		lpDDSPrimary->Blt(&destrect,lpDDSBackBuffer,NULL,DDBLT_WAIT,NULL);
	}
	++framenumber;

}
	
void Engine2::Pause(LPCSTR text/*=NULL*/)
{
	if(text)
	{
		strcpy(pausetext,text);
	}
	if(!pause)
	{
		tppauseon=timeGetTime();
		pause=TRUE;
	}
	else
	{
		//totalpausetime+=timeGetTime()-tppauseon;
		tppauseon=0;
		pause=FALSE;
		tplastupdate=timeGetTime()-totalpausetime;
	}
	DrawAll();
}

BOOL Engine2::DuplicateSprite(Sprite2 *sn,Sprite2 *s)
{
	if(!initialized)return(FALSE);
	if(sn==NULL || s==NULL)return(FALSE);
	
	memcpy(sn,s,sizeof(*s));
/*	if(soundsyslpDirectSound)
	{
		if(s->lpDSBSound)
			lpDirectSound->DuplicateSoundBuffer(s->lpDSBSound,&sn->lpDSBSound);
	}*/
	
	if(s->staticshield!=NULL)
	{
		sn->staticshield=new Sprite2;
		memcpy(sn->staticshield,s->staticshield,sizeof(*s->staticshield));
		sn->staticshield->enabled=FALSE;
	}
	return TRUE;
}

BOOL Engine2::LoadSprite(Sprite2 *s,char *filename,char *spritename)
{

	if(!initialized)return(FALSE);
	HBITMAP hbm;
//	HRESULT hres;
	char tmpstr[64];
	char bmpfile[64];
	int i;
	BOOL b;
	
	if(!GetPrivateProfileStringCurrentDir(filename,spritename,"bitmapfile",bmpfile,64))
	{
		strcpy(errormessage,"Bitmapfile key not found while loading sprite ");
		strcat(errormessage,spritename);
		OnError();
		return FALSE;
	}
	s->e=this;
/*
	if(stricmp(tmpstr,"none")==0)
	{
	s->size.x=GetPrivateProfileIntCurrentDir(filename,spritename,"width",-1);
	s->size.y=GetPrivateProfileIntCurrentDir(filename,spritename,"height",-1);
	if(s->size.x==-1||s->size.y==-1)
	{
		s->size.x=GetPrivateProfileIntCurrentDir(filename,spritename,"collisionrange",0)*2;
		s->size.y=s->size.x;
	}

	s->enabled=TRUE;
	s->nframes=1;
		goto SURFACEINITDONE;
	}*/

	for(i=0;i<MAXPROTOTYPES;++i)
	{
		if(prototypes[i])
		{
			if(stricmp(prototypes[i]->bitmapfile,bmpfile)==0)
			{
				s->InitWithSurfaceOfSprite(prototypes[i]);
				goto SURFACEINITDONE;
				break;
			}
		}
	}

	hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), bmpfile, 
		IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);

	if(hbm)
	{
	b=s->Initialize(lpDD,hbm,
		GetPrivateProfileIntCurrentDir(filename,spritename,"width",0),
		GetPrivateProfileIntCurrentDir(filename,spritename,"height",0),
		GetPrivateProfileIntCurrentDir(filename,spritename,"nframes",0),
		GetPrivateProfileIntCurrentDir(filename,spritename,"autocolorkey",1)
		);
	}
	else
	{
	b=s->Initialize2(lpDD,tmpstr,
		GetPrivateProfileIntCurrentDir(filename,spritename,"autocolorkey",1)
		);
	}
	if(!GetPrivateProfileIntCurrentDir(filename,spritename,"autocolorkey",1))
	{
		for(i=0;i<(int)s->nframes;++i)
		{
			DDSetColorKey((LPDIRECTDRAWSURFACE)s->lpDDSFrames[i],RGB(
				GetPrivateProfileIntCurrentDir(filename,spritename,"redcolorkey",0),
				GetPrivateProfileIntCurrentDir(filename,spritename,"greenrkey",0),
				GetPrivateProfileIntCurrentDir(filename,spritename,"blueorkey",0)));
		}
	}
	if(!b)
		return FALSE;
SURFACEINITDONE:
	strcpy(s->bitmapfile,tmpstr);
	strcpy(s->spritename,spritename);

	s->collisionrange=GetPrivateProfileIntCurrentDir(filename,spritename,"collisionrange",0);
	s->maxhitpoints=GetPrivateProfileIntCurrentDir(filename,spritename,"hitpoints",0);
	s->hitpoints=s->maxhitpoints;
	
	s->maxspeed=GetPrivateProfileIntCurrentDir(filename,spritename,"maxspeed",10000);

	s->maxacceleration=GetPrivateProfileIntCurrentDir(filename,spritename,"acceleration",1000);
	
	s->tfiredelay=GetPrivateProfileIntCurrentDir(filename,spritename,"launchdelay",0);
	
	s->turnspeed=GetPrivateProfileIntCurrentDir(filename,spritename,"turnspeed",300);
	
	s->weapondist.x=GetPrivateProfileIntCurrentDir(filename,spritename,"weapondistx",0);
	s->weapondist.y=GetPrivateProfileIntCurrentDir(filename,spritename,"weapondisty",0);
	s->centerweapondisty=GetPrivateProfileIntCurrentDir(filename,spritename,"centerweapondisty",0);
	s->centerfire=GetPrivateProfileIntCurrentDir(filename,spritename,"centerfire",0);

	s->canhit=GetPrivateProfileIntCurrentDir(filename,spritename,"canhit",0);
	s->canbehit=GetPrivateProfileIntCurrentDir(filename,spritename,"canbehit",0);
	s->deleteoutscreen=GetPrivateProfileIntCurrentDir(filename,spritename,"deleteifoutofscreen",0);
	s->deletedisabled=GetPrivateProfileIntCurrentDir(filename,spritename,"deleteifdisabled",0);
	s->deleteoutexscreen=GetPrivateProfileIntCurrentDir(filename,spritename,"deleteoutexscreen",0);
	s->disableoutexscreen=GetPrivateProfileIntCurrentDir(filename,spritename,"disableoutexscreen",0);
	s->disableanimcomplete=GetPrivateProfileIntCurrentDir(filename,spritename,"disableanimcomplete",0);
	if(GetPrivateProfileIntCurrentDir(filename,spritename,"angleframes",0))
		s->frametype=FRAMETYPE_DIRECTION;
	s->launchlifetime=GetPrivateProfileIntCurrentDir(filename,spritename,"launchlifetime",0);
	
	if(GetPrivateProfileStringCurrentDir(filename,spritename,"bouncestrenght",tmpstr,64))
		s->bouncestrenght=(float)str2double(tmpstr);
	
//	if(GetPrivateProfileStringCurrentDir(filename,spritename,"hitdamagedecreasespeed",tmpstr,64))
//		s->hitdamagedecreasespeed=(float)str2double(tmpstr);
	
	s->bouncing=GetPrivateProfileIntCurrentDir(filename,spritename,"bouncing",0);
	//s->animmode=GetPrivateProfileIntCurrentDir(filename,spritename,"animmode",0);
	//s->playanim=GetPrivateProfileIntCurrentDir(filename,spritename,"playanim",0);
	s->indestructible=GetPrivateProfileIntCurrentDir(filename,spritename,"indestructible",0);
	//s->usecollisionrect=GetPrivateProfileIntCurrentDir(filename,spritename,"usecollisionrect",0);
	s->enabled=GetPrivateProfileIntCurrentDir(filename,spritename,"enabled",0);
	s->homing=GetPrivateProfileIntCurrentDir(filename,spritename,"homing",0);
	
	if(GetPrivateProfileStringCurrentDir(filename,spritename,"hitforce",tmpstr,64))
		s->hitforce=(float)str2double(tmpstr);
	if(GetPrivateProfileStringCurrentDir(filename,spritename,"hitforcemodifier",tmpstr,64))
		s->hitforcemodifier=(float)str2double(tmpstr);

	if(GetPrivateProfileIntCurrentDir(filename,spritename,"angleframes",0)==1)
	{
		s->frametype=FRAMETYPE_DIRECTION;
	}
	else
	{
		s->frametype=FRAMETYPE_ANIMATION;
	}

	s->hitdamage=GetPrivateProfileIntCurrentDir(filename,spritename,"hitdamage",0);
	s->launchspeed=GetPrivateProfileIntCurrentDir(filename,spritename,"launchspeed",0);

	i=GetPrivateProfileIntCurrentDir(filename,spritename,"explosionnumber",-1);
	if(i>=0)s->explosion=prototypes[i];
	
	
	s->receivebonus=GetPrivateProfileIntCurrentDir(filename,spritename,"receivebonus",0);
	
	i=GetPrivateProfileIntCurrentDir(filename,spritename,"launchspritenumber",-1);
	if(i>=0)s->weapon=prototypes[i];
	s->defaultweapon=s->weapon;
	s->anglevdep=GetPrivateProfileIntCurrentDir(filename,spritename,"directionvdependend",0);
	s->maxshieldstrenght=GetPrivateProfileIntCurrentDir(filename,spritename,"maxshieldstrenght",0);
	s->shieldstrenght=s->maxshieldstrenght;
	s->shieldloadspeed=GetPrivateProfileIntCurrentDir(filename,spritename,"shieldloadspeed",0);
	
	s->maxenergy=GetPrivateProfileIntCurrentDir(filename,spritename,"maxenergy",0);
	s->energy=s->maxenergy;
	s->energyloadspeed=GetPrivateProfileIntCurrentDir(filename,spritename,"energyloadspeed",0);

	i=GetPrivateProfileIntCurrentDir(filename,spritename,"hitspritenumber",-1);
	if(i>=0)s->staticshield=prototypes[i];
	
	i=GetPrivateProfileIntCurrentDir(filename,spritename,"smokeexplnumber",-1);
	if(i>=0)s->smoke=prototypes[i];
	s->smoking=GetPrivateProfileIntCurrentDir(filename,spritename,"smoking",0);

	i=GetPrivateProfileIntCurrentDir(filename,spritename,"releasebonusnumber",-1);
	if(i!=-1)s->release=prototypes[i];
	i=GetPrivateProfileIntCurrentDir(filename,spritename,"debrisnumber",-1);
	if(i!=-1)s->debris=prototypes[i];
	s->ammo=GetPrivateProfileIntCurrentDir(filename,spritename,"ammo",0);
	s->ndebris=GetPrivateProfileIntCurrentDir(filename,spritename,"numdebris",10);
	
	//Sound
	if(GetPrivateProfileStringCurrentDir(filename,spritename,"sound",tmpstr,64)&&soundsys.lpDS)
	{
		if(stricmp(tmpstr,"NULL")!=0)
		{
	/*			for(i=0;i<100;++i)
			{
				if(prototypes[i])
				{
					if(stricmp(prototypes[i]->soundfile,tmpstr)==0)
					{
						lpDirectSound->DuplicateSoundBuffer(prototypes[i]->lpDSBSound,&s->lpDSBSound);
						strcpy(s->soundfile,prototypes[i]->soundfile);
						goto NOLOADSOUND;
						break;
					}
				}
			}
			s->lpDSBSound=DSLoadSoundBuffer(lpDirectSound,tmpstr);
/*#ifdef E_SFX_MINVOLUME
			if(s->lpDSBSound)
			{
				i=GetPrivateProfileIntCurrentDir("config.ini","game1","sfxvolume",100);

				s->lpDSBSound->SetVolume(E_SFX_MINVOLUME+(int)(((float)i/100)*(float)abs(E_SFX_MINVOLUME)));
			}
#endif*/
			s->soundnr=soundsys.GetSoundNr(tmpstr);
			if(s->soundnr>=0)
			{
			//soundsys.soundtype[s->soundnr]=SOUNDTYPE_FX;
			strcpy(s->soundfile,tmpstr);
			}
			else
			{
				strcpy(errormessage,"Could not load sound ");
				strcat(errormessage,tmpstr);
				OnError();
			}
		}
	}
	
//NOLOADSOUND:
/*
	if(s->lpDSBSound)
	{
		i=GetPrivateProfileIntCurrentDir(filename,spritename,"volume",100);
		i*=100;
		i-=10000;
		hres=s->lpDSBSound->SetVolume(i);
		if(hres!=DD_OK)
		{
			strcpy(errormessage,"");
			PrintDSError(errormessage,hres);
			OnError();
		}
	}*/

	s->type=GetPrivateProfileIntCurrentDir(filename,spritename,"type",1);
	if(s->type==SPRITETYPE_EXPLOSION)s->deletedisabled=TRUE;
	s->trespawn=GetPrivateProfileIntCurrentDir(filename,spritename,"respawntime",0);
	s->nlaunch=GetPrivateProfileIntCurrentDir(filename,spritename,"launchnumber",1);

	s->specialtype=GetPrivateProfileIntCurrentDir(filename,spritename,"special",0);
	s->tspecialdelay=GetPrivateProfileIntCurrentDir(filename,spritename,"specialdelay",0);
	i=GetPrivateProfileIntCurrentDir(filename,spritename,"specialsprite",-1);
	if(i!=-1)s->special=prototypes[i];
	
	if(GetPrivateProfileIntCurrentDir("config.ini","game1","alphablending",0))
		s->additive=GetPrivateProfileIntCurrentDir(filename,spritename,"additive",0);
	
	s->animfps=GetPrivateProfileIntCurrentDir("config.ini","game1","animfps",25);

	//Swing
	s->swing=GetPrivateProfileIntCurrentDir(filename,spritename,"swing",0);
	s->swingacceleration=GetPrivateProfileIntCurrentDir(filename,spritename,"swingacceleration",1000);
	s->swingangle=GetPrivateProfileIntCurrentDir(filename,spritename,"swingangle",90);
	s->swingtime=GetPrivateProfileIntCurrentDir(filename,spritename,"swingtime",500);

	s->e=this;
	//Collisions
	if(GetPrivateProfileStringCurrentDir(filename,spritename,"pbmfile",tmpstr,64))
	{
		if(stricmp(tmpstr,"NULL")!=0)
		{
			if(stricmp(tmpstr,bmpfile)==0)
			{
				if(!s->InitMK2Collisions(tmpstr,hbm))
				{
					strcpy(errormessage,"Error while loading ");
					strcat(errormessage,tmpstr);
					OnError();
				}
			}
			else if(!s->InitMK2Collisions(tmpstr))
			{
				strcpy(errormessage,"Error while loading ");
				strcat(errormessage,tmpstr);
				OnError();
			}
		}
	}

	s->damagemultiplicator=(float)GetPrivateProfileIntCurrentDir(filename,spritename,"damagemultiplicator",100)/100.0f;
	s->tdamagemulti=(UINT)GetPrivateProfileIntCurrentDir(filename,spritename,"damagemultitime",0);

	s->e=this;
	DeleteObject(hbm);
	return(TRUE);

}

void Engine2::OnError()
{
	LPDIRECTDRAWSURFACE3 lpDDS=NULL;
	DDSURFACEDESC       ddsd;

	if(lpDD&&lpDDSPrimary)
	{
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY ;
		ddsd.dwWidth = screenwidth;
		ddsd.dwHeight = screenheight;
		lpDD->CreateSurface(&ddsd, (LPDIRECTDRAWSURFACE*)&lpDDS,NULL);
		if(lpDDS)lpDDS->Blt(NULL,lpDDSPrimary,NULL,DDBLT_WAIT,NULL);
	
		Write2Surface(lpDDSPrimary,errormessage,screenwidth/2-150,screenheight/2-20);

		Write2Surface(lpDDSPrimary,"Press ESC to abort or SPACE to continue",screenwidth/2-150,screenheight/2);
	
		while(1)
		{
			if(GetAsyncKeyState(VK_ESCAPE)<0)exit(0);
			if(GetAsyncKeyState(VK_SPACE)<0)break;
		}
	}
	else
	{
		if(MessageBox(hwnd,errormessage,"Error",MB_OKCANCEL)==IDCANCEL)exit(0);
	}

	if(lpDD && lpDDSPrimary && lpDDS)
	{
		lpDDSPrimary->Blt(NULL,lpDDS,NULL,DDBLT_WAIT,NULL);
		lpDDS->Release();
	}
}

void Engine2::Write2Surface(LPDIRECTDRAWSURFACE3 lpDDS,char *text,int x,int y)
{
	HDC hdc;
	RECT rect;
	
	if(y<25&&!fullscreen)y=25;
	if(lpDDS->GetDC(&hdc)== DD_OK)
	{
		//SetBkColor( hdc, RGB( 0, 0, 0 ) );
		SetBkMode(hdc,TRANSPARENT);
		SetTextColor( hdc, RGB( 255, 255, 255 ) );
		if(!fullscreen&&lpDDS==lpDDSPrimary)
		{
			GetWindowRect(hwnd,&rect);
			x+=rect.left;
			y+=rect.top;
		}
		TextOut( hdc, x, y, text, strlen(text) );
		lpDDS->ReleaseDC(hdc);
	}
}

void Engine2::ClearSurface(LPDIRECTDRAWSURFACE3 lpDDS)
{
	DDBLTFX ddbltfxtmp;
	ddbltfxtmp.dwSize=sizeof(ddbltfxtmp);
	ddbltfxtmp.dwFillColor=0;
	lpDDS->Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&ddbltfxtmp);		
}



// Die Positionen der RGB Anteile
#define ROT_POS     10//11
#define GRUEN_POS   5
#define BLAU_POS    0

// Die Größe der Anteile in Bits
#define ROT_SIZE    5
#define GRUEN_SIZE  5//6
#define BLAU_SIZE   5

// Die AND-Maske für die RGB Anteile 
#define ROT_MASKE   unsigned short(( ( 1 << ROT_SIZE ) - 1 ) << ROT_POS)
#define GRUEN_MASKE unsigned short(( ( 1 << GRUEN_SIZE ) - 1 ) << GRUEN_POS)
#define BLAU_MASKE  unsigned short(( ( 1 << BLAU_SIZE ) - 1 ) << BLAU_POS)
	
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
//int i;
#define	bitmask (unsigned short)(((unsigned short)((1<<ROT_SIZE)-2)<<(unsigned short)ROT_POS)+ \
				 ((unsigned short)((1<<GRUEN_SIZE)-2)<<(unsigned short)GRUEN_POS)+ \
				 ((unsigned short)((1<<BLAU_SIZE)-2)<<(unsigned short)BLAU_POS))

BOOL Engine2::AdditiveBlt16(LPDIRECTDRAWSURFACE3 destsurface,LPDIRECTDRAWSURFACE3 srcsurface,RECT *destrect,RECT *srcrect)
{

	
	
	DDSURFACEDESC destddsd,srcddsd;
	HRESULT hresult;
	unsigned short *dest,*src;
	int destx,desty,desti,srci,tmp;
	int destpitch,srcpitch;
	int srcpixelwidth,srcpixelheight;
	int i,i2;

////////////	
	static BOOL firstrun=TRUE;
	static unsigned short remappalette[ 65536 ];

	// Palette für additives Shading
	if(firstrun)
	{
	for ( i = 0; i < 65536; i++ )
	{
		unsigned short r = (((unsigned short)i&ROT_MASKE)>>ROT_POS)*512;
		unsigned short g = (((unsigned short)i&GRUEN_MASKE)>>GRUEN_POS)*512;
		unsigned short b = (((unsigned short)i&BLAU_MASKE)>>BLAU_POS)*512;

		remappalette[ i ] = ColorCode( min( 255, r>>ROT_SIZE ), 
									   min( 255, g>>GRUEN_SIZE ), 
									   min( 255, b>>BLAU_SIZE ) );
	}firstrun=FALSE;}
///////////

	if(destrect->top<ScreenPos.y)
	{
		srcrect->top+=(int)ScreenPos.y-destrect->top;
		destrect->top=(int)ScreenPos.y;
	}
	if(destrect->bottom>ScreenPos.y+screenheight)
	{
		srcrect->bottom-=destrect->bottom-((int)ScreenPos.y+(int)screenheight);
		destrect->bottom=(int)ScreenPos.y+(int)screenheight;
	}

	if(destrect->left<ScreenPos.x)
	{
		srcrect->left+=(int)ScreenPos.x-destrect->left;
		destrect->left=(int)ScreenPos.x;
	}
	if(destrect->right>ScreenPos.x+screenwidth)
	{
		srcrect->right-=destrect->right-((int)ScreenPos.x+(int)screenwidth);
		destrect->right=(int)ScreenPos.x+(int)screenwidth;
	}


	destddsd.dwSize=sizeof(destddsd);
	srcddsd.dwSize=sizeof(srcddsd);

	hresult=destsurface->Lock(NULL,&destddsd,DDLOCK_WAIT,NULL);
	if(hresult!=DD_OK)return(FALSE);
	hresult=srcsurface->Lock(NULL,&srcddsd,DDLOCK_WAIT,NULL);
	if(hresult!=DD_OK)return(FALSE);

	dest=(unsigned short *)destddsd.lpSurface;
	src=(unsigned short *)srcddsd.lpSurface;

//	destwidth=destddsd.dwWidth;
	destpitch=destddsd.lPitch/2;

//	srcwidth=srcddsd.dwWidth;
	srcpitch=srcddsd.lPitch/2;

	destx=destrect->left;
	desty=destrect->top;
//	srcx=srcrect->left;
//	srcy=srcrect->top;
	//i=y*Pitch/2+x;

	desti=destrect->top*destpitch+destrect->left;
	srci=srcrect->top*srcpitch+srcrect->left;

	srcpixelwidth=srcrect->right-srcrect->left;
	srcpixelheight=srcrect->bottom-srcrect->top;

	for(i2=0;i2<srcpixelheight;++i2)
	{
		for(i=0;i<srcpixelwidth;++i)
		{
			tmp=i+desti;
			//cn=(src[i+srci]&bitmask)+(dest[tmp]&bitmask);
			//cn+=(dest[tmp]&bitmask);
			dest[tmp]=remappalette[( ((src[i+srci]&bitmask)+(dest[tmp]&bitmask)) >>1 )];
		}
		desti+=destpitch;
		srci+=srcpitch;
	}

	destsurface->Unlock(NULL);
	srcsurface->Unlock(NULL);

	return(TRUE);
}

GUID FAR *lpDisplayDevice;

BOOL WINAPI DDEnumCb(
  GUID FAR *lpGUID,
  LPSTR  lpDriverDescription,
  LPSTR  lpDriverName,
  LPVOID lpContext
)
{
	lpDisplayDevice=lpGUID;
	return TRUE;
}


void Engine2::OnItemClick(BaseItem *i)
{
	if(itemclickproc)itemclickproc(i);
}
	
BOOL Engine2::ScreenPointHitsItem(POINT p,BaseItem *bi,POINT *pwhere)
{
	RECT rect;
//	int i;
	if(bi&&bi->enabled)
	{
		if(bi->noscroll)
		{
			rect.left=(int)bi->position.x;
			rect.right=(int)bi->position.x+bi->size.x;
			rect.top=(int)bi->position.y;
			rect.bottom=(int)bi->position.y+bi->size.y;
		}
		else
		{
			rect.left=(int)(bi->position.x-ScreenPos.x);
			rect.right=(int)(bi->position.x+bi->size.x-ScreenPos.x);
			rect.top=(int)(bi->position.y-ScreenPos.y);
			rect.bottom=(int)(bi->position.y+bi->size.y-ScreenPos.y);
		}
		if(PointInRect(p,rect))
		{
			if(pwhere)
			{
				pwhere->x=p.x-rect.left;
				pwhere->y=p.y-rect.top;
			}
			return TRUE;
		}
	}
	return FALSE;
}
	
BOOL Engine2::CopyBitmap2Surface(LPDIRECTDRAWSURFACE3 lpDDS,char *file)
{
	if(!lpDDS)return FALSE;
	
	DDSURFACEDESC       ddsd;
	HRESULT ddrval;
	HBITMAP hbm;
	BITMAP bm;
	LPDIRECTDRAWSURFACE3 lpDDSTmp;
	RECT rect;
	
	hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		file, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	
	if(!hbm)
	{
		strcpy(errormessage,file);
		strcat(errormessage," could not be loaded");
		OnError();
		return FALSE;
	}
	
	GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap
	
	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
	ddsd.dwHeight = bm.bmHeight;
	ddsd.dwWidth = bm.bmWidth;
	ddrval=lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSTmp, NULL );
	if(ddrval!=DD_OK)
	{
		strcpy(errormessage,"IDirectDraw::CreateSurface failed in Engine2::CopyBitmap2Surface");
		OnError();
		return FALSE;
	}
	
	DDCopyBitmap((LPDIRECTDRAWSURFACE)lpDDSTmp, hbm, 0, 0,bm.bmWidth,bm.bmHeight);

	if(lpDDS==lpDDSPrimary&&!fullscreen)
	{
		GetWindowRect(hwnd,&rect);
	ddrval=lpDDS->Blt(&rect,lpDDSTmp,NULL,DDBLT_WAIT,NULL);
	if(ddrval!=DD_OK)
	{
		strcpy(errormessage,"IDirectDraw::Blt failed in Engine2::CopyBitmap2Surface");
		OnError();
		return FALSE;
	}

	}
	else
	{
	ddrval=lpDDS->Blt(NULL,lpDDSTmp,NULL,DDBLT_WAIT,NULL);
	if(ddrval!=DD_OK)
	{
		strcpy(errormessage,"IDirectDraw::Blt failed in Engine2::CopyBitmap2Surface");
		OnError();
		return FALSE;
	}
	}
	if(lpDDSTmp)lpDDSTmp->Release();

	return TRUE;
}

void Engine2::BackupPrimarySurface(BOOL restore,BOOL release)
{
	static LPDIRECTDRAWSURFACE3 lpDDSBackup=NULL;
	DDSURFACEDESC ddsd;
	HRESULT ddrval;

	if(release)
	{
		if(lpDDSBackup)lpDDSBackup->Release();
		lpDDSBackup=NULL;
		return;
	}

	if(!restore)
	{
		if(lpDDSBackup)
		{
			lpDDSBackup->Release();
			lpDDSBackup=NULL;
		}
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
		ddsd.dwHeight = screenheight;
		ddsd.dwWidth = screenwidth;
		ddrval=lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSBackup, NULL );
		if(ddrval!=DD_OK)
		{
			exit(0);
		}
		ddrval=lpDDSBackup->Blt(NULL,lpDDSPrimary, NULL, DDBLTFAST_NOCOLORKEY |DDBLT_WAIT ,NULL);
		if(ddrval!=DD_OK)
		{
			exit(0);
		}
	}
	else
	{
		ddrval=lpDDSPrimary->Blt(NULL,lpDDSBackup, NULL, DDBLTFAST_NOCOLORKEY |DDBLT_WAIT ,NULL);
		if(ddrval!=DD_OK)
		{
			exit(0);
		}
	}
}

/*
void engine::DrawPixel(int x,int y,int r,int g,int b)
{
	if(!initialized)return;

	unsigned short *screen;
	int i;

	screen=(unsigned short *)lpScreen;
	i=y*Pitch/2+x;
	screen[i]=ColorCode(r,g,b);
}


void engine::DrawTransparentPixel(int x,int y,int rn,int gn,int bn)
{
	unsigned short *screen;
	int i;
	unsigned short back;
	unsigned short newvalue,trans;
	static BOOL firstrun=TRUE;

	// Palette für additives Shading
	if(firstrun)
	{
	for ( i = 0; i < 65536; i++ )
	{
		int r = ((i&ROT_MASKE)>>ROT_POS)*512;
		int g = ((i&GRUEN_MASKE)>>GRUEN_POS)*512;
		int b = ((i&BLAU_MASKE)>>BLAU_POS)*512;

		remappalette[ i ] = ColorCode( min( 255, r>>ROT_SIZE ), 
									   min( 255, g>>GRUEN_SIZE ), 
									   min( 255, b>>BLAU_SIZE ) );
	}firstrun=FALSE;}

	screen=(unsigned short *)lpScreen;
	i=y*Pitch/2+x;
	back=screen[i];
	newvalue=ColorCode(rn,gn,bn)&bitmask;
	newvalue+=back&bitmask;
	screen[i] = remappalette[ (newvalue>>1) ]; 

}

*/
int Engine2::GetSpriteNumber(Sprite2* s)
{
	int i=0;
	while(s!=sprites[i] && i<MAXSPRITES-1)++i;
	if(s==sprites[i])return(i);
	return(-1);
}

int Engine2::GetItemNumber(BaseItem* i)
{
	int n=0;
	while(i!=items[n] && n<MAXITEMS-1)++n;
	if(i==items[n])return(n);
	return(-1);
}

void Engine2::DeleteItem(int n)
{
	delete items[n];
	items[n]=NULL;
	--currentnumitems;
}


float Engine2::GetFireAngle(Sprite2 *attacker,Sprite2 *target)
{
	float distance;
	POINT dest;
	float tweapon;
	float destangle;

	distance=SpriteGetDistance(attacker,target);

	tweapon=distance/attacker->weapon->launchspeed*1000;
	dest.x=(int)(target->position.x+target->size.x/2+target->speed.x*tweapon/1000);
	dest.y=(int)(target->position.y+target->size.y/2+target->speed.y*tweapon/1000);

	destangle=(float)(90-(atan2((dest.y-(attacker->position.y+attacker->size.y/2))*-1,dest.x-(attacker->position.x+attacker->size.x/2))/PI*180));
	if(destangle<0)
		destangle+=360;
	if(destangle>360)
		destangle-=360;

	return destangle;
}

float Engine2::GetAngle(Sprite2 *source,Sprite2 *dest)
{
	float destangle;



	destangle=(float)(90-(atan2(((dest->position.y+dest->size.y/2)-(source->position.y+source->size.y/2))*-1,(dest->position.x+dest->size.x/2)-(source->position.x+source->size.x/2))/PI*180));
	if(destangle<0)
		destangle+=360;
	if(destangle>360)
		destangle-=360;

	return destangle;
}

float Engine2::GetApproachSpeed(Sprite2 *s1,Sprite2 *s2)
{
	float p1x,p1y,p2x,p2y;
	float p1x2,p1y2,p2x2,p2y2;
	float dist1,dist2;
	float as;

	if(!(s1&&s2))return(0);

	p1x=s1->position.x;
	p1y=s1->position.y;
	p2x=s2->position.x;
	p2y=s2->position.y;

	p1x2=p1x+s1->speed.x/1000;
	p1y2=p1y+s1->speed.y/1000;
	p2x2=p2x+s2->speed.x/1000;
	p2y2=p2y+s2->speed.y/1000;

	dist1=GetDistance(p1x,p1y,p2x,p2y);
	dist2=GetDistance(p1x2,p1y2,p2x2,p2y2);

	as=(dist1-dist2)*1000;
	return(as);
}

BOOL Engine2::RestoreSurfaces()
{
	if(!initialized)return FALSE;
	int i,i2,w,h;
	int nframesx,nframesy;
	HBITMAP hbm;
	BITMAP bm;
	RECT rcRect;
	LPDIRECTDRAWSURFACE3 lpDDSTmp=NULL;
	DDSURFACEDESC ddsd;
	char tmpstr[64],tmpstr2[64];
	BOOL startatzero=TRUE;
	
	if(lpDDSPrimary->IsLost()==DDERR_SURFACELOST)
	{
		lpDDSPrimary->Restore();
		ClearSurface(lpDDSPrimary);
		Write2Surface(lpDDSPrimary,"Restoring, please wait...",screenwidth/2-80,screenheight/2-20);
	}
	else
		return FALSE;
	if(lpDDSBackBuffer->IsLost()==DDERR_SURFACELOST)
		lpDDSBackBuffer->Restore();

	for(i=0;i<MAXPROTOTYPES;++i)
	{
		if(prototypes[i])
		{
			hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), prototypes[i]->bitmapfile, 
				IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
			
			if(hbm)
			{
				GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap
				nframesx=bm.bmWidth/prototypes[i]->size.x;
				nframesy=bm.bmHeight/prototypes[i]->size.y;
				w=prototypes[i]->size.x;
				h=prototypes[i]->size.y;

				for(i2=0;i2<(int)prototypes[i]->nframes;++i2)
				{
					if(prototypes[i]->lpDDSFrames[i2]->IsLost()!=DDERR_SURFACELOST)continue;

					prototypes[i]->lpDDSFrames[i2]->Restore();

					rcRect.left = w*(i2%nframesx);
					rcRect.top = h*(int(i2/nframesx));
					rcRect.right = w*(i2%nframesx)+w;
					rcRect.bottom = h*(int(i2/nframesx))+h;
					
					
					//if(FAILED(ddrval))return FALSE;
					
					DDCopyBitmap((LPDIRECTDRAWSURFACE)prototypes[i]->lpDDSFrames[i2], hbm, rcRect.left, rcRect.top, w, h);
					//DDSetColorKey(lpDDSFrames[i], RGB(r,g,b));
				}

				DeleteObject(hbm);
			}
			else
			{
				for(i2=0;;++i2)
				{
					if(prototypes[i]->lpDDSFrames[i2] &&prototypes[i]->lpDDSFrames[i2]->IsLost()!=DDERR_SURFACELOST)continue;

					if(prototypes[i]->lpDDSFrames[i2])prototypes[i]->lpDDSFrames[i2]->Restore();

					strcpy(tmpstr,prototypes[i]->bitmapfile);
					sprintf(tmpstr2,"%d",i2);
					if(i2<10)
					{
						strcat(tmpstr,"00");
					}
					else if(i2<100)
					{
						strcat(tmpstr,"0");
					}
					strcat(tmpstr,tmpstr2);
					strcat(tmpstr,".bmp");
					
					hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), tmpstr, 
						IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
					
					if(!hbm&&i2==0)
					{
						startatzero=FALSE;
						continue;
					}
					if(!hbm&&i2==1&&!startatzero)
					{
						break;
					}
					if(/*!hbm||*/!(i2<(int)prototypes[i]->nframes+!startatzero))break;
					
					DDCopyBitmap((LPDIRECTDRAWSURFACE)prototypes[i]->lpDDSFrames[i2-!startatzero], hbm, 0, 0, prototypes[i]->size.x, prototypes[i]->size.y);
					DeleteObject(hbm);
				}
				if(i2<=1)
				{
					for(i2=0;;++i2)
					{
					if(prototypes[i]->lpDDSFrames[i2] &&prototypes[i]->lpDDSFrames[i2]->IsLost()!=DDERR_SURFACELOST)continue;

					if(prototypes[i]->lpDDSFrames[i2])prototypes[i]->lpDDSFrames[i2]->Restore();

						strcpy(tmpstr,prototypes[i]->bitmapfile);
						sprintf(tmpstr2,"%d",i2);
						if(i2<10)
						{
							strcat(tmpstr,"000");
						}
						else if(i2<100)
						{
							strcat(tmpstr,"00");
						}
						else if(i2<1000)
						{
							strcat(tmpstr,"0");
						}
						strcat(tmpstr,tmpstr2);
						strcat(tmpstr,".bmp");
						
					hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), tmpstr, 
						IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
					
					if(!hbm&&i2==0)
					{
						startatzero=FALSE;
						continue;
					}
					if(/*!hbm||*/!(i2<(int)prototypes[i]->nframes+!startatzero))break;
					DDCopyBitmap((LPDIRECTDRAWSURFACE)prototypes[i]->lpDDSFrames[i2-!startatzero], hbm, 0, 0, prototypes[i]->size.x, prototypes[i]->size.y);
					DeleteObject(hbm);
						
					}
				}
			}
		}
	}
					
	
	if(lpDDSBackGround->IsLost()==DDERR_SURFACELOST)
	{
		lpDDSBackGround->Restore();
		hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), backgroundimagefile, 
			IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
		if(hbm)
		{
			GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap
			
			ddsd.dwSize = sizeof( ddsd );
			ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
			ddsd.dwHeight = bm.bmHeight;
			ddsd.dwWidth = bm.bmWidth;
			lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSTmp, NULL );
			
			DDCopyBitmap((LPDIRECTDRAWSURFACE)lpDDSTmp, hbm, 0, 0,bm.bmWidth,bm.bmHeight);
			
			lpDDSBackGround->Blt(NULL,lpDDSTmp,NULL,DDBLT_WAIT,NULL);
			lpDDSTmp->Release();
			DeleteObject(hbm);
		}
	}

	//Items
	for(i=0;i<MAXITEMS;++i)
	{
		if(items[i])items[i]->RestoreSurfaces();
	}

	return TRUE;
}

/*
BOOL engine::SpriteDetectHit(Sprite2 *s1,Sprite2 *s2)
{
	static RECT rect;
	//	if(s1==NULL || s2==NULL)return(FALSE);
	
	if(abs((int)(s1->xpos-s2->xpos))>s1->width+s2->width)return(FALSE);
	if(abs((int)(s1->ypos-s2->ypos))>s1->height+s2->height)return(FALSE);
	
	if(SpriteGetDistance(s1,s2)<s1->collisionrange+s2->collisionrange)return TRUE;
	
	if(s1->usecollisionrect && s2->usecollisionrect)
		return(SpriteRectDetectHit(s1,s2));
	if(!s1->usecollisionrect && !s2->usecollisionrect)
		return(SpriteCircleDetectHit(s1,s2));
	if(s1->usecollisionrect && !s2->usecollisionrect)
	{
		rect.top=(int)s1->ypos+s1->collisionrect.top;
		rect.left=(int)s1->xpos+s1->collisionrect.left;
		rect.bottom=(int)s1->ypos+s1->collisionrect.bottom;
		rect.right=(int)s1->xpos+s1->collisionrect.right;
		return(CircleRectDetectHit((int)s2->xpos+s2->midpoint.x,(int)s2->ypos+s2->midpoint.y,s2->collisionrange,rect));
	}
	if(!s1->usecollisionrect && s2->usecollisionrect)
	{
		rect.top=(int)s2->ypos+s2->collisionrect.top;
		rect.left=(int)s2->xpos+s2->collisionrect.left;
		rect.bottom=(int)s2->ypos+s2->collisionrect.bottom;
		rect.right=(int)s2->xpos+s2->collisionrect.right;
		return(CircleRectDetectHit((int)s1->xpos+s1->midpoint.x,(int)s1->ypos+s1->midpoint.y,s1->collisionrange,rect));
	}
	return(FALSE);
}

BOOL engine::SpriteCircleDetectHit(BaseSprite *s1,BaseSprite *s2)
{
	static float dist;
	static int dx,dy;
	if(s1==NULL||s2==NULL)return(FALSE);
	
	dx=abs(((int)s1->xpos+s1->midpoint.x)-((int)s2->xpos+s2->midpoint.x));
	dy=abs(((int)s1->ypos+s1->midpoint.y)-((int)s2->ypos+s2->midpoint.y));
	dist=(float)sqrt(dx*dx+dy*dy);
	if(dist<s1->collisionrange+s2->collisionrange)return(TRUE);
	
	return(FALSE);
}*/

/*
BOOL engine::CircleRectDetectHit(int Mx,int My,int r,RECT rect)
{
	if(PointInRect(Mx,My,rect))return(TRUE);
	if(Mx>=rect.left && Mx<=rect.right)
	{
		if(abs(My-rect.top)<r)return(TRUE);
		if(abs(My-rect.bottom)<r)return(TRUE);
		return(FALSE);
	}
	if(My>=rect.top && My<=rect.bottom)
	{
		if(abs(Mx-rect.left)<r)return(TRUE);
		if(abs(Mx-rect.right)<r)return(TRUE);
		return(FALSE);
	}
	if(GetDistance(Mx,My,rect.left,rect.top)<r)return(TRUE);
	if(GetDistance(Mx,My,rect.right,rect.top)<r)return(TRUE);
	if(GetDistance(Mx,My,rect.left,rect.bottom)<r)return(TRUE);
	if(GetDistance(Mx,My,rect.right,rect.bottom)<r)return(TRUE);
	return(FALSE);
}
*/
BOOL Engine2::SpriteRectDetectHit(Sprite2 *s1,Sprite2 *s2)
{
	
	if(s2->position.x>s1->position.x+s1->size.x
		||s1->position.x>s2->position.x+s2->size.x
		||s2->position.y>s1->position.y+s1->size.y
		||s1->position.y>s2->position.y+s2->size.y
		)return FALSE;

	return TRUE;
/*	rect.top=(int)s2->position.y;
	rect.left=(int)s2->position.x;
	rect.right=(int)s2->position.x+s2->size.x;
	rect.bottom=(int)s2->position.y+s2->size.y;
	
	p.x=(int)s1->position.x;
	p.y=(int)s1->position.y;
	if(PointInRect(p,rect))return(TRUE);
	
	p.x=(int)s1->position.x+s1->size.x;
	p.y=(int)s1->position.y;
	if(PointInRect(p,rect))return(TRUE);
	
	p.x=(int)s1->position.x;
	p.y=(int)s1->position.y+s1->size.y;
	if(PointInRect(p,rect))return(TRUE);
	
	p.x=(int)s1->position.x+s1->size.x;
	p.y=(int)s1->position.y+s1->size.y;
	if(PointInRect(p,rect))return(TRUE);
	
	return(FALSE);*/
}
/*
float engine::GetDistance(int x1,int y1,int x2,int y2)
{
	x1=x1-x2;
	y1=y1-y2;
	return((float)sqrt(x1*x1+y1*y1));
}*/

Engine2::Engine2()
{
	memset(this,0,sizeof(*this));
	bActive=TRUE;
	framenumber=0;
	currentnumsprites=0;
	currentnumitems=0;
	pause=FALSE;
	showinfo=FALSE;
	gamespeed=1.0f;
	cpf=new CPackFile;
}

void Engine2::Update()
{
	int i;
	static UINT lastfpsupdate=0;
	static int framecount=0;
	POINT p;
	UINT tframe;

	tframe=timeGetTime();

	soundsys.ReleaseUnusedBuffers();

	currentnumsprites=0;
	currentnumitems=0;

	keyboard.UpdateKeyboard();
	mouse.Update();

	tnow=timeGetTime()-totalpausetime;

	if(pause)
	{
		totalpausetime+=tnow-tplastupdate;
		tnow-=tnow-tplastupdate;
	}

	if(timeGetTime()-lastfpsupdate>=1000)
	{
		lastfpsupdate=timeGetTime();
		fps=framecount;
		framecount=0;
	}
	framecount++;

	if(!pause)
	{
		ScreenPos.x+=ScrollSpeed.x*(tnow-tplastupdate)/1000;
		ScreenPos.y+=ScrollSpeed.y*(tnow-tplastupdate)/1000;
		
		for(i=0;i<MAXSPRITES;++i)
		{
			if(sprites[i])
			{
				++currentnumsprites;
				if(sprites[i]->deletedisabled&&!sprites[i]->enabled)
				{
					DeleteSprite(i);
					continue;
				}
				if(sprites[i]->deleteoutscreen&&!SpriteInScreen(sprites[i]))
				{
					if(sprites[i]->tminlife<sprites[i]->age)
					{
						DeleteSprite(i);
						continue;
					}
				}
				if(sprites[i]->deleteoutexscreen&&!SpriteInExtendedScreen(sprites[i]))
				{
					if(sprites[i]->tminlife<sprites[i]->age)
					{
						DeleteSprite(i);
						continue;
					}
				}
				/*			if(sprites[i]->enabled&&sprites[i]->tdisable<=0)
				{
				sprites[i]->Disable();
				tdisable=-1;
			}*/
				if(sprites[i]->enabled&&sprites[i]->disableoutexscreen&&!SpriteInExtendedScreen(sprites[i]))
				{
					sprites[i]->Disable();
					//sprites[i]->tpdisabled=tnow;
					sprites[i]->tdisabled=0;
				}
				
				//if(SpriteInScreen(sprites[i]))
				if(sprites[i]->gravdep&&sprites[i]->type!=SPRITETYPE_EXPLOSION)sprites[i]->speed.y+=gravity;
				sprites[i]->Update((int)((float)(tnow-tplastupdate)*gamespeed));
				
				//Bouncing
				if(sprites[i]->bouncing)
				{
					if(sprites[i]->position.x<ScreenPos.x)
					{
						sprites[i]->position.x=ScreenPos.x;
						sprites[i]->speed.x*=sprites[i]->bouncestrenght;
						if(sprites[i]->speed.x<0)sprites[i]->speed.x*=-1;
						if(sprites[i]->speed.x<ScrollSpeed.x)sprites[i]->speed.x=ScrollSpeed.x;
					}
					else if(sprites[i]->position.x+sprites[i]->size.x>screenwidth+ScreenPos.x)
					{
						sprites[i]->position.x=(float)screenwidth-sprites[i]->size.x+ScreenPos.x;
						sprites[i]->speed.x*=sprites[i]->bouncestrenght;
						if(sprites[i]->speed.x>0)sprites[i]->speed.x*=-1;
						if(sprites[i]->speed.x>ScrollSpeed.x)sprites[i]->speed.x=ScrollSpeed.x;
					}
					if(sprites[i]->position.y<ScreenPos.y)
					{
						sprites[i]->position.y=ScreenPos.y;
						sprites[i]->speed.y*=-sprites[i]->bouncestrenght;
						if(sprites[i]->speed.y<0)sprites[i]->speed.y*=-1;
						if(sprites[i]->speed.y<ScrollSpeed.y)sprites[i]->speed.y=ScrollSpeed.y;
					}
					else if(sprites[i]->position.y+sprites[i]->size.y>screenheight+ScreenPos.y)
					{
						sprites[i]->position.y=(float)screenheight-sprites[i]->size.y+ScreenPos.y;
						sprites[i]->speed.y*=sprites[i]->bouncestrenght;
						if(sprites[i]->speed.y>0)sprites[i]->speed.y*=-1;
						if(sprites[i]->speed.y>ScrollSpeed.y)sprites[i]->speed.y=ScrollSpeed.y;
					}
				}
			}
			
		}
		
		currentnumevents=0;
		for(i=0;i<MAXEVENTS;++i)
		{
			if(events[i])
			{
				++currentnumevents;
				if(events[i]->del)
				{
					DeleteEvent(i);
					continue;
				}
				events[i]->Update((UINT)((float)(tnow-tplastupdate)*gamespeed));
			}
		}

		for(i=0;i<MAXITEMS;++i)
		{
			if(items[i])
			{
				++currentnumitems;
				items[i]->Update((int)((float)(tnow-tplastupdate)*gamespeed));
				if(items[i]->enabled&&ScreenPointHitsItem(mouse.GetPos(),items[i],&p))
				{
					items[i]->bfocused=TRUE;
					items[i]->focpos.x=p.x;
					items[i]->focpos.y=p.y;
				}
				else
					items[i]->bfocused=FALSE;
			}
		}

	}//!pause
	else//count sprites&items&events
	{
		for(i=0;i<MAXITEMS;++i)
		{
			if(items[i])
			{
				items[i]->Update((int)((float)(tnow-tplastupdate)*gamespeed));
				++currentnumitems;
				if(items[i]->enabled&&ScreenPointHitsItem(mouse.GetPos(),items[i],&p))
				{
					items[i]->bfocused=TRUE;
					items[i]->focpos.x=p.x;
					items[i]->focpos.y=p.y;
				}
				else
					items[i]->bfocused=FALSE;
			}
		}
		for(i=0;i<MAXSPRITES;++i)
		{
			//sprites[i]->Update(tnow);
			if(sprites[i])++currentnumsprites;
		}
		currentnumevents=0;
		for(i=0;i<MAXEVENTS;++i)
		{
			if(events[i])
			{
				++currentnumevents;
			}
		}
	}


	//Cursor
	if(cursor&&cursor->enabled)
	{
		p=mouse.GetPos();
		cursor->position.x=(float)(p.x-cursor->size.x/2);
		cursor->position.y=(float)(p.y-cursor->size.y/2);
		cursor->Update(frametime);
	}


	if(updateproc)updateproc();
	tplastupdate=tnow;
	DrawAll();
	if(!pause)DetectHits();
	frametime=timeGetTime()-tframe;
}

BOOL Engine2::SpriteInScreen(Sprite2 *s)
{
	if(
		!s->enabled
		||s->position.x>(float)screenwidth+ScreenPos.x
		||s->position.y>(float)screenheight+ScreenPos.y
		||s->position.x<-(float)s->size.x+ScreenPos.x
		||s->position.y<-(float)s->size.y+ScreenPos.y
	)
	return FALSE;

	return TRUE;
}
	
BOOL Engine2::SpriteInExtendedScreen(Sprite2 *s)
{
	if(
		!s->enabled
		||s->position.x>(float)screenwidth+EXTENDEDSCREENRANGE+ScreenPos.x
		||s->position.y>(float)screenheight+EXTENDEDSCREENRANGE+ScreenPos.y
		||s->position.x<-(float)s->size.x-EXTENDEDSCREENRANGE+ScreenPos.x
		||s->position.y<-(float)s->size.y-EXTENDEDSCREENRANGE+ScreenPos.y
	)
	return FALSE;

	return TRUE;
}
	
BOOL Engine2::SpriteFullInScreen(Sprite2 *s)
{
	if(
		!s->enabled
		||s->position.x+(float)s->size.x/2>(float)screenwidth+ScreenPos.x
		||s->position.y+(float)s->size.y/2>(float)screenheight+ScreenPos.y
		||s->position.x<ScreenPos.x
		||s->position.y<ScreenPos.y
	)
	return FALSE;

	return TRUE;
}

Engine2::~Engine2()
{
	delete cpf;
}

void Engine2::OnWM(UINT message,WPARAM wParam,LPARAM lParam)
{

	BOOL deactivated;
	static BOOL pausebeforedeactivation=TRUE;
	//static BOOL pbdset=FALSE;

    switch( message )
    {
    case WM_ACTIVATEAPP:
    //case WM_ACTIVATE:
		deactivated= LOWORD(wParam)==WA_INACTIVE;
		bActive=!deactivated;
		if(bActive&&initialized)
		{
			RestoreSurfaces();
			totalpausetime+=timeGetTime()-tppauseon;
			tnow=timeGetTime()-totalpausetime;
			if(pause)
				Pause();
			DrawAll();
		}
		else if(deactivated&&initialized)
		{
			if(!pause)
			{
				Pause();
			}
		}
		break;
	case WM_DISPLAYCHANGE:
		break;
    case WM_CREATE:
		SetCapture(hwnd);
		SetCursor(NULL);
		break;
    case WM_SETCURSOR:
		SetCapture(hwnd);
		SetCursor(NULL);
		break;
    case WM_TIMER:
		break;
	case WM_CHAR:
		break;
	case WM_ENTERSIZEMOVE:
		if(!pause)Pause();
		break;
	case WM_EXITSIZEMOVE:
		DrawAll();
		if(pause)Pause();
		break;
    case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_ESCAPE:
			//exit(0);
			break;
		default:
			//exit(wParam);
			break;
		}
		break;
	case WM_KEYUP:
		break;
    case WM_PAINT:
		DrawAll();
		break;
    case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		//Mouse click on Item
		int i;
		POINT p;
		for(i=0;i<MAXITEMS;++i)
		{
			if(items[i]&&items[i]->enabled)
			{
				if(ScreenPointHitsItem(mouse.GetPos(),items[i],&p))
				{
					OnItemClick(items[i]);
					items[i]->OnPress(p.x,p.y);
					break;
				}
			}
		}

		break;
	}

}
	
void Engine2::SpawnSprite(Sprite2 *s)//In Screen
{
	Sprite2 *nearestsprite;
	int i=0;

	do{
		s->position.x=(float)random((int)ScreenPos.x,(int)(ScreenPos.x+screenwidth-s->size.x));
		s->position.y=(float)random((int)ScreenPos.y,(int)(ScreenPos.y+screenheight-s->size.y));
		s->angle=(float)random(0,359);
		nearestsprite=GetNearestSprite(s);
		++i;
	}while(SpriteGetDistance(s,nearestsprite)<150 && i<100);
	
	s->enabled=TRUE;
	s->speed.x=0;
	s->speed.y=0;
	s->hitpoints=s->maxhitpoints;
	s->shieldstrenght=s->maxshieldstrenght;
	s->smoking=FALSE;
	s->energy=s->maxenergy;
	s->tlastfire=0;
	s->tdisabled=0;
	s->tdisable=-1;

	if(s->type!=SPRITETYPE_BONUS)
	{
		s->tdamagemulti=0;
		s->damagemultiplicator=1.0f;
	}
	//s->tpenablehitdetection=0;
	s->tenablehitdetection=-1;
	//s->tplastframechange=0;
	s->tframechange=0;
	s->tlastspecial=s->tspecialdelay;
	if(s->defaultweapon)
	{
		s->weapon=s->defaultweapon;
		//s->nlaunch=s->defaultweapon->nlaunch;
	}
	if(respawnproc)respawnproc(s);
}

void Engine2::SpawnSpriteInCircle(Sprite2 *s,float mx,float my,float r)
{
	Sprite2 *nearestsprite;
	int i=0;

	do{
		s->position.x=mx+(float)random(0,(int)(2*r))-r;
		s->position.y=my+(float)random(0,(int)(2*r))-r;
		s->angle=(float)random(0,359);
		nearestsprite=GetNearestSprite(s);
		++i;
	}while(SpriteGetDistance(s,nearestsprite)<150&&GetDistance(mx,my,s->position.x+s->size.x/2,s->position.y+s->size.y/2)>r && i<100);
	s->enabled=TRUE;
	s->speed.x=0;
	s->speed.y=0;
	s->hitpoints=s->maxhitpoints;
	s->shieldstrenght=s->maxshieldstrenght;
	s->smoking=FALSE;
	s->energy=s->maxenergy;
	s->tlastfire=0;
	s->tdisabled=0;
	s->tdisable=-1;
	s->tenablehitdetection=-1;
//	s->tplastframechange=0;
	s->tframechange=0;
	s->tlastspecial=s->tspecialdelay;
	if(s->defaultweapon)
	{
		s->weapon=s->defaultweapon;
		//s->nlaunch=s->defaultweapon->nlaunch;
	}

}

BOOL Engine2::SpriteDetectHit(Sprite2 *s1,Sprite2 *s2)
{
	float dist;
	float dx,dy;
	BOOL b;
	if(!(s1&&s2))return(FALSE);
	
	if(s1->mk2collide&&s2->mk2collide)
	{
		b=MK2DetectHit(s1,s2);
		return b;
	}
	else
	{
		dx=(float)fabs((s1->position.x+s1->size.x/2)-(s2->position.x+s2->size.x/2));
		dy=(float)fabs((s1->position.y+s1->size.y/2)-(s2->position.y+s2->size.y/2));
		dist=(float)sqrt(dx*dx+dy*dy);
		if(dist<s1->collisionrange+s2->collisionrange)return(TRUE);
	}
	return(FALSE);
}

BOOL Engine2::Initialize(HINSTANCE hInstance,int sw,
		int sh,int bpp,BOOL fs,int backbuffers,WNDPROC wndproc,BOOL use2ndDisplaydevice)
{

	if(initialized)return(FALSE);
	
	DDSURFACEDESC       ddsd;
	DDSCAPS             ddscaps;
	HRESULT             ddrval;
	BOOL				ok=TRUE;
	char				tmpstr[64];
	//		DDCAPS				ddcaps;
	WNDCLASS wc;
	LPDIRECTDRAW lpDD;

	fullscreen=fs;
	screenwidth=sw;
	screenheight=sh;
	
	//		RegisterClass( wc );
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndproc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;//LoadIcon( hInstance, IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WNDCLASSNAME;
	if(RegisterClass( &wc )==0)return(FALSE);
	
	/*
	* create a window
	*/
	if(!fullscreen)
	{
		hwnd = CreateWindowEx(WS_EX_APPWINDOW,//WS_EX_TOPMOST,
			WNDCLASSNAME,WNDTITLE,WS_POPUPWINDOW|WS_CAPTION,
			0, 0,
			screenwidth,
			screenheight,
			NULL,NULL,hInstance,
			NULL );
	}
	else
	{
		hwnd = CreateWindowEx(WS_EX_TOPMOST,
			WNDCLASSNAME,WNDTITLE,WS_POPUP|WS_VISIBLE,
			0, 0,
			GetSystemMetrics( SM_CXSCREEN ),
			GetSystemMetrics( SM_CYSCREEN ),
			NULL,NULL,hInstance,
			NULL );
	}
	
	if( !hwnd )return FALSE;
		
	ShowWindow( hwnd, SW_SHOW );
	UpdateWindow( hwnd );
	SetFocus(hwnd);

	//enumerate drivers

	if(use2ndDisplaydevice)
	{
		DirectDrawEnumerate(&DDEnumCb,NULL);
		DirectDrawEnumerate(&DDEnumCb,NULL);	
	}
	else
	{
		lpDisplayDevice=NULL;
	}

	// create the main DirectDraw object
	ddrval = DirectDrawCreate( lpDisplayDevice, &lpDD, NULL );
	if( ddrval != DD_OK )
	{
		strcpy(errormessage,"IDirectDrawCreate failed: ");
		PrintDDError(errormessage,ddrval);
		OnError();
		ok=FALSE;
	}

	//Direct Draw 2
/*	ddrval = lpDD->SetCooperativeLevel(hwnd, DDSCL_NORMAL); 
	if(ddrval != DD_OK)
	{
		strcpy(errormessage,"IDirectDraw::SetCooperativeLevel failed: ");
		PrintDDError(errormessage,ddrval);
		OnError();
		ok=FALSE;
	}

	ddrval = lpDD->QueryInterface(IID_IDirectDraw2, (LPVOID *)&lpDD2); 
	if(ddrval != DD_OK) 
	{
		strcpy(errormessage,"IDirectDraw::QueryInterface failed: ");
		PrintDDError(errormessage,ddrval);
		strcpy(errormessage,", possible cause: old DirectX version");
		OnError();
		return FALSE;
	}
*/	

	if(fullscreen)
	{
		// Get exclusive mode
		ddrval = lpDD->SetCooperativeLevel( hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
		if( ddrval != DD_OK )
		{
			strcpy(errormessage,"IDirectDraw::SetCooperativeLevel failed: ");
			PrintDDError(errormessage,ddrval);
			OnError();
			ok=FALSE;
		}
		
		// Set the video mode
		ddrval = lpDD->SetDisplayMode( screenwidth, screenheight, bpp);
		if(ddrval!=DD_OK)
		{
			strcpy(errormessage,"IDirectDraw::SetDisplayMode to ");
			sprintf(tmpstr,"%d",screenwidth);
			strcat(errormessage,tmpstr);
			strcat(errormessage,"x");
			sprintf(tmpstr,"%d",screenheight);
			strcat(errormessage,tmpstr);
			strcat(errormessage,"x");
			sprintf(tmpstr,"%d",bpp);
			strcat(errormessage,tmpstr);
			strcat(errormessage," failed: ");
			PrintDDError(errormessage,ddrval);
			OnError();
			ok=FALSE;				
		}
		
		// Create the primary surface with back buffers
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE|DDSCAPS_FLIP|DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = backbuffers;
		ddrval = lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSPrimary, NULL );
		if( ddrval != DD_OK )
		{
			strcpy(errormessage,"IDirectDraw::CreateSurface failed: ");
			PrintDDError(errormessage,ddrval);
			OnError();
			ok=FALSE;
		}
		
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		ddrval = lpDDSPrimary->GetAttachedSurface(&ddscaps, &lpDDSBackBuffer);
		if( ddrval != DD_OK )
		{
			strcpy(errormessage,"IDirectDraw::GetAttachedSurface failed: ");
			PrintDDError(errormessage,ddrval);
			OnError();
			ok=FALSE;
		}
	}
	else
	{
		// window mode
		ddrval = lpDD->SetCooperativeLevel( hwnd, DDSCL_NORMAL);
		if( ddrval != DD_OK )
		{
			strcpy(errormessage,"IDirectDraw::SetCooperativeLevel failed: ");
			PrintDDError(errormessage,ddrval);
			OnError();
			ok=FALSE;
		}
		
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		ddrval = lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSPrimary, NULL );
		if( ddrval != DD_OK )
		{
			strcpy(errormessage,"IDirectDraw::CreateSurface failed: ");
			PrintDDError(errormessage,ddrval);
			OnError();
			ok=FALSE;
		}
		
		ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;	
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		
		  ddsd.dwWidth = screenwidth;
		  ddsd.dwHeight = screenheight;
		  
			ddrval = lpDD->CreateSurface(&ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSBackBuffer,NULL);
			if( ddrval != DD_OK )
			{
				exit(0);
				return(FALSE);
			}
				
	}
		
		//Direct Draw Clipper
		ddrval = lpDD->CreateClipper(0,&lpDDClip,NULL);
		if( ddrval != DD_OK )
		{
			strcpy(errormessage,"IDirectDraw::CreateClipper failed: ");
			PrintDDError(errormessage,ddrval);
			OnError();
			ok=FALSE;
		}

		lpDDClip->SetHWnd(0,hwnd);
		if(fullscreen)lpDDSBackBuffer->SetClipper(lpDDClip);
		
		//if(fullscreen)lpDDSBackBuffer->SetClipper(lpDDClip);
		//else 
			lpDDSPrimary->SetClipper(lpDDClip);
		
		ClearSurface(lpDDSPrimary);
		//Direct Sound Initialisation
/*		ddrval = DirectSoundCreate(NULL, &lpDirectSound, NULL);
		if( ddrval != DS_OK )
		{
			strcpy(errormessage,"IDirectSoundCreate failed: ");
			PrintDSError(errormessage,ddrval);
			OnError();
			ok=FALSE;
		}
		else
		{
			lpDirectSound->SetCooperativeLevel(hwnd,DSSCL_PRIORITY );	
			if( ddrval != DS_OK )
			{
				strcpy(errormessage,"IDirectSound::SetCooperativeLevel failed: ");
				PrintDSError(errormessage,ddrval);
				OnError();
				ok=FALSE;
			}
		}*/
		if(!soundsys.Initialize(hwnd,DSSCL_PRIORITY ))
		{
			strcpy(errormessage,"DSPlayer::Initialize failed");
			OnError();
			ok=FALSE;
		}
		
		ddrval = DirectInputCreate(hInstance, DIRECTINPUT_VERSION, &lpDirectInput, NULL); 
		if FAILED(ddrval) 
		{
			strcpy(errormessage,"IDirectInputCreate failed: ");
			PrintDIError(errormessage,ddrval);
			OnError();
			ok=FALSE;
		} 
	//init directinput keyboard
	if(!keyboard.Initialize(lpDirectInput,hwnd))
	{
		strcpy(errormessage,"DirectInput: Keyboard could not be initialized");
		OnError();
	}
	//init directinput mouse
	if(!mouse.Initialize(lpDirectInput,hwnd))
	{
		strcpy(errormessage,"DirectInput: Mouse could not be initialized");
		OnError();
	}

		if(fullscreen)
		{
			/*SetCapture(hwnd);*/
			SetCursor(NULL);
			ShowCursor(FALSE);
		}
		//if(!ok)return(FALSE);
		initialized=TRUE;
		lpDD2=lpDD;
		return(ok);
}

BOOL Engine2::RenderMap(LPDIRECTDRAWSURFACE3 lpDDS)
{

	int x,y;
	RECT destrect;
	POINT firstfield;
	firstfield.x=(int)(ScreenPos.x/FIELDSIZE);
	firstfield.y=(int)(ScreenPos.y/FIELDSIZE);

	for(x=firstfield.x;x<MAPSIZE;++x)
	{
		if(x*FIELDSIZE>(int)screenwidth+ScreenPos.x)
		{
			break;
		}
		for(y=firstfield.y;y<MAPSIZE;++y)
		{
			if(y*FIELDSIZE>(int)screenheight+ScreenPos.y)break;
			destrect.left=x*FIELDSIZE-(int)(ScreenPos.x+0.5);
			destrect.right=destrect.left+FIELDSIZE;
			destrect.top=y*FIELDSIZE-(int)(ScreenPos.y+0.5);
			destrect.bottom=destrect.top+FIELDSIZE;

			if(destrect.right<0||
				destrect.left>(int)screenwidth||
				destrect.bottom<0||
				destrect.top>(int)screenheight)break;

			lpDDS->Blt(&destrect,Map[x][y].lpDDS,NULL,DDBLT_WAIT,NULL);

		}
	}

	return TRUE;
}

BOOL Engine2::LoadMap(char *file)
{
	int i,i2,i3;
	HANDLE hfile;
	MAPFILESTRUCT mapstruct;
	HBITMAP hbm;
	POINT coordinates;
	DDSURFACEDESC ddsd;
	HRESULT hres;
	unsigned long ul;
	BITMAP bm;

	
	hfile=CreateFile(file,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(!hfile)return(FALSE);

	//size=GetFileSize(hfile,NULL);
	//string=new char[size+1];
	
	for(i=0;i<MAPSIZE*MAPSIZE;++i)
	{
		ReadFile(hfile,(LPVOID)&mapstruct,sizeof(mapstruct),&ul,NULL);
		
		hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), mapstruct.bitmapfile, 
			IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
			
		if(!hbm)break;
		coordinates.x=i%MAPSIZE;
		coordinates.y=(int)(i/MAPSIZE);
		strcpy(Map[coordinates.x][coordinates.y].bitmapfile,mapstruct.bitmapfile);

		for(i2=0;i2<MAPSIZE;++i2)
		{
			for(i3=0;i3<MAPSIZE;++i3)
			{
				if(stricmp(Map[i2][i3].bitmapfile,mapstruct.bitmapfile)==0&&(i2!=coordinates.x||i3!=coordinates.y))
				{
					Map[coordinates.x][coordinates.y].lpDDS=Map[i2][i3].lpDDS;
					goto NOSURFACECREATE;
					break;
				}
			}

		}
		GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		ddsd.dwHeight = bm.bmHeight;
		ddsd.dwWidth = bm.bmWidth;
		hres=lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&Map[coordinates.x][coordinates.y].lpDDS, NULL );
		if(hres!=DD_OK)
		{
			DeleteObject(hbm);
			break;
		}
NOSURFACECREATE:
		DDCopyBitmap((LPDIRECTDRAWSURFACE)Map[coordinates.x][coordinates.y].lpDDS,hbm,0,0,bm.bmWidth,bm.bmHeight);
		DeleteObject(hbm);
		
		Map[coordinates.x][coordinates.y].passable=mapstruct.passable;
		
	}
	CloseHandle(hfile);
	return TRUE;
}

BOOL Engine2::MakeScreenShot()
{
	HDC hdc;
	char tmpstr[64];
	//char tmpstr2[64];
	int i;

	CreateDirectory("screenshots",NULL);
	for(i=0;i<1000;++i)
	{
		sprintf(tmpstr,"%s%03d%s","screenshots\\shot",i,".bmp");
		if(!FileExistCurDir(tmpstr))break;
		else if(i==999)return FALSE;
	}
	
	if(lpDDSBackBuffer->GetDC(&hdc)!=DD_OK)return FALSE;
	SaveDC2File(hdc,tmpstr);	
	
	lpDDSBackBuffer->ReleaseDC(hdc);
	return TRUE;
}
