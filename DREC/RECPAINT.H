void CreateColors( void );
void DeleteColors( void );
void CreateControls( HANDLE hinstance, HWND hwnd );
void SetButtonState( HWND hwnd );

void CalcSizes( LPARAM lparam );
void MoveDisplayObjects( void );

void InitSpecs( void );
void UpdateLength( HWND hwnd, DWORD length, DWORD lengthtotal );
void DrawSpecs( HDC hdc );
void DrawLength( HDC hdc );
void DrawRecordLight( HDC hdc );
void line( HDC hdc, int x1, int y1, int x2, int y2 );

#define SPECTEXTLEN   24

extern TEXTMETRIC FAR tm;
extern RECT FAR clrect;
extern RECT FAR specrect;
extern RECT reclightrect;

extern int txtspc;
extern int txtspeclen;
extern char FAR szFormatDesc[];
extern char FAR szFormatTag[];
