/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Shared_ptr.h
 * Description : Memory <Smart Pointers> : Shared pointer Design
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 30/08/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#pragma once
#include <Pinaka/Core/PinakaEngineInc.h>

namespace pke
{
	template<typename T>
	class Shared_ptr
	{
	public:
		Shared_ptr() : raw(nullptr), ref_count(nullptr) {}
		Shared_ptr(T* ptr) : raw(ptr), ref_count(new int (1)) {}
		Shared_ptr(const Shared_ptr& other);
		Shared_ptr(Shared_ptr&& other);
		Shared_ptr& operator = (const Shared_ptr& other);
		Shared_ptr& operator = (Shared_ptr&& other);
		T& operator *();
		const T& operator *() const;
		T* operator->();
		const T* operator->() const;
		T* get() const;
		int use_count() const;
		void reset(T* ptr = nullptr);
		bool operator==(const Shared_ptr& other) const;
		bool operator!=(const Shared_ptr& other) const;
		~Shared_ptr();

	private:
		T* raw;
		int* ref_count;
	};

	template <typename T>
	Shared_ptr<T> make_shared(T value)
	{
		return Shared_ptr<T>(new T(value));
	}
}

#include "Shared_ptr.inl"