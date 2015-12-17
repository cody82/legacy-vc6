/****************************************************************************
Recinit.c

Windows initialization routines.

Development Team: Greg Landon,

Written by Microsoft Product Support Services, Windows Developer Support.
Copyright (c) 1994 Microsoft Corporation.  All rights reserved.
****************************************************************************/

#include "rec.h"
#include "recinit.h"
#include "recpaint.h"
#include "recfile.h"

//int PASCAL WinMain( HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
BOOL InitApplication( HINSTANCE hInstance );
BOOL InitInstance( HINSTANCE hInstance, int nCmdShow );
void Windowpos( int *x, int *y, int *xsize, int *ysize );


int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	if( !hPrevInstance )
		if( !InitApplication(hInstance) ) return( FALSE );

	if( !InitInstance(hInstance, nCmdShow) ) return( FALSE );

	while( GetMessage(&msg, NULL, NULL, NULL) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return( msg.wParam );
}

BOOL InitApplication( HINSTANCE hInstance )
{
	WNDCLASS  wc;

	wc.style			= NULL;
	wc.lpfnWndProc		= MainWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon( hInstance, "RecIcon" );
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszMenuName	= "RecMenu";
	wc.lpszClassName	= "RecClass";

	return( RegisterClass(&wc) );
}


/*
 This function is called at initialization time for every instance of 
 this application.  This function performs initialization tasks that 
 cannot be shared by multiple instances.  
*/        
BOOL InitInstance( HINSTANCE hInstance, int nCmdShow )
{
	HWND hwnd;
	int x,y,xsize,ysize;

	hinst = hInstance;

	// set the size and position of the window...
	Windowpos( &x, &y, &xsize, &ysize );

	// Create the main window...
	hwnd = CreateWindow( "RecClass", szBaseWindowTitle,	WS_OVERLAPPEDWINDOW,
				x, y, xsize, ysize,	NULL, NULL, hInstance, NULL );

	if( !hwnd ) return( FALSE );

	// create the record and play buttons...
	CreateControls( hInstance, hwnd );
	
	// initialize the state of the buttons...
	SetButtonState( hwnd );

	ShowWindow( hwnd, nCmdShow );

	UpdateWindow( hwnd );

	return( TRUE );
}

/*
 Set the initial size and position of the window.
*/
void Windowpos( int *x, int *y, int *xsize, int *ysize )
{
	HDC hdc;
	int scrnx,scrny;

	hdc = GetDC( NULL );
	scrnx = GetDeviceCaps( hdc, HORZRES );	// screen width
	scrny = GetDeviceCaps( hdc, VERTRES );	// screen height
	GetTextMetrics( hdc, &tm );
	ReleaseDC( NULL, hdc );

	txtspc = tm.tmHeight / 5;
	txtspeclen = tm.tmAveCharWidth * SPECTEXTLEN;

	*xsize = (int)( (double)txtspeclen * 2.5);
	*ysize = tm.tmHeight * 16;
	*x = (scrnx - *xsize) / 2;
	*y = (scrny - *ysize) / 3;
}
