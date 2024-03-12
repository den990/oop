#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../MyList/CMyList.hpp"

#include <sstream>
#include <string>

TEST_CASE("Testing Constructors")
{
	SECTION("Constructed by default constructor")
	{
		CMyList<std::string> lst = CMyList<std::string>();
		REQUIRE(lst.IsEmpty());
		REQUIRE(lst.GetSize() == 0);
	}
	SECTION("Constructed by copying constructor")
	{
		CMyList<std::string> lst1 = CMyList<std::string>();
		lst1.PushBack("Hello");

		CMyList<std::string> lst2 = CMyList<std::string>(lst1);
		REQUIRE(lst2.GetSize() == lst1.GetSize());
	}
}

TEST_CASE("Testing Push elements")
{
	SECTION("PushBack")
	{
		CMyList<std::string> lst;
		lst.PushBack("1");
		lst.PushBack("2");
		lst.PushBack("3");

		REQUIRE(lst.GetSize() == 3);
	}
	SECTION("PushFront")
	{
		CMyList<std::string> lst;
		lst.PushFront("1");
		lst.PushFront("2");
		lst.PushFront("3");

		REQUIRE(lst.GetSize() == 3);
	}
}

TEST_CASE("Testing IsEmpty")
{
	SECTION("List is empty")
	{

		CMyList<std::string> lst;
		REQUIRE(lst.IsEmpty());
	}

	SECTION("List is not empty")
	{

		CMyList<std::string> lst;
		lst.PushFront("1");
		lst.PushFront("2");
		lst.PushFront("3");

		REQUIRE(!(lst.IsEmpty()));
	}
}

TEST_CASE("Testing Insertions")
{
	SECTION("Insert in the beginning of empty list")
	{
		CMyList<std::string> lst;
		std::string placedStr = "hello";
		lst.Insert(lst.begin(), placedStr);

		REQUIRE(*lst.begin() == placedStr);
		REQUIRE(lst.GetSize() == 1);
	}

	SECTION("Insert in the beginning of non empty list")
	{
		CMyList<std::string> lst;
		std::string placedStr = "hello";

		lst.Insert(lst.begin(), "123");
		lst.Insert(lst.begin(), placedStr);

		REQUIRE(*lst.begin() == placedStr);
		REQUIRE(lst.GetSize() == 2);
	}

	SECTION("Insert in the end of empty list")
	{

		CMyList<std::string> lst;
		std::string placedStr = "hello";
		lst.Insert(lst.end(), placedStr);

		REQUIRE(*--lst.end() == placedStr);
		REQUIRE(lst.GetSize() == 1);
	}

	SECTION("Insert in the end of non empty list")
	{
		CMyList<std::string> lst;
		std::string placedStr = "hello";

		lst.Insert(lst.end(), "123");
		lst.Insert(lst.end(), placedStr);

		REQUIRE(*--lst.end() == placedStr);
		REQUIRE(lst.GetSize() == 2);
	}
}

TEST_CASE("Testing Erase")
{
	SECTION("Erase empty list")
	{
		CMyList<std::string> lst;
		REQUIRE(lst.GetSize() == 0);
		REQUIRE_THROWS_AS(lst.Erase(lst.begin()), std::out_of_range);
	}
	SECTION("Erase existing element in list")
	{
		CMyList<std::string> lst;
		lst.PushBack("sor");
		REQUIRE(lst.GetSize() == 1);

		lst.Erase(lst.begin());
		REQUIRE(lst.GetSize() == 0);
	}
	SECTION("Erase out of range element in list")
	{
		CMyList<std::string> lst;
		lst.PushBack("sor");
		REQUIRE(lst.GetSize() == 1);

		REQUIRE_THROWS_AS(lst.Erase(++lst.begin()), std::out_of_range);
		REQUIRE(lst.GetSize() == 1);
	}
}

TEST_CASE("Testing Clear")
{
	CMyList<std::string> lst;
	lst.PushFront("1");
	lst.PushFront("2");
	lst.PushFront("3");

	REQUIRE(lst.GetSize() == 3);
	lst.Clear();

	REQUIRE(lst.GetSize() == 0);
}

TEST_CASE("Testing operator= copying")
{
	CMyList<std::string> lst;
	lst.PushFront("Hello ");
	lst.PushFront("world");

	CMyList<std::string> lstCopy = lst;
	REQUIRE(lstCopy.GetSize() == lst.GetSize());
}

TEST_CASE("Testing iterators")
{
	CMyList<std::string> lst;
	lst.PushBack("1");
	lst.PushBack("2");
	lst.PushBack("3");

	SECTION("Testing ++ and -- operators of iterator")
	{
		auto it = lst.cbegin();
		REQUIRE(*it == "1");
		it++;
		REQUIRE(*it == "2");
		++it;
		REQUIRE(*it == "3");
		it--;
		REQUIRE(*it == "2");
		--it;
		REQUIRE(*it == "1");
	}

	SECTION("Testing cbegin")
	{
		auto it = lst.cbegin();
		REQUIRE(*it == "1");
	}

	SECTION("Testing cend")
	{
		auto it = lst.cend();
		--it;
		REQUIRE(*it == "3");
	}

	SECTION("Testing begin")
	{
		auto it = lst.begin();
		REQUIRE(*it == "1");
	}

	SECTION("Testing end")
	{
		auto it = lst.end();
		--it;
		REQUIRE(*it == "3");
	}

	SECTION("Testing rcbegin")
	{
		auto it = lst.crbegin();
		REQUIRE(*it == "3");
	}

	SECTION("Testing rcend")
	{
		auto it = lst.crend();
		--it;
		REQUIRE(*it == "1");
	}

	SECTION("Testing rbegin")
	{
		auto it = lst.rbegin();
		REQUIRE(*it == "3");
	}

	SECTION("Testing rend")
	{
		auto it = lst.rend();
		--it;
		REQUIRE(*it == "1");
	}

	SECTION("dereference iterator")
	{
		auto it = lst.begin();
		REQUIRE(*it == "1");
		*it = "now definitely not 1";
		REQUIRE(*it == "now definitely not 1");
		*it = "1";
		REQUIRE(*it == "1");
	}
}

TEST_CASE("Test range-based for")
{
	std::string str1("Grind");

	std::string str2("Never");
	std::string str3("Stops");
	std::ostringstream outputStream;

	CMyList<std::string> lst;

	lst.PushBack(str1);
	lst.PushBack(str2);
	lst.PushBack(str3);
	REQUIRE(lst.GetSize() == 3);

	for (auto& element : lst)
	{
		outputStream << element;
	}

	REQUIRE(outputStream.str() == "GrindNeverStops");
}

TEST_CASE("Clear after creation")
{
	CMyList<std::string> lst;
	lst.PushBack("abc");
	lst.Clear();

	REQUIRE(lst.IsEmpty());

	lst.PushBack("def");

	REQUIRE(!lst.IsEmpty());
}

TEST_CASE("Testing int List")
{
	CMyList<int> lst;
	int firstN = 100;
	int secondN = 200;
	int thirdN = 300;

	lst.Insert(lst.begin(), secondN);
	lst.PushBack(thirdN);
	lst.PushFront(firstN);
	REQUIRE(lst.GetSize() == 3);

	std::ostringstream outputStream;
	for (auto& element : lst)
	{
		outputStream << element;
	}
	REQUIRE(outputStream.str() == "100200300");

	lst.Erase(lst.begin());
	REQUIRE(lst.GetSize() == 2);

	lst.Clear();
	REQUIRE(lst.IsEmpty());

	lst.PushBack(100500);

	CMyList<int> newLst(lst);
	REQUIRE(newLst.GetSize() == lst.GetSize());
	auto itLst = lst.begin();
	auto itNewLst = newLst.begin();
	REQUIRE(*itLst == *itNewLst);
}