//==============================================================================
// Brief   : DNS User
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

#ifndef ODTONE_DNS_USR__HPP
#define ODTONE_DNS_USR__HPP
///////////////////////////////////////////////////////////////////////////////

#include "query_book.hpp"

#include <odtone/sap/user.hpp>
#include <odtone/net/dns/resolver.hpp>
#include <odtone/net/dns/types.hpp>

#include <map>

///////////////////////////////////////////////////////////////////////////////

namespace po = boost::program_options;

namespace odtone {

///////////////////////////////////////////////////////////////////////////////
/**
 * This class provides an implementation of an DNS-User.
 */
class dns_user : boost::noncopyable {
public:
	/**
	 * Construct the DNS-User.
	 *
	 * @param io The io_service object that DNS-User will use to
	 * dispatch handlers for any asynchronous operations performed on the socket.
	 * @param cfg Configuration options.
	 * @param domain Default domain name.
	 * @param additional Search for additional records.
	 */
	dns_user(boost::asio::io_service& io,
			 const mih::config& cfg,
			 std::string domain,
			 bool additional);

	/**
	 * Destruct the DNS-User.
	 */
	~dns_user();

protected:

	/**
	 * Handle completion of a send operation.
	 *
	 * @param ec The error code.
	 */
	void send_handler(odtone::mih::message& msg, const boost::system::error_code& ec);

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
	 * @param msg Received message.
	 * @param ec Error Code.
	 */
	void user_reg_handler(const mih::config& cfg,
						  const boost::system::error_code& ec);

	/**
	 * DNS Message handler.
	 *
	 * @param cbd Callback query data.
	 */
	void dns_message_handler(struct dns::callback_info *cbd);

	/**
	 * Search for a specific resource records type in the given list.
	 *
	 * @param rr_type The resource record type to search.
	 * @param str The resource record to search.
	 * @param rr_list The list of resource records to search.
	 */
	bool search_record(uint16 rr_type, std::string str,
						   std::vector<dns::resource_record> rr_list);

	/**
	 * Forward the finished queries to the MIHF.
	 *
	 * @param results The finished queries results.
	 */
	void forward_results(std::map<std::string, std::vector<query_entry> > results);

	/**
	 * Erase domains that are not needed anymore due to the completion of
	 * a MIHF discovery requets.
	 *
	 * @param domains The list of domains to be removed.
	 */
	void erase_request(std::vector<std::string> domains);

private:
	sap::user		_mihf;			/**< User SAP helper.					*/
	mih::id			_mihfid;		/**< MIHF destination ID.				*/
	std::string		_domain;		/**< Default domain name.				*/
	bool			_additional;	/**< Search for additional records?.	*/
	dns::resolver	_dns;			/**< DNS resolver descriptor.			*/
	query_book		_qbook;			/**< Query book.						*/

	/**
	 *  Map between the TID and the requested domains.
	 */
	std::map<uint16, std::vector<std::string> >	_request;
	boost::mutex _mutex;	/**< Mutex.	*/
};

} /* namespace odtone */

#endif

// EOF ////////////////////////////////////////////////////////////////////////
