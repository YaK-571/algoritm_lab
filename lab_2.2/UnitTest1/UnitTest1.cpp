#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_2.2/Array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Array<std::string> a;

			a.insert("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
			a.insert("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
			a.insert("CCCC");
			Assert::IsTrue(a[1] == "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
		}

		TEST_METHOD(TestMethod2)
		{
			Array<int> a;

			a.insert(1);
			a.insert(2);
			a.insert(3);
			a.insert(4);

			Assert::IsTrue(a.size_i() == 4);
		}

		TEST_METHOD(TestMethod3)
		{
			Array<int> a;

			a.insert(1);
			a.insert(2);
			a.insert(3);
			a.insert(0, 4);

			Assert::IsTrue(a[0] == 4);
		}

		TEST_METHOD(TestMethod4)
		{
			Array<int> a;

			a.insert(1);
			a.insert(2);
			a.insert(3);
			a.insert(4);

			a.remove(0);
			Assert::IsTrue(a[0] == 2);
		}
	};
}
