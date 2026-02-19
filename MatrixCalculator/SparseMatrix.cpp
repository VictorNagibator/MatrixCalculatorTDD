#include "SparseMatrix.h"
#include <stdexcept>

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

SparseMatrix SparseMatrix::add(SparseMatrix other) const
{
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("SparseMatrix dimensions must match for addition!");

    SparseMatrix result(rows, cols);
    // копируем все ненулевые элементы из текущей матрицы
    for (const auto& entry : data) {
        size_t i = entry.first.first;
        size_t j = entry.first.second;
        double val = entry.second;
        result.setElement(i, j, val);
    }

    // добавляем элементы из other
    for (const auto& entry : other.data) {
        size_t i = entry.first.first;
        size_t j = entry.first.second;
        double val = entry.second;
        double newVal = result.getElement(i, j) + val;
        result.setElement(i, j, newVal);
    }
    return result;
}