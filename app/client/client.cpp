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

#include <odtone/miis/information_containers.hpp>

using namespace odtone;
using boost::asio::ip::udp;

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

void send_rdf_get_information_request(handler &sap, const char *dst)
{
	mih::message		p;

	mih::iq_rdf_data query;
	mih::iq_rdf_data_list query_list;

	p.source(mih::id("user"));
	p.destination(mih::id(dst));

	// Below is an example of IS query. The MIH client queries
	// available networks for a specific location identified by
	// cellular cell ID “800”. The client requires the server to
	// return the network_id and link_type of all available
	// networks for this location.
	query._data.assign("PREFIX mihbasic: <http://www.mih.org/2006/09/rdf-basic-schema#> \
	PREFIX xsd: <http://www.w3.org/2001/XMLSchema#>			\
	SELECT ?network_id ?link_type					\
	WHERE {								\
	  ?network mihbasic:ie_network_id ?network_id .			\
		  ?network mihbasic:ie_network_type ?network_type .	\
		  ?network_type mihbasic:link_type ?link_type .		\
		  ?network mihbasic:ie_container_poa ?poa .		\
		  ?poa mihbasic:ie_poa_location ?x1 .			\
		  ?x1 mihbasic:location_cell_id \"1\" .		\
	}");

	// other queries can be added in the request
	query_list.push_back(query);

	// create and send a Get_Information request
	p << mih::request(mih::request::get_information)
		& mih::tlv_info_query_rdf_data_list(query_list);

	sap.send(p);
}

//
// example on how to create a TLV binary encoded
// Get_Information.response
//
void send_bin_get_information_response(handler &sap, const char *dst)
{
	mih::message		p;

	miis::ie_container_poa					poa;
	miis::ie_container_network				net;
	miis::ie_container_list_of_networks		list;

	// ie_container_poa
	//
	miis::ie_poa_link_addr		poa_la;
	mih::link_addr				la;
	mih::mac_addr				mac;
	miis::ie_poa_location		poa_loc;
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
	miis::ie_network_type		nt;
	miis::ie_operator_id		opid;

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

	bin_data.output() & miis::tlv_ie_container_list_of_networks(list);
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

  if (argc != 3)
    {
      std::cout << "Usage: client mihfid port\n";
      return -1;
    }

  handler sap("127.0.0.1", argv[2]);

  // std::cout << "sent link up indication to mihf" << std::endl;
  // send_link_up_indication(sap, argv[1]);

  // std::cout << "sent link down indication to mihf" << std::endl;
  // send_link_down_indication(sap, argv[1]);

  // std::cout << "sent link detected indication to mihf" << std::endl;
  // send_link_detected_indication(sap, argv[1]);

  // std::cout << "sent link going down indication to mihf" << std::endl;
  // send_link_going_down_indication(sap, argv[1]);

  // std::cout << "sent link handover imminent to mihf" << std::endl;
  // send_link_handover_imminent_indication(sap, argv[1]);

  // std::cout << "sent link handover complete to mihf" << std::endl;
  // send_link_handover_complete_indication(sap, argv[1]);

  std::cout << "sent get information request to mihf" << std::endl;
  send_rdf_get_information_request(sap, argv[1]);

  return 0;
}
