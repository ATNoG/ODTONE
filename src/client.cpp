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
#include <odtone/mih/types/information.hpp>
#include <odtone/mih/types/capabilities.hpp>
#include <odtone/mih/types/capabilities.hpp>
#include <odtone/mih/config.hpp>
#include <odtone/mih/tlv.hpp>
#include <odtone/mih/tlv_types.hpp>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <boost/asio.hpp>
#include <boost/variant/apply_visitor.hpp>

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


int main(int argc, char **argv)
{

  if (argc != 3)
    {
      std::cout << "Usage: client mihfid port\n";
      return -1;
    }

  handler sap("127.0.0.1", argv[2]);

  std::cout << "sent link up indication to mihf" << std::endl;
  send_link_up_indication(sap, argv[1]);

  std::cout << "sent link down indication to mihf" << std::endl;
  send_link_down_indication(sap, argv[1]);

  std::cout << "sent link detected indication to mihf" << std::endl;
  send_link_detected_indication(sap, argv[1]);

  std::cout << "sent link going down indication to mihf" << std::endl;
  send_link_going_down_indication(sap, argv[1]);

  std::cout << "sent link handover imminent to mihf" << std::endl;
  send_link_handover_imminent_indication(sap, argv[1]);

  std::cout << "sent link handover complete to mihf" << std::endl;
  send_link_handover_complete_indication(sap, argv[1]);

  return 0;
}
