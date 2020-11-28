#pragma once

class Array {
private:
    int *_data;
    unsigned int _size;
public:
    explicit Array(unsigned int size=0);
    int & operator[](unsigned int i);
    int & operator[](unsigned int i) const;
    void resize(unsigned int new_size);
    ~Array();
};

class Matrix {
public:
    Matrix(unsigned int rows=0, unsigned int cols=0);
    Matrix(Matrix& matrix, int d=0);
    explicit Matrix(int number);

    operator double ();

    Array & operator[](int i) const;
    Array & operator[](int i);

    Matrix& operator = (const Matrix& matrix);

    Matrix operator * (const int number) const;
    Matrix operator + (const Matrix& matrix) const;
    Matrix operator - (const Matrix& matrix) const;
    void operator += (const int number);

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
    void UpdateSum();
};
