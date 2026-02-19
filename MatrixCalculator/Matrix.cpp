#include "Matrix.h"
#include <stdexcept>

Matrix::Matrix(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;

	data = std::vector<double>(rows * cols, 0.0);
}

int Matrix::getRows() const
{
	return rows;
}

int Matrix::getCols() const
{
	return cols;
}

double Matrix::getElement(int i, int j) const
{
	if (i >= rows || j >= cols || i < 0 || j < 0)
		throw std::invalid_argument("Wrong matrix indexes!");

	return data[i * cols + j];
}

void Matrix::setElement(int i, int j, double value)
{
	if (i >= rows || j >= cols || i < 0 || j < 0)
		throw std::invalid_argument("Wrong matrix indexes!");

	data[i * cols + j] = value;
}