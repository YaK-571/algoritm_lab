#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_3.2/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		//проверка работает ли сортировка вставками на частном примере
		TEST_METHOD(TestMethod1)
		{
				int a[10]{ 8,12,6, 1, 17, 18, 200, 400, 11, 5 };

				insertionSort(a, a + 10 - 1, [](int a, int b) {return a < b; });

				Assert::IsTrue(a[2] == 6);
		}

		//проверка работает ли быстрая сортировка на частном примере
		TEST_METHOD(TestMethod2)
		{

			int a[10]{ 1,30,60,40,12,500,21,40,123,499 };

			quickSort(a, a + 10 - 1, [](int a, int b) {return a < b; });

			Assert::IsTrue(a[9] == 500);
		}

		//проверка совпадает ли результат у разных сортировок
		TEST_METHOD(TestMethod3)
		{

			int a[10]{ 10,9,8, 7, 6, 5, 4, 3, 2, 1 };
			int b[10]{ 10,9,8, 7, 6, 5, 4, 3, 2, 1 };

			insertionSort(a, a + 10 - 1, [](int a, int b) {return a < b; });
			quickSort(b, b + 10 - 1, [](int a, int b) {return a < b; });

			Assert::IsTrue(a[0] == b[0]);
			Assert::IsTrue(a[1] == b[1]);
			Assert::IsTrue(a[2] == b[2]);
			Assert::IsTrue(a[3] == b[3]);
			Assert::IsTrue(a[4] == b[4]);
			Assert::IsTrue(a[5] == b[5]);
			Assert::IsTrue(a[6] == b[6]);
			Assert::IsTrue(a[7] == b[7]);
			Assert::IsTrue(a[8] == b[8]);
			Assert::IsTrue(a[9] == b[9]);
		}

		//проверка того, что элементы действительн располагаются в нужном порядке
		TEST_METHOD(TestMethod4)
		{

			int a[10]{ 8,12,6, 1, 17, 4, 3, 400, 11, 2 };

			sort(a, a + 10 - 1, [](int a, int b) {return a < b; });

			Assert::IsTrue(a[0] == 1);
			Assert::IsTrue(a[1] == 2);
			Assert::IsTrue(a[2] == 3);
			Assert::IsTrue(a[3] == 4);
		}

		//проверка, что каждый элемент после сортировки не больше последующего
		TEST_METHOD(TestMethod5)
		{

			int a [10]{ 8,12,6, 1, 17, 18, 200, 400, 11, 5 };

			sort(a, a + 10 - 1, [](int a, int b) {return a < b; });

			int i = 0;
			while (i < 9)
			{
				Assert::IsTrue(a[i] <= a[i+1]);
				i = i + 1;
			}
		}

		
	};
}
