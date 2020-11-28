#include "matrix.h"
#include <stdexcept>

Matrix::Matrix(int rows, int cols)
    : _rows(rows), _columns(cols), _elements_sum(0), _changed(true) {
    _data = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        _data[i] = new int[cols];
        for (int j = 0; j < _columns; ++j) {
            _data[i][j] = 0;
        }
    }
}

Matrix::Matrix(Matrix& matrix, const int d)
        : _rows(matrix.GetRows()),
        _columns(matrix.GetColumns()),
        _elements_sum(matrix.GetSum() + d*_rows*_columns),
        _changed(true) {
    _data = new int* [_rows];
    for (int i = 0; i < _rows; ++i) {
        _data[i] = new int[_columns];
        for (int j = 0; j < _columns; ++j) {
            _data[i][j] = matrix[i][j] + d;
        }
    }
}

Matrix::Matrix(int number) : Matrix (1, 1) {
    _data[0][0] = number;
}

Matrix::operator double() {
    return (GetSum() + .0)/(_rows*_columns);
}

int* Matrix::operator[](int i) const {
    if (i < 0 || i >= _rows)
        throw std::invalid_argument("invalid index");
    return _data[i];
}

int* Matrix::operator[](int i) {
    if (i < 0 || i >= _rows)
        throw std::invalid_argument("invalid index");
    _changed = true;
    return _data[i];
}

int Matrix::GetColumns() const {
    return _columns;
}

int Matrix::GetRows() const {
    return _rows;
}

int Matrix::GetSum() {
    if (_changed) {
        UpdateSum();
        _changed = false;
    }
    return _elements_sum;
}

void Matrix::UpdateSum() {
    _elements_sum = 0;
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _columns; ++j) {
            _elements_sum += _data[i][j];
        }
    }
}

void Matrix::Print() const {
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _columns; ++j) {
            printf("%d ", _data[i][j]);
        }
        printf("\n");
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < _rows; ++i)
        delete [] _data[i];
    delete [] _data;
}

//-----------------------------------------------------------------------------

Matrix::Array::Array(int size)
        : _size(size), _data(new int[size]){};

int & Matrix::Array::operator[](int i) {
    if (i < 0 || i >= _size)
        throw std::invalid_argument("invalid index");
    return _data[i];
}

int & Matrix::Array::operator[](int i) const {
    if (i < 0 || i >= _size)
        throw std::invalid_argument("invalid index");
    return _data[i];
}

Matrix::Array::~Array() {
    delete [] _data;
}

//-----------------------------------------------------------------------------