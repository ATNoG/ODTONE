//=============================================================================
// Brief   : Base Types and Definitions
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

#ifndef ODTONE_BASE__HPP_
#define ODTONE_BASE__HPP_

///////////////////////////////////////////////////////////////////////////////
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

#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6))
#	define BOOST_HAS_NULLPTR
#endif

#define ODTONE_UNDEFINED_BOOL                           \
	struct undefined_bool_t {                          \
		void true_() {}                                \
	};                                                 \
	typedef void (undefined_bool_t::*undefined_bool)()

#define ODTONE_UNDEFINED_BOOL_TRUE  &undefined_bool_t::true_
#define ODTONE_UNDEFINED_BOOL_FALSE 0

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
typedef signed char        schar;	/**< Signed char.		*/
typedef signed short       sshort;	/**< Signed short.		*/
typedef signed int         sint;	/**< Signed integer.	*/
typedef signed long        slong;	/**< Signed long.		*/
typedef signed long long   sllong;	/**< Signed long long.	*/

typedef unsigned char      uchar;	/**< Unsigned char.			*/
typedef unsigned short     ushort;	/**< Unsigned short.		*/
typedef unsigned int       uint;	/**< Unsigned integer.		*/
typedef unsigned long      ulong;	/**< Unsigned long.			*/
typedef unsigned long long ullong;	/**< Unsigned long long.	*/

typedef boost::uint8_t     uint8;	/**< 8-bit unsigned interger.	*/
typedef boost::uint16_t    uint16;	/**< 16-bit unsigned interger	*/
typedef boost::uint32_t    uint32;	/**< 32-bit unsigned interger	*/
typedef boost::uint64_t    uint64;	/**< 64-bit unsigned interger	*/

typedef boost::int8_t      sint8;	/**< 8-bit signed interger.		*/
typedef boost::int16_t     sint16;	/**< 16-bit signed interger.	*/
typedef boost::int32_t     sint32;	/**< 32-bit signed interger.	*/
typedef boost::int64_t     sint64;	/**< 64-bit signed interger.	*/

typedef boost::intmax_t    sintmax; /**< Max bit size signed interger.		*/
typedef boost::uintmax_t   uintmax; /**< Max bit size unsigned interger.	*/

///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_HAS_NULLPTR
	struct nullptr_t { template<class T> operator T*() const { return 0; } };

	static const nullptr_t nullptr = {};
#else
	using std::nullptr_t;
#endif

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

///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_HAS_NULLPTR
	using odtone::nullptr;
#endif

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_BASE__HPP_ */
