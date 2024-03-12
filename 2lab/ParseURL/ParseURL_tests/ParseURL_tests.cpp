#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../ParseURL/ParseURL_handler.h"
//добавить с портами и https в каком регистре

TEST_CASE("SwitchProtocol function")
{
    SECTION("HTTP Port")
    {
        Protocol protocol;
        int port;
        std::string protocolStr = "http";
        std::string portStr = "";
        REQUIRE(PortDefinition(protocolStr, protocol, port, portStr) == true);
        REQUIRE(protocol == Protocol::HTTP);
        REQUIRE(port == 80);
    }
    SECTION("HTTPS Port")
    {
        Protocol protocol;
        int port;
        std::string protocolStr = "https";
        std::string portStr = "";
        REQUIRE(PortDefinition(protocolStr, protocol, port, portStr) == true);
        REQUIRE(protocol == Protocol::HTTPS);
        REQUIRE(port == 443);
    }
    SECTION("Have Port")
    {
        Protocol protocol;
        int port;
        std::string protocolStr = "ftp";
        std::string portStr = "";
        REQUIRE(PortDefinition(protocolStr, protocol, port, portStr) == true);
        REQUIRE(protocol == Protocol::FTP);
        REQUIRE(port == 21);
    }
    SECTION("FTP Port")
    {
        Protocol protocol;
        int port;
        std::string protocolStr = "http";
        std::string portStr = "3030";
        REQUIRE(PortDefinition(protocolStr, protocol, port, portStr) == true);
        REQUIRE(protocol == Protocol::HTTP);
        REQUIRE(port == 3030);
    }
}

TEST_CASE("ParseURL function")
{
    std::string url;
    Protocol protocol;
    int port;
    std::string host, document;
    SECTION("Empty URL")
    {
        url = "";
        REQUIRE(ParseURL(url, protocol, port, host, document) == false);
    }
    SECTION("No valid URL")
    {
        url = "vk.com";
        REQUIRE(ParseURL(url, protocol, port, host, document) == false);
    }
    SECTION("URL without port")
    {
        url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
        REQUIRE(ParseURL(url, protocol, port, host, document) == true);
        REQUIRE(protocol == Protocol::HTTP);
        REQUIRE(port == 80);
        REQUIRE(host == "www.mysite.com");
        REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
    }
    SECTION("URL with port")
    {
        url = "https://www.example.com:3030/index.html";
        REQUIRE(ParseURL(url, protocol, port, host, document) == true);
        REQUIRE(protocol == Protocol::HTTPS);
        REQUIRE(port == 3030);
        REQUIRE(host == "www.example.com");
        REQUIRE(document == "index.html");
    }
    SECTION("URL without document")
    {
        url = "http://www.mysite.com";
        REQUIRE(ParseURL(url, protocol, port, host, document) == false);
    }
}