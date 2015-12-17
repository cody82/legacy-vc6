//#define INITGUID
#include "common.h"
#include "player.h"
#include <windows.h>
#include "args.h"
#include <mmsystem.h>
#include <math.h>
#include "stream.h"
//#include <Afx.h>

#define _DIRECTX

#ifdef _DIRECTX
#include <dsound.h>

static LPDIRECTSOUND lpDirectSound = NULL;         
static LPDIRECTSOUNDBUFFER DSBuffer = NULL;
static bool DSInit = false;
DWORD BufPos = 0;
DWORD BufSize = 0;

#endif

DWORD PlayerThreadID = 0;
HANDLE PlayThreadHan = 0;                                          

// Copy of Args->OutMode, set in constructor
esOutputMode OutMode;
// Stuff for the wavfile renderer
HMMIO    hmmioOut;
MMIOINFO mmioinfoOut;
MMCKINFO ckOutRIFF;
MMCKINFO ckOut;

// A internal copy of Args->BufferSize(set by constructor)
unsigned long BufferSize;
// Number of queued buffers
long BufferCount, BuffersPlayed;
// Our critical section for wave out
//CRITICAL_SECTION cs;
// Needed for constructor
WAVEFORMATEX WAVFx, outFormatex;
// Our wavedevice handle for mmsystem output 
HWAVEOUT WaveDevice;
// Copy of the pointer given in the constructor

// Audio system events
// 0 = Break event,deactivates PlaySamples function and Header unprepare cb 
// 1 = Callback notification,set to true when new data is to be send
// 2 =
// 3 = DirectSound "decoding stopped" notification

bool MPAudioEvents[4];

bool Audio_Initialized = false;

// Executes user defined function and give it the sample data and information
bool ExecuteCallback(void *Data, DWORD len)  
{
    if (((Args->UseHdrCB) || (Args->OutputMode == omCallback)) && (Args->BufferCB)) 
    {
        unsigned long TSampleRate = Args->SampleRate;
        unsigned long TSize = len;
        long TBits = Args->AudioBits;
        long TChannels = Args->Channels;        
        try
        {
          return Args->BufferCB(Data, TBits, TChannels, TSampleRate, TSize, Args->OutCBData);
        }
        catch  (...)
        {
            int kkk = 1;
            return false;
        }
    } else 
        return true;
}

void ProcessAudioMessages()
{
    MSG msg;
    HWAVEOUT Wave;
    WAVEHDR *Wh; 
    HGLOBAL WHMemHnd,
                    DataMemHnd;
    while (PeekMessage(&msg, (HWND) -1, 0, 0, PM_NOREMOVE)) 
    {
        GetMessage(&msg,  (HWND) NULL,  0, 0);
        if (msg.message == MM_WOM_DONE)
        {
            //PeekMessage(&msg, (HWND) -1, MM_WOM_DONE, MM_WOM_DONE, PM_REMOVE);  
            Wave = (HWAVEOUT) msg.wParam;
            Wh = (WAVEHDR *) msg.lParam;
            WHMemHnd=GlobalHandle(Wh);
        
            ExecuteCallback(Wh->lpData, Wh->dwBufferLength);
            DataMemHnd=GlobalHandle(Wh->lpData);
            waveOutUnprepareHeader((HWAVEOUT)Wave, Wh, sizeof(WAVEHDR));
            GlobalUnlock(DataMemHnd);
            GlobalUnlock(WHMemHnd);
            GlobalFree(DataMemHnd);
            GlobalFree(WHMemHnd);
            BufferCount--;          
        } 
        else 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }    
}

#ifdef _DIRECTX

volatile LPVOID DoubleBuffer = NULL;
volatile DWORD  DXBufferSize = 0;
volatile DWORD  DXBufferPos = 0;
volatile HANDLE ReadyEvent = NULL; 
volatile HANDLE StoppedEvent = NULL; 
CRITICAL_SECTION BufferAccess;
volatile UINT  Timer = 0;
volatile bool  m_fPlayingDX, PauseDX;
volatile DWORD m_cbBufOffset;

bool WriteToBuffer(LPVOID buf, DWORD len) 
{
    EnterCriticalSection(&BufferAccess);
    if (DXBufferPos + len >= DXBufferSize) 
    {
        LeaveCriticalSection(&BufferAccess);
        return false;
    }
    MoveMemory((void *)((char *)DoubleBuffer + DXBufferPos), buf, len);
    DXBufferPos += len;
    if (DXBufferSize - DXBufferPos < Args->BufferSize) ResetEvent(ReadyEvent);
    LeaveCriticalSection(&BufferAccess);
    return true;
}

_inline unsigned char GetSilenceChar()
{
    if (Args->AudioBits == 16) 
        return 0;
    else 
        return 0x80;
}

bool WriteSilence(DWORD size) 
{
    unsigned char sil_char = GetSilenceChar();
    
    EnterCriticalSection(&BufferAccess);
    HRESULT hr;
    LPBYTE lpbuf1 = NULL;
    LPBYTE lpbuf2 = NULL;
    DWORD dwsize1 = 0;
    DWORD dwsize2 = 0;
    DWORD dwbyteswritten1 = 0;
    DWORD dwbyteswritten2 = 0;
    
    // Lock the sound buffer
    try 
    {
        hr = DSBuffer->Lock (m_cbBufOffset, size, (void **)&lpbuf1, &dwsize1, (void **)&lpbuf2, &dwsize2, 0);
        if (hr != DS_OK) 
            throw 1;
        memset(lpbuf1, sil_char, dwsize1);
        if (lpbuf2) 
            memset(lpbuf2, sil_char, dwsize2);
        else dwsize2 = 0;
        
        DSBuffer->Unlock (lpbuf1, dwsize1, lpbuf2, dwsize2);
        m_cbBufOffset = (m_cbBufOffset + dwsize1 + dwsize2) % DXBufferSize;
    }
    catch (...)
    {
        LeaveCriticalSection(&BufferAccess);
        return false;
    }        
    LeaveCriticalSection(&BufferAccess);
    return true;
}

DWORD GetMaxWriteSize (void)
{
    DWORD dwWriteCursor, dwPlayCursor, dwMaxSize;
    
    // Get current play position
    dwWriteCursor = dwPlayCursor = 0;
    if (DSBuffer->GetCurrentPosition(&dwPlayCursor, &dwWriteCursor) == DS_OK)
    {
        if (m_cbBufOffset <= dwPlayCursor)
            dwMaxSize = dwPlayCursor - m_cbBufOffset;
        else // (m_cbBufOffset > dwPlayCursor)
            dwMaxSize = DXBufferSize - m_cbBufOffset + dwPlayCursor;
    }
    else
    {
        // GetCurrentPosition call failed
        LastError = peOutputError;
        throw 1;
    }
    return (dwMaxSize);
}

bool SendToDX(DWORD size)
{
    EnterCriticalSection(&BufferAccess);
    HRESULT hr;
    LPBYTE lpbuf1 = NULL;
    LPBYTE lpbuf2 = NULL;
    DWORD dwsize1 = 0;
    DWORD dwsize2 = 0;
    DWORD dwbyteswritten1 = 0;
    DWORD dwbyteswritten2 = 0;
    
    // Lock the sound buffer
    try 
    {
        hr = DSBuffer->Lock (m_cbBufOffset, size, (void **)&lpbuf1, &dwsize1, (void **)&lpbuf2, &dwsize2, 0);
        if (hr != DS_OK) 
            throw 1;
        MoveMemory(lpbuf1, DoubleBuffer, dwsize1);
        if (lpbuf2) 
            MoveMemory(lpbuf2, (void *)((char *)DoubleBuffer + dwsize1), dwsize2);
        else 
            dwsize2 = 0;
        MoveMemory(DoubleBuffer, (void *)((char *)DoubleBuffer + dwsize1 + dwsize2), DXBufferPos - (dwsize1 + dwsize2));
        DXBufferPos -= dwsize1 + dwsize2;
        DSBuffer->Unlock (lpbuf1, dwsize1, lpbuf2, dwsize2);
        m_cbBufOffset = (m_cbBufOffset + dwsize1 + dwsize2) % DXBufferSize;
    }
    catch (...)
    {
        LeaveCriticalSection(&BufferAccess);
        return false;
    }        
    LeaveCriticalSection(&BufferAccess);
    if (DXBufferSize - DXBufferPos >= Args->BufferSize) SetEvent(ReadyEvent);
    return true;
}

void StopDX();
void CALLBACK TimeProcDX(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

void StartDX()
{
    StopDX();
    
    // Cue for playback if necessary
    /*if (!m_fCued)
    {
    Cue ();
    }
    */
    DSBuffer->SetCurrentPosition(0);
    WriteSilence(DXBufferSize);    
    // Begin DirectSound playback
    m_cbBufOffset = 0;
    HWND OldFocus = GetFocus();
    SetFocus(Args->wnd);
    HRESULT hr = DSBuffer->Play (0, 0, DSBPLAY_LOOPING);    
    SetFocus(OldFocus);
    if (hr == DS_OK)
    {
        Timer = timeSetEvent(floor(Frame2ms()) - 1, 0,  &TimeProcDX, 0, TIME_ONESHOT | TIME_CALLBACK_FUNCTION);
        if (!Timer) 
        {
            int i = GetLastError();
            LastError = peOutputError;           
            throw 1;
        }
        
        // Playback begun, no longer cued
        m_fPlayingDX = TRUE;
        //m_fCued = FALSE;
    }
    else
    {
        LastError = peOutputError;
        throw 1;
    }
}

void StopDX()
{
    if (m_fPlayingDX)
    {
        // Stop DirectSound playback
        // Delete Timer object
        MPAudioEvents[3] = 1;        
        if (Timer) 
            timeKillEvent(Timer);
        Timer = 0;
        DSBuffer->Stop ();        
        m_fPlayingDX = FALSE;
    }
}

void CALLBACK TimeProcDX(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    if (Timer) {
        timeKillEvent(Timer);
        Timer = 0;
    }
    if (!MPAudioEvents[3] || DXBufferPos)
    {   // All of sound not played yet, send more data to buffer
        DWORD dwFreeSpace = GetMaxWriteSize ();
        
        // Determine free space in sound buffer
        if (dwFreeSpace)
        {   // See how much wave data remains to be sent to buffer
            EnterCriticalSection(&BufferAccess);
            DWORD dwDataRemaining;
            if (PauseDX)  
                dwDataRemaining = 0;
            else
                dwDataRemaining = DXBufferPos;
            if (dwDataRemaining == 0)
            {   // All wave data has been sent to buffer
                // Fill free space with silence
                LeaveCriticalSection(&BufferAccess);
                if (WriteSilence (dwFreeSpace) == false)
                {   // Error writing silence data
                    LastError = peOutputError;
                    throw 1;
                }                
            }
            else 
            {
                if (dwDataRemaining >= dwFreeSpace)
                {   // Enough wave data remains to fill free space in buffer
                    // Fill free space in buffer with wave data
                    LeaveCriticalSection(&BufferAccess);
                    if (SendToDX(dwFreeSpace) == false)
                    {   // Error writing wave data
                        LastError = peOutputError;
                        throw 1;
                    }
                }
                else
                {   // Some wave data remains, but not enough to fill free space
                    // Send wave data to buffer, fill remainder of free space with silence
                    LeaveCriticalSection(&BufferAccess);
                    if (SendToDX(dwDataRemaining))
                    {
                        if (WriteSilence (dwFreeSpace - dwDataRemaining) == false)
                        {
                            // Error writing silence data
                            LastError = peOutputError;
                            throw 1;
                        }
                    }
                    else
                    {   // Error writing wave data
                        LastError = peOutputError;
                        throw 1;
                    }
                }
            }
        }        
        Timer = timeSetEvent(floor(Frame2ms()) - 1, 0,  TimeProcDX, 0, TIME_ONESHOT | TIME_CALLBACK_FUNCTION);
    }
    else
    {
        // All of sound has played, stop playback
        StopDX ();
        SetEvent(StoppedEvent);
    } 
} 

#endif

const IID IID_IDirectSound = {0x279AFA83, 0x4981, 0x11CE, {0xA5, 0x21, 0x00, 0x20, 0xAF, 0x0B, 0xE5, 0x60}};
const IID CLSID_DirectSound = {0x47d4d946, 0x62e8, 0x11cf, {0x93, 0xbc, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0}};

bool Init_MPAudio(){
    OutMode = Args->OutputMode;
    BuffersPlayed = 0;
    if (OutMode==omCallback) {
        if ((!Args->BufferCB) || (!Args->OutActionCB)) 
        {
            LastError = peOutputError;
            throw 1;
        }
        if (!Args->OutActionCB(true, Args->OutCBData)) 
        {
            LastError = peOutputError;
            throw 1;
        }
    }
    // Output via wave mapper
    if(OutMode==omMMSystem) {
        HGLOBAL CBMem;
        // Get device capatibilities to detect sound
        if (!waveOutGetNumDevs()) {
            LastError = peOutputError;
            throw 1;
        } 
        // Initialize waveout formatex structure with the options
        BufferCount = 0;
        outFormatex.wFormatTag        = WAVE_FORMAT_PCM;
        outFormatex.wBitsPerSample    = Args->AudioBits;
        outFormatex.nChannels         = Args->Channels;
        if (Args->SampleRate > 44100)
        {
            outFormatex.nSamplesPerSec    = 44100;
        }
        else
            outFormatex.nSamplesPerSec    = Args->SampleRate;
        
        outFormatex.nAvgBytesPerSec   = outFormatex.nSamplesPerSec*Args->Channels*(Args->AudioBits/8);
        outFormatex.nBlockAlign       = Args->Channels*(Args->AudioBits/8);
        
        // Initialize our callback buffer, preventing that the user have
        // to allocate one in his callback function(gains speed ;)
        BufferSize = Args->BufferSize; 
        
        for(int i=0;i<4;i++) MPAudioEvents[i]=false;
        // Open the device
        MMRESULT res=waveOutOpen(&WaveDevice,(UINT)Args->AudioDevice,&outFormatex, PlayerThreadID, 0, CALLBACK_THREAD);
        if(res!=MMSYSERR_NOERROR)
        {
            LastError = peOutputError;
            throw 1;
        }
        // Reset the wavedevice
        waveOutReset(WaveDevice);
        ProcessAudioMessages();
        // Sleep a bit
        Sleep(77);
        if (Args->UseHdrCB) 
        {
            if ((!Args->OutActionCB) || (!Args->OutActionCB(true, Args->OutCBData))) 
            {
                Args->UseHdrCB = false;
            }
        }        
        Audio_Initialized = true;
        return true;
    }
#ifdef _DIRECTX
    if (OutMode==omDirectSound) 
	{
        DSInit = false;
        HRESULT hr = CoInitialize(NULL);
        if ((hr != E_INVALIDARG) && (hr !=  E_OUTOFMEMORY) && (hr != E_UNEXPECTED))
        {
        }
        else        
        {
            LastError = peOutputError;
            throw 1;
        }
        try 
        {
            lpDirectSound = NULL;
            hr = CoCreateInstance(CLSID_DirectSound, NULL, CLSCTX_INPROC_SERVER, IID_IDirectSound,(void **) &lpDirectSound);
            if (hr != S_OK) {
                LastError = peOutputError;
                throw 1;
            }
            hr = lpDirectSound->Initialize(NULL);
		//	hr = DirectSoundCreate(NULL, &lpDirectSound, NULL);
            if (hr != S_OK) {
                LastError = peOutputError;
                throw 1;
            }
            hr = lpDirectSound->SetCooperativeLevel(Args->wnd, DSSCL_PRIORITY);
            WAVEFORMATEX wf;     
            DSBUFFERDESC dsbdesc;     
            // Set up wave format structure. 
            memset(&wf, 0, sizeof(WAVEFORMATEX)); 
            wf.wFormatTag = WAVE_FORMAT_PCM;     
            wf.nChannels = Args->Channels; 
            wf.nSamplesPerSec = Args->SampleRate;     
            wf.nBlockAlign = Args->Channels*(Args->AudioBits/8);
            wf.nAvgBytesPerSec = Args->SampleRate*Args->Channels*(Args->AudioBits/8);
            wf.wBitsPerSample = Args->AudioBits;
            wf.cbSize = 0;
            
            BufSize = Args->Buffers * Args->BufferSize;
            BufPos = 0;
            
            memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); 
            dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
			//DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER
            dsbdesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLVOLUME;
            dsbdesc.dwBufferBytes = BufSize; 
            dsbdesc.lpwfxFormat = &wf;
            
            hr = lpDirectSound->CreateSoundBuffer(&dsbdesc, &DSBuffer, NULL);
            if(DS_OK == hr) 
            { 
                Audio_Initialized = true;            
                
                InitializeCriticalSection(&BufferAccess); 
                ReadyEvent = CreateEvent(NULL, false, true, NULL);
                StoppedEvent = CreateEvent(NULL, false, true, NULL);
                DoubleBuffer = malloc(BufSize);
                DXBufferSize = BufSize;
                DXBufferPos = 0;
                PauseDX = false;
                Timer = 0;
                MPAudioEvents[3] = 0;
                m_fPlayingDX = false;
                m_cbBufOffset = 0;
                if (Args->UseHdrCB) 
                {
                    if ((!Args->OutActionCB) || (!Args->OutActionCB(true, Args->OutCBData))) 
                    {
                        Args->UseHdrCB = false;
                    }
                }
                return true;
            }
            LastError = peOutputError;
            throw 1;
        } 
		catch (...) 
        {
            lpDirectSound->Release();
            lpDirectSound = NULL;
            LastError = peOutputError;

            if (DSBuffer) 
                DSBuffer->Release();
            DSBuffer = NULL;
            if (lpDirectSound) 
                lpDirectSound->Release();
            lpDirectSound = NULL;
            if (DoubleBuffer) 
            {
                free(DoubleBuffer);
                DoubleBuffer = NULL;                
            }
            if (ReadyEvent) 
            {
                CloseHandle(ReadyEvent);
                ReadyEvent = NULL;
            }
            if (StoppedEvent) 
            {
                CloseHandle(StoppedEvent);
                StoppedEvent = NULL;
            }
            throw 1;
        }
    }
#endif
    // WAV file output
    if(OutMode==omWaveFile) 
    {
        // Open our wavefile
        if(!(hmmioOut=mmioOpen(Args->OutName,NULL,MMIO_ALLOCBUF|MMIO_WRITE|MMIO_CREATE))) {
            LastError = peOutputError;
            throw 1;
        }
        // Set the header in the structure
        ckOutRIFF.fccType=mmioFOURCC('W', 'A', 'V', 'E');
        ckOutRIFF.cksize=0;
        // Create chunk
        if(mmioCreateChunk(hmmioOut,&ckOutRIFF,MMIO_CREATERIFF)!=MMSYSERR_NOERROR) {
            LastError = peOutputError;
            throw 1;
        }
        // Now set our audio options...
        WAVFx.wFormatTag        = WAVE_FORMAT_PCM;
        WAVFx.wBitsPerSample    = Args->AudioBits;
        WAVFx.nChannels         = Args->Channels;
        WAVFx.nSamplesPerSec    = Args->SampleRate;
        WAVFx.nAvgBytesPerSec   = WAVFx.nSamplesPerSec*WAVFx.nChannels*WAVFx.wBitsPerSample/8;
        WAVFx.nBlockAlign       = WAVFx.nChannels*WAVFx.wBitsPerSample/8;
        WAVFx.cbSize          = 0;
        ckOut.ckid=mmioFOURCC('f', 'm', 't', ' ');
        ckOut.cksize=sizeof(WAVFx);
        // ...and store it
        if(mmioCreateChunk(hmmioOut,&ckOut,0)!=MMSYSERR_NOERROR) {
            LastError = peOutputError;
            throw 1;
        }
        // Write the stuff 
        if(mmioWrite(hmmioOut,(HPSTR)&WAVFx,sizeof(WAVFx))!=sizeof(WAVFx)){
            LastError = peOutputError;
            throw 1;
        }
        if(mmioAscend(hmmioOut,&ckOut,0)!=MMSYSERR_NOERROR) {
            LastError = peOutputError;
            throw 1;
        }
        ckOut.ckid=mmioFOURCC('d', 'a', 't', 'a');
        ckOut.cksize=0;
        if(mmioCreateChunk(hmmioOut,&ckOut,0)!=MMSYSERR_NOERROR){
            LastError = peOutputError;
            throw 1;
        }
        /*
        if (MMRESULT res = mmioGetInfo(hmmioOut, &mmioinfoOut,0)) {
        throw 1;
    }*/
        Audio_Initialized = true;
        if (Args->UseHdrCB) 
        {
            if ((!Args->OutActionCB) || (!Args->OutActionCB(true, Args->OutCBData))) 
            {
                Args->UseHdrCB = false;
            }
        }
        return true;
    }
    return false;
}

// Returns the buffer load in percent
long GetBufferload(){
    if(OutMode==omMMSystem){
        unsigned long result;
        result=((BufferCount-1) * Args->BufferSize)/((Args->Buffers * Args->BufferSize)/100);
        if(result>=100) result=0;if(result<=0) result=0;
        return result;
    };
#ifdef _DIRECTX
    if (OutMode == omDirectSound) 
    {
        return DXBufferPos * 100 / DXBufferSize;
    }
#endif
    return 0;
}

// Store "buf" with "len" size in buffer  
long PlaySamples(unsigned char *buf, long len){
    // Realtime sound output 
    //if (Args->CurrentPos < Args->StartFrame) return len;
    if (BuffersPlayed == 0) 
    {
        BuffersPlayed++;
        return len;
    }
    if (OutMode==omCallback) 
    {
        if ((MPAudioEvents[0]) || (MPAudioEvents[2])) return -1; 
        if (!ExecuteCallback(buf, len)) 
        {
            LastError = peOutputError;
            throw 1;
        }
        BuffersPlayed++;
        return len;
    }
    if(OutMode==omMMSystem)
    {
        LPWAVEHDR WaveHeader; 
        HGLOBAL WHMemHnd,DataMemHnd;
        // Return on break flag
        if ((MPAudioEvents[0]) || (MPAudioEvents[2])) return -1; 
        // If callback flag set, execute it
        // This copies the sampledata to our callback buffer and sets
        // event 1(Execute callback,please) which will be handled by 
        // PlaySamples() because we can't execute the callback directly from here.
        if(Args->UseHdrCB) 
        {
            ExecuteCallback(buf, len);
        } 
        // If buffer is full, wait
        ProcessAudioMessages();
        while (BufferCount >= Args->Buffers) 
        {
            Sleep(77);
            if ((MPAudioEvents[0]) || (MPAudioEvents[2])) return -1;
            ProcessAudioMessages();
        }
        // Allocate "len" size buffer, and copy "buf" in it
        WHMemHnd = GlobalAlloc(GMEM_MOVEABLE,sizeof(WAVEHDR));
        DataMemHnd=GlobalAlloc(GMEM_MOVEABLE,len);
        WaveHeader=(LPWAVEHDR)GlobalLock(WHMemHnd);
        WaveHeader->lpData=(LPSTR)GlobalLock(DataMemHnd);
        try 
        {
          CopyMemory(WaveHeader->lpData,buf,len);
        }
        catch (...)
        {
            int kkk = 1;
        }
        WaveHeader->dwBufferLength=len;
        WaveHeader->dwFlags=0;
        // Prepare the header for output
        // EnterCriticalSection(&cs);
        MMRESULT Res;
        try 
        {
          Res=waveOutPrepareHeader(WaveDevice,WaveHeader,sizeof(WAVEHDR));
        }
        catch (...)
        {
            int kkk = 1;
        }
        if(Res) 
        {
            GlobalFree(DataMemHnd);
            GlobalFree(WHMemHnd);  
            // LeaveCriticalSection(&cs);
            LastError = peOutputError;
            throw 1;            
        }
        // Send it to mmsystem
        Res = waveOutWrite(WaveDevice,WaveHeader,sizeof(WAVEHDR));
        if(Res) {
            GlobalFree(DataMemHnd);
            GlobalFree(WHMemHnd);  
            // LeaveCriticalSection(&cs);
            LastError = peOutputError;
            throw 1;            
        }
        BufferCount++;
        BuffersPlayed++;
        //LeaveCriticalSection(&cs);        
        return(len);
    }
#ifdef _DIRECTX
    if (OutMode == omDirectSound) {
        if (!m_fPlayingDX) StartDX();
        if ((MPAudioEvents[0]) || (MPAudioEvents[2])) return -1; 
        // If callback flag set, execute it
        if(MPAudioEvents[1]){
            // Send data to user 
            if(Args->UseHdrCB) ExecuteCallback(buf, len);
            // Reset event
            MPAudioEvents[1]=false;
        }
        while (!WriteToBuffer(buf, len)) 
        {
            while (!MPAudioEvents[3]) 
                if (WaitForSingleObject(ReadyEvent, 50) == WAIT_OBJECT_0) break;
                if (MPAudioEvents[3]) break;
        }
    }
#endif
    if(OutMode == omWaveFile) 
    {
        unsigned long i;
        if ((MPAudioEvents[0]) || (MPAudioEvents[2])) return -1; 
        // If callback flag set, execute it
        if(MPAudioEvents[1]){
            // Send data to user 
            if(Args->UseHdrCB) ExecuteCallback(buf, len);
            // Reset event
            MPAudioEvents[1]=false;
        }         
        // Write the buffer to file
        i = mmioWrite(hmmioOut, (const char *) buf, len);
        Sleep(20);
        return i;
        /*for(i=0; i<len; i++) {
        if(mmioinfoOut.pchNext == mmioinfoOut.pchEndWrite){
        mmioinfoOut.dwFlags |= MMIO_DIRTY;
        if(mmioAdvance(hmmioOut, &mmioinfoOut, MMIO_WRITE)!=MMSYSERR_NOERROR) {
        throw 1;
        }
        }
        *mmioinfoOut.pchNext = buf[i];
        mmioinfoOut.pchNext++;
    }*/
        BuffersPlayed++;
        return len;
    }
    // Return -1 because no outmode fitted
    return -1;
} 

// Pauses the output of sample data using break event
void Pause_Audio(){
    // Wave mapper output 
    if(OutMode==omMMSystem)
    {
        MPAudioEvents[0]=true;
        waveOutPause(WaveDevice);
    } 
#ifdef _DIRECTX
    if (OutMode == omDirectSound) 
    {
        PauseDX = 1;        
    }
#endif
}

// Resume paused audio output
void Resume_Audio(){
    // Wave mapper output
    if(OutMode==omMMSystem) {
        MPAudioEvents[0]=false; 
        waveOutRestart(WaveDevice);
    } 
#ifdef _DIRECTX
    if (OutMode == omDirectSound) 
    {
        PauseDX = 0;
    }
#endif
    
}

// Reset mmsystem
void Reset_Audio(){
    if(OutMode==omMMSystem){
        waveOutReset(WaveDevice);
    }
}

// Return count of queued buffers
unsigned long QueuedBuffers(){
    if (OutMode==omMMSystem) return BufferCount;
    return 0;
}

// Waits until last buffer is played
void FinishBuffer()
{
    if (OutMode==omMMSystem) 
    {
        ProcessAudioMessages();
        while(BufferCount) 
        {
            Sleep(77);
            ProcessAudioMessages();
        }
    }
#ifdef _DIRECTX
    if (OutMode == omDirectSound) 
    {
        MPAudioEvents[3] = 1;
        WaitForSingleObject(StoppedEvent, INFINITE);
    }
#endif
}

bool Audio_CanSetVolume(bool *Separate) {
    if (Args->OutputMode == omMMSystem) {
        
        WAVEOUTCAPS pwoc;
        if (waveOutGetDevCaps(Args->AudioDevice, &pwoc, sizeof(pwoc)) == MMSYSERR_NOERROR) {
            *Separate = pwoc.dwSupport & WAVECAPS_LRVOLUME;
            return (pwoc.dwSupport & WAVECAPS_VOLUME);
        } else 
            return false;
    }
#ifdef _DIRECTX
    if (Args->OutputMode == omDirectSound) {
        Separate = false;
        return true;
    }
#endif
    return false;
}

bool Audio_SetVolume(unsigned long Volume) {
    if (Args->OutputMode == omMMSystem) {
        if (Audio_Initialized) {
            return (waveOutSetVolume(WaveDevice, Volume) == MMSYSERR_NOERROR);
        } else  {
            HWAVEOUT phwo;
            WAVEFORMATEX outFormatex;
            outFormatex.wFormatTag        = WAVE_FORMAT_PCM;
            outFormatex.wBitsPerSample    = Args->AudioBits;
            outFormatex.nChannels         = Args->Channels;
            outFormatex.nSamplesPerSec    = Args->SampleRate;
            outFormatex.nAvgBytesPerSec   = Args->SampleRate*Args->Channels*(Args->AudioBits/8);
            outFormatex.nBlockAlign       = Args->Channels*(Args->AudioBits/8);
            outFormatex.cbSize = 0;
            if (waveOutOpen(&phwo, Args->AudioDevice, &outFormatex, 0, 0, CALLBACK_NULL | WAVE_ALLOWSYNC) == MMSYSERR_NOERROR) {
                bool res;
                res = (waveOutSetVolume(phwo, Volume) == MMSYSERR_NOERROR);
                waveOutClose(phwo);
                if (!res) LastError = peOutputError;
                return res;
            } else 
                return false;        
        }
    }
#ifdef _DIRECTX
    if (Args->OutputMode == omDirectSound) {
        if (DSBuffer) 
        {
            int X = (Volume & 0xFFFF0000) >> 16;
            X = (-10000/(log10(1) - log10(65536)))*(log10(X + 1) - log10(65536));
            DSBuffer->SetVolume(X);
            return true;
        }
        else {
            LastError = peIncorrectMode;
            return false;
        }
    }
#endif    
    return false;
}

bool Audio_GetVolume(unsigned long *Volume) {
    if (Args->OutputMode == omMMSystem) {
        if (Audio_Initialized) {
            return (waveOutGetVolume(WaveDevice, Volume) == MMSYSERR_NOERROR);
        } else  {
            HWAVEOUT phwo;
            WAVEFORMATEX outFormatex;
            outFormatex.wFormatTag        = WAVE_FORMAT_PCM;
            outFormatex.wBitsPerSample    = Args->AudioBits;
            outFormatex.nChannels         = Args->Channels;
            outFormatex.nSamplesPerSec    = Args->SampleRate;
            outFormatex.nAvgBytesPerSec   = Args->SampleRate*Args->Channels*(Args->AudioBits/8);
            outFormatex.nBlockAlign       = Args->Channels*(Args->AudioBits/8);
            outFormatex.cbSize = 0;
            if(waveOutOpen(&phwo, Args->AudioDevice, &outFormatex, 0, 0, CALLBACK_NULL | WAVE_ALLOWSYNC) == MMSYSERR_NOERROR) {
                bool res;
                res = (waveOutGetVolume(phwo, Volume) == MMSYSERR_NOERROR);
                waveOutClose(phwo);
                return res;
            } else 
                return false;        
        }
    }
#ifdef _DIRECTX
    if (Args->OutputMode == omDirectSound) {
        if (DSBuffer) {
            DSBuffer->GetVolume((long *)Volume);
            double xxx = (-10000/(log10(1) - log10(65536)));
            *Volume = 65536 * pow(10,(long) *Volume /xxx) - 1;
            
            *Volume = *Volume << 16 | *Volume; 
            return true;
        }
        else {
            LastError = peIncorrectMode;
            return false;
        }
    }
#endif    
    return false;
}

// Destructor
bool Done_MPAudio(){
    // Wave mapper output
    Audio_Initialized = false;
    if (OutMode==omCallback)
    {
        if (!Args->OutActionCB(false, Args->OutCBData)) 
        {
            return true;
        }
    }
    if(OutMode==omMMSystem) 
    {
        try
        {
            while (waveOutClose (WaveDevice) == WAVERR_STILLPLAYING) 
            {
                ProcessAudioMessages();
                Sleep(77);
            }
            ProcessAudioMessages();
        }
        catch (...) {/* ignore all possible errors */}
        if (Args->UseHdrCB && Args->OutActionCB) Args->OutActionCB(false, Args->OutCBData);
        WaveDevice=NULL;
        BufferCount=0;
    }
#ifdef _DIRECTX
    if (OutMode == omDirectSound) 
    {
        StopDX();
        if (DSBuffer) DSBuffer->Release();
        DSBuffer = NULL;
        if (lpDirectSound) lpDirectSound->Release();
        lpDirectSound = NULL;
        if (DoubleBuffer) 
            free(DoubleBuffer);
        if (ReadyEvent) 
            CloseHandle(ReadyEvent);
        if (StoppedEvent) 
            CloseHandle(StoppedEvent);
        DeleteCriticalSection(&BufferAccess); 
        if (Args->UseHdrCB && Args->OutActionCB) Args->OutActionCB(false, Args->OutCBData);
        CoUninitialize();
    }
#endif
    // Wav file output
    if(OutMode==omWaveFile) 
    {
        if (Args->UseHdrCB && Args->OutActionCB) Args->OutActionCB(false, Args->OutCBData);

        if(mmioFlush(hmmioOut,MMIO_EMPTYBUF)) 
        {
            return true;
        }
        /*mmioinfoOut.dwFlags|=MMIO_DIRTY;
        if(mmioSetInfo(hmmioOut,&mmioinfoOut,0)!=MMSYSERR_NOERROR){
        //throw 1;
        return;
    }*/
        if(mmioAscend(hmmioOut,&ckOut,0)!=MMSYSERR_NOERROR)
        {
            //throw 1;
            return true;
        }
        if(mmioAscend(hmmioOut,&ckOutRIFF,0)!=MMSYSERR_NOERROR)
        {
            //throw 1;
            return true;
        }
        if(mmioClose(hmmioOut,0)!=MMSYSERR_NOERROR) 
        {
            //throw 1;
            return true;
        }
        return true;
    }
    return true;
}