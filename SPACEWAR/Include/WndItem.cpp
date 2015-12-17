#include "wnditem.h"

WndItem::WndItem()
{
	BaseItem::BaseItem();
	int i;
	for(i=0;i<WNDMAXITEMS;++i)
		items[i]=NULL;
	noscroll=TRUE;
	transparent=TRUE;
}

WndItem::~WndItem()
{
}
	
void WndItem::RestoreSurfaces()
{
	int i;
	for(i=0;i<WNDMAXITEMS;++i)
	{
		if(items[i])items[i]->RestoreSurfaces();
	}

}
	
void WndItem::OnPress(int x,int y)
{
	int i;
	RECT rect;
	POINT p;
	
	p.x=x;
	p.y=y;

	for(i=0;i<WNDMAXITEMS;++i)
	{
		if(items[i]&&items[i]->enabled)
		{
			rect.left=(int)items[i]->position.x;
			rect.right=(int)items[i]->position.x+items[i]->size.x;
			rect.top=(int)items[i]->position.y;
			rect.bottom=(int)items[i]->position.y+items[i]->size.y;
			
			if(PointInRect(p,rect))
			{
				items[i]->OnPress(p.x-rect.left,p.y-rect.top);
			}
		}
	}
}

POINT WndItem::GetCenterPos(BaseItem *bi)
{
	POINT p;
	p.x=0;
	p.y=0;
	if(!bi)return p;
	p.x=size.x/2-bi->size.x/2;
	p.y=size.y/2-bi->size.y/2;
	return p;

}

BOOL WndItem::AddItem(BaseItem *bi)
{
	int i;
	for(i=0;i<WNDMAXITEMS;++i)
	{
		if(!items[i])
		{
			items[i]=bi;
			bi->e=e;
			bi->enabled=TRUE;
			return TRUE;
		}
	}
	return FALSE;
}

void WndItem::Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y)
{
	if(!enabled)return;

	DDBLTFX ddbltfxtmp;
	RECT destrect;
	HRESULT hr;
	int i;
	int x2,y2;

	if(!transparent)
	{
	ddbltfxtmp.dwSize=sizeof(ddbltfxtmp);
	ddbltfxtmp.dwFillColor=color;

	destrect.left=x;
	destrect.right=x+size.x;
	destrect.top=y;
	destrect.bottom=y+size.y;

	hr=lpDDS->Blt(&destrect,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&ddbltfxtmp);	
	if(hr!=DD_OK)
	{
		strcpy(e->errormessage,"ERROR: IDirectDrawSurface::Blt in WndItem::Draw failed: ");
		e->OnError();
	}
	}

	for(i=0;i<WNDMAXITEMS;++i)
	{
		if(items[i])
		{
			x2=x+(int)items[i]->position.x;
			y2=y+(int)items[i]->position.y;
			items[i]->Draw(lpDDS,x2,y2);
		}
	}
}

void WndItem::Update(UINT tnow)
{
	int i;
	RECT rect;

	for(i=0;i<WNDMAXITEMS;++i)
	{
		if(items[i]&&items[i]->enabled)
		{
		if(bfocused)
		{
			rect.left=(int)items[i]->position.x;
			rect.right=(int)items[i]->position.x+items[i]->size.x;
			rect.top=(int)items[i]->position.y;
			rect.bottom=(int)items[i]->position.y+items[i]->size.y;
			if(PointInRect(focpos,rect))
			{
				items[i]->bfocused=TRUE;
				items[i]->focpos.x=focpos.x-(int)position.x;
				items[i]->focpos.y=focpos.y-(int)position.y;
			}
			else
				items[i]->bfocused=FALSE;
		}
		else
			items[i]->bfocused=FALSE;

			items[i]->Update(tnow);
		}
	}
}