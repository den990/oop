#include "ParseURL_handler.h"

bool PortDefinition(std::string protocolStr, Protocol& protocol, const std::string& portStr, int& port)
{
	std::transform(protocolStr.begin(), protocolStr.end(), protocolStr.begin(), ::tolower);
    if (protocolStr == "http")
    {
        protocol = Protocol::HTTP;
    }
    else if (protocolStr == "https")
    {
        protocol = Protocol::HTTPS;
    }
    else if (protocolStr == "ftp")
    {
        protocol = Protocol::FTP;
    }
    else
    {
        return false;
    }
    if (portStr.empty())
    {
        port = defaultPorts.at(protocol);
    }
    else
    {
        port = stoi(portStr);
    }
	if (port < 1 || port > 65535)
		return false;
    return true;
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
    // R"()" R"()"
    std::regex urlRegex(
		"(https|http|ftp)"
		"://"
		"([^/:]+)"
        R"((?:\:(\d+))?)" // что такое(?
		"/(.*)$"); /*https - \w+, целое слово до ://
                                                                    ^ - все кроме /:
                                                                    ?::(\d+) - число которое не начинается с :?
                                                                    R"(^(\w+)://([^/:]+)(?:\:(\d+))?/(.*)$)"*/
    std::smatch urlMatch;
    if (!std::regex_match(url, urlMatch, urlRegex))
    {
        return false;
    }
    std::string protocolStr = urlMatch[1];
    host = urlMatch[2];
    std::string portStr = urlMatch[3];
    document = urlMatch[4];
	if (!PortDefinition(protocolStr, protocol, portStr, port)) // переименовать функцию, 
    {
        return false;
    }

    return true;
}