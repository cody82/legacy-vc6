#include <string.h>
#include <malloc.h>
#include <tchar.h>
#include "helper.h"

__inline LPTSTR DeleteString(LPTSTR s) {
    if (s) 
    {
        free (s);
    }
    return NULL;
}

LPTSTR xstrdup(const LPTSTR s) {
    if (!s) return NULL;
    LPTSTR e;
    int l = _tcsclen(s);
    e = (LPTSTR) malloc (l+sizeof (TCHAR));
    _tcscpy(e, s);
    return e;
}

LPTSTR xstrdupe(const LPTSTR s) {
    if (!s) return NULL;
    LPTSTR e;
    int l = _tcsclen(s);
    e = (LPTSTR) malloc (l+sizeof (TCHAR));
    if (!e) throw 1;
    _tcscpy(e, s);
    return e;
}

LPVOID encode_strlist(LPTSTR *strlist, DWORD *enc_len)
{
    LPTSTR buf, tmp_buf, cur_str;
    int i, j;
    i = 0;
    j = 0;
    cur_str = (LPTSTR) strlist[j];
    // define total length
    while (cur_str != NULL) 
    {
        i += _tcslen(cur_str) + sizeof TCHAR;
        cur_str = strlist[++j];
    }
    i+= sizeof TCHAR;
    // copy strings to buffer
    *enc_len = i;
    buf = (LPTSTR) malloc(i);
    tmp_buf = buf;
    j = 0;
    cur_str = (LPTSTR) strlist[j];
    // define total length
    while (cur_str != NULL) 
    {
        _tcscpy(tmp_buf, cur_str);
        tmp_buf += _tcslen(cur_str) + sizeof TCHAR;
        cur_str = strlist[++j];
    }
    *tmp_buf = (TCHAR) 0;
    return buf;
}

LPTSTR *decode_strlist(LPVOID str) 
{
    LPTSTR cur_str;
    LPTSTR *buf;
    int i, j;
    j = 0;
    cur_str = (LPTSTR) str;
    while (*cur_str != (TCHAR) 0) 
    {
        j++;
        cur_str += _tcslen(cur_str) + sizeof TCHAR;
    }
    j++;
    buf = (LPTSTR *) malloc(j * sizeof LPVOID);
    i = 0;
    cur_str = (LPTSTR) str;
    while (i < j) 
    {
        *buf = xstrdup(cur_str);
        buf += sizeof(LPTSTR);
        cur_str += _tcslen(cur_str) + sizeof TCHAR;        
    }
    *buf = NULL;
    return buf;
}
