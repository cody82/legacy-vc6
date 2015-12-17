#include "cmdlineitem.h"

CmdLineItem::CmdLineItem()
{
	BaseItem::BaseItem();
	color[0]=255;
	color[1]=255;
	color[2]=255;
	tlinedeleteinterval=0;
	tlastdelete=0;
	strcpy(text,"");
	maxlines=1000;
	nlines=0;
}

CmdLineItem::~CmdLineItem()
{
}

void CmdLineItem::Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y)
{
		HDC	hdc;
		RECT rect;
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
			SetBkMode(hdc,TRANSPARENT);
			SetTextColor( hdc, RGB( color[0], color[1], color[2] ) );
			DrawText(hdc,text,-1,&rect,DT_CENTER);
			lpDDS->ReleaseDC(hdc);
		}

}

void CmdLineItem::Update(UINT dtime)
{
	CountLines();
	while(nlines>maxlines)
	{
		DeleteFirstLine();
		CountLines();
	}

	if(tlinedeleteinterval>0)tlastdelete+=dtime;
	if(tlinedeleteinterval>0&&tlastdelete>=tlinedeleteinterval)
	{
		DeleteFirstLine();
		tlastdelete=0;
	}
}

void CmdLineItem::DeleteFirstLine()
{
	char *s;
	if(strlen(text)==0)return;
	s=strstr(text,"\n");
	if(strlen(s)>0)
	{
		strcpy(text,++s);
	}
	else
		strcpy(text,"");
}

void CmdLineItem::CountLines()
{
	UINT ui=1;
	char *s;

	s=text;
	do
	{
		if(s==strstr(s,"\n"))break;
		s=strstr(s,"\n");
		if(s)++ui;
	}while(s);

	nlines=ui;
}