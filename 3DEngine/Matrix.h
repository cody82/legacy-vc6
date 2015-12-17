/////////////////////////////////////////////////////////////////////////////////////
// Matrix Functions
/////////////////////////////////////////////////////////////////////////////////////
#define D3D_OVERLOADS
#define PI 3.141592653
#pragma warning (disable : 4244)

#include <d3d.h>

D3DMATRIX IdentityMatrix(void);
D3DMATRIX ZeroMatrix(void);
D3DMATRIX MatrixMult(const D3DMATRIX a, const D3DMATRIX b);

D3DMATRIX Translate(const float dx, const float dy, const float dz);
D3DMATRIX RotateX(const float rads);
D3DMATRIX RotateY(const float rads);
D3DMATRIX RotateZ(const float rads);
D3DMATRIX Scale(const float size);

D3DMATRIX ViewMatrix(const D3DVECTOR from,
                     const D3DVECTOR at,
                     const D3DVECTOR world_up,
                     const float roll);
D3DMATRIX ProjectionMatrix(const float near_plane,
                           const float far_plane,
                           const float fov);

/////////////////////////////////////////////////////////////////////////////////////
// MATRIX class
/////////////////////////////////////////////////////////////////////////////////////
class MATRIX : public D3DMATRIX
{
public:
	MATRIX(void);

	void Identity(void);
	void Zero(void);
	void Multiply(D3DMATRIX mat);

	void Translate(float dx, float dy, float dz);
	void RotateX(double rads);
	void RotateY(double rads);
	void RotateZ(double rads);
	void Scale(float x, float y, float z);

	void SetView(D3DVECTOR from, D3DVECTOR at, D3DVECTOR world_up, float roll);
	void SetProjection(float near_plane, float far_plane, float fov);
};
