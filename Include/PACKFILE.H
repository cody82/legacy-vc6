#ifndef __PACKFILE_H
#define __PACKFILE_H

#ifndef __AFX_H__
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#endif

#define MAXFILES 10000
#define MAXCHARS 256
#define BUFFERSIZE 4096

struct PACK
{
	char File[MAXCHARS];
	DWORD Begin;
	DWORD End;
};

struct PACKFILEHEADER
{
	DWORD nfiles;
	PACK Packs[MAXFILES];
};

BOOL ExtractFileFromPack(LPSTR pack,LPSTR file,LPSTR dir);
DWORD GetFileSizeInPack(LPSTR pack,LPSTR file);
BOOL FileInPack(LPSTR pack,LPSTR file);
BOOL CopyFileFromPack(LPSTR pack,LPSTR file,LPVOID mem);
BOOL AddFile2Pack(LPSTR pack,LPSTR file);
BOOL TruncateFilenameFromPath(LPSTR path);
BOOL AddDir2Pack(LPSTR pack,LPSTR path);
BOOL ExtractAllFilesFromPack(LPSTR pack,LPSTR dir);
DWORD GetFilePosInPack(LPSTR pack,LPSTR file);
BOOL GetPackFileHeader(LPSTR pack,PACKFILEHEADER *pfh);
BOOL GetFileInfoFromPFH(PACKFILEHEADER *pfh,LPSTR file,PACK *pack);

#endif