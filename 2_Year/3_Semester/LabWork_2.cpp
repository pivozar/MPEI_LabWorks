#include <stdio.h>

/*
 * Даны две матрицы разного размера. Для той из матриц, в которой больше максимальный элемент, найти сумму положительных элементов в каждой строке.
*/

const int NMAX = 100;

int ReadMatrix(int *num_rows, int *num_cols,
        double arr[][NMAX], char *filename);

double FindMaxMatrix(int num_rows, int num_cols,
        double arr[][NMAX]);

void ComputePosSumMatrix(int num_rows, int num_cols,
        double arr[][NMAX]);

double ComputePosSumRow(int row_size, double arr[]);

int main(int argc, char *argv[]) {
    
    double A[NMAX][NMAX], B[NMAX][NMAX];
    int num_rowsA, num_colsA, num_rowsB, num_colsB;
    double maxA, maxB;

    if (argc < 3) {
        printf("More arguments required!\n Usage: <file1.txt> <file2.txt>\n");
        return 1;
    }

    if (!ReadMatrix(&num_rowsA, &num_colsA, A, argv[1]))
        return 1;
 
    if (!ReadMatrix(&num_rowsB, &num_colsB, B, argv[2]))
        return 1;

    maxA = FindMaxMatrix(num_rowsA, num_colsA, A);
    maxB = FindMaxMatrix(num_rowsB, num_colsB, B);
    
    if (maxA > maxB)
        ComputePosSumMatrix(num_rowsA, num_colsA, A);
    else
        ComputePosSumMatrix(num_rowsB, num_colsB, B);

    return 0;
}

int ReadMatrix(int *num_rows, int *num_cols,
        double arr[][NMAX], char *filename) {
    FILE *file;
    
    if ((file = fopen(filename, "r")) == NULL) {
        printf("Impossible to open file '%s'\n", filename);
        return 0;
    }
    
    if (fscanf(file, "%d%d", num_rows, num_cols) < 1) {
        printf("Error while reading file '%s'\n", filename);
        return 0;
    }

    if (*num_rows < 0 || *num_rows > NMAX || *num_cols < 0 || *num_cols > NMAX) {
        printf("Array size must be from 1 to %d! (file: '%s')\n", NMAX, filename);
        return 0;
    }

    for (int i = 0; i < *num_rows; ++i)
        for (int j = 0; j < *num_cols; ++j)
            if (fscanf(file, "%lf", &arr[i][j]) < 1) {
                printf("Error while reading file '%s'\n", filename);
                return 0;
            }
    fclose(file);
    return 1;
}

double FindMaxMatrix(int num_rows, int num_cols,
        double arr[][NMAX]) {

    int maxMatr = arr[0][0];

    for (int i = 0; i < num_rows; ++i)
        for (int j = 1; j < num_cols; ++j)
            if (arr[i][j] > maxMatr)
                maxMatr = arr[i][j];
    return maxMatr;
}

void ComputePosSumMatrix(int num_rows, int num_cols,
        double arr[][NMAX]) {
    
    printf("Matrix %d x %d : \n", num_rows, num_cols);
    
    for (int i = 0; i < num_rows;)
        printf("Row no. %d: %4.2lf\n", ++i, ComputePosSumRow(num_cols, arr[i]));
    
    printf("\n");
}

double ComputePosSumRow(int row_size, double arr[]) {
    double posSum = 0;

    for (int i = 0; i < row_size; ++i)
        if (arr[i] > 0)
            posSum += arr[i];
    return posSum;
}
