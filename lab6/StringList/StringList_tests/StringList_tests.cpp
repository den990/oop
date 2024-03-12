#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../StringList/CStringList.h"

TEST_CASE("Testing Constructors")
{
	SECTION("Constructed by default constructor")
	{
			CStringList lst = CStringList();
			REQUIRE(lst.IsEmpty());
			REQUIRE(lst.GetSize() == 0);
	}
	SECTION("Constructed by copying constructor")
	{
			CStringList lst1 = CStringList();
			lst1.PushBack("Hello");

			CStringList lst2 = CStringList(lst1);
			REQUIRE(lst2.GetSize() == lst1.GetSize());
	}
	SECTION("Constructed by moved-out constructor")
	{

			CStringList lst1 = CStringList();
			lst1.PushBack("Hello");

			CStringList lst2 = CStringList(std::move(lst1));
			REQUIRE(lst2.GetSize() == 1);

			REQUIRE(lst1.GetSize() == 0);
	}
}

TEST_CASE("Testing Push elements")
{
	SECTION("PushBack")
	{
			CStringList lst;
			lst.PushBack("1");
			lst.PushBack("2");
			lst.PushBack("3");

			REQUIRE(lst.GetSize() == 3);
	}
	SECTION("PushFront")
	{
			CStringList lst;
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
			CStringList lst;
			REQUIRE(lst.IsEmpty());
	}

	SECTION("List is not empty")
	{

			CStringList lst;
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
			CStringList lst;
			std::string placedStr = "hello";
			lst.Insert(lst.begin(), placedStr);

			REQUIRE(*lst.begin() == placedStr);
			REQUIRE(lst.GetSize() == 1);

	}

	SECTION("Insert in the beginning of non empty list")
	{

			CStringList lst;
			std::string placedStr = "hello";

			lst.Insert(lst.begin(), "123");
			lst.Insert(lst.begin(), placedStr);

			REQUIRE(*lst.begin() == placedStr);
			REQUIRE(lst.GetSize() == 2);

	}

	SECTION("Insert in the end of empty list")
	{

			CStringList lst;
			std::string placedStr = "hello";
			lst.Insert(lst.end(), placedStr);

			REQUIRE(*--lst.end() == placedStr);
			REQUIRE(lst.GetSize() == 1);
	}

	SECTION("Insert in the end of non empty list")
	{

			CStringList lst;
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

			CStringList lst;
			REQUIRE(lst.GetSize() == 0);
			REQUIRE_THROWS_AS(lst.Erase(lst.begin()), std::out_of_range);

	}
	SECTION("Erase existing element in list")
	{
			CStringList lst;
			lst.PushBack("sor");
			REQUIRE(lst.GetSize() == 1);

			lst.Erase(lst.begin());
			REQUIRE(lst.GetSize() == 0);

	}
	SECTION("Erase out of range element in list")
	{
			CStringList lst;
			lst.PushBack("sor");
			REQUIRE(lst.GetSize() == 1);

			REQUIRE_THROWS_AS(lst.Erase(++lst.begin()), std::out_of_range);
			REQUIRE(lst.GetSize() == 1);
	}
}

TEST_CASE("Testing Clear")
{
	CStringList lst;
	lst.PushFront("1");
	lst.PushFront("2");
	lst.PushFront("3");

	REQUIRE(lst.GetSize() == 3);
	lst.Clear();

	REQUIRE(lst.GetSize() == 0);
}

TEST_CASE("Testing operator= copying")
{
	CStringList lst;
	lst.PushFront("Hello ");
	lst.PushFront("world");

	CStringList lstCopy = lst;
	REQUIRE(lstCopy.GetSize() == lst.GetSize());
}

TEST_CASE("Testing operator= move-out")
{
	CStringList lstMovedOut;
	lstMovedOut.PushFront("Hello ");
	lstMovedOut.PushFront("world");
	size_t lengthMoveOut = lstMovedOut.GetSize();

	CStringList lst = std::move(lstMovedOut);
	REQUIRE(lst.GetSize() == lengthMoveOut);
	REQUIRE(lstMovedOut.GetSize() == 0);
}

TEST_CASE("Testing iterators")
{
	CStringList lst;
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

	CStringList lst;

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
	CStringList lst;
	lst.PushBack("abc");
	lst.Clear();

	REQUIRE(lst.IsEmpty());

	lst.PushBack("def");

	REQUIRE(!lst.IsEmpty());
}

TEST_CASE("Testing valid move-out object")
{
	CStringList lst1;
	lst1.PushBack("per ");
	lst1.PushBack("aspera ");
	lst1.PushBack("ad ");
	lst1.PushBack("astra.");
	REQUIRE(lst1.GetSize() == 4);

	CStringList lst2(std::move(lst1));
	REQUIRE(lst2.GetSize() == 4);
	REQUIRE(lst1.GetSize() == 0);

	lst1.PushBack("per aspera ad astra");
	REQUIRE(lst1.GetSize() == 1);
}