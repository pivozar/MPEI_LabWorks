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
int WriteArrayBinary(int arr_size, float arr[], char *filename);
int PrintArray(char *filename);
int SwapInFile(int pos1, int pos2, char *filename);

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

    if (!WriteArrayBinary(arr_size, array, argv[1])) {
        return 1;
    }
    printf("Array before changes:\n");
    if (!PrintArray(argv[1])) {
        return 1;
    }

    printf("Enter positions of elements to swap:\n");
    scanf("%d%d", &pos1, &pos2);

    pos1--; pos2--;
    if (!SwapInFile(pos1, pos2, argv[1])) {
        return 1;
    }
    
    printf("Array after changes:\n");
    if (!PrintArray(argv[1])) {
        return 1;
    }

    return 0;
}

int ReadArray(int *arr_size, float arr[], char *filename) {
    FILE *file;
    
    if ((file = fopen(filename, "r")) == NULL) {
        printf("Impossible to open file: '%s'\n", filename);
        return 0;
    }

    if (fscanf(file, "%d", arr_size) < 1) {
        printf("Error while reading file: '%s'", filename);
        return 0;
    }

    if (*arr_size < 0 || *arr_size > NMAX) {
        printf("Array size must be from 1 to %d! (file: '%s')\n", NMAX, filename);
        return 0;
    }

    for (int i = 0; i < *arr_size; ++i) {
        if (fscanf(file,  "%f", &arr[i]) < 1) {
            printf("Error while reading file: '%s'", filename);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

int WriteArrayBinary(int arr_size, float arr[], char *filename) {
    FILE *file;

    if ((file = fopen(filename, "wb")) == NULL) {
        printf("Impossible to open file: '%s'\n", filename);
        return 0;
    }
    
    if (fwrite(arr, arr_size * sizeof(float), 1, file) < 1) {
        printf("Error while writing into file: '%s'\n", filename);
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

int PrintArray(char *filename) {
    FILE *file;

    float tmp = 0;

    if ((file = fopen(filename, "rb")) == NULL) {
        printf("Impossible to open file: '%s'\n", filename);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    int filesize = ftell(file) / sizeof(float);
    fseek(file, 0, SEEK_SET);

    for (int i=0; i < filesize; ++i) {
        if (fread(&tmp, sizeof(float), 1, file) < 1) {
            printf("Error while reading file: '%s'\n", filename);
            return 0;
        }
        if (i % 2 == 0) printf("{");
        printf("%.3f", tmp);
        if (i % 2 == 0) printf(" ");
        else printf("} ");
    }
    printf("\n");

    fclose(file);
    return 1;
}

int SwapInFile(int pos1, int pos2, char *filename) {
    FILE *file;
    float elem1[2], elem2[2];

    if ((file = fopen(filename, "rb+")) == NULL) {
        printf("Impossible to open file: '%s'\n", filename);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    int filesize = ftell(file) / (sizeof(float) * 2);
    fseek(file, 0, SEEK_SET);


    if (pos1 >= filesize || pos2 >= filesize || pos1 < 0 || pos2 < 0) {
        printf("This records are not exist: %d %d\n", pos1, pos2);
        return 0;
    }
    fseek(file, sizeof(float) * pos1 * 2, SEEK_SET);
    fread(elem1, sizeof(float), 2, file);

    fseek(file, sizeof(float) * pos2 * 2, SEEK_SET);
    fread(elem2, sizeof(float), 2, file);

    fseek(file, sizeof(float) * pos1 * 2, SEEK_SET);
    fwrite(elem2, sizeof(float), 2, file);

    fseek(file, sizeof(float) * pos2 * 2, SEEK_SET);
    fwrite(elem1, sizeof(float), 2, file);

    fclose(file);
    return 1;
}

