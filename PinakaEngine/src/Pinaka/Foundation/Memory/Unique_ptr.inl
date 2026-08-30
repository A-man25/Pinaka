/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Unique_ptr.inl
 * Description : Memory <Smart Pointers> : unique ptr Implementation
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 30/08/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

namespace pke 
{
	template <typename T>
	Unique_ptr<T>::Unique_ptr(Unique_ptr&& mov)
	{
		this->raw = mov.raw;
		mov.raw = nullptr;
	}

	template <typename T>
	Unique_ptr<T>& Unique_ptr<T>::operator = (Unique_ptr && mov)
	{
		if (this == &mov)
			return *this;

		delete this->raw;

		this->raw = mov.raw;
		mov.raw = nullptr;

		return *this;
	}

	template <typename T>
	bool Unique_ptr<T>::operator == (const Unique_ptr& other) const
	{
		return this->raw == other.raw;
	}

	template <typename T>
	bool Unique_ptr<T>::operator != (const Unique_ptr& other) const
	{
		return this->raw != other.raw;
	}

	template <typename T>
	T* Unique_ptr<T>::operator->()
	{
		return raw;
	}

	template <typename T>
	const T* Unique_ptr<T>::operator->() const
	{
		return raw;
	}

	template <typename T>
	T& Unique_ptr<T>::operator* ()
	{
		if (!raw)
			throw std::runtime_error("Dereferencing a nullptr");
		
		return *(raw);
	}

	template <typename T>
	const T& Unique_ptr<T>::operator* () const
	{
		if (!raw)
			throw std::runtime_error("Dereferencing a nullptr");
		
		return *(raw);
	}

	template <typename T>
	T* Unique_ptr<T>::get()const
	{
		return raw;
	}

	template <typename T>
	T* Unique_ptr<T>::release()
	{
		T* rawptr = raw;
		raw = nullptr;
		return rawptr;
	}

	template <typename T>
	void Unique_ptr<T>::reset(T* ptr)
	{
		if (raw == ptr)
			return;

		delete raw;
		raw = ptr;
	}

	template <typename T>
	Unique_ptr<T>::~Unique_ptr()
	{
		delete raw;
		raw = nullptr;
	}
}