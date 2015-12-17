#include "cpakfile.h"
	
CPackFile::CPackFile()
{
	isopen=FALSE;
	pfh=new PACKFILEHEADER;
	memset(pfh,0,sizeof(PACKFILEHEADER));
}

CPackFile::~CPackFile()
{
	Close();
	delete pfh;
}

BOOL CPackFile::Open(LPSTR pack)
{
	Close();
	if(GetPackFileHeader(pack,pfh))
	{
		strcpy(packfile,pack);
		isopen=TRUE;
		return TRUE;
	}
	else return FALSE;
}
	
DWORD CPackFile::GetFileSize(LPSTR file)
{
	if(!isopen)return FALSE;
	if(!FileExist(file))return FALSE;

	return GetFileSize(file);
}

void CPackFile::Close()
{
	isopen=FALSE;
}

BOOL CPackFile::FileExist(LPSTR file)
{
	if(!isopen)return FALSE;
	return FileInPack(packfile,file);
}

BOOL CPackFile::GetFileInfo(LPSTR file,PACK *p)
{
	if(!isopen)return FALSE;
	return GetFileInfoFromPFH(pfh,file,p);
}

BOOL CPackFile::ExtractFile(LPSTR file,LPSTR dir)
{
	if(!isopen)return FALSE;
	return ExtractFileFromPack(packfile,file,dir);
}

BOOL CPackFile::CopyFile(LPSTR file,LPVOID mem)
{
	if(!isopen)return FALSE;

	PACK pack;
	int i,i2;
	BOOL found=FALSE;
	HANDLE pakfile;
	HANDLE outfile;
	byte *b;
	DWORD dw;
	DWORD dw2;
	char tmpstr[MAX_PATH];
	char path[MAX_PATH];


	GetFileInfoFromPFH(pfh,file,&pack);
	

	for(i=0;i<(int)pfh->nfiles;++i)
	{
		if(stricmp(pfh->Packs[i].File,file)==0)
		{
			found=TRUE;
			break;
		}
	}
	if(!found)return FALSE;
		
	pakfile=CreateFile(packfile,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(pakfile==INVALID_HANDLE_VALUE)
		return FALSE;

	SetFilePointer(pakfile,(LONG)pfh->Packs[i].Begin,NULL,FILE_BEGIN);

	ReadFile(pakfile,mem,(LONG)(pfh->Packs[i].End-pfh->Packs[i].Begin),&dw,NULL);

	CloseHandle(pakfile);
	return TRUE;
}
