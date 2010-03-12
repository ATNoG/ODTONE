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
#include <odtone/mih/message.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

class command_service
	: boost::noncopyable
{
public:
	command_service();
	~command_service();

	bool link_get_parameters_request(mih::message_ptr &in, mih::message_ptr &out);
	bool link_get_parameters_response(mih::message_ptr &in, mih::message_ptr &out);

	bool link_configure_thresholds_request(mih::message_ptr &in, mih::message_ptr &out);
	bool link_configure_thresholds_response(mih::message_ptr &in, mih::message_ptr &out);

	bool link_actions_request(mih::message_ptr &in, mih::message_ptr &out);
	bool link_actions_response(mih::message_ptr &in, mih::message_ptr &out);

	bool net_ho_candidate_query_request(mih::message_ptr &in, mih::message_ptr &out);
	bool net_ho_candidate_query_response(mih::message_ptr &in, mih::message_ptr &out);

	bool mn_ho_candidate_query_request(mih::message_ptr &in, mih::message_ptr &out);
	bool mn_ho_candidate_query_response(mih::message_ptr &in, mih::message_ptr &out);

	bool n2n_ho_query_resources_request(mih::message_ptr &in, mih::message_ptr &out);
	bool n2n_ho_query_resources_response(mih::message_ptr &in, mih::message_ptr &out);

	bool mn_ho_commit_request(mih::message_ptr &in, mih::message_ptr &out);
	bool mn_ho_commit_response(mih::message_ptr &in, mih::message_ptr &out);

	bool net_ho_commit_request(mih::message_ptr &in, mih::message_ptr &out);
	bool net_ho_commit_response(mih::message_ptr &in, mih::message_ptr &out);

	bool n2n_ho_commit_request(mih::message_ptr &in, mih::message_ptr &out);
	bool n2n_ho_commit_response(mih::message_ptr &in, mih::message_ptr &out);

	bool mn_ho_complete_request(mih::message_ptr &in, mih::message_ptr &out);
	bool mn_ho_complete_response(mih::message_ptr &in, mih::message_ptr &out);

	bool n2n_ho_complete_request(mih::message_ptr &in, mih::message_ptr &out);
	bool n2n_ho_complete_response(mih::message_ptr &in, mih::message_ptr &out);

private:

};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

#endif
