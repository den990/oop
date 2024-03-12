#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include "../../../catch/catch.hpp"
#include "../HTMLDecode/Decode.h"

TEST_CASE("GetDecode function")
{
	SECTION("Reading empty string")
	{
		std::string emptyString;
		REQUIRE(GetDecode(emptyString) == "");
		REQUIRE(emptyString.empty());
	}
	SECTION("Reading not decoded string")
	{
		std::string checkString = "abcd";
		REQUIRE(GetDecode(checkString) == "abcd");
	}
	SECTION("Reading decoded strings")
	{
		std::string checkString = "&quot;";
		REQUIRE(GetDecode(checkString) == "\"");
		checkString = "&apos;";
		REQUIRE(GetDecode(checkString) == "'");
		checkString = "&lt;";
		REQUIRE(GetDecode(checkString) == "<");
		checkString = "&gt;";
		REQUIRE(GetDecode(checkString) == ">");
		checkString = "&amp;";
		REQUIRE(GetDecode(checkString) == "&");
	}
}
TEST_CASE("HtmlDecode function")
{
	SECTION("Reading empty string")
	{
		std::string emptyString;
		REQUIRE(HtmlDecode(emptyString) == "");
		REQUIRE(emptyString.empty());
	}
	SECTION("Reading decoded strings")
	{
		std::string notDecodedString = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
		REQUIRE(HtmlDecode(notDecodedString) == "Cat <says> \"Meow\". M&M's");
		notDecodedString = "&lt kdjdksjskjs &quot; lolkek";
		REQUIRE(HtmlDecode(notDecodedString) == "&lt kdjdksjskjs \" lolkek");
		notDecodedString = "&ltfd; kdjdksjskjs&quot; lolkek";
		REQUIRE(HtmlDecode(notDecodedString) == "&ltfd; kdjdksjskjs\" lolkek");
		notDecodedString = "&lt; kdjdksjskjs &quot fkfdjd &amp; lolkek";
		REQUIRE(HtmlDecode(notDecodedString) == "< kdjdksjskjs &quot fkfdjd & lolkek");
	}
	SECTION("No decoded strings")
	{
		std::string simpleString = "Sasha walked along the highway";
		REQUIRE(HtmlDecode(simpleString) == "Sasha walked along the highway");
		simpleString = "ghfghdghjkljfcfghrt";
		REQUIRE(HtmlDecode(simpleString) == "ghfghdghjkljfcfghrt");
	}
}