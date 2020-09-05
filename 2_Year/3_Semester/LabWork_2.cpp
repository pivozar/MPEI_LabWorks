#include <stdio.h>

const int NMAX = 100;

int ReadMatrix(int *num_rows, int *num_cols,
        double arr[][NMAX], char *filename);

double FindMaxMartix(int num_rows, int num_cols,
        double arr[][NMAX]);

double ComputePosSumMatrix(int num_rows, int num_cols,
        double arr[][NMAX]);

double ComutePosSumRow(int row_size, double arr[]);

int main(int argc, char *arg[]) {
    
    double A[NMAX][NMAX], B[NMAX][NMAX];
    int num_rowsA, num_colsA, num_rowsB, num_rowsB;
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
        ComputePosSum(num_rowsA, num_colsA, A);
    else
        ComputePosSum(num_rowsB, num_colsB, B);

    return 0;
}
