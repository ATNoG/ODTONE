//==============================================================================
// Brief   : DHCP Control
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

#include <map>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread/thread.hpp>

#include <odtone/mih/types/odtone.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace odtone {

/**
 * Callback routine definition.
 */
typedef boost::function<void (mih::mos_dscv&)> dhcp_results_t;

///////////////////////////////////////////////////////////////////////////////
/**
 * This class provides an abstraction to the dhcp client used.
 */
class dhcp_control : boost::noncopyable {
public:
	/**
	 * Construct the DHCP Control.
	 *
	 * @param version The DHCP version to use.
	 * @param nic Mapping of the local network interfaces.
	 * @param app_callback The DHCP-User callback.
	 */
	dhcp_control(ushort version,
				 std::map<mih::octet_string, mih::octet_string> nic,
				 dhcp_results_t app_callback);

	/**
	 * Destruct the DHCP Control.
	 */
	~dhcp_control();

	/**
	 * Initiates a new DHCP session.
	 *
	 * @param interface The network interface name identifier associated
	 * to the new session.
	 */
	void new_session(std::string interface);

	/**
	 * Terminates an active DHCP session.
	 *
	 * @param interface The network interface name identifier associated
	 * to the session to terminate.
	 */
	void shutdown_session(std::string interface);

	/**
	 * Requests configuration settings (but not addresses).
	 *
	 * @param interface The network interface name identifier associated
	 * to the session to request.
	 */
	void request(std::string interface);

	/**
	 * Callback to process the MIH DHCP Options results .
	 *
	 * @param options A linked-list storing the MIH DHCP Options results.
	 */
	void callback(struct mih_options *options);

private:
	ushort 				_version;		/**< The DHCP version to use.		 */
	dhcp_results_t		_app_callback;	/**< DHCP-User callback.			 */
};

} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
