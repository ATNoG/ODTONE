//=============================================================================
// Brief   : DNS Resolver
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

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <iostream>

#ifndef _WIN32
	#include <netinet/in.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/select.h>
#endif /* _WIN32 */

#include <odtone/bind_rv.hpp>
#include <odtone/net/dns/resolver.hpp>
#include <odtone/net/dns/message.hpp>
#include <odtone/net/dns/frame.hpp>
#include <odtone/net/dns/utils.hpp>

#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace dns {

///////////////////////////////////////////////////////////////////////////////
/**
 * Find the IP address of the DNS server.
 *
 * @return The IP address of the DNS server.
 */
static std::string get_dns_ip()
{
	struct sockaddr_in sa;

#ifndef _WIN32
	FILE	*fp;
	char	line[512];
	int	a, b, c, d;

	if ((fp = fopen("/etc/resolv.conf", "r")) == NULL) {
		return "";
	} else {
		for ( ; fgets(line, sizeof(line), fp) != NULL; ) {
			if (sscanf(line, "nameserver %d.%d.%d.%d",
			   &a, &b, &c, &d) == 4) {
				sa.sin_addr.s_addr =
				    htonl(a << 24 | b << 16 | c << 8 | d);
				break;
			}
		}
		(void) fclose(fp);
	}
#else
	// Not implemented yet
	return "";
#endif /* _WIN32 */

	std::string ip(inet_ntoa(sa.sin_addr));
	return ip;
}
///////////////////////////////////////////////////////////////////////////////

/**
 * Construct the DNS resolver.
 *
 * @param io The io_service object that the resolver will use to
 * dispatch handlers for any asynchronous operations performed on
 * the socket.
 */
resolver::resolver(boost::asio::io_service& io)
	: _sock(io),
	  _timer(io, boost::posix_time::seconds(1))
{
	_sock.open(boost::asio::ip::udp::v6());
	_sock.set_option(boost::asio::socket_base::receive_buffer_size(DNS_PACKET_LEN));
	_sock.set_option(boost::asio::socket_base::reuse_address(true));

	// start timer
	_timer.expires_from_now(boost::posix_time::seconds(1));
	_timer.async_wait(boost::bind(&resolver::cleanup, this));
}

/**
 * Destruct the DNS resolver.
 */
resolver::~resolver()
{
	boost::mutex::scoped_lock lock(_mutex);

	_active.clear();
	_cached.clear();
}

/**
 * Queries the DNS server.
 *
 * @param host The query to be performed.
 * @param type The query type.
 * @param app_callback The application callback function.
 */
void resolver::queue(std::string host, enum dns_query_type type, dns_callback_t app_callback)
{
	// Get the DNS Server IP address
	std::string ip = get_dns_ip();
	if (ip.compare("") == 0)
		return;

	dns_queue(&host, host, type, ip, app_callback);
}

/**
 * Handle the reception of an asynchronous message.
 *
 * @param buff The input message bytes.
 * @param rbytes The number of bytes of the input message.
 */
void resolver::receive_handler(buffer<uint8>& buff, size_t rbytes, const boost::system::error_code& ec)
{
	const frame *pud = frame::cast(buff.get(), rbytes);

	if(!pud)
		return;

	message dns_message(*pud);

	if (dns_message.nquery() < 1)
		return;

	/* Check if there is an active quuery */
	boost::optional<struct query> q;
	q = find_active_query(dns_message.tid());
	if (!q.is_initialized())
		return;

	// Associate the DNS message with the query
	q->dns_message = dns_message;

	/* Received 0 answers */
	if (dns_message.nanswer() == 0) {
		callback(q.get(), DNS_DOES_NOT_EXIST);
		return;
	}

	BOOST_FOREACH(struct resource_record tmp, dns_message.answer()) {
		if (tmp._type == q->qtype) {
			callback(q.get(), DNS_OK);
			break;
		}
	}
}

/**
 * Handle of sending procedure.
 *
 * @param ec The error code.
 * @param bytes_transferred Bytes transferred.
 */
void resolver::send_handler(const boost::system::error_code& ec,
							std::size_t bytes_transferred) {
	if (ec)
		return;
}

/**
 * Find out if a given query is active.
 *
 * @param query The query information.
 * @param status The query status.
 */
void resolver::callback(struct query query, enum dns_status status)
{
	struct callback_info cb_info;

	cb_info.context		= query.ctx;
	cb_info.name		= query.name;
	cb_info.query_type	= (enum dns_query_type) query.qtype;
	cb_info.error		= status;
	cb_info.dns_message = query.dns_message;
	query.callback(&cb_info);

	boost::mutex::scoped_lock lock(_mutex);

	/* Cache the query */
	_cached.push_back(query);

	/* Remove from active queries */
	_active.remove(query);
}

/**
 * Queue the resolution.
 *
 * @param ctx The query context.
 * @param name The query to be performed.
 * @param qtype The query type.
 * @param dns_ip The DNS server IP address.
 * @param app_callback The application callback function.
 */
void resolver::dns_queue(void *ctx, std::string name,
		enum dns_query_type qtype, std::string dns_ip, dns_callback_t app_callback)
{
	time_t now = time(NULL);

	/* Search the cache first */
	boost::optional<struct query> cached_query;
	cached_query = find_cached_query(name, qtype);
	if (cached_query.is_initialized()) {
		cached_query->ctx = ctx;
		callback(cached_query.get(), DNS_OK);
		return;
	}

	/* DNS message */
	message dns_message;
	dns_message.tid(++(_tid));
	dns_message.qr(false);
	dns_message.opcode(0);
	dns_message.aa(false);
	dns_message.tc(false);
	dns_message.rd(true);
	dns_message.ra(false);
	dns_message.z(false);
	dns_message.rcode(false);

	// Set DNS query
	question query(name, qtype, 1);
	std::vector<question> query_list;
	query_list.push_back(query);
	dns_message.query(query_list);

	boost::asio::ip::udp::endpoint server(boost::asio::ip::address::from_string(dns_ip), 53);

	// Listen messages from the DNS server
	buffer<uint8> buff;
	void* rbuff;
	size_t rlen;

	buff = buffer<uint8>(1500);

	rbuff = buff.get();
	rlen = buff.size();

	_sock.async_receive_from(boost::asio::buffer(rbuff, rlen),
				 server,
				 boost::bind(&resolver::receive_handler,
					this,
					bind_rv(buff),
					boost::asio::placeholders::bytes_transferred,
					boost::asio::placeholders::error));

	// Send DNS message
	frame_vla fm;
	void *sbuff;
	size_t slen;

	dns_message.get_frame(fm);
	sbuff = fm.get();
	slen = fm.size();

	_sock.async_send_to(boost::asio::buffer(sbuff, slen),
						server,
						boost::bind(&resolver::send_handler, this, _1, _2));

	// Store query as active
	struct query query_info;
	query_info.ctx		= ctx;
	boost::algorithm::to_lower(name);
	query_info.name = name;
	query_info.qtype	= qtype;
	query_info.tid		= dns_message.tid();
	query_info.callback	= app_callback;
	query_info.expire	= now + DNS_QUERY_TIMEOUT;

	boost::mutex::scoped_lock lock(_mutex);
	_active.push_back(query_info);
}

/**
 * Cancel the query.
 *
 * @param context The query context.
 */
void resolver::dns_cancel(const void *context)
{
	boost::mutex::scoped_lock lock(_mutex);

	BOOST_FOREACH(struct query tmp, _active) {
		if (tmp.ctx == context) {
			_active.remove(tmp);
			break;
		}
	}
}

/**
 * Find a given query in cache.
 *
 * @param name The domain name.
 * @param qtype The query type.
 * @return The query information if found.
 */
boost::optional<struct query> resolver::find_cached_query(std::string name, enum dns_query_type qtype)
{
	boost::mutex::scoped_lock lock(_mutex);
	boost::optional<struct query> query;

	BOOST_FOREACH(struct query tmp, _cached) {
		if(tmp.qtype == qtype && name.compare(tmp.name) == 0) {
			query = tmp;
			break;
		}
	}

	return query;
}

/**
 * Find out if a given query is active.
 *
 * @param tid The transaction identifier.
 * @return The query information if found.
 */
boost::optional<struct query> resolver::find_active_query(uint16 tid)
{
	boost::mutex::scoped_lock lock(_mutex);
	boost::optional<struct query> query;

	BOOST_FOREACH(struct query tmp, _active) {
		if (tid == tmp.tid) {
			query = tmp;
			break;
		}
	}

	return query;
}

/**
 * Cleanup expired queries.
 */
void resolver::cleanup()
{
	_timer.expires_from_now(boost::posix_time::seconds(1));
	_timer.async_wait(boost::bind(&resolver::cleanup, this));

	time_t now = time(NULL);

	boost::mutex::scoped_lock lock(_mutex);

	/* Cleanup expired active queries */
	BOOST_FOREACH(struct query tmp, _active) {
		if (tmp.expire < now) {
			callback(tmp, DNS_TIMEOUT);
		}
	}

	/* Cleanup cached queries */
	BOOST_FOREACH(struct query tmp, _cached) {
		if (tmp.expire < now) {
			_cached.remove(tmp);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
} /* namespace dns */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
