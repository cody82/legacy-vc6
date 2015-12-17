
// MD2 View

// Written by William Chin
// Developed in MSDEV C++ v6.0 using the DirectX 7.0a SDK
// Date : 16th May 2000
// File : ImportMD2.cpp

// Website: http://members.aol.com/billybop7
// Email:  billybop7@aol.com 



#include "iostream.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <math.h>
#include <windows.h>
#include "d3dtextr.h"
#include "debug.hpp"
#include "ImportMD2.hpp"

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

// for debuging the RenderMD2 function
bool RenderingMd2ModelForFirstTime = true;

D3DVERTEX src_v[10000];

// pointer to the CMD2 class
CMD2* pCMD2 = NULL;


CMD2::CMD2()
{
	// set the pointer to the CMD2 class
	pCMD2 = this;
}

// Load in a MD2 model from file, read all the model data, and put it
// into the model object.
BOOL CMD2::LoadMD2Model( MD2MODEL *model, char *filename )
{
	FILE *fp = NULL;
	MD2HEADER header;
	MD2BYTE_VERTEX bverts;
	float bscale[3];		
	float translate[3]; 
	char name[16];		
	int v;
	int frame_num;
	int N;
	int id;
	int findex;
	int num_indices_per_primitive;	
	int cnt = 0;
	int prim_cnt = 0;
	int num_glcmds = 0;
	int num_indices = 0;
	float fs, ft;
	float scale = 0.5f;
	int i;
	char filename_minus_ext[256];
	char filename_with_bmp_ext[256];
	

	fp = fopen(filename,"rb");

	if(fp == NULL)
	{
		PrintMessage("CMD2::LoadMD2Model - Can't find model : ", filename);
		return FALSE;
	}
	else
		PrintMessage("CMD2::LoadMD2Model - Loading : ", filename);
	

	// read file header into MD2HEADER structure
	fread(&header, sizeof(MD2HEADER), 1, fp); 



    // QUICK CHECK TO GET the number of GLCMDS in model

	// move file pointer to the start of the GL command list
	fseek(fp, (UINT)header.offset_glcmds, SEEK_SET);
	
	// if there are no GL commands here quit
	if(header.offset_end == header.offset_glcmds)
	{
		fclose(fp);
		return FALSE;
	}

	id = 1;
	num_glcmds = 0;
	num_indices = 0;

	while( id != 0 )	
	{
		// read in primitive commands from md2 file
		fread(&id,sizeof(int),1,fp);
		
		// id = 0 indicates the end of the command list
		if(id != 0)
		{
			num_indices_per_primitive = abs(id);

			for(findex = 0; findex < num_indices_per_primitive; findex++)
			{
				fread(&fs,sizeof(float),1,fp);
				fread(&ft,sizeof(float),1,fp);
				fread(&N,sizeof(int),1,fp);

				num_indices++;
			} 
			num_glcmds++;
		}

	} // end while


	// LOAD FACE AND TEXTURE CO_ORDINATES
	
	// the GL command format:
	// a positive integer for the "id" variable starts a tristrip command, 
	// followed by that many vertex structures.
	// a negative integer foir "id" starts a trifan command, followed 
	// by -x vertexes a zero indicates the end of the command list.
	// a vertex consists of a floating point s, a floating point t,
	// and an integer vertex index.


	// move file pointer to the start of the GL command list
	fseek(fp, (UINT)header.offset_glcmds, SEEK_SET);
	
	// if there are no GL commands here quit
	if(header.offset_end == header.offset_glcmds)
	{
		fclose(fp);
		return FALSE;
	}
		
	model->NumPrimitives = num_glcmds;
	model->Primitives = new MD2OBJECT[num_glcmds];


	id = 1;
	num_indices = 0;
	prim_cnt = 0;

	while( id != 0 )	
	{
		// read in primitive commands from md2 file
		fread(&id,sizeof(int),1,fp);
		
		// id = 0 indicates the end of the command list
		if(id != 0)
		{
			num_indices_per_primitive = abs(id);

			if(id < 0 )
				model->Primitives[prim_cnt].PrimitiveType = MD2_TRIANGLEFAN;

			if(id > 0 )
				model->Primitives[prim_cnt].PrimitiveType = MD2_TRIANGLESTRIP;
		
			
			model->Primitives[prim_cnt].FaceIndices = new MD2FACEINDEX[num_indices_per_primitive];
			model->Primitives[prim_cnt].NumFaceIndices = num_indices_per_primitive;

			for(findex = 0; findex < num_indices_per_primitive; findex++)
			{
				// read texture co-ordinates s and t
				fread(&fs,sizeof(float),1,fp);
				model->Primitives[prim_cnt].FaceIndices[findex].s = fs;

				fread(&ft,sizeof(float),1,fp);
				model->Primitives[prim_cnt].FaceIndices[findex].t = ft;

				// read face index
				fread(&N,sizeof(int),1,fp);
				model->Primitives[prim_cnt].FaceIndices[findex].index = N;

				num_indices++;

			} // end for findex
		
			prim_cnt++;
		
		} // end if

	} // end while
	model->NumIndices = num_indices;


	// LOAD VERTS FOR EACH FRAME OF ANIMATION

	model->Frames = new MD2FRAME[header.num_frames];
	model->NumFrames = header.num_frames;

	model->NumVerts = header.num_verts;

	// read vertices for all frames

	fseek(fp, (UINT)header.offset_frames, SEEK_SET);

	for(frame_num = 0; frame_num < header.num_frames; frame_num++)
	{
		fread(bscale,sizeof(float),3,fp);		
		fread(translate,sizeof(float),3,fp);
		fread(name,1,16,fp);				
		
		if(strlen(name) <= 16)
			strcpy(model->Frames[frame_num].framename, name );
	
		model->Frames[frame_num].Verts = new MD2VERT[header.num_verts];


		for(v = 0; v < header.num_verts; v++) // VERTS
		{
			fread(&bverts,sizeof(MD2BYTE_VERTEX),1,fp); 

			model->Frames[frame_num].Verts[v].x = scale * (bscale[0] * bverts.v[0] + translate[0]);
			model->Frames[frame_num].Verts[v].y = scale * (bscale[1] * bverts.v[1] + translate[1]);
			model->Frames[frame_num].Verts[v].z = scale * (bscale[2] * bverts.v[2] + translate[2]);
		}
	}

	// Change the file extension  and look
	// for a bitmap with the same name as the model's name
	filename_minus_ext[0] = 0;
	filename_with_bmp_ext[0] = 0;

	strcpy(filename_minus_ext, filename);

	for(i = 0; i < 256; i++)
	{
		if(filename_minus_ext[i] == 46) // 46 = full stop character
		{
			// mark the end of the string with 0
			filename_minus_ext[i] = 0;

			// add .bmp extension
			strcpy(filename_with_bmp_ext, filename_minus_ext);
			strcat(filename_with_bmp_ext, ".bmp");
			break;
		}
	}

	// copy bmp skin name into model
	strcpy(model->SkinName, filename_with_bmp_ext);
	
	// Load the skin
	if( D3DTextr_CreateTextureFromFile(filename_with_bmp_ext) != S_OK )
		PrintMessage("Couldn't find texture : ", filename_with_bmp_ext);
	else
		PrintMessage("CMD2::LoadMD2Model - loaded ", filename_with_bmp_ext);

	fclose(fp);
	return TRUE;
}


void CMD2::ReleaseMD2Model( MD2MODEL *model )
{
	int i;

	for(i = 0; i < model->NumFrames; i++)
		SAFE_DELETE_ARRAY(model->Frames[i].Verts);

	SAFE_DELETE_ARRAY(model->Frames);

	for(i = 0; i < model->NumPrimitives; i++)
		SAFE_DELETE_ARRAY(model->Primitives[i].FaceIndices);

	SAFE_DELETE_ARRAY(model->Primitives);
}

BOOL CMD2::RenderMD2Model( LPDIRECT3DDEVICE7 m_pd3dDevice, 
						   float wx, float wy, float wz, 
						   float rotation_angle,
						   MD2MODEL *model )
{
	FILE *fp_log = NULL;
	int prim_cnt;
	int num_prims;
	int num_indices;
	int index_cnt;
	int num_tex_indices;
	int PrimitiveType;
	int index;
	int num_verts;
	int v;
	int num_verts_per_poly;
	int frame_num;
	float x,y,z;
	float tex_coord_s;
	float tex_coord_t;
	D3DPRIMITIVETYPE D3dPrimType;
	LPDIRECTDRAWSURFACE7 current_texture;
	float sine, cosine;
	float convert_degrees_to_radians = 0.017453292f; // (2 * PI) / 360 = 0.017453292

	// work out the cosine and sine of the rotation angle about the y axis
	// in advance to speed things up a little in the rendering loop.
	sine   = sinf(rotation_angle * convert_degrees_to_radians);
	cosine = cosf(rotation_angle * convert_degrees_to_radians);


	frame_num = model->CurrentFrame;

	// note polys refers to primitives in this context

	// create a file called "md2logfile.txt" for writing debug info to,
	// but only for the first time the RenderMD2Model function 
	// is called 
	if(RenderingMd2ModelForFirstTime == true)
		fp_log = fopen("md2render.txt","w");

	// if we can't open this file bug out
	if(RenderingMd2ModelForFirstTime == true)
	{
		if(fp_log == NULL)
		{
			RenderingMd2ModelForFirstTime = false;
			return FALSE;
		}
	}


	// FACE INDICES AND TEXTURE CO_ORDINATES
	// these are deal with one polygon at a time.
	// each poly has an associated number of indices and 
	// texture co-ordinates.

	// get the total number of primitives (polys) to be rendered
	num_prims = model->NumPrimitives;

	// printout number of polys to logfile
	if(RenderingMd2ModelForFirstTime == true)
	{
		fprintf( fp_log, "num_prims in model= %d\n\n", num_prims);
		fprintf( fp_log, "FACE INDEXES and TEXTURE CO_ORDINATES\n\n");
	}
			
	
	// go through the list of polys one by one and render then
	for(prim_cnt = 0; prim_cnt < num_prims; prim_cnt++)
	{
		// get the number of indices (indexes) for this poly
		num_indices = model->Primitives[prim_cnt].NumFaceIndices;

		// number of texture co-ordinates is the same as the number of indices
		num_tex_indices = num_indices;

		// get the Id value for the current prim
		PrimitiveType = model->Primitives[prim_cnt].PrimitiveType;

		// Is the current poly a TRIANGLEFAN (list of triangles in a circle 
		// that share a commom vert in the centre of the circle).
		
		if( PrimitiveType == MD2_TRIANGLEFAN)
		{
			D3dPrimType = D3DPT_TRIANGLEFAN;
			// make a note of this in the logfile
			if(RenderingMd2ModelForFirstTime == true)
			{
				fprintf( fp_log, "prim_cnt = %d, PrimitiveType = MD2_TRIANGLEFAN, num indices = %d, num texture co-ordinates = %d\n",  
					     prim_cnt, num_indices, num_tex_indices);
			}
		}

		// Is the current poly a TRIANGLESTRIP (list of triangles usually in a strip
		// or box shape that are connected together and share common two verts
		// along the joining line beween triangles.
		// triangle strips are composed of at least two triangle or more.
		// you need three vertices to define the first trianlge in the strip
		// then a further one vertex per additional triangle.

		if( PrimitiveType == MD2_TRIANGLESTRIP)
		{
			D3dPrimType = D3DPT_TRIANGLESTRIP;

			// make a note of this in the logfile
			if(RenderingMd2ModelForFirstTime == true)
			{
				fprintf( fp_log, "prim_cnt = %d, PrimitiveType = MD2_TRIANGLESTRIP, num indices = %d, num texture co-ordinates = %d\n",  
					     prim_cnt, num_indices, num_tex_indices);
			}
		}

		// go through all the indices, and texture co-ordinates for this poly
		for(index_cnt = 0; index_cnt < num_indices; index_cnt++)
		{
			index = model->Primitives[prim_cnt].FaceIndices[index_cnt].index;

			tex_coord_s = model->Primitives[prim_cnt].FaceIndices[index_cnt].s;
			tex_coord_t = model->Primitives[prim_cnt].FaceIndices[index_cnt].t;

			// Note : swap Y and Z co-ordinates because MD2 models have 
			// the Z axis as the up axis, and we use the Y axis as up in this sample.
			x = model->Frames[frame_num].Verts[index].x;
			z = model->Frames[frame_num].Verts[index].y;
			y = model->Frames[frame_num].Verts[index].z;

			src_v[index_cnt].x  = wx + (x*cosine - z*sine); 
			src_v[index_cnt].y  = wy + y;
			src_v[index_cnt].z  = wz + (x*sine + z*cosine);
			src_v[index_cnt].tu = tex_coord_s;
			src_v[index_cnt].tv = tex_coord_t;

			if(RenderingMd2ModelForFirstTime == true)
			{
				fprintf( fp_log, "X = %f, Y = %f, Z = %f\n"
						,x, y, z);

				fprintf( fp_log, "tex_coord_s = %f, tex_coord_t = %f, index = %d\n"
						,src_v[index_cnt].tu, src_v[index_cnt].tv, index);
			}
		}

		num_verts_per_poly = num_indices;

		current_texture = D3DTextr_GetSurface( model->SkinName );
		m_pd3dDevice->SetTexture( 0, current_texture );

		if (m_pd3dDevice->DrawPrimitive(D3dPrimType, 
										D3DFVF_VERTEX, 
										(LPVOID)&src_v, 
										(DWORD)num_verts_per_poly, 
										NULL) != D3D_OK) 
		{
			PrintMessage("CMD2::RenderMD2Model - DrawPrimitive FAILED", NULL);	
			PrintMessage(ITOA(prim_cnt), NULL);	
			return FALSE;
		}

		// new line in logfile
		if(RenderingMd2ModelForFirstTime == true)
			fprintf( fp_log, "\n");
	}


	// VERTEX LIST AND ANIMATION

	// were only going to deal with the first frame of animation data
	// to start with. We'll deal with the animation at a later date.
	//frame_num = 0; 

	// get the number of verts. Note every frame has the same number 
	// of verts in it.
	num_verts = model->NumVerts;

	// printout number of verts and the frame name to logfile
	if(RenderingMd2ModelForFirstTime == true)
	{
		fprintf( fp_log, "\nVERTS LIST\n\n");
		fprintf( fp_log, "num_verts in frame = %d\n\n", num_verts);

		fprintf( fp_log, "frame_num = %d, framename = %s\n\n"
				,frame_num, model->Frames[frame_num].framename);
	}

	// loop through all the verts for this frame
	for(v = 0; v < num_verts; v++) // VERTS
	{
		x = model->Frames[frame_num].Verts[v].x;
		y = model->Frames[frame_num].Verts[v].y;
		z = model->Frames[frame_num].Verts[v].z;

		if(RenderingMd2ModelForFirstTime == true)
			fprintf( fp_log, "vert %d,   x = %f, y = %f, z = %f\n" ,v, x, y, z );
	}

	// close thise log file
	if(RenderingMd2ModelForFirstTime == true)
	{
		fprintf( fp_log, "\n\nEnd of file\n" );
		fclose(fp_log);
	}

	// make sure info isn't writen to the md2logfile 
	// after the pass through this fucntion
	RenderingMd2ModelForFirstTime = false;
	return true;
}