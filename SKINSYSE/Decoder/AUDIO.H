#ifndef AUDIO_H
#define AUDIO_H

extern bool MPAudioEvents[4];
extern bool Audio_Initialized;
extern HWAVEOUT WaveDevice;
extern long BufferCount;
extern HANDLE PlayThreadHan;
extern DWORD PlayerThreadID;

extern void ProcessAudioMessages();
extern bool Init_MPAudio();
extern bool Done_MPAudio();
extern long PlaySamples(unsigned char *buf,long len);
extern long GetBufferload();
extern unsigned long QueuedBuffers();
extern void FinishBuffer();
extern bool ExecuteCallback();
extern void Reset_Audio();
extern void Pause_Audio();
extern void Resume_Audio();
extern bool Audio_CanSetVolume(bool *Separate); 
extern bool Audio_SetVolume(unsigned long Volume);
extern bool Audio_GetVolume(unsigned long *Volume);


#endif