/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Shared_ptr.inl
 * Description : Memory <Smart Pointers> : Shared pointer Implementation
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
	Shared_ptr<T>::Shared_ptr(const Shared_ptr& other)
	{
		this->raw = other.raw;
		this->ref_count = other.ref_count;
	
		if (ref_count)
			(*ref_count)++;
	}

	template <typename T>
	Shared_ptr<T>::Shared_ptr(Shared_ptr&& other)
	{
		this->raw = other.raw;
		this->ref_count = other.ref_count;

		other.raw = nullptr;
		other.ref_count = nullptr;
	}

	template <typename T>
	Shared_ptr<T>& Shared_ptr<T>::operator=(const Shared_ptr& obj)
	{
		if (this == &obj)
			return *this;

		if (ref_count)
		{
			(*ref_count)--;

			if (*ref_count == 0)
			{
				delete raw;
				delete ref_count;
			}
		}

		this->raw = obj.raw;
		this->ref_count = obj.ref_count;

		if (ref_count)
			(*ref_count)++;

		return *this;
	}

	template <typename T>
	Shared_ptr<T>& Shared_ptr<T>::operator=(Shared_ptr&& other)
	{
		if (this == &other)
			return *this;

		if (this->ref_count)
		{
			(*ref_count)--;

			if (*ref_count == 0)
			{
				delete raw;
				delete ref_count;
			}
		}

		this->raw = other.raw;
		this->ref_count = other.ref_count;

		other.raw = nullptr;
		other.ref_count = nullptr;

		return *this;
	}

	template <typename T>
	T& Shared_ptr<T>::operator*()
	{
		if (!raw)
			throw std::runtime_error("De referencing a nullptr");

		return *raw;
	}

	template <typename T>
	const T& Shared_ptr<T>::operator*() const
	{
		if (!raw)
			throw std::runtime_error("De referencing a nullptr");

		return *raw;
	}

	template <typename T>
	T* Shared_ptr<T>::operator->()
	{
		return raw;
	}

	template <typename T>
	const T* Shared_ptr<T>::operator->() const
	{
		return raw;
	}

	template <typename T>
	T* Shared_ptr<T>::get()const
	{
		return raw;
	}

	template <typename T>
	int Shared_ptr<T>::use_count() const
	{
		if (!ref_count)
			return 0;

		return *ref_count;
	}

	template <typename T>
	void Shared_ptr<T>::reset(T* ptr)
	{
		if (ptr == raw)
			return;

		if (ref_count)
		{
			(*ref_count)--;
			if (*ref_count = 0)
			{
				delete raw;
				delete ref_count;
			}
		}

		raw = ptr;
		if (raw)
			ref_count = new int(1);
		else
			ref_count = nullptr;
	}


	template <typename T>
	bool Shared_ptr<T>::operator==(const Shared_ptr& other) const
	{
		return raw == other.raw;
	}

	template <typename T>
	bool Shared_ptr<T>::operator!=(const Shared_ptr& other) const
	{
		return raw != other.raw;
	}

	template <typename T>
	Shared_ptr<T>::~Shared_ptr()
	{
		if (ref_count)
		{
			(*ref_count)--;

			if (*ref_count == 0)
			{
				delete raw;
				delete ref_count;
			}
		}
	}
}	

