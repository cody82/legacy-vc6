#ifndef __DD7VIDEOSTREAM_H
#define __DD7VIDEOSTREAM_H

#include <windows.h>
#include <mmstream.h>   
#include <amstream.h>
#include <ddstream.h> 
#include <ddrawex.h>  

//link: amstrmid.lib

class CDD7VideoStream
{
public:
	CDD7VideoStream();
	~CDD7VideoStream();

	BOOL Initialize(LPDIRECTDRAW7 lpDD,LPCTSTR szFilename);
	void Shutdown();

	BOOL Render(LPDIRECTDRAWSURFACE7 lpDDSDest);

	POINT pSize;
	float pos_x;
	float pos_y;

private:
	IMultiMediaStream        *lpMMStream;
	IMediaStream             *lpPrimaryVidStream;    
	IDirectDrawMediaStream   *lpDDStream;
	IDirectDrawStreamSample  *lpSample;
	LPDIRECTDRAWSURFACE7 lpDDS;

};


#endif