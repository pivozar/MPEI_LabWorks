#ifndef STRING_DLL_H
#define STRING_DLL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILDING_STRING_DLL
#define STRING_DLL __declspec(dllexport)
#else
#define STRING_DLL __declspec(dllimport)
#endif

bool __stdcall STRING_DLL IsWordChar(char c);

void STRING_DLL SolveString(char *str, char *wbegin=nullptr, char *wend=nullptr);

void STRING_DLL ReverseWord(char *wbegin, char *wend);

#ifdef __cplusplus
}
#endif

#endif  // STRING_DLL_H
