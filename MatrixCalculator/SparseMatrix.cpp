#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
}

int SparseMatrix::getRows() const
{
	return rows;
}

int SparseMatrix::getCols() const
{
	return cols;
}

void SparseMatrix::setElement(int i, int j, double value) {
    if (value == 0.0)
        data.erase({ i, j });
    else
        data[{i, j}] = value;
}

double SparseMatrix::getElement(int i, int j) const {
    auto it = data.find({ i, j });

    // если не найден, то 0 (в разряженных матрицах так)
    return (it != data.end()) ? it->second : 0.0;
}