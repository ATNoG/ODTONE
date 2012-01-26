//==============================================================================
// Brief   : DHCP User
// Authors : Carlos Guimaraes <cguimaraes@av.it.pt>
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

#include "dhcp_control.hpp"

#include <map>
#include <odtone/sap/user.hpp>
#include <boost/optional.hpp>


///////////////////////////////////////////////////////////////////////////////

namespace po = boost::program_options;

namespace odtone {

///////////////////////////////////////////////////////////////////////////////
/**
 * This class provides an implementation of an DHCP-User.
 */
class dhcp_user : boost::noncopyable {
public:
	/**
	 * Construct the DHCP-User.
	 *
	 * @param io The io_service object that DHCP-User will use to
	 * dispatch handlers for any asynchronous operations performed on the socket.
	 * @param cfg Configuration options.
	 * @param nic Mapping of the local network interfaces.
	 * @param version The DHCP version that the DHCP-User will manage.
	 */
	dhcp_user(boost::asio::io_service& io,
			  const odtone::mih::config& cfg,
	          std::map<std::string, std::string> nic,
	          ushort version);

	/**
	 * Destruct the DHCP-User.
	 */
	~dhcp_user();

protected:
	/**
	 * Default MIH event handler.
	 *
	 * @param msg Received message.
	 * @param ec Error code.
	 */
	void event_handler(mih::message& msg,
	                   const boost::system::error_code& ec);

	/**
	 * User registration handler.
	 *
	 * @param cfg Configuration options.
	 * @param ec Error Code.
	 */
	void user_reg_handler(const odtone::mih::config& cfg,
	                      const boost::system::error_code& ec);

	/**
	 * Capability Discover handler.
	 *
	 * @param msg Received message.
	 * @param ec Error Code.
	 */
	void cap_disc_handler(mih::message& msg,
	                      const boost::system::error_code& ec);

	/**
	 * Event subscribe handler.
	 *
	 * @param msg Received message.
	 * @param ec Error Code.
	 */
	void subscription_handler(mih::message& msg,
	                          const boost::system::error_code& ec);

	/**
	 * DHCP IEEE 802.21 results handler.
	 *
	 * @param pos_list List of discovered PoS.
	 */
	void dhcp_results_handler(mih::mos_dscv &pos_list);

	/**
	 * Find and retrieve the network interface name identifier associated
	 * with a given link address.
	 *
	 * @param addr The link address of the interface to find.
	 * @return The network interface name identifier.
	 */
	boost::optional<std::string> find_nic(mih::link_addr addr);
private:
	odtone::sap::user _mihf;
	odtone::mih::id   _mihfid;

	boost::mutex _mutex;
	uint16 tid;
	std::vector<std::string> _sessions;
	std::map<std::string, std::string> _nic;	// map<link address, interface name>
	std::vector<uint16>	_requests;		/**< Transaction ID of the requests. */

	dhcp_control _control;
};

} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
