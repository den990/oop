#pragma once
#include "CMyListNode.hpp"
#include "CMyListIterator.hpp"

template <typename T>
class CMyList
{
public:
	using Iterator = CMyListIterator<T>;
	using ConstIterator = CMyListConstIterator<T>;

	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ReverseConstIterator = std::reverse_iterator<ConstIterator>;

	CMyList()
		: m_size(0)
		, m_head(new CMyListNode<T>())
		, m_tail(nullptr)
	{
		try
		{
			m_tail = new CMyListNode<T>();
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

	CMyList(const CMyList& other)
		: CMyList()
	{

		for (const T& element : other)
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

	~CMyList() noexcept
	{
		Clear();
		delete m_head->m_prev;
		delete m_tail;
	}

	CMyList& operator=(const CMyList& other)
	{
		if (std::addressof(other) != this)
		{
			Clear();

			CMyList tmpCopy(other);
			std::swap(m_head, tmpCopy.m_head);
			std::swap(m_tail, tmpCopy.m_tail);
			std::swap(m_size, tmpCopy.m_size);
		}

		return *this;
	}

	void Insert(Iterator const& position, const T data)
	{
		CMyListNode<T>* newNodePtr = new CMyListNode<T>(data);
		CMyListNode<T>* positionPtr = position.m_nodePtr;

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

	void Erase(Iterator const& position)
	{
		if (IsEmpty())
		{
			throw std::out_of_range("List is out of range");
		}

		CMyListNode<T>* positionPtr = position.m_nodePtr;

		if (positionPtr->m_next == nullptr || positionPtr->m_prev == nullptr)
		{
			throw std::out_of_range("Erasing past-the-end-iterator");
		}

		CMyListNode<T>* followingPtr;
		positionPtr->m_prev->m_next = followingPtr = positionPtr->m_next;
		positionPtr->m_next->m_prev = positionPtr->m_prev;

		if (positionPtr == m_head)
		{
			m_head = m_head->m_next;
		}

		delete positionPtr;
		m_size--;
	}

	void PushBack(const T& data)
	{
		Insert(end(), data);
	}
	void PushFront(const T& data)
	{
		Insert(begin(), data);
	}

	size_t GetSize() const noexcept
	{
		return m_size;
	}

	bool IsEmpty() const noexcept
	{
		return m_size == 0;
	}

	void Clear() noexcept
	{
		if (!IsEmpty())
		{
			m_head->m_prev->m_next = m_tail;
			m_tail->m_prev = m_head->m_prev;

			CMyListNode<T>* tempNode;
			while ((tempNode = m_head) != m_tail)
			{
				m_head = m_head->m_next;
				delete tempNode;
			}

			m_size = 0;
		}
	}

	Iterator begin() const
	{
		return Iterator(m_head);
	}
	Iterator end() const
	{
		return Iterator(m_tail);
	}
	ReverseIterator rbegin() const
	{
		return std::make_reverse_iterator(end());
	}
	ReverseIterator rend() const
	{
		return std::make_reverse_iterator(begin());
	}

	ConstIterator cbegin() const
	{
		return ConstIterator(m_head);
	}
	ConstIterator cend() const
	{
		return ConstIterator(m_tail);
	}

	ReverseConstIterator crbegin() const
	{
		return std::make_reverse_iterator(cend());
	}
	ReverseConstIterator crend() const
	{
		return std::make_reverse_iterator(cbegin());
	}


private:
	CMyListNode<T>* m_head;
	CMyListNode<T>* m_tail;
	size_t m_size;
};