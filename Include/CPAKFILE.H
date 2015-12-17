#ifndef __CPACKFILE_H
#define __CPACKFILE_H

#ifndef __AFX_H__
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#endif

#include "packfile.h"

class CPackFile
{
public:
	CPackFile();
	~CPackFile();

	BOOL Open(LPSTR pack);
	void Close();

	BOOL FileExist(LPSTR file);
	BOOL ExtractFile(LPSTR file,LPSTR dir);
	BOOL CopyFile(LPSTR file,LPVOID mem);
	DWORD GetFileSize(LPSTR file);
	BOOL GetFileInfo(LPSTR file,PACK *p);

	char packfile[256];
private:
	BOOL isopen;
	PACKFILEHEADER *pfh;

};



#endif
