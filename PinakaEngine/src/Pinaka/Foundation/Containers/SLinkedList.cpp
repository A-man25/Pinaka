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
	SLinkedList<T>::SLinkedList(std::initializer_list<T>list)
	{
		if (list.size() > 0)
		{
			m_pHead = new Node<T>();
			Node<T>* thisNode = m_pHead;

			int index = 0;
			for (const auto& value : list)
			{
				thisNode->m_val = value;
				index++;
				if (index < list.size())
				{
					thisNode->m_pNext = new Node<T>();
					thisNode = thisNode->m_pNext;
				}
			}
		}		
	}

	template <typename T>
	SLinkedList<T>::SLinkedList(const SLinkedList& iother)
	{
		if (iother.m_pHead == nullptr)
			return;
			
		m_pHead = new Node<T>();
		m_pHead->m_val = iother.m_pHead->m_val;
		Node<T>* curr = m_pHead;
		Node<T>* otherCurr = iother.m_pHead;
		while (otherCurr != nullptr)
		{
			curr->m_val = otherCurr->m_val;
			curr->m_pNext = new Node<T>();
			curr = curr->m_pNext;
			otherCurr = otherCurr->m_pNext;
		}

		m_Size = iother.m_Size;

	}

	template <typename T>
	SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList& other) const
	{
		

	}

}