#ifndef __CMDLINEITEM_H
#define __CMDLINEITEM_H

#include "engine.h"

#define CLI_BUFFERSIZE 1024

class CmdLineItem : public BaseItem
{
public:

	UINT maxlines;
	UINT nlines;
	char text[CLI_BUFFERSIZE];
	byte color[3];
	UINT tlinedeleteinterval;
	UINT tlastdelete;

	CmdLineItem();
	virtual ~CmdLineItem();

	virtual void Draw(LPDIRECTDRAWSURFACE3 lpDDS,int x,int y);

	virtual void Update(UINT dtime);

	void DeleteFirstLine();

private:
	void CountLines();
};

#endif