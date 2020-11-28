#pragma once

class Matrix {
public:
    Matrix(int rows=0, int cols=0);
    Matrix(Matrix& matrix, int d=0);
    explicit Matrix(int number);

    operator double ();

    int* operator[](int i) const;
    int* operator[](int i);

    int GetColumns() const;
    int GetRows() const;
    int GetSum();

    void Print() const;

    ~Matrix();
private:
    class Array {
    private:
        int *_data;
        int _size;
    public:
        explicit Array(int size=1);
        int& operator [] (int i) const;
        int& operator [] (int i);
        ~Array();
    };
    int **_data;
    int _rows;
    int _columns;
    int _elements_sum;
    bool _changed;
    void UpdateSum();
};