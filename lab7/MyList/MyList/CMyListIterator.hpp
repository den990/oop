#pragma once

#include "CMyListNode.hpp"
#include <iterator>
#include <stdexcept>

template <typename T>
class CMyListConstIterator;

template <typename T>
class CMyList;

template <typename T>
class CMyListIterator
{
public:
	friend class CMyList<T>;
	friend class CMyListConstIterator<T>;

	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	bool operator!=(CMyListIterator const& other) const
	{
		return m_nodePtr != other.m_nodePtr;
	}
	bool operator==(CMyListIterator const& other) const
	{
		return m_nodePtr == other.m_nodePtr;
	}

	reference operator*() const
	{
		return m_nodePtr->m_data;
	}
	pointer operator->() const
	{
		return &m_nodePtr->m_data;
	}

	CMyListIterator& operator++()
	{
		m_nodePtr = m_nodePtr->m_next;
		return *this;
	}
	CMyListIterator& operator--()
	{
		m_nodePtr = m_nodePtr->m_prev;
		return *this;
	}

	CMyListIterator operator++(int)
	{
		CMyListIterator tmp(*this);
		++(*this);
		return tmp;
	}

	CMyListIterator operator--(int)
	{
		CMyListIterator tmp(*this);
		--(*this);
		return tmp;
	}

	CMyListIterator(CMyListNode<T>* node)
		: m_nodePtr(node)
	{
	}

private:
	CMyListNode<T>* m_nodePtr;
};

template <typename T>
class CMyListConstIterator
{
public:
	friend class CMyList<T>;

	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = const T;
	using pointer = const T*;
	using reference = const T&;

	CMyListConstIterator(CMyListNode<T>* node)
		: m_nodePtr(node)
	{
	}

	CMyListConstIterator(const class CMyListIterator<T>& other)
		: CMyListConstIterator(other.m_nodePtr)
	{
	}

	bool operator!=(CMyListConstIterator const& other) const
	{
		return m_nodePtr != other.m_nodePtr;
	}
	bool operator==(CMyListConstIterator const& other) const
	{
		return m_nodePtr == other.m_nodePtr;
	}

	reference operator*() const
	{
		return m_nodePtr->m_data;
	}

	pointer operator->() const
	{
		return &m_nodePtr->m_data;
	}

	CMyListConstIterator& operator++()
	{
		m_nodePtr = m_nodePtr->m_next;
		return *this;
	}
	CMyListConstIterator& operator--()
	{
		m_nodePtr = m_nodePtr->m_prev;
		return *this;
	}

	CMyListConstIterator operator++(int)
	{
		CMyListConstIterator tmp(*this);
		++(*this);
		return tmp;
	}
	CMyListConstIterator operator--(int)
	{
		CMyListConstIterator tmp(*this);
		--(*this);
		return tmp;
	}

private:
	CMyListNode<T>* m_nodePtr;
};