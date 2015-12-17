#define INC_OLE2
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <commdlg.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <digitalv.h>
#include <vfw.h>
#include "langplay.h"
#include <profiles.h>
#include <int2str.h>

HWND hwndMovie;                 /* window handle of the movie */
char szAppName [] = "IntroPlay";

/* function declarations */
long FAR PASCAL WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void exitintro();

HWND initApp(HINSTANCE hInstance, HINSTANCE hPrevInstance, int nCmdShow)
{
        HWND            hWnd;   /* window handle to return */
        int             iWinHeight;
        WORD    wVer;
		char tmpstr[64];

        /* first let's make sure we are running on 1.1 */
        wVer = HIWORD(VideoForWindowsVersion());
        if (wVer < 0x010a){
                /* oops, we are too old, blow out of here */
                MessageBeep(MB_ICONHAND);
                MessageBox(NULL, "Video for Windows version is too old",
                          "LangPlay Error", MB_OK|MB_ICONSTOP);
                return FALSE;
        }

        if (!hPrevInstance){
                WNDCLASS    wndclass;

                wndclass.style         = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
                wndclass.lpfnWndProc   = WndProc;
                wndclass.cbClsExtra    = 0;
                wndclass.cbWndExtra    = 0;
                wndclass.hInstance     = hInstance;
                wndclass.hIcon         = LoadIcon (hInstance, "AppIcon");
                wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
                wndclass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
                wndclass.lpszMenuName  = szAppName;
                wndclass.lpszClassName = szAppName;

                if (!RegisterClass(&wndclass)){
                        MessageBox(NULL, "RegisterClass failure", szAppName, MB_OK);
                        return NULL;
                }
        }

        iWinHeight = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU) +
                        (GetSystemMetrics(SM_CYFRAME) * 2);

        /* create the main window for the app */
        hWnd = CreateWindow(szAppName, szAppName, //WS_SYSMENU |
                WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, 320, 240,
                NULL, NULL, hInstance, NULL);

        if (hWnd == NULL){
                MessageBox(NULL, "CreateWindow failure", szAppName, MB_OK);
                return NULL;
        }

        /* Show the main window */
        ShowWindow(hWnd, nCmdShow);
        UpdateWindow(hWnd);

        /* create the movie window using MCIWnd that has no file open initially */
        hwndMovie = MCIWndCreate(hWnd, hInstance, MCIWNDF_NOPLAYBAR |WS_CHILD |WS_VISIBLE | MCIWNDF_NOOPEN |
                                MCIWNDF_NOERRORDLG | MCIWNDF_NOTIFYSIZE|MCIWNDF_NOTIFYMODE , NULL);

        if (!hwndMovie){
                /* we didn't get the movie window, destroy the app's window and bail out */
                DestroyWindow(hWnd);
				exitintro();
                return NULL;
        }
            
GetPrivateProfileStringCurrentDir("config.ini","intro","avifile",tmpstr,64);
		if (MCIWndOpen(hwndMovie, tmpstr, 0) == 0){
                        /* we opened the file o.k., now set up to */
                        /* play it.                                */
                        ShowWindow(hwndMovie, SW_SHOW);
                } else {
                        /* generic error for open */
                        MessageBox(hWnd, "Unable to open Movie", NULL,
                              MB_ICONEXCLAMATION|MB_OK);
						exitintro();
                }

MCIWndPlay(hwndMovie);


			return hWnd;
}




/*--------------------------------------------------------------+
| WinMain - main routine.                                       |
|                                                               |
+--------------------------------------------------------------*/
int PASCAL WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                                LPSTR lpszCmdParam, int nCmdShow)
{
        HWND        hWnd;
        MSG         msg;

        if ((hWnd = initApp(hInstance, hPrevInstance,nCmdShow)) == NULL)
                return 0;       /* died initializing, bail out */

        while (GetMessage(&msg, NULL, 0, 0)){
                TranslateMessage(&msg);
                DispatchMessage(&msg);
				//MCIWndPlay(hwndMovie);
       }
        return msg.wParam;
}


/*--------------------------------------------------------------+
| WndProc - window proc for the app                             |
|                                                               |
+--------------------------------------------------------------*/
long FAR PASCAL WndProc (HWND hWnd, UINT message, WPARAM wParam,
                                                LPARAM lParam)
{
        PAINTSTRUCT ps;
		RECT rect;
		POINT size;

        switch (message){
		case WM_KEYDOWN:
			switch(wParam)
			{
			case VK_ESCAPE:
				exitintro();
				break;
			}

                case WM_CREATE:
                        return 0;

                case WM_INITMENUPOPUP:
                        break;

                case WM_COMMAND:
                        return 0;

                case WM_PAINT:
                        BeginPaint(hWnd, &ps);
                        EndPaint(hWnd, &ps);
                        return 0;

                case WM_SIZE:

					break;
                case WM_DESTROY:
					exitintro();
                        return 0;

                case MCIWNDM_NOTIFYSIZE:

					GetWindowRect(hwndMovie,&rect);
					AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW |WS_CLIPCHILDREN,FALSE);
					
					size.x=rect.right-rect.left;
					size.y=rect.bottom-rect.top;
					
					rect.left=GetSystemMetrics(SM_CXSCREEN)/2-size.x/2;
					rect.right=rect.left+size.x;
					rect.top=GetSystemMetrics(SM_CYSCREEN)/2-size.y/2;
					rect.bottom=rect.top+size.y;
					
					SetWindowPos(hWnd,HWND_TOP,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,SWP_DRAWFRAME);

                    break;
				case MCIWNDM_NOTIFYMODE:
					if((LONG)lParam==525)
						exitintro();
					break;

                case WM_ACTIVATE:
                case WM_QUERYNEWPALETTE:
                case WM_PALETTECHANGED:
                        //
                        // Forward palette-related messages through to the MCIWnd,
                        // so it can do the right thing.
                        //
                        if (hwndMovie)
                                return SendMessage(hwndMovie, message, wParam, lParam);
                        break;
        } /* switch */
        return DefWindowProc(hWnd, message, wParam, lParam);
}

void exitintro()
{
	char tmpstr[64];

	MCIWndClose(hwndMovie);  // close an open movie
	MCIWndDestroy(hwndMovie);    // now destroy the MCIWnd window
	PostQuitMessage(0);

	GetPrivateProfileStringCurrentDir("config.ini","intro","startfile",tmpstr,64);
	WinExec(tmpstr,SW_SHOW);

}