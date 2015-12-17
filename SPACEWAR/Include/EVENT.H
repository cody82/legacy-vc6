#ifndef __EVENT_H
#define __EVENT_H

class Event;
#include "engine.h"

class Event
{
public:

	UINT t2raise;
	UINT tinterval;
	BOOL repeat;
	BOOL del;
	BOOL enabled;

	//VOIDPROC event;
	void (*event)();

	Event();
	~Event();
	void Update(UINT dtime);
	void Raise();

};


#endif