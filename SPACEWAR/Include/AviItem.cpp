#include "aviitem.h"

AviItem::AviItem()
	{
	BaseItem::BaseItem();
		CurrentTime=0;
		FileOpen=FALSE;
		tplastupdate=0;
		size.x=320;
		size.y=240;
		speed.x=0;
		speed.y=0;
		Loop=TRUE;
		isPlaying=FALSE;
		enabled=FALSE;
		reverse=FALSE;
		attach=NULL;
		attachpos.x=0;
		attachpos.y=0;
		AVIFileInit();
	}

AviItem::~AviItem()
	{
		AVIFileExit();          // releases AVIFile library 
		Close();
	}

BOOL AviItem::InScreen()
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

void AviItem::Play(BOOL loop)
{
	if(!FileOpen)return;
	Loop=loop;
	isPlaying=TRUE;
	enabled=TRUE;
	reverse=FALSE;
}

void AviItem::Reverse()
{
	isPlaying=TRUE;
	enabled=TRUE;
	reverse=TRUE;
}

void AviItem::Pause()
{
	if(!FileOpen)return;
	isPlaying=FALSE;
}

void AviItem::Stop()
{
	isPlaying=FALSE;
	enabled=FALSE;
	CurrentTime=0;
}

	BOOL AviItem::Open(LPCSTR file)
	{
		if(FileOpen)Close();
		enabled=TRUE;
		LPVOID data;
  
		if(AVIFileOpen(&pfile, file, OF_SHARE_DENY_WRITE, 0L)!=0)
			return FALSE;

		if(AVIFileGetStream(pfile,&pstream,streamtypeVIDEO,0)!=0)
			return FALSE;

		if(AVIStreamInfo(pstream,&streaminfo,sizeof(streaminfo))!=0)
			return FALSE;

		if((pframe=AVIStreamGetFrameOpen(pstream,NULL))==NULL)
			return FALSE;

		data=AVIStreamGetFrame(pframe,AVIStreamStart(pstream));
		if(data==NULL)return FALSE;

		DibInfo((HDIB)data,&bminfo);

		size.x=bminfo.biWidth;
		size.y=bminfo.biHeight;

		FileOpen=TRUE;
		return TRUE;
	}

	void AviItem::Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y)
	{
		if(!FileOpen)return;
		if(!enabled)return;
		if(!drawdata)return;
		HDC hdc;
		RECT destrect,srcrect;
		if(lpDDS->GetDC(&hdc)!=DD_OK)
			return;

			
		destrect.left=x;
		destrect.right=x+size.x;
		destrect.top=y;
		destrect.bottom=y+size.y;
			
		srcrect.left=0;
		srcrect.right=bminfo.biWidth;
		srcrect.top=0;
		srcrect.bottom=bminfo.biHeight;

		PaintDIB(hdc,&destrect,(HDIB)drawdata,&srcrect,NULL);
		lpDDS->ReleaseDC(hdc);
	}

	void AviItem::Update(UINT dtime)
	{
		//UINT dtime;
		int i;
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
		if(isPlaying&&!reverse)
		{
		CurrentTime+=dtime;
		
		drawdata=AVIStreamGetFrame(pframe,AVIStreamTimeToSample(pstream,(LONG)CurrentTime));
		if(drawdata==NULL)
		{
			if(Loop)
			{
			CurrentTime=0;
			drawdata=AVIStreamGetFrame(pframe,AVIStreamTimeToSample(pstream,(LONG)CurrentTime));
			if(drawdata==NULL)
			{
				enabled=FALSE;
				Close();
			}
			}
			else
				Stop();
		}
		}
		else if(isPlaying&&reverse)
		{
			i=(int)CurrentTime-(int)dtime;
			if(i<0)CurrentTime=AVIStreamSampleToTime(pstream,AVIStreamLength(pstream)-1);
			else CurrentTime=(UINT)i;

		drawdata=AVIStreamGetFrame(pframe,AVIStreamTimeToSample(pstream,(LONG)CurrentTime));
		if(drawdata==NULL)
		{
			if(Loop)
			{
			CurrentTime=0;
			drawdata=AVIStreamGetFrame(pframe,AVIStreamTimeToSample(pstream,(LONG)CurrentTime));
			if(drawdata==NULL)
			{
				enabled=FALSE;
				Close();
			}
			}
			else
				Stop();
		}
		}
		
		tplastupdate=e->tnow;
	}

	void AviItem::Close()
	{
		if(!FileOpen)return;
		AVIFileRelease(pfile);  // closes the file 
		FileOpen=FALSE;
		enabled=FALSE;
		drawdata=NULL;
	}
