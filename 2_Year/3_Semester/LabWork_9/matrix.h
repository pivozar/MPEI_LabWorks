#pragma once
#include "array.h"
#include "exception.h"

class Matrix {
public:
    Matrix(unsigned int rows=0, unsigned int cols=0);
    Matrix(Matrix& matrix, int d=0);
    explicit Matrix(int number);

    operator double ();
    Array operator [] (int i) const;
    Array & operator [] (int i);
    Matrix& operator = (const Matrix& matrix);
    friend Matrix operator * (const int lhs, const Matrix& rhs);
    friend Matrix operator * (const Matrix& lhs, const int rhs);
    friend Matrix operator + (const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator - (const Matrix& lhs, const Matrix& rhs);
    Matrix & operator += (const int number);
    bool operator == (const Matrix& matrix) const;
    bool operator != (const Matrix& matrix) const;

    void resize(unsigned int new_rows, unsigned int new_columns);
    unsigned int GetColumns() const;
    unsigned int GetRows() const;
    int GetSum();
    void Print() const;

    ~Matrix();
private:
    Array *_data;
    unsigned int _rows;
    unsigned int _columns;
    int _elements_sum;
    bool _changed;
    enum { MAX_SIZE = 100 };
    void UpdateSum();
};
