//=============================================================================
// Brief   : MIH Base Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis   <sreis@av.it.pt>
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

#ifndef ODTONE_MIH_TYPES_BASE__HPP_
#define ODTONE_MIH_TYPES_BASE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/exception.hpp>
#include <boost/variant/variant.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <string>
#include <vector>
#include <ostream>

#ifdef BOOST_MSVC
#	pragma warning(push)
#	pragma warning(disable : 4800)
#endif

///////////////////////////////////////////////////////////////////////////////
/**
 * Define a postfix increment operator for enumeration types.
 */
template<class EnumT>
inline EnumT operator++(EnumT& rs, int)
{
	ODTONE_STATIC_ASSERT(boost::is_enum<EnumT>::value, "EnumT must be an enumeration type");

	return rs = (EnumT)(rs + 1);
}

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * Define a OCTET data type.
 */
typedef uint8       octet;

/**
 * Define a OCTET_STRING data type.
 */
typedef std::string octet_string;

/**
 * Define NULL data type.
 */
struct null {
  template<class ArchiveT> void serialize(ArchiveT&) {}

  bool operator==(const null &) const { return true; }
};

inline std::ostream& operator<<(std::ostream& os, const null&)
{
	os << "(null)";

	return os;
}

///////////////////////////////////////////////////////////////////////////////
/**
 * Define BITMAP data type.
 */
template<size_t N, class EnumT>
class bitmap {
	ODTONE_STATIC_ASSERT(!(N % 8), "N must be a multiple of 8");
	//	ODTONE_STATIC_ASSERT(boost::is_enum<EnumT>::value, "EnumT must be an enumeration");

public:
	bitmap() { clear(); }

	void clear()
	{
		for (size_t i = 0; i < sizeof(_bitmap); ++i)
			_bitmap[i] = 0x00;
	}

	void clear(EnumT pos)     { _bitmap[uint(pos) / 8] &= ~(1 << (uint(pos) % 8)); }
	void set(EnumT pos)       { _bitmap[uint(pos) / 8] |= (1 << (uint(pos) % 8)); }
	bool get(EnumT pos) const { return _bitmap[uint(pos) / 8] & (1 << (uint(pos) % 8)); }

	void merge(bitmap b) {
		ODTONE_STATIC_ASSERT((sizeof(_bitmap) == sizeof(b._bitmap)),
		                    "Both bitmaps must have the same size");
		for (size_t i = 0; i < sizeof(_bitmap); ++i)
			_bitmap[i] |= b._bitmap[i];
	}

	void common(bitmap b) {
		ODTONE_STATIC_ASSERT((sizeof(_bitmap) == sizeof(b._bitmap)),
		                    "Both bitmaps must have the same size");
		for (size_t i = 0; i < sizeof(_bitmap); ++i)
			_bitmap[i] &= b._bitmap[i];
	}

	void full() {
		for (size_t i = 0; i < sizeof(_bitmap); ++i)
			_bitmap[i] = 0xFF;
	}

	bool operator==(const bitmap& bit) const {
		if(sizeof(_bitmap) == sizeof(bit._bitmap)) {
			for (size_t i = 0; i < sizeof(_bitmap); ++i) {
				if(_bitmap[i] != bit._bitmap[i]) {
					return false;
				}
			}
		}
		else {
			return false;
		}

		return true;
	}

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
          for (size_t i = ODTONE_COUNT_OF(_bitmap); i > 0 ; --i)
            ar & _bitmap[i-1];
	}

private:
	octet _bitmap[N / 8];
};


///////////////////////////////////////////////////////////////////////////////
struct percentage_exception : virtual public exception {
	percentage_exception() : exception("odtone::mih::percentage: out of range")
	{ }
};

/**
 * Define PERCENTAGE data type.
 */
class percentage {
public:
	percentage() : _val(0)
	{ }

	percentage& operator=(uint val)
	{
		if (val > 100)
			boost::throw_exception(percentage_exception());

		_val = val;
		return *this;
	}

	operator uint() { return _val; }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _val;
	}

private:
	octet _val;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Define ENUMERATED data type.
 */
template<class T>
class enumeration {
	ODTONE_STATIC_ASSERT(boost::is_enum<T>::value, "T must be an enumeration");

public:
	enumeration()
	{ }
	enumeration(T val) : _val(val)
	{ }

	enumeration& operator=(T val)
	{
		_val = val;
		return *this;
	}

	T get() const { return T(_val); }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _val;
	}

	bool operator==(T val) const { return (_val == val); }
	bool operator!=(T val) const { return (_val != val); }

	bool operator==(const enumeration& e) const { return (_val == e._val); }
	bool operator!=(const enumeration& e) const { return (_val != e._val); }

	friend std::ostream& operator<<(std::ostream& os, const enumeration& e)
	{
		std::ios::fmtflags prev;

		prev = os.setf(std::ios::hex, std::ios::basefield);
		os << uint(e._val);
		os.setf(prev);

		return os;
	}

private:
	uint8 _val;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of STATUS data type.
 */
enum status_enum {
	status_success = 0,
	status_failure = 1,
	status_rejected = 2,
	status_authorization_failure = 3,
	status_network_error = 4,
};

/**
 * Define a STATUS data type.
 */
typedef enumeration<status_enum> status;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

#ifdef BOOST_MSVC
#	pragma warning(pop)
#endif

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_BASE__HPP_ */
