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

#include "dns_usr.hpp"
#include "log.hpp"

#include <odtone/net/dns/types.hpp>
#include <odtone/net/dns/frame.hpp>
#include <odtone/net/dns/message.hpp>
#include <odtone/net/dns/utils.hpp>

#include <odtone/mih/response.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/odtone.hpp>
#include <odtone/mih/tlv_types.hpp>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

namespace odtone {

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct the DNS-User.
 *
 * @param io The io_service object that DNS-User will use to
 * dispatch handlers for any asynchronous operations performed on the socket.
 * @param cfg Configuration options.
 * @param domain Default domain name.
 * @param additional Search for additional records.
 */
dns_user::dns_user(boost::asio::io_service& io,
				   const mih::config& cfg,
				   std::string domain,
				   bool additional)
	: _mihf(cfg, io, boost::bind(&dns_user::event_handler, this, _1, _2)),
	  _dns(io)
{
	_domain = domain;
	_additional = additional;
	_mihfid = mih::id("local-mihf");

	// Register with MIHF
	mih::message m;

	m << odtone::mih::indication(odtone::mih::indication::user_register);
	m.destination(odtone::mih::id("local-mihf"));

	_mihf.async_send(m, boost::bind(&dns_user::user_reg_handler, this, boost::cref(cfg), _2));
}

/**
 * Destruct the DNS-User.
 */
dns_user::~dns_user()
{
}

/**
 * Handle completion of a send operation.
 *
 * @param ec The error code.
 */
void dns_user::send_handler(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	if (ec) {
		ODTONE_LOG(1, __FUNCTION__, " error: ", ec.message());
		return;
	}
}

/**
 * User registration handler.
 *
 * @param cfg Configuration options.
 * @param ec Error Code.
 */
void dns_user::user_reg_handler(const mih::config& cfg,
                                 const boost::system::error_code& ec)
{
	if (ec) {
		ODTONE_LOG(1, __FUNCTION__, " error: ", ec.message());
		return;
	}

	ODTONE_LOG(0, "DNS-User register result: ", ec.message());
}

/**
 * Default MIH event handler.
 *
 * @param msg Received message.
 * @param ec Error code.
 */
void dns_user::event_handler(mih::message& msg,
                              const boost::system::error_code& ec)
{
	if (ec) {
		ODTONE_LOG(1, __FUNCTION__, " error: ", ec.message());
		return;
	}

	switch (msg.mid()) {
		case mih::indication::capability_discover: {
			ODTONE_LOG(0, "received a \"capability_discover\" indication");

			std::vector<mih::octet_string> domains;

			// Decode the message looking for a mos_dscv TLV
			boost::optional<mih::net_type_addr_list> capabilities_list_net_type_addr;
			boost::optional<mih::mih_evt_list>		 capabilities_event_list;
			boost::optional<mih::mih_cmd_list>		 capabilities_cmd_list;
			boost::optional<mih::iq_type_list>		 capabilities_query_type;
			boost::optional<mih::transport_list>	 capabilities_trans_list;
			boost::optional<mih::mbb_ho_supp_list>	 capabilities_mbb_ho_supp;
			boost::optional<mih::mos_dscv>			 mos_dscv;

			msg >> mih::indication(mih::indication::capability_discover)
				& mih::tlv_net_type_addr_list(capabilities_list_net_type_addr)
				& mih::tlv_event_list(capabilities_event_list)
				& mih::tlv_command_list(capabilities_cmd_list)
				& mih::tlv_query_type_list(capabilities_query_type)
				& mih::tlv_transport_option_list(capabilities_trans_list)
				& mih::tlv_mbb_ho_supp_list(capabilities_mbb_ho_supp)
				& mih::tlv_mos_dscv(mos_dscv);

			// If the message carries a mos_dscv TLV it means that it
			// is being used as a complementary discovery procedure
			// and therefore, it must search for PoS is these domains
			if(mos_dscv) {
				// MIIS
				BOOST_FOREACH(mih::mos_info mos, mos_dscv->is) {
					if(mos.id.to_string().compare("") != 0 &&
					   std::find(domains.begin(), domains.end(), mos.id.to_string()) == domains.end()) {
						domains.push_back(mos.id.to_string());
					}
				}
				// MICS
				BOOST_FOREACH(mih::mos_info mos, mos_dscv->cs) {
					if(mos.id.to_string().compare("") != 0 &&
					   std::find(domains.begin(), domains.end(), mos.id.to_string()) == domains.end()) {
						domains.push_back(mos.id.to_string());
					}
				}
				// MIES
				BOOST_FOREACH(mih::mos_info mos, mos_dscv->es) {
					if(mos.id.to_string().compare("") != 0 &&
					   std::find(domains.begin(), domains.end(), mos.id.to_string()) == domains.end()) {
						domains.push_back(mos.id.to_string());
					}
				}
			} else {
				// The message does not carry any domain in the discovery
				// trigger and therefore it searches for PoS in its
				// default domain.
				domains.push_back(_domain);
			}

			// Trigger DNS Queries
			{
				boost::mutex::scoped_lock lock(_mutex);
				_request[msg.tid()] = domains;
			}

			BOOST_FOREACH(mih::octet_string domain, domains) {
				dns::dns_callback_t callback = boost::bind(&dns_user::dns_message_handler, this, _1);
				_dns.queue(domain.c_str(), dns::DNS_NAPTR_RECORD, callback);
			}
		} break;

		default: {
			ODTONE_LOG(0, "received a unknown message. Discarding it...");
		} break;
	}
}

/**
 * DNS Message handler.
 *
 * @param cbd Callback query data.
 */
void dns_user::dns_message_handler(struct dns::callback_info *cbd)
{
	switch (cbd->error) {
	case dns::DNS_OK:
	{
		switch(cbd->query_type) {
		case dns::DNS_A_RECORD:
		{
			dns::question a = cbd->dns_message.query().back();

			BOOST_FOREACH(dns::resource_record rr, cbd->dns_message.answer()) {
				if(rr._type == dns::DNS_A_RECORD && rr._name == a._domain) {
					dns::a_record record = dns::parse_a_record(&rr._rr_data[0], 0, rr._rr_len);

					query_entry query;
					query.target = a._domain;
					query.a = record._ipv4;
					_qbook.set_target_results(query);

					// Stop searching when found the first record
					break;
				}
			}
		} break;

		case dns::DNS_AAAA_RECORD:
		{
			dns::question a = cbd->dns_message.query().back();

			BOOST_FOREACH(dns::resource_record rr, cbd->dns_message.answer()) {
				if(rr._type == dns::DNS_A_RECORD && rr._name == a._domain) {
					dns::aaaa_record record = dns::parse_aaaa_record(&rr._rr_data[0], 0, rr._rr_len);

					query_entry query;
					query.target = a._domain;
					query.aaaa = record._ipv6;
					_qbook.set_target_results(query);

					// Stop searching when found the first record
					break;
				}
			}
		} break;

		case dns::DNS_SRV_RECORD:
		{
			dns::question a = cbd->dns_message.query().back();

			BOOST_FOREACH(dns::resource_record rr, cbd->dns_message.answer()) {
				if(rr._type == dns::DNS_SRV_RECORD && rr._name == a._domain) {
					dns::srv_record record = dns::parse_srv_record(&rr._rr_data[0], 0, rr._rr_len);

					query_entry query;
					query.replacement = a._domain;
					query.port = record._port;
					query.target = record._target;
					_qbook.set_srv_results(query);

					if(!(_additional && search_record(dns::DNS_A_RECORD, query.target, cbd->dns_message.add()))) {
						dns::dns_callback_t callback = boost::bind(&dns_user::dns_message_handler, this, _1);
						_dns.queue(query.target.c_str(), dns::DNS_A_RECORD, callback);
					}

					// Stop searching when found the first record
					break;
				}
			}
		} break;

		case dns::DNS_NAPTR_RECORD:
		{
			dns::question a = cbd->dns_message.query().back();
			std::vector<std::string> request;

			BOOST_FOREACH(dns::resource_record rr, cbd->dns_message.answer()) {
				if(rr._type == dns::DNS_NAPTR_RECORD && rr._name == a._domain) {
					dns::naptr_record record = dns::parse_naptr_record(&rr._rr_data[0], 0, rr._rr_len);

					query_entry query;
					query.replacement = record._replacement;
					_qbook.add(a._domain, query);

					// Check additional
					if(!(_additional && search_record(dns::DNS_SRV_RECORD, query.replacement, cbd->dns_message.add()))) {
						// TODO: check NAPTR flags
						dns::dns_callback_t callback = boost::bind(&dns_user::dns_message_handler, this, _1);
						_dns.queue(query.replacement.c_str(), dns::DNS_SRV_RECORD, callback);
					}
				}
			}
		} break;

		default:
			ODTONE_LOG(0, "Unexpected query type: ", cbd->query_type);
			return;
			// NOTREACHED
			break;
		}

		// Check if there are complete results
		std::map<std::string, std::vector<query_entry> > results;
		results = _qbook.get_finished_queries();
		if(results.size() > 0) {
			forward_results(results);
		}

		break;
	}
	case dns::DNS_TIMEOUT: {
		ODTONE_LOG(0, "Query timeout for ", cbd->name);
		// TODO: send failure response
	} break;
	case dns::DNS_DOES_NOT_EXIST: {
		ODTONE_LOG(0, "No such address: ", cbd->name);
		// TODO: send failure response
	} break;
	case dns::DNS_ERROR:
		ODTONE_LOG(0, "System error occured");
		break;
	}
}

/**
 * Search for a specific resource records type in the given list.
 *
 * @param rr_type The resource record type to search.
 * @param str The resource record to search.
 * @param rr_list The list of resource records to search.
 */
bool dns_user::search_record(uint16 rr_type, std::string str, std::vector<dns::resource_record> rr_list)
{
	BOOST_FOREACH(dns::resource_record rr, rr_list) {
		if(rr._type == rr_type && rr._name == str) {
			switch(rr_type) {
				case dns::DNS_A_RECORD: {
					dns::a_record record = dns::parse_a_record(&rr._rr_data[0], 0, rr._rr_len);

					query_entry query;
					query.target = str;
					query.a = record._ipv4;
					_qbook.set_target_results(query);

					return true;
				} break;

				case dns::DNS_AAAA_RECORD: {
					dns::aaaa_record record = dns::parse_aaaa_record(&rr._rr_data[0], 0, rr._rr_len);

					query_entry query;
					query.target = str;
					query.aaaa = record._ipv6;
					_qbook.set_target_results(query);

					return true;
				} break;

				case dns::DNS_SRV_RECORD: {
					dns::srv_record record = dns::parse_srv_record(&rr._rr_data[0], 0, rr._rr_len);

					query_entry query;
					query.replacement = str;
					query.port = record._port;
					query.target = record._target;
					_qbook.set_srv_results(query);

					if(!(_additional && search_record(dns::DNS_A_RECORD, query.target, rr_list))) {
						return false;
					}

					return true;
				} break;
			}
		}
	}
	return false;
}

/**
 * Forward the finished queries to the MIHF.
 *
 * @param results The finished queries results.
 */
void dns_user::forward_results(std::map<std::string, std::vector<query_entry> > results)
{
	boost::mutex::scoped_lock lock(_mutex);

	// For each TID that has a pending request
	std::map<uint16, std::vector<std::string> >::iterator it_req = _request.begin();
	while(it_req != _request.end()) {
		bool			send = true;
		mih::mos_dscv	mos_list;

		// For each complete query, check if it belongs to the TID
		BOOST_FOREACH(std::string domain, it_req->second) {
			std::map<std::string, std::vector<query_entry> >::const_iterator it_results;
			it_results = results.find(domain);

			// No results
			if (it_results == results.end()) {
				send = false;
				break;
			} else {
				BOOST_FOREACH(query_entry tmp, it_results->second) {
					mih::mos_info mos;
					mos.id = mih::id(tmp.target);
					if(tmp.a.compare("") != 0) {
						mih::ip_addr ip_addr(mih::ip_addr::ipv4, tmp.a);
						mos.ip = ip_addr;
					} else if(tmp.aaaa.compare("") != 0) {
						mih::ip_addr ip_addr(mih::ip_addr::ipv6, tmp.aaaa);
						mos.ip = ip_addr;
					}
					mos.port = tmp.port;

					// Check which is the type of the MoS
					switch(tmp.replacement[4]) {
						case 'i': {
							mos_list.is.push_back(mos);
						} break;

						case 'c': {
							mos_list.cs.push_back(mos);
						} break;

						case 'e': {
							mos_list.es.push_back(mos);
						} break;

						default: {
							ODTONE_LOG(0, "Discarding unknown service type");
							return;
						}
					}
				}
			}
		}

		// If the request has all responses available, send the results to the MIHF
		if(send) {
			mih::message rsp;
			mih::status st = mih::status_success;

			rsp << mih::response(mih::response::capability_discover)
				& mih::tlv_status(st)
				& mih::tlv_mos_dscv(mos_list);

			rsp.tid(it_req->first);
			rsp.destination(mih::id(""));

			_mihf.async_send(rsp, boost::bind(&dns_user::send_handler, this, _1, _2));

			// Delete the complete request
			std::vector<std::string> tmp = it_req->second;
			_request.erase(it_req++);
			erase_request(tmp);
		} else {
			++it_req;
		}
	}
}

/**
 * Erase domains that are not needed anymore due to the completion of
 * a MIHF discovery requets.
 *
 * @param domains The list of domains to be removed.
 */
void dns_user::erase_request(std::vector<std::string> domains)
{
	for(std::map<uint16, std::vector<std::string> >::iterator it = _request.begin(); it != _request.end(); ++it) {
		BOOST_FOREACH(std::string tmp, it->second) {
			std::vector<std::string>::iterator it_str;
			it_str = std::find(domains.begin(), domains.end(), tmp);
			if(it_str != domains.end()) {
				domains.erase(it_str);
			}
		}
	}

	BOOST_FOREACH(std::string tmp, domains) {
		_qbook.del(tmp);
	}
}

} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
