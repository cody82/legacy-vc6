#include <include.h>

//BOOL                    bActive;        // is application active?

LPDIRECTSOUNDBUFFER lpDirectSoundBuffer;

//function prototypes
BOOL initFail( HWND hwnd );
void updateFrame( void );
void ProcessKeyboard();
void ReStart(int&,int&);
int random(int,int);
BOOL loaddeathmessages();

//main sprites
Sprite2 *sprite1=new Sprite2;
Sprite2 *sprite2=new Sprite2;

Engine2 mainengine;

Text3 framerate;
Text3 strenght1display;
int strenght1;
int currentplayer=1;

short int landscape[800];

//RECT        rcRect;
const BOOL		window=GetPrivateProfileIntCurrentDir("config.ini","bunker","window",0);;
//energybar testbar;

long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
    switch( message )
    {
    case WM_ACTIVATEAPP:
//		bActive = wParam;
		break;
    case WM_CREATE:
		break;
    case WM_SETCURSOR:
		SetCursor(NULL);
		return TRUE;
    case WM_TIMER:
		break;
    case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		case 107:
			strenght1+=10;
			break;
		case 109:
			strenght1-=10;
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

/*
 * WinMain - initialization, message loop
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow)
{
	MSG         msg;
	char tmpstr[64];
	int i;

	mainengine.Initialize(hInstance,nCmdShow,800,600,32,
		1,
		2,
		WindowProc);
	
	GetPrivateProfileStringCurrentDir("config.ini","bunker","backgroundsound",tmpstr,64);
	if(stricmp(tmpstr,"NULL")!=0 && mainengine.soundsys.lpDS)
	{
		lpDirectSoundBuffer=DSLoadSoundBuffer(mainengine.soundsys.lpDS,tmpstr);
		lpDirectSoundBuffer->Play(0,0,DSBPLAY_LOOPING );
	}

	GetPrivateProfileStringCurrentDir("config.ini","bunker","backgroundimage",tmpstr,64);
	if(strcmp(tmpstr,"NULL")!=0)mainengine.SetBackGround(tmpstr);

	mainengine.LoadPrototypes("prototypes.ini");
	if(lpDirectSoundBuffer)lpDirectSoundBuffer->Play(0,0,DSBPLAY_LOOPING );

	mainengine.DuplicateSprite(sprite1,mainengine.prototypes[0]);
	mainengine.DuplicateSprite(sprite2,mainengine.prototypes[0]);

	mainengine.AddSpriteEx(sprite1);
	mainengine.AddSpriteEx(sprite2);

	for(i=0;i<800;++i)
	{
		if(i>0)
			landscape[i]=(int)(100*sin((double)i/100)+100);//landscape[i-1]+(random(0,6)-3);
		else landscape[i]=200;
	}

	sprite1->position.x=100;
	sprite1->position.y=600-landscape[(int)sprite1->position.x+sprite1->size.x/2]-sprite1->size.y/2-sprite1->collisionrange;

	sprite1->gravdep=FALSE;
	sprite2->gravdep=FALSE;

	sprite2->position.x=700;
	sprite2->position.y=600-landscape[(int)sprite2->position.x+sprite2->size.x/2]-sprite2->size.y/2-sprite2->collisionrange;

	mainengine.AddItem(&strenght1display);
	strenght1display.position.y=200;
	strenght1display.intptr=&strenght1;

	mainengine.gravity=10;
	mainengine.showinfo=TRUE;

	mainengine.preflipproc=updateFrame;
	return mainengine.Start();
} /* WinMain */

void updateFrame( void )
{
    //static DWORD		lastTickCount=0;
    //const static DWORD	delay = (int)(((double)1/(double)GetPrivateProfileIntCurrentDir("config.ini","bunker","framerate",0))*1000);
	static int			i=0,i2,i3,i4=0;
	//static int			framecount=0;
	//static int			lastframerate=0;
	DDBLTFX ddbltfx;
	RECT destrect;

		
//		sprintf(strenght1display.text,"%d",strenght1);

		ddbltfx.dwSize=sizeof(ddbltfx);
		ddbltfx.dwFillColor=RGB(0,80,140);
		destrect.bottom=600;

		for(i=0;i<MAXSPRITES;++i)
		{
			if(mainengine.sprites[i] &&mainengine.sprites[i]->enabled&& mainengine.sprites[i]->position.y+mainengine.sprites[i]->size.y/2+mainengine.sprites[i]->collisionrange>600-landscape[(int)mainengine.sprites[i]->position.x+mainengine.sprites[i]->size.x/2])
			{
				i2=mainengine.sprites[i]->position.x+mainengine.sprites[i]->size.x/2;
				for(i3=-20;i3<20;++i3)
					if(i2+i3>=0&&i2+i3<800)landscape[i2+i3]+=5*sin(0.5*3.14+(i3+20)*(2*3.14/40))-5;
				
				for(i3=0;i3<60;++i3)
					if(landscape[i2+i3-30]<i4)
						if(i2+i3-30<800 && i2+i3-30>=0)landscape[i2+i3-30]+=(i4-landscape[i2+i3-30])/2;
					else if(landscape[i2+i3-30]>i4)
						if(i2+i3-30<800 && i2+i3-30>=0)landscape[i2+i3-30]-=(landscape[i2+i3-30]-i4)/2;

				mainengine.sprites[i]->Disable();
			}
		}
		for(i=0;i<800;++i)
		{
			destrect.left=i;
			destrect.right=i+1;
			destrect.top=600-landscape[i];
				mainengine.lpDDSBackBuffer->Blt(&destrect,NULL,NULL,DDBLT_COLORFILL,&ddbltfx);
		}

		ProcessKeyboard();

		//++framecount;
} /* updateFrame */

void ProcessKeyboard()
{
	static int timesincelastshot=0;
	Sprite2 *ns;

	if(GetKeyState(VK_LEFT)<0)
	{
		if(currentplayer==1)sprite1->currentturnspeed=-100;
		else if(currentplayer==2)sprite2->currentturnspeed=-100;
	}
	else if(GetKeyState(VK_RIGHT)<0)
	{
		if(currentplayer==1)sprite1->currentturnspeed=100;
		else if(currentplayer==2)sprite2->currentturnspeed=100;
	}
	else 
	{
		if(currentplayer==1)sprite1->currentturnspeed=0;
		else if(currentplayer==2)sprite2->currentturnspeed=0;
	}
	
	if(sprite1->angle>90 && sprite1->angle<270)
	{
		if(sprite1->angle>180)sprite1->angle=270;
		if(sprite1->angle<180)sprite1->angle=90;
	}
	if(sprite2->angle>90 && sprite2->angle<270)
	{
		if(sprite2->angle>180)sprite2->angle=270;
		if(sprite2->angle<180)sprite2->angle=90;
	}

	if(GetKeyState(VK_NUMPAD0)<0)
	{
		
		if(currentplayer==1)
		{
			if(timesincelastshot>50&&sprite1->tfiredelay<=0&&sprite1->enabled)
			{
				sprite1->weapon->launchspeed=strenght1;
				sprite1->Fire(1);
				timesincelastshot=0;
				++currentplayer;
				if(currentplayer>2)currentplayer=1;
			}
		}
		else if(currentplayer==2)
		{
			if(timesincelastshot>50&&sprite2->tfiredelay<=0&&sprite2->enabled)
			{
				sprite2->weapon->launchspeed=strenght1;
				sprite2->Fire(1);
				timesincelastshot=0;
				++currentplayer;
				if(currentplayer>2)currentplayer=1;
			}
		}
	}
	++timesincelastshot;
}; /* ProcessKeyboard */