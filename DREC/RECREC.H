void InitWaveHeaders( void );
int InitWaveRecorder( HWND hwnd );
void DestroyWaveRecorder( HWND hwnd );
int StartWaveRecord( HWND hwnd );
void StopWaveRecord( HWND hwnd );
int WriteWaveBuffer( UINT size );
int AddNextBuffer( HWND hwnd );
void UpdateRecordDisplay( HWND hwnd );
void CloseWaveDeviceRecord( HWND hwnd );
int CreateTmpFile( void );
void CloseTmpFile( void );

extern LPWAVEHDR pwavehdr[];	// pointers to wave header information
extern HANDLE hwavehdr[];		// wave header memory handle
extern char tmpfilename[];		// filename of temporary wave file
extern HFILE htmpfile;			// temporary file handle
extern UINT WaveBufSize;		// size of buffer as a multiple of the nBlockAlign header field
extern BOOL recordeddata;     // for knowing when we've recorded data
extern DWORD dwBytedatasize;
extern DWORD dwTotalwavesize;
