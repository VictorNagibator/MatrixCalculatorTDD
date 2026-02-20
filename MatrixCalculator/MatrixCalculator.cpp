#include <iostream>
#include <limits>
#include <stdexcept>
#include <sstream>
#include "matrix.h"
#include "sparsematrix.h"

// функци€ дл€ ввода обычной матрицы
static Matrix inputDenseMatrix() {
    int rows, cols;
    std::cout << "Enter number of rows and columns: ";
    std::cin >> rows >> cols;

    Matrix m(rows, cols);
    std::cout << "Enter matrix elements row by row (total " << rows * cols << " numbers):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double val;
            std::cin >> val;
            m.setElement(i, j, val);
        }
    }
    return m;
}

// функци€ дл€ ввода разреженной матрицы
static SparseMatrix inputSparseMatrix() {
    int rows, cols;
    std::cout << "Enter number of rows and columns: ";
    std::cin >> rows >> cols;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем буфер после ввода чисел

    SparseMatrix m(rows, cols);
    std::cout << "Enter non-zero elements as: row col value\n";
    std::cout << "Empty line to finish input.\n";
    while (true) {
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) break;

        std::istringstream iss(line);
        int i, j;
        double val;
        if (iss >> i >> j >> val) {
            if (i >= rows || j >= cols) {
                std::cout << "Error: indices out of range. Try again.\n";
                continue;
            }
            m.setElement(i, j, val);
        }
        else {
            std::cout << "Error: invalid format. Please enter three numbers: row col value\n";
        }
    }
    return m;
}

// функци€ дл€ вывода обычной матрицы
static void printMatrix(const Matrix& m) {
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            std::cout << m.getElement(i, j) << "\t";
        }
        std::cout << "\n";
    }
}

// функци€ дл€ вывода разреженной матрицы (в виде плотной, с нул€ми на месте отсутствующих элементов)
static void printSparseMatrix(const SparseMatrix& m) {
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            std::cout << m.getElement(i, j) << "\t";
        }
        std::cout << "\n";
    }
}

// очистка входного буфера после ввода чисел
static void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::cout << "========================================\n";
    std::cout << "=          MATRIX CALCULATOR           =\n";
    std::cout << "========================================\n";

    int choiceType;
    do {
        std::cout << "\nSelect matrix type:\n";
        std::cout << "1 - Dense matrix\n";
        std::cout << "2 - Sparse matrix\n";
        std::cout << "0 - Exit\n";
        std::cout << "Your choice: ";
        std::cin >> choiceType;
        clearInput();

        if (choiceType == 0) {
            std::cout << "Goodbye!\n";
            break;
        }

        if (choiceType != 1 && choiceType != 2) {
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }

        // меню операций дл€ выбранного типа
        int op;
        do {
            std::cout << "\n--- Operations ---\n";
            std::cout << "1 - Addition\n";
            std::cout << "2 - Subtraction\n";
            std::cout << "3 - Matrix multiplication\n";
            std::cout << "4 - Multiplication by scalar\n";
            std::cout << "5 - Determinant (square matrix only)\n";
            std::cout << "0 - Back to matrix type selection\n";
            std::cout << "Your choice: ";
            std::cin >> op;
            clearInput();

            if (op == 0) break;

            try {
                if (choiceType == 1) { // плотные матрицы
                    switch (op) {
                    case 1: { // сложение
                        std::cout << "First matrix:\n";
                        Matrix a = inputDenseMatrix();
                        std::cout << "Second matrix:\n";
                        Matrix b = inputDenseMatrix();
                        Matrix c = a.add(b);
                        std::cout << "Result:\n";
                        printMatrix(c);
                        break;
                    }
                    case 2: { // вычитание
                        std::cout << "First matrix:\n";
                        Matrix a = inputDenseMatrix();
                        std::cout << "Second matrix:\n";
                        Matrix b = inputDenseMatrix();
                        Matrix c = a.subtract(b);
                        std::cout << "Result:\n";
                        printMatrix(c);
                        break;
                    }
                    case 3: { // умножение матриц
                        std::cout << "First matrix:\n";
                        Matrix a = inputDenseMatrix();
                        std::cout << "Second matrix:\n";
                        Matrix b = inputDenseMatrix();
                        Matrix c = a.multiply(b);
                        std::cout << "Result:\n";
                        printMatrix(c);
                        break;
                    }
                    case 4: { // умножение на скал€р
                        std::cout << "Matrix:\n";
                        Matrix a = inputDenseMatrix();
                        std::cout << "Enter scalar: ";
                        double scalar;
                        std::cin >> scalar;
                        clearInput();
                        Matrix c = a.multiply(scalar);
                        std::cout << "Result:\n";
                        printMatrix(c);
                        break;
                    }
                    case 5: { // определитель
                        std::cout << "Matrix:\n";
                        Matrix a = inputDenseMatrix();
                        double det = a.determinant();
                        std::cout << "Determinant = " << det << "\n";
                        break;
                    }
                    default:
                        std::cout << "Invalid operation.\n";
                    }
                }
                else { // разреженные матрицы
                    switch (op) {
                    case 1: { // сложение
                        std::cout << "First matrix:\n";
                        SparseMatrix a = inputSparseMatrix();
                        std::cout << "Second matrix:\n";
                        SparseMatrix b = inputSparseMatrix();
                        SparseMatrix c = a.add(b);
                        std::cout << "Result:\n";
                        printSparseMatrix(c);
                        break;
                    }
                    case 2: { // вычитание
                        std::cout << "First matrix:\n";
                        SparseMatrix a = inputSparseMatrix();
                        std::cout << "Second matrix:\n";
                        SparseMatrix b = inputSparseMatrix();
                        SparseMatrix c = a.subtract(b);
                        std::cout << "Result:\n";
                        printSparseMatrix(c);
                        break;
                    }
                    case 3: { // умножение матриц
                        std::cout << "First matrix:\n";
                        SparseMatrix a = inputSparseMatrix();
                        std::cout << "Second matrix:\n";
                        SparseMatrix b = inputSparseMatrix();
                        SparseMatrix c = a.multiply(b);
                        std::cout << "Result:\n";
                        printSparseMatrix(c);
                        break;
                    }
                    case 4: { // умножение на скал€р
                        std::cout << "Matrix:\n";
                        SparseMatrix a = inputSparseMatrix();
                        std::cout << "Enter scalar: ";
                        double scalar;
                        std::cin >> scalar;
                        clearInput();
                        SparseMatrix c = a.multiply(scalar);
                        std::cout << "Result:\n";
                        printSparseMatrix(c);
                        break;
                    }
                    case 5: { // определитель
                        std::cout << "Matrix:\n";
                        SparseMatrix a = inputSparseMatrix();
                        double det = a.determinant();
                        std::cout << "Determinant = " << det << "\n";
                        break;
                    }
                    default:
                        std::cout << "Invalid operation.\n";
                    }
                }
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } while (true);

    } while (choiceType != 0);

    return 0;
}