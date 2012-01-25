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

///////////////////////////////////////////////////////////////////////////////
#include "query_book.hpp"
#include "log.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone {

/**
 * Update an query entry.
 *
 * @param it Query entry iterator.
 * @param query Updated query entry.
 */
void query_book::update(std::multimap<std::string, query_entry>::iterator it, query_entry query)
{
	if(!query.target.empty()) {
		it->second.target = query.target;
	}

	if(query.port != 0) {
		it->second.port = query.port;
	}

	if(!query.a.empty()) {
		it->second.a = query.a;
	}

	if(!query.aaaa.empty()) {
		it->second.aaaa = query.aaaa;
	}
}

/**
 * Add a new query entry.
 *
 * @param id The domain name identifier.
 * @param query The query entry to insert.
 */
void query_book::add(const std::string &id, query_entry query)
{
	boost::mutex::scoped_lock lock(_mutex);

	boost::algorithm::to_lower(query.replacement);
	_qbook.insert(std::pair<std::string, query_entry>(id, query));
	ODTONE_LOG(4, "(query_book) added a new entry:\n   domain: ", id, "\n   replacement: ", query.replacement);
}

/**
 * Set the results of a SRV query.
 *
 * @param query The results of the SRV query.
 */
void query_book::set_srv_results(query_entry query)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::string id;
	for(std::multimap<std::string, query_entry>::iterator it = _qbook.begin(); it != _qbook.end(); it++) {
		boost::algorithm::to_lower(query.replacement);
		if(it->second.replacement == query.replacement) {
			update(it, query);
		}
	}
}

/**
 * Set the results of a A/AAAA query.
 *
 * @param query The results of the A/AAAA query.
 */
void query_book::set_target_results(query_entry query)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::string id;
	for(std::multimap<std::string, query_entry>::iterator it = _qbook.begin(); it != _qbook.end(); it++) {
		if(it->second.target == query.target) {
			update(it, query);
		}
	}
}

/**
 * Remove an existing query entry.
 *
 * @param id The domain name identifier.
 */
void query_book::del(std::string &id)
{
	boost::mutex::scoped_lock lock(_mutex);
	_qbook.erase(id);
}

/**
 * Get the query entries of a given domain.
 *
 * @param id The domain name identifier.
 * @return The query entries of the given domain.
 */
const std::pair<std::multimap<std::string, query_entry>::iterator, std::multimap<std::string, query_entry>::iterator> query_book::get(const std::string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	return _qbook.equal_range(id);
}

/**
 * Get the domains and respective query entry which have the final (A/AAAA) information.
 *
 * @param id The domain name identifier.
 * @return The domains and respective query entry which have the final (A/AAAA) information.
 */
std::map<std::string, std::vector<query_entry> > query_book::get_finished_queries()
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<std::string, std::vector<query_entry> > finished;

	// Get the domains that have results
	for(std::multimap<std::string, query_entry>::iterator it = _qbook.begin(); it != _qbook.end(); it++) {
		if(!it->second.a.empty() || !it->second.aaaa.empty()) {
			std::map<std::string, std::vector<query_entry> >::iterator it_domain;
			it_domain = finished.find(it->first);

			if (it_domain == finished.end()) {
				std::vector<query_entry> tmp;
				tmp.push_back(it->second);
				finished[it->first] = tmp;
			} else {
				it_domain->second.push_back(it->second);
			}
		}
	}

	// Delete the domains that does not have all results available
	for(std::multimap<std::string, query_entry>::iterator it = _qbook.begin(); it != _qbook.end(); it++) {
		if(it->second.a.empty() && it->second.aaaa.empty()) {
			std::map<std::string, std::vector<query_entry> >::iterator it_domain;
			it_domain = finished.find(it->first);

			if (it_domain != finished.end()) {
				finished.erase(it_domain);
			}
		}
	}

	return finished;
}

} /* namespace odtone */
