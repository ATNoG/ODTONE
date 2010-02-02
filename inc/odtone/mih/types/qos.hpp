//=============================================================================
// Brief   : MIH QOS Types
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

#ifndef ODTONE_MIH_TYPES_QOS__HPP_
#define ODTONE_MIH_TYPES_QOS__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
typedef uint8 num_cos_types;
typedef uint8 cos_id;

///////////////////////////////////////////////////////////////////////////////
struct pk_delay {
	cos_id cos;
	uint16 value;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & cos;
		ar & value;
	}
};

///////////////////////////////////////////////////////////////////////////////
struct min_pk_tx_delay : pk_delay { };

typedef std::vector<min_pk_tx_delay> min_pk_tx_delay_list;

///////////////////////////////////////////////////////////////////////////////
struct avg_pk_tx_delay : pk_delay { };

typedef std::vector<avg_pk_tx_delay> avg_pk_tx_delay_list;

///////////////////////////////////////////////////////////////////////////////
struct max_pk_tx_delay : pk_delay { };

typedef std::vector<max_pk_tx_delay> max_pk_tx_delay_list;

///////////////////////////////////////////////////////////////////////////////
struct pk_delay_jitter : pk_delay { };

typedef std::vector<pk_delay_jitter> pk_delay_jitter_list;

///////////////////////////////////////////////////////////////////////////////
struct pk_loss_rate : pk_delay { };

typedef std::vector<pk_loss_rate> pk_loss_rate_list;

///////////////////////////////////////////////////////////////////////////////
typedef boost::variant<num_cos_types,
					   min_pk_tx_delay_list,
					   avg_pk_tx_delay_list,
					   max_pk_tx_delay_list,
					   pk_delay_jitter_list,
					   pk_loss_rate_list> qos_param_val;

///////////////////////////////////////////////////////////////////////////////
struct qos_list {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & cos;
		ar & min_pk_delay_lst;
		ar & avg_pk_tx_delay_lst;
		ar & max_pk_tx_delay_lst;
		ar & pk_delay_jitter_lst;
		ar & pk_loss_rate_lst;
	}

	num_cos_types        cos;
	min_pk_tx_delay_list min_pk_delay_lst;
	avg_pk_tx_delay_list avg_pk_tx_delay_lst;
	max_pk_tx_delay_list max_pk_tx_delay_lst;
	pk_delay_jitter_list pk_delay_jitter_lst;
	pk_loss_rate_list    pk_loss_rate_lst;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_QOS__HPP_ */
