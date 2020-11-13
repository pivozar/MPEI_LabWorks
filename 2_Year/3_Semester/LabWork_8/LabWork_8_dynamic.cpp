#include <stdio.h>
#include <windows.h>

/*
 * Разработать dll-библиотеку на языке С++ с функцией обработки строк
 * (задание см. в работе «Обработка строк»). На языке С++ написать программу,
 * статически подключающую разработанную библиотеку, и программу,
 * динамически подключающую разработанную библиотеку.
 *
 * Реверсировать буквы в каждом слове.
*/

typedef void (*LibraryFunction)(char*, char*, char*);

int ReadString(char *filename, char str[]);

int main(int argc, char *argv[]) {
    char string[50];

    HINSTANCE hLib;

    LibraryFunction func;

    hLib = LoadLibrary(TEXT("string_dll.dll"));

    if (hLib == NULL) {
        printf("Unable to load the library 'string_dll.dll'!\n");
        return 1;
    }

    func = (LibraryFunction) GetProcAddress(hLib, "SolveString");

    if (!func) {
        printf("Unable to find the function 'SolveString'!\n");
    }

    if (argc < 2) {
        printf("More arguments required!\n");
        return 0;
    }

    if (!ReadString(argv[1], string))
        return 0;
    printf("Before: '%s'\n", string);

    func(string, nullptr, nullptr);

    printf("After: '%s'\n", string);
    FreeLibrary(hLib);
    
    return 0;
}

int ReadString(char *filename, char str[]) {
    FILE *file;
    int str_size;
    
    if ((file = fopen(filename, "r")) == NULL) {
        printf("Impossible to open file: '%s'\n", filename);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    str_size = ftell(file) / sizeof(char);
    fseek(file, 0, SEEK_SET);

    fgets(str, str_size, file);
    
    fclose(file);
    return 1;
}