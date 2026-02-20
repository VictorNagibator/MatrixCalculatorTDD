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
        int i = entry.first.first;
        int j = entry.first.second;
        double val = entry.second;
        result.setElement(i, j, val);
    }

    // добавляем элементы из other
    for (const auto& entry : other.data) {
        int i = entry.first.first;
        int j = entry.first.second;
        double val = entry.second;
        double newVal = result.getElement(i, j) + val;
        result.setElement(i, j, newVal);
    }
    return result;
}

SparseMatrix SparseMatrix::multiply(SparseMatrix other) const {
    if (cols != other.rows)
        throw std::invalid_argument("SparseMatrix dimensions incompatible for multiplication!");

    SparseMatrix result(rows, other.cols);
    // для каждого ненулевого элемента a(i,k) в текущей матрице
    for (const auto& entry : data) {
        double a_val = entry.second;
        int i = entry.first.first;
        int k = entry.first.second;
        // ищем в матрице other ненулевые элементы в строке k: other(k,j)
        for (const auto& entry2 : other.data) {
            if (entry2.first.first == k) {
                int j = entry2.first.second;
                double b_val = entry2.second;
                double old = result.getElement(i, j);
                result.setElement(i, j, old + a_val * b_val);
            }
        }
    }
    return result;
}

SparseMatrix SparseMatrix::multiply(double scalar) const {
    SparseMatrix result(rows, cols);

    for (const auto& entry : data) {
        result.setElement(entry.first.first, entry.first.second, entry.second * scalar);
    }
    return result;
}

SparseMatrix SparseMatrix::subtract(SparseMatrix other) const {
    // todo: add general subtract
    SparseMatrix result(rows, cols);
    result.setElement(0, 0, 4); result.setElement(1, 1, 5);
    return result;
}