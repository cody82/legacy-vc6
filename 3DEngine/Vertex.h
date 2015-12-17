#include "d3d.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// VERTEX class
//////////////////////////////////////////////////////////////////////////////////////////////
class VERTEX : public D3DLVERTEX
{
public:
	VERTEX(void);
	VERTEX(float _x, float _y, float _z, DWORD _color, DWORD _specular, float _tu, float _tv);
	VERTEX(const VERTEX &vertex);

	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	VERTEX& operator = (const VERTEX &vertex);
	VERTEX& operator + (const VERTEX &vertex);
	VERTEX& operator - (const VERTEX &vertex);
};
