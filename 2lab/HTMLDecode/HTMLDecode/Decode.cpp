#include <iostream>
#include <map>
#include <string>

// &a&b&lt; должно &a&b<
//разобраться
/* const */ std::map<std::string, std::string> replace{
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" }
};

//checkStr неудачное имя
//GetDecode переименовать
std::string GetDecode(std::string const& checkStr)
{
	if (replace.find(checkStr) != replace.end())
	{
		return replace[checkStr];
	}
	return checkStr;
}

std::string HtmlDecode(std::string const& html)
{
	std::string newStr;
	//название пременных index
	size_t indexStart = 0, indexEnd = 0;
	while ((indexStart = (html.find("&", indexStart))) != std::string::npos)
	{
		//
		std::string checkStr;
		newStr.append(html, indexEnd, indexStart - indexEnd);
		indexEnd = html.find(";", indexStart) + 1;
		if (indexEnd == 0)
		{
			return html;
		}
		//6 заменить
		if (((indexEnd - indexStart) > 6) || (html[indexStart + 1] == '&'))
		{
			indexEnd = indexStart;
			indexStart++;
			continue;
		}
		checkStr.append(html, indexStart, indexEnd - indexStart);
		newStr += GetDecode(checkStr);
		indexStart = indexEnd;
	}
	if (newStr.size() == 0)
	{
		return html;
	}
	if (indexEnd != html.size())
	{
		newStr.append(html, indexEnd);
	}
	return newStr;
}