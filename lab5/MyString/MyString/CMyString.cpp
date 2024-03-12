#include "CMyString.h"

constexpr char STRING_END_SYMBOL = '\0';

CMyString::CMyString()
	: m_length(0)
	, m_string(new char[1])
{
	m_string[0] = STRING_END_SYMBOL;
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (pString == nullptr)
	{
		m_string = new char[1];
		m_string[0] = STRING_END_SYMBOL;
		m_length = 0;
	}
	else
	{
		m_string = new char[length + 1];
		m_length = length;
		memcpy(m_string, pString, length);
		m_string[m_length] = STRING_END_SYMBOL;
	}
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, (pString != nullptr) ? strlen(pString) : 0)
{
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.GetStringData(), other.GetLength())
{
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	static const char zeroLengthString[] = "";
	return m_string ? m_string : zeroLengthString;
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_string(other.m_string)
	, m_length(other.m_length)
{
	other.m_string = nullptr; //чистить ли?
	other.m_length = 0;
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::~CMyString()
{
	delete[] m_string;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if ((start > m_length) || (length > m_length - start))
	{
		throw std::out_of_range("Start is very big");
	}
	//обработать если пустая строка
	if (m_length == 0)
	{
		return CMyString();
	}
	return CMyString(&m_string[start], length);
}

void CMyString::Clear() 
{
	m_length = 0;
	delete[] m_string;
	m_string = nullptr;
	m_string = new char[m_length + 1];
	m_string[0] = STRING_END_SYMBOL; 
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (std::addressof(other) != this)
	{
		CMyString tmpCopy(other);
		std::swap(m_string, tmpCopy.m_string);
		std::swap(m_length, tmpCopy.m_length);
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (std::addressof(other) != this)
	{
		delete[] m_string;
		m_length = 0;
		m_string = nullptr;
		std::swap(m_string, other.m_string);
		std::swap(m_length, other.m_length);
	}
	return *this;
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	*this = *this + other;
	return *this;
}

const char& CMyString::operator[](size_t index) const
{
	assert(index < m_length);
	return m_string[index];
}

// оператор индексированного доступа для записи
char& CMyString::operator[](size_t index)
{
	assert(index < m_length);
	return m_string[index];
}

CMyString operator+(CMyString const& myString1, CMyString const& myString2)
{
	size_t newLength = myString1.GetLength() + myString2.GetLength();
	char* newString = new char[newLength + 1];
	memcpy(newString, myString1.GetStringData(), myString1.GetLength());
	memcpy(newString + myString1.GetLength(), myString2.GetStringData(), myString2.GetLength());
	newString[newLength] = STRING_END_SYMBOL;
	CMyString temp;
	try
	{

		temp = CMyString(newString, newLength);
		delete[] newString;
	}
	catch (std::bad_alloc& e)
	{
		delete[] newString;
		throw;
	}
	return temp;
}

bool operator==(CMyString const& myString1, CMyString const& myString2)
{
	if (myString1.GetLength() != myString2.GetLength())
	{
		return false;
	}
	return (memcmp(myString1.GetStringData(), myString2.GetStringData(), myString1.GetLength()) == 0);
}

bool operator!=(CMyString const& myString1, CMyString const& myString2)
{
	return !(myString1 == myString2);
}

bool operator>(CMyString const& myString1, CMyString const& myString2)
{
	size_t minLength = std::min(myString1.GetLength(), myString2.GetLength());
	return (memcmp(myString1.GetStringData(), myString2.GetStringData(), minLength) > 0);
}

bool operator>=(CMyString const& myString1, CMyString const& myString2)
{
	return !(myString1 < myString2);
}

bool operator<(CMyString const& myString1, CMyString const& myString2)
{
	size_t minLength = std::min(myString1.GetLength(), myString2.GetLength());
	return (memcmp(myString1.GetStringData(), myString2.GetStringData(), minLength) < 0);
}

bool operator<=(CMyString const& myString1, CMyString const& myString2)
{
	return !(myString1 > myString2);
}

std::ostream& operator<<(std::ostream& stream, CMyString const& myString)
{
	stream << myString.GetStringData();
	return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& myString)
{
	size_t inputStringLength = 0;
	size_t inputStringSize = 1;
	char inputChar;

	char* resultString = new char[1];
	while (stream.get(inputChar) && (inputChar != '\n') && (inputChar != ' '))
	{
		resultString[inputStringLength] = inputChar;
		inputStringLength++;
		if (inputStringLength == inputStringSize)
		{
			try
			{
				char* newString = new char[inputStringSize * 2];
				memcpy(newString, resultString, inputStringSize);
				delete[] resultString;
				resultString = newString;
				inputStringSize *= 2;
			}
			catch (std::bad_alloc& e)
			{
				delete[] resultString;
				throw;
			}
		}
	}

	resultString[inputStringLength] = STRING_END_SYMBOL;
	delete[] myString.m_string; //чистим от мусора
	myString.m_length = inputStringLength;
	myString.m_string = resultString;
	return stream;
}