#include "caviplaytest.h"

CAVIPlayTest::CAVIPlayTest()
	{
		CurrentTime=0;
		FileOpen=FALSE;
		AVIFileInit();
	}

CAVIPlayTest::~CAVIPlayTest()
	{
		AVIFileExit();          // releases AVIFile library 
		Close();
	}

	BOOL CAVIPlayTest::Open(LPCSTR file)
	{
		if(FileOpen)Close();
		LPVOID data;
  
		if(AVIFileOpen(&pfile, file, OF_SHARE_DENY_WRITE, 0L)!=0)
			return FALSE;

		if(AVIFileGetStream(pfile,&pstream,streamtypeVIDEO,0)!=0)
			return FALSE;

		if(AVIStreamInfo(pstream,&streaminfo,sizeof(streaminfo))!=0)
			return FALSE;

		if((pframe=AVIStreamGetFrameOpen(pstream,NULL))==NULL)
			return FALSE;

		data=AVIStreamGetFrame(pframe,AVIStreamStart(pstream));
		if(data==NULL)return FALSE;

		DibInfo((HDIB)data,&bminfo);
		FileOpen=TRUE;
		return TRUE;
	}

	BOOL CAVIPlayTest::Paint(HDC hdc)
	{
		if(!FileOpen)return FALSE;
		LPVOID data;
		RECT destrect,srcrect;

		data=AVIStreamGetFrame(pframe,AVIStreamTimeToSample(pstream,(LONG)CurrentTime));
		if(data==NULL)return FALSE;
			
		destrect.left=0;
		destrect.right=bminfo.biWidth;
		destrect.top=0;
		destrect.bottom=bminfo.biHeight;
			
		srcrect.left=0;
		srcrect.right=bminfo.biWidth;
		srcrect.top=0;
		srcrect.bottom=bminfo.biHeight;

		PaintDIB(hdc,&destrect,(HDIB)data,&srcrect,NULL);
		return TRUE;
	}

	void CAVIPlayTest::Close()
	{
		if(!FileOpen)return;
		AVIFileRelease(pfile);  // closes the file 
		FileOpen=FALSE;
	}
