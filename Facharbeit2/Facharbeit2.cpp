#include <gamelib.h>

#include "mechwavedlg.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	CUniversal::GetWndClass(hInstance);

	CMechanicWaveDlg mwdlg;
	mwdlg.Create();

	mwdlg.DoModal();

	return 0;
}



