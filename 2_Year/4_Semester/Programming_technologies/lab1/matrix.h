#pragma once
#include "list.h"
#include <stdexcept>
#include <iostream>

struct MatrixCell {
	unsigned int row;
	unsigned int column;
	int value;
};

class SparseMatrix {
public:
	unsigned int rows;
	unsigned int columns;
	List<MatrixCell> data;

	SparseMatrix(unsigned int rows = 0, unsigned int cols = 0);
	SparseMatrix(const SparseMatrix& matrix);

	int GetElement(unsigned int row, unsigned int column) const;
	void UpdateElement(unsigned int row, unsigned int column, int new_value);

	SparseMatrix& operator = (const SparseMatrix& matrix);
	friend SparseMatrix operator * (const int lhs, const SparseMatrix& rhs);
	friend SparseMatrix operator + (const SparseMatrix& lhs, const SparseMatrix& rhs);
	friend SparseMatrix operator * (const SparseMatrix& lhs, const SparseMatrix& rhs);
	friend SparseMatrix operator - (const SparseMatrix& lhs, const SparseMatrix& rhs);
	
	friend bool operator == (const SparseMatrix& lhs, const SparseMatrix& rhs);
	friend bool operator != (const SparseMatrix& lhs, const SparseMatrix& rhs);
	
	SparseMatrix Transpose() const;

	void Print() const;
};