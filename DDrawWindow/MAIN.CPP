#include <windows.h>

HWND hwnd;

long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
	switch(message)
	{
		
	case WM_ERASEBKGND:
		break;
	//case WM_ACTIVATEAPP:
	case WM_ACTIVATE:
		break;	
	case WM_CREATE:
		break;
	case WM_PAINT:
		break;
		
	case WM_SETCURSOR:
		SetCursor(LoadCursor(NULL,IDC_ARROW));
		//	else
		//		SetCursor(NULL);
		break;
		
	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_RETURN:
			break;
		case VK_ESCAPE:
			break;
		default:
			break;
		}
		
		break;
	case WM_COMMAND:				
			break;
				
	case WM_DESTROY:
			break;
	case WM_CLOSE:
		PostQuitMessage(0);
			break;
	case WM_QUIT:
		break;
	}

	return DefWindowProc(hWnd,message,wParam,lParam);

} /* WindowProc */

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "mainwindow";
	if(RegisterClass( &wc )==0)return(0);
	
	//Create main window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		"mainwindow","DDrawWindow",WS_POPUPWINDOW|WS_CAPTION,
		0, 0,
		800,
		600,
		NULL,NULL,hInstance,
		NULL );
	
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	
	MSG msg;
	while(1)
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
			if(GetMessage( &msg, NULL, 0, 0 )==0)
			{
				return 0;
			}
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
        else
        {
            WaitMessage();
        }
	}

	return 0;

}