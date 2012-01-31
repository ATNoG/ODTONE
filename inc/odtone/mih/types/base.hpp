//=============================================================================
// Brief   : MIH Base Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis   <sreis@av.it.pt>
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

typedef uint8		octet;			/**< OCTET data type.			*/
typedef std::string octet_string;	/**< OCTET_STRING data type.	*/

/**
 * Define NULL data type.
 */
struct null {
	/**
	 * Serialize/deserialize the NULL data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT> void serialize(ArchiveT& ar) {}

	bool operator==(const null &) const
	{
		return true;
	}
};

/**
 * NULL data type output.
 *
 * @param os ostream.
 * @param n NULL data type.
 * @return ostream reference.
 */
inline std::ostream& operator<<(std::ostream& os, const null& n)
{
	os << "(null)";

	return os;
}

///////////////////////////////////////////////////////////////////////////////
/**
 * BITMAP data type.
 * @note N must be a multiple of 8.
 */
template<size_t N, class EnumT>
class bitmap {
	ODTONE_STATIC_ASSERT(!(N % 8), "N must be a multiple of 8");
	//	ODTONE_STATIC_ASSERT(boost::is_enum<EnumT>::value, "EnumT must be an enumeration");

public:
	/**
	 * Contruct an empty BITMAP data type.
	 */
	bitmap()
	{
		clear();
	}

	/**
	 * Clear the BITMAP data type.
	 */
	void clear()
	{
		for (size_t i = 0; i < sizeof(_bitmap); ++i)
			_bitmap[i] = 0x00;
	}

	/**
	 * Clear the position.
	 *
	 * @param pos The position on the bitmap to clear.
	 */
	void clear(EnumT pos)
	{
		_bitmap[uint(pos) / 8] &= ~(1 << (uint(pos) % 8));
	}

	/**
	 * Set the position.
	 *
	 * @param pos The position on the bitmap to set.
	 */
	void set(EnumT pos)
	{
		_bitmap[uint(pos) / 8] |= (1 << (uint(pos) % 8));
	}

	/**
	 * Get the position value.
	 *
	 * @param pos The position on the bitmap to get.
	 */
	bool get(EnumT pos) const
	{
		return _bitmap[uint(pos) / 8] & (1 << (uint(pos) % 8));
	}

	/**
	 * Merge the value of the bitmap with another BITMAP data type.
	 * @note Both bitmaps must have the same size
	 *
	 * @param b The BITMAP data type to merge with.
	 */
	void merge(bitmap b)
	{
		ODTONE_STATIC_ASSERT((sizeof(_bitmap) == sizeof(b._bitmap)),
		                    "Both bitmaps must have the same size");
		for (size_t i = 0; i < sizeof(_bitmap); ++i)
			_bitmap[i] |= b._bitmap[i];
	}

	/**
	 * Set the common values between the BITMAP and another BITMAP data type.
	 * @note Both bitmaps must have the same size
	 *
	 * @param b The BITMAP data type to compare with.
	 */
	void common(bitmap b)
	{
		ODTONE_STATIC_ASSERT((sizeof(_bitmap) == sizeof(b._bitmap)),
		                    "Both bitmaps must have the same size");
		for (size_t i = 0; i < sizeof(_bitmap); ++i)
			_bitmap[i] &= b._bitmap[i];
	}

	/**
	 * Clear the values of the bitmap, if they are set on the given BITMAP.
	 * @note Both bitmaps must have the same size
	 *
	 * @param b The BITMAP data type with the values to clear.
	 */
	void except(bitmap b)
	{
		ODTONE_STATIC_ASSERT((sizeof(_bitmap) == sizeof(b._bitmap)),
		                    "Both bitmaps must have the same size");
		for (size_t i = 0; i < sizeof(_bitmap); ++i)
			_bitmap[i] &= ~b._bitmap[i];
	}

	/**
	 * Set all poisition of the BITMAP data type.
	 */
	void full()
	{
		for (size_t i = 0; i < sizeof(_bitmap); ++i)
			_bitmap[i] = 0xFF;
	}

	/**
	 * Check if the two bitmaps are equal.
	 * @note Both bitmaps must have the same size
	 *
	 * @param bit The BITMAP data type to compare with.
	 */
	bool operator==(const bitmap& bit) const
	{
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

	/**
	 * Serialize/deserialize the BITMAP data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
          for (size_t i = ODTONE_COUNT_OF(_bitmap); i > 0 ; --i)
            ar & _bitmap[i-1];
	}

private:
	octet _bitmap[N / 8];	/**< BITMAP data type value.	*/
};


///////////////////////////////////////////////////////////////////////////////
/**
 * Percentage exception.
 */
struct percentage_exception : virtual public exception {
	/**
	 * Construct a percentage exception.
	 */
	percentage_exception() : exception("odtone::mih::percentage: out of range")
	{ }
};

/**
 * PERCENTAGE data type.
 */
class percentage {
public:
	/**
	 * Construct a PERCENTAGE data type. It is initialize to 0%.
	 */
	percentage() : _val(0)
	{ }

	/**
	 * Set the PERCENTAGE data type value.
	 *
	 * @param val The percentage value.
	 * @return The reference to the PERCENTAGE data type.
	 */
	percentage& operator=(uint val)
	{
		if (val > 100)
			boost::throw_exception(percentage_exception());

		_val = val;
		return *this;
	}

	/**
	 * Get the PERCENTAGE data type value.
	 *
	 * @return The PERCENTAGE data type value.
	 */
	operator uint()
	{
		return _val;
	}

	/**
	 * Serialize/deserialize the PERCENTAGE data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _val;
	}

private:
	octet _val;	/**< PERCENTAGE data type value.	*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * ENUMERATED data type.
 */
template<class T>
class enumeration {
	ODTONE_STATIC_ASSERT(boost::is_enum<T>::value, "T must be an enumeration");

public:
	/**
	 * Construct an empty ENUMERATION data type.
	 */
	enumeration()
	{ }

	/**
	 * Construct an ENUMERATION data type.
	 *
	 * @param val The value of the ENUMERATION data type.
	 */
	enumeration(T val) : _val(val)
	{ }

	/**
	 * Set the ENUMERATION data type.
	 *
	 * @param val The value to assign to the ENUMERATION data type.
	 */
	enumeration& operator=(T val)
	{
		_val = val;
		return *this;
	}

	/**
	 * Get the ENUMERATION data type value.
	 *
	 * @return The value of the ENUMERATION data type.
	 */
	T get() const
	{
		return T(_val);
	}

	/**
	 * Serialize/deserialize the ENUMERATION data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _val;
	}

	/**
	 * Check if the ENUMERATION value is equal to the argument value.
	 *
	 * @param val The value to compare with.
	 * @return True if they are equal or false otherwise.
	 */
	bool operator==(T val) const
	{
		return (_val == val);
	}

	/**
	 * Check if the ENUMERATION value is equal to the argument value.
	 *
	 * @param val The value to compare with.
	 * @return True if they are equal or false otherwise.
	 */
	bool operator!=(T val) const
	{
		return (_val != val);
	}

	/**
	 * Check if the ENUMERATION is equal to another ENUMERATION.
	 *
	 * @param e The ENUMERATION to compare with.
	 * @return True if they are equal or false otherwise.
	 */
	bool operator==(const enumeration& e) const
	{
		return (_val == e._val);
	}

	/**
	 * Check if the ENUMERATION is equal to another ENUMERATION.
	 *
	 * @param e The ENUMERATION to compare with.
	 * @return True if they are equal or false otherwise.
	 */
	bool operator!=(const enumeration& e) const
	{
		return (_val != e._val);
	}

	/**
	 * ENUMERATION data type output.
	 *
	 * @param os ostream.
	 * @param e ENUMERATION data type.
	 * @return ostream reference.
	 */
	friend std::ostream& operator<<(std::ostream& os, const enumeration& e)
	{
		std::ios::fmtflags prev;

		prev = os.setf(std::ios::hex, std::ios::basefield);
		os << uint(e._val);
		os.setf(prev);

		return os;
	}

private:
	uint8 _val;	/**< ENUMERATION data type value.	*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * STATUS data type enumeration.
 */
enum status_enum {
	status_success = 0,					/**< Status success.				*/
	status_failure = 1,					/**< Status failure.				*/
	status_rejected = 2,				/**< Status rejected.				*/
	status_authorization_failure = 3,	/**< Status authorization failure.	*/
	status_network_error = 4,			/**< Status network error.			*/
};

/**
 * STATUS data type.
 */
typedef enumeration<status_enum> status;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

#ifdef BOOST_MSVC
#	pragma warning(pop)
#endif

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_BASE__HPP_ */
