#ifndef BITSTREAM_H
#define BITSTREAM_H

#include "common.h"
#include "args.h"

// Header mask definition
#define HDRCMPMASK 0xfffffd00

// Maximum frame size
#define MAXFRAMESIZE 1792

extern int head_read(unsigned char *hbuf,unsigned long *newhead);
extern int head_check(unsigned long newhead); 
extern bool Init_Stream();
extern bool Done_Stream();
  // Reads a frame
  extern int    ReadFrame();
  // Steps one frame back
  extern int    BackFrame(int num);
  // Returns the maximum count of the frames in stream
  extern unsigned long GetMaxFrames();
  // Returns the minimum count of the frames in stream
  extern unsigned long GetMinFrames();
  // Calculate framesize of the current frame 
  extern unsigned long CalcFramesize();
  // Returns the bitrate of the stream
  extern unsigned long GetBitrate();
  // Returns the samplerate of the stream
  extern unsigned long GetSampleRate();
  // Returns the milli seconds one frame has
  extern real Frame2ms();
  // Returns the total milli seconds of the stream 
  extern real Totalms();
  // Returns the current Position in ms
  extern unsigned long Currentms();
  // Seek to stream position in frames
  extern bool Seek_Stream(unsigned long Position);
  // Gets the stream bits for the decoder
  extern unsigned long  __inline Get1Bit(void);
  extern unsigned long __inline GetBits(int);
  extern unsigned long __inline GetBitsFast(int);
  // Sets the bit pointer
  extern void SetPointer(long);
  // Gets the ID3Tag
  extern ID3TagStruct* GetID3Tag();
  // Resets bitstream potision to zero 
  extern void Reset_Stream();

extern bool StreamInit;
extern unsigned char *wordpointer;

extern unsigned long MaxFrames, MinFrames;

extern const long freqs[];

#endif
