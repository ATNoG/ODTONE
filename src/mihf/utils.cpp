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
#include "utils.hpp"
#include "log.hpp"
#include "mihfid.hpp"
#include "local_transactions.hpp"
#include "transaction_manager.hpp"

#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>
#include <odtone/mih/tlv.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf { namespace utils {

bool is_local_request(mih::message_ptr &in)
{
	return ((in->destination().to_string().length() == 0) ||
			(mihfid == in->destination()));
}


bool forward_request(mih::message_ptr &in)
{
	log(1, "(utils) forwarding request to ", in->destination().to_string());

	local_transactions->add(in);
	in->source(mihfid);
	// tmanager->message_out(in);

	return false;
}

} /* namespace utils */ } /* namespace mihf */ } /* namespace odtone */
