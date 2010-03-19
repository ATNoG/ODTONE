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

///////////////////////////////////////////////////////////////////////////////
#include "command_service.hpp"

#include "log.hpp"
#include "utils.hpp"
#include "mihfid.hpp"
#include "transmit.hpp"

#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/mih/request.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

command_service::command_service(local_transaction_pool &lpool)
	: _lpool(lpool)
{
}

bool command_service::link_get_parameters_request(mih::message_ptr &in,
						  mih::message_ptr &out)
{
	log(1, "(mics) received a Link_Get_Parameters.request from",
	    in->source().to_string());


	if(utils::is_local_request(in)) {
		//
		// Kick this message to MIH_Link SAP.
		//
		// The solution found to handle this corner case in the
		// 802.21 standard was to send the message, as is, to the
		// link sap.
		//
		// local_transactions was made to handle request's
		// from users to peer mihf's but in this case we add an
		// entry to handle the MIH_Link_Get_Parameters and
		// Link_Get_Parameters.
		//
		in->destination(mih::id("link"));
		_lpool.add(in);
		in->source(mihfid);
		// transmit(in);

		return false;
	} else {
		return utils::forward_request(in);
	}

	return false;
}

bool command_service::link_get_parameters_response(mih::message_ptr &in,
						   mih::message_ptr &out)
{
	log(1, "(mics) received Link_Get_Parameters.response from ",
	    in->source().to_string());

	pending_transaction p;
	mih::octet_string from = in->source().to_string();

	if(!_lpool.get(from, p)) {
		log(1, "(mics) warning: no local transaction for this msg ",
			"discarding it");
		return false;
	}

	in->tid(p.tid);
	in->source(mihfid);
	in->destination(mih::id(p.user));

	log(1, "(mics) forwarding Link_Get_Parameters.response to ", p.user);

	// transmit(in);

	return false;
}

bool command_service::link_configure_thresholds_request(mih::message_ptr &in,
							mih::message_ptr &out)
{
	log(1, "(mics) received a Link_Configure_Thresholds.request from",
	    in->source().to_string());

	if(utils::is_local_request(in)) {
		//
		// Kick this message to MIH_Link SAP.
		//
		// The solution found to handle this corner case in the
		// 802.21 standard was to send the message, as is, to the
		// link sap.
		//
		// local_transactions was made to handle request's
		// from users to peer mihf's but in this case we add an
		// entry to handle the MIH_Link_Get_Parameters and
		// Link_Get_Parameters.
		//
		in->destination(mih::id("link"));
		_lpool.add(in);
		in->source(mihfid);
		// transmit(in);

		return false;
	} else {
		return utils::forward_request(in);
	}


	return false;
}

bool command_service::link_configure_thresholds_response(mih::message_ptr &in,
							 mih::message_ptr &out)
{
	log(1, "(mics) received Link_Configure_Thresholds.response from ",
	    in->source().to_string());

	pending_transaction p;
	if(!_lpool.get(in->source().to_string(), p)) {
		log(1, "(mics) warning: no local transaction for this msg ",
		    "discarding it");
		return false;
	}

	in->tid(p.tid);
	in->source(mihfid);
	in->destination(mih::id(p.user));

	log(1, "(mics) forwarding Link_Configure_Thresholds.response to ", p.user);

	// transmit(in);

	return false;
}


bool command_service::link_actions_request(mih::message_ptr &in,
					   mih::message_ptr &out)
{
	log(1, "(mics) received a Link_Actions.request from",
	    in->source().to_string());

	if(utils::is_local_request(in)) {
		//
		// Kick this message to MIH_Link SAP.
		//
		// The solution found to handle this corner case in the
		// 802.21 standard was to send the message, as is, to the
		// link sap.
		//
		in->destination(mih::id("link"));
		_lpool.add(in);
		in->source(mihfid);
		// transmit(in);

		return false;
	} else {
		return utils::forward_request(in);
	}

	return false;
}


bool command_service::link_actions_response(mih::message_ptr &in,
					    mih::message_ptr &out)
{
	log(1, "(mics) received Link_Actions.response from ",
	    in->source().to_string());

	pending_transaction p;
	if(!_lpool.get(in->source().to_string(), p))
		{
			log(1, "(mics) no local pending transaction for this message, discarding");
			return false;
		}

	in->tid(p.tid);
	in->source(mihfid);
	in->destination(mih::id(p.user));

	log(1, "(mics) forwarding Link_Actions.response to ", p.user);

	// transmit(in);

	return false;
}

bool generic_command_request(const char *recv_msg,
			     const char *send_msg,
			     mih::message_ptr &in,
			     mih::message_ptr &out)
{
	log(1, recv_msg, in->source().to_string());

	if(utils::is_local_request(in)) {
		//
		// Kick this message to default MIH User as an indication
		//
		in->opcode(mih::operation::indication);
		in->destination(mih::id("user"));
		//
		// source identifier is the remote MIHF
		//
		log(1, send_msg);
		// transmit(in);

		return false;
	} else {
		return utils::forward_request(in);
	}

	return false;
}

bool generic_command_response(const char *recv_msg,
			      const char *send_msg,
			      mih::message_ptr &in,
			      mih::message_ptr &out)
{
	log(1, recv_msg, in->source().to_string());

	if(utils::is_local_request(in)) {
		//
		// Kick this message to default MIH User as an indication
		//
		log(1, send_msg);
		in->opcode(mih::operation::confirm);
		in->destination(mih::id("user"));
		//
		// source identifier is the remote MIHF
		//
		// transmit(in);

		return false;
	} else {
		return utils::forward_request(in);
	}

}

////

bool command_service::net_ho_candidate_query_request(mih::message_ptr &in,
						     mih::message_ptr &out)
{
	return generic_command_request("(mics) received a Net_HO_Candidate_Query.request from",
				       "(mics) sending a Net_HO_Candidate_Query.indication to user.",
				       in, out);
}

bool command_service::net_ho_candidate_query_response(mih::message_ptr &in,
						      mih::message_ptr &out)
{
	return generic_command_response("(mics) received Net_HO_Candidate_Query.response from ",
					"(mics) sending a Net_HO_Candidate_Query.confirm to user",
					in, out);
}

/////

bool command_service::mn_ho_candidate_query_request(mih::message_ptr &in,
						    mih::message_ptr &out)
{
	return generic_command_request("(mics) received a MN_HO_Candidate_Query.request from",
				       "(mics) sending a MN_HO_Candidate_Query.indication to user.",
				       in, out);
}

bool command_service::mn_ho_candidate_query_response(mih::message_ptr &in,
						     mih::message_ptr &out)
{
	return generic_command_response("(mics) received MN_HO_Candidate_Query.response from ",
					"(mics) sending a MN_HO_Candidate_Query.confirm to user",
					in, out);
}


bool command_service::n2n_ho_query_resources_request(mih::message_ptr &in,
						     mih::message_ptr &out)
{
	return generic_command_request("(mics) received a MN_N2N_HO_Query_Resources.request from",
				       "(mics) sending a MN_N2N_HO_Query_Resources.indication to user.",
				       in, out);
}

bool command_service::n2n_ho_query_resources_response(mih::message_ptr &in,
						      mih::message_ptr &out)
{
	return generic_command_response("(mics) received MN_N2N_HO_Query_Resources.response from ",
					"(mics) sending a MN_N2N_HO_Query_Resources.confirm to user",
					in, out);
}


bool command_service::mn_ho_commit_request(mih::message_ptr &in,
					   mih::message_ptr &out)
{
	return generic_command_request("(mics) received a MN_HO_Commit.request from",
				       "(mics) sending a MN_HO_Commit.indication to user.",
				       in, out);
}

bool command_service::mn_ho_commit_response(mih::message_ptr &in,
					    mih::message_ptr &out)
{
	return generic_command_response("(mics) received MN_HO_Commit.response from ",
					"(mics) sending a MN_HO_Commit.confirm to user",
					in, out);
}


bool command_service::net_ho_commit_request(mih::message_ptr &in,
					    mih::message_ptr &out)
{
	return generic_command_request("(mics) received a Net_HO_Commit.request from",
				       "(mics) sending a Net_HO_Commit.indication to user.",
				       in, out);
}

bool command_service::net_ho_commit_response(mih::message_ptr &in,
					     mih::message_ptr &out)
{
	return generic_command_response("(mics) received Net_HO_Commit.response from ",
					"(mics) sending a Net_HO_Commit.confirm to user",
					in, out);
}

//

bool command_service::mn_ho_complete_request(mih::message_ptr &in,
					     mih::message_ptr &out)
{
	return generic_command_request("(mics) received a MN_HO_Complete.request from",
				       "(mics) sending a MN_HO_Complete.indication to user.",
				       in, out);
}

bool command_service::mn_ho_complete_response(mih::message_ptr &in,
					      mih::message_ptr &out)
{
	return generic_command_response("(mics) received MN_HO_Complete.response from ",
					"(mics) sending a MN_HO_Complete.confirm to user",
					in, out);
}


bool command_service::n2n_ho_commit_request(mih::message_ptr &in,
					    mih::message_ptr &out)
{
	return generic_command_request("(mics) received a N2N_HO_Commit.request from",
				       "(mics) sending a N2N_HO_Commit.indication to user.",
				       in, out);
}

bool command_service::n2n_ho_commit_response(mih::message_ptr &in,
					     mih::message_ptr &out)
{
	return generic_command_response("(mics) received N2N_HO_Commit.response from ",
					"(mics) sending a N2N_HO_Commit.confirm to user",
					in, out);
}


bool command_service::n2n_ho_complete_request(mih::message_ptr &in,
					      mih::message_ptr &out)
{
	return generic_command_request("(mics) received a N2N_HO_Complete.request from",
				       "(mics) sending a N2N_HO_Complete.indication to user.",
				       in, out);
}

bool command_service::n2n_ho_complete_response(mih::message_ptr &in,
					       mih::message_ptr &out)
{
	return generic_command_response("(mics) received N2N_HO_Complete.response from ",
					"(mics) sending a N2N_HO_Complete.confirm to user",
					in, out);
}


} /* namespace mihf */ } /* namespace odtone */

