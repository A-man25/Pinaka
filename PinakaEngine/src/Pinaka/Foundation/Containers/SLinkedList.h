/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : SlinkedList.h
 * Description : Data Structure : Singly Linked List
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 27/08/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 *------------------------------------------------------------------------*/

#pragma once
#include <Pinaka/Core/PinakaEngineInc.h>

namespace pke
{
	template <typename T>
	class Node
	{
	public:
		T m_val;
		Node* m_pNext;
	};

	template <typename T>
	class SLinkedList
	{
	public:
		SLinkedList() :m_pHead(nullptr), m_Size(0) {}
		SLinkedList(std::initializer_list<T> list);
		SLinkedList(const SLinkedList& iother);
		SLinkedList(SLinkedList&& iother);
		~SLinkedList();
		SLinkedList& operator = (const SLinkedList& iother) const;
		SLinkedList operator = (SLinkedList&& iOther);
		void pushback(const T& ivalue);
		void pushfront(const T& ivalue);
		void insertAt(const T& ivalue);
		T& pop();
		void removefirst();
		void removeAt(int iIndex);
		void reverse();
		void rotateRight();
		void rotateLeft();
		int size() const;
		bool isEmpty() const;
		T& at() const;
		bool search(const T& ivalue);
		void clear();

	private:
		Node<T>* m_pHead;
		int m_Size;
	};
}
