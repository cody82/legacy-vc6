/****************************************************************************
Rec.c

Main application message handler module.

Development Team: Greg Landon,

Written by Microsoft Product Support Services, Windows Developer Support.
Copyright (c) 1994 Microsoft Corporation.  All rights reserved.
****************************************************************************/

#include "rec.h"
#include "recinit.h"
#include "recfile.h"
#include "recdlg.h"
#include "recpaint.h"
#include "recrec.h"
#include "recplay.h"
#include "recrec.h"
#include <stdio.h>
#include <string.h>

HINSTANCE hinst;			// the instance of this app.
WAVEINCAPS wavecaps;	// the capabilities of the wave audio device
TEXTMETRIC FAR tm;		// text metrics
DWORD maxFmtSize;			// largest format size required for compression
LPWAVEFORMATEX pwavefmtex;
HWND recbut,playbut,fmtbut;	// play and record buttons
HGLOBAL hwavemem[2];	// handle to wave buffer objects
LPSTR pwavemem[2];		// pointers to wave buffers
BOOL bDeviceOpen=OFF;	// device open status
int ModeFlag=OFF;		// recording/playing mode


LONG CALLBACK MainWndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int retval=0;
	LPWAVEHDR pwavehdrtmp;

	switch( message )
	{
			// initialize variables
		case WM_CREATE:
			clrect.left = clrect.top = 0;
			if( InitWaveRecorder( hwnd ) )
			{
				DestroyWaveRecorder( hwnd );
				PostQuitMessage( 0 );
				break;
			}
			CreateColors();
			break;

			// recalculate size and position of objects...
		case WM_SIZE:
			CalcSizes( lparam );
			MoveDisplayObjects();
			InvalidateRect( hwnd, NULL, TRUE );
			break;

			// update the display...
		case WM_PAINT:
			hdc = BeginPaint( hwnd, &ps );
			DrawRecordLight( hdc );
			DrawSpecs( hdc );
			DrawLength( hdc );
			EndPaint( hwnd, &ps );
			break;
			
		case WM_TIMER:
			if( wparam == ID_TIMERREC )
				UpdateRecordDisplay( hwnd );
			else if( wparam == ID_TIMERPLAY )
				UpdatePlayDisplay( hwnd );
			break;

			// done recording buffer...
		case MM_WIM_DATA:
			// write it out
			pwavehdrtmp = (LPWAVEHDR)lparam;
			if( WriteWaveBuffer( (UINT)pwavehdrtmp->dwBytesRecorded ) )
				StopWaveRecord( hwnd );
			
			if( ModeFlag )
				AddNextBuffer( hwnd );			// queue it again...
			else
				CloseWaveDeviceRecord( hwnd );	// stop recording...
			break;
			
			// done playing queued wave buffer...
		case MM_WOM_DONE:
			if( MoreBuffers )
				QueueNextBuffer( hwnd );
			else
				StopWavePlay( hwnd, FALSE );
			break;

			// closing wave output device...			
		case MM_WOM_CLOSE:
			bDeviceOpen = FALSE;
			break;
			
			// give user last chance to save the wave data...
		case WM_CLOSE:
			CheckSaveFile( hwnd );
			return DefWindowProc(hwnd, message, wparam, lparam);

			// bye...			
		case WM_DESTROY:
			if( ModeFlag == RECORD ) StopWaveRecord( hwnd );
			else if( ModeFlag == PLAY ) StopWavePlay( hwnd, TRUE );
			DestroyWaveRecorder( hwnd );
			DeleteColors();
			PostQuitMessage( 0 );
			break;

		case WM_COMMAND:
		{
			switch( wparam )
			{
				// change the wave format...
				case ID_FMTBUT:
					GetWaveFormat( hwnd );
					InvalidateRect( hwnd, &specrect, TRUE );
					break;

				// user pressed the record/stop button...
				case ID_RECBUT:
					if( ModeFlag )	// stop recording...
						StopWaveRecord( hwnd );
					else			// start recording...
						StartWaveRecord( hwnd );
					break;
					
				// user pressed the play/stop button...
				case ID_PLAYBUT:
					if( ModeFlag )	// stop playing...
						StopWavePlay( hwnd, TRUE );
					else			// start playing...
						StartWavePlay( hwnd );
					break;
					
				// user selected open a wave file...
				case IDM_OPEN:
					ReadWaveFile( hwnd );
					break;

				// user selected save option from menu...
				case IDM_SAVE:
					SaveWaveFile( hwnd, SAVE );
					break;

				// user selected saveas option from menu...
				case IDM_SAVEAS:
					SaveWaveFile( hwnd, SAVEAS );
					break;

				// user selected exit option from menu, close this...
				case IDM_EXIT:
					PostMessage( hwnd, WM_CLOSE, NULL, NULL );
					break;

				//  display the about dialog box...
				case IDM_ABOUT:
					AboutBox( hwnd );
					break;

				default:
					return DefWindowProc(hwnd, message, wparam, lparam);
			}
			break;
		}

		default:
			return DefWindowProc(hwnd, message, wparam, lparam);
    }
    return retval;
}
