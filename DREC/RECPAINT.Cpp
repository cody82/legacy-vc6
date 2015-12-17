/****************************************************************************
Recpaint.c

This module contains routines to handle text/painting/sizing.

Development Team: Greg Landon,

Written by Microsoft Product Support Services, Windows Developer Support.
Copyright (c) 1994 Microsoft Corporation.  All rights reserved.
****************************************************************************/

#include "rec.h"
#include "recrec.h"
#include "recpaint.h"
#include <stdio.h>
#include <string.h>

// text drawing variables
#define NTEXTLINES 2
LPSTR txtspecbase[NTEXTLINES]={"Bytes","Seconds"};
int txtspc;
int txtspeclen;

extern TEXTMETRIC FAR tm;		// text metrics
RECT FAR clrect;		// the client rectangle
RECT FAR specrect;		// the box for the specs
RECT FAR lengthdisp;	// display region for length text numbers
RECT FAR lengthpos;	// display region for length posiiton
int bordersizex,bordersizey;	// the window margins
DWORD dwBytePosition;		// used for drawing the current byte position
DWORD dwBytePositiontotal; // used for computing the current byte position
char FAR szFormatDesc[ACMFORMATDETAILS_FORMAT_CHARS];	// format description
char FAR szFormatTag[ACMFORMATTAGDETAILS_FORMATTAG_CHARS];	// format tag description

// size/location for play and record buttons...
possize_t recpos, playpos, fmtpos;

// record light...
RECT reclightrect;

// pens of various colors...
HPEN whtpen,blkpen,ltpen,dkpen;
HBRUSH whtbrush,blkbrush,ltbrush,dkbrush;

// the record/play light...
HBITMAP bmreclightoff,bmreclighton,bmreclightplay;


/*
 Create the color objects to be used in this app.
*/
void CreateColors( void )
{
	whtbrush = (HBRUSH)GetStockObject( WHITE_BRUSH );
	blkbrush = (HBRUSH)GetStockObject( BLACK_BRUSH );
	whtpen = (HPEN)GetStockObject( WHITE_PEN );
	blkpen = (HPEN)GetStockObject( BLACK_PEN );
	ltpen = (HPEN)CreatePen( PS_SOLID, 0, RGB(196,196,196) );
	dkpen = (HPEN)CreatePen( PS_SOLID, 0, RGB(128,128,128) );
	bmreclightoff = LoadBitmap( hinst, MAKEINTRESOURCE(Lightoff) );
	bmreclighton = LoadBitmap( hinst, MAKEINTRESOURCE(Lightrec) );
	bmreclightplay = LoadBitmap( hinst, MAKEINTRESOURCE(Lightplay) );
}

/*
 Delete the objects.
*/
void DeleteColors( void )
{
	DeleteObject( ltpen );
	DeleteObject( dkpen );
	DeleteObject( bmreclightoff );
	DeleteObject( bmreclighton );
	DeleteObject( bmreclightplay );
}

/*
	Create record/play buttons.
*/
void CreateControls( HANDLE hinstance, HWND hwnd )
{
	recbut = CreateWindow( "button", "Record", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
						recpos.x, recpos.y, recpos.xsize, recpos.ysize, hwnd, (HMENU)ID_RECBUT, hinst, NULL );
	playbut = CreateWindow( "button", "Play", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
						playpos.x, playpos.y, playpos.xsize, playpos.ysize, hwnd, (HMENU)ID_PLAYBUT, hinst, NULL );
	fmtbut = CreateWindow( "button", "Audio Format", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
						fmtpos.x, fmtpos.y, fmtpos.xsize, fmtpos.ysize, hwnd, (HMENU)ID_FMTBUT, hinst, NULL );
}

/*
 Enable/disable button states according to what functions we can perform.
*/
void SetButtonState( HWND hwnd )
{
	EnableWindow( recbut, (ModeFlag != PLAY) );
	EnableWindow( playbut, (dwTotalwavesize != 0) && (ModeFlag != RECORD) );
	EnableWindow( fmtbut, !ModeFlag );
	EnableMenuItem( GetSubMenu(GetMenu(hwnd),0), 0, MF_BYPOSITION | ((ModeFlag)?MF_DISABLED:MF_ENABLED) );
}

/*
 Calculate the button/control positions based on the window size.
*/
void CalcSizes( LPARAM lparam )
{
	int tottxtspc;

	// client rectangle size...
	clrect.right = LOWORD(lparam);
	clrect.bottom = HIWORD(lparam);

	tottxtspc = txtspc*(NTEXTLINES+1) + tm.tmHeight*NTEXTLINES;
	bordersizex = ( clrect.right - txtspeclen*2 ) / 3;
	bordersizey = clrect.bottom / 16;

	// specification rectangle...
	specrect.left   = clrect.left + bordersizex;
	specrect.right  = clrect.right - bordersizex;
	specrect.top	= clrect.top + bordersizey * 2 + tm.tmHeight*2;
	specrect.bottom = specrect.top + tm.tmHeight*2 + txtspc*3;

	// length position indicator...	
	lengthpos.left = specrect.left;
	lengthpos.right = specrect.right;
	lengthpos.top = specrect.bottom + tm.tmHeight;
	lengthpos.bottom = lengthpos.top + tm.tmHeight;
	
	// play/record button size/positions...
	recpos.xsize = playpos.xsize = (specrect.right-specrect.left)/2  - LIGHTWID*2 - tm.tmAveCharWidth;
	recpos.ysize = playpos.ysize = tm.tmHeight*2 + txtspc;
	recpos.x = bordersizex + tm.tmAveCharWidth;
	recpos.y = playpos.y = lengthpos.bottom + bordersizey + bordersizey/2;
	playpos.x = specrect.right - playpos.xsize - tm.tmAveCharWidth;
	fmtpos.xsize = ( specrect.right - specrect.left ) + 1;
	fmtpos.ysize = tm.tmHeight + tm.tmHeight / 2;
	fmtpos.x = specrect.left;
	fmtpos.y = specrect.top / 2 - fmtpos.ysize / 2;
	
	// display region for length text numbers...	
	lengthdisp.left   = playpos.x + strlen(txtspecbase[1]) * tm.tmAveCharWidth + txtspc;
	lengthdisp.right  = specrect.right - 1;
	lengthdisp.top    = specrect.top + 1;
	lengthdisp.bottom = specrect.bottom - 1;
	
	// record light position...
	reclightrect.left  = (clrect.right - clrect.left)/2 - LIGHTWID/2;
	reclightrect.right = reclightrect.left + LIGHTWID;
	reclightrect.top   = recpos.y + recpos.ysize/2 - LIGHTHT/2;
	reclightrect.bottom= reclightrect.top + LIGHTHT;
}
                            
/*
 Position the controls.
*/
void MoveDisplayObjects( void )
{
	MoveWindow( recbut, recpos.x, recpos.y, recpos.xsize, recpos.ysize, FALSE );
	MoveWindow( playbut, playpos.x, playpos.y, playpos.xsize, playpos.ysize, FALSE );
	MoveWindow( fmtbut, fmtpos.x, fmtpos.y, fmtpos.xsize, fmtpos.ysize, FALSE );
}

/*
 Draw the spec strings to the display in the proper places.
*/
void DrawSpecs( HDC hdc )
{
	int y,yheight=tm.tmHeight+txtspc;

	// draw the format and tag descriptions...
	SetTextColor( hdc, RGB(0,0,128) );
	SetBkMode( hdc, TRANSPARENT );
	TextOut( hdc, specrect.left+tm.tmAveCharWidth, specrect.top+txtspc, szFormatTag, lstrlen(szFormatTag) );
	TextOut( hdc, specrect.left+tm.tmAveCharWidth, specrect.top+tm.tmHeight+txtspc, szFormatDesc, lstrlen(szFormatDesc) );

	// draw the spec titles...
	SetTextColor( hdc, RGB(0,0,0) );
	y = specrect.top + txtspc;
	TextOut( hdc, playpos.x, y, txtspecbase[0], lstrlen(txtspecbase[0]) );
	TextOut( hdc, playpos.x, y+yheight, txtspecbase[1], lstrlen(txtspecbase[1]) );
	
	// draw the spec box...
	SelectObject( hdc, dkpen );
	line( hdc, specrect.left, specrect.top, specrect.left, specrect.bottom );
	line( hdc, specrect.left, specrect.top, specrect.right, specrect.top );
	SelectObject( hdc, whtpen );
	line( hdc, specrect.left, specrect.bottom, specrect.right, specrect.bottom );
	line( hdc, specrect.right, specrect.top, specrect.right, specrect.bottom );
	
	// draw the length position indicator box..
	line( hdc, lengthpos.left-1, lengthpos.bottom, lengthpos.right, lengthpos.bottom );
	line( hdc, lengthpos.right, lengthpos.top-1, lengthpos.right, lengthpos.bottom );
	SelectObject( hdc, dkpen );
	line( hdc, lengthpos.left-1, lengthpos.top-1, lengthpos.left-1, lengthpos.bottom);
	line( hdc, lengthpos.left-1, lengthpos.top-1, lengthpos.right, lengthpos.top-1 );
}

/*
 Update the display of the sample length.
*/
void UpdateLength( HWND hwnd, DWORD length, DWORD lengthtotal )
{
	HDC hdc;
	
	// store these...
	dwBytePosition = length;
	dwBytePositiontotal = lengthtotal;

	// if we're starting or ending play/record repaint...
	if( dwBytePosition == 0 || dwBytePosition == dwBytePositiontotal )
	{	
		InvalidateRect( hwnd, &lengthdisp, TRUE );
		InvalidateRect( hwnd, &lengthpos, TRUE );
	}
	else	// otherwise just call this directly and reduce the overhead...
	{
		hdc = GetDC( hwnd );
		DrawLength( hdc );
		ReleaseDC( hwnd, hdc );
	}
}

/*
 Draw the limit specs in the proper location on the display.
*/
void DrawLength( HDC hdc )
{
	double tmp;
	int y, yheight= tm.tmHeight + txtspc;
	char limspecs[NTEXTLINES][SPECTEXTLEN];
	static int rightpos=-1;
	                
	sprintf( limspecs[0], "%7ld", dwBytePosition );
	sprintf( limspecs[1], "%5.1lf", (double)dwBytePosition/(double)pwavefmtex->nAvgBytesPerSec );
	
	// draw the limits...
	SetTextAlign( hdc, TA_RIGHT );
	SetTextColor( hdc, RGB(0,0,128) );
	SetBkColor( hdc, RGB(196,196,196) );
	y = specrect.top + txtspc;
	TextOut( hdc, specrect.right-tm.tmAveCharWidth, y, limspecs[0], lstrlen(limspecs[0]) );
	TextOut( hdc, specrect.right-tm.tmAveCharWidth, y+yheight, limspecs[1], lstrlen(limspecs[1]) );
	SetTextAlign( hdc, TA_LEFT );

	// calulate and draw position indicator...
	if( dwBytePosition )
	{
		SelectObject( hdc, ltpen );
		line( hdc, rightpos, lengthpos.top, rightpos, lengthpos.bottom-1 );
		
		tmp = (double)dwBytePosition / (double)dwBytePositiontotal * (double)(lengthpos.right-lengthpos.left-1);
		rightpos = lengthpos.left + (int)tmp;
		
		SelectObject( hdc, whtpen );
		line( hdc, lengthpos.left, lengthpos.top, lengthpos.left, lengthpos.bottom-1 );
		line( hdc, lengthpos.left, lengthpos.top, rightpos, lengthpos.top );
		SelectObject( hdc, dkpen );
		line( hdc, lengthpos.left+1, lengthpos.bottom-1, rightpos, lengthpos.bottom-1 );
		line( hdc, rightpos, lengthpos.top, rightpos, lengthpos.bottom-1 );
	}
}

/*
 Draw a line.
*/
void line( HDC hdc, int x1, int y1, int x2, int y2 )
{
	MoveToEx( hdc, x1, y1, NULL );
	LineTo( hdc, x2, y2 );
}

/*
 Draw the record/play light.
*/
void DrawRecordLight( HDC hdc )
{
	HBITMAP	oldbm;
	HDC		hdcmem;
	HGDIOBJ	bmpid;
	
	if( ModeFlag == RECORD ) bmpid = bmreclighton;
	else if( ModeFlag == PLAY ) bmpid = bmreclightplay;
	else bmpid = bmreclightoff;

	// select bitmap object...
	hdcmem = CreateCompatibleDC( hdc );
	oldbm = (HBITMAP)SelectObject( hdcmem, bmpid );

	// blit it...
	BitBlt( hdc, reclightrect.left, reclightrect.top, LIGHTWID, LIGHTHT, hdcmem, 0, 0, SRCCOPY );

	SelectObject( hdcmem, oldbm );
	DeleteDC( hdcmem );
}



