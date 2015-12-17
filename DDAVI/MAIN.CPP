// NoMoRe:
// Hier mal zum angucken, habe auf die schnelle gemacht... Der Knackpunt, 
// sieh doch selbst rein... Du mußt für DShow das DDrawEx benutzen.. dann
// Klappts... Ist etwas gewöhnungsbedürftig aber... Und ist gleich DX3 dabei..
// Sollte aber wirklich zum angucken sein, da es ziemlich unsauber ist...
//
//
// Viel Spaß mit Probieren...
//                                        Janusch
//

#include <windows.h>
#include <mmstream.h>   
#include <amstream.h>
#include <ddstream.h> 
#include <initguid.h>  
#include <ddrawex.h>  

#define APPLICATIONNAME "AVI-Play"
#define CLASSNAME "MMSDDRAW FULLSCREEN"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
//Global variables
HWND              ghWnd;
HINSTANCE         ghInst;

RECT              rect, rect2;            // Rectangles for screen coordinates
                                          // rect  - Videogröße

//DirectDrawEx Global interfaces
IDirectDraw             *g_pDD=NULL;   
IDirectDraw3            *g_pDD3=NULL; 
IDirectDrawFactory      *g_pDDF=NULL;
IDirectDrawSurface      *g_pPrimarySurface=NULL,
                        *g_pDDSoff_screen=NULL;
IDirectDrawClipper      *g_pDDClipper=NULL;

//Global MultiMedia streaming interfaces
IMultiMediaStream        *g_pMMStream=NULL;
IMediaStream             *g_pPrimaryVidStream=NULL;    
IDirectDrawMediaStream   *g_pDDStream=NULL;
IDirectDrawStreamSample  *g_pSample=NULL;

//Function prototypes
int PASCAL WinMain(HINSTANCE hInstC, HINSTANCE hInstP, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WndMainProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HRESULT InitDDrawEx();
HRESULT RenderFileToMMStream(LPCTSTR szFilename);    
HRESULT InitRenderToSurface();
void RenderToSurface();


//;-------------------------------------------------------------------------------------

HRESULT InitRenderToSurface()
{    
    HRESULT            hr;
    DDSURFACEDESC    ddsd;
    
    hr = g_pMMStream->GetMediaStream(MSPID_PrimaryVideo, &g_pPrimaryVidStream);
    if (FAILED(hr))
    {   goto Exit;
    }

    hr = g_pPrimaryVidStream->QueryInterface(IID_IDirectDrawMediaStream, (void **)&g_pDDStream);
    if (FAILED(hr))
    {   goto Exit;
    }

    ddsd.dwSize = sizeof(ddsd);
    hr = g_pDDStream->GetFormat(&ddsd, NULL, NULL, NULL);
    if (FAILED(hr))
    {   goto Exit;
    }

      rect.top = rect.left = 0;            
    rect.bottom = ddsd.dwHeight;
    rect.right = ddsd.dwWidth;

    hr = g_pDDStream->CreateSample(g_pDDSoff_screen, &rect, 0, &g_pSample);
    if (FAILED(hr))
    {   goto Exit;
    }

    g_pMMStream->SetState(STREAMSTATE_RUN);
Exit:
    if (FAILED(hr)) 
    {    MessageBox(ghWnd, "Initialization failure in InitRenderToSurface", "Error", MB_OK);
        return E_FAIL;
    }
    return NOERROR;
}

//;-------------------------------------------------------------------

void RenderToSurface()
{
    HRESULT        hr;


    
    if (g_pSample->Update(0, NULL, NULL, 0) != S_OK) {
        g_pMMStream->SetState(STREAMSTATE_STOP);        
    }
    else 
    {

    
    hr = g_pPrimarySurface->Blt(&rect, g_pDDSoff_screen, &rect, DDBLT_WAIT, NULL); 
    if(FAILED(hr))
    {   MessageBox(ghWnd, "Blt failed", "Error", MB_OK);
            
    }
    }
}

//;------------------------------------------------------------------

HRESULT RenderFileToMMStream(LPCTSTR szFilename)       
{    
    HRESULT hr;
    IAMMultiMediaStream *pAMStream=NULL;

    WCHAR wFile[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, szFilename, -1, wFile,    
                                sizeof(wFile)/sizeof(wFile[0]));

    hr =CoCreateInstance(CLSID_AMMultiMediaStream, NULL, CLSCTX_INPROC_SERVER,
                                      IID_IAMMultiMediaStream, (void **)&pAMStream);
    if (FAILED(hr))
    {   MessageBox(ghWnd, "Could not create a CLSID_MultiMediaStream object\n"
        "Check you have run regsvr32 amstream.dll\n", "Error", MB_OK);
          return E_FAIL;
    }

    hr = pAMStream->Initialize(STREAMTYPE_READ, 0, NULL);
    if (FAILED(hr))
    {   MessageBox(ghWnd, "Initialize failed.", "Error", MB_OK);
          return E_FAIL;
    }
    hr = pAMStream->AddMediaStream(g_pDD3, &MSPID_PrimaryVideo, 0, NULL);
    if (FAILED(hr))
    {   MessageBox(ghWnd, "AddMediaStream failed.", "Error", MB_OK);
          return E_FAIL;
    }
    hr = pAMStream->AddMediaStream(NULL, &MSPID_PrimaryAudio, AMMSF_ADDDEFAULTRENDERER, NULL);
    if (FAILED(hr))
    {   MessageBox(ghWnd, "AddMediaStream failed.", "Error", MB_OK);
          return E_FAIL;
    }
    hr = pAMStream->OpenFile(wFile, 0); 
    if (FAILED(hr))
    {   MessageBox(ghWnd, "File format not supported.", "Error", MB_OK);
          return E_FAIL;
    }

    g_pMMStream = pAMStream;    
    pAMStream->AddRef();

    return NOERROR;
}

//;----------------------------------------------------------------------------

HRESULT InitDDrawEx()
{    
    HRESULT            hr=NOERROR;
    DDSURFACEDESC    ddsd, ddsd2;

    CoInitialize(NULL);
    
    hr = CoCreateInstance(CLSID_DirectDrawFactory, NULL, CLSCTX_INPROC_SERVER, 
                            IID_IDirectDrawFactory, (void **)&g_pDDF);
    if (FAILED(hr))
    {   MessageBox(ghWnd, "Couldn't create DirectDrawFactory", "Error", MB_OK);
          return E_FAIL;
    }


    hr = (g_pDDF->CreateDirectDraw(NULL, GetDesktopWindow(), DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN, 
                NULL, NULL, &g_pDD));   

    if (FAILED(hr))
    {   MessageBox(ghWnd, "Couldn't create DirectDraw object", "Error", MB_OK);
          return E_FAIL;
    }
    hr =(g_pDD->QueryInterface(IID_IDirectDraw3, (LPVOID*)&g_pDD3));
    
    if (FAILED(hr))
    {   MessageBox(ghWnd, "Couldn't get IDirectDraw3", "Error", MB_OK);
          return E_FAIL;
    }
   	if (FAILED( g_pDD3->SetDisplayMode(640, 480, 16,0,0) ) )
  	{
	  	return E_FAIL;
  	}   

      ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);    
      ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE; 
    hr = g_pDD3->CreateSurface(&ddsd, &g_pPrimarySurface, NULL);
    
    if(FAILED(hr))
    {   MessageBox(ghWnd, "Couldn't create Primary Surface", "Error", MB_OK);
          return E_FAIL;
    }

    hr = g_pPrimarySurface->GetSurfaceDesc(&ddsd);
    if(FAILED(hr))
    {   MessageBox(ghWnd, "Couldn't GetSurfaceDesc", "Error", MB_OK);
            return E_FAIL;
    }

    ZeroMemory(&ddsd2, sizeof(ddsd2));
    ddsd2.dwSize = sizeof(ddsd2);    
    ddsd2.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd2.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd2.dwHeight = ddsd.dwHeight;    
    ddsd2.dwWidth  = ddsd.dwWidth;   
    ddsd2.ddpfPixelFormat = ddsd.ddpfPixelFormat; 

    hr = g_pDD3->CreateSurface(&ddsd2, &g_pDDSoff_screen, NULL);
    if(FAILED(hr))
    {   MessageBox(ghWnd, "Couldn't create off-screen Surface", "Error", MB_OK);
            return E_FAIL;
    }


    hr = g_pDD3->CreateClipper(0, &g_pDDClipper, NULL);
    if(FAILED(hr))
    {   MessageBox(ghWnd, "Couldn't create Clipper", "Error", MB_OK);
            return E_FAIL;
    }
    
    hr = g_pPrimarySurface->SetClipper(g_pDDClipper);
    if(FAILED(hr))
    {   MessageBox(ghWnd, "Call to SetClipper failed", "Error", MB_OK);
            return E_FAIL;
    }

    hr = g_pDDClipper->SetHWnd(0, ghWnd);
    if(FAILED(hr))
    {   MessageBox(ghWnd, "Call to SetHWnd failed", "Error", MB_OK);
            return E_FAIL;
    }



    return NOERROR;    
}

//;----------------------------------------------------------------------------------

LRESULT CALLBACK WndMainProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

   {  
        
    switch(message)
    {
        case WM_COMMAND:
            {
            }
        break;
            
        case WM_DESTROY:
           
           break;
    
        default:
           return DefWindowProc(hWnd, message, wParam, lParam);
    
      } 

      return FALSE;

   } 

//;--------------------------------------------------------------------------------

int PASCAL WinMain(HINSTANCE hInstC, HINSTANCE hInstP, LPSTR lpCmdLine, int nCmdShow)

   {  
    
      MSG        msg;
      WNDCLASS  wc;
      HRESULT    hr;

     ZeroMemory(&wc, sizeof wc);


      ZeroMemory(&wc, sizeof wc);
    	wc.style = CS_HREDRAW | CS_VREDRAW;
      wc.lpfnWndProc = WndMainProc;
      ghInst = wc.hInstance = hInstC;
      wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
      wc.lpszClassName = CLASSNAME;
      wc.lpszMenuName = NULL;
      wc.hCursor = LoadCursor(NULL, IDC_ARROW);
      RegisterClass(&wc);

	// Create a fullscreen window
	ghWnd =CreateWindowEx(
		WS_EX_TOPMOST,
    CLASSNAME,
    APPLICATIONNAME,
		WS_POPUP,
		0, 0,
		GetSystemMetrics( SM_CXSCREEN ),
		GetSystemMetrics( SM_CYSCREEN ),
		NULL,
		NULL,
		ghInst,
		NULL );

  ShowWindow(ghWnd, nCmdShow);   
  UpdateWindow(ghWnd);

  if (ghWnd)
  {                
          hr = InitDDrawEx();    
          if (FAILED(hr)) 
          {
              return 0;
          }
   }
   else
   {
          MessageBox(ghWnd, "Couldn't create window.", "Error", MB_OK);
          return 0;
   }




      HRESULT hrt;
      //Init....
      hrt=RenderFileToMMStream("TEST.AVI");
      if(FAILED(hr))
      {
        return 0;
      }
      hrt=InitRenderToSurface();
      if(FAILED(hr))
      {
        return 0;
      }


	while(!KEY_DOWN(VK_ESCAPE))
	{	

		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!GetMessage(&msg, NULL, 0, 0 )) return msg.wParam;
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else 
		{	
                RenderToSurface();    
		}				
	}      
      return msg.wParam;

}  

//;------------------------------------------------------------- Das War's