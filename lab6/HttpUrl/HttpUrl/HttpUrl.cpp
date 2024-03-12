#include <iostream>
#include "CHttpUrl.h"
int main()
{
	/*while (!std::cin.eof())
	{
		std::string url;
		std::cin >> url;
		CHttpUrl a(url);
		a.Print(std::cout);
	}*/
	CHttpUrl url("example", "document", "");
	/*st << "Domain: " << GetDomain() << std::endl
			<< "Document: " << GetDocument() << std::endl
			<< "Protocol: " << ProtocolToString(GetProtocol()) << std::endl
			<< "Port: " << GetPort() << std::endl;
}*/