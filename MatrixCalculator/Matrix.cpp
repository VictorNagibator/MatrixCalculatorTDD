#include "Matrix.h"

Matrix::Matrix(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
}

int Matrix::getRows() const
{
	return rows;
}

int Matrix::getCols() const
{
	return cols;
}