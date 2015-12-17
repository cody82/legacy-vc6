#ifndef __FILEARCHIVE_H
#define __FILEARCHIVE_H

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

#define FA_NAMESIZE 64
#define FA_INFOSIZE 16
#define FA_HEADERSIZE 64
#define FA_RESERVEDSIZE FA_HEADERSIZE-2*sizeof(DWORD)-FA_INFOSIZE

class CFileArchive
{
	struct s_Header
	{
		char Info[FA_INFOSIZE];
		DWORD Version;
		DWORD FileCount;
		BYTE Reserved[FA_RESERVEDSIZE];
	};
	struct s_FileInfo
	{
		char Name[FA_NAMESIZE];
		DWORD Begin;
		DWORD Size;
	};

public:
	CFileArchive();
	virtual ~CFileArchive();

	virtual BOOL Open(LPSTR file);
	virtual BOOL Create(LPSTR file);
	virtual VOID Close();

	virtual BOOL AddFile(LPSTR file);
	virtual BOOL ExtractFile(LPSTR file);
	virtual BOOL FileExists(LPSTR file);
	virtual BOOL ReadFile(LPSTR file,LPVOID buffer);
	virtual BOOL ReadFileInfos();

	virtual DWORD GetFileSize(LPSTR file);
	virtual DWORD GetFilePos(LPSTR file);

	virtual BOOL AddDir(LPSTR path,BOOL subdir);
	virtual BOOL ExtractAllFiles();

	virtual VOID SetKey(BYTE key);

	virtual BOOL DeleteFile(LPSTR file);
	//virtual BOOL CreateDirTree(LPSTR path);
	virtual VOID EnDeCrypt(LPVOID buffer,DWORD size);
	//virtual BOOL TruncateFilenameFromPath(LPSTR path);

public:
	HANDLE hFile;
	char szFile[64];

	BYTE Key;

	s_Header Header;

	s_FileInfo *Files;
};

#endif