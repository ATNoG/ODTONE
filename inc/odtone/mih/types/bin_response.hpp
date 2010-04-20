//=============================================================================
// Brief   : MIH Binary Information Query Response Types
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

#ifndef ODTONE_MIH_TYPES_BIN_RESPONSE__HPP_
#define ODTONE_MIH_TYPES_BIN_RESPONSE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/tlv.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
class ir_bin_iarchive;
class ir_bin_oarchive;

class ir_bin_data {
	friend class ir_bin_iarchive;
	friend class ir_bin_oarchive;

	struct unspecified_bool_t {
		void true_() {}
	};
	typedef void (unspecified_bool_t::*unspecified_bool)();

public:
	ir_bin_data()
		: _cnt(0)
	{ }

	void serialize(iarchive& ar)
	{
		_cnt = ar.list_length();

		//TODO: we need to known the actual size in octets to avoid uncessary copies
		_ar.clear();
		_ar.append(ar.buffer().begin(), ar.buffer().end());
	}

	void serialize(oarchive& ar)
	{
		ar.list_length(_cnt);
		ar.append(_ar.buffer().begin(), _ar.buffer().end());
	}

	ir_bin_iarchive input();
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
	archive _ar;
	uint    _cnt;
};

typedef std::vector<ir_bin_data> ir_bin_data_list;

///////////////////////////////////////////////////////////////////////////////
class ir_bin_iarchive {
public:
	ir_bin_iarchive(ir_bin_data& data)
		: _data(data)
	{ }

	template<class T>
	typename boost::enable_if<is_tlv_type<T>, ir_bin_iarchive&>::type operator&(const T& val)
	{
		if (!_data._cnt)
			return *this; //TODO: should we throw an error?

		val.serialize(_data._ar.input());
		--_data._cnt;

		return *this;
	}

private:
	ir_bin_data& _data;
};

class ir_bin_oarchive {
public:
	ir_bin_oarchive(ir_bin_data& data)
		: _data(data)
	{ }

	template<class T>
	typename boost::enable_if<is_tlv_type<T>, ir_bin_oarchive&>::type operator&(const T& val)
	{
		val.serialize(_data._ar.output());
		++_data._cnt;

		return *this;
	}

private:
	ir_bin_data& _data;
};

///////////////////////////////////////////////////////////////////////////////
inline ir_bin_iarchive ir_bin_data::input()
{
	return ir_bin_iarchive(*this);
}

inline ir_bin_oarchive ir_bin_data::output()
{
	return ir_bin_oarchive(*this);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_BIN_RESPONSE__HPP_ */
