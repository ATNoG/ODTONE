//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Simao Reis <sreis@av.it.pt>
//

//=============================================================================
// Brief     : MIH Command Service
//=============================================================================

#ifndef ODTONE_MIHF_COMMAND_SERVICE_HPP
#define ODTONE_MIHF_COMMAND_SERVICE_HPP

///////////////////////////////////////////////////////////////////////////////
#include "local_transaction_pool.hpp"
#include "transmit.hpp"
#include "meta_message.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

class command_service
	: boost::noncopyable
{
public:
	command_service(local_transaction_pool &lpool, transmit &t);

	bool link_get_parameters_request(meta_message_ptr &in, meta_message_ptr &out);
	bool link_get_parameters_response(meta_message_ptr &in, meta_message_ptr &out);

	bool link_configure_thresholds_request(meta_message_ptr &in, meta_message_ptr &out);
	bool link_configure_thresholds_response(meta_message_ptr &in, meta_message_ptr &out);

	bool link_actions_request(meta_message_ptr &in, meta_message_ptr &out);
	bool link_actions_response(meta_message_ptr &in, meta_message_ptr &out);

	bool net_ho_candidate_query_request(meta_message_ptr &in, meta_message_ptr &out);
	bool net_ho_candidate_query_response(meta_message_ptr &in, meta_message_ptr &out);

	bool mn_ho_candidate_query_request(meta_message_ptr &in, meta_message_ptr &out);
	bool mn_ho_candidate_query_response(meta_message_ptr &in, meta_message_ptr &out);

	bool n2n_ho_query_resources_request(meta_message_ptr &in, meta_message_ptr &out);
	bool n2n_ho_query_resources_response(meta_message_ptr &in, meta_message_ptr &out);

	bool mn_ho_commit_request(meta_message_ptr &in, meta_message_ptr &out);
	bool mn_ho_commit_response(meta_message_ptr &in, meta_message_ptr &out);

	bool net_ho_commit_request(meta_message_ptr &in, meta_message_ptr &out);
	bool net_ho_commit_response(meta_message_ptr &in, meta_message_ptr &out);

	bool n2n_ho_commit_request(meta_message_ptr &in, meta_message_ptr &out);
	bool n2n_ho_commit_response(meta_message_ptr &in, meta_message_ptr &out);

	bool mn_ho_complete_request(meta_message_ptr &in, meta_message_ptr &out);
	bool mn_ho_complete_response(meta_message_ptr &in, meta_message_ptr &out);

	bool n2n_ho_complete_request(meta_message_ptr &in, meta_message_ptr &out);
	bool n2n_ho_complete_response(meta_message_ptr &in, meta_message_ptr &out);

protected:
	bool generic_command_request(const char *recv_msg,
				     const char *send_msg,
				     meta_message_ptr &in,
				     meta_message_ptr &out);

	bool generic_command_response(const char *recv_msg,
				      const char *send_msg,
				      meta_message_ptr &in,
				      meta_message_ptr &out);

	local_transaction_pool	&_lpool;
	transmit		&_transmit;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

#endif
