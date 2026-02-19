#pragma once
#include <vector>

class Matrix
{
public:
	Matrix() = default;
	Matrix(int rows, int cols);

	int getRows() const;
	int getCols() const;

	double getElement(int i, int j) const;
	void setElement(int i, int j, double value);

	Matrix add(Matrix another) const;
	Matrix multiply(Matrix another) const;
	Matrix multiply(double scalar) const;
	Matrix subtract(Matrix another) const;
	double determinant() const;
private:
	int rows = 0;
	int cols = 0;

	std::vector<double> data;
};