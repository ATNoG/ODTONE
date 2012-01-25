//==============================================================================
// Brief   : Query Book
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

#ifndef ODTONE_QUERY_BOOK__HPP
#define ODTONE_QUERY_BOOK__HPP

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>

#include <map>
#include <vector>
#include <string>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone {

struct query_entry
{
	std::string replacement;
	std::string target;
	uint16 port;
	std::string a;
	std::string aaaa;

	query_entry() : replacement(""), target(""), port(0), a(""), aaaa("") {}
};

class query_book
{
public:
	/**
	 * Add a new query entry.
	 *
	 * @param id The domain name identifier.
	 * @param query The query entry to insert.
	 */
	void add(const std::string &id, query_entry entry_info);

	/**
	 * Set the results of a SRV query.
	 *
	 * @param query The results of the SRV query.
	 */
	void set_srv_results(query_entry query);

	/**
	 * Set the results of a A/AAAA query.
	 *
	 * @param query The results of the A/AAAA query.
	 */
	void set_target_results(query_entry query);

	/**
	 * Remove an existing query entry.
	 *
	 * @param id The domain name identifier.
	 */
	void del(std::string &id);

	/**
	 * Get the query entries of a given domain.
	 *
	 * @param id The domain name identifier.
	 * @return The query entries of the given domain.
	 */
	const std::pair<std::multimap<std::string, query_entry>::iterator, std::multimap<std::string, query_entry>::iterator> get(const std::string &id);

	/**
	 * Get the domains and respective query entry which have the final (A/AAAA) information.
	 *
	 * @param id The domain name identifier.
	 * @return The domains and respective query entry which have the final (A/AAAA) information.
	 */
	std::map<std::string, std::vector<query_entry> > get_finished_queries();

private:
	/**
	 * Update an query entry.
	 *
	 * @param it Query entry iterator.
	 * @param query Updated query entry.
	 */
	void update(std::multimap<std::string, query_entry>::iterator it, query_entry query);

private:
	std::multimap<std::string, query_entry> _qbook;	/**< Query book map.	*/
	boost::mutex _mutex;							/**< Mutex.				*/
};

} /* namespace odtone */

#endif
