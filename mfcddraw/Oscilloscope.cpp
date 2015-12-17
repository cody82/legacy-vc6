#include "stdafx.h"
#include "Oscilloscope.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

COscilloscope::COscilloscope()
{
	fCoords=fReflectCoords=NULL;
	fSpeed=800;
	lpGenerator=new CWaveGenerator;
	bReflect=FALSE;
	bFixedEnd=TRUE;
	((CWaveGenerator*)lpGenerator)->fFrequence=5;
}

COscilloscope::~COscilloscope()
{
	delete lpGenerator;
	delete[] fCoords;
	delete[] fReflectCoords;
}

BEGIN_MESSAGE_MAP(COscilloscope,CDDrawWnd)
	//{{AFX_MSG_MAP(CDDrawWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID COscilloscope::Draw(CGenerator *gen,float from,float to)
{
	RECT r;
	int i,m;
	CDC *dc;
	CPen pen;

	GetWindowRect(&r);
	
	m=(r.bottom-r.top)/2;
	dc=GetDDrawDC();

	pen.CreatePen(PS_SOLID,1,RGB(255,255,255));
	dc->SelectObject(&pen);

	dc->MoveTo(0,m+(int)gen->Function(from));

	for(i=1;i<r.right-r.left;++i)
	{
		dc->LineTo(i,m+(int)gen->Function( from + ((float)i/((float)r.right-(float)r.left)) * (to-from) ));
	}

	ReleaseDDrawDC();
}
	
VOID COscilloscope::DrawCoords()
{
	CDC *dc;
	CPen pen;
	POINT start;
	RECT r;
	int i,m;
	DWORD dw;

	GetWindowRect(&r);
	m=(r.bottom-r.top)/2;

	dc=GetDDrawDC();

	if(!dc)return;

	pen.CreatePen(PS_SOLID,1,RGB(255,255,255));
	dc->SelectObject(&pen);

	dc->MoveTo(0,(int)(m+fCoords[0]+fReflectCoords[0]));
	for(i=1;i<(int)dwCoordCount;++i)
	{
		dc->LineTo(i,m+fCoords[i]+fReflectCoords[i]);
	}

	ReleaseDDrawDC();
}

void COscilloscope::OnPaint() 
{
	CPaintDC dc(this);

	DrawCoords();

	Flip();

}

VOID COscilloscope::Update(float dTime)
{
	POSITION p;
	DWORD dw,dw2;
	static float shift=0;
	float f;

	dw2=(DWORD)(fSpeed*dTime+shift);
	f=(fSpeed*dTime+shift)-(float)dw2;
	shift=f;
	if(dw2==0)return;

	f=0;
	float f2=dTime/(float)dw2;

	for(dw=0;dw<dw2;++dw)
	{
		lpGenerator->Update(f2);
		f=lpGenerator->GetValue();
		Shift();
		fCoords[0]=f;
	}

	Clear();
	DrawCoords();
	Flip();
}

VOID COscilloscope::Shift()
{
	DWORD dw,dw2,dw3;
	float f;

	f=fCoords[dwCoordCount-1];
	if(bFixedEnd)f*=-1;
		
	memmove(&fCoords[1],fCoords,sizeof(float)*(dwCoordCount-1));
		
	fCoords[0]=0;
	fReflectCoords[dwCoordCount-1]=bReflect?f:0;
		
	memmove(fReflectCoords,&fReflectCoords[1],sizeof(float)*(dwCoordCount-1));

}

VOID COscilloscope::CreateCoords(DWORD count)
{
	if(fCoords)delete[] fCoords;
	if(fReflectCoords)delete[] fReflectCoords;

	fCoords=new float[count];
	fReflectCoords=new float[count];

	dwCoordCount=count;

	memset(fCoords,0,sizeof(float)*count);
	memset(fReflectCoords,0,sizeof(float)*count);

}

void COscilloscope::OnSize(UINT nType, int cx, int cy) 
{
	CDDrawWnd::OnSize(nType,cx,cy);

	CreateCoords((DWORD)cx);
}
