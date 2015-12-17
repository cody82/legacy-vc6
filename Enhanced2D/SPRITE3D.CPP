//-----------------------------------------------------------------------------
//
// File: Sprite3D.cpp		Date: 03/08/1999	for DirectX 6.0 / 6.1
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
// This is the Sprite3D module. This module contains functions for the Sprit3D
// class which will manage the Sprite for rendering 3D on 2D.
//
// Notes:
// The Sprite3D class can be used with any DirectDraw or Direct3D program. You
// just need to include the Direct3D Framework helper library and modify it for
// your own purposes. The Sprite3D class disables the ZBuffer and writes itself
// over any other 3D or 2D stuff in your scene.
//
// If you are using this class for drawing sprites with alphablending please
// note that you should render the object which is most in front of you at
// last! Otherwise alphablending will not work correctly. You should also not
// attempt to blit something over the sprites drawed with this class, because
// that would destroy the alphblending effect as well.
//
// The class supports two creation methods. The first method is the easiest,
// but it is restricted to a more simple outfit. You can also prepare the
// vertices for the structure yourself and then pass it to the Sprite3D class
// using the second CreateSprite() method.
//
//-----------------------------------------------------------------------------

#include "Sprite3D.h"


//-----------------------------------------------------------------------------
// Name: Sprite3D::Sprite3D()
// Desc: The default constructor of the Sprite3D class
//-----------------------------------------------------------------------------
Sprite3D::Sprite3D()
{}


//-----------------------------------------------------------------------------
// Name: Sprite3D::~Sprite3D()
// Desc: The default destructor of the Sprite3D class
//-----------------------------------------------------------------------------
Sprite3D::~Sprite3D()
{}


//-----------------------------------------------------------------------------
// Name: Sprite3D::CreateSprite()
// Desc: Creates the settings for the Sprit3D class
//-----------------------------------------------------------------------------
void Sprite3D::CreateSprite( char* strTexFilename, D3DCOLOR color, D3DCOLOR specular,
							 int x1, int y1, int x2, int y2,
							 float tu1, float tv1, float tu2, float tv2 )
{
	// Set the screen and texture coordinates
	m_nX1 = x1; m_nX2 = x2;
	m_nY1 = y1; m_nY2 = y2;
	m_fTU1 = tu1; m_fTU2 = tu2;
	m_fTV1 = tv1; m_fTV2 = tv2;

	// Set the texture filename and the colors
	m_strTexFilename = strTexFilename;
	m_cColor		 = color;
	m_cSpecular		 = specular;

	// Generate the vertices from the set screen coordinates
	m_vSpriteVertices[0] = D3DTLVERTEX( D3DVECTOR( x1, y1, 0 ), 1, m_cColor, m_cSpecular, tu1, tv1 );
	m_vSpriteVertices[1] = D3DTLVERTEX( D3DVECTOR( x2, y1, 0 ), 1, m_cColor, m_cSpecular, tu2, tv1 );
	m_vSpriteVertices[2] = D3DTLVERTEX( D3DVECTOR( x1, y2, 0 ), 1, m_cColor, m_cSpecular, tu1, tv2 );
	m_vSpriteVertices[3] = D3DTLVERTEX( D3DVECTOR( x2, y2, 0 ), 1, m_cColor, m_cSpecular, tu2, tv2 );
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::RenderSprite()
// Desc: Renders the sprite onto the screen
//-----------------------------------------------------------------------------
void Sprite3D::RenderSprite( LPDIRECT3DDEVICE3 pd3dDevice )
{
	ULONG lOldZFunc;

	// Overwrite all other objects on screen
	pd3dDevice->GetRenderState( D3DRENDERSTATE_ZFUNC, &lOldZFunc );
	pd3dDevice->SetRenderState( D3DRENDERSTATE_ZFUNC, D3DCMP_ALWAYS );

	pd3dDevice->SetTexture( 0, D3DTextr_GetTexture(m_strTexFilename) );
	pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, m_vSpriteVertices, 4, NULL );
	
	pd3dDevice->SetRenderState( D3DRENDERSTATE_ZFUNC, lOldZFunc );
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::Move()
// Desc: Moves the sprite x and y pixels
//-----------------------------------------------------------------------------
void Sprite3D::Move( int x, int y )
{
	m_nX1 += x; m_nX2 += x;
	m_nY1 += y; m_nY2 += y;
	RefreshPosition();
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::RefreshVertices()
// Desc: Refreshes the sprite's vertices to update the render settings
//-----------------------------------------------------------------------------
void Sprite3D::RefreshVertices()
{
	m_vSpriteVertices[0] = D3DTLVERTEX( D3DVECTOR( m_nX1, m_nY1, 0 ), 1, m_cColor, m_cSpecular, m_fTU1, m_fTV1 );
	m_vSpriteVertices[1] = D3DTLVERTEX( D3DVECTOR( m_nX2, m_nY1, 0 ), 1, m_cColor, m_cSpecular, m_fTU2, m_fTV1 );
	m_vSpriteVertices[2] = D3DTLVERTEX( D3DVECTOR( m_nX1, m_nY2, 0 ), 1, m_cColor, m_cSpecular, m_fTU1, m_fTV2 );
	m_vSpriteVertices[3] = D3DTLVERTEX( D3DVECTOR( m_nX2, m_nY2, 0 ), 1, m_cColor, m_cSpecular, m_fTU2, m_fTV2 );
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::RefreshPosition()
// Desc: Refreshes only the position of the vertices
//-----------------------------------------------------------------------------
void Sprite3D::RefreshPosition()
{
	m_vSpriteVertices[0].sx = m_nX1; m_vSpriteVertices[0].sy = m_nY1;
	m_vSpriteVertices[1].sx = m_nX2; m_vSpriteVertices[1].sy = m_nY1;
	m_vSpriteVertices[2].sx = m_nX1; m_vSpriteVertices[2].sy = m_nY2;
	m_vSpriteVertices[3].sx = m_nX2; m_vSpriteVertices[3].sy = m_nY2;
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::GetColor()
// Desc: Returns the ambient color of the sprite
//-----------------------------------------------------------------------------
D3DCOLOR Sprite3D::GetColor()
{
	return m_cColor;
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::GetSpecular()
// Desc: Returns the specular color of the sprite
//-----------------------------------------------------------------------------
D3DCOLOR Sprite3D::GetSpecular()
{
	return m_cSpecular;
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::GetCoordinates()
// Desc: Returns the coordinates of the sprite
//-----------------------------------------------------------------------------
void Sprite3D::GetCoordinates( int& x1, int& y1, int& x2, int& y2 )
{
	x1 = m_nX1; x2 = m_nX2;
	y1 = m_nY1; y2 = m_nY2;
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::GetVertices()
// Desc: Returns a ptr to the sprite's vertices
//-----------------------------------------------------------------------------
D3DTLVERTEX* Sprite3D::GetVertices()
{
	return m_vSpriteVertices;
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::GetTexFilename()
// Desc: Returns the sprite's texture filename
//-----------------------------------------------------------------------------
char* Sprite3D::GetTexFilename()
{
	return m_strTexFilename;
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::SetColors()
// Desc: Sets the colors of the whole sprite
//-----------------------------------------------------------------------------
void Sprite3D::SetColors( D3DCOLOR color, D3DCOLOR specular )
{
	m_cColor = color;
	m_cSpecular = specular;
	RefreshVertices();
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::SetPosition()
// Desc: Sets the position and size of the sprite
//-----------------------------------------------------------------------------
void Sprite3D::SetPosition( int x1, int y1, int x2, int y2 )
{
	m_nX1 = x1; m_nX2 = x2;
	m_nY1 = y1; m_nY2 = y2;
	RefreshVertices();
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::SetVertices()
// Desc: Uses an array of vertices to set the sprite vertices
//-----------------------------------------------------------------------------
void Sprite3D::SetVertices( D3DTLVERTEX *vVertices )
{
	memcpy( m_vSpriteVertices, vVertices, sizeof(D3DTLVERTEX)*NUM_SPRITECOORDS );
	RefreshVertices();
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::SetTexFilename()
// Desc: Sets the texture filename of this sprite
//-----------------------------------------------------------------------------
void Sprite3D::SetTexFilename( char* strTexFilename )
{
	m_strTexFilename = strTexFilename;
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::SetTextureCoords()
// Desc: Sets the texture coordinates of the sprite
//-----------------------------------------------------------------------------
void Sprite3D::SetTextureCoords( float tu1, float tv1, float tu2, float tv2 )
{
	m_fTU1 = tu1; m_fTU2 = tu2;
	m_fTV1 = tv1; m_fTV2 = tv2;
	RefreshVertices();
}


//-----------------------------------------------------------------------------
// Name: Sprite3D::SetVertexColor()
// Desc: Sets the vertex' color parameters
//-----------------------------------------------------------------------------
void Sprite3D::SetVertexColor( int nNumVertex, D3DCOLOR color, D3DCOLOR specular )
{
	m_vSpriteVertices[nNumVertex].color = color;
	m_vSpriteVertices[nNumVertex].specular = specular;
}
