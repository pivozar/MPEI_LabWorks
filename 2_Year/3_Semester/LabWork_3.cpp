#include <stdio.h>

/*В двоичном файле поменять местами две записи с заданными номерами.
 * Обязательно проверить, что записи с такими номерами существуют в файле.
 * Следует читать не весь файл, а только нужные записи – 
 * в двоичном файле возможен прямой доступ (никаких циклов!).
 * При выполнении этого задания необходимо преобразовать текстовый файл в двоичный,
 * а также вывести на экран содержимое двоичного файла до обработки и после обработки.
 * Не забывайте закрывать файлы.
 * Каждая запись представляет собой 2 числа типа float
*/

int ReadFloat(float *a, float *b, char* filename) {
    FILE *file;

    if ((file = fopen(filename, "r")) == NULL) {
        printf("Impossible to open file '%s'\n", filename);
        return 0;
    }
    if (scanf("%f %f", a, b) < 1) {
        printf("Impossible to read from file: '%s'\n", filename);
        return 0;
    }
    fclose(file);
    return 1;
}

int WriteFloatBinary(float *a, float *b, char* filename) {
    FILE *file;

    if ((file = fopen(filename, "wb")) == NULL) {
        printf("Impossible to write to file: '%s'\n", filename);
        return 0;
    }
    if (fwrite(

int main(int argc, char* argv[]) {
    float a, b;
    
    if (!ReadFloat(&a, &b, argv[1]))
        return 0;
    
    return 0;
}
