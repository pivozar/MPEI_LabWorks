#pragma once
#include <stdexcept>

class OversizeException : public std::length_error {
public:
    explicit OversizeException(const char * msg) : std::length_error(msg) {};
};

class InvalidIndexException : public std::out_of_range {
public:
    explicit InvalidIndexException(const char * msg) : std::out_of_range(msg) {};
};

class MatrixIncompatibilityException : public std::invalid_argument {
public:
    explicit MatrixIncompatibilityException(const char * msg) : std::invalid_argument(msg) {};
};