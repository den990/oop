#pragma once

#include <iostream>
#include <string>

struct CStringListNode
{
	CStringListNode()
		: m_data("")
		, m_next(nullptr)
		, m_prev(nullptr)
	{
	}

	CStringListNode(std::string data)
		: m_data(std::move(data))
		, m_next(nullptr)
		, m_prev(nullptr)
	{
	}

	~CStringListNode()
	{
	}

	CStringListNode* m_next;
	CStringListNode* m_prev;

	std::string m_data;
};