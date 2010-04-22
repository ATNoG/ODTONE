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

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/variant/apply_visitor.hpp>

#include <odtone/mih/types/information_elements.hpp>

using namespace odtone;
using boost::asio::ip::udp;

namespace po = boost::program_options;

static const char* const kConf_MIH_Dest = "dest";
static const char* const kConf_MIH_Port = "port";
static const char* const kConf_File     = "conf.file";

static const char* const kConf_MIH_LinkUp_indication = "indication.link_up";
static const char* const kConf_MIH_LinkDown_indication = "indication.link_down";
static const char* const kConf_MIH_LinkDetected_indication = "indication.link_detected";
static const char* const kConf_MIH_LinkGoingDown_indication = "indication.link_going_down";
static const char* const kConf_MIH_LinkHandoverImminent_indication = "indication.link_handover_iminent";
static const char* const kConf_MIH_LinkHandoverComplete_indication = "indication.link_handover_complete";

// /* dummy synchronous mih sap handler */
class handler
{
public:
  handler(const mih::octet_string &dst_ip, const mih::octet_string &dst_port)
    : _io_service(),
      _soc(_io_service, udp::endpoint(udp::v4(), 0)),
      _res(_io_service),
      _qry(udp::v4(), dst_ip, dst_port)
  {
    _it = _res.resolve(_qry);
  }

  // mih::message send_recv(mih::frame &pud)
  // {
  //   _soc.send_to(boost::asio::buffer(msg.buffer()), *_it);

  //   udp::endpoint sender_endpoint;
  //   uint8 data[1500];
  //   size_t len = _soc.receive_from(boost::asio::buffer(data, 1500),
  //                                  sender_endpoint);

  //   mih::message rsp(data, len);

  //   return rsp;
  // }

  void send(mih::message &msg)
  {
      mih::frame_vla fm;
      void *sbuff;
      size_t slen;

      msg.get_frame(fm);

      sbuff = fm.get();
      slen = fm.size();

      _soc.send_to(boost::asio::buffer(sbuff, slen), *_it);
  }

private:
  boost::asio::io_service _io_service;
  udp::socket             _soc;
  udp::resolver           _res;
  udp::resolver::query    _qry;
  udp::resolver::iterator _it;

};


void send_link_up_indication(handler &sap, const char *dst)
{
  mih::message		p;
  mih::link_tuple_id	li;
  mih::mac_addr			mac;

  mac.address("00:11:22:33:44:55");
  li.type = mih::link_type_802_11;
  li.addr = mac;

  p << mih::indication(mih::indication::link_up)
	& mih::tlv_link_identifier(li);

  p.source(mih::id("link"));
  p.destination(mih::id(dst));

  sap.send(p);
}


void send_link_down_indication(handler &sap, const char *dst)
{
  mih::message		p;
  mih::link_tuple_id	li;
  mih::mac_addr			mac;

  mac.address("00:11:22:33:44:55");
  li.type = mih::link_type_802_11;
  li.addr = mac;

  p << mih::indication(mih::indication::link_down)
	  & mih::tlv_link_identifier(li);

  p.source(mih::id("link"));
  p.destination(mih::id(dst));

  sap.send(p);
}

void send_link_detected_indication(handler &sap, const char *dst)
{
  mih::message		p;
  mih::message			msg;

  mih::link_det_info_list		list;
  mih::link_det_info			link;
  mih::mac_addr					mac;

  mac.address("00:11:22:33:44:55");

  link.id.addr = mac;
  link.id.type = mih::link_type_802_11;

  list.push_back(link);

  p << mih::indication(mih::indication::link_detected)
	  & mih::tlv_link_det_info_list(list);

  p.source(mih::id("link"));
  p.destination(mih::id(dst));

  sap.send(p);
}

void send_link_going_down_indication(handler &sap, const char *dst)
{
	mih::message				p;
	mih::message				msg;
	mih::link_tuple_id		li;
	mih::mac_addr				mac;

	mac.address("00:11:22:33:44:55");
	li.type = mih::link_type_802_11;
	li.addr = mac;

	p << mih::indication(mih::indication::link_going_down)
		& mih::tlv_link_identifier(li);

	p.source(mih::id("link"));
	p.destination(mih::id(dst));

	sap.send(p);
}

void send_link_handover_imminent_indication(handler &sap, const char *dst)
{
	mih::message				p;
	mih::message				msg;

	mih::link_tuple_id oli;
	mih::link_tuple_id nli;
	mih::mac_addr      mac;

	mac.address("00:11:22:33:44:55");
	oli.type = mih::link_type_802_11;
	oli.addr = mac;

	mac.address("66:77:88:99:00:11");
	nli.type = mih::link_type_ethernet;
	nli.addr = mac;

	p << mih::indication(mih::indication::link_handover_imminent)
		& mih::tlv_link_identifier(oli)
		& mih::tlv_new_link_identifier(nli);

	p.source(mih::id("link"));
	p.destination(mih::id(dst));

	sap.send(p);
}

void send_link_handover_complete_indication(handler &sap, const char *dst)
{
	mih::message				p;
	mih::message				msg;

	mih::link_tuple_id oli;
	mih::link_tuple_id nli;
	mih::mac_addr      mac;

	mac.address("00:11:22:33:44:55");
	oli.type = mih::link_type_802_11;
	oli.addr = mac;

	mac.address("66:77:88:99:00:11");
	nli.type = mih::link_type_ethernet;
	nli.addr = mac;

	p << mih::indication(mih::indication::link_handover_complete)
		& mih::tlv_link_identifier(oli)
		& mih::tlv_new_link_identifier(nli);

	p.source(mih::id("link"));
	p.destination(mih::id(dst));

	sap.send(p);
}

void send_get_information_request(handler &sap, const char *dst)
{
	mih::message		p;

	mih::ie_container_poa					poa;
	mih::ie_container_network				net;
	mih::ie_container_list_of_networks		list;

	// ie_container_poa
	//
	mih::ie_poa_link_addr		poa_la;
	mih::link_addr				la;
	mih::mac_addr				mac;
	mih::ie_poa_location		poa_loc;
	mih::cell_id				poa_cell;
	mih::ch_range				range;

	mac.address("00:11:22:33:44:55");
	la	   = mac;
	poa_la = la;

	poa_cell = 10;				// random value
	poa_loc	 = poa_cell;

	range.high = 2;
	range.low  = 1;

	poa.poa_link_addr	  = poa_la;
	poa.poa_location	  = poa_loc;
	poa.poa_channel_range = range;
	//

	// ie_container_network
	//
	mih::link_type				lt;
	mih::ie_network_type		nt;
	mih::ie_operator_id		opid;

	lt		= mih::link_type_802_11;
	nt.link = lt;

	opid.opname = "name";
	opid.opnamespace = mih::op_namespace_gsm_umts;

	net.network_type = nt;
	net.operator_id = opid;

	net.poas.push_back(poa);
	//

	// ie_container_list_of_networks
	//
	list.push_back(net);
	//

	//
	mih::ir_bin_data			bin_data;
	mih::ir_bin_data_list		bin_data_list;

	bin_data.output() & mih::tlv_ie_container_list_of_networks(list);
	bin_data_list.push_back(bin_data);
	//

	p << mih::response(mih::response::get_information)
		& mih::tlv_info_resp_bin_data_list(bin_data_list);

	p.uir(true);
	p.source(mih::id("user"));
	p.destination(mih::id(dst));

	sap.send(p);
}


int main(int argc, char **argv)
{

	po::options_description desc(mih::octet_string("Client Configuration Options"));

	desc.add_options()
		("help", "Display available Options")
		(kConf_File, po::value<std::string>()->default_value("client.conf"), "Configuration File")
		(kConf_MIH_Port, po::value<mih::octet_string>()->default_value("1025"), "MIHFs port")
		(kConf_MIH_Dest, po::value<mih::octet_string>()->default_value("local-mihf"), "MIH Destination identifier")
		(kConf_MIH_LinkUp_indication, "Send a MIH_LinkUp.indication to MIHF")
		(kConf_MIH_LinkDown_indication, "Send a MIH_LinkDown.indication to MIHF")
		(kConf_MIH_LinkDetected_indication, "Send a MIH_LinkDetected.indication to MIHF")
		(kConf_MIH_LinkGoingDown_indication, "Send a MIH_LinkGoingDown.indication to MIHF")
		(kConf_MIH_LinkHandoverImminent_indication, "Send a MIH_LinkHandoverImminent.indicatio to MIHF")
		(kConf_MIH_LinkHandoverComplete_indication, "Send a MIH_LinkHandoverComplete.indication to MIHF")
		 ;
	mih::config cfg(desc);

	cfg.parse(argc, argv, kConf_File);

	if (cfg.help() || argc == 1) {
		std::cerr << desc << std::endl;
		return EXIT_SUCCESS;
	}


	mih::octet_string dest = cfg.get<mih::octet_string>(kConf_MIH_Dest);
	mih::octet_string port = cfg.get<mih::octet_string>(kConf_MIH_Port);

	handler sap("127.0.0.1", port.c_str());

	if (cfg.count(kConf_MIH_LinkUp_indication)) {
	    std::cout << "sent link up indication to mihf" << std::endl;
	    send_link_up_indication(sap, dest.c_str());
	}

	if (cfg.count(kConf_MIH_LinkDown_indication)) {
		std::cout << "sent link down indication to mihf" << std::endl;
		send_link_down_indication(sap, dest.c_str());
	}

	if (cfg.count(kConf_MIH_LinkDetected_indication)) {
		std::cout << "sent link detected indication to mihf" << std::endl;
		send_link_detected_indication(sap, dest.c_str());
	}

	if (cfg.count(kConf_MIH_LinkGoingDown_indication)) {
		std::cout << "sent link going down indication to mihf" << std::endl;
		send_link_going_down_indication(sap, argv[1]);
	}

	if (cfg.count(kConf_MIH_LinkHandoverImminent_indication)) {
		std::cout << "sent link handover imminent to mihf" << std::endl;
		send_link_handover_imminent_indication(sap, argv[1]);
	}

	if (cfg.count(kConf_MIH_LinkHandoverComplete_indication)) {
		std::cout << "sent link handover complete to mihf" << std::endl;
		send_link_handover_complete_indication(sap, argv[1]);
	}

  // std::cout << "sent get information request to mihf" << std::endl;
  // send_get_information_request(sap, argv[1]);

	return 0;
}
