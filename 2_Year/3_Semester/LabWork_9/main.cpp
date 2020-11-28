#include <cstdio>
#include "matrix.h"

int ReadMatrix(Matrix& m, char *filename);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("More arguments required!\n");
        return 1;
    }
    Matrix m1; m1.Print();
    printf("------------\nm1:\n");

    if (!ReadMatrix(m1, argv[1]))
        return 1;

    m1.Print();
    printf("------------\nm2:\n");
    Matrix m2 = Matrix(m1);
    m2.Print();
    printf("------------\nm3:\n");
    Matrix m3 = Matrix(m1, 5);
    m3.Print();
    printf("------------\n");
    Matrix m4 = 2;
    m4.Print();
    printf("m3 average: %.2lf", double(m3));
    return 0;
}

int ReadMatrix(Matrix& m, char *filename) {
    int r, c, tmp;
    FILE *file;
    if ((file = fopen(filename, "r")) == nullptr) {
        printf("Impossible to open file: '%s'\n", filename);
        return 0;
    }
    if (fscanf(file, "%d%d", &r, &c) < 1) {
        printf("Impossible to read from file: '%s'\n", filename);
        return 0;
    }
    m = Matrix(r, c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            fscanf(file, "%d", &tmp);
            m[i][j] = tmp;
        }
    }
    fclose(file);
    return 1;
}