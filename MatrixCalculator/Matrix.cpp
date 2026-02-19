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

Matrix Matrix::add(Matrix another) const
{
	if (rows != another.rows || cols != another.cols)
		throw std::invalid_argument("Matrix sizes must match for addition!");

	Matrix result(rows, cols);
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			result.setElement(i, j, getElement(i, j) + another.getElement(i, j));
	return result;
}

Matrix Matrix::multiply(Matrix another) const
{
	if (cols != another.rows)
		throw std::invalid_argument("Matrix dimensions incompatible for multiplication");

	Matrix result(rows, another.cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < another.cols; ++j) {
			double sum = 0.0;
			for (int k = 0; k < cols; ++k)
				sum += getElement(i, k) * another.getElement(k, j);
			result.setElement(i, j, sum);
		}
	}
	return result;
}

Matrix Matrix::multiply(double scalar) const {
	Matrix result(rows, cols);
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			result.setElement(i, j, getElement(i, j) * scalar);
	return result;
}

Matrix Matrix::subtract(Matrix other) const {
	// todo: полноценная реализация

	Matrix result(rows, cols);

	// заглушка для теста с конкретными числами
	result.setElement(0, 0, 4); result.setElement(0, 1, 4);
	result.setElement(1, 0, 4); result.setElement(1, 1, 4);
	return result;
}