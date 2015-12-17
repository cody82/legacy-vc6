#include "profiles.h"

int GetPrivateProfileIntCurrentDir(char *file,char *section,char *key,int defaultint)
{
	char path[256];
	GetCurrentDirectory(256,path);
	if(path[strlen(path)-1]!='\\')
		strcat(path,"\\");
	strcat(path,file);
	return(GetPrivateProfileInt(section,key,defaultint,path));
} /* GetPrivateProfileIntCurrentDir */

BOOL GetPrivateProfileStringCurrentDir(char *file,char *section,char *key,char *retbuffer,int size)
{
	char path[256];
	int i=0;
	GetCurrentDirectory(256,path);
	if(path[strlen(path)-1]!='\\')
		strcat(path,"\\");
	strcat(path,file);
	i=GetPrivateProfileString(section,key,"\0",retbuffer,size,path);
	if(i==0)
		return(FALSE);
	else
		return(TRUE);
} /* GetPrivateProfileStringCurrentDir */

BOOL WritePrivateProfileStringCurrentDir(char *file,char *section,char *key,char *string)
{
	char path[256];
	GetCurrentDirectory(256,path);
	if(path[strlen(path)-1]!='\\')
		strcat(path,"\\");
	strcat(path,file);
	return(WritePrivateProfileString(section,key,string,path));
} /* WritePrivateProfileStringCurrentDir */

BOOL WritePrivateProfileIntCurrentDir(char *file,char *section,char *key,int i)
{
	char path[256];
	char buffer[64];

	GetCurrentDirectory(256,path);
	if(path[strlen(path)-1]!='\\')
		strcat(path,"\\");
	strcat(path,file);
	sprintf(buffer,"%d",i);
	return(WritePrivateProfileString(section,key,buffer,path));
} /* WritePrivateProfileIntCurrentDir */

BOOL GetProfileSectionNamesCurDir(char *file,char *buffer,int size)
{
	char path[256];
	UINT ui;

	GetCurrentDirectory(256,path);
	if(path[strlen(path)-1]!='\\')
		strcat(path,"\\");
	strcat(path,file);

	ui=GetPrivateProfileSectionNames(buffer,size,path);
	if(buffer[0]==0||ui==0)return FALSE;

	return TRUE;
} /* GetProfileSectionNamesCurDir */

BOOL GetProfileSectionCurDir(char *file,char *section,char *buffer,int size)
{
	char path[256];
	UINT ui;

	GetCurrentDirectory(256,path);
	if(path[strlen(path)-1]!='\\')
		strcat(path,"\\");
	strcat(path,file);

	ui=GetPrivateProfileSection(section,buffer,size,path);
	if(buffer[0]==0||ui==0)return FALSE;

	return TRUE;
} /* GetProfileSectionCurDir */

