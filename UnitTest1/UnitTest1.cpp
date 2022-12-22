#include "pch.h"
#include "CppUnitTest.h"
#include "../IT_DB/Data.h"
#include "../IT_DB/Data.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Table table;
			table.addcol("product", Type::String, 3);
			table.change_cell(1, 0, Value("pear"));
			table.change_cell(1, 1, Value("melon"));
			table.change_cell(1, 2, Value("apple"));
			vector<Value> column{ Value(1.1), Value(3.3), Value(2.2) };
			table.addcol("weight", Type::Real, column);
			vector<Value> column2{ Value((unsigned)7777), Value((unsigned)9007), Value((unsigned)10001) };
			table.addcol("time", Type::Time, column2);
			vector<Value> column3{ Value(make_pair(7777, 10001)), Value(make_pair(6666, 7777)), Value(make_pair(5555, 6666)) };
			table.addcol("time_invl", Type::TimeInvl, column3);
			Assert::AreEqual((string)"pear", table.table[1].column[0].string_value);
			table.sort(3, 0);
			int id = table.table[0].column[0].integer_value;
			Assert::AreEqual((string)"apple", table.table[1].column[id].string_value);
			table.sort(2, 0);
			id = table.table[0].column[0].integer_value;
			Assert::AreEqual((string)"melon", table.table[1].column[id].string_value);
		}

		TEST_METHOD(TestMethod2)
		{
			Table table;
			table.addcol("product", Type::String, 3);
			table.change_cell(1, 0, Value("pear"));
			table.change_cell(1, 1, Value("melon"));
			table.change_cell(1, 2, Value("apple"));
			vector<Value> column{ Value(11), Value(33), Value(22) };
			table.addcol("quantity", Type::Integer, column);
			vector<Value> column2{ Value('a'), Value('b'), Value('c') };
			table.addcol("symbol", Type::Char, column2);
			table.addrow();
			table.addrow();
			table.change_cell(1, 3, Value("pineapple"));
			table.change_cell(1, 4, Value("grape"));
			table.change_cell(2, 3, Value(44));
			table.change_cell(2, 4, Value(55));
			table.change_cell(3, 3, Value('d'));
			table.change_cell(3, 4, Value('e'));
			table.deleterow(1); //видаляємо рядок "melon"
			table.deleterow(1); //видаляємо рядок "apple"
			Assert::AreEqual((string)"pear", table.table[1].column[0].string_value);
			Assert::AreEqual((string)"pineapple", table.table[1].column[1].string_value);
			Assert::AreEqual((string)"grape", table.table[1].column[2].string_value);
		}

		TEST_METHOD(TestMethod3)
		{
			Table table;
			table.addcol("product", Type::String, 3);
			table.change_cell(1, 0, Value("pear"));
			table.change_cell(1, 1, Value("melon"));
			table.change_cell(1, 2, Value("apple"));
			vector<Value> column{ Value((unsigned)7777), Value((unsigned)9007), Value((unsigned)10001) };
			table.addcol("time", Type::Time, column);
			vector<Value> column2{ Value(make_pair(7777, 10001)), Value(make_pair(6666, 7777)), Value(make_pair(5555, 6666)) };
			table.addcol("time_invl", Type::TimeInvl, column2);
			vector<Value> column3{ Value(11), Value(33), Value(22) };
			table.addcol("quantity", Type::Integer, column3);
			vector<Value> column4{ Value('a'), Value('b'), Value('c') };
			table.addcol("symbol", Type::Char, column4);
			table.deletecol(2); //видаляємо колонку "quantity"
			table.deletecol(2); //видаляємо колонку "symbol"
			Assert::AreEqual((string)"pear", table.table[1].column[0].string_value);
			Assert::AreEqual(11, table.table[2].column[0].integer_value);
			Assert::AreEqual('a', table.table[3].column[0].char_value);
		}
	};
}
