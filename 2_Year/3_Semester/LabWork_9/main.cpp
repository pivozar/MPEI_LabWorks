#include <cstdio>
#include <stdexcept>

#include "matrix.h"

void ReadMatrix(Matrix &m, char * filename);
void TestMatrix9(char *filename);
void TestMatrix11(char *filename);
void TestMatrix12(char *filename);
void TestArray();

int main(int argc, char *argv[]) {
    //TestArray();
    //TestMatrix9(argv[1]);
    //TestMatrix11(argv[1]);
    //TestMatrix12(argv[1]);
    return 0;
}

void ReadMatrix(Matrix& m, char *filename) {
    FILE *file = fopen(filename, "r");
    int r, c;
    fscanf(file, "%d%d", &r, &c);
    m.resize(r, c);
    for (int i = 0; i < m.GetRows(); ++i) {
        for (int j = 0; j < m.GetColumns(); ++j) {
            fscanf(file, "%d", &m[i][j]);
        }
    }
}

void TestMatrix9(char *filename) {
    Matrix m1;
    ReadMatrix(m1, filename);
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
}

void TestMatrix11(char *filename) {
    Matrix m1, m2, m3, m4;
    ReadMatrix(m1, filename);
    printf("m1:\n");
    m1.Print();
    m2 = m1 = m1;
    m3 = (-3)*m2;  /*m3 = m2*(-3); - без использования дружественных членов
                    класса, применение оператора умножения
                    матрицы на число с использованием числа
                    в качестве l-значения было бы невозможным
                    */
    m4 = m1 + m3;
    m3 = m2 - m4;
    m2 += 3;
    if (m4 == (-2)*m1) {
        printf("m4:\n");
        m4.Print();
    }
    m1.resize(2, 4);
    try {
        m2 = m1 + m3;
    }
    catch (std::invalid_argument & exc) {
        printf("%s\n", exc.what());
    }
    printf("m2\n");
    m2.Print();
    printf("m3\n");
    m3.Print();
}

void TestMatrix12(char *filename) {
    Matrix m1, m2, m3, m4;
    ReadMatrix(m1, filename);
    m2 = m1 = m1;
    m3 = (-3)*m2;
    m4 = m1 + m3;
    m3 = m2 - m4;
    m2 += 3;
    m1.resize(2, 4);
    try {
        Matrix m_temp(99, 55);
        //Matrix m_res = m1 + m3;
        m_temp[100][55] = 1;
    }
    catch (OversizeException & exc) {
        printf("%s\n", exc.what());
    }
    catch (MatrixIncompatibilityException & exc) {
        printf("%s\n", exc.what());
    }
    catch (InvalidIndexException & exc) {
        printf("%s\n", exc.what());
    }
}

void TestArray() {
    int n;
    scanf("%d", &n);
    Array a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    printf("%d\n", a[0] + a[n-1]);
    a.resize(3);
    printf("%d %d %d", a[0], a[1], a[2]);
}
