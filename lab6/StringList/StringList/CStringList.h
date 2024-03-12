#pragma once

#include <algorithm>

#include "CStringListIterator.h"
#include "CStringListNode.h"

class CStringList
{
public:
	using Iterator = CStringListIterator;
	using ConstIterator = CStringListConstIterator;

	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ReverseConstIterator = std::reverse_iterator<ConstIterator>;

	CStringList();
	CStringList(const CStringList& other);
	CStringList(CStringList&& other);

	~CStringList() noexcept;

	CStringList& operator=(const CStringList& other);
	CStringList& operator=(CStringList&& other);

	void PushBack(const std::string& data);
	void PushFront(const std::string& data);

	void Insert(Iterator const& position, const std::string& data);
	void Erase(Iterator const& position);

	size_t GetSize() const noexcept;
	bool IsEmpty() const noexcept;

	void Clear() noexcept;

	Iterator begin() const;
	Iterator end() const;
	ReverseIterator rbegin() const;
	ReverseIterator rend() const;

	ConstIterator cbegin() const;
	ConstIterator cend() const;
	ReverseConstIterator crbegin() const;
	ReverseConstIterator crend() const;

private:
	CStringListNode* m_head;
	CStringListNode* m_tail;

	size_t m_size;
};