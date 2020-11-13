#include <stdio.h>
#include "string_dll.h"

__stdcall bool IsWordChar(char c) {
    return c >= 'a' && c <= 'z'
            || c >= 'A' && c <= 'Z'
            || c >= '0' && c <= '9';
}

void SolveString(char *str, char *wbegin, char *wend) {
    if(*str != '\0') {
        if(IsWordChar(*str)) {
            if (!wbegin)
                wbegin = str;
            SolveString(str + 1, wbegin);
        }
        else {
            if(wbegin) {
                wend = str;
                ReverseWord(wbegin, wend);  
            }
            SolveString(str + 1);
        }
    }
}

void ReverseWord(char *wbegin, char *wend) {
    char tmp;
    int i = 0;
    while (i < (wend - wbegin) / 2) {
        tmp = *(wbegin + i);
        *(wbegin + i) = *(wend - 1 - i);
        *(wend - 1 - i) = tmp;
        i++;
    }
}