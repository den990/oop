#pragma once
#include <iostream>
#include <iosfwd>
#include <cassert>

class CMyString
{
public:
	// ����������� �� ���������
	CMyString();

	// �����������, ���������������� ������ ������� ������
	// � ����������� ������� ��������
	CMyString(const char* pString);

	// �����������, ���������������� ������ ������� ��
	// ����������� ������� �������� �����
	CMyString(const char* pString, size_t length);

	// ����������� �����������
	CMyString(CMyString const& other);

	// ������������ ����������� (��� ������������, ����������� � C++11)
	//  ����������� ��������� � ������������ ���������� ������������
	CMyString(CMyString&& other) noexcept;

	// �����������, ���������������� ������ ������� ��
	// ������ ����������� ���������� C++
	CMyString(std::string const& stlString);

	// ���������� ������ - ����������� ������, ���������� ��������� ������
	~CMyString();

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength() const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������
	const char* GetStringData() const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();

	CMyString& operator=(CMyString const& other);
	CMyString& operator=(CMyString&& other) noexcept;

	CMyString& operator+=(CMyString const& other);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);
	friend CMyString operator+(CMyString const& myString1, CMyString const& myString2);
	friend bool operator==(CMyString const& myString1, CMyString const& myString2);
	friend bool operator!=(CMyString const& myString1, CMyString const& myString2);

	friend bool operator>(CMyString const& myString1, CMyString const& myString2);
	friend bool operator>=(CMyString const& myString1, CMyString const& myString2);

	friend bool operator<(CMyString const& myString1, CMyString const& myString2);
	friend bool operator<=(CMyString const& myString1, CMyString const& myString2);

	friend std::istream& operator>>(std::istream& stream, CMyString& myString);
	friend std::ostream& operator<<(std::ostream& stream, CMyString const& myString);

private:
	char* m_string;
	size_t m_length;
};
