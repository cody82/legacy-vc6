#include <windows.h>
#include "3dengine.h"

C3DEngine e;
C3DObject obj;

long PASCAL WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	e.OnWM(message,wParam,lParam);
	
	switch(message)
	{
		case WM_ACTIVATEAPP:
			break;

		case WM_CREATE:
			break;

		case WM_SETCURSOR:
			return TRUE;

		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_CLOSE, 0, 0);
					break;
			}
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{

	obj.lpVertexes=new VERTEX[8];
	obj.nVertexes=8;
	obj.Triangles=new int[36];
	obj.nTriangles=36/3;

	obj.lpVertexes[0] = VERTEX(-10,+10,-10, D3DRGB(1,0,1), D3DRGB(0,0,0), 0,0);
	obj.lpVertexes[1] = VERTEX(+10,+10,-10, D3DRGB(0,0,1), D3DRGB(0,0,0), 0,0);
	obj.lpVertexes[2] = VERTEX(-10,-10,-10, D3DRGB(1,1,1), D3DRGB(0,0,0), 0,0);
	obj.lpVertexes[3] = VERTEX(+10,-10,-10, D3DRGB(1,1,0), D3DRGB(0,0,0), 0,0);
	obj.lpVertexes[4] = VERTEX(-10,+10,+10, D3DRGB(1,0,0), D3DRGB(0,0,0), 0,0);
	obj.lpVertexes[5] = VERTEX(+10,+10,+10, D3DRGB(0,1,1), D3DRGB(0,0,0), 0,0);
	obj.lpVertexes[6] = VERTEX(-10,-10,+10, D3DRGB(1,0,1), D3DRGB(0,0,0), 0,0);
	obj.lpVertexes[7] = VERTEX(+10,-10,+10, D3DRGB(1,0,1), D3DRGB(0,0,0), 0,0);

	obj.Triangles[0] = 0;//1
	obj.Triangles[1] = 1;
	obj.Triangles[2] = 2;
	obj.Triangles[3] = 3;//2
	obj.Triangles[4] = 2;
	obj.Triangles[5] = 1;
	obj.Triangles[6] = 2;//3
	obj.Triangles[7] = 3;
	obj.Triangles[8] = 6;
	obj.Triangles[9] = 7;//4
	obj.Triangles[10] = 6;
	obj.Triangles[11] = 3;
	obj.Triangles[12] = 1;//5
	obj.Triangles[13] = 5;
	obj.Triangles[14] = 3;
	obj.Triangles[15] = 3;//6
	obj.Triangles[16] = 5;
	obj.Triangles[17] = 7;
	obj.Triangles[18] = 5;//7
	obj.Triangles[19] = 4;
	obj.Triangles[20] = 6;
	obj.Triangles[21] = 5;//8
	obj.Triangles[22] = 6;
	obj.Triangles[23] = 7;
	obj.Triangles[24] = 0;//9
	obj.Triangles[25] = 4;
	obj.Triangles[26] = 1;
	obj.Triangles[27] = 1;//10
	obj.Triangles[28] = 4;
	obj.Triangles[29] = 5;
	obj.Triangles[30] = 0;//11
	obj.Triangles[31] = 2;
	obj.Triangles[32] = 4;
	obj.Triangles[33] = 2;//12
	obj.Triangles[34] = 6;
	obj.Triangles[35] = 4;

	obj.vRotSpeed.x=25;
	obj.vRotSpeed.y=50;
	obj.vRotSpeed.z=100;


	e.Initialize(800,600,1,16,WinProc,hInst,TRUE);
	e.pFirstObject=&obj;

	obj.e=&e;
	
	e.Start();

	return 0;
}