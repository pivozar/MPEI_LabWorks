#include <cstdio>

/*
 * Написать функцию, указанную в задании, используя только операции над битам
 * и (никаких возведений в степень и т.п.). Во всех вариантах необходимо
 * менять все биты сразу, а не по одному в цикле. Биты нумеруются с 0 до 31
 * начиная с правого бита. Бит с номером p должен меняться.
 * 
 * Написать программу для проверки правильности работы функции.
 * Для того, чтобы было удобно проверять правильность работы с битами,
 * исходное и полученное число можно вывести, используя формат
 * %08x – целое число в шестнадцатеричной системе счисления, 8 знаков,
 * впереди добавляются нули. Необходимо проверять корректность
 * введённых значений переменных n и p.
 *
 * Написать функцию, которая в числе x устанавливает 0 в n бит,
 * находящиеся слева от позиции p, остальные биты остаются без изменения.
*/

void bitMaker(int& num, int n, int p);

void PrintNumBinary(int num);

int main(int argc, char *argv[]) {
    int num, p, n;
    FILE *file;

    if (argc < 2) {
        printf("More arguments reqiured!");
        return 0;
    }

    if ((file = fopen( argv[1], "r")) == NULL) {
        printf("Impossible to open file: '%s'\n", argv[2]);
        return 0;
    }

    fscanf(file, "%d %d %d", &num, &p, &n);
    fclose(file);

    printf("Before:\n");
    PrintNumBinary(num);

    bitMaker(num, n, p);

    printf("After:\n");
    PrintNumBinary(num);

    return 1;
}

void bitMaker(int& num, int n, int p) {

    unsigned int bits_left = -1;
    bits_left = bits_left << (n + p);
    unsigned int bits_right = (p == 0) ? 0 : -1;
    bits_right = bits_right >> (32 - p);
    
    //PrintNumBinary(bits_left);
    //PrintNumBinary(bits_right);

    //unsigned int bits_left = ((1 << (32 - n - p + 1)) - 1) << (n + p - 1);
    //unsigned int bits_right = (1 << (p - 1)) - 1;

    unsigned int mask = bits_left | bits_right;
    num &= mask;
}

void PrintNumBinary(int num) {
    for (int i = sizeof(int)*8 - 1; i > -1; --i) {
        printf("%d", bool(num & (1 << i)));
    }
    printf("\n%d\n", num);
}


