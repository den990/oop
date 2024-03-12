#include <iostream>
#include <string>
#include <map>
#include "Decode.h"

//должна собираться без warning
int main()
{
    std::string htmlLine, newStr;
    while (getline(std::cin, htmlLine))
    {
        newStr = HtmlDecode(htmlLine);
        std::cout << newStr << std::endl;
    }
}
