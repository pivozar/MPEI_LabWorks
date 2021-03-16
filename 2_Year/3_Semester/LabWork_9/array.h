#pragma once
#include "exception.h"

class Array {
private:
    int *_data;
    unsigned int _size;
    enum { MAX_SIZE = 100 };
public:
    explicit Array(unsigned int size=0);
    int & operator [] (unsigned int i);
    int operator [] (unsigned int i) const;
    void resize(unsigned int new_size);
    ~Array();
};
