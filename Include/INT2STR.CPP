#include "int2str.h"

void DrawLine(LPDIRECTDRAWSURFACE3 lpDDS,int x1,int y1,int x2,int y2,COLORREF c,int width)
{
	HDC hdc;
	HPEN hpen;
	HPEN oldpen;
	POINT oldpos;
	HRESULT hres;

	hpen=CreatePen(PS_SOLID,width,c);
	if(!hpen)return;

		
	while((hres=lpDDS->GetDC(&hdc))==DDERR_WASSTILLDRAWING);
	if(hres!=DD_OK)
	{
		DeleteObject(hpen);
		return;
	}

	oldpen=(HPEN)SelectObject(hdc,hpen);

	if(!MoveToEx(hdc,x1,y1,&oldpos))
	{
		SelectObject(hdc,oldpen);
		DeleteObject(hpen);
		return;
	}

	if(!LineTo(hdc,x2,y2))
	{
		SelectObject(hdc,oldpen);
		DeleteObject(hpen);
		return;
	}

	//Restore
	MoveToEx(hdc,oldpos.x,oldpos.y,NULL);
	SelectObject(hdc,oldpen);
	DeleteObject(hpen);

	lpDDS->ReleaseDC(hdc);
}

void DDPolyLine(LPDIRECTDRAWSURFACE3 lpDDS,POINT *points,int npoints,COLORREF c,int width)
{
	HDC hdc;
	HPEN hpen;
	HPEN oldpen;

	hpen=CreatePen(PS_SOLID,width,c);

	lpDDS->GetDC(&hdc);

	oldpen=(HPEN)SelectObject(hdc,hpen);

	Polyline(hdc,points,npoints);
	
	//Restore
	SelectObject(hdc,oldpen);
	DeleteObject(hpen);

	lpDDS->ReleaseDC(hdc);

}

void DDPolyBezier(LPDIRECTDRAWSURFACE3 lpDDS,POINT *points,int npoints,COLORREF c,int width)
{
	HDC hdc;
	HPEN hpen;
	HPEN oldpen;
	HRESULT hres;

	hpen=CreatePen(PS_SOLID,width,c);
	if(!hpen)return;

		
	while((hres=lpDDS->GetDC(&hdc))==DDERR_WASSTILLDRAWING);
	if(hres!=DD_OK)
	{
		DeleteObject(hpen);
		return;
	}

	oldpen=(HPEN)SelectObject(hdc,hpen);

	PolyBezier(hdc,points,(DWORD)npoints);

	//Restore
	SelectObject(hdc,oldpen);
	DeleteObject(hpen);

	lpDDS->ReleaseDC(hdc);

}

float GetAngle(POINT p1,POINT p2)//Bogenmaß
{
	POINT d;

	d.x=p2.x-p1.x;
	d.y=p2.y-p1.y;

	return (float) atan2(d.y,d.x);
}

void DDPutPixel(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y)
{
	RECT r;
		DDBLTFX ddbltfxtmp;
	ddbltfxtmp.dwSize=sizeof(ddbltfxtmp);
	ddbltfxtmp.dwFillColor=RGB(255,0,0);

	r.left=x;
	r.right=x+1;
	r.top=y;
	r.bottom=y+1;

	lpDDS->Blt(&r,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,&ddbltfxtmp);
}

void DDSimpleBezier(LPDIRECTDRAWSURFACE3 lpDDS,POINT *points,int npoints,COLORREF c,int width)
{
	int i;
	POINT *p;
	int n;
	float f1,f2,d1,d2;
	n=npoints*3+1;
	p=new POINT[n];
	int pstart;

	for(i=0;i<npoints;++i)
	{
		pstart=i*3;
		if(i==0)//Erster Punkt
		{
			p[0]=points[0];
			p[1].x=points[0].x+(points[1].x-points[0].x)/2;
			p[1].y=points[0].y+(points[1].y-points[0].y)/2;
		}
		else if(i==npoints-1)//Letzter Punkt
		{
			p[pstart].x=points[i].x+(points[i-1].x-points[i].x)/2;
			p[pstart].y=points[i].y+(points[i-1].y-points[i].y)/2;

			p[pstart+1]=points[i];
		}
		else//Punkte in der Mitte
		{
			f1=GetAngle(points[i],points[i-1]);
			f2=GetAngle(points[i],points[i+1]);
			d1=GetDistance(points[i].x,points[i].y,points[i-1].x,points[i-1].y)/2;
			d2=GetDistance(points[i].x,points[i].y,points[i+1].x,points[i+1].y)/2;
			f1=(float)((f1+f2)/2+3.14/4);
			p[pstart].x=(int)(points[i].x+cos(f1)*d1);//Control Point
			p[pstart].y=(int)(points[i].y+sin(f1)*d1);

			p[pstart+1]=points[i];//end point

			f1+=(float)(3.14/2);
			p[pstart+2].x=(int)(points[i].x+cos(f1)*d2);//Control Point
			p[pstart+2].y=(int)(points[i].y+sin(f1)*d2);

		}
	}

	DDPolyBezier(lpDDS,p,n,c,width);
}

int random(int min,int max)
{
	static BOOL firstrun=TRUE;
	int number;
	double d;
	static int lastresult=-1;
	if(firstrun)
	{
		srand((unsigned)time( NULL ));
		firstrun=FALSE;
	}
	
	do{
	number=rand();//maximum: 32767
	d=(double)number/(double)RAND_MAX;
	d*=(double)(max-min);
	d+=(double)min;
	number=(int)(d+0.5);
	}while(number==lastresult);

	lastresult=number;
	return(number);
}

float GetDistance(float x1,float y1,float x2,float y2)
{
	float dx,dy;
	dx=(float)fabs(x1-x2);
	dy=(float)fabs(y1-y2);
	return((float)sqrt(dx*dx+dy*dy));
}

char* int2str(int x)
{
	char *string=new char[];
	int i=-1;

	if(x<0){string[++i]='-';x*=-1;}

	if(x<10)
	{
		string[++i]=(char)(x+48);
		string[++i]=0;
		return(string);
	}
	if(x<100)
	{
		string[++i]=(char)(int(x/10)+48);
		x-=int(x/10)*10;
		string[++i]=(char)(x+48);
		string[++i]=0;
		return(string);
	}
	if(x<1000)
	{
		string[++i]=(char)(int(x/100)+48);
		x-=int(x/100)*100;
		string[++i]=(char)(int(x/10)+48);
		x-=int(x/10)*10;
		string[++i]=(char)(x+48);
		string[++i]=0;
		return(string);
	}
	if(x<10000)
	{
		string[++i]=(char)(int(x/1000)+48);
		x-=int(x/1000)*1000;
		string[++i]=(char)(int(x/100)+48);
		x-=int(x/100)*100;
		string[++i]=(char)(int(x/10)+48);
		x-=int(x/10)*10;
		string[++i]=(char)(x+48);
		string[++i]=0;
		return(string);
	}
	if(x<100000)
	{
		string[0]=(char)(int(x/10000)+48);
		x-=int(x/10000)*10000;
		string[1]=(char)(int(x/1000)+48);
		x-=int(x/1000)*1000;
		string[2]=(char)(int(x/100)+48);
		x-=int(x/100)*100;
		string[3]=(char)(int(x/10)+48);
		x-=int(x/10)*10;
		string[4]=(char)(x+48);
		string[5]=0;
		return(string);
	}
return(0);
}

void int2str(int x,char *buffer)
{
	int i=-1;

	if(x<0){buffer[++i]='-';x*=-1;}

	if(x<10)
	{
		buffer[++i]=(char)(x+48);
		buffer[++i]=0;
	}else
	if(x<100)
	{
		buffer[++i]=(char)(int(x/10)+48);
		x-=int(x/10)*10;
		buffer[++i]=(char)(x+48);
		buffer[++i]=0;
	}else
	if(x<1000)
	{
		buffer[++i]=(char)(int(x/100)+48);
		x-=int(x/100)*100;
		buffer[++i]=(char)(int(x/10)+48);
		x-=int(x/10)*10;
		buffer[++i]=(char)(x+48);
		buffer[++i]=0;
	}else
	if(x<10000)
	{
		buffer[++i]=(char)(int(x/1000)+48);
		x-=int(x/1000)*1000;
		buffer[++i]=(char)(int(x/100)+48);
		x-=int(x/100)*100;
		buffer[++i]=(char)(int(x/10)+48);
		x-=int(x/10)*10;
		buffer[++i]=(char)(x+48);
		buffer[++i]=0;
	}else
	if(x<100000)
	{
		buffer[0]=(char)(int(x/10000)+48);
		x-=int(x/10000)*10000;
		buffer[1]=(char)(int(x/1000)+48);
		x-=int(x/1000)*1000;
		buffer[2]=(char)(int(x/100)+48);
		x-=int(x/100)*100;
		buffer[3]=(char)(int(x/10)+48);
		x-=int(x/10)*10;
		buffer[4]=(char)(x+48);
		buffer[5]=0;
	}
}

float GetAngleDiff(float a1,float a2)
{	
	if(a1>=360)a1-=360;
	else if(a1<0)a1+=360;

	if(a2>=360)a2-=360;
	else if(a2<0)a2+=360;

	if(a1>a2)
	{
		a1-=a2;
		if(a1>=180)
		{
			return(360-a1);
		}
		else
		{
			return(a1);
		}
	}
	else if(a1<a2)
	{
		a2-=a1;
		if(a2>=180)
		{
			return(360-a2);
		}
		else
		{
			return(a2);
		}
	}
	return(0);
}

int str2int(char *string)
{
	int i=0,d=1,sign=1;
	int result=0;

	int count=strlen(string);
	if(string[0]=='-')
	{
		sign=-1;
		++string;
		--count;
	}

	for(i=0;i<count-1;++i)d*=10;
	for(i=0;i<count;++i)
	{
		result+=((int)string[i]-48)*d;
		d/=10;
	}
	return(result*sign);
}

double str2double(char* string)
{
	char str1[64],str2[64];
	int i1=0,i2=0,i3=0;
	double d=1;
	double result;
	int sign=1;
	if(string[i1]=='-'){sign=-1;++i1;}
	do
	{
		str1[i3]=string[i1];
		++i3;
		++i1;
	}while(string[i1]!='.');
	str1[i3]='\0';
	++i1;
	while(string[i1]!='\0')
	{
		str2[i2++]=string[i1++];
	}
	str2[i2]='\0';

	i1=str2int(str1);
	i2=str2int(str2);

	for(unsigned int i=0;i<strlen(str2);++i)d*=10;

	result=(double)sign*((double)i1+(double)i2/d);

	return(result);
}

// Gibt den Farbcode für ein RGB-Tripel zurück
unsigned short ColorCode(int r,int g,int b)//565 16bit
{
  r = ( r > 255 ) ? 255 : ( r < 0 ) ? 0 : r;
  g = ( g > 255 ) ? 255 : ( g < 0 ) ? 0 : g;
  b = ( b > 255 ) ? 255 : ( b < 0 ) ? 0 : b;

  return (unsigned short) (((r>>3)<<10/*11*/)|
                             ((g>>3/*2*/)<<5)|
                              (b>>3));
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
/*
BOOL AdditiveBlt16(LPDIRECTDRAWSURFACE3 destsurface,LPDIRECTDRAWSURFACE3 srcsurface,RECT *destrect,RECT *srcrect)
{

	
	
	DDSURFACEDESC destddsd,srcddsd;
	HRESULT hresult;
	unsigned short *dest,*src,cn;
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
////////////

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
*/
BOOL DrawAdditiveRect(LPDIRECTDRAWSURFACE3 lpDDS,RECT rect,int rn,int gn,int bn)
{
	unsigned short *screen;
	int i,i2,i3;
	unsigned short c,cn;
	unsigned short back;
	static BOOL firstrun=TRUE;
	static unsigned short remappalette[ 65536 ];
	int pitch;
	
	DDSURFACEDESC ddsd;
	HRESULT hresult;

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


	ddsd.dwSize=sizeof(ddsd);
	ddsd.lpSurface=NULL;
	hresult=lpDDS->Lock(NULL,&ddsd,DDLOCK_WAIT,NULL);
	if(hresult!=DD_OK)
	{
		return FALSE;
	}
		
	pitch=ddsd.lPitch;




	screen=(unsigned short *)ddsd.lpSurface;
	c=ColorCode(rn,gn,bn)&bitmask;
	for(i3=0;i3<rect.bottom-rect.top;++i3)
	{
	i2=(rect.top+i3)*pitch/2+rect.left;
	for(i=0;i<rect.right-rect.left;++i)
	{
		back=screen[i2+i];
		cn=c;
		cn+=back&bitmask;
//		cn=c+back&bitmask;
		screen[i2+i]=remappalette[(cn)>>1];
	}
	}
	hresult=lpDDS->Unlock(NULL);

	return TRUE;
}

BOOL FileOpenDlg(HWND hWnd,char *buffer,int size)
{
	OPENFILENAME ofn;

//	char *szFile= new char[size];
	char szFileTitle[]="Datei öffnen";

	memset(buffer,0,size);
	/* use the OpenFile dialog to get the filename */
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = NULL;
	ofn.lpstrFile = buffer;
	ofn.nMaxFile = size;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nMaxFileTitle = sizeof(szFileTitle);
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	/* use CommDlg to get our filename */
	if (GetOpenFileName(&ofn))
	{
		return TRUE;
	}
	else
	{
		memset(buffer,0,size);
		return FALSE;
	}
}

BOOL FileExist(char *filename)
{
	HANDLE h;
	h=CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(h!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(h);
		return TRUE;
	}
	else return FALSE;
}

BOOL FileExistCurDir(char *filename)
{
	char path[256];

	GetCurrentDirectory(256,path);
	if(path[strlen(path)-1]!='\\')
		strcat(path,"\\");
	strcat(path,filename);

	return FileExist(path);

}


BOOL code(char *string,unsigned char key)
{
	int size;
	int i2;
	
	size=strlen(string);
	for(i2=0;i2<size;++i2)
	{
		string[i2]^=key;
	}

	return(TRUE);
}

char *maketextstring(char *filename)
{
	HANDLE hfile;
	int size;
	unsigned long i;
	char *string;

	hfile=CreateFile(filename,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(!hfile)return(NULL);

	size=GetFileSize(hfile,NULL);
	string=new char[size+1];
	ReadFile(hfile,(void*)string,size,&i,NULL);
	string[size-1]='\0';
	return(string);
}

HBITMAP LoadBMP(char *szFile)
{
	return (HBITMAP)LoadImage(NULL,szFile, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
}

BOOL PointInRect(POINT p,RECT rect)
{
	if(p.x>rect.left && p.x<rect.right && p.y>rect.top && p.y<rect.bottom)return(TRUE);
	return(FALSE);
}

/*
LPDIRECTDRAWSURFACE3 DDLoadBitmap3(LPDIRECTDRAW dd,LPSTR file)
{
	HANDLE dib;
	BITMAPINFOHEADER bih;
	DDSURFACEDESC ddsd;
	LPDIRECTDRAWSURFACE3 lpdds3;
	HDC hdc;
	
	dib=OpenDIB(file);
	if(!dib)return NULL;

	DibInfo(dib,&bih);
    
	//
    // create a DirectDrawSurface for this bitmap
    //
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth = bih.biWidth;
    ddsd.dwHeight = bih.biHeight;

    if (dd->CreateSurface(&ddsd, (LPDIRECTDRAWSURFACE*)&lpdds3, NULL) != DD_OK)
	return NULL;

	lpdds3->GetDC(&hdc);
	DibBlt(hdc,0,0,bih.biWidth,bih.biHeight,dib,0,0,SRCCOPY);
	lpdds3->ReleaseDC(hdc);
	return lpdds3;
}
*/
/*
BOOL DeleteBitmap(HBITMAP hbm)
{
	return DeleteObject(hbm);
}
*/
BOOL DDAlphaBlend(LPDIRECTDRAWSURFACE3 lpDDS1,LPDIRECTDRAWSURFACE3 lpDDS2,LPRECT rect1,LPRECT rect2)
{
	HDC hdc1;
	HDC hdc2;
	BLENDFUNCTION blendfunction;
     
	while(lpDDS1->GetDC(&hdc1)==DDERR_WASSTILLDRAWING);
	while(lpDDS2->GetDC(&hdc2)==DDERR_WASSTILLDRAWING);

	if(!(hdc1&&hdc2))return FALSE;

	blendfunction.AlphaFormat=0;
	blendfunction.BlendFlags=0;
	blendfunction.BlendOp=AC_SRC_OVER;
	blendfunction.SourceConstantAlpha=128;

	AlphaBlend(hdc1,rect1->left,rect1->top,rect1->right-rect1->left,rect1->bottom-rect1->top,hdc2,rect2->left,rect2->top,rect2->right-rect2->left,rect2->bottom-rect2->top,blendfunction);
	//AlphaBlend(hdc1,0,0,300,300,hdc2,0,0,300,300,blendfunction);

	lpDDS1->ReleaseDC(hdc1);
	lpDDS2->ReleaseDC(hdc2);

	return TRUE;
}

BOOL SaveDC2File(HDC hdc,char *file)
{
	HBITMAP hbm;
	HDC hdcCompatible;
	BITMAP bm;
	HANDLE hdib;
	
	hdcCompatible = CreateCompatibleDC(hdc);
	
	hbm = CreateCompatibleBitmap(hdc, 
                     GetDeviceCaps(hdc, HORZRES), 
                     GetDeviceCaps(hdc, VERTRES));
	
	if(!hbm)return FALSE;
	if(!hdcCompatible)
	{
		DeleteObject(hbm);
		return FALSE;
	}
	
	GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap
 
	SelectObject(hdcCompatible, hbm); 

	if(!BitBlt(hdcCompatible, 
               0,0, 
               bm.bmWidth, bm.bmHeight, 
               hdc, 
               0,0, 
               SRCCOPY))
	{
		DeleteObject(hbm);
		return FALSE;
	}
	
	hdib=DibFromBitmap(hbm,0,0,NULL);
	
	DeleteObject(hbm);

	if(!hdib)return FALSE;
	
	return WriteDIB(file,hdib);
}

/*
** this assumes that R, G, and B are passed as floats in the range [0,1]
*/
DWORD MakeSurfaceRGB( LPDIRECTDRAWSURFACE lpDDS, float r, float g, float b )
{
   unsigned long dw = 0;
   COLORREF cref = RGB( r * 255, g * 255, b * 255 );
   COLORREF tmpCref;
   DDSURFACEDESC ddsd;
   HDC hdc = NULL;

   /*
   ** Get a DC from the surface
   */
   if ( lpDDS->GetDC( &hdc ) != DD_OK )
      // something bad happened
      return 0;

   /*
   ** save pixel in surface then store a pixel into the surface
   */
   tmpCref = GetPixel( hdc, 0, 0 );
   SetPixel( hdc, 0, 0, cref );
   lpDDS->ReleaseDC( hdc );

   memset( &ddsd, 0, sizeof( ddsd ) );
   ddsd.dwSize = sizeof( ddsd );

   /*
   ** lock the back buffer so that we can read back the value
   ** we just wrote with SetPixel()
   */
   if ( lpDDS->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL ) != DD_OK )
   {
      // something bad happened
      // should probably restore the color we wrote out
      // earlier, but I'm too lazy to write that code
      return 0;
   }

   /*
   ** read back the color
   */
   dw = * ( DWORD * ) ddsd.lpSurface;

   /*
   ** mask off high bits if the bit count is not 32
   */
   if ( ddsd.ddpfPixelFormat.dwRGBBitCount != 32 ) 
      dw &= ( ( 1 << ddsd.ddpfPixelFormat.dwRGBBitCount ) - 1 );


   /*
   ** unlock the back buffer
   */
   lpDDS->Unlock( NULL );

   /*
   ** restore the pixel we overwrote
   */
   if ( lpDDS->GetDC( &hdc ) == DD_OK )
   {
      SetPixel( hdc, 0, 0, tmpCref );
      lpDDS->ReleaseDC( hdc );
   }

   return dw;
}

BOOL CreateRotatedSurfaces360(LPDIRECTDRAW lpDD,LPDIRECTDRAWSURFACE source,LPDIRECTDRAWSURFACE *dest,int totalframes)
{
	int i;
	float degs;
	float step=360/(float)totalframes;
	RECT srcrect,destclip;
	DDSURFACEDESC ddsd;
	int width,height;
	int x,y;
	HRESULT hr;

	memset(&ddsd,0,sizeof(DDSURFACEDESC));
	ddsd.dwSize=sizeof(DDSURFACEDESC);
	source->GetSurfaceDesc(&ddsd);
	width=(int)ddsd.dwWidth;
	height=(int)ddsd.dwHeight;

	srcrect.left=0;
	srcrect.right=width;
	srcrect.top=0;
	srcrect.bottom=height;
	destclip=srcrect;
	x=width/2;
	y=height/2;

	memset(&ddsd,0,sizeof(DDSURFACEDESC));
	ddsd.dwSize=sizeof(DDSURFACEDESC);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth = width;
    ddsd.dwHeight = height;

	for(i=0;i<totalframes-1;++i)
	{
		hr=lpDD->CreateSurface(&ddsd,&dest[i],NULL);
		if(hr!=DD_OK)
		{
			return FALSE;
		}
		degs=step*(float)(i+1);
		DrawRotatedZoomed(source,dest[i],srcrect,destclip,x,y,degs,1.0f,1.0f,false);
	}

	return TRUE;
}
