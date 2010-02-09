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

#include <odtone/debug.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/types/information.hpp>
#include <odtone/mih/types/capabilities.hpp>
#include <odtone/mih/types/capabilities.hpp>
#include <odtone/mih/config.hpp>
#include <odtone/mih/tlv.hpp>
#include <odtone/mih/tlv_types.hpp>

#include <odtone/mihf/generic_server.hpp>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <boost/asio.hpp>


#include <odtone/miis/information_containers.hpp>

using namespace odtone;
using boost::asio::ip::udp;

class dummy_server
	: public mihf::generic_server
{
public:
	dummy_server(boost::asio::io_service &io)
		: mihf::generic_server(io)
	{
	}

protected:
	void process_message(mih::message_ptr& msg)
	{
		mih::ir_bin_data_list		bin_data_list;

		*msg >> mih::response(mih::response::get_information)
			& mih::tlv_info_resp_bin_data_list(bin_data_list);

		mih::ir_bin_data bd = bin_data_list[0];

		miis::ie_container_list_of_networks l;
		bd.input() & miis::tlv_ie_container_list_of_networks(l);

	}
};


int main(int argc, char **argv)
{
	dummy_server ds(mihf::io_service);
	ds.init("127.0.0.1", 4000, 1);

	mihf::io_service.run();

	return 0;
}
