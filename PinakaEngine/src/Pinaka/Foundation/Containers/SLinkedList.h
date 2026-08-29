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
/************************************************************************
* Class : Node 
*************************************************************************/
	template <typename T>
	class Node
	{
	public:
		T m_val;
		Node* m_pNext = nullptr;
		Node() = default;
		Node(T iVal) : m_val(iVal), m_pNext(nullptr) {}
	};

/************************************************************************
* Class : Iterator
*************************************************************************/
	template <typename T>
	class Iterator
	{
	private:
		Node<T>* itr;
	public:
		Iterator(Node<T>* initr) : itr(initr) {}
		T& operator*();
		const T& operator*() const;
		Iterator& operator ++ ();
		bool operator == (const Iterator& other)const;
		bool operator != (const Iterator& other)const;
	};

/************************************************************************
* Class : Singly Linked List
*************************************************************************/
	template <typename T>
	class SLinkedList
	{
	public:
		SLinkedList() :m_pHead(nullptr), m_Size(0) {}
		SLinkedList(std::initializer_list<T> list);
		SLinkedList(const SLinkedList& copy);
		SLinkedList(SLinkedList&& iother);
		~SLinkedList();
		SLinkedList& operator = (const SLinkedList& copy);
		SLinkedList& operator = (SLinkedList&& iOther);
		void pushback(const T& ivalue);
		void pushfront(const T& ivalue);
		void insertAt(const T& ivalue, int index);
		void clear();
		T popback();
		T popfront();
		T popAt(int iIndex);
		inline int size() const { return m_Size; }
		inline bool isEmpty() const { return m_Size == 0; }
		T& at(int iIndex);
		const T& at(int iIndex) const;
		bool search(const T& ivalue) const;
		void reverse();
		bool isCycle() const;
		T& front();
		T& back();
		const T& front() const;
		const T& back() const;

		Iterator<T> begin();
		Iterator<T> end();

	private:
		Node<T>* m_pHead = nullptr;
		int m_Size = 0;
	};
}

#include "SLinkedList.inl"