#include "array.h"

Array::Array(unsigned int size) : _size(size) {
    if (size > MAX_SIZE)
        throw OversizeException("Array size must be less than 100!\n");
    _data = new int[_size];
    for (int i = 0; i < _size; ++i) {
        _data[i] = 0;
    }
}

int & Array::operator [] (unsigned int i) {
    if (i < 0 || i >= _size)
        throw InvalidIndexException("Invalid index: index is out of range!\n");
    return _data[i];
}

int Array::operator [] (unsigned int i) const {
    if (i < 0 || i >= _size)
        throw InvalidIndexException("Invalid index: index is out of range!\n");
    return _data[i];
}

void Array::resize(unsigned int new_size) {
    if (new_size > MAX_SIZE)
        throw OversizeException("Array size must be less than 100!\n");
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
