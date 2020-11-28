#include "matrix.h"
#include <stdexcept>

Matrix::Matrix(unsigned int rows, unsigned int cols)
    : _rows(rows), _columns(cols), _elements_sum(0), _changed(true) {
    _data = new Array[_rows];
    for (int i = 0; i < _rows; ++i) {
        _data[i].resize(_columns);
    }
}

Matrix::Matrix(Matrix& matrix, int d)
        : _rows(matrix.GetRows()),
        _columns(matrix.GetColumns()),
        _elements_sum(matrix.GetSum() + (signed)(d*_rows*_columns)),
        _changed(true) {
    _data = new Array [_rows];
    for (int i = 0; i < _rows; ++i) {
        _data[i].resize(_columns);
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

Array & Matrix::operator[](int i) const {
    if (i < 0 || i >= _rows)
        throw std::invalid_argument("invalid index");
    return _data[i];
}

Array & Matrix::operator[](int i) {
    if (i < 0 || i >= _rows)
        throw std::invalid_argument("invalid index");
    _changed = true;
    return _data[i];
}

unsigned int Matrix::GetColumns() const {
    return _columns;
}

unsigned int Matrix::GetRows() const {
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
    delete [] _data;
}

//-----------------------------------------------------------------------------

Array::Array(unsigned int size) : _size(size) {
    _data = new int[_size];
    for (int i = 0; i < _size; ++i) {
        _data[i] = 0;
    }
}

int & Array::operator[](unsigned int i) {
    if (i < 0 || i >= _size)
        throw std::invalid_argument("invalid index");
    return _data[i];
}

int & Array::operator[](unsigned int i) const {
    if (i < 0 || i >= _size)
        throw std::invalid_argument("invalid index");
    return _data[i];
}

void Array::resize(unsigned int new_size) {
    delete [] _data;
    _data = new int[new_size];
    _size = new_size;
    for (int i = 0; i < _size; ++i) {
        _data[i] = 0;
    }
}

Array::~Array() {
    delete [] _data;
}

//-----------------------------------------------------------------------------
