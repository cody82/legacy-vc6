/****************************************************************************
Recfile.c

This module contains file i/o routines.

Development Team: Greg Landon,

Written by Microsoft Product Support Services, Windows Developer Support.
Copyright (c) 1994 Microsoft Corporation.  All rights reserved.
****************************************************************************/

#include "rec.h"
#include "recfile.h"
#include "recrec.h"
#include "recpaint.h"
#include "recdlg.h"
#include <stdio.h>
#include <math.h>

int CopyWaveToTempFile( HMMIO mmfp, DWORD datasize );
void InitFilename( HWND hwnd, LPOPENFILENAME fname );
int GetSaveFilename( HWND hwnd, int savemode );
int CopyDataToWaveFile( HMMIO mmfp );
int QueryUserSave( HWND hwnd, LPCSTR name );
int FileExist( LPCSTR name );
int WFerror( HWND hwnd, HMMIO mmfp, char *msg, int retval );

OPENFILENAME savename;
char szFileName[MAXFILENAME]="Untitled.wav";
char szFileTitle[MAXFILENAME];
char szBaseWindowTitle[] = "Dual-buffer recorder";
char szWindowTitle[80];
char szFilterSpec[128]="Wave Files (*.wav)\0*.wav\0All Files (*.*)\0*.*\0";
HCURSOR hcur;

MMCKINFO mminfopar;
MMCKINFO mminfosub;

BOOL savedfile=OFF;		// set when a save is done on the current file


int ReadWaveFile( HWND hwnd )
{
	OPENFILENAME openfile;
	HMMIO mmfp;
	static int initopenname=0;
   
	// initialize the save file struct...
	if( !initopenname ) InitFilename( hwnd, &openfile );
	initopenname = 1;
	
   // get a filename using a common dialog...
   InitFilename( hwnd, &openfile );
	if( !GetOpenFileName ((LPOPENFILENAME)&openfile) ) return FALSE;
	
	// open the wave file for reading...
	mmfp = mmioOpen( openfile.lpstrFile, NULL, MMIO_READ|MMIO_ALLOCBUF );
	if( !mmfp ) return ierrormsg( hwnd, "Open for read failed." , -1 );
	
	hcur = SetCursor( LoadCursor( NULL, IDC_WAIT ) );

	// search for wave type and format chunks...
	mminfopar.fccType = mmioFOURCC('W','A','V','E');
	if( mmioDescend( mmfp, (LPMMCKINFO)&mminfopar, NULL, MMIO_FINDRIFF ) )
		return WFerror( hwnd, mmfp, "Wave format not found in file.", -2 );

	mminfosub.ckid = mmioFOURCC('f','m','t',' ');
	if( mmioDescend( mmfp, &mminfosub, &mminfopar, MMIO_FINDCHUNK ) )
		return WFerror( hwnd, mmfp, "Format chunk not found.", -3 );

	// read the wave format if the size checks out...
	if( mminfosub.cksize > maxFmtSize ) return ierrormsg( hwnd, "Format size in file doesn't match ACM's.", -4 );

	// read the wave format...
	if( (DWORD)mmioRead( mmfp, (HPSTR)pwavefmtex, mminfosub.cksize ) != mminfosub.cksize )
		return WFerror( hwnd, mmfp, "Error reading format chunk.", -4 );
		
	// get the total wave data size (mminfo.cksize)...
	mmioAscend( mmfp, &mminfosub, 0 );
	mminfosub.ckid = mmioFOURCC('d','a','t','a');
	if( mmioDescend( mmfp, &mminfosub, &mminfopar, MMIO_FINDCHUNK ) )
		return WFerror( hwnd, mmfp, "Data chunk not found.", -5 );

	// if there's no data get out...
	if( mminfosub.cksize == 0L )
		return WFerror( hwnd, mmfp, "The data chunk contains no data.", -6 );

	// now read the wave data and copy it to the temorary file...
	if( CopyWaveToTempFile( mmfp, mminfosub.cksize ) )
	{
		mminfosub.cksize = 0;
		errormsg( hwnd, "Error reading the wave data." );
	}

	// all done...
	mmioClose( mmfp, 0 );
	
	SetCursor( hcur );
	
	dwTotalwavesize = mminfosub.cksize;

	// this data wasn't recorded, it was read in...
	recordeddata = OFF;

	// store the format and tag decription strings...
	GetFormatTagDetails( pwavefmtex->wFormatTag );
	GetFormatDetails( pwavefmtex );
		
	// update display...
	InvalidateRect( hwnd, &specrect, TRUE );
	UpdateLength( hwnd, dwTotalwavesize, dwTotalwavesize );
	SetButtonState( hwnd );

	return 0;	
}

/*
 Copy the wave data from the RIFF file to the temorary file.
*/
int CopyWaveToTempFile( HMMIO mmfp, DWORD datasize )
{
	LPSTR pbuf = (LPSTR)pwavemem[0]; // use one of the wave buffers for copying
	DWORD ntotal=0;
	UINT nbytes,readsize=WAVE_BUFSIZE;
	int err=0;

	// create the temporary file based on the current temp name...	  
	if( CreateTmpFile() ) return -1;

	// enter read/copy loop...
	while( ntotal < datasize )
	{
		if( ntotal+readsize > datasize ) readsize = (UINT)(datasize - ntotal);
		
		if( (nbytes = (UINT)mmioRead( mmfp, pbuf, readsize )) == 0 )
		{
			err = -2;
			break;
		}
		
		if( _lwrite( htmpfile, pbuf, nbytes ) != nbytes ) err = -3;
		
		ntotal += nbytes;
	}
	
	// close read file...   
	CloseTmpFile();

	return err;
}	

/*
 Initialize non-variant fields of OPENFILENAME struct.
*/
void InitFilename( HWND hwnd, LPOPENFILENAME fname )
{
	// just do this once...	
	fname->lStructSize      = sizeof(OPENFILENAME);
	fname->hwndOwner        = hwnd;
	fname->lpstrFilter      = szFilterSpec;
	fname->nMaxCustFilter   = 0;
	fname->nFilterIndex     = 1;
	fname->lpstrFile        = szFileName;
	fname->nMaxFile         = MAXFILENAME;
	fname->lpstrInitialDir  = NULL;
	fname->lpstrFileTitle   = szFileTitle;
	fname->nMaxFileTitle    = MAXFILENAME;
	fname->lpstrTitle      = NULL;
	fname->lpstrDefExt      = "WAV";
	fname->Flags            = 0;
	fname->lpstrCustomFilter= NULL;
}

/*     
 If unsaved wave data has been recorded, ask the user to save it.
*/
void CheckSaveFile( HWND hwnd )
{
	if( recordeddata && dwTotalwavesize && !savedfile )
		if( MessageBox( hwnd, "Wave data has not been saved.  Do you want to save it?", "Just checking", MB_YESNO ) == IDYES )
			SaveWaveFile( hwnd,  SAVEAS );
}

/*
 Save the wave file by creating the required RIFF chunks and copy
 the wave data from the temporary wave file to the RIFF .wave file.
*/
int SaveWaveFile( HWND hwnd, int savemode )
{
	HMMIO mmfp;
	DWORD dwTotalSamples;
	double fTotalSamples;
	static int initsavename=0;

	// if no data recorded, don't bother...
	if( !dwTotalwavesize ) return ierrormsg( hwnd, "No recorded wave data to save.", 0 );

	// initialize the save file struct...
	if( !initsavename ) InitFilename( hwnd, &savename );
	initsavename = 1;

	// get a filename/use the current one, or cancel...
	if( GetSaveFilename( hwnd, savemode ) == FALSE ) return 0;

	// open the wave file for write...
	mmfp = mmioOpen( savename.lpstrFile, NULL, MMIO_CREATE | MMIO_WRITE | MMIO_ALLOCBUF );
	if( !mmfp ) return ierrormsg( hwnd, "Error opening file for write.", -1 );

	hcur = SetCursor( LoadCursor( NULL, IDC_WAIT ) );

	// create wave RIFF chunk...
	mminfopar.fccType = mmioFOURCC('W','A','V','E');
	mminfopar.cksize = 0L;		 	// let the function determine the size
	if( mmioCreateChunk( mmfp, &mminfopar, MMIO_CREATERIFF ) )
		return WFerror( hwnd, mmfp, "Error creating RIFF wave chunk.", -2 );

	// create the format chunk and write the wave format...
	mminfosub.ckid = mmioFOURCC('f','m','t',' ');
	mminfosub.cksize = maxFmtSize;
	if( mmioCreateChunk( mmfp, &mminfosub, 0 ) )
		return WFerror( hwnd, mmfp, "Error creating RIFF format chunk.", -3 );

	if( mmioWrite( mmfp, (HPSTR)pwavefmtex, (LONG)maxFmtSize ) != (LONG)maxFmtSize )
		return WFerror( hwnd, mmfp, "Error writing RIFF format data.", -3 );

	// back out of format chunk...
	mmioAscend( mmfp, &mminfosub, 0 );
	
	// write the fact chunk (required for all non-PCM .wav files...
	// this chunk just contains the total length in samples...
	mminfosub.ckid = mmioFOURCC('f','a','c','t');
	mminfosub.cksize = sizeof(DWORD);
	if( mmioCreateChunk( mmfp, &mminfosub, 0 ) )
		return WFerror( hwnd, mmfp, "Error creating RIFF 'fact' chunk.", -4 );

	fTotalSamples = (double)dwTotalwavesize / (double)pwavefmtex->nAvgBytesPerSec * (double)pwavefmtex->nSamplesPerSec;
	dwTotalSamples = (DWORD)fTotalSamples;
	if( mmioWrite( mmfp, (HPSTR)&dwTotalSamples, (LONG)sizeof(DWORD) ) != (LONG)sizeof(DWORD) )
		return WFerror( hwnd, mmfp, "Error writing RIFF 'fact' data.", -4 );

	// back out of fact chunk...
	mmioAscend( mmfp, &mminfosub, 0 );

	// now create and write the wave data chunk...
	mminfosub.ckid = mmioFOURCC('d','a','t','a');
	mminfosub.cksize = 0L;	 	// let the function determine the size
	if( mmioCreateChunk( mmfp, &mminfosub, 0 ) )
		return WFerror( hwnd, mmfp, "Error creating RIFF data chunk.", -5 );

	// copy the data from the temp file to the wave file...		
	if( CopyDataToWaveFile( mmfp ) ) 
		return WFerror( hwnd, mmfp, "Error writing wave data.", -5 );

	// back out and cause the size of the data buffer to be written...
	mmioAscend( mmfp, &mminfosub, 0 );

	// ascend out of the RIFF chunk...
	mmioAscend( mmfp, &mminfopar, 0 );

	// done...
	mmioClose( mmfp, 0 );

	SetCursor( hcur );
	
	// indicate filename on window title...
	sprintf( szWindowTitle, "%s - %s", szBaseWindowTitle, szFileTitle );
	SetWindowText( hwnd, szWindowTitle );

	// set this so we don't ask for a filename when the user does "SAVE"...
	savedfile = TRUE;

	return 0;
}

/*
 Copy the wave data in the temporary file to the wave file.
*/
int CopyDataToWaveFile( HMMIO mmfp )
{
	LPSTR pbuf = (LPSTR)pwavemem[0]; // use one of the wave buffers for copying
	HFILE ht;
	LONG nbytes;

	// open the temp file for reading...	  
	if( (ht = _lopen( tmpfilename, OF_READ ) ) == HFILE_ERROR ) return -1;

	// copy to RIFF/wave file...
	while( (nbytes = (LONG)_lread( ht, pbuf, WAVE_BUFSIZE )) )
		mmioWrite( mmfp, pbuf, nbytes );
	
	// close read file...   
	_lclose( ht );
	
	return 0;
}	

/*
 Get a save filename according to the save mode.  The savemode is either
 "save" or "saveas" where "saveas" queries for a new name and "save" checks
 to see if the file exists and checks with the user before saving.
 Returns:
	TRUE	- We have a filename, use that for the save.
	FALSE	- Cancel the save operation.
*/
int GetSaveFilename( HWND hwnd, int savemode )
{
	int response;

redosave:

	// if we're saving the file as the current name...
	if( savemode == SAVE )
	{
		if( ! *szFileName )	 // ...huh? go get a filename first...
			savemode = SAVEAS;
		else if( !savedfile ) // see if there's a file by that name already...
		{
			if( FileExist( szFileName ) )	// there is. overwrite?
			{
				response = QueryUserSave( hwnd, szFileName );
				if( response == IDNO )
					savemode = SAVEAS;			// no, get a filename
				else if( response == IDYES )
					return TRUE;					// yes, overwrite it
				else
					return FALSE;					// cancel the save operation
			}
		}
	}

	if( savemode == SAVEAS )		// get a save filename...
	{
		InitFilename( hwnd, &savename ); // setup for common dlg
		if( !GetSaveFileName( (LPOPENFILENAME)&savename ) ) return FALSE;

		// now go check to see if the files exists...
		savemode = SAVE;
		goto redosave;
	}

	return TRUE;
}

/*
 return TRUE if a file exists.
*/
int FileExist( LPCSTR name )
{
	OFSTRUCT info;
	return ( (OpenFile( name, &info, OF_EXIST ) == -1) ? 0 : 1 );
}

/*
 Notify user that the file exists and ask to overwrite, return 1 for yes, 0 for no.
*/
int QueryUserSave( HWND hwnd, LPCSTR name )
{
	char buf[128];
	wsprintf( buf, "File %s exists, overwite?", name );
	return MessageBox( hwnd, buf, "Save File", MB_YESNOCANCEL );
}

/*
 Close the wave file, display an error message, and return an error value.
*/
int WFerror( HWND hwnd, HMMIO mmfp, char *msg, int retval )
{
	mmioClose( mmfp, 0 );
	SetCursor( hcur );
	return ierrormsg(hwnd,msg,retval);
}
