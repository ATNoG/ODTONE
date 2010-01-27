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

#include <odtone/mihf/utils.hpp>

#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>
#include <odtone/mih/tlv.hpp>
#include <odtone/mihf/log.hpp>
#include <odtone/mihf/mihfid.hpp>
#include <odtone/mihf/local_transactions.hpp>
#include <odtone/mihf/transaction_manager.hpp>
#include <odtone/mihf/sqlite_handler.hpp>


namespace odtone { namespace mihf { namespace utils {

bool forward_to_user(uint16 mid, mih::message& in, mih::message& out)
{
	// out = in;

	// sqlite_result *r = db->get_result("SELECT user, transid FROM pending_transactions WHERE msgid = %d AND destination = %Q ",
	//                                   mid,
	//                                   in->source().to_string().c_str());
	// while(db->fetch_row(r))
	//   {
	//     mih::octet_string user    = (mih::octet_string) db->getstr(r);
	//     uint16            transid = (uint16) db->getval(r);

	//     out->destination(mih::id(user.c_str()));
	//     out->set_transid(transid);

	//     comhand->send(out);
	//   }
	// db->free_result(r);

	// db->execute("DELETE FROM pending_transactions WHERE msgid = %d AND destination = %Q;", mid, in->source().to_string().c_str());

	return false;
}

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
	tmanager->message_out(in);

	return false;
}


void register_interface(mih::link_tuple_id &li)
{
	mih::mac_addr mac = boost::get<mih::mac_addr>(li.addr);

	db->execute("insert into link_addr(link_addr_type, link_addr) values (%d, %Q)", 1, mac.address().c_str());

	uint16 linktype_id = db->getval("select id from link_addr where link_addr_type = %d and link_addr = %Q", 1, mac.address().c_str());

	db->execute("insert into link_id(link_type, link_addr) values (%d, %d)", mac.type(), linktype_id);

	uint linkid_id = db->getval("select id from link_id where link_type = %d and link_addr = %d", mac.type(), linktype_id);

	db->execute("insert into link_tuple_id(link_id) values(%d)", linkid_id);
}

} } }
