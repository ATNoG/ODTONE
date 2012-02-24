//==============================================================================
// Brief   : Link Response Pool
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

/**
 * Struct to store the link action parameters.
 */
struct action {
	mih::link_ac_result	link_ac_result;	/**< The link action results. */
	boost::optional<mih::link_scan_rsp_list> link_scan_rsp_list; /**< The link scan response list.	*/
};

/**
 * Struct to store pending Link SAP responses
 */
struct pending_link_response {
	mih::octet_string	user;			/**< The MIH source identifier. 	*/
	uint16				tid;			/**< The transaction identifier. 	*/
	mih::status			st;				/**< Status. 						*/
	boost::variant<	mih::link_status_rsp,
					action > response;	/**< The response parameters. 		*/
};

/**
 * This class allows the storage of Link SAP responses.
 */
class link_response_pool
{
public:
	/**
	 * Construct a Link Response Pool.
	 */
	link_response_pool();

	/**
	 * Add a new entry in the Link Responde Pool.
	 *
	 * @param user The MIH source identifier.
	 * @param tid The transaction identifier.
	 * @param link_status The link status response.
	 */
	void add(mih::octet_string user,
             uint16 tid,
	         mih::link_status_rsp link_status);

	/**
	 * Add a new entry in the Link Responde Pool.
	 *
	 * @param user MIH source identifier.
	 * @param tid The transaction identifier.
	 * @param link_scan_rsp_list The link scan response list.
	 * @param link_ac_result The link action result
	 */
	void add(mih::octet_string user,
             uint16 tid,
	         boost::optional<mih::link_scan_rsp_list> link_scan_rsp_list,
	         mih::link_ac_result link_ac_result);

	/**
	 * Remove an existing record from the Link Response Pool
	 *
	 * @param tid The transaction identifier to be removed.
	 * @param id The MIH source identifier to be removed.
	 */
	void del(const uint16 tid, const mih::octet_string id);

	/**
	 * Searchs for a record in the Link Response Pool.
	 *
	 * @param tid The transaction identifier to search for.
	 * @param id The MIH source identifier to search for.
	 * @return The Link Response record found.
	 */
	pending_link_response find(const uint16 tid, const mih::octet_string id);

	/**
	 * Check the existence of a record in the Link Response Pool.
	 *
	 * @param tid The transaction identifier to search for.
	 * @param id The MIH source identifier to search for.
	 * @return True if exists or false otherwise.
	 */
	bool check(const uint16 tid, const mih::octet_string id);

protected:
	std::list<pending_link_response> _cpool;	/**< The list of pending responses.	*/
	boost::mutex _mutex;						/**< Mutex.							*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */


#endif
