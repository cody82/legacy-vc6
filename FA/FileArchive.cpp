#include "filearchive.h"

CFileArchive::CFileArchive()
{
	hFile=NULL;
	Files=NULL;
	Close();
}

CFileArchive::~CFileArchive()
{
	Close();
}

BOOL CFileArchive::Open(LPSTR file)
{
	DWORD dw;

	Close();

	hFile=CreateFile(file,
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	if(hFile==INVALID_HANDLE_VALUE)
	{
		hFile=NULL;
		return FALSE;
	}

	if(!::ReadFile(hFile,&Header,sizeof(s_Header),&dw,NULL))
	{
		Close();
		return FALSE;
	}

	ReadFileInfos();

	strcpy(szFile,file);

	return TRUE;
}
	
BOOL CFileArchive::Create(LPSTR file)
{
	DWORD dw;

	Close();

	hFile=CreateFile(file,
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	if(hFile==INVALID_HANDLE_VALUE)
	{
		hFile=NULL;
		return FALSE;
	}

	strcpy(Header.Info,"FileArchive");
	Header.Version=1;
	if(!WriteFile(hFile,&Header,sizeof(s_Header),&dw,NULL))
	{
		Close();
		DeleteFile(file);
		return FALSE;
	}

	strcpy(szFile,file);

	return TRUE;
}
	
BOOL CFileArchive::ReadFileInfos()
{
	DWORD dw,dw2;

	if(!hFile)return FALSE;

	if(Files)delete[] Files;

	Files=new s_FileInfo[Header.FileCount];

	SetFilePointer(hFile,sizeof(s_Header),NULL,FILE_BEGIN);

	for(dw2=0;dw2<Header.FileCount;++dw2)
	{
		::ReadFile(hFile,&Files[dw2],sizeof(s_FileInfo),&dw,NULL);
		SetFilePointer(hFile,Files[dw2].Size,NULL,FILE_CURRENT);
	}

	return TRUE;
}

VOID CFileArchive::Close()
{
	memset(&Header,0,sizeof(s_Header));
	memset(szFile,0,64);

	if(hFile)
	{
		CloseHandle(hFile);
		hFile=NULL;
	}
	if(Files)
	{
		delete[] Files;
		Files=NULL;
	}

	Key=0;
}

BOOL CFileArchive::AddFile(LPSTR file)
{
	if(!hFile)return FALSE;

	s_FileInfo fi;
	HANDLE addfile;
	LPVOID buffer=NULL,buffer2=NULL;
	DWORD dw;

	addfile=CreateFile(file,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if(addfile==INVALID_HANDLE_VALUE)return FALSE;


	//Neue FileInfo
	strcpy(fi.Name,file);
	fi.Begin=::GetFileSize(hFile,NULL)+sizeof(s_FileInfo);
	fi.Size=::GetFileSize(addfile,NULL);

	//Neuer Header
	Header.FileCount++;

	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	WriteFile(hFile,&Header,sizeof(s_Header),&dw,NULL);

	//Neues FileInfo
	SetFilePointer(hFile,0,NULL,FILE_END);
	WriteFile(hFile,&fi,sizeof(s_FileInfo),&dw,NULL);

	//Neue datei
	buffer=GlobalAllocPtr(0,::GetFileSize(addfile,NULL));
	SetFilePointer(addfile,0,NULL,FILE_BEGIN);
	::ReadFile(addfile,buffer,::GetFileSize(addfile,NULL),&dw,NULL);

	if(Key>0)EnDeCrypt(buffer,::GetFileSize(addfile,NULL));

	WriteFile(hFile,buffer,::GetFileSize(addfile,NULL),&dw,NULL);
	GlobalFreePtr(buffer);

	CloseHandle(addfile);

	ReadFileInfos();

	return TRUE;
}
	
BOOL CFileArchive::ReadFile(LPSTR file,LPVOID buffer)
{
	DWORD dw,dw2;
	BOOL b;

	if(!hFile)return FALSE;

	for(dw=0;dw<Header.FileCount;++dw)
	{
		if(stricmp(file,Files[dw].Name)==0)
		{
			SetFilePointer(hFile,Files[dw].Begin,NULL,FILE_BEGIN);
			b=::ReadFile(hFile,buffer,Files[dw].Size,&dw2,NULL);
			if(!b)return FALSE;

			if(Key>0)EnDeCrypt(buffer,Files[dw].Size);

			return TRUE;
		}
	}

	return FALSE;
}

DWORD CFileArchive::GetFileSize(LPSTR file)
{
	DWORD dw;

	if(!hFile)return 0;

	for(dw=0;dw<Header.FileCount;++dw)
	{
		if(stricmp(file,Files[dw].Name)==0)
		{
			return Files[dw].Size;
		}
	}

	return 0;
}

BOOL CFileArchive::ExtractFile(LPSTR file)
{
	DWORD dw,dw2;
	HANDLE newfile;
	LPVOID buffer;
	char tmpstr[MAX_PATH];
	char path[MAX_PATH];

	strcpy(tmpstr,"");
	strcpy(path,"");

	for(dw=0;dw<Header.FileCount;++dw)
	{
		if(stricmp(file,Files[dw].Name)==0)
		{
			newfile=CreateFile(file,
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL
				);
			if(newfile==INVALID_HANDLE_VALUE)
			{
				return FALSE;
			}
			
			SetFilePointer(hFile,Files[dw].Begin,NULL,FILE_BEGIN);

			buffer=GlobalAllocPtr(0,Files[dw].Size);
			::ReadFile(hFile,buffer,Files[dw].Size,&dw2,NULL);

			if(Key>0)EnDeCrypt(buffer,Files[dw].Size);

			WriteFile(newfile,buffer,Files[dw].Size,&dw2,NULL);
			GlobalFreePtr(buffer);

			CloseHandle(newfile);

			return TRUE;
		}
	}

	return FALSE;
}

BOOL CFileArchive::FileExists(LPSTR file)
{
	DWORD dw;

	if(!hFile)return FALSE;

	for(dw=0;dw<Header.FileCount;++dw)
	{
		if(stricmp(file,Files[dw].Name)==0)
			return TRUE;
	}

	return FALSE;
}

BOOL CFileArchive::AddDir(LPSTR path,BOOL subdir)
{
	WIN32_FIND_DATA wfd;
	char tmpstr[MAX_PATH];
	char thisfile[64];
	HANDLE sh;

	GetModuleFileName(NULL,thisfile,64);

	//if(!ff.FindFile(path,0))return;
	strcpy(tmpstr,path);
	if(strlen(tmpstr)>0&&tmpstr[strlen(tmpstr)-1]!='\\')
		strcat(tmpstr,"\\");
	strcat(tmpstr,"*.*");
	sh=FindFirstFile(tmpstr,&wfd);
	if(sh==INVALID_HANDLE_VALUE)return FALSE;

	while(TRUE)
	{
		//b=ff.FindNextFile();
		if(!FindNextFile(sh,&wfd))break;
		

		if(stricmp(wfd.cFileName,".")!=0 && stricmp(wfd.cFileName,"..")!=0)
		{
			
			if(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
			{
				strcpy(tmpstr,path);
				if(strlen(tmpstr)>0&&tmpstr[strlen(tmpstr)-1]!='\\')
					strcat(tmpstr,"\\");
				strcat(tmpstr,wfd.cFileName);
				if(tmpstr[strlen(tmpstr)-1]!='\\')
				strcat(tmpstr,"\\");
		if(subdir)
				AddDir(tmpstr,subdir);
			}
			else if(stricmp(szFile,wfd.cFileName)!=0)
			{
		//hf=CreateFile("test.txt",GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		//SetFilePointer(hf,0,NULL,FILE_END);
		strcpy(tmpstr,path);
		//if(tmpstr[strlen(tmpstr)-1]=='\\')tmpstr[strlen(tmpstr)-1]='\0';
		strcat(tmpstr,wfd.cFileName);
		//WriteFile(hf,(LPVOID)tmpstr,strlen(tmpstr),&dw,NULL);
		//WriteFile(hf,(LPVOID)"\r\n",2,&dw,NULL);
		//CloseHandle(hf);
		//strcpy(tmpstr2,"Adding ");
		//strcat(tmpstr2,tmpstr);
		//strcat(tmpstr2,"...");
		//puts(tmpstr2);
		if(stricmp(thisfile,tmpstr)!=0)
				AddFile(tmpstr);
			}
		}
		//if(!b)break;
	}
	FindClose(sh);

	return TRUE;
}

BOOL CFileArchive::ExtractAllFiles()
{
	DWORD dw;

	for(dw=0;dw<Header.FileCount;++dw)
	{
		ExtractFile(Files[dw].Name);
	}

	return TRUE;
}

VOID CFileArchive::SetKey(BYTE key)
{
	Key=key;
}

VOID CFileArchive::EnDeCrypt(LPVOID buffer,DWORD size)
{
	BYTE *b;
	DWORD dw;

	b=(BYTE*)buffer;

	for(dw=0;dw<size;++dw)
	{
		b[dw]^=Key;
	}
}

DWORD CFileArchive::GetFilePos(LPSTR file)
{
	DWORD dw;

	if(!hFile)return 0;

	for(dw=0;dw<Header.FileCount;++dw)
	{
		if(stricmp(file,Files[dw].Name)==0)
			return Files[dw].Begin;
	}

	return 0;

}

BOOL CFileArchive::DeleteFile(LPSTR file)
{
	DWORD dw;
	DWORD writedest;
	DWORD readsrc;
	LPVOID buffer;
	DWORD dw2;
	DWORD readsize;

	if(!hFile)return 0;

	for(dw=0;dw<Header.FileCount;++dw)
	{
		if(stricmp(file,Files[dw].Name)==0)
		{
			if(dw==Header.FileCount-1)//Letzte Datei
			{
				SetFilePointer(hFile,Files[dw].Begin-sizeof(s_FileInfo),NULL,FILE_BEGIN);
				SetEndOfFile(hFile);
				goto OK;
			}
			else
			{
				writedest=Files[dw].Begin-sizeof(s_FileInfo);
				readsrc=Files[dw+1].Begin-sizeof(s_FileInfo);
				readsize=::GetFileSize(hFile,NULL)-readsrc;

				buffer=GlobalAllocPtr(0,readsize);

				SetFilePointer(hFile,readsrc,NULL,FILE_BEGIN);
				::ReadFile(hFile,buffer,readsize,&dw2,NULL);

				SetFilePointer(hFile,writedest,NULL,FILE_BEGIN);
				WriteFile(hFile,buffer,readsize,&dw2,NULL);

				SetEndOfFile(hFile);

				goto OK;
			}
		}
	}

	return FALSE;

OK:
	Header.FileCount--;
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	WriteFile(hFile,&Header,sizeof(s_Header),&dw2,NULL);

	ReadFileInfos();

	return TRUE;
}

/*
BOOL CFileArchive::TruncateFilenameFromPath(LPSTR path)
{
	int i;
	BOOL b=FALSE;

	for(i=strlen(path)-1;i>=0;--i)
	{
		if(path[i]=='\\')
		{
			path[i]='\0';
			b=TRUE;
			break;
		}
	}

	return b;
}

BOOL CFileArchive::CreateDirTree(LPSTR path)
{
	char tmpstr[MAX_PATH];
	DWORD l=strlen(path);
	DWORD dw;
	char olddir[MAX_PATH];

	GetCurrentDirectory(MAX_PATH,olddir);

	strcpy(tmpstr,path);

	for(dw=0;dw<l;++dw)
	{
		if(tmpstr[dw]=='\\')tmpstr[dw]='\0';
	}

	for(dw=0;dw<l;++dw)
	{
		if(tmpstr[dw]=='\0')
		{
			CreateDirectory(&tmpstr[dw+1],NULL);
			SetCurrentDirectory(&tmpstr[dw+1]);
		}
		else if(dw==0&&tmpstr[dw]!='\0')
		{
			CreateDirectory(tmpstr,NULL);
			SetCurrentDirectory(tmpstr);
		}
	}

	SetCurrentDirectory(olddir);

	return TRUE;
}*/

