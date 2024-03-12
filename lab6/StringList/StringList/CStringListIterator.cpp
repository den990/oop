#include "CStringListIterator.h"

CStringListIterator::CStringListIterator(CStringListNode* node)
	: m_nodePtr(node)
{
}

bool CStringListIterator::operator!=(CStringListIterator const& other) const
{
	return m_nodePtr != other.m_nodePtr;
}

bool CStringListIterator::operator==(CStringListIterator const& other) const
{
	return m_nodePtr == other.m_nodePtr;
}

CStringListIterator::reference CStringListIterator::operator*() const
{
	return m_nodePtr->m_data;
}

CStringListIterator::pointer CStringListIterator::operator->() const
{
	return &m_nodePtr->m_data;
}

CStringListIterator& CStringListIterator::operator++()
{
	m_nodePtr = m_nodePtr->m_next;
	return *this;
}

CStringListIterator& CStringListIterator::operator--()
{
	m_nodePtr = m_nodePtr->m_prev;
	return *this;
}

CStringListIterator CStringListIterator::operator++(int)
{
	CStringListIterator tmp(*this);
	++(*this);
	return tmp;
}

CStringListIterator CStringListIterator::operator--(int)
{
	CStringListIterator tmp(*this);
	--(*this);
	return tmp;
}
//const
CStringListConstIterator::CStringListConstIterator(CStringListNode* node)
	: m_nodePtr(node)
{
}

CStringListConstIterator::CStringListConstIterator(const CStringListIterator& other)
	: CStringListConstIterator(other.m_nodePtr)
{
	
}

bool CStringListConstIterator::operator!=(CStringListConstIterator const& other) const
{
	return m_nodePtr != other.m_nodePtr;
}

bool CStringListConstIterator::operator==(CStringListConstIterator const& other) const
{
	return m_nodePtr == other.m_nodePtr;
}

CStringListConstIterator::reference CStringListConstIterator::operator*() const
{
	return m_nodePtr->m_data;
}

CStringListConstIterator::pointer CStringListConstIterator::operator->() const
{
	return &m_nodePtr->m_data;
}

CStringListConstIterator& CStringListConstIterator::operator++()
{
	m_nodePtr = m_nodePtr->m_next;
	return *this;
}

CStringListConstIterator& CStringListConstIterator::operator--()
{
	m_nodePtr = m_nodePtr->m_prev;
	return *this;
}

CStringListConstIterator CStringListConstIterator::operator++(int)
{
	CStringListConstIterator tmp(*this);
	++(*this);
	return tmp;
}

CStringListConstIterator CStringListConstIterator::operator--(int)
{
	CStringListConstIterator tmp(*this);
	--(*this);
	return tmp;
}