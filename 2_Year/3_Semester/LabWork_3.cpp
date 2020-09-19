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

const int NMAX = 100;

int ReadArray(int *arr_size, float arr[], char *filename);
int WriteArrayBinary(int arr_size, float arr[], filename);
int PrintArray(int arr_size, float arr[], filename);
int SwapInFile(int pos1, int pos2, filename);

int main(int argc, char* argv[]) {
    float array[NMAX];
    int arr_size;
    int pos1, pos2;

    if (argc < 2) {
        printf("More arguments required!\n");
        return 1;
    }
    if (!ReadArray(&arr_size, array, argv[1]))
        return 1;

    WriteArrayBinary(arr_size, array, filename);
    printf("Array before changes:\n");
    PrintArray(arr_size, array, filename);

    pintf("Enter positions of elements to swap:\n");
    scanf("%d%d", &pos1, &pos2);
    
    SwapInFile(pos1, pos2, filename);
    

    return 0;
}

int ReadArray(int *arr_size, float arr[], char *filename) {
    FILE *file;
    
    if ((file = fopen(filename, "r")) == NULL) {
        printf("Impossible to open file '%s'\n", filename);
        return 0;
    }

    if (fscanf(file, "%d", arr_size) < 1) {
        printf("Error while reading file '%s'", filename);
        return 0;
    }

    if (*arr_size < 0 || *arr_size > NMAX) {
        printf("Array size must be from 1 to %d! (file: '%s')\n", NMAX, filename);
        return 0;
    }

    for (int i = 0; i < *arr_size; ++i) {
        if (fscanf(file,  "%lf", &arr[i]) < 1) {
            printf("Error while reading file '%s'", filename);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

