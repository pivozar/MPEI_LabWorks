#include <cstdio>
#include "matrix.h"

void ReadMatrix(Matrix &m);

int main(int argc, char *argv[]) {
    int r, c;
    scanf("%d%d", &r, &c);
    Matrix m1(r, c);
    ReadMatrix(m1);
    printf("------------\nm1:\n");
    m1.Print();
    printf("------------\nm2:\n");
    Matrix m2 = Matrix(m1);
    m2.Print();
    printf("------------\nm3:\n");
    Matrix m3 = Matrix(m1, 5);
    m3.Print();
    printf("------------\nm4:\n");
    Matrix m4 = Matrix(2);
    m4.Print();
    printf("m3 average: %.2lf\n", double(m3));
    return 0;
}

void ReadMatrix(Matrix& m) {
    for (int i = 0; i < m.GetRows(); ++i) {
        for (int j = 0; j < m.GetColumns(); ++j) {
            scanf("%d", &m[i][j]);
        }
    }
}