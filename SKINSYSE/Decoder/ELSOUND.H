#ifndef ELSOUND_H 
#define ELSOUND_H 

#include <windows.h>

// Possible modes to take data from
enum esInputMode {
    imFile, 
    imCallback
};

// Possible modes to put data to
enum esOutputMode {
    omMMSystem, 
    omWaveFile, 
    omDirectSound,
    omCallback
};

// Current player mode
enum esPlayerMode {
    pmClosed,
    pmOpened,
    pmReady,
    pmStopped,
    pmPlaying,
    pmPaused
};

enum esPlayerError {
    peNoError,
    peNotImplemented, // Feature not implemented
    peIncorrectMode,  // not correct mode for performing an operation
    peInternalError,  // failed to allocate memory/resources
    peInvalidHandle,  // Invalid player object handle
    peInputError,
    peOutputError,
    peNoMemory,
    peNoResources,    
    peNoCallback
};

typedef bool (_stdcall *WaveOutCB)(void *SampleData, int SBits, int Channels, unsigned long SampleRate, unsigned long Size, unsigned long userdata);
typedef bool (_stdcall *WaveOutActionCB)(bool Init, unsigned long userdata);

typedef bool (_stdcall *InFileOpenCB)(unsigned long UserData1, unsigned long *UserData2, bool *IsSeekable);
typedef bool (_stdcall *InFileCloseCB)(unsigned long UserData1, unsigned long UserData2);
typedef bool (_stdcall *InFileGetSizeCB)(unsigned long UserData1, unsigned long UserData2, unsigned long *InSize);
typedef bool (_stdcall *InFileSeekCB)(unsigned long UserData1, unsigned long UserData2, LPDWORD NewPos, DWORD dwMoveMethod);
typedef bool (_stdcall *InFileReadCB)(unsigned long UserData1, unsigned long UserData2, LPVOID buffer, DWORD bytes_to_read, DWORD *bytes_read);

typedef HANDLE (*InitModuleProc)(); 
typedef bool (*DeInitModuleProc)(HANDLE handle); 
typedef bool (*OpenProc)  (HANDLE handle); 
typedef bool (*CloseProc) (HANDLE handle); 
typedef bool (*PlayProc)  (HANDLE handle); 
typedef bool (*StopProc)  (HANDLE handle); 
typedef bool (*PauseProc) (HANDLE handle); 
typedef bool (*ResumeProc)(HANDLE handle); 
typedef long (*GetLastErrorProc)(HANDLE handle); 
typedef bool (*SetPosProc)(HANDLE handle, unsigned long NewPos); 
typedef long (*GetVersionProc)(); 
typedef long (*GetAboutProc)(char *buffer, unsigned long *buflen); 
typedef long (*GetInfo1Proc)(char *buffer, unsigned long *buflen); 
typedef long (*GetExtsProc)(char *buffer, unsigned long *buflen); 
typedef bool (*SetInputNameProc)(HANDLE handle, char *Name); 
typedef bool (*SetOutputNameProc)(HANDLE handle, char *Name); 
typedef bool (*SetInputModeProc)(HANDLE handle, unsigned long InMode); 
typedef bool (*SetOutputModeProc)(HANDLE handle, unsigned long OutMode); 
typedef bool (*SetOutputDevProc)(HANDLE handle, unsigned long DevNum); 
typedef unsigned long (*GetPosProc)(HANDLE handle); 
typedef unsigned long (*GetSizeProc)(HANDLE handle); 
typedef unsigned long (*GetModeProc)(HANDLE handle); 
typedef bool (*SetAudioBuffersProc)(HANDLE handle, unsigned long buffers, unsigned long size);
typedef bool (*SetPriorityProc)(HANDLE handle, long Priority);
typedef bool (*SetLimitsProc)(HANDLE handle, unsigned long StartPos, unsigned long EndPos);
typedef bool (*SetOutCBProc)(HANDLE handle, WaveOutCB OutCB, WaveOutActionCB OutActionCB, unsigned long UserData);
typedef bool (*ESGetInfo2Proc)(HANDLE handle, unsigned long *Info2);
typedef bool (*SetInCBProc)(HANDLE handle, InFileOpenCB openCB, 
                            InFileCloseCB closeCB, 
                            InFileGetSizeCB getsizeCB,
                            InFileSeekCB seekCB,
                            InFileReadCB readCB,
                            unsigned long UserData1);
typedef bool (*ESSetVolumeProc)(HANDLE handle, unsigned long Volume);
typedef bool (*ESGetVolumeProc)(HANDLE handle, unsigned long *Volume);
typedef bool (*ESCanSetVolumeProc)(HANDLE handle, bool *Separate); 
typedef bool (*ESSetDevNumProc)(HANDLE handle, unsigned long DevNum);
typedef bool (*ESSetWindowProc)(HANDLE handle, HWND Wnd);
typedef bool (*ESCanPauseProc)(HANDLE handle);
typedef bool (*ESCanSetPosProc)(HANDLE handle);
typedef bool (*ESSetExtrasProc)(HANDLE handle, void *Volume);
typedef bool (*ESUseOutCBProc)(HANDLE handle, bool UseCB);
typedef bool (*ESHasEQProc)(HANDLE handle, bool *ItDoes);
typedef bool (*ESEQProc)(HANDLE handle, LPVOID *EQData, unsigned long *channels, unsigned long *bands);
typedef bool (*ESUseEQProc)(HANDLE handle, bool UseEQ);

HANDLE __declspec(dllexport) _stdcall ESInitModule();
long __declspec(dllexport) _stdcall ESGetLastError(HANDLE handle);
bool __declspec(dllexport) _stdcall ESDeInitModule(HANDLE handle);
bool __declspec(dllexport) _stdcall ESOpen(HANDLE handle);
bool __declspec(dllexport) _stdcall ESClose(HANDLE handle);
bool __declspec(dllexport) _stdcall ESPlay(HANDLE handle);
bool __declspec(dllexport) _stdcall ESStop(HANDLE handle);
bool __declspec(dllexport) _stdcall ESPause(HANDLE handle);
bool __declspec(dllexport) _stdcall ESResume(HANDLE handle);
unsigned long __declspec(dllexport) _stdcall ESGetPos(HANDLE handle); 
unsigned long __declspec(dllexport) _stdcall ESGetSize(HANDLE handle); 
bool __declspec(dllexport) _stdcall ESSetPos(HANDLE handle, unsigned long NewPos); 
bool __declspec(dllexport) _stdcall ESGetAbout(char *buffer, unsigned long *buflen);
bool __declspec(dllexport) _stdcall ESGetExts(char *buffer, unsigned long *buflen);
bool __declspec(dllexport) _stdcall ESGetName(char *buffer, unsigned long *buflen);
long __declspec(dllexport) _stdcall ESGetVersion();
bool __declspec(dllexport) _stdcall ESSetPriority(HANDLE handle, long Priority);

bool __declspec(dllexport) _stdcall ESSetInputName(HANDLE handle, char *Name); 
bool __declspec(dllexport) _stdcall ESSetOutputName(HANDLE handle, char *Name); 
bool __declspec(dllexport) _stdcall ESSetInputMode(HANDLE handle, unsigned long InMode); 
bool __declspec(dllexport) _stdcall ESSetOutputMode(HANDLE handle, unsigned long OutMode); 
bool __declspec(dllexport) _stdcall ESSetOutputDev(HANDLE handle, unsigned long DevNum); 
unsigned long __declspec(dllexport) _stdcall ESGetPlayerMode(HANDLE handle); 
bool __declspec(dllexport) _stdcall ESSetAudioBuffers(HANDLE handle, unsigned long buffers, unsigned long size);
bool __declspec(dllexport) _stdcall ESSetLimits(HANDLE handle, unsigned long StartPos, unsigned long EndPos);
bool __declspec(dllexport) _stdcall ESSetOutCB(HANDLE handle, WaveOutCB OutCB, WaveOutActionCB OutActionCB, unsigned long UserData);
bool __declspec(dllexport) _stdcall ESGetInfo1(HANDLE handle, void *InfoBuf, unsigned long *buflen);
bool __declspec(dllexport) _stdcall ESGetInfo2(HANDLE handle, unsigned long *Info2);
bool __declspec(dllexport) _stdcall ESSetInCB(HANDLE handle, InFileOpenCB openCB, 
                                              InFileCloseCB closeCB, InFileGetSizeCB getsizeCB,
                                              InFileSeekCB seekCB, InFileReadCB readCB,
                                              unsigned long UserData1);
bool __declspec(dllexport) _stdcall ESCanSetVolume(HANDLE handle, bool *Separate); 
bool __declspec(dllexport) _stdcall ESSetVolume(HANDLE handle, unsigned long Volume);
bool __declspec(dllexport) _stdcall ESGetVolume(HANDLE handle, unsigned long *Volume);
bool __declspec(dllexport) _stdcall ESSetDevNum(HANDLE handle, unsigned long DevNum);
bool __declspec(dllexport) _stdcall ESInitStream(HANDLE handle);
bool __declspec(dllexport) _stdcall ESSetWindow(HANDLE handle, HWND Wnd);
bool __declspec(dllexport) _stdcall ESCanPause(HANDLE handle);
bool __declspec(dllexport) _stdcall ESCanSetPos(HANDLE handle);
bool __declspec(dllexport) _stdcall ESSetExtras(HANDLE handle, void *Param);
bool __declspec(dllexport) _stdcall ESUseOutCB(HANDLE handle, bool UseCB);

bool __declspec(dllexport) _stdcall ESHasEQ(HANDLE handle, bool *ItDoes);
bool __declspec(dllexport) _stdcall ESEQ(HANDLE handle, LPVOID *EQData, unsigned long *channels, unsigned long *bands);
bool __declspec(dllexport) _stdcall ESUseEQ(HANDLE handle, bool UseEQ);

#endif