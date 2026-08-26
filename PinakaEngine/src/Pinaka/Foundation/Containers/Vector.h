/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : vector.h
 * Description : Data Structure : Vector
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 26/08/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#pragma once
#include "Pinaka/Core/PinakaEngineInc.h"

namespace pke
{
	template<typename T>
	class Vector
	{
	public:
		Vector():m_Size(0), m_pVal(nullptr), m_Capacity(0) {}
		Vector(std::initializer_list<T> iList);
		Vector(const Vector& iOther);
		Vector(Vector&& iOther);
		Vector& operator = (const Vector& iOther);
		Vector& operator = (Vector&& iOther);
		T& operator [] (int iIndex);
		const T& operator [] (int iIndex) const;
		Vector operator + (const Vector& iRhs) const; /* merge 2 vectors (LHS is this)*/
		~Vector();
		bool operator == (const Vector& iRhs) const;
		void pushBack(const T& iValue);
		T popBack();
		void frontInsert(const T& iValue);
		void insertAt(const T& iValue, int index);
		T& at(int iIndex);
		const T& at(int iIndex) const;
		int size() const;
		int capacity() const;
		bool isEmpty() const;
		void clear();
		bool linearSearch(const T& iVal, pke::Vector<int>& oIndexList) const;
		void reverse();
		void rotateRight();
		void rotateLeft();
		void deleteAt(int index);
		void remove(const T& obj);
	private:
		int m_Size;
		T* m_pVal;
		int m_Capacity;
	};

}

#include "Vector.inl"