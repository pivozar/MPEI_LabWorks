#include "matrix.h"

bool operator == (const MatrixCell& lhs, const MatrixCell& rhs) {
	return lhs.row == rhs.row && lhs.column == rhs.column;
}

bool operator != (const MatrixCell& lhs, const MatrixCell& rhs) {
	return !(lhs == rhs);
}

bool operator < (const MatrixCell& lhs, const MatrixCell& rhs) {
	return lhs.row < rhs.row || lhs.row == rhs.row && lhs.column < rhs.column;
}

SparseMatrix::SparseMatrix(unsigned int rows, unsigned int columns)
	: rows(rows), columns(columns), data() {}

SparseMatrix::SparseMatrix(const SparseMatrix& matrix)
	: rows(matrix.rows),
	columns(matrix.columns),
	data(matrix.data) {}

SparseMatrix& SparseMatrix::operator = (const SparseMatrix& matrix) {
	if (this == &matrix)
		return *this;
	rows = matrix.rows;
	columns = matrix.columns;
	data._clear();
	data = matrix.data;
	return *this;
}

void SparseMatrix::UpdateElement(unsigned int row, unsigned int column, int new_value) {
	MatrixCell new_cell = { row, column, new_value };
	if (data.GetHead() == nullptr) {
		if (new_value != 0)
			data.PushBack(new_cell);
		return;
	}
	auto it = data.GetHead();
	if (new_cell < it->value) {
		if (new_value != 0)
			data.PushFront(new_cell);
		return;
	}
	else if (new_cell == it->value) {
		if (new_value != 0) it->value = new_cell;
		else data.PopFront();
		return;
	}
	while (it->next != nullptr && it->next->value < new_cell) {
		it = it->next;
	}
	if (it->next == nullptr) {
		if (new_value != 0)
			data.PushBack(new_cell);
		return;
	}
	else if (it->next->value == new_cell) {
		auto old_it = it;
		it = it->next;
		if (new_value != 0) it->value = new_cell;
		else data.RemoveAfter(old_it);
	}
	else if (new_value != 0)
		data.InsertAfter(it, new_cell);
}

int SparseMatrix::GetElement(unsigned int row, unsigned int column) const {
	MatrixCell new_cell = { row, column, -1 };
	if (data.GetHead() == nullptr)
		return 0;

	auto it = data.GetHead();
	if (new_cell < it->value)
		return 0;
	else if (new_cell == it->value)
		return (it->value).value;
	while (it->next != nullptr && it->next->value < new_cell) {
		it = it->next;
	}
	if (it->next == nullptr)
		return 0;
	else if (it->next->value == new_cell) {
		auto old_it = it;
		it = it->next;
		return (it->value).value;
	}
	else return 0;
}

SparseMatrix SparseMatrix::Transpose() const {
	SparseMatrix res(rows, columns);
	for (auto i = data.GetHead(); i != nullptr; i = i->next) {
		res.UpdateElement((i->value).column, (i->value).row, (i->value).value);
	}
	return res;
}

SparseMatrix operator * (const int lhs, const SparseMatrix& rhs) {
	SparseMatrix res(rhs.rows, rhs.columns);
	for (auto i = rhs.data.GetHead(); i != nullptr; i = i->next)
		res.UpdateElement((i->value).row, (i->value).column, (i->value).value * lhs);
	return res;
}

SparseMatrix operator + (const SparseMatrix& lhs, const SparseMatrix& rhs) {
	if (lhs.rows != rhs.rows || lhs.columns != rhs.columns)
		throw std::invalid_argument("Matrices are incompatible!\n");

	SparseMatrix res(rhs.rows, rhs.columns);

	for (auto i = rhs.data.GetHead(); i != nullptr; i = i->next)
		res.UpdateElement((i->value).row, (i->value).column, (i->value).value + lhs.GetElement((i->value).row, (i->value).column));

	for (auto i = lhs.data.GetHead(); i != nullptr; i = i->next)
		res.UpdateElement((i->value).row, (i->value).column, (i->value).value + rhs.GetElement((i->value).row, (i->value).column));
	return res;
}

SparseMatrix operator - (const SparseMatrix& lhs, const SparseMatrix& rhs) { return lhs + (-1) * rhs; }

SparseMatrix operator * (const SparseMatrix& lhs, const SparseMatrix& rhs) {
	if (lhs.columns != rhs.rows)
		throw std::invalid_argument("Matrices are incompatible!\n");
	SparseMatrix res(lhs.rows, rhs.columns);
	for (int i = 0; i < lhs.rows; ++i) {
		for (int j = 0; j < rhs.columns; ++j) {
			int sum = 0;
			for (int s = 0; s < rhs.rows; ++s)
				sum += lhs.GetElement(i, s) * rhs.GetElement(s, j);
			res.UpdateElement(i, j, sum);
		}
	}
	return res;
}

bool operator == (const SparseMatrix& lhs, const SparseMatrix& rhs) {
	if (lhs.rows != rhs.rows || lhs.columns != rhs.columns)
		return false;
	auto j = lhs.data.GetHead();
	for (auto i = rhs.data.GetHead(); i != nullptr; i = i->next) {
		if ((i->value).value != (j->value).value)
			return false;
		j = j->next;
	}
	return true;
}

bool operator != (const SparseMatrix& lhs, const SparseMatrix& rhs) {
	return !(lhs == rhs);
}

void SparseMatrix::Print() const {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j)
			std::cout << GetElement(i, j) << ' ';
		std::cout << std::endl;
	}
}