//=============================================================================
// Brief   : MIH Binary Information Query Response Types
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

#ifndef ODTONE_MIH_TYPES_BIN_RESPONSE__HPP_
#define ODTONE_MIH_TYPES_BIN_RESPONSE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/exception.hpp>
#include <odtone/mih/tlv.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

/**
 * IR_BIN_DATA input archive.
 */
class ir_bin_iarchive;

/**
 * IR_BIN_DATA output archive.
 */
class ir_bin_oarchive;

///////////////////////////////////////////////////////////////////////////////
/**
 * IR_BIN_DATA data type.
 */
class ir_bin_data {
//
// TODO: need to improve this with a generic IE element, so this can be turned into a std::vector
//
	friend class ir_bin_iarchive;
	friend class ir_bin_oarchive;

	struct unspecified_bool_t {
		void true_() {}
	};
	typedef void (unspecified_bool_t::*unspecified_bool)();

public:
	/**
	 * Construct an empty IR_BIN_DATA data type.
	 */
	ir_bin_data()
		: _cnt(0)
	{ }

	/**
	 * Deserialize the IR_BIN_DATA data type.
	 *
	 * @param ar The archive from where deserialize the data type.
	 */
	void serialize(iarchive& ar)
	{
		_cnt = ar.list_length();

		_ar.clear();
		for (uint i = 0; i < _cnt; ++i) {
			uint pos;
			uint end;

			pos = ar.position();
			ar.position(pos + 4);
			end = ar.list_length();
			end += ar.position();
			_ar.append(ar.begin() + pos, ar.begin() + end);
			ar.position(end);
		}
	}

	/**
	 * Serialize the IR_BIN_DATA data type.
	 *
	 * @param ar The archive to where serialize the data type.
	 */
	void serialize(oarchive& ar)
	{
		ar.list_length(_cnt);
		ar.append(_ar.begin(), _ar.end());
	}

	/**
	 * Get the IR_BIN_DATA input archive.
	 *
	 * @return The IR_BIN_DATA input archive.
	 */
	ir_bin_iarchive input();

	/**
	 * Get the IR_BIN_DATA output archive.
	 *
	 * @return The IR_BIN_DATA output archive.
	 */
	ir_bin_oarchive output();

	operator unspecified_bool()
	{
		return _cnt ? &unspecified_bool_t::true_ : 0;
	}

	bool operator!()
	{
		return !_cnt;
	}

private:
	archive _ar;	/**< Archive of the IR_BIN_DATA.			*/
	uint    _cnt;	/**< Number of elements in the IR_BIN_DATA.	*/
};

/**
 * LIST(IR_BIN_DATA) data type.
 */
typedef std::vector<ir_bin_data> ir_bin_data_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * ir_bin_archive_error exception.
 */
struct ir_bin_iarchive_error : virtual public exception {
	/**
	 * Construct a ir_bin_iarchive_erro exception.
	 */
	ir_bin_iarchive_error() : exception("odtone::mih::ir_bin_iarchive: invalid number of elements")
	{ }
};

///////////////////////////////////////////////////////////////////////////////
/**
 * IR_BIN_DATA input archive.
 */
class ir_bin_iarchive {
public:
	/**
	 * Construct a ir_bin_iarchive from a ir_bin_data data type.
	 *
	 * @param data The ir_bin_data from where extract the information.
	 */
	ir_bin_iarchive(ir_bin_data& data)
		: _ar(data._ar), _cnt(data._cnt), _pos(0)
	{ }

	/**
	 * Serialize an IE to the IR_BIN_DATA data type.
	 *
	 * @param val The value to serialize.
	 */
	template<class T>
	typename boost::enable_if<is_tlv_type<T>, ir_bin_iarchive&>::type operator&(const T& val)
	{
		if (_pos < _cnt) {
			val.serialize(_ar);
			++_pos;

		} else {
			boost::throw_exception(ir_bin_iarchive_error());
		}

		return *this;
	}

private:
	iarchive _ar;	/**< Input archive of the IR_BIN_DATA.		*/
	uint&    _cnt;	/**< Number of elements in the IR_BIN_DATA.	*/
	uint     _pos;	/**< Position in the input archive.			*/
};

/**
 * IR_BIN_DATA output archive.
 */
class ir_bin_oarchive {
public:
	/**
	 * Construct a ir_bin_iarchive.
	 */
	ir_bin_oarchive(ir_bin_data& data)
		: _ar(data._ar), _cnt(data._cnt)
	{ }

	/**
	 * Deserialize an IE from the IR_BIN_DATA data type.
	 *
	 * @param val The value to deserialize.
	 */
	template<class T>
	typename boost::enable_if<is_tlv_type<T>, ir_bin_oarchive&>::type operator&(const T& val)
	{
		val.serialize(_ar);
		++_cnt;

		return *this;
	}

private:
	oarchive _ar;	/**< Output archive of the IR_BIN_DATA.		*/
	uint&    _cnt;	/**< Number of elements in the IR_BIN_DATA.	*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Get the IR_BIN_DATA input archive.
 *
 * @return The IR_BIN_DATA input archive.
 */
inline ir_bin_iarchive ir_bin_data::input()
{
	return ir_bin_iarchive(*this);
}

/**
 * Get the IR_BIN_DATA output archive.
 *
 * @return The IR_BIN_DATA output archive.
 */
inline ir_bin_oarchive ir_bin_data::output()
{
	return ir_bin_oarchive(*this);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_BIN_RESPONSE__HPP_ */
