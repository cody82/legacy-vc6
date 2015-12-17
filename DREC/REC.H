#include <windows.h>
#include <commdlg.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <msacm.h>

#define OFF		0
#define RECORD	1
#define PLAY	2
                
#define WAVE_BUFSIZE 32000		// buffer about 32k

#define MAXFILENAME	256
#define SAVE		0
#define SAVEAS		1

// timer IDs...
#define ID_TIMERREC  1
#define ID_TIMERPLAY 2

// system menu items...
#define IDM_NEW			100
#define IDM_OPEN		110
#define IDM_SAVE		120
#define IDM_SAVEAS		130
#define IDM_EXIT		140
#define IDM_ABOUT		400

// custom buttons ids/bitmaps...
#define ID_RECBUT    800
#define ID_PLAYBUT   801
#define ID_FMTBUT    802
#define ID_POSTIMER  812

// dialog icon button...
#define ID_ICONBUTTON	901

// record light...
#define LIGHTWID    16
#define LIGHTHT		16
#define Lightoff    920
#define Lightrec    921
#define Lightplay   922

typedef struct
{
	int x,y,xsize,ysize;
} possize_t;

extern HINSTANCE hinst;
extern WAVEINCAPS wavecaps;
extern LPWAVEFORMATEX pwavefmtex;
extern DWORD maxFmtSize;
extern HWND hwndglobal;
extern HWND recbut, playbut, fmtbut;
extern BOOL bDeviceOpen;
extern int  ModeFlag;

// wave buffer globals...
extern HGLOBAL hwavemem[2];
extern LPSTR pwavemem[2];


long FAR PASCAL MainWndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
