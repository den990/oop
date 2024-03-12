#include "ParseURL_handler.h"

int main()
{
    std::string input;
    while (std::getline(std::cin, input))
    {
        Protocol protocol;
        int port;
        std::string host, document;
        if (ParseURL(input, protocol, port, host, document))
        {
            std::cout << input << std::endl;
            std::cout << "HOST: " << host << std::endl;
            std::cout << "PORT: " << port << std::endl; // порт от 1 65535 (почему?), выяснить и доложить
            std::cout << "DOC: " << document << std::endl;
        }
        else
        {
            std::cout << "Incorrect URL" << std::endl;
        }
    }
}
