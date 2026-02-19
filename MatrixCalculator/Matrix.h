#pragma once

class Matrix
{
public:
	Matrix() = default;
	Matrix(int rows, int cols);

	int getRows() const;
	int getCols() const;
};