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