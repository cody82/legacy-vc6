//-----------------------------------------------------------------------------
//
// File: Sprite3D.h			Date: 03/04/1999	for DirectX 6.0 / 6.1
//
// Copyright (C) 1999 by Tobias M. Lensing - All rights reserved
//
// Note: This is free software. Permission to copy, modify and distribute this
//       code freely for non-commercial and commercial purposes is hereby
//       granted as long as the above copyright note is included with the
//       product. Reselling this source code is strictly forbidden!
//
//       This application may be used under the terms of the GNU Library
//       General Public License which is included to the project package.
//
// This is the header file of the Sprite3D module which manages the Direct3D
// Immediate Mode stuff for Enhanced2D. In this file the Sprite3D class is
// implemented. This file must be included with the Sprite3D module.
//
//-----------------------------------------------------------------------------

#ifndef _SPRITE3D_H_
#define _SPRITE3D_H_

#define D3D_OVERLOADS
#define STRICT
//#include "D3DFrame.h"
#include "D3DTextr.h"

#define NUM_SPRITECOORDS 4

class Sprite3D
{
public:
	// Constructors and Destructors
	Sprite3D();
	~Sprite3D();

	// Element Functions
	void CreateSprite( char* strTexName, D3DCOLOR color, D3DCOLOR specular,
					   int x1, int y1, int x2, int y2,
					   float tu1, float tv1, float tu2, float tv2 );
	void CreateSprite( char* strTexName, D3DTLVERTEX* vVertices );
	void RenderSprite( LPDIRECT3DDEVICE3 pd3dDevice );
	void RefreshVertices();
	void RefreshPosition();

	D3DTLVERTEX* GetVertices();
	char*        GetTexFilename();
	D3DCOLOR     GetColor();
	D3DCOLOR     GetSpecular();
	void		 GetCoordinates( int& x1, int& y1, int& x2, int& y2 );

	void SetVertices( D3DTLVERTEX* vVertices );
	void SetTexFilename( char* strTexFilename );
	void SetColors( D3DCOLOR color, D3DCOLOR specular );
	void SetPosition( int x1, int y1, int x2, int y2 );
	void SetTextureCoords( float tu1, float tv1, float tu2, float tv2 );
	void SetVertexColor( int nNumVertex, D3DCOLOR color, D3DCOLOR specular );
	void Move( int x, int y );

protected:
	int m_nX1, m_nY1, m_nX2, m_nY2;			// screen coordinates used to generate sprites
	float m_fTU1, m_fTV1, m_fTU2, m_fTV2;	// texture coordinates for the sprite
	char* m_strTexFilename;					// the texture's filename
	D3DCOLOR m_cColor, m_cSpecular;			// light parameters of ALL vertices
	D3DTLVERTEX m_vSpriteVertices[4];		// the sprite's vertices for Direct3D rendering
};


#endif // _SPRITE3D_H_