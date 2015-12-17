#include <include.h>

Engine2 mainengine;

Text4 maintext;
LPDIRECTSOUNDBUFFER lpDSBSound;
AviItem avi[4];
BitmapItem bmp[4];

void updateFrame();

long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
	mainengine.OnWM(message,wParam,lParam);
    switch( message )
    {
    case WM_ACTIVATEAPP:
		break;
    case WM_CREATE:
		break;
    case WM_TIMER:
		break;
    case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		default:
			//exit(wParam);
			break;
		}
	case WM_KEYUP:
		break;
    case WM_PAINT:
		break;
    case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
} /* WindowProc */

int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow)
{
	char tmpstr[64];

	//BOOL Initialize(HINSTANCE hInstance,int sw,
	//	int sh,int bpp,BOOL fs,int backbuffers,WNDPROC wndproc,BOOL use2ndDisplaydevice=FALSE);

	mainengine.Initialize(hInstance,800,600,16,
		GetPrivateProfileIntCurrentDir("config.ini","credits","fullscreen",0),//fullscreen
		1,
		WindowProc);

	if(GetPrivateProfileStringCurrentDir("config.ini","credits","sound",tmpstr,64))
		if(stricmp(tmpstr,"NULL")!=0 &&mainengine.soundsys.lpDS)
		{
			lpDSBSound=DSLoadSoundBuffer(mainengine.soundsys.lpDS,tmpstr);
			if(lpDSBSound)lpDSBSound->Play(0,0,DSBPLAY_LOOPING );
		}
	
	if(GetPrivateProfileStringCurrentDir("config.ini","credits","background",tmpstr,64))
		if(stricmp(tmpstr,"NULL")!=0)
		{
			mainengine.SetBackGround(tmpstr);
		}

	if(GetPrivateProfileStringCurrentDir("config.ini","credits","text",tmpstr,64))
		if(stricmp(tmpstr,"NULL")!=0)
		{
			maintext.strptr=maketextstring(tmpstr);
			code(maintext.strptr,GetPrivateProfileIntCurrentDir("config.ini","credits","maxbubbles",0));
		}

	maintext.SetTxtColor(255,255,0);
	maintext.position.x=0;
	maintext.position.y=(float)mainengine.screenheight;
	maintext.size.x=mainengine.screenwidth;
	maintext.size.y=1700;
	maintext.speed.y=-30;
	maintext.enabled=TRUE;

	mainengine.AddItem(&bmp[0]);
	bmp[0].Load("bitmaps\\logo1.bmp",TRUE);
	bmp[0].attach=&maintext;
	bmp[0].attachpos.x=maintext.size.x/2-bmp[0].size.x/2;
	bmp[0].attachpos.y=-bmp[0].size.y;

	//AVI´s
	if(GetPrivateProfileIntCurrentDir("config.ini","credits","avi",1))
	{
	avi[0].Open("videos\\cnv.avi");
	avi[0].Play(TRUE);
	mainengine.AddItem(&avi[0]);
	avi[0].attach=&maintext;
	avi[0].attachpos.y=200;

	avi[1].Open("videos\\falcon2.avi");
	avi[1].Play(TRUE);
	mainengine.AddItem(&avi[1]);
	avi[1].attach=&maintext;
	avi[1].attachpos.x=maintext.size.x-avi[1].size.x;
	avi[1].attachpos.y=600;
	
	avi[2].Open("videos\\br.avi");
	avi[2].Play(TRUE);
	mainengine.AddItem(&avi[2]);
	avi[2].attach=&maintext;
	avi[2].attachpos.y=1000;
	
	avi[3].Open("videos\\ncc.avi");
	avi[3].Play(TRUE);
	mainengine.AddItem(&avi[3]);
	avi[3].attach=&maintext;
	avi[3].attachpos.y=1400;
	avi[3].attachpos.x=maintext.size.x-avi[1].size.x;
	}
	//End AVI´s	

	mainengine.AddItem(&maintext);

	mainengine.showinfo=GetPrivateProfileIntCurrentDir("config.ini","credits","showinfo",1);
		
	mainengine.updateproc=updateFrame;
	mainengine.ScrollSpeed.y=-30;



	return(mainengine.Start());
} /* WinMain */


void updateFrame()
{
	if(maintext.position.y+maintext.size.y<0)
	{
		//maintext.position.x=0;
		maintext.position.y=(float)mainengine.screenheight+200;
	}

} /* updateFrame */

