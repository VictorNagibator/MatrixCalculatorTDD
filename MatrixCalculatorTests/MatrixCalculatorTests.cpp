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
	};
}
