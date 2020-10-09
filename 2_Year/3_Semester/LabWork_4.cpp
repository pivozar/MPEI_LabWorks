#include <stdio.h>

/*
 * Для решения задачи вам нужно ввести строки с помощью функций gets или fgets,
 * разбить строку на слова и выбрать нужные (функция scanf с форматом %s вводит
 * строку до пробела, но в данной задаче вам не нужно так делать!). Стандартные
 * функции работы со строками НЕ использовать! Обратите внимание, что во всех
 * случаях слова могут разделяться любым (!) количеством символов, не относящихся
 * к слову (будем считать, что к слову относятся большие и маленькие латинские буквы и цифры).
 * Желательно всю обработку выполнить за один проход строки, хотя это возможно не во всех вариантах.
 * Обязательно проверить работу программы на пустой строке и на строке, состоящей только из символов,
 * не относящихся к слову.
 *
 * Реверсировать буквы в каждом слове.
*/

int ReadString(char *filename, char str[]);
bool IsWordChar(char c);
int SolveString(char str[]);
void ReverseWord(char *wbegin, char *wend);

int main(int argc, char *argv[]) {
    char string[50];

    if (argc < 2) {
        printf("More arguments required!\n");
        return 0;
    }

    if (!ReadString(argv[1], string))
        return 0;
    printf("Before: '%s'\n", string);

    SolveString(string);

    printf("After: '%s'\n", string);
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

bool IsWordChar(char c) {
    return c >= 'a' && c <= 'z'
            || c >= 'A' && c <= 'Z'
            || c >= '0' && c <= '9';
}

int SolveString(char str[]) {
    char *wbegin, *wend, *p = str;
    bool isWordNow = true;

    while (!IsWordChar(*p) && *p) {
        p++;
    }
    wbegin = p++;
    for (; *p; p++) {
        if (IsWordChar(*p) && !isWordNow) {
            wbegin = p;
            isWordNow = true;
        }
        else if (!IsWordChar(*p) && IsWordChar(*(p-1))) {
            wend = p;
            isWordNow = false;
            ReverseWord(wbegin, wend);
        }
    }
    return 1;
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
