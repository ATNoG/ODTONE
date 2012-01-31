//=============================================================================
// Brief   : Buffer
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2012 Universidade Aveiro
// Copyright (C) 2009-2012 Instituto de Telecomunicações - Pólo Aveiro
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
/**
 * A container for data of a specific data type with linear and finite
 * sequence of elements.
 */
template<class T>
class buffer {
	ODTONE_STATIC_ASSERT(boost::is_pod<T>::value, "T must be POD type");

	buffer(const buffer&)/* = delete*/;
	buffer& operator=(const buffer&)/* = delete*/;

public:
	/**
	 * Construct an empty buffer. The created buffer will be empty and
	 * with zero length.
	 */
	buffer()
		: _ptr(nullptr), _len(0)
	{ }

	/**
	 * Construct a buffer. The new created buffer will be a copy of another
	 * buffer.
	 *
	 * @param buff Buffer to copy.
	 */
	buffer(buffer&& buff)
		: _ptr(nullptr), _len(0)
	{
		std::swap(_ptr, buff._ptr);
		std::swap(_len, buff._len);
	}

	/**
	 * Construct an empty buffer. Although the created buffer is empty, it has
	 * the length defined at its creation.
	 *
	 * @param len Number of elements the buffer can store.
	 */
	buffer(size_t len)
		: _ptr(nullptr), _len(0)
	{
		size(len);
	}

	/**
	 * Destruct a buffer.
	 */
	~buffer()
	{
		if (_ptr)
			std::free(_ptr);
	}

	/**
	 * Copy the elements from another buffer. The elements contained in the
	 * buffer will be overwrited.
	 *
	 * @param buff The buffer from which to copy the elements.
	 * @return The reference to the buffer.
	 */
	buffer& operator=(buffer&& buff)
	{
		if (this != boost::addressof(buff)) {
			std::swap(_ptr, buff._ptr);
			std::swap(_len, buff._len);
		}

		return *this;
	}

	/**
	 * Set the number of elements the buffer can store.
	 *
	 * @param len The number of elements the buffer can store.
	 */
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

	/**
	 * Remove all stored elements from the buffer.
	 */
	void zero()
	{
		std::memset(_ptr, 0, _len * sizeof(T));
	}

	/**
	 * Get the pointer to the first element of the buffer.
	 *
	 * @return The pointer to the first element of the buffer.
	 */
	T* get()
	{
		return _ptr;
	}

	/**
	 * Get the pointer to the first element of the buffer.
	 *
	 * @return The pointer to the first element of the buffer.
	 */
	const T* get() const
	{
		return _ptr;
	}

	/**
	 * Get the number of elements the buffer can store.
	 *
	 * @return The number of elements the buffer can store.
	 */
	size_t size() const
	{
		return _len;
	}

private:
	T*     _ptr;	/**< Pointer to the first element.				*/
	size_t _len;	/**< Number of elements the buffer can store	*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * A container (buffer) for 8-bit unsigned int data type with linear and
 * finite sequence of elements.
 */
template<class T>
class buffer_vla : buffer<uint8> {
	ODTONE_STATIC_ASSERT(!boost::is_enum<T>::value    //needed for buggy compilers
						 && boost::is_pod<T>::value
						 && boost::is_class<T>::value, "T must be a class/struct POD type");

	typedef buffer<uint8> base;

	buffer_vla(const buffer_vla&)/* = delete*/;
	buffer_vla& operator=(const buffer_vla&)/* = delete*/;

public:
	/**
	 * Construct an empty buffer. The created buffer will be empty and
	 * with zero length.
	 */
	buffer_vla()
		: base()
	{ }

	/**
	 * Construct a buffer. The new created buffer will be a copy of another
	 * buffer.
	 *
	 * @param buff Buffer to copy.
	 */
	buffer_vla(buffer_vla&& buff)
		: base(std::move(buff))
	{ }

	/**
	 * Construct an empty buffer. Although the created buffer is empty, it has
	 * the length defined at its creation.
	 *
	 * @param len Number of elements the buffer can store.
	 */
	buffer_vla(size_t len)
		: base(sizeof(T) + len)
	{
		ODTONE_ASSERT((sizeof(T) + len) > len);
	}

	/**
	 * Copy the elements from another buffer. The elements contained in the
	 * buffer will be overwrited.
	 *
	 * @param buff The buffer from which to copy the elements.
	 * @return The reference to the buffer.
	 */
	buffer_vla& operator=(buffer_vla&& buff)
	{
		if (this != boost::addressof(buff))
			*this = std::move<base>(buff);

		return *this;
	}

	/**
	 * Set the number of elements the buffer can store.
	 *
	 * @param len The number of elements the buffer can store.
	 */
	void size(size_t len)
	{
		ODTONE_ASSERT((sizeof(T) + len) > len);

		base::size(sizeof(T) + len);
	}

	using base::zero;
	using base::size;

	/**
	 * Get the reference to the first element of the buffer.
	 *
	 * @return The reference to the first element of the buffer.
	 */
	T& operator*()  { return *get(); }

	/**
	 * Get the pointer to the first element of the buffer.
	 *
	 * @return The pointer to the first element of the buffer.
	 */
	T* operator->() { return get(); }

	/**
	 * Get the pointer to the first element of the buffer.
	 *
	 * @return The pointer to the first element of the buffer.
	 */
	T* get()        { return reinterpret_cast<T*>(base::get()); }

	/**
	 * Get the reference to the first element of the buffer.
	 *
	 * @return The reference to the first element of the buffer.
	 */
	const T& operator*() const  { return *get(); }

	/**
	 * Get the pointer to the first element of the buffer.
	 *
	 * @return The pointer to the first element of the buffer.
	 */
	const T* operator->() const { return get(); }

	/**
	 * Get the pointer to the first element of the buffer.
	 *
	 * @return The pointer to the first element of the buffer.
	 */
	const T* get() const        { return reinterpret_cast<const T*>(base::get()); }
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_BUFFER__HPP_ */
