//=============================================================================
// Brief   : MIH Base Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis   <sreis@av.it.pt>
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
// Define a postfix increment operator for enumeration types
template<class EnumT>
inline EnumT operator++(EnumT& rs, int)
{
	ODTONE_STATIC_ASSERT(boost::is_enum<EnumT>::value, "EnumT must be an enumeration type");

	return rs = (EnumT)(rs + 1);
}

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
typedef uint8       octet;
typedef std::string octet_string;

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
template<size_t N, class EnumT>
class bitmap {
	ODTONE_STATIC_ASSERT(!(N % 8), "N must be a multiple of 8");
	//	ODTONE_STATIC_ASSERT(boost::is_enum<EnumT>::value, "EnumT must be an enumeration");

public:
	bitmap() { clear(); }

	void clear()
	{
		for (size_t i = 0; i < sizeof(_bitmap); ++i)
			_bitmap[i] = 0;
	}

	void clear(EnumT pos)     { _bitmap[uint(pos) / 8] &= ~(1 << (uint(pos) % 8)); }
	void set(EnumT pos)       { _bitmap[uint(pos) / 8] |= (1 << (uint(pos) % 8)); }
	bool get(EnumT pos) const { return _bitmap[uint(pos) / 8] & (1 << (uint(pos) % 8)); }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
          for (size_t i = 0; i < ODTONE_COUNT_OF(_bitmap); ++i)
            ar & _bitmap[i];
	}

private:
	octet _bitmap[N / 8];
};


///////////////////////////////////////////////////////////////////////////////
struct percentage_exception : virtual public exception {
	percentage_exception() : exception("odtone::mih::percentage: out of range")
	{ }
};

class percentage {
public:
	percentage() : _val(0)
	{ }

	percentage& operator=(uint val)
	{
		if (val > 100 || val < 0)
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
enum status_enum {
	status_success = 0,
	status_failure = 1,
	status_rejected = 2,
	status_authorization_failure = 3,
	status_network_error = 4,
};

typedef enumeration<status_enum> status;

///////////////////////////////////////////////////////////////////////////////
enum boolean_enum {
	boolean_false = 0,
	boolean_true = 1
};

typedef enumeration<boolean_enum> boolean;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

#ifdef BOOST_MSVC
#	pragma warning(pop)
#endif

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_BASE__HPP_ */
