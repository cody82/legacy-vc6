#ifndef HELPER_H
#define HELPER_H

#include <windows.h>
#include <tchar.h>

extern LPTSTR __inline DeleteString(LPTSTR s);

LPTSTR xstrdup(const LPTSTR s);
LPTSTR xstrdupe(const LPTSTR s);

LPVOID encode_strlist(LPTSTR *strlist, DWORD *enc_len);
LPTSTR *decode_strlist(LPVOID str);

#endif