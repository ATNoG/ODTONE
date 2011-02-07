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
// Author:     Carlos Guimarães <cguimaraes@av.it.pt>
//

#ifndef ODTONE_MIHF_LINK_RESPONSE_POOL__HPP
#define ODTONE_MIHF_LINK_RESPONSE_POOL__HPP

///////////////////////////////////////////////////////////////////////////////
#include "meta_message.hpp"

#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>

#include <boost/thread.hpp>
#include <list>

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

struct pending_link_response {
	mih::octet_string    user;
	uint16               tid;
	struct capabilities {
		mih::event_list   event_list;
		mih::command_list command_list;
	} cap;
	mih::link_status_rsp link_status;
	struct action_response {
		mih::link_ac_result                      link_ac_result;
		boost::optional<mih::link_scan_rsp_list> link_scan_rsp_list;
	} action;
};

class link_response_pool
{
public:
	link_response_pool();

	void add(mih::octet_string user,
                 uint16 tid,
                 mih::event_list event,
                 mih::command_list command);

	void add(mih::octet_string user,
                 uint16 tid,
	         mih::link_status_rsp link_status);

	void add(mih::octet_string user,
                 uint16 tid,
	         boost::optional<mih::link_scan_rsp_list> link_scan_rsp_list,
	         mih::link_ac_result link_ac_result);

	void del(const uint16 tid, const mih::octet_string id);

	pending_link_response find(const uint16 tid, const mih::octet_string id);

	bool check(const uint16 tid, const mih::octet_string id);

protected:
	std::list<pending_link_response> _cpool;
	boost::mutex _mutex;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */


#endif
