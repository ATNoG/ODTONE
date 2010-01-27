//=============================================================================
// Brief   : MIH Binary Query Types
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

#ifndef ODTONE_MIH_TYPES_BIN_QUERY__HPP_
#define ODTONE_MIH_TYPES_BIN_QUERY__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/information.hpp>
#include <odtone/mih/types/location.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
typedef cost_curr               curr_pref;
typedef std::vector<network_id> netwk_inc;
typedef uint32                  nghb_radius;
typedef uint32                  ie_type;
typedef std::vector<ie_type>    rpt_templ;

///////////////////////////////////////////////////////////////////////////////
enum net_type_inc_enum {
	net_type_inc_gsm = 0,
	net_type_inc_gprs = 1,
	net_type_inc_edge = 2,
	net_type_inc_ethernet = 3,
	net_type_inc_wireless_other = 4,
	net_type_inc_ieee802_21 = 5,
	net_type_inc_cdma2000 = 6,
	net_type_inc_umts = 7,
	net_type_inc_cdma2000_hrpd = 8,
	net_type_inc_ieee802_16 = 9,
	net_type_inc_ieee802_20 = 10,
	net_type_inc_ieee802_22 = 11,
};

typedef bitmap<32, net_type_inc_enum> net_type_inc;

///////////////////////////////////////////////////////////////////////////////
struct querier_loc {
	querier_loc() : _location(null()), _link_addr(null()), _nghb_radius(null())
	{ }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _location;
		ar & _link_addr;
		ar & _nghb_radius;
	}


	boost::variant<null, location>    _location;
	boost::variant<null, link_addr>   _link_addr;
	boost::variant<null, nghb_radius> _nghb_radius;
};

///////////////////////////////////////////////////////////////////////////////
struct rpt_limit {
	rpt_limit() : _max_ies(0), _start_entry(0)
	{ }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _max_ies;
		ar & _start_entry;
	}


	uint16 _max_ies;
	uint16 _start_entry;
};

///////////////////////////////////////////////////////////////////////////////
struct iq_bin_data {
	iq_bin_data()
		: _querier_loc(null()), _net_type_inc(null()), _netwk_inc(null()),
		_rpt_templ(null()), _rpt_limit(null()), _currency(null())
	{ }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _querier_loc;
		ar & _net_type_inc;
		ar & _netwk_inc;
		ar & _rpt_templ;
		ar & _rpt_limit;
		ar & _currency;
	}


	boost::variant<null, querier_loc>  _querier_loc;
	boost::variant<null, net_type_inc> _net_type_inc;
	boost::variant<null, netwk_inc>    _netwk_inc;
	boost::variant<null, rpt_templ>    _rpt_templ;
	boost::variant<null, rpt_limit>    _rpt_limit;
	boost::variant<null, curr_pref>    _currency;
};

typedef std::vector<iq_bin_data> iq_bin_data_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_BIN_QUERY__HPP_ */
