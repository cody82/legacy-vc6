#include "packfile.h"

BOOL ExtractFileFromPack(LPSTR pack,LPSTR file,LPSTR dir)
{
	int i,i2;
	BOOL found=FALSE;
	HANDLE pakfile;
	HANDLE outfile;
	byte *b;
	DWORD dw;
	DWORD dw2;
	PACKFILEHEADER *pfh;
	pfh=new PACKFILEHEADER;
	char tmpstr[MAX_PATH];
	char path[MAX_PATH];

	pakfile=CreateFile(pack,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(pakfile==INVALID_HANDLE_VALUE)
	{
		delete pfh;
		return FALSE;
	}

	ReadFile(pakfile,(LPVOID)pfh,sizeof(*pfh),&dw,NULL);
	for(i=0;i<(int)pfh->nfiles;++i)
	{
		if(stricmp(pfh->Packs[i].File,file)==0)
		{
			found=TRUE;
			break;
		}
	}

	if(!found)
	{
		delete pfh;
		CloseHandle(pakfile);
		return FALSE;
	}

	if(dir&&strlen(dir)>0)
	{
		strcpy(path,dir);
		if(path[strlen(path)-1]!='\\'&&file[0]!='\\')
			strcat(path,"\\");
		else if(path[strlen(path)-1]=='\\'&&file[0]=='\\')
			path[strlen(path)-1]='\0';
		strcat(path,file);
	}
	else
	{
		strcpy(path,file);
	}

	strcpy(tmpstr,path);
	if(TruncateFilenameFromPath(tmpstr))
	{
		CreateDirectory(tmpstr,NULL);
	}

	outfile=CreateFile(path,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(outfile==INVALID_HANDLE_VALUE)
	{
		delete pfh;
		CloseHandle(pakfile);
		return FALSE;
	}

	SetFilePointer(pakfile,(LONG)pfh->Packs[i].Begin,NULL,FILE_BEGIN);

	b=new byte[BUFFERSIZE];
	for(i2=(int)pfh->Packs[i].Begin;i2<(int)pfh->Packs[i].End;++i2)
	{
		ReadFile(pakfile,(LPVOID)b,BUFFERSIZE,&dw,NULL);
		WriteFile(outfile,(LPVOID)b,dw,&dw2,NULL);
		if(dw2<BUFFERSIZE)break;
	}
	
	CloseHandle(outfile);
	CloseHandle(pakfile);

	delete b;
	delete pfh;
	return TRUE;

}

DWORD GetFileSizeInPack(LPSTR pack,LPSTR file)
{
	int i;
	BOOL found=FALSE;
	HANDLE pakfile;
	DWORD dw;
	PACKFILEHEADER *pfh;
	pfh=new PACKFILEHEADER;

	pakfile=CreateFile(pack,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(pakfile==INVALID_HANDLE_VALUE)
	{
		delete pfh;
		return 0;
	}

	ReadFile(pakfile,(LPVOID)pfh,sizeof(*pfh),&dw,NULL);
	for(i=0;i<MAXFILES;++i)
	{
		if(stricmp(file,pfh->Packs[i].File)==0)
		{
			dw=pfh->Packs[i].End-pfh->Packs[i].Begin;
			delete pfh;
			CloseHandle(pakfile);
			return dw;
		}
	}
	delete pfh;
	CloseHandle(pakfile);
	return 0;
}

BOOL FileInPack(LPSTR pack,LPSTR file)
{
	int i;
	BOOL found=FALSE;
	HANDLE pakfile;
	DWORD dw;
	PACKFILEHEADER *pfh;
	pfh=new PACKFILEHEADER;

	pakfile=CreateFile(pack,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(pakfile==INVALID_HANDLE_VALUE)
	{
		delete pfh;
		return FALSE;
	}

	ReadFile(pakfile,(LPVOID)pfh,sizeof(*pfh),&dw,NULL);
	for(i=0;i<MAXFILES;++i)
	{
		if(stricmp(file,pfh->Packs[i].File)==0)
		{
			delete pfh;
			CloseHandle(pakfile);
			return TRUE;
		}
	}
	delete pfh;
	CloseHandle(pakfile);
	return FALSE;

}

BOOL CopyFileFromPack(LPSTR pack,LPSTR file,LPVOID mem)
{
	int i;
	BOOL found=FALSE;
	HANDLE pakfile;
	DWORD dw;
	DWORD size;
	PACKFILEHEADER *pfh;
	pfh=new PACKFILEHEADER;
	LPBYTE pb=(LPBYTE)mem;

	pakfile=CreateFile(pack,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(pakfile==INVALID_HANDLE_VALUE)
	{
		delete pfh;
		return FALSE;
	}

	ReadFile(pakfile,(LPVOID)pfh,sizeof(*pfh),&dw,NULL);
	for(i=0;i<MAXFILES;++i)
	{
		if(stricmp(file,pfh->Packs[i].File)==0)
		{
			found=TRUE;
			break;
		}
	}
	if(!found)
	{
		delete pfh;
		CloseHandle(pakfile);
		return FALSE;
	}

	size=pfh->Packs[i].End-pfh->Packs[i].Begin;
	dw=SetFilePointer(pakfile,pfh->Packs[i].Begin,NULL,FILE_BEGIN);

	ReadFile(pakfile,mem,size,&dw,NULL);

	delete pfh;
	CloseHandle(pakfile);
	return TRUE;

}

BOOL AddFile2Pack(LPSTR pack,LPSTR file)
{
	HANDLE pakfile;
	HANDLE addfile;
	byte *b;
	DWORD dw;
	DWORD addsize;
	DWORD dw2;
	int i;
	PACKFILEHEADER *pfh;
	pfh=new PACKFILEHEADER;


	addfile=CreateFile(file,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(addfile==INVALID_HANDLE_VALUE)
	{
		delete pfh;
		return FALSE;
	}

	pakfile=CreateFile(pack,GENERIC_WRITE|GENERIC_READ,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(pakfile==INVALID_HANDLE_VALUE)
	{
		delete pfh;
		CloseHandle(addfile);
		return FALSE;
	}

	memset(pfh,0,sizeof(*pfh));
	if(GetFileSize(pakfile,NULL)>0)
	{
		ReadFile(pakfile,(LPVOID)pfh,sizeof(*pfh),&dw,NULL);
		for(i=0;i<MAXFILES;++i)
		{
			if(stricmp(file,pfh->Packs[i].File)==0)
			{
				delete pfh;
				CloseHandle(pakfile);
				CloseHandle(addfile);
				return FALSE;
			}
		}
	}
	
	strcpy(pfh->Packs[pfh->nfiles].File,file);
	pfh->nfiles++;
	if(pfh->nfiles==1)
		pfh->Packs[pfh->nfiles-1].Begin=sizeof(*pfh);
	else
		pfh->Packs[pfh->nfiles-1].Begin=pfh->Packs[pfh->nfiles-2].End;

	addsize=GetFileSize(addfile,NULL);
	pfh->Packs[pfh->nfiles-1].End=pfh->Packs[pfh->nfiles-1].Begin+addsize;

	SetFilePointer(pakfile,0,NULL,FILE_BEGIN);
	WriteFile(pakfile,(LPVOID)pfh,sizeof(*pfh),&dw,NULL);

	SetFilePointer(pakfile,0,NULL,FILE_END);

	b=new byte[BUFFERSIZE];
	for(i=0;i>=0/*(int)addsize*/;++i)
	{
		ReadFile(addfile,(LPVOID)b,BUFFERSIZE,&dw,NULL);
		WriteFile(pakfile,(LPVOID)b,dw,&dw2,NULL);
		if(dw<BUFFERSIZE)break;
	}

	CloseHandle(addfile);
	CloseHandle(pakfile);

	delete b;
	delete pfh;
	return TRUE;
}

BOOL TruncateFilenameFromPath(LPSTR path)
{
	char *c;

	c=strrchr(path,'\\');
	if(c)
	{
		*c='\0';
		return TRUE;
	}
	return FALSE;
}

BOOL AddDir2Pack(LPSTR pack,LPSTR path)
{
	WIN32_FIND_DATA wfd;
	char tmpstr[MAX_PATH],tmpstr2[MAX_PATH];
	HANDLE sh;

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
				AddDir2Pack(pack,tmpstr);
			}
			else if(stricmp(pack,wfd.cFileName)!=0)
			{
		//hf=CreateFile("test.txt",GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		//SetFilePointer(hf,0,NULL,FILE_END);
		strcpy(tmpstr,path);
		//if(tmpstr[strlen(tmpstr)-1]=='\\')tmpstr[strlen(tmpstr)-1]='\0';
		strcat(tmpstr,wfd.cFileName);
		//WriteFile(hf,(LPVOID)tmpstr,strlen(tmpstr),&dw,NULL);
		//WriteFile(hf,(LPVOID)"\r\n",2,&dw,NULL);
		//CloseHandle(hf);
		strcpy(tmpstr2,"Adding ");
		strcat(tmpstr2,tmpstr);
		strcat(tmpstr2,"...");
		puts(tmpstr2);
				AddFile2Pack(pack,tmpstr);
			}
		}
		//if(!b)break;
	}
	FindClose(sh);

	return TRUE;
}

BOOL ExtractAllFilesFromPack(LPSTR pack,LPSTR dir)
{
	int i;
	HANDLE pakfile;
	PACKFILEHEADER *pfh;
	DWORD dw;
	pfh=new PACKFILEHEADER;


	pakfile=CreateFile(pack,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(pakfile==INVALID_HANDLE_VALUE)
	{
		delete pfh;
		return FALSE;
	}

	ReadFile(pakfile,(LPVOID)pfh,sizeof(*pfh),&dw,NULL);
	for(i=0;i<MAXFILES;++i)
	{
		if(strlen(pfh->Packs[i].File)>0)
		{
			ExtractFileFromPack(pack,pfh->Packs[i].File,dir);
		}
	}
	delete pfh;
	return TRUE;
}

DWORD GetFilePosInPack(LPSTR pack,LPSTR file)
{

	if(!FileInPack(pack,file))return 0;
	
	int i;
	HANDLE pakfile;
	DWORD dw;
	PACKFILEHEADER *pfh;
	pfh=new PACKFILEHEADER;

	pakfile=CreateFile(pack,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(pakfile==INVALID_HANDLE_VALUE)
	{
		delete pfh;
		return 0;
	}

	ReadFile(pakfile,(LPVOID)pfh,sizeof(*pfh),&dw,NULL);
	for(i=0;i<MAXFILES;++i)
	{
		if(stricmp(file,pfh->Packs[i].File)==0)
		{
			dw=pfh->Packs[i].Begin;
			delete pfh;
			CloseHandle(pakfile);
			return dw;
		}
	}
	delete pfh;
	CloseHandle(pakfile);
	return 0;

}

BOOL GetPackFileHeader(LPSTR pack,PACKFILEHEADER *pfh)
{
	if(!pfh)return FALSE;

	HANDLE pakfile;
	DWORD dw;

	pakfile=CreateFile(pack,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(pakfile==INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	ReadFile(pakfile,(LPVOID)pfh,sizeof(*pfh),&dw,NULL);
	CloseHandle(pakfile);
	return TRUE;

}

BOOL GetFileInfoFromPFH(PACKFILEHEADER *pfh,LPSTR file,PACK *pack)
{
	if(!pfh)return FALSE;
	if(!pack)return FALSE;

	int i;

	for(i=0;i<MAXFILES;++i)
	{
		if(stricmp(file,pfh->Packs[i].File)==0)
		{
			memcpy(pack,&pfh->Packs[i],sizeof(PACK));
			return TRUE;
		}
	}
	return FALSE;

}