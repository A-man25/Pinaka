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

#include "SLinkedList.h"

namespace pke
{
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
		if (m_pHead)
		{
			Node<T>* cursor = m_pHead;

			while (cursor != nullptr)
			{
				Node<T>* nextCursor = cursor->m_pNext;
				delete cursor;
				cursor = nextCursor;
			}

			m_Size = 0;
			m_pHead = nullptr;
		}
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
}