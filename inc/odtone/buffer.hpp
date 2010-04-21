//=============================================================================
// Brief   : Buffer
// Authors : Bruno Santos <bsantos@av.it.pt>
//
//
// Copyright (C) 2009 Universidade Aveiro - Instituto de Telecomunicacoes Polo Aveiro
//
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#ifndef ODTONE_BUFFER__HPP_
#define ODTONE_BUFFER__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <boost/utility.hpp>
#include <boost/move/move.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/type_traits/is_class.hpp>
#include <cstdlib>
#include <cstring>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
template<class T>
class buffer {
	ODTONE_STATIC_ASSERT(boost::is_pod<T>::value, "T must be POD type");

	BOOST_MOVABLE_BUT_NOT_COPYABLE(buffer);

public:
	buffer() : _ptr(nullptr), _len(0)
	{ }

	buffer(BOOST_RV_REF(buffer) buff) : _ptr(buff._ptr), _len(buff._len)
	{
		buff._ptr = nullptr;
		buff._len = 0;
	}

	buffer(size_t len) : _ptr(nullptr)
	{
		size(len);
	}

	~buffer()
	{
		std::free(_ptr);
	}

	buffer& operator=(BOOST_RV_REF(buffer) buff)
	{
		if (this != boost::addressof(buff)) {
			std::free(_ptr);

			_ptr = buff._ptr;
			_len = buff._len;
			buff._ptr = nullptr;
			buff._len = 0;
		}

		return *this;
	}

	void size(size_t len)
	{
		ODTONE_ASSERT((len * sizeof(T)) >= len);

		if (len != _len) {
			void* p = std::realloc(_ptr, len * sizeof(T));

			if (!p && len)
				throw std::bad_alloc();

			_ptr = reinterpret_cast<T*>(p);
			_len = len;
		}
	}

	void zero()
	{
		std::memset(_ptr, 0, _len * sizeof(T));
	}

	T*       get()        { return _ptr; }
	const T* get() const  { return _ptr; }
	size_t   size() const { return _len; }

private:
	T*     _ptr;
	size_t _len;
};

///////////////////////////////////////////////////////////////////////////////
template<class T>
class buffer_vla : buffer<uint8> {
	ODTONE_STATIC_ASSERT(!boost::is_enum<T>::value    //needed for buggy compilers
						 && boost::is_pod<T>::value
						 && boost::is_class<T>::value, "T must be a class/struct POD type");

	BOOST_MOVABLE_BUT_NOT_COPYABLE(buffer_vla);

	typedef buffer<uint8> base;

public:
	buffer_vla() : base()
	{ }

	buffer_vla(size_t len) : base(sizeof(T) + len)
	{
		ODTONE_ASSERT((sizeof(T) + len) > len);
	}

	buffer_vla(BOOST_RV_REF(buffer_vla) buff) : base(boost::move<base>(buff))
	{ }

	buffer_vla& operator=(BOOST_RV_REF(buffer_vla) buff)
	{
		static_cast<base&>(*this) = boost::move<base>(buff);

		return *this;
	}

	void size(size_t len)
	{
		ODTONE_ASSERT((sizeof(T) + len) > len);

		base::size(sizeof(T) + len);
	}

	using base::zero;
	using base::size;

	T& operator*()  { return *get(); }
	T* operator->() { return get(); }
	T* get()        { return reinterpret_cast<T*>(base::get()); }

	const T& operator*() const  { return *get(); }
	const T* operator->() const { return get(); }
	const T* get() const        { return reinterpret_cast<const T*>(base::get()); }
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_BUFFER__HPP_ */
