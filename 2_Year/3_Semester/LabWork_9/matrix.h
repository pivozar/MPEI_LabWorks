#pragma once

class Matrix {
public:
    Matrix(unsigned int rows=0, unsigned int cols=0);
    Matrix(Matrix& matrix, int d=0);
    explicit Matrix(int number);

    operator double ();

    int* operator[](int i) const;
    int* operator[](int i);

    unsigned int GetColumns() const;
    unsigned int GetRows() const;
    int GetSum();

    void Print() const;

    ~Matrix();
private:
    int **_data;
    unsigned int _rows;
    unsigned int _columns;
    int _elements_sum;
    bool _changed;
    void UpdateSum();
};
