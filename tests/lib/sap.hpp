//==============================================================================
// Brief   : Test SAP IO Service
// Authors : Carlos Guimarães <cguimaraes@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2012 Universidade Aveiro
// Copyright (C) 2009-2012 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#ifndef ODTONE_SAP_TEST__HPP_
#define ODTONE_SAP_TEST__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/buffer.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/config.hpp>
#include <odtone/sap/sap.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace test {

static const char* const kConf_MIH_SAP_id		= "test.id";
static const char* const kConf_Port				= "test.port";

static const char* const kConf_MIHF1_Local_Port	= "mihf.local_port";
static const char* const kConf_MIHF2_Local_Port	= "mihf2.local_port";

static const char* const kConf_File					= "conf.file";
static const char* const kConf_Receive_Buffer_Len	= "conf.recv_buff_len";


///////////////////////////////////////////////////////////////////////////////
/**
 * Test SAP I/O Service.
 *
 * This module handles the comunication between Test SAP and its local the
 * MIHF. After being initialized, and in order to run this service, it must
 * be invoked the run() method of the boost::asio::io_service associated.
 */
class test {
	typedef boost::function<void(mih::message& pm, const boost::system::error_code& ec)> default_handler;
	typedef boost::function<void(const boost::system::error_code& ec)> handler;

public:
	/**
	 * Construct a Test SAP I/O Service.
	 * The defined callback is invoked when a request message is received
	 * The signature of the callback is:
	 * void(odtone::mih::message&, const boost::system::error_code&).
	 *
	 * @param io The io_service object that Test SAP I/O Service will use to
		         dispatch handlers for any asynchronous operations performed on
		         the socket.
	 * @param cfg Configuration parameters.
	 * @param h Message processing handler.
	 */
	test(boost::asio::io_service& io, const mih::config& cfg, const default_handler& h);

	/**
	 * Destruct a Test SAP I/O Service.
	 */
	~test();

	/**
	 * Asynchronously send a MIH message to the local MIHF.
	 * After sending the message, the callback is called to report the
	 * success or failure in delivering the message to the local MIHF.
	 * This method retuns immediately.
	 *
	 * @param msg MIH message to send.
	 * @param h Response handler function.
	 */
	void async_send_mihf1(mih::message& msg, const handler& h = handler());

	/**
	 * Asynchronously send a MIH message to the local MIHF.
	 * After sending the message, the callback is called to report the
	 * success or failure in delivering the message to the local MIHF.
	 * This method retuns immediately.
	 *
	 * @param msg MIH message to send.
	 * @param h Response handler function.
	 */
	void async_send_mihf2(mih::message& msg, const handler& h = handler());

private:
	/**
	 * Received message callback. This function is executed to process the
	 * received messages. If this is a valid message, the message is
	 * dispatched to the handler defined by the user.
	 *
	 * @param buff Message byte buffer.
	 * @param rbytes Size of the message.
	 * @param ec Error code.
	 */
	void recv_handler(buffer<uint8>& buff, size_t rbytes,
					  const boost::system::error_code& ec);

	/**
	 * Sent message handler. After sending the message, this function is called to
	 * report the success or failure in delivering the message to the local MIHF.
	 *
	 * @param fm MIH message sent.
	 * @param h Message handler.
	 * @param sbytes Size of the message.
	 * @param ec Error code.
	 */
	void send_handler(mih::frame_vla& fm, const handler& h, size_t sbytes,
					  const boost::system::error_code& ec);

private:
	default_handler                 _handler;	/**< User defined handler.	*/
	boost::asio::ip::udp::socket    _sock;		/**< Link SAP socket.		*/
	boost::asio::ip::udp::endpoint  _ep1;		/**< Local MIHF 1 endpoint.	*/
	boost::asio::ip::udp::endpoint  _ep2;		/**< Local MIHF 2 endpoint.	*/
	odtone::mih::id                 _link_id;	/**< Link SAP MIH ID.		*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace test */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_SAP_TEST__HPP_ */
