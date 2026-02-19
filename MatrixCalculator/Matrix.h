#pragma once

class Matrix
{
public:
	Matrix() = default;
	Matrix(int rows, int cols);

	int getRows() const;
	int getCols() const;
private:
	int rows = 0;
	int cols = 0;
};