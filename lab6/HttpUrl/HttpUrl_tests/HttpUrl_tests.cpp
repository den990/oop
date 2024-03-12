#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../HttpUrl/CHttpUrl.h"

const int MIN_PORT = 1;
const int MAX_PORT = 65535;

TEST_CASE("Testing Constructors with string")
{
	SECTION("Construct HttpUrl with string of correct url")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://vk.com"));
		}
	}
	SECTION("Construct HttpUrl with string of correct url (with complicated domain)")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("http://r93711zs.beget.tech/pay/pay.html"));
		}
	}
	SECTION("Construct HttpUrl with string of correct url (and with document)")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://faceit.com/stats"));
		}
	}
	SECTION("Construct HttpUrl with string of correct url (and with MIN available port)")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("http://localhost:" + std::to_string(MIN_PORT) + "/stats"));
		}
	}
	SECTION("0 port")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://localhost:" + std::to_string(MIN_PORT - 1) + "/stats"), CUrlParsingError);
		}
	}
	SECTION("Construct HttpUrl with string of correct url (and with MAX available port)")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://locahost:" + std::to_string(MAX_PORT) + "/kvantero"));
		}
	}
	SECTION("Construct HttpUrl with string of incorrect url (port is greater than MAX available port)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://localhost:" + (MAX_PORT + 1)), CUrlParsingError);
		}
	}
	SECTION("Construct HttpUrl with string of incorrect url (no protocol)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("//vk.com/im"), CUrlParsingError);
		}
	}
	SECTION("Construct HttpUrl with string of incorrect url (no domain)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://"), CUrlParsingError);
		}
	}
	SECTION("Construct HttpUrl with string of incorrect url (wrong protocol)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("abcde://vk.com/im"), CUrlParsingError);
		}
	}
	SECTION("Construct HttpUrl with string of incorrect url (wrong domain)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://v k.com"), CUrlParsingError);
		}
	}
	SECTION("Construct HttpUrl with string of incorrect url (wrong document)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://r93711zs.beget.tech/pay / pay.html"), CUrlParsingError);
		}
	}
	SECTION("Construct HttpUrl with string of incorrect url (port is not a number)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://localhost:string"), CUrlParsingError);
		}
	}
	SECTION("Construct HttpUrl with string of incorrect url (port is less than MIN available port)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("https://localhost:123abc"), CUrlParsingError);
		}
	}
}

TEST_CASE("Testing Constructors with protocol, domain, document")
{
	Protocol protocol;
	std::string domain;
	std::string document;
	SECTION("Construct HttpUrl with correct values and empty document")
	{
		protocol = Protocol::HTTP;
		domain = "vk.com";
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol));
		}
	}
	SECTION("Construct HttpUrl with correct values and valued document")
	{
		protocol = Protocol::HTTPS;
		domain = "r93711zs.beget.tech";
		document = "pay/pay.html";
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol));
		}
	}
	SECTION("Construct HttpUrl with incorrect domain")
	{
		protocol = Protocol::HTTP;
		domain = "face i t .com";
		THEN("HttpUrl is created")
		{
			REQUIRE_THROWS_AS(CHttpUrl(domain, document, protocol), CUrlParsingError);
		}
	}
	SECTION("Construct HttpUrl with incorrect document")
	{
		protocol = Protocol::HTTPS;
		domain = "faceit.com";
		document = "st ats /kvanter o---";
		THEN("HttpUrl is created")
		{
			REQUIRE_THROWS_AS(CHttpUrl(domain, document, protocol), CUrlParsingError);
		}
	}
}

TEST_CASE("Testing Constructors with protocol, domain, document and PORT")
{
	Protocol protocol;
	std::string domain;
	std::string document;
	Port port;
	SECTION("Construct HttpUrl with correct values and random port")
	{
		protocol = Protocol::HTTP;
		domain = "faceit.com";
		port = 52532;
			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol, MIN_PORT));
	}
	//добавить тест с плохим портом
}

TEST_CASE("Testing get-methods")
{
	Protocol protocol = Protocol::HTTPS;
	std::string domain = "faceit.com";
	Port port = 4554;
	std::string document = "/stats/ratings/form.php?";
	std::string correctStringUrl = CHttpUrl::ProtocolToString(protocol) + "://" + domain + ":" + std::to_string(port) + document; \

	CHttpUrl correctUrl(domain, document, protocol, port);
	SECTION("Testing GetProtocol")
	{
		REQUIRE(correctUrl.GetProtocol() == protocol);
	}
	SECTION("Testing GetDomain")
	{
		REQUIRE(correctUrl.GetDomain() == domain);
	}
	SECTION("Testing GetDocument")
	{
		REQUIRE(correctUrl.GetDocument() == document);
	}
	SECTION("Testing GetPort")
	{
		REQUIRE(correctUrl.GetPort() == port);
	}
	SECTION("Testing GetURL")
	{
		REQUIRE(correctUrl.GetURL() == correctStringUrl);
	}
}


//TEST_CASE("Print function")
//{
//	CHttpUrl url("http://r93711zs.beget.tech/pay/pay.html");
//	std::ostringstream out;
//	url.Print(out);
//	REQUIRE(out.str() == "Domain: r93711zs.beget.tech\nDocument: pay/pay.html\nProtocol: http\nPort: 80\n");
//}