#include "3dobject.h"

C3DObject::C3DObject()
{
	lpVertexes=NULL;
	nVertexes=0;
	pNext=NULL;
	//Material=NULL;

	vRotSpeed.x=0;
	vRotSpeed.y=0;
	vRotSpeed.z=0;

	vRot.x=0;
	vRot.y=0;
	vRot.z=0;
}

C3DObject::~C3DObject()
{
	if(lpVertexes)delete lpVertexes;
	lpVertexes=NULL;
	nVertexes=0;
}

void C3DObject::Draw(LPDIRECT3DDEVICE2 device)
{
	int i;
	VERTEX *vertexes;

	//device->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, Texture.GetHandle());
	//e->Device->SetLightState(D3DLIGHTSTATE_MATERIAL,Material);

	vertexes=new VERTEX[nVertexes];
	
	for(i=0;i<nVertexes;++i)vertexes[i]=lpVertexes[i];
	
	//memcpy(vertexes,lpVertexes,sizeof(VERTEX)*nVertexes);
	for(i = 0; i < nVertexes; i++)
	{
		vertexes[i].RotateX(vRot.x);
		vertexes[i].RotateY(vRot.y);
		vertexes[i].RotateZ(vRot.z);
	}

	
	for(i = 0; i < nTriangles; i++)
	{
		D3DLVERTEX v[3];
		//D3DLVERTEX vt;
		int *tri;
		tri=&Triangles[i*3];

		int i2;
		for(i2=0;i2<3;++i2)
			v[i2]=vertexes[tri[i2]];
					
		device->DrawPrimitive(D3DPT_TRIANGLELIST, D3DVT_LVERTEX, v, 3, D3DDP_WAIT);

		//vt=v[0];
		//v[0]=v[2];
		//v[2]=vt;

		//device->DrawPrimitive(D3DPT_TRIANGLELIST, D3DVT_LVERTEX, v, 3, D3DDP_WAIT);
	}
/*	HDC hdc;
	char tmpstr[64];
	e->BackBuffer->GetDC(&hdc);
	sprintf(tmpstr,"%f",vRot.y);
	SetBkMode(hdc,TRANSPARENT);
	SetTextColor(hdc,RGB(255,255,255));
	TextOut(hdc,0,30,tmpstr,strlen(tmpstr));
	e->BackBuffer->ReleaseDC(hdc);*/

	delete vertexes;

}

void C3DObject::Update(DWORD dTime)
{
	int i;
//	for(i = 0; i < nVertexes; i++)
//	{
	vRot.x+=vRotSpeed.x*(float)dTime/1000;
	vRot.y+=vRotSpeed.y*(float)dTime/1000;
	vRot.z+=vRotSpeed.z*(float)dTime/1000;
//	}

	while(vRot.x>=360)vRot.x-=360;
	while(vRot.x<0)vRot.x+=360;

	while(vRot.y>=360)vRot.y-=360;
	while(vRot.y<0)vRot.y+=360;

	while(vRot.z>=360)vRot.z-=360;
	while(vRot.z<0)vRot.z+=360;
/*
	for(i = 0; i < nVertexes; i++)
	{
		lpVertexes[i].RotateX(vRotSpeed.x*(float)dTime/1000);
		lpVertexes[i].RotateY(vRotSpeed.y*(float)dTime/1000);
		lpVertexes[i].RotateZ(vRotSpeed.z*(float)dTime/1000);
	}
*/
}

