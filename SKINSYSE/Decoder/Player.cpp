#include "common.h"
#include "args.h"
#include "player.h"
#include "helper.h"
#include "stream.h"
#include "audio.h"
#include <stdio.h>
#include <process.h>
#include "decoder.h"

#define _DIRECTX

MPArgs *Args;
struct frame fr;
esPlayerError LastError = peNoError;
HANDLE ThreadQueueEvent = NULL;
HANDLE SeekEvent, SeekEvent2, FinishEvent;
unsigned long NewSeekPosition;

int xxx = 0;

void HardAudioReset(MPPlayer *ptr)
{
    FinishBuffer();
    try {
        Done_MPAudio();
    }
    catch(...) {}
    try {
        Init_MPAudio();
    }
    catch(...) {
        LastError = peOutputError;            
        throw 1;            
        return;
    }
}

void SynthesisFilterInit()
{
    typedef int (*func)(real *,int,unsigned char * , int *);
    typedef int (*func_mono)(real *,unsigned char * , int *);
    
    static func funcs[2][4] = 
    {
        { synth_1to1,
            synth_2to1,
            synth_4to1,
            synth_ntom} ,
        { synth_1to1_8bit,
        synth_2to1_8bit,
        synth_4to1_8bit ,
        synth_ntom_8bit}
    };
    
    static func_mono funcs_mono[2][2][4] = 
    {
        { { synth_1to1_mono2stereo ,
            synth_2to1_mono2stereo ,
            synth_4to1_mono2stereo ,
            synth_ntom_mono2stereo } ,
        { synth_1to1_8bit_mono2stereo ,
        synth_2to1_8bit_mono2stereo ,
        synth_4to1_8bit_mono2stereo ,
        synth_ntom_8bit_mono2stereo } } ,
        { { synth_1to1_mono ,
        synth_2to1_mono ,
        synth_4to1_mono ,
        synth_ntom_mono } ,
        { synth_1to1_8bit_mono ,
        synth_2to1_8bit_mono ,
        synth_4to1_8bit_mono ,
        synth_ntom_8bit_mono } }
    };
         
    fr.synth = (synthProc) funcs[Args->Force8bit][fr.down_sample];
    fr.synth_mono = funcs_mono[Args->ForceMono][Args->Force8bit][fr.down_sample];
    
    fr.block_size = 128 >> (Args->ForceMono + Args->Force8bit + fr.down_sample);
    
    if(Args->Force8bit) 
    {
        Args->AudioBits=8;
        make_conv16to8_table();
    }    
}

unsigned long __stdcall PlayThread(void *ptr) 
{
    MMRESULT mmRes;
    //int clip;
    long numframes = -1;
    MSG msg;
    PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
    try 
    {
        Init_MPAudio();
    }
    catch(...)
    {
        LastError = peOutputError;
        SetEvent(ThreadQueueEvent);
        SetEvent(FinishEvent);
        ExitThread(0);
        return 0;
    }
    SetEvent(ThreadQueueEvent);
    long OldRate = 0, NewRate = 0;
    int OldBits = 0, OldChannel = 0;
    //unsigned long left,right;
    unsigned long FrameNum = 0;
    long OldScaleFactor = 32768;
    MPPlayer *Player = (MPPlayer *)ptr;    
    Args->IsVBR = false;
    try 
    {
        while(numframes) 
        {
            if (WaitForSingleObject(SeekEvent, 0) == WAIT_OBJECT_0) 
            {
                if (Args->OutputMode == omMMSystem) 
                {
                    mmRes = waveOutReset(WaveDevice);
                    ProcessAudioMessages();
                    BufferCount = 0;
                }
                if (Seek_Stream(NewSeekPosition))
                    NewSeekPosition = -1;
                else
                    NewSeekPosition = 0;
                SetEvent(SeekEvent2);
            }
            ProcessAudioMessages();
            OldBits = fr.bitrate_index;
            try
            {
                once_more:  
                BOOL Res = ReadFrame();
                if (Res == -2) 
                    break;
                if(Res) Args->CurrentPos++;
                /*if(Args->CurrentPos > MaxFrames) 
                    break; */
                if(Player->UserBreak) 
                {
                    break;
                }
                if (Args->CurrentPos < Args->StartFrame) 
                {
                    continue;
                }
                
                if (Args->CurrentPos > Args->EndFrame) 
                {
                    break; 
                }
                if(!Res && Res !=-2) goto once_more;            
                numframes--;
                if (OldScaleFactor != Args->ScaleFactor) 
                {
                    make_decode_tables(Args->ScaleFactor);
                    OldScaleFactor = Args->ScaleFactor;
                }
                if (fr.header_change)
                {
                    int reset_audio=0;
                    if ((Args->SampleRate >= 48000)  && (Args->OutputMode == omMMSystem)) 
                    {
                        fr.down_sample = 1;
                        Args->SampleRate = Args->SampleRate/2;
                        Args->ForceFreq = Args->SampleRate;
                        Init_MPEGDecoder(fr.down_sample);
                        
                    }
                    if(Args->ForceFreq < 0) 
                    {
                        if(Args->SampleRate != freqs[fr.sampling_frequency>>(fr.down_sample)]) 
                        {
                            Args->SampleRate = freqs[fr.sampling_frequency>>(fr.down_sample)];
                            reset_audio=1;
                        }
                    } 
                    else 
                    if (Args->SampleRate != Args->ForceFreq) 
                    {
                        Args->SampleRate = Args->ForceFreq;
                        reset_audio=1;
                    }                
                    if ((OldBits != fr.bitrate_index) && (OldBits != 0)) 
                    {
                        Args->IsVBR = true;
                    }
                    if(reset_audio) {
                        HardAudioReset(Player);
                    }
                    fr.header_change = 0;
                } 
                if(fr.error_protection) GetBits(16);          
                xxx = Args->CurrentPos;
                if(fr.WhatLayer==3) /*clip=*/do_layer3(); else
                if(fr.WhatLayer==2) /*clip=*/do_layer2(); else 
                if(fr.WhatLayer==1) /*clip=*/do_layer1();
                if (Player->PauseFlag) 
                {
                    if (Args->OutputMode = omMMSystem) Pause_Audio();
                    Player->ThreadSync = 1;  
                    while(Player->PauseFlag)
                    {
                        Sleep(77);
                        if (Player->UserBreak) break;
                        if (WaitForSingleObject(SeekEvent, 0) == WAIT_OBJECT_0) 
                        {
                            if (Args->OutputMode == omMMSystem) 
                            {
                                mmRes = waveOutReset(WaveDevice);
                                ProcessAudioMessages();
                                BufferCount = 0;
                            }
                            if (Seek_Stream(NewSeekPosition))
                                NewSeekPosition = -1;
                            else
                                NewSeekPosition = 0;
                            SetEvent(SeekEvent2);
                        }
                    }
                    if (Args->OutputMode = omMMSystem) Resume_Audio();                    
                } 
            }
            catch (...)
            {
                throw;
            }
        }                                
    } catch (...) 
    {
        int kkk = 1;
    }
    if(!Player->UserBreak)
    {
        try 
        { 
            AudioFlush();
            FinishBuffer(); 
        } 
        catch (...) 
        {
        }
        if (Decoder_Initialized) 
        {
            Done_MPEGDecoder();
            Decoder_Initialized = false;        
        }
        Reset_Stream();
        Done_MPAudio();
        Player->FPlayerMode = pmStopped;
    }
    else
    {
        if (Args->OutputMode == omMMSystem)
        {
            AudioFlush();
            mmRes = waveOutReset(WaveDevice);
            ProcessAudioMessages();
            BufferCount = 0;
        }
        if (Decoder_Initialized) 
        {
            Done_MPEGDecoder();
            Decoder_Initialized = false;        
        }        
        Reset_Stream(); 
        Done_MPAudio();
        Player->FPlayerMode = pmOpened;
    }
    Player->UserBreak=0; 
    SetEvent(FinishEvent);
    ExitThread(0);
    return 0;
}

MPPlayer::~MPPlayer() {
    if (PlayerMode() > pmClosed) Close();
    if (Args) delete Args;
    CloseHandle(FinishEvent);
    CloseHandle(SeekEvent);
    CloseHandle(SeekEvent2);
}

MPPlayer::MPPlayer() {
    ModuleTag = 0x14581458;
    FinishEvent = CreateEvent(NULL, false, false, NULL);
    SeekEvent = CreateEvent(NULL, false, false, NULL);
    SeekEvent2 = CreateEvent(NULL, false, false, NULL);
    Args = new MPArgs();
    if (!Args) throw 1;
    Args->InputMode=imFile;
    Args->OutputMode=omMMSystem;  
    Args->Player = this;
    FPlayerMode = pmClosed;
    UserBreak = false;
    LastError = peNoError;
    fr.single = -1;     
    fr.down_sample = 0;
    
    equalizer_cnt=0;
    for(int i=0; i<32; i++) {
        equalizer[0][i]=equalizer[1][i]=1.0;
        equalizer_sum[0][i]=equalizer_sum[1][i]=0.0;
    }
};

esPlayerError MPPlayer::ESGetLastError() {
    esPlayerError res = LastError;
    LastError = peNoError;
    return res;
}

bool MPPlayer::SetInName (const char *FileName){
    if (PlayerMode() != pmClosed) {
        LastError = peIncorrectMode;
        return false;
    }  
    if (Args->InName) free(Args->InName);
    Args->InName = (char *) xstrdup((LPTSTR) FileName);
    return true;
}

bool MPPlayer::SetOutName(const char *FileName){
    if (PlayerMode() >= pmPlaying) {
        LastError = peIncorrectMode;
        return false;
    }  
    if (Args->OutName) free(Args->OutName);
    Args->OutName = (char *) xstrdup((LPTSTR) FileName);
    return true;
}

bool MPPlayer::SetInMode (esInputMode InMode){
    if (PlayerMode() > pmClosed) {
        LastError = peIncorrectMode;
        return false;
    }
    Args->InputMode = InMode;
    return true;
}

bool MPPlayer::SetOutMode(esOutputMode OutMode){
    if (PlayerMode() >= pmPlaying) {
        LastError = peIncorrectMode;
        return false;
    }
#ifndef _DIRECTX
    if (OutMode == omDirectSound) {
        LastError = peNotImplemented;
        return false;
    }
#endif
    Args->OutputMode = OutMode;
    return true;
}

bool MPPlayer::Open(){
    if ((PlayerMode() != pmClosed) || ((Args->InputMode == imFile) && (!Args->InName))) {
        if (PlayerMode() != pmClosed) 
            LastError = peIncorrectMode; 
        else 
            LastError = peInputError;
        return false;
    }
    PauseFlag = 0;
    try {
        Init_Stream();            
    } catch (...) {
        LastError = peInputError;
        return false;
    }
    FPlayerMode = pmOpened;
    return true;
}

bool MPPlayer::InitStream(){
    if ((PlayerMode() != pmOpened) && (PlayerMode() != pmStopped))
    {
        LastError = peIncorrectMode;
        return false;
    }
    try 
    {
        memset(&fr, 0, sizeof(fr));
        fr.single = -1;
        if (!ReadFrame()) 
        {
            Reset_Stream();
            return false;
        }
        Reset_Stream();
    } 
    catch ( ... ) 
    {
        return false;
    }
    Args->SampleRate = freqs[fr.sampling_frequency];
    if(fr.single>=0) Args->ForceMono=1;
    if(Args->ForceMono) {
        if(fr.single<0) fr.single=3;
        Args->Channels=1;
    }
    if(fr.down_sample==1) 
    {
        Args->SampleRate = Args->SampleRate/2;
        Args->ForceFreq = Args->SampleRate;
    }
    if (fr.down_sample==2) 
    {
        Args->SampleRate = Args->SampleRate/4;
        Args->ForceFreq = Args->SampleRate;
    }
    if ((Args->SampleRate >= 48000)  && (Args->OutputMode == omMMSystem)) 
    {
        /*
            This doesn't work :(((
            fr.down_sample = 3;
            synth_ntom_set_step(12, 11);
            Args->ForceFreq = Args->SampleRate = 44100;
        */
        fr.down_sample = 1;
        Args->SampleRate = Args->SampleRate/2;
        Args->ForceFreq = Args->SampleRate;
    }
    SynthesisFilterInit();
    try {
        // create decoder 
        Init_MPEGDecoder(fr.down_sample);
        make_decode_tables(Args->ScaleFactor);        
    }
    catch(...){
        LastError = peInternalError;
        return false;
    }
    FPlayerMode = pmReady;
    return true;
}

bool MPPlayer::Play() {
    if (PlayerMode() != pmReady) 
    {
        LastError = peIncorrectMode;
        return false;
    }
    if ((Args->OutputMode == omCallback) && ((!Args->BufferCB) || (!Args->OutActionCB))) 
    {
        LastError = peNoCallback;
        return false;
    }
    if (Args->EndPos == 0) SetLimits(Args->StartPos, Args->EndPos);
    fr.header_change = 0;
    
    ThreadQueueEvent = CreateEvent(NULL, false, false, NULL);
    if (!ThreadQueueEvent) 
    {
        LastError = peInternalError;
        return false;
    }
    ResetEvent(FinishEvent);
    if (PlayThreadHan)
    {
        CloseHandle(PlayThreadHan);
        PlayThreadHan = NULL;
    }
    PlayThreadHan = CreateThread(NULL, 0, PlayThread, this, 0, &PlayerThreadID);
    if (!PlayThreadHan) 
    {
        LastError = peInternalError;
        return false;           
    }
    WaitForSingleObject(ThreadQueueEvent, INFINITE);
    CloseHandle(ThreadQueueEvent);
    
    if (LastError != peNoError)
        return false;
    SetThreadPriority(PlayThreadHan, Args->PlayPriority);
    FPlayerMode = pmPlaying;
    return true;    
}

bool MPPlayer::Pause(){
    if ((PlayerMode() == pmPlaying) || (PlayerMode() == pmPaused)) {
        PauseFlag = true;
        FPlayerMode = pmPaused;
        return true;
    } else {
        LastError = peIncorrectMode;
        return false;
    }
}

bool MPPlayer::Resume(){
    if ((PlayerMode() == pmPlaying) || (PlayerMode() == pmPaused)) {
        PauseFlag = false;   
        FPlayerMode = pmPlaying;
        return true;
    } else {
        LastError = peIncorrectMode;
        return false;
    }
}

bool MPPlayer::Stop()
{
    if ((PlayerMode() == pmPlaying) || (PlayerMode() == pmPaused)) 
    {
        UserBreak = 1;
        WaitForSingleObject(FinishEvent, INFINITE);
        if (PlayThreadHan)
        {
            CloseHandle(PlayThreadHan);
            PlayThreadHan = NULL;
        }
        LastError = peNoError;
        return true;
    } 
    if (PlayerMode() == pmStopped) 
    {
            FPlayerMode = pmOpened;             
            return true;
    } else {
        LastError = peIncorrectMode;
        return false;
    }
}

bool MPPlayer::Close(){
    if ((PlayerMode() == pmPlaying) || (PlayerMode() == pmPaused)) Stop();
    if (StreamInit) {
        Done_Stream();
        StreamInit = false;
    }    
    FPlayerMode = pmClosed;
    return true;
}

unsigned long MPPlayer::GetSize(){
    if (PlayerMode() > pmOpened) {
        return Totalms();
    } else {
        LastError = peIncorrectMode;
        return -1;
    }
}

unsigned long MPPlayer::GetPos()
{
    if (PlayerMode() >= pmStopped) 
    {
        if (PlayerMode() == pmStopped) 
        {
            return Totalms();
        }
        return Currentms();
    } 
    else 
    {
        LastError = peIncorrectMode;
        return -1;
    }
}

bool MPPlayer::CanSetPos() 
{
    if (PlayerMode() >= pmOpened) 
    {
        return Args->Seekable;
    } 
    else 
    {
        LastError = peIncorrectMode;
        return false;
    }
}

bool MPPlayer::SetPos(unsigned long NewPos){
    if ((PlayerMode() == pmPlaying) || (PlayerMode() == pmPaused)) 
    {
        NewSeekPosition = NewPos;
        SetEvent(SeekEvent);
        WaitForSingleObject(SeekEvent2, INFINITE);
        return (NewSeekPosition == -1);
    } else {
        LastError = peIncorrectMode;
        return false;
    }
}

bool MPPlayer::SetAudioBuffers(unsigned long buffers, unsigned long size){
    if (PlayerMode() >= pmReady) 
    {
        LastError = peIncorrectMode;
        return false;        
    } else 
    {
        if (buffers) Args->Buffers = buffers;
        if (size) Args->BufferSize = size;
    }
    return true;
}

bool MPPlayer::SetOutputDevice(unsigned long DevNum) {
    if (PlayerMode() != pmClosed) {
        LastError = peIncorrectMode;
        return false;        
    } else {
        Args->AudioDevice = DevNum;
        return true;
    }
}

bool MPPlayer::SetLimits(unsigned long StartPos, unsigned long EndPos) 
{
    Args->StartPos = StartPos;
    if ((EndPos != 0) && (EndPos < StartPos)) 
    {
         Args->EndPos = 0xFFFFFFFF; 
    } else
    {
        Args->EndPos = EndPos;
    }
    if (PlayerMode() >= pmReady) 
    {
        Args->StartFrame = Args->StartPos / Frame2ms();
        if ((!Args->EndPos)  || (Args->EndPos == 0xFFFFFFFF))
        {
            Args->EndPos = 0xFFFFFFFF; 
            Args->EndFrame = 0xFFFFFFFF; 
        } else
            Args->EndFrame = Args->EndPos / Frame2ms();
    } 
    return true;
}

bool MPPlayer::SetPriority(long Priority) 
{
    if (PlayerMode() >= pmPlaying)
    {
        return SetThreadPriority(PlayThreadHan, Priority);        
    } 
    else 
    {
        Args->PlayPriority = Priority;
        return true;
    }
}

esPlayerMode MPPlayer::PlayerMode() {
    //esPlayerMode mode = FPlayerMode;
    //if (mode == pmStopped) FPlayerMode = pmOpened;
    return FPlayerMode;
}

bool MPPlayer::SetInCB(InFileOpenCB openCB, InFileCloseCB closeCB, InFileGetSizeCB getsizeCB,
             InFileSeekCB seekCB, InFileReadCB readCB, unsigned long UserData1) {
    if (PlayerMode() != pmClosed) {
        LastError = peIncorrectMode;
        return false;
    }
    Args->InOpenCB = openCB;
    Args->InCloseCB = closeCB;
    Args->InGetSizeCB = getsizeCB;
    Args->InSeekCB = seekCB;
    Args->InReadCB = readCB;
    Args->InCBData1 = UserData1;
    return true;
}

bool MPPlayer::SetOutCB(WaveOutCB OutCB, WaveOutActionCB OutActionCB, unsigned long UserData) {
    if (PlayerMode() >= pmPlaying) {
        LastError = peIncorrectMode;
        return false;
    } else {
        Args->BufferCB = (WaveOutCB) OutCB;
        Args->OutActionCB = (WaveOutActionCB) OutActionCB;
        Args->OutCBData = UserData;
        return true;
    }
}

bool MPPlayer::CanSetVolume(bool *Separate) {
    return Audio_CanSetVolume(Separate);    
}

bool MPPlayer::SetVolume(unsigned long Volume) {
    return Audio_SetVolume(Volume);
}

bool MPPlayer::GetVolume(unsigned long *Volume){
    return Audio_GetVolume(Volume);    
}

bool MPPlayer::SetDevNum(unsigned long DevNum) {
    if (PlayerMode() >= pmPlaying) {
        LastError = peIncorrectMode;
        return false;
    } else {
        Args->AudioDevice = DevNum;
        return true;
    }
}

bool MPPlayer::SetWindow(HWND Wnd) {
    if (PlayerMode() >= pmPlaying) {
        LastError = peIncorrectMode;
        return false;
    } else {
        Args->wnd = Wnd;
        return true;
    }
}

bool MPPlayer::UseOutCB(bool UseCB) {
    if (PlayerMode() >= pmPlaying) {
        LastError = peIncorrectMode;
        return false;
    } else {
        Args->UseHdrCB = UseCB;
        return true;
    }
}