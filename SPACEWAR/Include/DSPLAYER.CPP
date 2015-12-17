#include "dsplayer.h"

DSPlayer::DSPlayer()
{
	int i;

	for(i=0;i<MAXSOUNDS;++i)
		lpDSB[i]=NULL;

	for(i=0;i<MAXORGINALSOUNDS;++i)
		lpDSBOrg[i]=NULL;

	for(i=0;i<MAXORGINALSOUNDS;++i)
		strcpy(soundtype[i],"");

	minvolume=SOUNDMINVOLUME;

	lpDS=NULL;
}
	
BOOL DSPlayer::LoadSound(LPSTR file,int i)
{
	ReleaseOrginalBuffer(i);
	lpDSBOrg[i]=DSLoadSoundBuffer(lpDS,file);
	if(lpDSBOrg[i])
	{
		strcpy(filenames[i],file);
		return TRUE;
	}
	return FALSE;
}
	
int DSPlayer::Play(int n)
{
	int i;
	for(i=0;i<MAXORGINALSOUNDS;++i)
	{
		if(!lpDSB[i])break;
	}

	if(lpDSBOrg[n])
	{
		lpDS->DuplicateSoundBuffer(lpDSBOrg[n],&lpDSB[i]);
		if(loop[n])
			lpDSB[i]->Play(0,0,DSBPLAY_LOOPING);
		else
			lpDSB[i]->Play(0,0,0);
	}
	else return -1;

	return i;

}

DSPlayer::~DSPlayer()
{
	int i;
	
/*	try
	{
	mp3.Erase();
	GAUDIO_ShutDown();*/

	for(i=0;i<MAXSOUNDS;++i)
	{
		if(lpDSB[i])
		{
			lpDSB[i]->Release();
			lpDSB[i]=NULL;
		}
	}
	
	for(i=0;i<MAXORGINALSOUNDS;++i)
	{
		if(lpDSBOrg[i])
		{
			lpDSBOrg[i]->Release();
			lpDSBOrg[i]=NULL;
		}
	}

	if(lpDS)
	{
		lpDS->Release();
		lpDS=NULL;
	}
/*	}
	catch(...)
	{
	}
*/	
}

BOOL DSPlayer::Initialize(HWND hwnd,DWORD dsprio)
{
	HRESULT hr;
	
	hr=DirectSoundCreate(NULL, &lpDS, NULL);
	if(hr!=DS_OK)
	{
		lpDS=NULL;
		return FALSE;
	}

	hr=lpDS->SetCooperativeLevel(hwnd,dsprio);
	if(hr!=DS_OK)
	{
		lpDS->Release();
		lpDS=NULL;
		return FALSE;
	}

//	GAUDIO_SetPointerToDirectSound(lpDS);

	return TRUE;
}
	
BOOL DSPlayer::LoadSounds(LPSTR inifile)
{
	int i;
	char tmpstr[64],tmpstr2[64];
	int v1,v2,v3;
	float f;
	DWORD dw;

	if(!lpDS)return FALSE;

	minvolume=GetPrivateProfileIntCurrentDir(inifile,"mastervolume","dsminvolume",SOUNDMINVOLUME);

	for(i=0;i<MAXORGINALSOUNDS;++i)
	{
		sprintf(tmpstr,"sound%.3d",i);
		
		if(!GetPrivateProfileStringCurrentDir(inifile,"files",tmpstr,tmpstr2,64))break;
		if(stricmp(tmpstr2,"NULL")!=0)
			if(!LoadSound(tmpstr2,i))break;
		
		if(GetPrivateProfileStringCurrentDir(inifile,"type",tmpstr,tmpstr2,64))
			SetType(i,tmpstr2);

		v1=GetPrivateProfileIntCurrentDir(inifile,"volume",tmpstr,100);
		v2=GetPrivateProfileIntCurrentDir(inifile,"typevolume",tmpstr2,100);
		v3=GetPrivateProfileIntCurrentDir(inifile,"mastervolume","volume",100);
		SetVolume(i,(int)((float)(v1*v2*v3)/(100*100)));

		loop[i]=GetPrivateProfileIntCurrentDir(inifile,"loop",tmpstr,0);

		if(GetPrivateProfileStringCurrentDir(inifile,"frequency",tmpstr,tmpstr2,64))
		{
			f=(float)str2double(tmpstr2);

			if(lpDSBOrg[i])
			{
				lpDSBOrg[i]->GetFrequency(&dw);
				lpDSBOrg[i]->SetFrequency((DWORD)(f*(float)dw));
			}
		}
	}
	return TRUE;
}

int DSPlayer::Play(int n,BOOL loop)
{
	int i;
	if(n<0)return -1;

	for(i=0;i<MAXORGINALSOUNDS;++i)
	{
		if(!lpDSB[i])break;
	}

	if(lpDSBOrg[n])
	{
		lpDS->DuplicateSoundBuffer(lpDSBOrg[n],&lpDSB[i]);
		if(loop)
			lpDSB[i]->Play(0,0,DSBPLAY_LOOPING);
		else
			lpDSB[i]->Play(0,0,0);
	}

	return i;
}

int DSPlayer::PlayFile(LPCSTR file,BOOL loop)
{
	int i;

	for(i=0;i<MAXORGINALSOUNDS;++i)
	{
		if(stricmp(filenames[i],file)==0)
		{
			return Play(i,loop);
		}
	}

	i=LoadSound(file);
	return Play(i,loop);
	
}
	
int DSPlayer::GetSoundNr(LPSTR file)
{
	int i;

	for(i=0;i<MAXORGINALSOUNDS;++i)
	{
		if(stricmp(file,filenames[i])==0&&lpDSBOrg[i])
		{
			return i;
		}
	}
	return -1;
}

int DSPlayer::LoadSound(LPCSTR file)
{
	int i;
	
	for(i=0;i<MAXORGINALSOUNDS;++i)
	{
		if(lpDSBOrg[i]&&stricmp(file,filenames[i])==0)
		{
			return i;
		}
	}

	for(i=0;i<MAXORGINALSOUNDS;++i)
	{
		if(lpDSBOrg[i]==NULL)
		{
			lpDSBOrg[i]=DSLoadSoundBuffer(lpDS,file);
			if(!lpDSBOrg[i])
			{
				return -1;
			}
			strcpy(filenames[i],file);
			break;
		}
	}
	return i;
}
	
void DSPlayer::SetVolume(int percent)
{
	int i;

	for(i=0;i<MAXORGINALSOUNDS;++i)
	{
		if(lpDSBOrg[i])
			lpDSBOrg[i]->SetVolume((int)(minvolume+(float)percent/100*abs(minvolume)));
	}
	for(i=0;i<MAXSOUNDS;++i)
	{
		if(lpDSB[i])
			lpDSB[i]->SetVolume((int)(minvolume+(float)percent/100*abs(minvolume)));
	}
}

void DSPlayer::SetVolume(int n,int percent)
{
	if(lpDSBOrg[n])lpDSBOrg[n]->SetVolume((int)(minvolume+(float)percent/100*abs(minvolume)));
}

void DSPlayer::SetVolume2(LPSTR type,int percent)
{
	int i;

	for(i=0;i<MAXORGINALSOUNDS;++i)
	{
		if(soundtype[i]==type&&lpDSBOrg[i])
			lpDSBOrg[i]->SetVolume((int)(minvolume+(float)percent/100*abs(minvolume)));
	}
	for(i=0;i<MAXSOUNDS;++i)
	{
		if(soundtype[i]==type&&lpDSB[i])
			lpDSB[i]->SetVolume((int)(minvolume+(float)percent/100*abs(minvolume)));
	}
}

void DSPlayer::ReleaseUnusedBuffers()
{
	int i;
	DWORD dw=0;

	for(i=0;i<MAXSOUNDS;++i)
	{
		if(lpDSB[i])
		{
			lpDSB[i]->GetStatus(&dw);
			if(dw==0)//!(dw&DSBSTATUS_LOOPING ||dw&DSBSTATUS_PLAYING ))
			{
				lpDSB[i]->Release();
				strcpy(filenames[i],"");
				lpDSB[i]=NULL;
			}
		}
	}
}
	
void DSPlayer::SetType(int n,LPSTR type2)
{
	if(n<0||n>=MAXORGINALSOUNDS)return;
	strcpy(soundtype[n],type2);
}

BOOL DSPlayer::ReleaseOrginalBuffer(int n)
{
	if(lpDSBOrg[n])
	{
		lpDSBOrg[n]->Release();
		lpDSBOrg[n]=NULL;
		strcpy(filenames[n],"");
		return TRUE;
	}
	else return FALSE;
}

BOOL DSPlayer::ReleaseOrginalBufferFile(LPCSTR file)
{
	int i;

	for(i=0;i<MAXORGINALSOUNDS;++i)
	{
		if(stricmp(filenames[i],file)==0)
		{
			lpDSBOrg[i]->Release();
			lpDSBOrg[i]=NULL;
			strcpy(filenames[i],"");
			return TRUE;
		}
	}

	return FALSE;

}
/*
BOOL DSPlayer::PlayMP3(LPSTR file)
{
	ZeroMemory(&mp3, sizeof mp3);
	mp3.OutputMode= GAUDIO_OUTPUTMODE_DIRECTSOUND;
	mp3.Source= GAUDIO_STRSRC_DISK;
	mp3.SampleFlag=GAUDIO_SAMPFLG_LOOP;

	mp3.Name= file;

	mp3.Init();

	//mp3.SetPrimaryDSBuffer(GAUDIO_DSPRIMBUF_MAXIMUMFREQ);
	mp3.Play();

	return TRUE;
}
*/