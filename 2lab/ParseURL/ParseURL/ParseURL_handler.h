#include <iostream>
#include <string>
#include <regex>
#include <map>

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

const std::map<Protocol, int> defaultPorts =
{
    {Protocol::HTTP, 80},
    {Protocol::HTTPS, 443},
    {Protocol::FTP, 21}
};

bool PortDefinition(const std::string& protocolStr, Protocol& protocol, int& port, const std::string& portStr);
bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);