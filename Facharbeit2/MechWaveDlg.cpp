#include "mechwavedlg.h"

IMPLEMENT_CLASSINFO(CMechanicWaveDlg,CWindow)

BOOL CALLBACK AboutDlgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch(message)
	{
	case WM_COMMAND:
		if(HIWORD(wParam)==BN_CLICKED)
		{
			switch(LOWORD(wParam))
			{
			case IDOK:
				EndDialog(hWnd,IDOK);
				return 0;
			case IDCANCEL:
				EndDialog(hWnd,IDCANCEL);
				return 0;
			}
		}
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

CMechanicWaveDlg::CMechanicWaveDlg() : CWindow()
{
	bUpdate=TRUE;
	gu.ge=&ge;
}

CMechanicWaveDlg::~CMechanicWaveDlg()
{
}
	
BOOL CMechanicWaveDlg::Update(DWORD dTime)
{
	//ge.lpD3DXEngine->ClearBackBuffer(0,0,64);
	//ge.lpD3DXEngine->DrawEngineStats();
	//ge.lpD3DXEngine->UpdateFrame();
	gu.Update(dTime);
	return TRUE;
}

BOOL CMechanicWaveDlg::Create()
{
	CWindow::Create("Mechanische Welle",100,100,800,600,NULL,0,0,IDR_WAVEMENU);

	s_GE_Init gi;
	
	Display.Create("Graph",150,70,640,480,hWnd,0,0);
	
	gi.hWnd=Display.hWnd;//
	
	gi.hInst=CUniversal::GetWndClass(NULL)->hInstance;
	gi.pRes.x=640;
	gi.pRes.y=480;
	gi.nBpp=D3DX_DEFAULT;
	gi.nBackbuffers=1;
	gi.bFullscreen=FALSE;
	gi.dwD3DXDeviceIndex=D3DX_DEFAULT;
	gi.bNoDSound=TRUE;
	gi.bNoDInput=TRUE;
	
	ge.Initialize(gi);
	

	gu.Init();

	return TRUE;
}

VOID CMechanicWaveDlg::Destroy()
{
	ge.Shutdown();
	CWindow::Destroy();
}

long FAR PASCAL CMechanicWaveDlg::WindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	case WM_PAINT:
		CWindow::WindowProc(hWnd,message,wParam,lParam);
		gu.Update(0);
		return 0;
	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_RETURN:
			break;
		case VK_ESCAPE:
			Destroy();
			break;
		default:
			break;
		}
		break;
	case WM_COMMAND:
		{
			WORD wNotifyCode = HIWORD(wParam);
			WORD wControlID= LOWORD(wParam);
			HWND hwndCtl = (HWND) lParam;
		
			if(wNotifyCode==BN_CLICKED)
			{
				switch(wControlID)
				{
				case ID_DATEI_BEENDEN:
					Destroy();
					break;
				case ID_INFO_ABOUT:
					DialogBox(CUniversal::GetWndClass(NULL)->hInstance,MAKEINTRESOURCE(IDD_ABOUT),hWnd,AboutDlgProc);
					break;
				case ID_ANSICHT_HINTERGRUNDFARBE:
					{
						CHOOSECOLOR cc;                 // common dialog box structure 
						DWORD rgbCurrent;        // initial color selection
						static COLORREF acrCustClr[16]; // array of custom colors 
						
						// Initialize CHOOSECOLOR 
						ZeroMemory(&cc, sizeof(CHOOSECOLOR));
						cc.lStructSize = sizeof(CHOOSECOLOR);
						cc.hwndOwner = hWnd;
						cc.lpCustColors = acrCustClr;
						cc.rgbResult = gu.Wave->crWndColor;
						cc.Flags = CC_FULLOPEN | CC_RGBINIT;
						
						if (ChooseColor(&cc)==TRUE)
						{
							rgbCurrent = cc.rgbResult;
							gu.Wave->crWndColor=rgbCurrent;
						}
					}
					break;
				case ID_WELLE_AUSLOESEN:
					gu.Wave->SingleWave();
					break;
				case ID_EINSTELLUNGEN_ENGINEINFO_EIN:
					ge.lpD3DXEngine->bDrawEngineStats=TRUE;
					break;
				case ID_EINSTELLUNGEN_ENGINEINFO_AUS:
					ge.lpD3DXEngine->bDrawEngineStats=FALSE;
					break;
				case ID_ANSICHT_WELLENFARBE:
					{
						CHOOSECOLOR cc;                 // common dialog box structure 
						DWORD rgbCurrent;        // initial color selection
						static COLORREF acrCustClr[16]; // array of custom colors 
						
						// Initialize CHOOSECOLOR 
						ZeroMemory(&cc, sizeof(CHOOSECOLOR));
						cc.lStructSize = sizeof(CHOOSECOLOR);
						cc.hwndOwner = hWnd;
						cc.lpCustColors = acrCustClr;
						cc.rgbResult = gu.Wave->crWaveColor;
						cc.Flags = CC_FULLOPEN | CC_RGBINIT;
						
						if (ChooseColor(&cc)==TRUE)
						{
							rgbCurrent = cc.rgbResult;
							gu.Wave->crWaveColor=rgbCurrent;
						}
					}
					break;
				}
			}
			break;
		}
	}
	return CWindow::WindowProc(hWnd,message,wParam,lParam);

}

CWaveGraph::CWaveGraph() : CGameUpdater()
{
	Wave=NULL;
}

CWaveGraph::~CWaveGraph()
{
}

BOOL CWaveGraph::Init()
{
	Wave=new CMechanicWave;
	Objects.Add(Wave);
	Wave->SetSize(640,480);
	Wave->CenterScreen();
	Wave->CreateCoords(320);
	Wave->SetWindowColor(0,0,0);
	Wave->SingleWave();
	return TRUE;
}

BOOL CWaveGraph::DrawBackground()
{
	//ge->lpD3DXEngine->ClearBackBuffer(BgColor.rgbtRed,BgColor.rgbtGreen,BgColor.rgbtBlue);
	return TRUE;
}
