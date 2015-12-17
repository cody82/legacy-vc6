#include <ddrawwindow.h>

long FAR PASCAL DDrawWindowProc( HWND hWnd, UINT message, 
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
