#include "bitmapitem.h"

BitmapItem::BitmapItem()
{
	BaseItem::BaseItem();
	lpDDSBitmap=NULL;
	size.x=0;
	size.y=0;
	attach=NULL;
	attachpos.x=0;
	attachpos.y=0;
	speed.x=0;
	speed.y=0;
	tplastupdate=0;
	colorkey=FALSE;
}

BitmapItem::~BitmapItem()
{
	if(lpDDSBitmap)lpDDSBitmap->Release();
}

void BitmapItem::SetColorkey(int r,int g,int b)
{
	if(lpDDSBitmap)
	{
		DDSetColorKey((LPDIRECTDRAWSURFACE)lpDDSBitmap,RGB(r,g,b));
		colorkey=TRUE;
	}
}

BOOL BitmapItem::InScreen()
{
	if(!noscroll)
	{
	if(
		position.x+(float)size.x<e->ScreenPos.x||
		position.y+(float)size.y<e->ScreenPos.y||
		position.x>e->ScreenPos.x+(float)e->screenwidth||
		position.y>e->ScreenPos.y+(float)e->screenheight

		)return FALSE;
	return TRUE;
	}
	else //noscroll
	{
	if(
		position.x+(float)size.x<0||
		position.y+(float)size.y<0||
		position.x>(float)e->screenwidth||
		position.y>(float)e->screenheight

		)return FALSE;
	return TRUE;
	}
}

BOOL BitmapItem::Load(LPSTR file,BOOL autocolorkey,LPDIRECTDRAW dd)
{
		HBITMAP				hbm;
		DDSURFACEDESC       ddsd;
		HRESULT             ddrval;
		BITMAP				bm;

		if(!e&&!dd)return FALSE;
		if(!file)return FALSE;

	hbm = (HBITMAP)LoadImage(NULL,
		file, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	
	if(!hbm)
	{
		return FALSE;
	}

		GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap
		size.x=bm.bmWidth;
		size.y=bm.bmHeight;
			
			ddsd.dwSize = sizeof( ddsd );
			ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;//|DDSCAPS_SYSTEMMEMORY;
			ddsd.dwHeight = bm.bmHeight;
			ddsd.dwWidth = bm.bmWidth;
			
			if(dd)
			ddrval = dd->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSBitmap, NULL );
		else
			ddrval = e->lpDD->CreateSurface( &ddsd, (LPDIRECTDRAWSURFACE*)&lpDDSBitmap, NULL );

			if(ddrval!=DD_OK)
		{
				DeleteObject(hbm);
			return(FALSE);
		}

	DDCopyBitmap((LPDIRECTDRAWSURFACE)lpDDSBitmap, hbm, 0, 0,size.x,size.y);
	DeleteObject(hbm);

	if(autocolorkey)
	{
		DDSetColorKey((LPDIRECTDRAWSURFACE)lpDDSBitmap, CLR_INVALID);
		colorkey=TRUE;
	}
	enabled=TRUE;
	strcpy(bmpfile,file);

	return TRUE;
}

	void BitmapItem::Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y)
	{
		RECT destrect;
		HRESULT hr;

		if(!enabled)return;
		if(!InScreen())return;
		if(!lpDDSBitmap)return;
		destrect.left=x;
		destrect.right=x+size.x;
		destrect.top=y;
		destrect.bottom=y+size.y;
		

		if(colorkey)
			hr=lpDDS->Blt(&destrect,lpDDSBitmap,NULL,DDBLT_KEYSRC |DDBLT_WAIT,NULL);
		else
			hr=lpDDS->Blt(&destrect,lpDDSBitmap,NULL,DDBLT_WAIT,NULL);

		if(hr!=DD_OK)
		{
		}
	}
	
	void BitmapItem::RestoreSurfaces()
	{
		if(lpDDSBitmap)
	if(lpDDSBitmap->IsLost()==DDERR_SURFACELOST)
	{
		lpDDSBitmap->Restore();
		DDReLoadBitmap((LPDIRECTDRAWSURFACE)lpDDSBitmap,bmpfile);
	}

	}

	void BitmapItem::Update(UINT dtime)
	{
		//UINT dtime;
		if(!enabled)
		{
			tplastupdate=e->tnow;
			return;
		}
		if(!tplastupdate)tplastupdate=e->tnow;
		if(tplastupdate==e->tnow)return;

		//dtime=tnow-tplastupdate;

		if(attach)
		{
			position.x=attach->position.x+attachpos.x;
			position.y=attach->position.y+attachpos.y;
		}
		else
		{
			position.x+=speed.x*(dtime)/1000;
			position.y+=speed.y*(dtime)/1000;
		}
		tplastupdate=e->tnow;
	}
