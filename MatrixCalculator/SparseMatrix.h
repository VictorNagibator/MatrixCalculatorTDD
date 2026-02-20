#pragma once
#include <map>

class SparseMatrix
{
public:
    SparseMatrix(int rows, int cols);

    int getRows() const;
    int getCols() const;

    double getElement(int i, int j) const;
    void setElement(int i, int j, double value);
    SparseMatrix add(SparseMatrix other) const;
    SparseMatrix multiply(SparseMatrix other) const;
    SparseMatrix multiply(double scalar) const;
    SparseMatrix subtract(SparseMatrix other) const;
private:
    int rows = 0, cols = 0;

    std::map<std::pair<int, int>, double> data;
};

