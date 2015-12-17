#ifndef __BITBOOL_H
#define __BITBOOL_H

#include "windows.h"
#include "int2str.h"

//#define BBC_MAXBB

struct BYTEBITARRAY
{
	byte b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1;
};

class CBitBool
{
public:
	CBitBool();
	~CBitBool();

	BOOL New(UINT size,BOOL deleteifdestroyed);
	BOOL NewFromPBM_ascii(LPSTR file,BOOL deleteifdestroyed);
	void Delete();
	BOOL GetBit(UINT bitpos);
	BOOL GetBit(UINT bytepos,UINT bitpos);
	BOOL SetBit(UINT bitpos,BOOL b);
	BOOL SetBit(UINT bytepos,UINT bitpos,BOOL b);
	void Invert();
	BOOL NewFromPBM_asciiInFile(HANDLE hfile,DWORD begin,DWORD size,BOOL deleteifdestroyed);
	BOOL Equal(CBitBool *bb);
	BOOL NewFromPBM_asciiRect(LPSTR file,RECT rect,BOOL deleteifdestroyed);
	static POINT GetPBMSize(LPSTR file);
	BOOL NewFromBMP(LPSTR file,HDC hdc,BOOL deletedestroyed);
	BOOL NewFromBMPRect(HBITMAP hbm,HDC hdc,RECT rect,BOOL deletedestroyed);

	static BOOL LoadPBM_sw_ascii(byte *b,LPSTR file);
	static BOOL LoadPBM_sw_asciiInFile(byte *b,HANDLE hfile,DWORD begin,DWORD size);

	BYTEBITARRAY *bits;
	UINT bytesize;
	UINT bitsize;
	BOOL deldestroyed;
	char pbmfile[128];

};
/*
class CBBContainer
{
public:

	CBBContainer();
	~CBBContainer();
	int Load(LPSTR file);
};
*/


#endif