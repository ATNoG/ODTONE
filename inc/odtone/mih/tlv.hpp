//=============================================================================
// Brief   : MIH TLV Serialization DSL
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

#ifndef ODTONE_MIH_TLV__HPP_
#define ODTONE_MIH_TLV__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/exception.hpp>
#include <odtone/mih/archive.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/optional.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * Bad TLV exception.
 */
struct bad_tlv : virtual public exception {
	/**
	 * Construct a bad TLV exception.
	 */
	bad_tlv() : exception("odtone::mih::tlv_fwd::serialize(iarchive&): TLV missmatch")
	{ }
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Base TLV.
 */
template<class ValueT, ValueT Value>
struct base_tlv_ {
	/**
	 * Deserialize the TLV type value.
	 *
	 * @param ar The input archive from where extract the TLV value.
	 * @param val The value to deserialize.
	 * @return True if the value was deserialized or false otherwise.
	 */
	template<class T>
	static bool serialize(iarchive& ar, T& val)
	{
		uint pos = ar.position();
		ValueT tp;

		ar & tp;
		if (tp != Value) {
			ar.position(pos);
			return false;
		}

		try {
			uint len = ar.list_length();
			iarchive in(ar, len);
			in & val;

		} catch (...) {
			ar.position(pos);
			throw;
		}
		return true;
	}

	/**
	 * Serialize the TLV type value.
	 *
	 * @param ar The output archive to where insert the TLV value.
	 * @param val The value to serialize.
	 */
	template<class T>
	static void serialize(oarchive& ar, T& val)
	{
		uint pos = ar.position();
		archive tmp;
		oarchive out(tmp);

		out & val;
		try {
			ar & Value;
			ar & tmp.buffer();

		} catch (...) {
			ar.position(pos);
			throw;
		}
	}
};

/**
 * MIH TLV
 */
template<uint8 Value>
struct tlv_ : base_tlv_<uint8, Value> {
	typedef tlv_<Value> tlv_serializer;
};

/**
 * MIH TLV
 */
template<uint32 Value>
struct tlv4_ : base_tlv_<uint32, Value> {
	typedef tlv4_<Value> tlv_serializer;
};

/**
 * Vendor's IEEE organizationally unique identifier (OUI).
 */
template<uint8 A, uint8 B, uint8 C>
struct oui_ {
	typedef oui_<A, B, C> tlv_serializer;

	/**
	 * Deserialize the TLV type value.
	 *
	 * @param ar The input archive from where extract the TLV value.
	 * @param val The value to deserialize.
	 * @return True if the value was deserialized or false otherwise.
	 */
	template<class T>
	static bool serialize(iarchive& ar, T& val)
	{
		uint pos = ar.position();
		uint8 tp;

		ar & tp;
		if (tp != 100) {
			ar.position(pos);
			return false;
		}

		try {
			uint len = ar.list_length();

			if (len < 3) {
				ar.position(pos);
				return false;
			}

			uint8 oui[3];

			ar & oui[0];
			ar & oui[1];
			ar & oui[2];

			if (oui[0] != A || oui[1] != B || oui[2] != C) {
				ar.position(pos);
				return false;
			}

			iarchive in(ar, len - 3);

			in & val;

		} catch (...) {
			ar.position(pos);
			throw;
		}
		return true;
	}

	/**
	 * Serialize the TLV type value.
	 *
	 * @param ar The output archive to where insert the TLV value.
	 * @param val The value to serialize.
	 */
	template<class T>
	static void serialize(oarchive& ar, T& val)
	{
		uint pos = ar.position();
		archive tmp;
		oarchive out(tmp);

		out & A;
		out & B;
		out & C;
		out & val;
		try {
			uint8 tp = 100;

			ar & tp;
			ar & tmp.buffer();

		} catch (...) {
			ar.position(pos);
			throw;
		}
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * The MIH types support serialization and deserialization for the
 * input archive and output archive. However, these particular
 * archives do not include the TLVs fields.
 * So this class is responsible for managing the mandatory TLVs and
 * for offering mechanisms to serialize and deserialize them.
 */
template<class T, class TLV>
class tlv_type_ {
	typedef typename TLV::tlv_serializer impl;

public:
	typedef tlv_type_<T, TLV> tlv_type;

public:
	/**
	 * Construct a TLV of a particular type.
	 *
	 * @param val The value of the TLV.
	 */
	tlv_type_(T& val)
		: _val(val)
	{ }

	/**
	 * Deserialize the TLV type value.
	 *
	 * @param ar The input archive from where extract the TLV value.
	 */
	void serialize(iarchive& ar) const
	{
		bool res = impl::serialize(ar, _val);
		if (!res)
			boost::throw_exception(bad_tlv());
	}

	/**
	 * Serialize the TLV type value.
	 *
	 * @param ar The output archive to where serialize the TLV value.
	 */
	void serialize(oarchive& ar) const
	{
		impl::serialize(ar, _val);
	}

private:
	T& _val;	/**< TLV value.	*/
};

/**
 * The MIH types support serialization and deserialization for the
 * input archive and output archive. However, these particular
 * archives do not include the TLVs fields.
 * So this class is responsible for managing the optional TLVs and
 * for offering mechanisms to serialize and deserialize them.
 */
template<class T, class TLV>
class tlv_type_<boost::optional<T>, TLV> {
	typedef typename TLV::tlv_serializer impl;

public:
	typedef tlv_type_<boost::optional<T>, TLV> tlv_type;

public:
	/**
	 * Construct a TLV of a particular type.
	 *
	 * @param val value of the TLV.
	 */
	tlv_type_(boost::optional<T>& val)
		: _val(val)
	{ }

	/**
	 * Deserialize the TLV type value.
	 *
	 * @param ar The input archive from where parse the TLV value.
	 */
	void serialize(iarchive& ar) const
	{
		if (ar.position() >= ar.length())
			return;

		T tmp;

		bool res = impl::serialize(ar, tmp);
		if (res)
			_val = tmp;
		else
			_val = boost::none;
	}

	/**
	 * Serialize the TLV type value.
	 *
	 * @param ar The output archive to where serialize the TLV value.
	 */
	void serialize(oarchive& ar) const
	{
		if (_val)
			impl::serialize(ar, _val.get());
	}

private:
	boost::optional<T>& _val;	/**< TLV value.	*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Cast between the number of TLV and the data type presented in it,
 * and the correspondent TLV type.
 */
template<class T, class TLV>
class tlv_cast_ {
	typedef typename tlv_type_<T, TLV>::tlv_type                  tlv_type;
	typedef typename tlv_type_<boost::optional<T>, TLV>::tlv_type tlv_optional_type;

public:
	/**
	 * Cast between the number of TLV and the data type presented in it,
	 * and the correspondent TLV type.
	 *
	 * @param val The value of the TLV.
	 * @return The correspondent TLV type.
	 */
	tlv_type operator()(const T& val) const
	{
		return tlv_type(const_cast<T&>(val));
	}

	/**
	 * Cast between the number of TLV and the data type presented in it,
	 * and the correspondent TLV type. However it supports optional value.
	 *
	 * @param val The value of the TLV.
	 * @return The correspondent TLV type.
	 */
	tlv_optional_type operator()(const boost::optional<T>& val) const
	{
		return tlv_optional_type(const_cast<boost::optional<T>&>(val));
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * This class allows to check if a given class is a TLV.
 * It has only a boolean value that is true when the given class is a TLV, or
 * false otherwise.
 */
template<class T>
class is_tlv_type {
	typedef char true_t;
	class false_t { char dummy[2]; };

	template<class U> static true_t  test(typename U::tlv_type* = 0);
	template<class U> static false_t test(...);

public:
	static const bool value = sizeof(test<T>(0)) == sizeof(true_t);
};

///////////////////////////////////////////////////////////////////////////////
template<class T>
inline typename boost::enable_if<is_tlv_type<T>, iarchive&>::type operator&(iarchive& ar, const T& val)
{
	return ar & const_cast<T&>(val);
}

template<class T>
inline typename boost::enable_if<is_tlv_type<T>, oarchive&>::type operator&(oarchive& ar, const T& val)
{
	return ar & const_cast<T&>(val);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TLV__HPP_ */
