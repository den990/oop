#include "CStringList.h"

CStringList::CStringList()
	: m_size(0)
	, m_head(new CStringListNode())
	, m_tail(nullptr)
{
	try
	{
		m_tail = new CStringListNode();
	}
	catch (const std::bad_alloc&)
	{
		delete m_head;
		throw;
	}

	m_head->m_next = m_tail;
	m_tail->m_prev = m_head;
	m_head = m_tail;
}

CStringList::CStringList(const CStringList& other)
	: CStringList()
{

	for (const std::string& element : other)
	{
		try
		{
			PushBack(element);
		}
		catch (const std::exception&)
		{
			Clear();
			throw;
		}
	}
}

CStringList::CStringList(CStringList&& other)
	: m_head(other.m_head)
	, m_tail(other.m_tail)
	, m_size(other.GetSize())
{

	other.m_head = nullptr;
	other.m_tail = nullptr;
	other.m_size = 0;

	try // почему влияет? на метод clear
	{
		other.m_head = new CStringListNode();
		other.m_tail = new CStringListNode();
	}
	catch (const std::bad_alloc&)
	{
		delete other.m_head;
		throw;
	}

	other.m_head->m_next = other.m_tail;
	other.m_tail->m_prev = other.m_head;
	other.m_head = other.m_tail;
}

CStringList::~CStringList() noexcept
{
	Clear();
	delete m_head->m_prev;
	delete m_tail;
}

CStringList& CStringList::operator=(const CStringList& other)
{
	if (std::addressof(other) != this)
	{

		CStringList tmpCopy(other);
		std::swap(m_head, tmpCopy.m_head);
		std::swap(m_tail, tmpCopy.m_tail);
		std::swap(m_size, tmpCopy.m_size);
	}

	return *this;
}

CStringList& CStringList::operator=(CStringList&& other)
{
	if (std::addressof(other) != this)
	{

		std::swap(m_head, other.m_head);
		std::swap(m_tail, other.m_tail);
		std::swap(m_size, other.m_size);
	}

	return *this;
}

size_t CStringList::GetSize() const noexcept
{
	return m_size;
}

bool CStringList::IsEmpty() const noexcept
{
	return m_size == 0;
}

void CStringList::Clear() noexcept
{
	if (!IsEmpty())
	{
		m_head->m_prev->m_next = m_tail;
		m_tail->m_prev = m_head->m_prev;

		CStringListNode* tempNode;
		while ((tempNode = m_head) != m_tail)
		{
			m_head = m_head->m_next;
			delete tempNode;
		}

		m_size = 0;
	}
}

void CStringList::PushBack(const std::string& data)
{
	Insert(end(), data);
}

void CStringList::PushFront(const std::string& data)
{
	Insert(begin(), data);
}

void CStringList::Insert(Iterator const& position, const std::string& data)
{
	CStringListNode* newNodePtr = new CStringListNode(data);
	CStringListNode* positionPtr = position.m_nodePtr;

	newNodePtr->m_next = positionPtr;
	newNodePtr->m_prev = positionPtr->m_prev;

	positionPtr->m_prev->m_next = newNodePtr;
	positionPtr->m_prev = newNodePtr;

	if (positionPtr == m_head)
	{
		m_head = newNodePtr;
	}

	m_size++;
}

void CStringList::Erase(Iterator const& position)
{
	if (IsEmpty())
	{
		throw std::out_of_range("String is empty");
	}

	CStringListNode* positionPtr = position.m_nodePtr;

	if (positionPtr->m_next == nullptr && positionPtr->m_prev == nullptr)
	{
		throw std::out_of_range("Error, erasing past-the-end-iterator");
	}

	CStringListNode* followingPtr;
	positionPtr->m_prev->m_next = followingPtr = positionPtr->m_next;
	positionPtr->m_next->m_prev = positionPtr->m_prev;

	if (positionPtr == m_head)
	{
		m_head = m_head->m_next;
	}

	delete positionPtr;
	m_size--;
}

CStringList::Iterator CStringList::begin() const
{
	return Iterator(m_head);
}

CStringList::Iterator CStringList::end() const
{
	return Iterator(m_tail);
}

CStringList::ReverseIterator CStringList::rbegin() const
{
	return std::make_reverse_iterator(end());
}

CStringList::ReverseIterator CStringList::rend() const
{
	return std::make_reverse_iterator(begin());
}

CStringList::ConstIterator CStringList::cbegin() const
{
	return ConstIterator(m_head);
}

CStringList::ConstIterator CStringList::cend() const
{
	return ConstIterator(m_tail);
}

CStringList::ReverseConstIterator CStringList::crbegin() const
{
	return std::make_reverse_iterator(cend());
}

CStringList::ReverseConstIterator CStringList::crend() const
{
	return std::make_reverse_iterator(cbegin());
}