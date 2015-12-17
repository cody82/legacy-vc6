#include "bitbool.h"

CBitBool::CBitBool()
{
	bits=NULL;
	bytesize=0;
	bitsize=0;
	deldestroyed=TRUE;
	strcpy(pbmfile,"");
}

CBitBool::~CBitBool()
{
	if(deldestroyed)
		Delete();
}

void CBitBool::Invert()
{
	UINT i;
	for(i=0;i<bitsize;++i)
		SetBit(i,!GetBit(i));
}

BOOL CBitBool::Equal(CBitBool *bb)
{
	if(!bb)return FALSE;
	
	//if(strcmp(pbmfile,bb->pbmfile)==0)return TRUE;

	if(	bitsize!=bb->bitsize||
		bytesize!=bb->bytesize//||
		//deldestroyed!=bb->deldestroyed
		)
		return FALSE;

	if(bits==bb->bits)return TRUE;

	if(memcmp(bits,bb->bits,bytesize)==0)return TRUE;

	return FALSE;
}

BOOL CBitBool::NewFromPBM_ascii(LPSTR file,BOOL deleteifdestroyed)
{
	Delete();
	HANDLE hf;
	byte *data;
	DWORD size;
	unsigned long ul;
	int i,i2,i3;
	int n,x,y;
	char tmpstr[64];

	hf=CreateFile(file,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hf==INVALID_HANDLE_VALUE)return(FALSE);

	size=GetFileSize(hf,NULL);
	data=new byte[size];

	ReadFile(hf,(void*)data,size,&ul,NULL);

	CloseHandle(hf);

	n=0;
	for(i=0;n<2;)
	{
		if(data[i]==10)++n;
		++i;
	}

	//Format

	for(i2=0;;++i2)
	{
		if(data[i+i2]<48||data[i+i2]>57)break;
	}
	memcpy(tmpstr,&data[i],i2);
	tmpstr[i2]='\0';
	x=str2int(tmpstr);

	i2++;
	i2+=i;
	for(i3=0;;++i3)
	{
		if(data[i2+i3]<48||data[i2+i3]>57)break;
	}
	memcpy(tmpstr,&data[i2],i3);
	tmpstr[i3]='\0';
	y=str2int(tmpstr);


	//End Format
	for(;n<3;)
	{
		if(data[i]==10)++n;
		++i;
	}

	New(x*y,deleteifdestroyed);
	i2=0;
	for(;i<(int)size;++i)
	{
		if(data[i]!=10&&data[i]!=32)
		{
			if(data[i]=='1')
				SetBit(i2,TRUE);
			else
				SetBit(i2,FALSE);
			++i2;
		}
	}
	delete data;

	strcpy(pbmfile,file);

	return TRUE;

}

BOOL CBitBool::NewFromPBM_asciiInFile(HANDLE hfile,DWORD begin,DWORD size,BOOL deleteifdestroyed)
{
	Delete();
	byte *data;
	unsigned long ul;
	int i,i2,i3;
	int n,x,y;
	char tmpstr[64];

	SetFilePointer(hfile,begin,NULL,FILE_BEGIN);
	data=new byte[size];

	ReadFile(hfile,(void*)data,size,&ul,NULL);

	//CloseHandle(hf);

	n=0;
	for(i=0;n<2;)
	{
		if(data[i]==10)++n;
		++i;
	}

	//Format

	for(i2=0;;++i2)
	{
		if(data[i+i2]<48||data[i+i2]>57)break;
	}
	memcpy(tmpstr,&data[i],i2);
	tmpstr[i2]='\0';
	x=str2int(tmpstr);

	i2++;
	i2+=i;
	for(i3=0;;++i3)
	{
		if(data[i2+i3]<48||data[i2+i3]>57)break;
	}
	memcpy(tmpstr,&data[i2],i3);
	tmpstr[i3]='\0';
	y=str2int(tmpstr);


	//End Format
	for(;n<3;)
	{
		if(data[i]==10)++n;
		++i;
	}

	New(x*y,deleteifdestroyed);
	i2=0;
	for(;i<(int)size;++i)
	{
		if(data[i]!=10&&data[i]!=32)
		{
			if(data[i]=='1')
				SetBit(i2,TRUE);
			else
				SetBit(i2,FALSE);
			++i2;
		}
	}
	delete data;
	strcpy(pbmfile,"");
	return TRUE;

}

BOOL CBitBool::NewFromPBM_asciiRect(LPSTR file,RECT rect,BOOL deleteifdestroyed)
{
	Delete();
	HANDLE hf;
	//byte *data;
	DWORD size,filesize;
	unsigned long ul;
	int i,i2,i3;
	int n,x,y,cx,cy;
	char tmpstr[64];
	byte header[64];
	byte dbyte[2];
	CBitBool bb;

	bb.NewFromPBM_ascii(file,TRUE);

	cx=rect.right-rect.left;
	cy=rect.bottom-rect.top;

	y=rect.top;
	x=rect.left;

	i=0;

	New((UINT)(cx*cy),deleteifdestroyed);

	for(y=rect.top;y<rect.bottom;y++)
	{
		for(x=rect.left;x<rect.right;x++)
		{
			SetBit((UINT)i++,bb.GetBit((UINT)(cx*y+x)));
		}
	}
	strcpy(pbmfile,file);

	//size of data(bits)
/*	size=(rect.right-rect.left)*(rect.bottom-rect.top);


	hf=CreateFile(file,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hf==INVALID_HANDLE_VALUE)return(FALSE);

	filesize=GetFileSize(hf,NULL);
	//data=new byte[size];

	//Read header
	ReadFile(hf,(void*)header,64,&ul,NULL);
	SetFilePointer(hf,0,NULL,FILE_BEGIN);

	n=0;
	for(i=0;n<2;)
	{
		if(header[i]==10)++n;
		++i;
	}

	//Format

	for(i2=0;;++i2)
	{
		if(header[i+i2]<48||header[i+i2]>57)break;
	}
	memcpy(tmpstr,&header[i],i2);
	tmpstr[i2]='\0';
	x=str2int(tmpstr);

	i2++;
	i2+=i;
	for(i3=0;;++i3)
	{
		if(header[i2+i3]<48||header[i2+i3]>57)break;
	}
	memcpy(tmpstr,&header[i2],i3);
	tmpstr[i3]='\0';
	y=str2int(tmpstr);

	bb.New(x*y,TRUE);

	//End Format
	for(;n<3;)
	{
		if(header[i]==10)++n;
		++i;
	}

	//Start of data
	SetFilePointer(hf,i,NULL,FILE_BEGIN);

	i2=0;
	for(;i<(int)(rect.bottom-rect.top);++i)
	{
		//go left
		//ReadFile(hf,(void*)&dbyte,1,&ul,NULL);
		//if(dbyte[0]!='.')SetFilePointer(hf,-1,NULL,FILE_CURRENT);

		for(int i5=0;i5<(int)(rect.left);++i5)
		{
			do//next pixel
			{
				ReadFile(hf,(void*)&dbyte,1,&ul,NULL);
			}while(dbyte[0]!=0x20);
			ReadFile(hf,(void*)&dbyte,1,&ul,NULL);
			if(dbyte[0]!=10)SetFilePointer(hf,-1,NULL,FILE_CURRENT);
		}

		//Read line
		for(i3=0;i3<(int)(rect.right-rect.left);++i3)
		{
			ReadFile(hf,(void*)&dbyte,1,&ul,NULL);
			//if(dbyte[0]!='.')SetFilePointer(hf,-1,NULL,FILE_CURRENT);

			if(i2==430)
				i2=i2;
			if(dbyte[0]=='1')
				SetBit(i2,TRUE);
			else
				SetBit(i2,FALSE);

			do//next pixel
			{
				ReadFile(hf,(void*)&dbyte,1,&ul,NULL);
			}while(dbyte[0]!=0x20);
			ReadFile(hf,(void*)&dbyte,1,&ul,NULL);
			if(dbyte[0]!=10)
				SetFilePointer(hf,-1,NULL,FILE_CURRENT);
			else 
				i2=i2;
			++i2;
		}
		//go start o´next line
		//do
		//{
			for(int i4=0;i4<(int)(x-rect.right);++i4)
			{
			do//next pixel
			{
				ReadFile(hf,(void*)&dbyte,1,&ul,NULL);
			}while(dbyte[0]!=0x20);
			ReadFile(hf,(void*)&dbyte,1,&ul,NULL);
			if(dbyte[0]!=10)SetFilePointer(hf,-1,NULL,FILE_CURRENT);
			}

		//}while(dbyte[0]!='.');
	}
	
	//delete data;
	CloseHandle(hf);*/


	return TRUE;

}

BOOL CBitBool::New(UINT size,BOOL deleteifdestroyed)//size in bits
{
	Delete();
	UINT s;
	bitsize=size;
	s=size/8;
	if(size%8>0)s+=1;

	deldestroyed=deleteifdestroyed;
	bits=new BYTEBITARRAY[s];
	strcpy(pbmfile,"");
	if(bits)
	{
		bytesize=s;
		memset(bits,0,bytesize);
		return TRUE;
	}
	else 
	{
		bytesize=0;
		bitsize=0;
		return FALSE;
	}
}
/*
BOOL CBitBool::NewFromPBM(LPSTR binfile)
{
	Delete();
	HANDLE hf;
	byte *data;
	DWORD size;
	unsigned long ul;
	int i,i2,i3;
	int n,x,y;
	char tmpstr[64];

	hf=CreateFile(binfile,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hf==INVALID_HANDLE_VALUE)return(FALSE);

	size=GetFileSize(hf,NULL);
	data=new byte[size];

	ReadFile(hf,(void*)data,size,&ul,NULL);

	CloseHandle(hf);

	n=0;
	for(i=0;n<2;)
	{
		if(data[i]==10)++n;
		++i;
	}

	//Format

	for(i2=0;;++i2)
	{
		if(data[i+i2]<48||data[i+i2]>57)break;
	}
	memcpy(tmpstr,&data[i],i2);
	tmpstr[i2]='\0';
	x=str2int(tmpstr);

	i2++;
	i2+=i;
	for(i3=0;;++i3)
	{
		if(data[i2+i3]<48||data[i2+i3]>57)break;
	}
	memcpy(tmpstr,&data[i2],i3);
	tmpstr[i3]='\0';
	y=str2int(tmpstr);


	//End Format

	for(;n<3;)
	{
		if(data[i]==10)++n;
		++i;
	}

	New((UINT)(x*y));
	memcpy(bits,&data[i],bytesize);
	delete data;

	return TRUE;
}*/

void CBitBool::Delete()
{
	if(bits)
		delete bits;
	bits=NULL;
	bytesize=0;
	strcpy(pbmfile,"");

}

BOOL CBitBool::GetBit(UINT bitpos)
{
	if(!bits)return FALSE;

	UINT bytepos;
	bytepos=(UINT)(bitpos/8);
	bitpos=bitpos%8;

	if(bytepos>=bytesize)return FALSE;

	switch(bitpos)
	{
	case 0:
		return bits[bytepos].b0;
		break;
	case 1:
		return bits[bytepos].b1;
		break;
	case 2:
		return bits[bytepos].b2;
		break;
	case 3:
		return bits[bytepos].b3;
		break;
	case 4:
		return bits[bytepos].b4;
		break;
	case 5:
		return bits[bytepos].b5;
		break;
	case 6:
		return bits[bytepos].b6;
		break;
	case 7:
		return bits[bytepos].b7;
		break;
	}
	return FALSE;
}

BOOL CBitBool::GetBit(UINT bytepos,UINT bitpos)
{
	if(!bits)return FALSE;
	if(bytepos>=bytesize)return FALSE;

	switch(bitpos)
	{
	case 0:
		return bits[bytepos].b0;
		break;
	case 1:
		return bits[bytepos].b1;
		break;
	case 2:
		return bits[bytepos].b2;
		break;
	case 3:
		return bits[bytepos].b3;
		break;
	case 4:
		return bits[bytepos].b4;
		break;
	case 5:
		return bits[bytepos].b5;
		break;
	case 6:
		return bits[bytepos].b6;
		break;
	case 7:
		return bits[bytepos].b7;
		break;
	}
	return FALSE;

}

BOOL CBitBool::SetBit(UINT bitpos,BOOL b)
{
	if(!bits)return FALSE;
	UINT bytepos;
	bytepos=(UINT)(bitpos/8);
	bitpos=bitpos%8;
	if(bytepos>=bytesize)return FALSE;

	switch(bitpos)
	{
	case 0:
		bits[bytepos].b0=b;
		break;
	case 1:
		bits[bytepos].b1=b;
		break;
	case 2:
		bits[bytepos].b2=b;
		break;
	case 3:
		bits[bytepos].b3=b;
		break;
	case 4:
		bits[bytepos].b4=b;
		break;
	case 5:
		bits[bytepos].b5=b;
		break;
	case 6:
		bits[bytepos].b6=b;
		break;
	case 7:
		bits[bytepos].b7=b;
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;
}

BOOL CBitBool::SetBit(UINT bytepos,UINT bitpos,BOOL b)
{
	if(!bits)return FALSE;
	if(bytepos>=bytesize)return FALSE;

	switch(bitpos)
	{
	case 0:
		bits[bytepos].b0=b;
		break;
	case 1:
		bits[bytepos].b1=b;
		break;
	case 2:
		bits[bytepos].b2=b;
		break;
	case 3:
		bits[bytepos].b3=b;
		break;
	case 4:
		bits[bytepos].b4=b;
		break;
	case 5:
		bits[bytepos].b5=b;
		break;
	case 6:
		bits[bytepos].b6=b;
		break;
	case 7:
		bits[bytepos].b7=b;
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;

}

BOOL CBitBool::LoadPBM_sw_ascii(byte *b,LPSTR file)
{
	unsigned long ul;
	int i,i2,n;
	HANDLE hf;
	int size;
	char *data;

	hf=CreateFile(file,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hf==INVALID_HANDLE_VALUE)return(FALSE);

	size=GetFileSize(hf,NULL);

	data=new char[size];
	ReadFile(hf,(void*)data,size,&ul,NULL);

	CloseHandle(hf);

	n=0;
	for(i=0;n<3;)
	{
		if(data[i]==10)++n;
		++i;
	}

	i2=0;
	for(;i<size;++i)
	{
		if(data[i]!=10&&data[i]!=32)
		{
			if(data[i]=='1')
				b[i2]=!TRUE;
			else b[i2]=!FALSE;
			++i2;
		}
	}
	delete data;

	return TRUE;
}

POINT CBitBool::GetPBMSize(LPSTR file)
{
	HANDLE hf;
	//byte *data;
	DWORD size,filesize;
	unsigned long ul;
	int i,i2,i3;
	int n,x,y,cx,cy;
	char tmpstr[64];
	byte header[64];
	byte dbyte[2];
	CBitBool bb;
	POINT ret;

	hf=CreateFile(file,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hf==INVALID_HANDLE_VALUE)
	{
		ret.x=0;
		ret.y=0;
		return(ret);
	}

	filesize=GetFileSize(hf,NULL);
	//data=new byte[size];

	//Read header
	ReadFile(hf,(void*)header,64,&ul,NULL);
	SetFilePointer(hf,0,NULL,FILE_BEGIN);

	CloseHandle(hf);
	n=0;
	for(i=0;n<2;)
	{
		if(header[i]==10)++n;
		++i;
	}

	//Format

	for(i2=0;;++i2)
	{
		if(header[i+i2]<48||header[i+i2]>57)break;
	}
	memcpy(tmpstr,&header[i],i2);
	tmpstr[i2]='\0';
	x=str2int(tmpstr);

	i2++;
	i2+=i;
	for(i3=0;;++i3)
	{
		if(header[i2+i3]<48||header[i2+i3]>57)break;
	}
	memcpy(tmpstr,&header[i2],i3);
	tmpstr[i3]='\0';
	y=str2int(tmpstr);

	ret.x=x;
	ret.y=y;
	return ret;
}

BOOL CBitBool::NewFromBMP(LPSTR file,HDC hdc,BOOL deletedestroyed)
{
	HBITMAP hbm;
	BITMAP bm;
	HDC hdc2;

	hbm=(HBITMAP)LoadImage(NULL,file,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(!hbm)return FALSE;
	
	GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap

	New((UINT)(bm.bmWidth*bm.bmHeight),deletedestroyed);

	hdc2 = CreateCompatibleDC(hdc);
	if(!hdc2)
	{
		DeleteObject(hbm);
		return FALSE;
	}
	
	SelectObject(hdc2, hbm);

	int x,y,i=0;
	COLORREF black,white,c,falsecolor;
	black=RGB(0,0,0);
	white=RGB(255,255,255);
	falsecolor=GetPixel(hdc2,0,0);

	for(y=0;y<bm.bmHeight;++y)
	{
		for(x=0;x<bm.bmWidth;++x)
		{
			c=GetPixel(hdc2,x,y);
			if(c!=falsecolor)
				SetBit((UINT)i++,TRUE);
			else
				SetBit((UINT)i++,FALSE);
			
		}
	}

	DeleteDC(hdc2);
	DeleteObject(hbm);

	return TRUE;

}

BOOL CBitBool::NewFromBMPRect(HBITMAP hbm,HDC hdc,RECT rect,BOOL deletedestroyed)
{
	BITMAP bm;
	HDC hdc2;
	int w,h;

	if(!hbm)return FALSE;
	
	GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap

	w=rect.right-rect.left;
	h=rect.bottom-rect.top;

	New((UINT)(w*h),deletedestroyed);

	hdc2 = CreateCompatibleDC(hdc);
	if(!hdc2)
		return FALSE;
	
	SelectObject(hdc2, hbm);

	int x,y,i=0;
	COLORREF black,white,c,falsecolor;
	black=RGB(0,0,0);
	white=RGB(255,255,255);
	falsecolor=GetPixel(hdc2,0,0);

	for(y=rect.top;y<rect.bottom;++y)
	{
		for(x=rect.left;x<rect.right;++x)
		{
			c=GetPixel(hdc2,x,y);
			if(c!=falsecolor)
				SetBit((UINT)i++,TRUE);
			else
				SetBit((UINT)i++,FALSE);
			
		}
	}

	DeleteDC(hdc2);

	return TRUE;

}

BOOL CBitBool::LoadPBM_sw_asciiInFile(byte *b,HANDLE hfile,DWORD begin,DWORD size)
{
	unsigned long ul;
	int i,i2,n;
	//HANDLE hf;
	char *data;

	SetFilePointer(hfile,begin,NULL,FILE_BEGIN);

	data=new char[size];
	ReadFile(hfile,(void*)data,size,&ul,NULL);

	//CloseHandle(hf);

	n=0;
	for(i=0;n<3;)
	{
		if(data[i]==10)++n;
		++i;
	}

	i2=0;
	for(;i<(int)size;++i)
	{
		if(data[i]!=10&&data[i]!=32)
		{
			if(data[i]=='1')
				b[i2]=!TRUE;
			else b[i2]=!FALSE;
			++i2;
		}
	}
	delete data;

	return TRUE;
}