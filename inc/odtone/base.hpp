//=============================================================================
// Brief   : Base Types and Definitions
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

#ifndef ODTONE_BASE__HPP_
#define ODTONE_BASE__HPP_

///////////////////////////////////////////////////////////////////////////////
#define BOOST_ENABLE_ASSERT_HANDLER

#include <cstddef>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>

///////////////////////////////////////////////////////////////////////////////
#define ODTONE_SCOPED(def)     switch(def) case 0: default:
#define ODTONE_COUNT_OF(array) (sizeof(array) / sizeof(array[0]))

#ifdef BOOST_HAS_STATIC_ASSERT
#	define ODTONE_STATIC_ASSERT(exp, reason) static_assert(exp, reason)
#else
#	define ODTONE_STATIC_ASSERT(exp, reason) BOOST_STATIC_ASSERT(exp)
#endif

#if defined(__GNUC__)
#	define ODTONE_LIKELY(x) __builtin_expect(!!(x), 1)
#else
#	define ODTONE_LIKELY(x) (x)
#endif

#if defined(__GNUC__)
#	define ODTONE_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#	define ODTONE_UNLIKELY(x) (x)
#endif

#if defined(__GNUC__)
#	define ODTONE_RETURN_ADDRESS __builtin_return_address(0)
#elif defined(BOOST_MSVC)
	extern "C" void* _ReturnAddress();

#	define ODTONE_RETURN_ADDRESS _ReturnAddress()
#else
#	define ODTONE_RETURN_ADDRESS 0
#endif

#if defined(__GNUC__)
#	define ODTONE_THREAD_LOCAL __thread
#elif defined(BOOST_MSVC)
#	define ODTONE_THREAD_LOCAL __declspec(thread)
#else
#	error no thread local storage
#endif

#if defined(__GNUC__)
#	define ODTONE_NORETURN_BEGIN
#	define ODTONE_NORETURN_END   __attribute__((noreturn))
#elif defined(BOOST_MSVC)
#	define ODTONE_NORETURN_BEGIN __declspec(noreturn)
#	define ODTONE_NORETURN_END
#else
#	define ODTONE_NORETURN_BEGIN
#	define ODTONE_NORETURN_END
#endif

#if defined(__GNUC__)
#	define ODTONE_DEPRECATE __attribute__((deprecated))
#elif defined(BOOST_MSVC)
#	define ODTONE_DEPRECATE __declspec(deprecated)
#else
#	define ODTONE_DEPRECATE
#endif

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
typedef signed char        schar;
typedef signed short       sshort;
typedef signed int         sint;
typedef signed long        slong;
typedef signed long long   sllong;

typedef unsigned char      uchar;
typedef unsigned short     ushort;
typedef unsigned int       uint;
typedef unsigned long      ulong;
typedef unsigned long long ullong;

typedef boost::uint8_t     uint8;
typedef boost::uint16_t    uint16;
typedef boost::uint32_t    uint32;
typedef boost::uint64_t    uint64;

typedef boost::int8_t      sint8;
typedef boost::int16_t     sint16;
typedef boost::int32_t     sint32;
typedef boost::int64_t     sint64;

typedef boost::intmax_t    sintmax;
typedef boost::uintmax_t   uintmax;

///////////////////////////////////////////////////////////////////////////////
struct nullptr_t { template<class T> operator T*() const { return 0; } };

static const nullptr_t nullptr = nullptr_t();

///////////////////////////////////////////////////////////////////////////////
struct nullref_t { template<class T> operator T&() const { return *(T*) 0; } };

static const nullref_t nullref = nullref_t();

template<class T>
inline bool operator==(nullref_t, const T& r)
{
	return &r == nullptr;
}

template<class T>
inline bool operator==(const T& r, nullref_t)
{
	return &r == nullptr;
}

template<class T>
inline bool operator!=(nullref_t, const T& r)
{
	return &r != nullptr;
}

template<class T>
inline bool operator!=(const T& r, nullref_t)
{
	return &r != nullptr;
}

///////////////////////////////////////////////////////////////////////////////
template<class MemberT, class ParentT>
inline MemberT* member_of(ParentT* parent, MemberT ParentT::* Member)
{
	return &(parent->*Member);
}

template<class ParentT, class MemberT>
inline ParentT* parent_of(MemberT* member, MemberT ParentT::* Member)
{
	ParentT* parent = 0;

	if (!member)
		return nullptr;

	return reinterpret_cast<ParentT*>(reinterpret_cast<char*>(member) - reinterpret_cast<const char*>(&(parent->*Member)));
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_BASE__HPP_ */
