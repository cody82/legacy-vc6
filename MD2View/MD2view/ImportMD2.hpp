
// MD2 View

// Written by William Chin
// Developed in MSDEV C++ v6.0 using the DirectX 7.0a SDK
// Date : 16th May 2000
// File : ImportMD2.hpp

// Website: http://members.aol.com/billybop7
// Email:  billybop7@aol.com 

 
#ifndef IMPORTMD2_HPP
#define IMPORTMD2_HPP

#include <windows.h>
#include "D3DApp.h"


#define MAX_SKINNAME 64
#define MAX_NUM_SKINS 64

#define MD2_TRIANGLEFAN 1
#define MD2_TRIANGLESTRIP 2

// MD2 File Header structure
typedef struct
{
	int ident;
	int version;

	int skinwidth;
	int skinheight;
	int framesize;	

	int num_skins;
	int num_verts;
	int num_tex_verts;	
	int num_faces;
	int num_glcmds; 
	int num_frames;

	int offset_skins;	
	int offset_tex_verts;		
	int offset_faces;	
	int offset_frames; 
	int offset_glcmds; 
	int offset_end;	

} MD2HEADER;


typedef struct
{
	float x;
	float y;
	float z;

} MD2VERT;


typedef struct
{
	float s;
	float t;
	int   index;
} MD2FACEINDEX; // GLVERTS


typedef struct
{
	BYTE v[3]; 
	BYTE lightnormalindex;

} MD2BYTE_VERTEX; 


typedef struct
{				
	char framename[16];		
	MD2VERT *Verts;

} MD2FRAME;

typedef struct
{			
	int PrimitiveType;
	MD2FACEINDEX *FaceIndices;
	int NumFaceIndices;

} MD2OBJECT;


typedef struct
{		
	MD2FRAME  *Frames;
	MD2OBJECT *Primitives;
	int NumPrimitives;
	int NumFrames;
	int NumVerts;
	int NumIndices;
	int CurrentFrame;
	float skx;
	float sky;

	char SkinName[256];	//16
	
} MD2MODEL;


class CMD2
{
	
public:

	CMD2();

	BOOL LoadMD2Model( MD2MODEL *model, char *filename );
	BOOL RenderMD2Model( LPDIRECT3DDEVICE7 m_pd3dDevice, 
						   float wx, float wy, float wz, 
						   float rotation_angle,
						   MD2MODEL *model );
	void ReleaseMD2Model( MD2MODEL *model );

};

#endif // IMPORTMD2_HPP