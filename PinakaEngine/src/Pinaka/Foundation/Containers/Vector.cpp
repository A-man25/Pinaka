#include "Vector.h"

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
	Vector<T>::~Vector()
	{
		delete[] m_pVal;
		m_pVal = nullptr;
		m_Size = 0;
		m_Capacity = m_Size;
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
		if (this == iOther)
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
		if (this == iOther)
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


}