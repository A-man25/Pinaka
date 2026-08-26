/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Vector.cpp
 * Description : Data Structure : Vector
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 26/08/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

namespace pke
{
	template <typename T>
	Vector<T>::Vector(std::initializer_list<T> iList)
	{
		m_Size = iList.size();
		m_Capacity = m_Size;
		m_pVal = new T[m_Size];
		int i = 0;
		for (const auto& itr : iList)
		{
			m_pVal[i] = itr;
			i++;
		}
	}

	template <typename T>
	Vector<T>::Vector(const Vector& iOther)
	{
		m_Size = iOther.m_Size;
		m_Capacity = iOther.m_Capacity;
		m_pVal = new T[m_Capacity];
		for (int i = 0; i < m_Size; i++)
			m_pVal[i] = iOther.m_pVal[i];
	}

	template <typename T>
	Vector<T>::Vector(Vector&& iOther)
	{
		m_Size = iOther.m_Size;
		m_Capacity = iOther.m_Capacity;
		m_pVal = iOther.m_pVal;
		iOther.m_pVal = nullptr;
		iOther.m_Capacity = 0;
		iOther.m_Size = 0;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator = (const Vector& iOther)
	{
		if (this == &iOther)
			return *this;

		m_Size = iOther.m_Size;
		m_Capacity = iOther.m_Capacity;
		delete[] m_pVal;
		m_pVal = new T[m_Capacity];
		for (int i = 0; i < m_Size; i++)
			m_pVal[i] = iOther.m_pVal[i];

		return *this;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator = (Vector&& iOther)
	{
		if (this == &iOther)
			return *this;

		m_Size = iOther.m_Size;
		m_Capacity = iOther.m_Capacity;
		delete[] m_pVal ;
		m_pVal = iOther.m_pVal;
		iOther.m_pVal = nullptr;
		iOther.m_Capacity = 0;
		iOther.m_Size = 0;

		return *this;
	}

	template <typename T>
	T& Vector<T>::operator [] (int index)
	{
		if (index < 0 || index >= m_Size)
			throw std::out_of_range("Accessing out of bound index");

		return m_pVal[index];
	}

	template <typename T>
	const T& Vector<T>::operator [] (int index) const
	{
		if (index < 0 || index >= m_Size)
			throw std::out_of_range("Accessing out of bound index");

		return m_pVal[index];
	}

	template <typename T>
	Vector<T> Vector<T>::operator + (const Vector<T>& iRhs) const
	{
		Vector<T>newVec;
		newVec.m_Size = m_Size + iRhs.m_Size;
		newVec.m_Capacity = newVec.m_Size;
		newVec.m_pVal = new T[newVec.m_Size];

		for (int i = 0; i < m_Size; i++)
			newVec.m_pVal[i] = m_pVal[i];

		for (int i = 0; i < iRhs.m_Size;i++)
			newVec.m_pVal[m_Size + i] = iRhs.m_pVal[i];
		
		return newVec;
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		delete[] m_pVal;
		m_pVal = nullptr;
		m_Size = 0;
		m_Capacity = m_Size;
	}

	template <typename T>
	bool Vector<T>::operator == (const Vector& iRhs) const
	{
		if (m_Size != iRhs.m_Size)
			return false;

		for (int i = 0; i < m_Size;i++)
		{
			if(!(m_pVal[i] == iRhs.m_pVal[i]))
				return false;
		}

		return true;
	}

	template <typename T>
	void Vector<T>::pushBack(const T& iVal)
	{
		if (m_Size == m_Capacity)
		{
			int newCapacity = (m_Capacity == 0) ? 1 : m_Capacity * 2;

			T* newArray = new T[newCapacity];

			for (int i = 0; i < m_Size; i++)
				newArray[i] = m_pVal[i];

			delete[] m_pVal;

			m_pVal = newArray;
			m_Capacity = newCapacity;
		}

		m_pVal[m_Size] = iVal;
		m_Size++;
	}

	template <typename T>
	T Vector<T>::popBack()
	{
		if (m_Size == 0)
			throw std::out_of_range("vector is empty");

		T poppedVal = m_pVal[m_Size - 1];
		m_Size--;

		return poppedVal;
	}

	template<typename T>
	void Vector<T>::frontInsert(const T& iValue)
	{
		if(m_Size == m_Capacity)
			m_Capacity = (m_Capacity == 0 ) ? 1 : 2 * m_Size;
		
		T* newVec = new T[m_Capacity];
		newVec[0] = iValue;
		for (int i = 1; i <= m_Size; i++)
			newVec[i] = m_pVal[i-1];

		delete[]m_pVal;

		m_pVal = newVec;
		m_Size++;
	}

	template <typename T>
	void Vector<T>::insertAt(const T& iValue, int iIndex)
	{
		if (iIndex < 0 || iIndex > m_Size)
			throw std::out_of_range("index out of range");

		if (m_Size == m_Capacity)
			m_Capacity = (m_Capacity == 0) ? 1 : 2 * m_Size;

		T* newVec = new T[m_Capacity];
		newVec[iIndex] = iValue;
		for(int i = 0; i<iIndex; i++)
			newVec[i] = m_pVal[i];
		
		for(int i = iIndex; i<m_Size; i++)
			newVec[i + 1] = m_pVal[i];

		delete[] m_pVal;
		m_pVal = newVec;
		m_Size++;
	}

	template <typename T>
	T& Vector<T>::at(int iIndex)
	{
		if (iIndex < 0 || iIndex >= m_Size)
			throw std::out_of_range("index out of range");

		return m_pVal[iIndex];
	}

	template <typename T>
	const T& Vector<T>::at(int iIndex) const
	{
		if (iIndex < 0 || iIndex >= m_Size)
			throw std::out_of_range("index out of range");

		return m_pVal[iIndex];
	}

	template <typename T>
	int Vector<T>::size() const
	{
		return m_Size;
	}
	template <typename T>
	int Vector<T>::capacity() const
	{
		return m_Capacity;
	}

	template <typename T>
	bool Vector<T>::isEmpty() const
	{
		return m_Size == 0;
	}

	template <typename T>
	void Vector<T>::clear()
	{
		delete[]m_pVal;
		m_pVal = nullptr;
		m_Size = 0;
		m_Capacity = 0;
	}

	template <typename T>
	bool Vector<T>::linearSearch(const T& iVal, pke::Vector<int>& oIndexList) const
	{
		bool bFound = false;
		for (int i = 0; i < m_Size; i++)
		{
			if (m_pVal[i] == iVal)
			{
				 oIndexList.pushBack(i);
				 bFound = true;
			}
			
		}

		return bFound;
	}

	template<typename T>
	void Vector<T>::reverse()
	{
		if (m_Size <= 1)
			return;

		int start = 0;
		int end = m_Size - 1;

		while (start <= end)
		{
			std::swap(m_pVal[start], m_pVal[end]);
			start++;
			end--;
		}
	}

	template<typename T>
	void Vector<T>::rotateLeft()
	{
		if (m_Size <= 1)
			return;

		std::swap(m_pVal[m_Size - 1], m_pVal[0]);

		int first = 0;
		int second = first + 1;

		while (second < m_Size - 1)
		{
			std::swap(m_pVal[first], m_pVal[second]);
			first++;
			second++;
		}

	}

	template <typename T>
	void Vector<T>::rotateRight()
	{
		if (m_Size <= 1)
			return;

		std::swap(m_pVal[m_Size - 1], m_pVal[0]);

		int second = m_Size - 1;
		int first = second-1;

		while (first > 0)
		{
			std::swap(m_pVal[first], m_pVal[second]);
			first--;
			second--;
		}
	}

	template <typename T>
	void Vector<T>::deleteAt(int iIndex)
	{
		if (iIndex < 0 || iIndex >= m_Size)
			return;

		for (int i = iIndex; i < m_Size - 1;i++)
			m_pVal[i] = m_pVal[i + 1];

		m_Size--;
	}

	template <typename T>
	void Vector<T>::remove(const T& val)
	{
		if (m_Size <= 0)
			return;

		T* newVec = new T[m_Capacity];

		int nOccurance = 0;
		for (int i = 0; i < m_Size; i++)
		{
			if (m_pVal[i] == val)
			{
				nOccurance++;
				continue;
			}

			newVec[i - nOccurance] = m_pVal[i];
		}
		delete[] m_pVal;
		m_pVal = newVec;
		m_Size = m_Size - nOccurance;
		
	}
}