#ifndef __MECHWAVEDLG_H
#define __MECHWAVEDLG_H

#include "resource.h"
#include <gamelib.h>
#include "mechanicwave.h"

class CWaveGraph : public CGameUpdater
{
public:
	CWaveGraph();
	virtual ~CWaveGraph();
	
	virtual BOOL Init();
	virtual BOOL DrawBackground();

	CMechanicWave *Wave;
};

class CMechanicWaveDlg : public CWindow
{
public:
	CMechanicWaveDlg();
	virtual ~CMechanicWaveDlg();

	virtual VOID Destroy();
	virtual long FAR PASCAL WindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
	virtual BOOL Update(DWORD dTime);

	DECLARE_CLASSINFO;

	//////
	BOOL Create();

	CGameEngine ge;
	CWindow Display;
	CWaveGraph gu;
};

#endif