#include "buttons.h"

void OnButtonExitClick()
{
	gamedata.tpexit=timeGetTime()+500;
}

void OnButtonResumeClick()
{
	mainengine.Pause("");
	window[0].enabled=mainengine.pause;
}

void OnButtonRestartClick()
{
}

void OnButtonOptionsClick()
{
}
