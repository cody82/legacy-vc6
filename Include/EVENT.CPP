#include "event.h"

Event::Event()
{
	repeat=FALSE;
	t2raise=0;
	tinterval=0;
	del=FALSE;
	event=NULL;
	enabled=TRUE;
}

Event::~Event()
{
}

void Event::Update(UINT dtime)
{
	if(!enabled)return;
	if(dtime>=t2raise)
	{
		Raise();
		if(repeat)
			t2raise=tinterval;
		else
		{
			del=TRUE;
		}
	}
	else
		t2raise-=dtime;
}

void Event::Raise()
{
	if(event)
		event();
}