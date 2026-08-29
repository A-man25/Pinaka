/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : SLinkedList.cpp
 * Description : Data Structure : Singly Linked List implementation
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 27/08/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

namespace pke
{

/************************************************************************
* Singly Linked List Implementation
*************************************************************************/
	template <typename T>
	SLinkedList<T>::SLinkedList(std::initializer_list<T> list)
	{
		if (list.size() == 0)
			return;

		m_Size = list.size();

		m_pHead = new Node<T>();
		Node<T>* cursor = m_pHead;

		int index = 0;
		for (const auto& value : list)
		{
			cursor->m_val = value;
			if (index != list.size() - 1)
			{
				cursor->m_pNext = new Node<T>();
				cursor = cursor->m_pNext;
			}

			index++;
		}
	}

	template<typename T>
	SLinkedList<T>::SLinkedList(const SLinkedList& copy)
	{
		if (copy.m_Size <= 0)
			return;

		m_pHead = new Node<T>();
		Node<T>* cursor = m_pHead;

		Node<T>* copyCursor = copy.m_pHead;

		while (copyCursor != nullptr)
		{
			cursor->m_val = copyCursor->m_val;
			if (copyCursor->m_pNext != nullptr)
			{
				cursor->m_pNext = new Node<T>();
				cursor = cursor->m_pNext;
			}

			copyCursor = copyCursor->m_pNext;
		}

		m_Size = copy.m_Size;
	}

	template <typename T>
	SLinkedList<T>::SLinkedList(SLinkedList&& iother)
	{
		if (iother.m_Size <= 0)
			return;

		m_pHead = iother.m_pHead;
		m_Size = iother.m_Size;
		iother.m_pHead = nullptr;
		iother.m_Size = 0;
	}

	template <typename T>
	SLinkedList<T>::~SLinkedList()
	{
		this->clear();
	}

	template<typename T>
	void SLinkedList<T>::clear()
	{
		if (m_pHead)
		{
			Node<T>* pCur = m_pHead;
			while (pCur)
			{
				Node<T>* next = pCur->m_pNext;
				delete pCur;
				pCur = next;
			}

			m_pHead = nullptr;
			m_Size = 0;
		}
	}

	template <typename T>
	SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList& copy)
	{
		if (this == &copy )
			return *this;

		this->clear();

		if (!copy.m_pHead)
			return *this;

		m_pHead = new Node<T>();
		Node<T>* cursor = m_pHead;
		Node<T>* copyCursor = copy.m_pHead;

		while (copyCursor != nullptr)
		{
			cursor->m_val = copyCursor->m_val;

			if (copyCursor->m_pNext)
			{
				cursor->m_pNext = new Node<T>();
				cursor = cursor->m_pNext;
			}
			copyCursor = copyCursor->m_pNext;
		}

		m_Size = copy.m_Size;

		return *this;
	}

	template <typename T>
	SLinkedList<T>& SLinkedList<T>::operator=(SLinkedList&& iother)
	{
		if (this == &iother)
			return *this;

		this->clear();

		m_pHead = iother.m_pHead;
		m_Size = iother.m_Size;
		iother.m_pHead = nullptr;
		iother.m_Size = 0;

		return *this;
	}

	template <typename T>
	void SLinkedList<T>::pushback(const T& value)
	{
		if (!m_pHead)
		{
			m_pHead = new Node<T>(value);
			m_Size++;
			return;
		}
		
		Node<T>* cursor = m_pHead;
		while (cursor->m_pNext)
			cursor = cursor->m_pNext;

		cursor->m_pNext = new Node<T>(value);
		m_Size++;
	}

	template <typename T>
	void SLinkedList<T>::pushfront(const T& value)
	{
		if (!m_pHead)
		{
			m_pHead = new Node<T>(value);
			m_Size++;
			return;
		}

		Node<T>* cursor = new Node<T>(value);
		cursor->m_pNext = m_pHead;
		m_pHead = cursor;
		m_Size++;
	}

	template <typename T>
	void SLinkedList<T>::insertAt(const T& value, int index)
	{
		if (index < 0 ||index > m_Size)
			throw std::out_of_range("index out of range");

		if (index == 0)
		{
			this->pushfront(value);
			return;
		}
		
		Node<T>* cursor = m_pHead;

		int curIndx = 0;
		while (cursor->m_pNext && curIndx < index-1)
		{
			cursor = cursor->m_pNext;
			curIndx++;
		}

		Node<T>* newNode = new Node<T>(value);
		newNode->m_pNext = cursor->m_pNext;
		cursor->m_pNext = newNode;
		m_Size++;
	}

	template <typename T>
	T SLinkedList<T>::popback()
	{
		if (!m_pHead)
			throw std::runtime_error("head is null");

		if (!m_pHead->m_pNext) 
		{
			T value = m_pHead->m_val;
			delete m_pHead;
			m_pHead = nullptr;
			m_Size--;
			return value;
		}

		Node<T>* curs = m_pHead;
		while (curs->m_pNext->m_pNext)
			curs = curs->m_pNext;

		T value = curs->m_pNext->m_val;
		delete curs->m_pNext;
		curs->m_pNext = nullptr;
		m_Size--;
		return value;
	}

	template <typename T>
	T SLinkedList<T>::popfront()
	{
		if (!m_pHead)
			throw std::runtime_error("Empty List");

		if (!m_pHead->m_pNext)
		{
			T value = m_pHead->m_val;
			this->clear();
			return value;
		}

		Node<T>* cursor = m_pHead->m_pNext;
		T value = m_pHead->m_val;
		delete m_pHead;
		m_pHead = cursor;
		m_Size--;

		return value;
	}

	template <typename T>
	T SLinkedList<T>::popAt(int index)
	{
		if (index < 0 || index >= m_Size)
			throw std::out_of_range("Invalid Index");

		if (index == 0)
			return this->popfront();
		

		Node<T>* prevNode = m_pHead;
		Node<T>* nodeToDel = prevNode->m_pNext;

		int curIdx = 0;

		while (curIdx < index - 1)
		{
			prevNode = nodeToDel;
			nodeToDel = nodeToDel->m_pNext;
			curIdx++;
		}

		prevNode->m_pNext = nodeToDel->m_pNext;
		T val = nodeToDel->m_val;
		delete nodeToDel;
		m_Size--;

		return val;
	}

	template <typename T>
	T& SLinkedList<T>::at(int index)
	{
		if (!m_pHead)
			throw std::runtime_error("List is empty");

		if (index < 0 || index >= m_Size)
			throw std::out_of_range("index out of bounds");

		if (index == 0)
			return m_pHead->m_val;

		int curidx = 0;
		Node<T>* curNode = m_pHead;

		while (curidx < index)
		{
			curNode = curNode->m_pNext;
			curidx++;
		}

		return curNode->m_val;
	}

	template <typename T>
	const T& SLinkedList<T>::at(int index) const
	{
		if (!m_pHead)
			throw std::runtime_error("List is empty");

		if (index < 0 || index >= m_Size)
			throw std::out_of_range("index out of bounds");

		Node<T>* curNode = m_pHead;

		for (int i = 0; i < index; i++)
			curNode = curNode->m_pNext;

		return curNode->m_val;
	}

	template <typename T>
	bool SLinkedList<T>::search(const T& value) const
	{
		if (!m_pHead)
			return false;

		Node<T>* cur = m_pHead;
		while (cur)
		{
			if (cur->m_val == value)
				return true;

			cur = cur->m_pNext;
		}

		return false;
	}

	template <typename T>
	void SLinkedList<T>::reverse()
	{
		if (m_Size <= 1)
			return;

		Node<T>* prev = nullptr;
		Node<T>* curr = m_pHead;

		while (curr)
		{
			Node<T>* next = curr->m_pNext;
			curr->m_pNext = prev;
			prev = curr;
			curr = next;
		}

		m_pHead = prev;
	}

	template<typename T>
	bool SLinkedList<T>::isCycle() const
	{
		if (!m_pHead || !m_pHead->m_pNext)
			return false;

		Node<T>* slow = m_pHead;
		Node<T>* fast = m_pHead;

		while (fast && fast->m_pNext)
		{
			slow = slow->m_pNext;
			fast = fast->m_pNext->m_pNext;

			if (slow == fast)
				return true;
		}

		return false;
	}

	template <typename T>
	T& SLinkedList<T>::front()
	{
		if (!m_pHead)
			throw std::runtime_error("List is empty");

		return m_pHead->m_val;
	}

	template <typename T>
	T& SLinkedList<T>::back()
	{
		if (!m_pHead)
			throw std::runtime_error("List is empty");

		Node<T>* curr = m_pHead;
		while (curr->m_pNext)
			curr = curr->m_pNext;

		return curr->m_val;
	}

	template <typename T>
	const T& SLinkedList<T>::front() const
	{
		if (!m_pHead)
			throw std::runtime_error("List is empty");

		return m_pHead->m_val;
	}

	template <typename T>
	const T& SLinkedList<T>::back() const
	{
		if (!m_pHead)
			throw std::runtime_error("List is empty");

		Node<T>* curr = m_pHead;
		while (curr->m_pNext)
			curr = curr->m_pNext;

		return curr->m_val;
	}

	template <typename T>
	Iterator<T> SLinkedList<T>::begin()
	{
		return Iterator<T>(m_pHead);
	}

	template <typename T>
	Iterator<T> SLinkedList<T>::end()
	{
		return Iterator<T>(nullptr);
	}


/************************************************************************
* Iterator  Implementation
*************************************************************************/
	template <typename T>
	T& Iterator<T>::operator*()
	{
		return this->itr->m_val;
	}

	template <typename T>
	const T& Iterator<T>::operator*() const
	{
		return this->itr->m_val;
	}

	template <typename T>
	Iterator<T>& Iterator<T>::operator ++ ()
	{
		this->itr = this->itr->m_pNext;
		return *this;
	}

	template<typename T>
	bool Iterator<T>::operator == (const Iterator& other) const
	{
		return this->itr == other.itr;
	}

	template<typename T>
	bool Iterator<T>::operator != (const Iterator& other) const
	{
		return this->itr != other.itr;
	}

}