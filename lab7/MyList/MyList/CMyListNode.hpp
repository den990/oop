#pragma once
#include <algorithm>

template <typename T>
struct CMyListNode
{
	CMyListNode()
		: m_data(T())
		, m_next(nullptr)
		, m_prev(nullptr)
	{
	}

	CMyListNode(T data)
		: m_data(std::move(data))
		, m_next(nullptr)
		, m_prev(nullptr)
	{
	}

	~CMyListNode()
	{
	}

	CMyListNode<T>* m_next;
	CMyListNode<T>* m_prev;

	T m_data;
};
