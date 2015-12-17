/****************************************************************************
Recplay.c

This module contains routines related to playing the wave.

Development Team: Greg Landon,

Written by Microsoft Product Support Services, Windows Developer Support.
Copyright (c) 1994 Microsoft Corporation.  All rights reserved.
****************************************************************************/

#include "rec.h"
#include "recrec.h"
#include "recplay.h"
#include "recdlg.h"
#include "recpaint.h"

int ReadWaveBuffer( void );
void CloseWaveDevicePlay( HWND hwnd );
int OpenTmpFile( void );

HWAVEOUT hwaveout;
int bufindex;
int MoreBuffers=OFF;


/*
 Prepare headers, add buffer, and start recording.
*/
int StartWavePlay( HWND hwnd )
{
	// if the device is still open, just return...
	if( bDeviceOpen ) return -1;
	
	dwBytedatasize = bufindex = 0;
	
	// open the device for recording...
	if( waveOutOpen( &hwaveout, (UINT)WAVE_MAPPER, pwavefmtex, (DWORD)hwnd, NULL, WAVE_FORMAT_DIRECT|CALLBACK_WINDOW|WAVE_ALLOWSYNC ) )
		return ierrormsg(hwnd,"Error opening wave out device.",-1);
		
	bDeviceOpen = TRUE;
	
	// prepare the headers...
	
	InitWaveHeaders();

	if( waveOutPrepareHeader( hwaveout, pwavehdr[0], sizeof(WAVEHDR) ) ||
		 waveOutPrepareHeader( hwaveout, pwavehdr[1], sizeof(WAVEHDR) ) )
	{
		CloseWaveDevicePlay( hwnd );
		return ierrormsg(hwnd,"Error preparing header for playing.",-2);
	}

	// open the temporary file for reading...	
	if( OpenTmpFile() )
	{
		CloseWaveDevicePlay( hwnd );
		return ierrormsg(hwnd,"Error opening temporary wave file for read.",-3);
	}

	// write the first buffer to start playing,..
	if( QueueNextBuffer( hwnd ) )
	{
		CloseWaveDevicePlay( hwnd );
		return -4;
	}
	
	ModeFlag = MoreBuffers = PLAY;
	
	// set the timer for updating the display...
	SetTimer( hwnd, ID_TIMERPLAY, 250, NULL );
	UpdateLength( hwnd, 0, dwTotalwavesize );

	// turn the play light on...
	InvalidateRect( hwnd, &reclightrect, FALSE );
	
	// adjust control button states...
	SetWindowText( playbut, "Stop" );
	SetButtonState( hwnd );

	// and queue the next buffer up...
	QueueNextBuffer( hwnd );

	return 0;
}

/*
 Write the buffer to the wave device and toggle buffer index.
*/
int QueueNextBuffer( HWND hwnd )
{

	// fill the wave buffer with data from the file...
	if( ReadWaveBuffer() == 0 )
	{
		// reset flags field (remove WHDR_DONE attribute)...
		pwavehdr[bufindex]->dwFlags = (DWORD)WHDR_PREPARED;
		
		// now queue the buffer for output...
		if( waveOutWrite( hwaveout, pwavehdr[bufindex], sizeof(WAVEHDR) ) )
		{
			StopWavePlay( hwnd, TRUE );
			return ierrormsg(hwnd,"Error writing wave buffer.",-1);
		}

		// toggle for next buffer...
		bufindex = 1 - bufindex;
	}
	
	return 0;
}

/*
 Read a wave chunk from the temp file.
*/
int ReadWaveBuffer( void )
{
	// if we haven't encountered the end of the wave yet,
	// read another buffer in...
	if( dwBytedatasize < dwTotalwavesize )
	{
		// read wave chunk from the temporary file...
		pwavehdr[bufindex]->dwBufferLength = _lread( htmpfile, pwavemem[bufindex], WaveBufSize );
		
		// update total number of bytes read so far...
		dwBytedatasize += pwavehdr[bufindex]->dwBufferLength;
	}
	else
	{	// otherwise the last buffer has been queued, just let it finish playing...
		MoreBuffers = OFF;	// handled in MM_WOM_DONE in MainWndProc()
		return 1;
	}
	
	return 0;
}

/*
 Get the total bytes played and update the display with the information.
*/
void UpdatePlayDisplay( HWND hwnd )
{
	MMTIME mmtime;
	
	mmtime.wType = TIME_BYTES;
	waveOutGetPosition( hwaveout, &mmtime, sizeof(mmtime) );
	
	UpdateLength( hwnd, mmtime.u.cb, dwTotalwavesize );
}

/*
 Open the temporary file for reading.
*/
int OpenTmpFile( void )
{
	if( (htmpfile = _lopen( tmpfilename, OF_READ )) ) return 0;
	return 1;
}

/*
 Stop the wave playing.
*/
void StopWavePlay( HWND hwnd, BOOL prematurely )
{
	// if the device isn't open, just return...
	if( bDeviceOpen == FALSE ) return;

	// stop playing...
	waveOutReset( hwaveout );

	// stop the timer...
	KillTimer( hwnd, ID_TIMERPLAY );
	
	// update the length only if we played to the end...
	if( !prematurely ) UpdateLength( hwnd, dwBytedatasize, dwTotalwavesize );

	ModeFlag = MoreBuffers = OFF;
	
	// close the device and unprepare the headers...
	CloseWaveDevicePlay( hwnd );

	// update display...
	InvalidateRect( hwnd, &specrect, TRUE );
	InvalidateRect( hwnd, &reclightrect, FALSE );
	SetWindowText( playbut, "Play" );
	SetButtonState( hwnd );
}

/*
 Close the wave output device.
*/
void CloseWaveDevicePlay( HWND hwnd )
{
	// unprepare the headers...
	if( waveOutUnprepareHeader( hwaveout, pwavehdr[0], sizeof(WAVEHDR) ) ||
		waveOutUnprepareHeader( hwaveout, pwavehdr[1], sizeof(WAVEHDR) ) )
			errormsg( hwnd, "Error unpreparing play header." );

	// close the device...
	if( waveOutClose( hwaveout ) ) errormsg( NULL, "Error closing wave play device." );
	
	bDeviceOpen = FALSE;
	
	// close the temporary file...
	CloseTmpFile();
}
