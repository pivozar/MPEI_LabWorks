#include "matrix.h"

Matrix::Matrix(unsigned int rows, unsigned int cols)
    : _rows(rows), _columns(cols), _elements_sum(0), _changed(true) {
    if (rows > MAX_SIZE || cols > MAX_SIZE)
        throw OversizeException("Matrix size must be less than 100 in both dimensions!\n");
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

Matrix::operator double () {
    return (_rows != 0 && _columns != 0) ? (GetSum() + .0)/(_rows*_columns) : 0;
}

Array & Matrix::operator [] (int i) const {
    if (i < 0 || i >= _rows)
        throw InvalidIndexException("Invalid index: indices are out of range!\n");
    return _data[i];
}

Array & Matrix::operator [] (int i) {
    if (i < 0 || i >= _rows)
        throw InvalidIndexException("Invalid index: indices are out of range!\n");
    _changed = true;
    return _data[i];
}

Matrix& Matrix::operator = (const Matrix &matrix) {
    if (*this == matrix)
        return *this;
    resize(matrix.GetRows(), matrix.GetColumns());
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _columns; ++j) {
            _data[i][j] = matrix[i][j];
        }
    }
    return *this;
}

Matrix operator * (const Matrix& lhs, const int rhs) {
    Matrix res(lhs.GetRows(), lhs.GetColumns());
    for (int i = 0; i < lhs.GetRows(); ++i) {
        for (int j = 0; j < lhs.GetColumns(); ++j) {
            res[i][j] = rhs * lhs[i][j];
        }
    }
    return res;
}

Matrix operator * (const int lhs, const Matrix& rhs) {
    return rhs * lhs;
}

Matrix operator + (const Matrix& lhs, const Matrix &rhs)  {
    if (lhs.GetRows() != rhs.GetRows() || lhs.GetColumns() != rhs.GetColumns())
        throw MatrixIncompatibilityException("Matrices are incompatible!\n");
    Matrix res(lhs.GetRows(), lhs.GetColumns());
    for (int i = 0; i < lhs.GetRows(); ++i) {
        for (int j = 0; j < lhs.GetColumns(); ++j) {
            res[i][j] = lhs[i][j] + rhs[i][j];
        }
    }
    return res;
}

Matrix operator - (const Matrix& lhs, const Matrix &rhs)  {
    return lhs + (-1)*rhs;
}

Matrix & Matrix::operator += (const int number) {
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _columns; ++j) {
            (*this)[i][j] += number;
        }
    }
    return *this;
}

bool Matrix::operator == (const Matrix &matrix) const {
    if (_rows != matrix.GetRows() || _columns != matrix.GetColumns())
        return false;
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _columns; ++j) {
            if ((*this)[i][j] != matrix[i][j])
                return false;
        }
    }
    return true;
}

bool Matrix::operator != (const Matrix &matrix) const {
    return !(*this == matrix);
}

void Matrix::resize(unsigned int new_rows, unsigned int new_columns) {
    if (new_rows > MAX_SIZE || new_columns > MAX_SIZE)
        throw OversizeException("Matrix size must be less than 100 in both dimensions!\n");
    delete [] _data;
    _rows = new_rows;
    _columns = new_columns;
    _data = new Array[_rows];
    for (int i = 0; i < _rows; ++i) {
        _data[i].resize(_columns);
    }
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
