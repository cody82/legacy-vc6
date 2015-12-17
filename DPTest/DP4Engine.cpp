#include "dp4engine.h"

static CDP4Engine DP4Engine;

CDP4Engine::CDP4Engine()
{
	Connections=NULL;
	dwNumConnections=0;
	lpDP=NULL;
	dwEnumCounter=0;
	dwNumSessions=0;
	Sessions=NULL;
	bHost=FALSE;
	Players=NULL;
	dwNumPlayers=0;
	MessageProc=NULL;
	SysMessageProc=NULL;
	ChatProc=NULL;
	CoInitialize (NULL);
}

CDP4Engine::~CDP4Engine()
{
	Shutdown();
	CoUninitialize();
}

BOOL CDP4Engine::Initialize()
{
	HRESULT hr;

	hr = CoCreateInstance(CLSID_DirectPlay,NULL,CLSCTX_INPROC_SERVER,IID_IDirectPlay4A,(VOID**)&DP4Engine.lpDP);
	if(FAILED(hr))
	{
		return FALSE;
	}

	return TRUE;
}
	
BOOL CDP4Engine::CreateSession(LPSTR pszName,DWORD dwMaxPlayers)
{
	DPSESSIONDESC2 dpsd;
	HRESULT hr;

	ZeroMemory( &dpsd, sizeof(dpsd) );
	dpsd.dwSize           = sizeof(dpsd);

	//dpsd.guidApplication  = g_AppGUID;
	dpsd.lpszSessionNameA = pszName;
//	dpsd.lpszSessionName = pszName;
	dpsd.dwMaxPlayers     = dwMaxPlayers;
	// The DPSESSION_KEEPALIVE flag keeps the session alive 
	//  if players abnormally exit.
	dpsd.dwFlags          = DPSESSION_KEEPALIVE | DPSESSION_MIGRATEHOST;
	//if ( g_bUseProtocol )
	dpsd.dwFlags |= DPSESSION_DIRECTPLAYPROTOCOL;
	
	// Create a new session.
	//g_bHostPlayer = TRUE;
	hr = DP4Engine.lpDP->Open( &dpsd, DPOPEN_CREATE );
	if(FAILED(hr))
	{
		return FALSE;
	}

	DP4Engine.bHost=TRUE;

	return TRUE;
}
	
DWORD CDP4Engine::GetNumConnections()
{
	return DP4Engine.dwNumConnections;
}
	
st_DP4E_Connection *CDP4Engine::GetConnections()
{
	return DP4Engine.Connections;
}
	
DWORD CDP4Engine::GetNumSessions()
{
	return DP4Engine.dwNumSessions;
}

DWORD CDP4Engine::GetNumPlayers()
{
	return DP4Engine.dwNumPlayers;
}

st_DP4E_Player *CDP4Engine::GetPlayers()
{
	return DP4Engine.Players;
}

st_DP4E_Session *CDP4Engine::GetSessions()
{
	return DP4Engine.Sessions;
}
	
VOID CDP4Engine::SetChatProc(CHATPROC proc)
{
	DP4Engine.ChatProc=proc;
}

void CDP4Engine::Shutdown()
{
	if(DP4Engine.lpDP)
	{
		DP4Engine.lpDP->Release();
		DP4Engine.lpDP=NULL;
	}
}
	
VOID CDP4Engine::HandleSystemMessage(LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,DPID idFrom, DPID idTo)
{
	switch (lpMsg->dwType)
	{
	case DPSYS_CREATEPLAYERORGROUP:
        {
            /*LPDPMSG_CREATEPLAYERORGROUP		lp = (LPDPMSG_CREATEPLAYERORGROUP) lpMsg;
			LPSTR							lpszPlayerName;
			LPSTR							szDisplayFormat = "\"%s\" has joined\r\n";
            
			// get pointer to player name
			if (lp->dpnName.lpszShortNameA)
				lpszPlayerName = lp->dpnName.lpszShortNameA;
			else
				lpszPlayerName = "unknown";

			// allocate space for string
			lpszStr = (LPSTR) GlobalAllocPtr(GHND, lstrlen(szDisplayFormat) +
												   lstrlen(lpszPlayerName) + 1);
			if (lpszStr == NULL)
				break;

			// build string
			wsprintf(lpszStr, szDisplayFormat, lpszPlayerName);*/
			EnumPlayers();
        }
		break;

	case DPSYS_DESTROYPLAYERORGROUP:
        {
            /*LPDPMSG_DESTROYPLAYERORGROUP	lp = (LPDPMSG_DESTROYPLAYERORGROUP)lpMsg;
			LPSTR							lpszPlayerName;
			LPSTR							szDisplayFormat = "\"%s\" has left\r\n";
            
			// get pointer to player name
			if (lp->dpnName.lpszShortNameA)
				lpszPlayerName = lp->dpnName.lpszShortNameA;
			else
				lpszPlayerName = "unknown";

			// allocate space for string
			lpszStr = (LPSTR) GlobalAllocPtr(GHND, lstrlen(szDisplayFormat) +
												   lstrlen(lpszPlayerName) + 1);
			if (lpszStr == NULL)
				break;

			// build string
			wsprintf(lpszStr, szDisplayFormat, lpszPlayerName);*/
			EnumPlayers();
        }
		break;

	case DPSYS_ADDPLAYERTOGROUP:
        {
            //LPDPMSG_ADDPLAYERTOGROUP lp = (LPDPMSG_ADDPLAYERTOGROUP)lpMsg;
			EnumPlayers();
        }
		break;

	case DPSYS_DELETEPLAYERFROMGROUP:
        {
            //LPDPMSG_DELETEPLAYERFROMGROUP lp = (LPDPMSG_DELETEPLAYERFROMGROUP)lpMsg;
			EnumPlayers();
        }
		break;

	case DPSYS_SESSIONLOST:
        {
            //LPDPMSG_SESSIONLOST lp = (LPDPMSG_SESSIONLOST)lpMsg;
        }
		break;

	case DPSYS_HOST:
        {
            /*LPDPMSG_HOST	lp = (LPDPMSG_HOST)lpMsg;
			LPSTR			szDisplayFormat = "You have become the host\r\n";

			// allocate space for string
			lpszStr = (LPSTR) GlobalAllocPtr(GHND, lstrlen(szDisplayFormat) + 1);
			if (lpszStr == NULL)
				break;

			// build string
			lstrcpy(lpszStr, szDisplayFormat);

			// we are now the host
			lpDPInfo->bIsHost = TRUE;*/
			EnumPlayers();
			DP4Engine.bHost=TRUE;
        }
		break;

	case DPSYS_SETPLAYERORGROUPDATA:
        {
            //LPDPMSG_SETPLAYERORGROUPDATA lp = (LPDPMSG_SETPLAYERORGROUPDATA)lpMsg;
			EnumPlayers();
        }
		break;

	case DPSYS_SETPLAYERORGROUPNAME:
        {
            //LPDPMSG_SETPLAYERORGROUPNAME lp = (LPDPMSG_SETPLAYERORGROUPNAME)lpMsg;
			EnumPlayers();
        }
		break;

	case DPSYS_CHAT:
		{
			if(DP4Engine.ChatProc)
			{
				DP4Engine.ChatProc( 
					((DPMSG_CHAT*)lpMsg)->lpChat->lpszMessageA,
					((DPMSG_CHAT*)lpMsg)->idFromPlayer,
					((DPMSG_CHAT*)lpMsg)->idToPlayer,
					((DPMSG_CHAT*)lpMsg)->idToGroup
					);
				return;
			}
			//LPSTR lpszText,DPID idFrom, DPID idToPlayer,DPID idToGroup
		}
		break;
	}

	if(DP4Engine.SysMessageProc)DP4Engine.SysMessageProc(lpMsg,dwMsgSize,idFrom,idTo);
}

VOID CDP4Engine::HandleApplicationMessage(LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,DPID idFrom, DPID idTo)
{
/*	LPSTR	lpszStr = NULL;
	HRESULT	hr;

	switch (lpMsg->dwType)
	{
	case APPMSG_CHATSTRING:
        {
            LPMSG_CHATSTRING   lp = (LPMSG_CHATSTRING) lpMsg;

			// create string to display
			hr = NewChatString(lpDPInfo->lpDirectPlay3A, idFrom, lp->szMsg, &lpszStr);
			if FAILED(hr)
				break;
        }
		break;
	}

	// post string to chat window
	if (lpszStr)
	{
		// make sure window is still valid
		if (ghChatWnd)
			PostMessage(ghChatWnd, WM_USER_ADDSTRING, (WPARAM) 0, (LPARAM) lpszStr);
		else
			GlobalFreePtr(lpszStr);
	}
*/
	if(DP4Engine.MessageProc)DP4Engine.MessageProc(lpMsg,dwMsgSize,idFrom,idTo);
}
	
BOOL CDP4Engine::SendChatMessage(st_DP4E_Player *Player,LPSTR lpszMessage)
{
	HRESULT hr;
	DPCHAT dpchat;

	ZeroMemory(&dpchat,sizeof(DPCHAT));
	dpchat.dwSize=sizeof(DPCHAT);
	dpchat.lpszMessageA=lpszMessage;

	hr=DP4Engine.lpDP->SendChatMessage(DP4Engine.LocalPlayer.id,Player->id,DPSEND_GUARANTEED,&dpchat);
	if(FAILED(hr))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDP4Engine::ReceiveMessages()
{
	DPID				idFrom, idTo;
	LPVOID				lpvMsgBuffer;
	DWORD				dwMsgBufferSize;
	HRESULT				hr;

	lpvMsgBuffer = NULL;
	dwMsgBufferSize = 0;

	// loop to read all messages in queue
	do
	{
		// loop until a single message is successfully read
		do
		{
			// read messages from any player, including system player
			idFrom = 0;
			idTo = 0;

			hr = DP4Engine.lpDP->Receive(&idFrom, &idTo, DPRECEIVE_ALL,lpvMsgBuffer, &dwMsgBufferSize);

			// not enough room, so resize buffer
			if (hr == DPERR_BUFFERTOOSMALL)
			{
				if (lpvMsgBuffer)
					GlobalFreePtr(lpvMsgBuffer);
				lpvMsgBuffer = GlobalAllocPtr(GHND, dwMsgBufferSize);
				if (lpvMsgBuffer == NULL)
					hr = DPERR_OUTOFMEMORY;
			}
		} while (hr == DPERR_BUFFERTOOSMALL);

		if ((SUCCEEDED(hr)) &&							// successfully read a message
			(dwMsgBufferSize >= sizeof(DPMSG_GENERIC)))	// and it is big enough
		{
			// check for system message
			if (idFrom == DPID_SYSMSG)
			{
				HandleSystemMessage((LPDPMSG_GENERIC) lpvMsgBuffer,dwMsgBufferSize, idFrom, idTo);
			}
			else
			{
				HandleApplicationMessage((LPDPMSG_GENERIC) lpvMsgBuffer,dwMsgBufferSize, idFrom, idTo);
			}
		}
	} while (SUCCEEDED(hr));

	// free any memory we created
	if (lpvMsgBuffer)
		GlobalFreePtr(lpvMsgBuffer);

	return (TRUE);
}

BOOL CDP4Engine::EnumPlayers()
{
	HRESULT hr;
	BOOL countonly;

	DP4Engine.dwNumPlayers=0;
	countonly=TRUE;
	hr = DP4Engine.lpDP->EnumPlayers(NULL,DPConnect_EnumPlayersCallback2,&countonly,0);
	if(FAILED(hr))
	{
		return FALSE;
	}

	if(DP4Engine.Players)delete[] DP4Engine.Players;
	DP4Engine.Players=new st_DP4E_Player[DP4Engine.dwNumPlayers];
	countonly=FALSE;
	DP4Engine.dwEnumCounter=0;

	hr = DP4Engine.lpDP->EnumPlayers(NULL,DPConnect_EnumPlayersCallback2,&countonly,0);
	if(FAILED(hr))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDP4Engine::JoinSession(DWORD dwSessionIndex)
{
	HRESULT hr;
	DPSESSIONDESC2 dpsd;

	ZeroMemory( &dpsd, sizeof(dpsd) );
	dpsd.dwSize          = sizeof(dpsd);
	dpsd.guidInstance    = DP4Engine.Sessions[dwSessionIndex].guidInstance;
	//dpsd.guidApplication = g_AppGUID;
 
	// Join the session
	DP4Engine.bHost = FALSE;
	hr = DP4Engine.lpDP->Open( &dpsd, DPOPEN_JOIN );
	if(FAILED(hr))
	{
		return FALSE;
	}

	return TRUE;
}
	
VOID CDP4Engine::SetMessageProc(MESSAGEPROC proc)
{
	DP4Engine.MessageProc=proc;
}

VOID CDP4Engine::SetSysMessageProc(MESSAGEPROC proc)
{
	DP4Engine.SysMessageProc=proc;
}

BOOL CDP4Engine::CreatePlayer(LPSTR lpszPlayerName)
{
	DPNAME dpname;
	HRESULT hr;

	ZeroMemory( &dpname, sizeof(DPNAME) );
	dpname.dwSize         = sizeof(DPNAME);
	dpname.lpszShortNameA = lpszPlayerName;

	hr = DP4Engine.lpDP->CreatePlayer( &DP4Engine.LocalPlayer.id, &dpname,NULL, NULL, 0, 0);
	strcpy(DP4Engine.LocalPlayer.name,lpszPlayerName);

	if(FAILED(hr))
	{
		return FALSE;
	}

    return TRUE;
}

BOOL FAR PASCAL CDP4Engine::DPConnect_EnumPlayersCallback2(
		DPID dpId,
		DWORD dwPlayerType,
		LPCDPNAME lpName,
		DWORD dwFlags,
		LPVOID lpContext)
{
    if (dpId==0||lpName==NULL)
        return FALSE; 
 
    // Found a Player
	if(*(BOOL*)lpContext)//Count only
	{
		DP4Engine.dwNumPlayers++;
		return TRUE;
	}

	DP4Engine.Players[DP4Engine.dwEnumCounter].id=dpId;
	if(lpName->lpszShortNameA)
		strcpy(DP4Engine.Players[DP4Engine.dwEnumCounter].name,lpName->lpszShortNameA);

	DP4Engine.dwEnumCounter++;

	return TRUE;
}

BOOL CDP4Engine::EnumSessions()
{
	DPSESSIONDESC2 dpsd;
	HRESULT hr;
	BOOL countonly;

	// Enum sessions and let DirectPlay decide the timeout.
	ZeroMemory( &dpsd, sizeof(dpsd) );
	dpsd.dwSize          = sizeof(dpsd);
	//dpsd.guidApplication = NULL;
 
	// Enumerate all the active DirectPlay games 
	//  on the selected connection.
	
	countonly=TRUE;
	DP4Engine.dwNumSessions=0;
	hr = DP4Engine.lpDP->EnumSessions(&dpsd,0,DPConnect_EnumSessionsCallback,&countonly,DPENUMSESSIONS_ALL|DPENUMSESSIONS_ASYNC);
	if(FAILED(hr))
	{
		return FALSE;
	}
	
	DP4Engine.dwEnumCounter=0;
	if(DP4Engine.Sessions)delete[] DP4Engine.Sessions;
	DP4Engine.Sessions=new st_DP4E_Session[DP4Engine.dwNumSessions];
	countonly=FALSE;
	hr = DP4Engine.lpDP->EnumSessions(&dpsd,0,DPConnect_EnumSessionsCallback,&countonly,DPENUMSESSIONS_ALL|DPENUMSESSIONS_ASYNC);
	if(FAILED(hr))
	{
		return FALSE;
	}

	return TRUE;
}
	
BOOL FAR PASCAL CDP4Engine::DPConnect_EnumSessionsCallback( 
        LPCDPSESSIONDESC2 pdpsd,
        DWORD*            pdwTimeout,
        DWORD             dwFlags,
        VOID*             pvContext )
{ 
    if ( dwFlags & DPESC_TIMEDOUT )
        return FALSE; // Timed out, so stop the enumeration.
 
    // Found a good session
	if(*(BOOL*)pvContext)//Count only
	{
		DP4Engine.dwNumSessions++;
		return TRUE;
	}

	DP4Engine.Sessions[DP4Engine.dwEnumCounter].dwCurrentPlayers=pdpsd->dwCurrentPlayers;
	DP4Engine.Sessions[DP4Engine.dwEnumCounter].dwMaxPlayers=pdpsd->dwMaxPlayers;
	DP4Engine.Sessions[DP4Engine.dwEnumCounter].guidApplication=pdpsd->guidApplication;
	DP4Engine.Sessions[DP4Engine.dwEnumCounter].guidInstance=pdpsd->guidInstance;
	
	if(pdpsd->lpszPasswordA)
		strcpy(DP4Engine.Sessions[DP4Engine.dwEnumCounter].lpszPasswordA,pdpsd->lpszPasswordA);
	else
		ZeroMemory(DP4Engine.Sessions[DP4Engine.dwEnumCounter].lpszPasswordA,64);

	if(pdpsd->lpszSessionNameA)
		strcpy(DP4Engine.Sessions[DP4Engine.dwEnumCounter].lpszSessionNameA,pdpsd->lpszSessionNameA);
	else
		ZeroMemory(DP4Engine.Sessions[DP4Engine.dwEnumCounter].lpszSessionNameA,64);

	DP4Engine.dwEnumCounter++;

	return TRUE;
}
	
BOOL CDP4Engine::InitializeConnection(DWORD index)
{
	HRESULT hr;

	hr = DP4Engine.lpDP->InitializeConnection(DP4Engine.Connections[index].pConnection,0);
	if(FAILED(hr))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDP4Engine::EnumConnections()
{
	HRESULT hr;
	BOOL countonly;

	DP4Engine.dwNumConnections=0;
	countonly=TRUE;
	hr = DP4Engine.lpDP->EnumConnections(NULL,DPConnect_EnumConnectionsCallback,&countonly,0);
	if(FAILED(hr))
	{
		return FALSE;
	}

	if(DP4Engine.Connections)delete DP4Engine.Connections;
	DP4Engine.Connections=new st_DP4E_Connection[DP4Engine.dwNumConnections];
	countonly=FALSE;
	DP4Engine.dwEnumCounter=0;
	hr = DP4Engine.lpDP->EnumConnections(NULL,DPConnect_EnumConnectionsCallback,&countonly,0);
	if(FAILED(hr))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL FAR PASCAL CDP4Engine::DPConnect_EnumConnectionsCallback( 
        LPCGUID   pguidSP,
        VOID*     pConnection,
        DWORD     dwConnectionSize,
        LPCDPNAME pName,
        DWORD     dwFlags,
        VOID*     pvContext )
{
	HRESULT       hr;
    LPDIRECTPLAY4 pDP = NULL;
    VOID*         pConnectionBuffer = NULL;
    HWND          hWndListBox = (HWND)pvContext;
 
    // Create a IDirectPlay object.
    hr = CoCreateInstance(CLSID_DirectPlay,NULL,CLSCTX_ALL, IID_IDirectPlay4A,(VOID**)&pDP);
 	if(FAILED(hr))
	{
		// Error, stop enumerating
		return FALSE;
	}

    // Test the if the connection is available 
    // by attempting to initialize.
    // the connection
    hr = pDP->InitializeConnection( pConnection, 0 );
  	if(FAILED(hr))
    {
        if(pDP)
		{
			pDP->Release();
			pDP=NULL;
		}
        return TRUE; // Unavailable connection, keep enumerating
    }
 
    // Don't need the IDirectPlay interface any more, so release it.
    if(pDP)
	{
		pDP->Release();
		pDP=NULL;
	}
	
	// Found a good connection
	if(*(BOOL*)pvContext)//Count only
	{
		DP4Engine.dwNumConnections++;
		return TRUE;
	}
	
	//Get Connections
	DWORD dw=DP4Engine.dwEnumCounter;

	DP4Engine.Connections[dw].pguidSP=pguidSP;
	strcpy(DP4Engine.Connections[dw].pShortName,pName->lpszShortNameA);
	DP4Engine.Connections[dw].dwConnectionSize=dwConnectionSize;
	DP4Engine.Connections[dw].pConnection=new BYTE[dwConnectionSize];
	memcpy(DP4Engine.Connections[dw].pConnection,pConnection,dwConnectionSize);

	++DP4Engine.dwEnumCounter;

	return TRUE;
}
