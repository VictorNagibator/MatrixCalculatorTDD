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
	if (rows != other.rows || cols != other.cols)
		throw std::invalid_argument("Matrix dimensions must match for subtraction!");

	Matrix result(rows, cols);
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			result.setElement(i, j, getElement(i, j) - other.getElement(i, j));
	return result;
}

double Matrix::determinant() const {
	if (rows != cols)
		throw std::invalid_argument("Determinant is defined only for square matrices");

	if (rows == 2) {
		return getElement(0, 0) * getElement(1, 1) - getElement(0, 1) * getElement(1, 0);
	}
	if (rows == 1) {
		return getElement(0, 0);
	}

	// общий случай: разложение по первой строке (простой рекурсивный вариант)
	double det = 0.0;
	int sign = 1;
	for (int j = 0; j < rows; ++j) {
		// создаём минор (rows - 1) x (rows - 1) без 0-й строки и j-го столбца
		Matrix minor(rows - 1, rows - 1);
		for (int i = 1; i < rows; ++i) {
			int colDest = 0;
			for (int k = 0; k < rows; ++k) {
				if (k == j) continue;
				minor.setElement(i - 1, colDest, getElement(i, k));
				++colDest;
			}
		}
		det += sign * getElement(0, j) * minor.determinant();
		sign = -sign;
	}
	return det;
}