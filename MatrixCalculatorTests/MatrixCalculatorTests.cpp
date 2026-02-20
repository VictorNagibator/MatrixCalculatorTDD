#include "pch.h"
#include "CppUnitTest.h"
#include "../MatrixCalculator/matrix.h"
#include "../MatrixCalculator/matrix.cpp"
#include "../MatrixCalculator/sparsematrix.h"
#include "../MatrixCalculator/sparsematrix.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixCalculatorTests
{
	TEST_CLASS(MatrixCalculatorTests)
	{
	public:
		TEST_METHOD(CanCreate)
		{
			Matrix m;
			Assert::IsTrue(true); // если компилируется, значит, фактически тест пройден
		}

		TEST_METHOD(CanCreateWithSize)
		{
			Matrix m(3, 4);
			Assert::AreEqual(3, m.getRows()); // проверка количества строк
			Assert::AreEqual(4, m.getCols()); // проверка количества столбцов
		}

		TEST_METHOD(CanCreateWithAnotherSize)
		{
			Matrix m(100, 20);
			Assert::AreEqual(100, m.getRows()); // проверка количества строк
			Assert::AreEqual(20, m.getCols()); // проверка количества столбцов
		}

		TEST_METHOD(SetAndGetElement)
		{
			Matrix m(2, 2);

			m.setElement(0, 0, 5.0);
			Assert::AreEqual(5.0, m.getElement(0, 0));
		}

		TEST_METHOD(SetElementAtWrongPosition)
		{
			Matrix m(2, 2);

			auto func = [&] { 
				// явно выход за границы
				m.setElement(3, 3, 5.0); 
				};
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(GetElementAtWrongPosition)
		{
			Matrix m(2, 2);

			auto func = [&] {
				// явно выход за границы
				m.getElement(3, 3);
				};
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(AddMatrixSameSize)
		{
			Matrix a(2, 2);
			a.setElement(0, 0, 1); a.setElement(0, 1, 1);
			a.setElement(1, 0, 1); a.setElement(1, 1, 1);

			Matrix b(2, 2);
			b.setElement(0, 0, 2); b.setElement(0, 1, 2);
			b.setElement(1, 0, 2); b.setElement(1, 1, 2);

			Matrix c = a.add(b);

			Assert::AreEqual(3.0, c.getElement(0, 0));
			Assert::AreEqual(3.0, c.getElement(0, 1));
			Assert::AreEqual(3.0, c.getElement(1, 0));
			Assert::AreEqual(3.0, c.getElement(1, 1));
		}

		TEST_METHOD(AddMatrixDifferentSize)
		{
			Matrix a(2, 2), b(3, 3);

			auto func = [&] {
				Matrix c = a.add(b); // складываем матрицы разных размеров - исключение
				};
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(MultiplyMatrixCorrectSize)
		{
			Matrix a(2, 2);
			a.setElement(0, 0, 1); a.setElement(0, 1, 2);
			a.setElement(1, 0, 3); a.setElement(1, 1, 4);

			Matrix e(2, 2);
			e.setElement(0, 0, 1); e.setElement(1, 1, 1);

			Matrix c = a.multiply(e);

			Assert::AreEqual(1.0, c.getElement(0, 0));
			Assert::AreEqual(2.0, c.getElement(0, 1));
			Assert::AreEqual(3.0, c.getElement(1, 0));
			Assert::AreEqual(4.0, c.getElement(1, 1));
		}

		TEST_METHOD(MultiplyMatrixDifferentSize)
		{
			Matrix a(2, 2), b(3, 3);

			auto func = [&] {
				Matrix c = a.multiply(b); // умножаем матрицы неподходящих размеров - исключение
				};
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(MultiplyByScalar)
		{
			Matrix a(2, 2);
			a.setElement(0, 0, 1); a.setElement(0, 1, 2);
			a.setElement(1, 0, 3); a.setElement(1, 1, 4);

			double scalar = 2.5;
			Matrix c = a.multiply(scalar);

			Assert::AreEqual(2.5, c.getElement(0, 0));
			Assert::AreEqual(5.0, c.getElement(0, 1));
			Assert::AreEqual(7.5, c.getElement(1, 0));
			Assert::AreEqual(10.0, c.getElement(1, 1));
		}

		TEST_METHOD(SubtractMatrices)
		{
			Matrix a(2, 2);
			a.setElement(0, 0, 5); a.setElement(0, 1, 6);
			a.setElement(1, 0, 7); a.setElement(1, 1, 8);

			Matrix b(2, 2);
			b.setElement(0, 0, 1); b.setElement(0, 1, 2);
			b.setElement(1, 0, 3); b.setElement(1, 1, 4);

			Matrix c = a.subtract(b);

			Assert::AreEqual(4.0, c.getElement(0, 0));
			Assert::AreEqual(4.0, c.getElement(0, 1));
			Assert::AreEqual(4.0, c.getElement(1, 0));
			Assert::AreEqual(4.0, c.getElement(1, 1));
		}

		TEST_METHOD(SubtractMatricesOtherValues)
		{
			Matrix a(2, 2);
			a.setElement(0, 0, 10); a.setElement(0, 1, 20);
			a.setElement(1, 0, 30); a.setElement(1, 1, 40);

			Matrix b(2, 2);
			b.setElement(0, 0, 1); b.setElement(0, 1, 2);
			b.setElement(1, 0, 3); b.setElement(1, 1, 4);

			Matrix c = a.subtract(b);

			Assert::AreEqual(9.0, c.getElement(0, 0));
			Assert::AreEqual(18.0, c.getElement(0, 1));
			Assert::AreEqual(27.0, c.getElement(1, 0));
			Assert::AreEqual(36.0, c.getElement(1, 1));
		}

		TEST_METHOD(Determinant2x2)
		{
			Matrix m(2, 2);
			m.setElement(0, 0, 1); m.setElement(0, 1, 2);
			m.setElement(1, 0, 3); m.setElement(1, 1, 4);

			double det = m.determinant();
			Assert::AreEqual(-2.0, det); // 1*4 - 2*3 = -2
		}

		TEST_METHOD(Determinant1x1)
		{
			Matrix m(1, 1);
			m.setElement(0, 0, 42.0);
			Assert::AreEqual(42.0, m.determinant());
		}

		TEST_METHOD(Determinant3x3)
		{
			Matrix m(3, 3);
			m.setElement(0, 0, 6); m.setElement(0, 1, 1); m.setElement(0, 2, 1);
			m.setElement(1, 0, 4); m.setElement(1, 1, -2); m.setElement(1, 2, 5);
			m.setElement(2, 0, 2); m.setElement(2, 1, 8); m.setElement(2, 2, 7);
			
			double det = m.determinant();
			Assert::AreEqual(-306.0, det);
		}
	};

	TEST_CLASS(SparseMatrixTest)
	{
	public:
		TEST_METHOD(CanCreateSparseMatrix)
		{
			SparseMatrix m(5, 5);

			Assert::AreEqual(5, m.getRows());
			Assert::AreEqual(5, m.getCols());
		}

		TEST_METHOD(SparseSetAndGet)
		{
			SparseMatrix m(10, 10);
			m.setElement(2, 3, 5.0);

			Assert::AreEqual(5.0, m.getElement(2, 3));
			Assert::AreEqual(0.0, m.getElement(0, 0));
		}

		TEST_METHOD(SparseAdd)
		{
			SparseMatrix a(3, 3);
			a.setElement(0, 0, 1); a.setElement(1, 1, 2); a.setElement(2, 2, 3);

			SparseMatrix b(3, 3);
			b.setElement(0, 0, 4); b.setElement(1, 1, 5); b.setElement(2, 2, 6);

			SparseMatrix c = a.add(b);

			Assert::AreEqual(5.0, c.getElement(0, 0));
			Assert::AreEqual(7.0, c.getElement(1, 1));
			Assert::AreEqual(9.0, c.getElement(2, 2));
			Assert::AreEqual(0.0, c.getElement(0, 1)); // не установлено, должно быть 0
		}

		TEST_METHOD(SparseAddAnother)
		{
			SparseMatrix a(3, 3);

			SparseMatrix b(3, 3);
			b.setElement(0, 0, 4);

			SparseMatrix c = a.add(b);

			Assert::AreEqual(4.0, c.getElement(0, 0));
			Assert::AreEqual(0.0, c.getElement(0, 1));
		}

		TEST_METHOD(SparseMultiply)
		{
			SparseMatrix a(2, 3);
			a.setElement(0, 0, 1); a.setElement(0, 2, 3);
			a.setElement(1, 1, 5);

			SparseMatrix b(3, 2);
			b.setElement(0, 0, 2); b.setElement(1, 1, 4); b.setElement(2, 0, 6);

			SparseMatrix c = a.multiply(b);
			// c(0,0) = 1*2 + 3*6 = 2+18=20
			// c(1,1) = 5*4 = 20
			// остальные нули
			Assert::AreEqual(20.0, c.getElement(0, 0));
			Assert::AreEqual(20.0, c.getElement(1, 1));
			Assert::AreEqual(0.0, c.getElement(0, 1));
		}

		TEST_METHOD(SparseMultiplyByScalar)
		{
			SparseMatrix a(2, 2);
			a.setElement(0, 0, 1); a.setElement(1, 1, 3);
			SparseMatrix c = a.multiply(2.5);

			Assert::AreEqual(2.5, c.getElement(0, 0));
			Assert::AreEqual(7.5, c.getElement(1, 1));
			Assert::AreEqual(0.0, c.getElement(0, 1));
		}

		TEST_METHOD(SparseSubtract)
		{
			SparseMatrix a(2, 2);
			a.setElement(0, 0, 5); a.setElement(1, 1, 8);

			SparseMatrix b(2, 2);
			b.setElement(0, 0, 1); b.setElement(1, 1, 3);

			SparseMatrix c = a.subtract(b);
			Assert::AreEqual(4.0, c.getElement(0, 0));
			Assert::AreEqual(5.0, c.getElement(1, 1));
		}

		TEST_METHOD(SparseAnotherSubtract)
		{
			SparseMatrix a(1, 1);
			a.setElement(0, 0, 6);

			SparseMatrix b(1, 1);
			b.setElement(0, 0, 1);

			SparseMatrix c = a.subtract(b);
			Assert::AreEqual(5.0, c.getElement(0, 0));
		}
	};
}
