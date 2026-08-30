/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Unique_ptr.h
 * Description : Memory <Smart Pointers> : unique ptr
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 30/08/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#pragma once
#include<Pinaka/Core/PinakaEngineInc.h>

namespace pke
{
	template <typename T>
	class Unique_ptr
	{
	private:
		T* raw;
	public:
		Unique_ptr() :raw(nullptr) {}
		Unique_ptr(T* ptr) : raw(ptr) {}
		Unique_ptr(Unique_ptr&& mov);
		Unique_ptr(const Unique_ptr& obj) = delete;
		Unique_ptr& operator = (const Unique_ptr& mov) = delete;
		Unique_ptr& operator = (Unique_ptr&& mov);
		bool operator == (const Unique_ptr& other) const;
		bool operator != (const Unique_ptr& other) const;
		T* operator ->();
		const T* operator ->() const;
		T& operator * ();
		const T& operator *() const;
		T* get() const;
		T* release();
		void reset(T* ptr = nullptr);
		~Unique_ptr();
	};

	template<typename T>
	Unique_ptr<T> make_unique(T value)
	{
		return Unique_ptr(new T(value));
	}
}

#include "Unique_ptr.inl"