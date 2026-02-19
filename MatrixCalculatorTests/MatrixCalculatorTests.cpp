#include "pch.h"
#include "CppUnitTest.h"
#include "../MatrixCalculator/matrix.h"
#include "../MatrixCalculator/matrix.cpp"

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
	};
}
