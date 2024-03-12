#pragma once

#include "CStringListNode.h"

class CStringListIterator
{
public:
	friend class CStringList;
	friend class CStringListConstIterator;

	using iterator_category = std::bidirectional_iterator_tag; // итератор может перемещаться как вперед, так и назад.
	using difference_type = std::ptrdiff_t; // разница указателей  // тип целого числа со знаком, который может использоваться для идентификации расстояния между итераторами
	using value_type = std::string;
	using pointer = std::string*;
	using reference = std::string&;

	bool operator!=(CStringListIterator const& other) const;
	bool operator==(CStringListIterator const& other) const;

	reference operator*() const;
	pointer operator->() const;

	CStringListIterator& operator++();
	CStringListIterator& operator--();

	CStringListIterator operator++(int);
	CStringListIterator operator--(int);

	CStringListIterator(CStringListNode* node);
private:
	CStringListNode* m_nodePtr;
};


class CStringListConstIterator
{
public:
	friend class CStringList;

	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = const std::string;
	using pointer = const std::string*;
	using reference = const std::string&;

	CStringListConstIterator(const class CStringListIterator& other);

	bool operator!=(CStringListConstIterator const& other) const;
	bool operator==(CStringListConstIterator const& other) const;

	reference operator*() const;
	pointer operator->() const;

	CStringListConstIterator& operator++();
	CStringListConstIterator& operator--();

	CStringListConstIterator operator++(int);
	CStringListConstIterator operator--(int);

protected:
	CStringListConstIterator(CStringListNode* node);

private:
	CStringListNode* m_nodePtr;
};
