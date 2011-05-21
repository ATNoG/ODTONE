//=============================================================================
// Brief   : Buffer
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#ifndef ODTONE_BUFFER__HPP_
#define ODTONE_BUFFER__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <boost/utility.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/type_traits/is_class.hpp>
#include <cstdlib>
#include <cstring>
#include <utility>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
template<class T>
class buffer {
	ODTONE_STATIC_ASSERT(boost::is_pod<T>::value, "T must be POD type");

	buffer(const buffer&) = delete;
	buffer& operator=(const buffer&) = delete;

public:
	buffer()
		: _ptr(nullptr), _len(0)
	{ }

	buffer(buffer&& buff)
		: _ptr(nullptr), _len(0)
	{
		std::swap(_ptr, buff._ptr);
		std::swap(_len, buff._len);
	}

	buffer(size_t len)
		: _ptr(nullptr), _len(0)
	{
		size(len);
	}

	~buffer()
	{
		if (_ptr)
			std::free(_ptr);
	}

	buffer& operator=(buffer&& buff)
	{
		if (this != boost::addressof(buff)) {
			std::swap(_ptr, buff._ptr);
			std::swap(_len, buff._len);
		}

		return *this;
	}

	void size(size_t len)
	{
		ODTONE_ASSERT((len * sizeof(T)) >= len);

		if (len != _len) {
			void* p = std::realloc(_ptr, len * sizeof(T));

			if (!p && len)
				boost::throw_exception(std::bad_alloc());

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

	typedef buffer<uint8> base;

	buffer_vla(const buffer_vla&) = delete;
	buffer_vla& operator=(const buffer_vla&) = delete;

public:
	buffer_vla()
		: base()
	{ }

	buffer_vla(buffer_vla&& buff)
		: base(std::move(buff))
	{ }

	buffer_vla(size_t len)
		: base(sizeof(T) + len)
	{
		ODTONE_ASSERT((sizeof(T) + len) > len);
	}

	buffer_vla& operator=(buffer_vla&& buff)
	{
		if (this != boost::addressof(buff))
			*this = std::move<base>(buff);

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
