#ifndef __DP4ENGINE_H
#define __DP4ENGINE_H

#include <windows.h>
#include <windowsx.h>
#include <dplay.h>
//link: dplayx.lib

struct st_DP4E_Connection
{
	LPCGUID   pguidSP;
    VOID*     pConnection;
    DWORD     dwConnectionSize;
    char	  pShortName[64];
};

struct st_DP4E_Session
{

    GUID  guidInstance;
    GUID  guidApplication;
	DWORD dwMaxPlayers;
    DWORD dwCurrentPlayers;
    char lpszSessionNameA[64];
    char lpszPasswordA[64];
};

struct st_DP4E_Player
{
	DPID id;
	char name[64];
};

typedef VOID (*MESSAGEPROC)(LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,DPID idFrom, DPID idTo);
typedef VOID (*CHATPROC)(LPSTR lpszText,DPID idFrom, DPID idToPlayer,DPID idToGroup);

class CDP4Engine
{
public:
	CDP4Engine();
	~CDP4Engine();

	static BOOL Initialize();

	static BOOL EnumConnections();
	static DWORD GetNumConnections();
	static st_DP4E_Connection *GetConnections();

	static BOOL InitializeConnection(DWORD index);

	static BOOL EnumSessions();
	static DWORD GetNumSessions();
	static st_DP4E_Session *GetSessions();

	static BOOL CreateSession(LPSTR pszName,DWORD dwMaxPlayers);
	static BOOL JoinSession(DWORD dwSessionIndex);

	static BOOL CreatePlayer(LPSTR lpszPlayerName);

	static BOOL EnumPlayers();
	static DWORD GetNumPlayers();
	static st_DP4E_Player *GetPlayers();

	static BOOL SendChatMessage(st_DP4E_Player *Player,LPSTR lpszMessage);
	static BOOL ReceiveMessages();

	static VOID SetMessageProc(MESSAGEPROC proc);
	static VOID SetSysMessageProc(MESSAGEPROC proc);
	static VOID SetChatProc(CHATPROC proc);

	static void Shutdown();

protected:
	static BOOL FAR PASCAL DPConnect_EnumConnectionsCallback( 
        LPCGUID   pguidSP,
        VOID*     pConnection,
        DWORD     dwConnectionSize,
        LPCDPNAME pName,
        DWORD     dwFlags,
        VOID*     pvContext );

	static BOOL FAR PASCAL DPConnect_EnumSessionsCallback( 
        LPCDPSESSIONDESC2 pdpsd,
        DWORD*            pdwTimeout,
        DWORD             dwFlags,
        VOID*             pvContext );

	static BOOL FAR PASCAL DPConnect_EnumPlayersCallback2(
		DPID dpId,
		DWORD dwPlayerType,
		LPCDPNAME lpName,
		DWORD dwFlags,
		LPVOID lpContext);

	static VOID HandleSystemMessage(LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,DPID idFrom, DPID idTo);
	static VOID HandleApplicationMessage(LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,DPID idFrom, DPID idTo);

	MESSAGEPROC MessageProc;
	MESSAGEPROC SysMessageProc;
	CHATPROC ChatProc;

	LPDIRECTPLAY4A lpDP;
	BOOL bHost;

	DWORD dwEnumCounter;

	st_DP4E_Connection *Connections;
	DWORD dwNumConnections;

    
	st_DP4E_Session *Sessions;
	DWORD dwNumSessions;

	st_DP4E_Player LocalPlayer;

	st_DP4E_Player *Players;
	DWORD dwNumPlayers;

};

#endif