#ifndef __C3DOBJECT_H
#define __C3DOBJECT_H

class C3DObject;

#include "3dengine.h"

class C3DObject
{
public:
	C3DObject();
	~C3DObject();

	void Draw(LPDIRECT3DDEVICE2 device);
	void Update(DWORD dTime);

	VERTEX *lpVertexes;
	int nVertexes;
	int *Triangles;
	int nTriangles;

	VECTOR3D vRot;
	VECTOR3D vRotSpeed;

	//TEXTURE Texture;

	//D3DMATERIALHANDLE Material;

	//List
	C3DObject *pNext;

	C3DEngine *e;
};

#endif