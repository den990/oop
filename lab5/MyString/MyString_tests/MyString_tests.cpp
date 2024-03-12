#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../MyString/CMyString.h"

TEST_CASE("Testing Constructors")
{
	SECTION("MyString with nullptr with 1 parametr")
	{
		CMyString mystr = CMyString(nullptr);
		REQUIRE(mystr.GetLength() == 0);
		REQUIRE(strcmp(mystr.GetStringData(), "") == 0);
	}
	SECTION("MyString with nullptr with 2 parametrs")
	{
		CMyString mystr = CMyString(nullptr, 1);
		REQUIRE(mystr.GetLength() == 0);
		REQUIRE(strcmp(mystr.GetStringData(), "") == 0);
	}
	SECTION("MyString is empty")
	{
		CMyString mystr = CMyString();
		REQUIRE(mystr.GetLength() == 0);
		REQUIRE(strcmp(mystr.GetStringData(), "") == 0);
	}

	SECTION("MyString contains C string")
	{
		const char* cStr = "Hello world";
		CMyString mystr = CMyString(cStr);

		REQUIRE(mystr.GetLength() == strlen(cStr));
		REQUIRE(strcmp(mystr.GetStringData(), cStr) == 0);
	}

	SECTION("MyString contains C string")
	{
		const char* cStr = "Hello \0world";
		CMyString mystr = CMyString(cStr, 12);

		REQUIRE(mystr.GetLength() == 12);
		REQUIRE(memcmp(mystr.GetStringData(), cStr, 12) == 0);
	}

	SECTION("MyString contains C string")
	{
		const char* cStr = "Hello world";
		int cStrLength = strlen(cStr);
		CMyString mystr = CMyString(cStr, cStrLength);

		REQUIRE(mystr.GetLength() == cStrLength);
		REQUIRE(strcmp(mystr.GetStringData(), cStr) == 0);
	}

	SECTION("MyString1 contains same string as MyString2")
	{
		const char* cStr = "Hello world";
		int cStrLength = strlen(cStr);

		CMyString mystr1 = CMyString(cStr, cStrLength);
		CMyString mystr2 = CMyString(mystr1);

		REQUIRE(mystr1.GetLength() == mystr2.GetLength());
		REQUIRE(strcmp(mystr1.GetStringData(), mystr2.GetStringData()) == 0);
	}

	SECTION("MyString contains same string as STL string")
	{
		std::string stlString = "This is STL string";

		CMyString mystr1 = CMyString(stlString);

		REQUIRE(mystr1.GetLength() == stlString.size());
		REQUIRE(strcmp(mystr1.GetStringData(), stlString.c_str()) == 0);
	}

	SECTION("MyString contains same \0 string as STL string")
	{
		std::string stlString = "This is STL string";

		CMyString mystr1 = CMyString(stlString);

		REQUIRE(mystr1.GetLength() == stlString.size());
		REQUIRE(strcmp(mystr1.GetStringData(), stlString.c_str()) == 0);
	}
}

TEST_CASE("Testing Clear")
{

	SECTION("MyString is still empty")
	{
		CMyString mystr;
		mystr.Clear();

		REQUIRE(strcmp(mystr.GetStringData(), "") == 0);
		REQUIRE(mystr.GetLength() == 0);
	}

	SECTION("MyString is empty")
	{
		CMyString mystr("This is STL string");
		mystr.Clear();

		REQUIRE(strcmp(mystr.GetStringData(), "") == 0);
		REQUIRE(mystr.GetLength() == 0);
	}
}

TEST_CASE("Testing GetLength")
{

	SECTION("Length is 0")
	{
		CMyString mystr;
		REQUIRE(mystr.GetLength() == 0);
	}

	SECTION("Length is correct size of string")
	{
		std::string stlString("STL");
		CMyString mystr(stlString);

		REQUIRE(mystr.GetLength() == stlString.size());
	}
}

TEST_CASE("Testing GetStringDate")
{

	SECTION("Data is empty string")
	{
		CMyString mystr;
		REQUIRE(strcmp(mystr.GetStringData(), "") == 0);
	}

	SECTION("Data is MyString data")
	{
		std::string stlString("STL");
		CMyString mystr(stlString);

		REQUIRE(strcmp(mystr.GetStringData(), stlString.c_str()) == 0);
	}
}

TEST_CASE("Testing SubString")
{

	SECTION("return correct substring")
	{
		CMyString mystr("Hello world");
		CMyString substring = mystr.SubString(1, 5);

		REQUIRE(strcmp(substring.GetStringData(), "ello ") == 0);
	}

	SECTION("return correct substring")
	{
		CMyString sNulls("Hello\0, world", 13);

		auto const subString = sNulls.SubString(0, 8);

		REQUIRE(memcmp(subString.GetStringData(), "Hello\0, ", 8) == 0);
	}
	SECTION("Empty substring")
	{
		CMyString sNulls("Hello\0, world", 13);

		auto const subString = sNulls.SubString(0, 0);

		REQUIRE(strcmp(subString.GetStringData(), "") == 0);
	}

	SECTION("throw exception")
	{
		std::ostringstream outputStream;
		CMyString mystr("Hello world");

		try
		{
			CMyString substring = mystr.SubString(mystr.GetLength() + 1, 5);
		}
		catch (const std::exception& e)
		{
			outputStream << e.what();
		}
		REQUIRE(outputStream.str() == "Start is very big");
	}
}

TEST_CASE("Testing << operator")
{

	SECTION("Put MyString Data in outputStream")
	{
		std::ostringstream outputStream;

		CMyString mystr("This is \0 nullish code symbol");
		outputStream << mystr;
		REQUIRE(outputStream.str() == mystr.GetStringData());
	}

	SECTION("Put MyString Data in outputStream")
	{
		std::ostringstream outputStream;

		CMyString mystr;
		outputStream << mystr;
		REQUIRE(outputStream.str() == mystr.GetStringData());
	}

	SECTION("Put MyString Data in outputStream")
	{
		std::ostringstream outputStream;

		CMyString mystr("This string is designed for << test");
		outputStream << mystr;
		REQUIRE(outputStream.str() == mystr.GetStringData());
	}
}

TEST_CASE("Testing operator >>")
{
	SECTION("Reading till ' '")
	{
		std::istringstream inputStream("Hello world");
		CMyString mystr;
		REQUIRE(inputStream >> mystr);
		CMyString correstStr = "Hello";
		REQUIRE(mystr == correstStr);
	}
	SECTION("Reading till '\n'")
	{
		std::istringstream inputStream("Helloworld\nworldhello");
		CMyString mystr;
		REQUIRE(inputStream >> mystr);
		CMyString correstStr = "Helloworld";
		REQUIRE(mystr == correstStr);
	}
	SECTION("Reading till 'eof'")
	{
		std::istringstream inputStream("Helloworld");
		CMyString mystr;
		CMyString correstStr = "Helloworld";

		inputStream >> mystr;
		REQUIRE(mystr == correstStr);
	}
}

TEST_CASE("Testing operator +=")
{
	SECTION("First CMyString is empty")
	{
		CMyString str1 = "";
		CMyString str2 = "";

		str1 += str2;
		REQUIRE(strcmp(str1.GetStringData(), "") == 0);
	}

	SECTION("CMyString contains first its data and other's data")
	{
		CMyString str1 = "Hello ";
		CMyString str2 = "world!";

		str1 += str2;
		REQUIRE(strcmp(str1.GetStringData(), "Hello world!") == 0);
	}
}

TEST_CASE("Testing operator +")
{

	SECTION("First CMyString is empty")
	{
		CMyString str1 = "";
		CMyString str2 = "";

		CMyString str3 = str1 + str2;
		REQUIRE(strcmp(str3.GetStringData(), "") == 0);
	}

	SECTION("Result CMyString contains data of both CMyStrings")
	{
		CMyString str1 = "Hello ";
		CMyString str2 = "world!";

		CMyString str3 = str1 + str2;
		REQUIRE(strcmp(str3.GetStringData(), "Hello world!") == 0);
	}

	SECTION("Result CMyString contains data of both CMyString and std::string")
	{
		std::string str1 = "Hello ";
		CMyString str2 = "world!";

		CMyString str3 = str1 + str2;
		REQUIRE(strcmp(str3.GetStringData(), "Hello world!") == 0);
	}

	SECTION("Result CMyString contains data of both CMyString and const char*")
	{
		CMyString str2 = "world!";

		CMyString str3 = "Hello " + str2;
		REQUIRE(strcmp(str3.GetStringData(), "Hello world!") == 0);
	}

	SECTION("Result CMyString contains data of both CMyString and const char*")
	{
		CMyString str1("Hello \0", 7);

		CMyString str2("wo\0rld!", 6);
		CMyString strResult = str1 + str2;
		REQUIRE(memcmp(strResult.GetStringData(), "Hello \0wo\0rld!", 13) == 0);
	}
}

TEST_CASE("Testing operator ==")
{

	SECTION("return true")
	{
		CMyString str1 = "Hi";
		CMyString str2 = "Hi";

		REQUIRE(str1 == str2);
	}

	SECTION("return false")
	{
		CMyString str1 = "Hi";
		CMyString str2 = "Not Hi";

		REQUIRE(!(str1 == str2));
	}
}

TEST_CASE("Testing operator !=")
{

	SECTION("return false")
	{
		CMyString str1 = "Hi";
		CMyString str2 = "Hi";

		REQUIRE(!(str1 != str2));
	}

	SECTION("return true")
	{
		CMyString str1 = "Hi";
		CMyString str2 = "Definitely Not Hi";

		REQUIRE(str1 != str2);
	}
}

TEST_CASE("Testing >, <, >=, <= operators")
{
	SECTION("CMyStrings are equal")
	{
		CMyString str1 = "Hi";
		CMyString str2 = "Hi";
		REQUIRE(!(str1 > str2));
		REQUIRE(!(str1 < str2));
		REQUIRE(str1 >= str2);
		REQUIRE(str1 <= str2);
	}
	SECTION("First CMyString is greater(ASCII) than second one")
	{
		CMyString str1 = "aab";
		CMyString str2 = "aaa";
		REQUIRE(str1 > str2);
		REQUIRE(!(str1 < str2));
		REQUIRE(str1 >= str2);
		REQUIRE(!(str1 <= str2));
	}
	SECTION("First CMyString is lesser(ASCII) than second one")
	{
		CMyString str1 = "aaaaaa";
		CMyString str2 = "aab";
		REQUIRE(!(str1 > str2));
		REQUIRE(str1 < str2);
		REQUIRE(!(str1 >= str2));
		REQUIRE(str1 <= str2);
	}
}

TEST_CASE("Testing operator []")
{
	SECTION("Reading []")
	{
		const CMyString str("Hello world");
		REQUIRE(str[0] == 'H');
	}
	SECTION("Writing []")
	{
		CMyString str1("Hello world");
		str1[0] = 'e';
		CMyString correctStr = "eello world";
		REQUIRE(str1 == correctStr);
	}
}

TEST_CASE("Testing moving")
{
	SECTION("Moved string is empty and string where we have moved contains data of first one")
	{
		CMyString firstString("Hello world");
		CMyString secondString(std::move(firstString));

		REQUIRE(std::strcmp(firstString.GetStringData(), "") == 0);
		REQUIRE(firstString.GetLength() == 0);

		REQUIRE(std::strcmp(secondString.GetStringData(), "Hello world") == 0);
	}

	SECTION("Moved string is empty and string where we have moved contains data of first one")
	{
		CMyString firstString("Hello world");
		CMyString secondString = std::move(firstString);

		REQUIRE(std::strcmp(firstString.GetStringData(), "") == 0);
		REQUIRE(firstString.GetLength() == 0);

		REQUIRE(std::strcmp(secondString.GetStringData(), "Hello world") == 0);
	}

	SECTION("New string which is based on movedOut string has nullish length")
	{

		CMyString movedOutString("Hello world");
		CMyString movedInString(std::move(movedOutString));

		CMyString movedOutBasedString(movedOutString);
		REQUIRE(movedOutBasedString.GetLength() == 0);
	}
}