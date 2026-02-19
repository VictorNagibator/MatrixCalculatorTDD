#pragma once

class SparseMatrix
{
public:
    SparseMatrix(int rows, int cols);

    int getRows() const;
    int getCols() const;
private:
    int rows = 0, cols = 0;
};

