/****************************************************************************
Recdlg.c

Error message routines and dialog boxes.

Development Team: Greg Landon,

Written by Microsoft Product Support Services, Windows Developer Support.
Copyright (c) 1994 Microsoft Corporation.  All rights reserved.
****************************************************************************/

#include "rec.h"
#include "recdlg.h"	
#include "recrec.h"
#include "recplay.h"
#include "recpaint.h"
#include <mmreg.h>
#include <string.h>

#define ICONSIZE	32

BOOL CALLBACK About( HWND hDlg, UINT message, WPARAM wparam, LPARAM lparam );
void PaintIcon( DRAWITEMSTRUCT FAR *lp, int buttonid );
LPWAVEFORMATEX AllocTmpFormat( void );
void FreeTmpFormat( void );

HGLOBAL htmpfmt;


/*
 Call the ACM dialog compression enumeration functions which allows the user to
 select a compression based on the current wave format.
*/
int GetWaveFormat( HWND hwnd )
{
	ACMFORMATCHOOSE acmopt;
	MMRESULT err;
	LPWAVEFORMATEX ptmpfmt;

	// store the format temporarily...
	if( (ptmpfmt = AllocTmpFormat()) == NULL )
		return ierrormsg( hwnd, "Error allocating temporary format buffer.", -1 );
		
	memcpy( ptmpfmt, pwavefmtex, (size_t)maxFmtSize );
		
	// setup ACM choose fields and display the dialog...
	memset( &acmopt, 0, sizeof(acmopt) );  // zero out
	acmopt.cbStruct  = sizeof(acmopt);
	acmopt.fdwStyle  = ACMFORMATCHOOSE_STYLEF_INITTOWFXSTRUCT;
	acmopt.hwndOwner = hwnd;
	acmopt.pwfx      = pwavefmtex;
	acmopt.cbwfx     = maxFmtSize;
	acmopt.pszTitle  = "Select Compression";
	acmopt.fdwEnum   = ACM_FORMATENUMF_INPUT;
	err = acmFormatChoose( &acmopt );
	
	// if the same format was selected we don't want to reset dwTotalwavesize below,
	// so act like a cancel...
	if( !memcmp( pwavefmtex, ptmpfmt, sizeof(WAVEFORMATEX) ) ) err = ACMERR_CANCELED;
	if( err )
	{
		memcpy( pwavefmtex, ptmpfmt, (size_t)maxFmtSize );
		FreeTmpFormat();
		if( err == ACMERR_CANCELED ) return 0;
		return ierrormsg( hwnd, "Error in FormatChoose function", -2 );
	}
    
	// store the format description...
	strcpy( szFormatDesc, acmopt.szFormat );
	
	// get the format tag details, we don't need to call acmGetFormatDetails since
	// that information was supplied by the choose function...
	GetFormatTagDetails( acmopt.pwfx->wFormatTag );
	
	FreeTmpFormat();

	// now set the play button to a grayed state cause we don't want
	// to try to play the recorded data with a different format...	
	UpdateLength( hwnd, dwTotalwavesize = 0, NULL );
	SetButtonState( hwnd );
	
	return 0;
}											

/*
 Allocate a temporary buffer sufficient to contain a max size WAVEFORMATEX structure.
*/
LPWAVEFORMATEX AllocTmpFormat( void )
{
	LPWAVEFORMATEX ptmpfmt;
	
	// allocate temporary WAVEFMTEX structure...
	if( !(htmpfmt = GlobalAlloc( GMEM_MOVEABLE, (UINT)maxFmtSize )) ) return NULL;
	if( !(ptmpfmt = (LPWAVEFORMATEX)GlobalLock( htmpfmt )) )
	{
		GlobalFree( htmpfmt );
		return NULL;
	}
		
	return ptmpfmt;
}

void FreeTmpFormat( void )
{
	GlobalUnlock( htmpfmt );
	GlobalFree( htmpfmt );
}

/*
 Get the format tag details and store the string description.
*/
int GetFormatTagDetails( WORD wFormatTag )
{
	ACMFORMATTAGDETAILS acmtagdetails;
	
	// zero out...
	memset( &acmtagdetails, 0, sizeof(acmtagdetails) );
	
	acmtagdetails.cbStruct = sizeof(acmtagdetails);	
	acmtagdetails.dwFormatTag = (DWORD)wFormatTag;
	
	if( acmFormatTagDetails( NULL, &acmtagdetails, ACM_FORMATTAGDETAILSF_FORMATTAG ) )
		return ierrormsg( NULL, "Warning, FormatTagDetails function failed", -1 );

	// store the format tag details description string...	
	strcpy( szFormatTag, acmtagdetails.szFormatTag );

	return 0;
}

/*
 Get the format details and store the string description.
*/
int GetFormatDetails( LPWAVEFORMATEX pfmtin )
{
	ACMFORMATDETAILS acmfmtdetails;

	// zero out struct...	
	memset( &acmfmtdetails, 0, sizeof(acmfmtdetails) );

	acmfmtdetails.cbStruct    = sizeof(acmfmtdetails);
	acmfmtdetails.pwfx        = pfmtin;
	acmfmtdetails.dwFormatTag = (DWORD)pfmtin->wFormatTag;
	acmfmtdetails.cbwfx       = sizeof(WAVEFORMATEX) + pfmtin->cbSize;

	if( acmFormatDetails( NULL, &acmfmtdetails, ACM_FORMATDETAILSF_FORMAT ) )
		return ierrormsg( NULL, "Warning, FormatDetails function failed", -1 );
	
	// store the format details description string...	
	strcpy( szFormatDesc, acmfmtdetails.szFormat );
	
	return 0;
}

/* Display an error message. */
void errormsg( HWND hwnd, LPSTR msg )
{
	MessageBox( hwnd, msg, "Error", MB_OK );
}

/* Display an error message and return an error value. */
int ierrormsg( HWND hwnd, LPSTR msg, int retval )
{
	MessageBox( hwnd, msg, "Error", MB_OK );
	return retval;
}

/*
 Show the about box.
*/
void AboutBox( HWND hwnd )
{
	//FARPROC lpProcAbout;

	//lpProcAbout = MakeProcInstance( (FARPROC)About, hinst );
	DialogBox( hinst, "AboutBox", hwnd, About );
	//FreeProcInstance( lpProcAbout );
}

/*
 Process the about box messages, use the program icon for the ok button.
*///BOOL (CALLBACK* DLGPROC)(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK About( HWND hDlg, UINT message, WPARAM wparam, LPARAM lparam )
{
	static HWND hIconbut;
	DRAWITEMSTRUCT FAR *pdrawitem;
	DWORD dwUnits;
	
	switch ( message )
	{
		case WM_INITDIALOG:
			dwUnits = GetDialogBaseUnits();
			hIconbut = CreateWindow( "button", NULL,
						WS_CHILD | BS_OWNERDRAW | WS_VISIBLE | WS_BORDER,
						72*LOWORD(dwUnits)/4-16, 38*HIWORD(dwUnits)/8,
						ICONSIZE+1, ICONSIZE+1, hDlg, (HMENU)ID_ICONBUTTON, NULL, NULL );
			return TRUE;
			
		case WM_SYSCOMMAND:
			if( wparam == SC_CLOSE ) wparam = ID_ICONBUTTON;
			
		case WM_COMMAND:
			if( wparam == ID_ICONBUTTON )
			{
				EndDialog(hDlg, TRUE);
				return TRUE;
			}
			break;
			
		case WM_DESTROY:
			DestroyWindow( hIconbut );
			return TRUE;
			
		case WM_DRAWITEM:		// draw icon for ok button...
			pdrawitem = (DRAWITEMSTRUCT FAR*)lparam;
			if( pdrawitem->CtlType == ODT_BUTTON )	PaintIcon( pdrawitem, wparam );
			return TRUE;
	}
	return( FALSE );
}

/*
 Paint the owner draw icon if the user pushes or releases it.
*/
void PaintIcon( DRAWITEMSTRUCT FAR *lp, int buttonid )
{
	HICON	icon;
	LPSTR resstr;

	if( lp->itemState & ODS_SELECTED ) resstr = "RecIcon1";	// button pushed
	else resstr = "RecIcon";	// button released

	if( (icon = LoadIcon(hinst,resstr)) ) DrawIcon( lp->hDC, 0, 0, icon );
}

