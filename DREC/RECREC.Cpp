/****************************************************************************
Recrec.c

This module contains routines related to recording the wave.

Development Team: Greg Landon,

Written by Microsoft Product Support Services, Windows Developer Support.
Copyright (c) 1994 Microsoft Corporation.  All rights reserved.
****************************************************************************/

#include "rec.h"
#include "recrec.h"
#include "recdlg.h"
#include "recpaint.h"
#include <stdlib.h>
#include <io.h>
#include <dos.h>
#include <string.h>
#include <windows.h>

void CloseWaveDevPlay( HWND hwnd );
void DeleteTmpFile( void );
int AllocWaveFormatEx( HWND hwnd );
void FreeWaveFormatEx( void );
int AllocWaveHeader( HWND hwnd );
void FreeWaveHeader( void );
int AllocPCMBuffers( HWND hwnd );
void FreePCMBuffers( void );

LPWAVEHDR pwavehdr[2];	// pointers to wave header information
HANDLE hwavehdr[2];		// wave header memory handle
HLOCAL hwavefmtex;		// WAVEFMTEX memory handle
HWAVEIN hwavein;		// device ID for recording input
char tmpfilename[145];	// temporary wave filename
HFILE htmpfile;			// handle to temporary wave file
extern int bufindex;			// controls which wave buffer we're using
UINT WaveBufSize;		// size of buffer as a multiple of the nBlockAlign header field
DWORD dwDiskFreespace; // amount of available disk speace in bytes
BOOL recordeddata=OFF; // for knowing when we've recorded data
DWORD dwBytedatasize=0;	// accumulative size of recorded data
DWORD dwTotalwavesize;	// total number of samples recorded


/*
 Zero out the wave headers and initialize the data pointers and buffer lengths.
*/
void InitWaveHeaders( void )
{
	// make the wave buffer size a multiple of the block align...
	WaveBufSize=(WAVE_BUFSIZE - WAVE_BUFSIZE % pwavefmtex->nBlockAlign );

	// zero out the wave headers...	
	memset( pwavehdr[0], 0, sizeof(WAVEHDR) );
	memset( pwavehdr[1], 0, sizeof(WAVEHDR) );
	
	// now init the data pointers and buffer lengths...
	pwavehdr[0]->dwBufferLength = pwavehdr[1]->dwBufferLength = WaveBufSize;
	pwavehdr[0]->lpData = pwavemem[0];
	pwavehdr[1]->lpData = pwavemem[1];
}

/*
 Allocate format and wave headers, data buffers, and temporary filename.
*/
int InitWaveRecorder( HWND hwnd )
{
	// allocate memory for wave format structure...
	if( AllocWaveFormatEx( hwnd ) ) return -1;
	
	// find a device compatible with the available wave characteristics...
	if( waveInGetNumDevs() < 1 )
		return ierrormsg( hwnd, "No wave audio recording devices found.", -1 );

	// allocate the wave header memory...
	if( AllocWaveHeader( hwnd ) ) return -3;
	
	// allocate the wave data buffer memory...
	if( AllocPCMBuffers( hwnd ) ) return -4;

	// generate a temporary filename for writing to...
	GetTempFileName( ".", "wr", 0, tmpfilename );
	
	return 0;
}

/*
 Free the memory associated with the wave buffers.
*/
void DestroyWaveRecorder( HWND hwnd )
{
	FreeWaveFormatEx();
	FreePCMBuffers();
	FreeWaveHeader();
	DeleteTmpFile();
}

/*
 Prepare headers, add buffer, adjust display, and start recording.
*/
int StartWaveRecord( HWND hwnd )
{
	dwTotalwavesize = dwBytedatasize = bufindex = 0;
	
	// open the device for recording...
	if( waveInOpen( &hwavein, (UINT)WAVE_MAPPER, (LPWAVEFORMATEX)pwavefmtex, (DWORD)hwnd, NULL, CALLBACK_WINDOW|WAVE_ALLOWSYNC ) )
		return ierrormsg(hwnd,"Could not open the input device for recording.",-1);
	
	// tell CloseWaveDeviceRecord() that the device is open...	
	bDeviceOpen = TRUE;

	// prepare the headers...
	
	InitWaveHeaders();
	
	if( waveInPrepareHeader( hwavein, pwavehdr[0], sizeof(WAVEHDR) ) ||
		 waveInPrepareHeader( hwavein, pwavehdr[1], sizeof(WAVEHDR) ) )
	{
		CloseWaveDeviceRecord( hwnd );
		return ierrormsg(hwnd,"Error preparing header for recording.",-2);
	}

	// add the first buffer...
	if( AddNextBuffer( hwnd ) ) return -3;

	// create the file we'll be writing to...
	if( CreateTmpFile() )
	{
		CloseWaveDeviceRecord( hwnd );
		return -4;
	}

	// start recording to first buffer...
	if( waveInStart( hwavein ) )
	{
		CloseWaveDeviceRecord( hwnd );
		return ierrormsg(hwnd,"Error starting wave record.",-5);
	}

	ModeFlag = RECORD;
	
	// set the timer for updating the display...
	SetTimer( hwnd, ID_TIMERREC, 250, NULL );
	UpdateLength( hwnd, 0, dwDiskFreespace );

	// queue the next buffer...
	if( AddNextBuffer( hwnd ) ) return -6;
	
	// turn the record light on...
	InvalidateRect( hwnd, &reclightrect, FALSE );
	
	// adjust control button states...
	SetWindowText( recbut, "Stop" );
	SetButtonState( hwnd );

	return 0;
}

/*
 Add the buffer to the wave input queue and toggle buffer index. This
 routine is called from the main window proc.
*/
int AddNextBuffer( HWND hwnd )
{
	// queue the buffer for input...
	if( waveInAddBuffer( hwavein, pwavehdr[bufindex], sizeof(WAVEHDR) ) )
	{
		StopWaveRecord( hwnd );
		return ierrormsg(hwnd,"Error adding buffer.",-1);
	}

	// toggle for next buffer...
	bufindex = 1 - bufindex;
	
	return 0;
}

/*
 Get the total bytes recorded and update the display with the information.
*/
void UpdateRecordDisplay( HWND hwnd )
{
	MMTIME mmtime;
	
	mmtime.wType = TIME_BYTES;
	waveInGetPosition( hwavein, &mmtime, sizeof(mmtime) );
	
	UpdateLength( hwnd, mmtime.u.cb, dwDiskFreespace );
}

/*
 Stop the recording.
*/
void StopWaveRecord( HWND hwnd )
{
	// set flag before stopping since it's used in the MM_WIM_DATA message
	// in our main window proc to control whether we add another buffer
	// or to close the device.
	ModeFlag = OFF;
	
	// stop recording and return queued buffers...
	if( waveInReset( hwavein ) ) errormsg( hwnd, "Error in waveInReset" );

	// stop the timer...	
	KillTimer( hwnd, ID_TIMERREC );
}

/*
 Close the temp file and wave recording device.
*/
void CloseWaveDeviceRecord( HWND hwnd )
{
	// if the device is already closed, just return...
	if( bDeviceOpen == FALSE ) return;
    
    // unprepare the headers...
	if( waveInUnprepareHeader( hwavein, pwavehdr[0], sizeof(WAVEHDR)) )
		errormsg( hwnd, "Error in waveInUnprepareHeader (1)" );
	
	if( waveInUnprepareHeader( hwavein, pwavehdr[1], sizeof(WAVEHDR)) )
		errormsg( hwnd, "Error in waveInUnprepareHeader (2)" );
	
	// save the total size recorded and update the display...
	dwTotalwavesize = dwBytedatasize;
	UpdateLength( hwnd, dwTotalwavesize, dwDiskFreespace );
	
	// tell the file save functions that we've got unsaved data...
	recordeddata = TRUE;

	// close the temporary file...
	CloseTmpFile();

	// close the wave input device...
	if( waveInClose( hwavein ) ) errormsg( hwnd, "Error closing input device." );
	
	// tell this function we are now closed...
	bDeviceOpen = FALSE;
	
	// update display...
	InvalidateRect( hwnd, &specrect, TRUE );
	InvalidateRect( hwnd, &reclightrect, FALSE );
	SetWindowText( recbut, "Record" );
	SetButtonState( hwnd );
}

/*
 Write the recorded data to the temporary file.
*/
int WriteWaveBuffer( UINT size )
{
	if( size == 0 ) return 0;
	
	if( _lwrite( htmpfile, pwavemem[bufindex], size ) != size )
		return ierrormsg( NULL, "Error writing data to temporary file.", -1 );
	
	// running total bytes recorded...
	dwBytedatasize += size;
	
	return 0;
}

/*
 Create the temporary file for writing the wave data to.
*/
int CreateTmpFile( void )
{
	struct _diskfree_t info;
	int idrive=0;
	
	if( (htmpfile = _lcreat( tmpfilename, 0 )) == HFILE_ERROR )
		return ierrormsg( NULL, "Error creating temporary file.", -1 );
		
	// get available space on the temp disk...
	//if( tmpfilename[1] == ':' ) idrive = toupper(tmpfilename[0]) - 'A' + 1;
	//_dos_getdiskfree( idrive, &info );
	ULARGE_INTEGER i;
	GetDiskFreeSpaceEx(tmpfilename,NULL,NULL,&i);
	dwDiskFreespace = i.LowPart;//(DWORD)info.avail_clusters * (DWORD)info.sectors_per_cluster * (DWORD)info.bytes_per_sector;
	
	return 0;
}

/*
 Close the temporary file contaning the newly recorded data.
*/
void CloseTmpFile( void )
{
	if( _lclose( htmpfile ) ) errormsg( NULL, "Error closing temporary file.");
}

/*
 Delete the temporary wave file.
*/
void DeleteTmpFile( void )
{
	if( tmpfilename[0] ) remove( tmpfilename );
}

/*
 Allocate and lock WAVEFORMATEX structure based on maximum format size
 according to the ACM.
*/
int AllocWaveFormatEx( HWND hwnd )
{
	// get the largest format size required from installed ACMs...
	// maxFmtSize is the sum of sizeof(WAVEFORMATEX) + pwavefmtex->cbSize
	if( acmMetrics( NULL, ACM_METRIC_MAX_SIZE_FORMAT, &maxFmtSize ) )
		return ierrormsg( hwnd, "Error getting the max compression format size.", -1 );
		
	// allocate the WAVEFMTEX structure...
	if( (hwavefmtex = GlobalAlloc( GMEM_MOVEABLE, (UINT)maxFmtSize )) == NULL )
		return ierrormsg( hwnd, "Error allocating local memory for WaveFormatEx structure.", -2 );
		
	if( (pwavefmtex = (LPWAVEFORMATEX)GlobalLock( hwavefmtex )) == NULL )
		return ierrormsg( hwnd, "Error locking WaveFormatEx memory.", -3 );

	// initialize the format to standard PCM...
	memset( pwavefmtex, 0, (size_t)maxFmtSize );
	pwavefmtex->wFormatTag = WAVE_FORMAT_PCM;
	pwavefmtex->nChannels = 1;
	pwavefmtex->nSamplesPerSec = 11025;
	pwavefmtex->nAvgBytesPerSec = 11025;
	pwavefmtex->nBlockAlign = 1;
	pwavefmtex->wBitsPerSample = 8;
	pwavefmtex->cbSize = 0;
	
	// store the format and tag decription strings...
	GetFormatTagDetails( pwavefmtex->wFormatTag );
	GetFormatDetails( pwavefmtex );
		
	return 0;
}
 
/*
 Free the WAVEFORMATEX buffer.
*/
void FreeWaveFormatEx( void )
{
	GlobalUnlock( hwavefmtex );
	GlobalFree( hwavefmtex );
	pwavefmtex = NULL;
}

/*
 Allocate and lock header memory
*/
int AllocWaveHeader( HWND hwnd )
{
	int i;
	for(i=0; i<2; i++ )
	{
		hwavehdr[i] = GlobalAlloc( GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT, (DWORD)sizeof(WAVEHDR) );
		if( !hwavehdr[i] ) return ierrormsg(hwnd,"Error allocating wave header memory.",-1);

		pwavehdr[i] = (LPWAVEHDR) GlobalLock( hwavehdr[i] );
		if( !pwavehdr[i] ) return ierrormsg(hwnd,"Couldn't lock header memory for recording.",-2);
	}
	return 0;
}

/*
 Free the wave header memory.
*/
void FreeWaveHeader( void )
{
	int i;
	for( i=0; i<2; i++ )
	{
		GlobalUnlock( hwavehdr[i] );
		GlobalFree( hwavehdr[i] );
	}
}

/*
 Allocate and lock wave memory
*/
int AllocPCMBuffers( HWND hwnd )
{
	int i;
	for( i=0; i<2; i++ )
	{
		if( (hwavemem[i] = GlobalAlloc( GMEM_MOVEABLE | GMEM_SHARE, WAVE_BUFSIZE )) == NULL )
		{
			errormsg( hwnd, "Error allocating wave buffer memory." );
			return -1;
		}
		pwavehdr[i]->lpData = pwavemem[i] = (LPSTR)GlobalLock( hwavemem[i] );
	}
	return 0;
}

/*
 Free the wave memory.
*/
void FreePCMBuffers( void )
{
	int i;
	for(i=0; i<2; i++ )
	{
		GlobalUnlock( hwavemem[i] );
		GlobalFree( hwavemem[i] );
	}
}
