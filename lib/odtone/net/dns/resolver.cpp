//=============================================================================
// Brief   : DNS Resolver
// Authors : Carlos Guimaraes <cguimaraes@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
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

#ifdef _WIN32
	#pragma comment(lib,"ws2_32")
	#pragma comment(lib,"advapi32")
	#include <winsock.h>
	typedef	int		socklen_t;
	typedef	unsigned char	uint8_t;
	typedef	unsigned short	uint16_t;
	typedef	unsigned int	uint32_t;
#else
	#define	closesocket(x)	close(x)
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <netinet/in.h>
	#include <unistd.h>
#endif /* _WIN32 */

#include <odtone/net/dns/resolver.hpp>
#include <odtone/net/dns/message.hpp>
#include <odtone/net/dns/frame.hpp>
#include <odtone/net/dns/utils.hpp>

#include <boost/thread.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace dns {

///////////////////////////////////////////////////////////////////////////////
/**
 * Put the given file descriptor in non-blocking mode.
 *
 * @param fd The file descriptor to put in non-blocking mode.
 * @return 0 if success or -1 otherwise.
 */
static int nonblock(int fd)
{
#ifdef	_WIN32
	unsigned long	on = 1;
	return (ioctlsocket(fd, FIONBIO, &on));
#else
	int	flags;

	flags = fcntl(fd, F_GETFL, 0);

	return (fcntl(fd, F_SETFL, flags | O_NONBLOCK));
#endif /* _WIN32 */
}

/**
 * Find what DNS server to use.
 *
 * @param dns The resolver descriptor.
 * @return 0 if OK, -1 if error.
 */
static int getdnsip(struct sockaddr_in &sa)
{
	int	ret = 0;

#ifdef _WIN32
	int	i;
	LONG	err;
	HKEY	hKey, hSub;
	char	subkey[512], dhcpns[512], ns[512], value[128], *key =
	"SYSTEM\\ControlSet001\\Services\\Tcpip\\Parameters\\Interfaces";

	if ((err = RegOpenKey(HKEY_LOCAL_MACHINE,
	    key, &hKey)) != ERROR_SUCCESS) {
		fprintf(stderr, "cannot open reg key %s: %d\n", key, err);
		ret--;
	} else {
		for (ret--, i = 0; RegEnumKey(hKey, i, subkey,
		    sizeof(subkey)) == ERROR_SUCCESS; i++) {
			DWORD type, len = sizeof(value);
			if (RegOpenKey(hKey, subkey, &hSub) == ERROR_SUCCESS &&
			    (RegQueryValueEx(hSub, "NameServer", 0,
			    &type, value, &len) == ERROR_SUCCESS ||
			    RegQueryValueEx(hSub, "DhcpNameServer", 0,
			    &type, value, &len) == ERROR_SUCCESS)) {
				sa.sin_addr.s_addr = inet_addr(value);
				ret++;
				RegCloseKey(hSub);
				break;
			}
		}
		RegCloseKey(hKey);
	}
#else
	FILE	*fp;
	char	line[512];
	int	a, b, c, d;

	if ((fp = fopen("/etc/resolv.conf", "r")) == NULL) {
		ret--;
	} else {
		for (ret--; fgets(line, sizeof(line), fp) != NULL; ) {
			if (sscanf(line, "nameserver %d.%d.%d.%d",
			   &a, &b, &c, &d) == 4) {
				sa.sin_addr.s_addr =
				    htonl(a << 24 | b << 16 | c << 8 | d);
				ret++;
				break;
			}
		}
		(void) fclose(fp);
	}
#endif /* _WIN32 */

	return (ret);
}
///////////////////////////////////////////////////////////////////////////////

/**
 * Construct the DNS resolver.
 */
resolver::resolver()
{
	// Initialize the resolver descriptor
	int	rcvbufsiz = 128 * 1024;

#ifdef _WIN32
	{ WSADATA data; WSAStartup(MAKEWORD(2,2), &data); }
#endif /* _WIN32 */

	if ((sock = socket(PF_INET, SOCK_DGRAM, 17)) == -1)
		return;
	else if (nonblock(sock) != 0)
		return;

	sa.sin_family = AF_INET;
	sa.sin_port = htons(53);

	/* Increase socket's receive buffer */
	(void) setsockopt(sock, SOL_SOCKET, SO_RCVBUF,
	    (char *) &rcvbufsiz, sizeof(rcvbufsiz));
}

/**
 * Destruct the DNS resolver.
 */
resolver::~resolver()
{
	if (sock != -1)
	(void) closesocket(sock);

	active.clear();
	cached.clear();
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
	fd_set set;
	struct timeval tv = {0, 100000};

	// Get the DNS Server IP address
	if (getdnsip(sa) != 0)
		return;

	dns_queue(&host, host, type, app_callback);

	FD_ZERO(&set);
	FD_SET(sock, &set);

	if (select(sock + 1, &set, NULL, NULL, &tv) == 1)
		dns_poll();
}

/**
 * Handle the reception of an asynchronous message.
 *
 * @param buff The input message bytes.
 * @param rbytes The number of bytes of the input message.
 */
void resolver::receive_handler(const unsigned char *buff, int rbytes)
{
	const frame *pud = frame::cast(buff, rbytes);

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
 * Find out if a given query is active.
 *
 * @param query The query information.
 * @param status The query status.
 */
void resolver::callback(struct query query, enum dns_status status)
{
	struct callback_info cbd;

	cbd.context	= query.ctx;
	cbd.query_type	= (enum dns_query_type) query.qtype;
	cbd.error	= status;
	cbd.name	= query.name;
	cbd.dns_message = query.dns_message;
	query.callback(&cbd);

	/* Cache the query */
	cached.push_back(query);
}

/**
 * Queue the resolution.
 *
 * @param ctx Query context.
 * @param name Query to be performed.
 * @param qtype Query type.
 * @param app_callback The application callback function.
 */
void resolver::dns_queue(void *ctx, std::string name,
		enum dns_query_type qtype, dns_callback_t app_callback)
{
	time_t				now = time(NULL);
	struct callback_info	cbd;

	/* Search the cache first */
	boost::optional<struct query> cached_query;
	cached_query = find_cached_query(qtype, name);
	if (cached_query.is_initialized()) {
		cached_query->ctx = ctx;
		callback(cached_query.get(), DNS_OK);
		if (cached_query->expire < now) {
			cached.remove(cached_query.get());
		}
		return;
	}

	/* DNS message */
	message dns_message;
	dns_message.tid(++(tid));
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

	frame_vla fm;
	void *sbuff;
	size_t slen;

	dns_message.get_frame(fm);
	sbuff = fm.get();
	slen = fm.size();

	if (sendto(sock, sbuff, slen, 0,
	    (struct sockaddr *) &sa, sizeof(sa)) < 0) {
		(void) memset(&cbd, 0, sizeof(cbd));
		cbd.error = DNS_ERROR;
		app_callback(&cbd);
		return;
	}

	// Store query as active
	struct query query_info;
	query_info.ctx	= ctx;
	query_info.qtype	= (uint16_t) qtype;
	query_info.tid	= dns_message.tid();
	query_info.callback	= app_callback;
	query_info.expire	= now + DNS_QUERY_TIMEOUT;
	boost::algorithm::to_lower(name);
	query_info.name = name;

	active.push_back(query_info);
}

/**
 * Check if there are pending messages.
 */
void resolver::dns_poll()
{
	struct sockaddr_in	sa;
	socklen_t			len = sizeof(sa);
	int					n;
	unsigned char		pkt[DNS_PACKET_LEN];
	time_t				now;

	now = time(NULL);

	/* Check our socket for new stuff */
	while ((n = recvfrom(sock, pkt, sizeof(pkt), 0,
	    (struct sockaddr *) &sa, &len)) > 0 &&
	    n > (int) sizeof(struct header)) {
		receive_handler(pkt, n);
	}

	/* Cleanup expired active queries */
	BOOST_FOREACH(struct query tmp, active) {
		if (tmp.expire < now) {
			callback(tmp, DNS_TIMEOUT);
			active.remove(tmp);
		}
	}

	/* Cleanup cached queries */
	BOOST_FOREACH(struct query tmp, cached) {
		if (tmp.expire < now) {
			cached.remove(tmp);
		}
	}
}

/**
 * Cancel the query.
 *
 * @param context The query context.
 */
void resolver::dns_cancel(const void *context)
{
	BOOST_FOREACH(struct query tmp, active) {
		if (tmp.ctx == context) {
			active.remove(tmp);
			break;
		}
	}
}

/**
 * Find a given query in cache.
 *
 * @param qtype The query type.
 * @param name The domain name.
 * @return The query information if found.
 */
boost::optional<struct query> resolver::find_cached_query(enum dns_query_type qtype, std::string name)
{
	boost::optional<struct query> query;

	BOOST_FOREACH(struct query tmp, cached) {
		if(tmp.qtype == qtype && name.compare(tmp.name) == 0) {
			cached.push_back(tmp);
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
boost::optional<struct query> resolver::find_active_query(uint16_t tid)
{
	boost::optional<struct query> query;

	BOOST_FOREACH(struct query tmp, active) {
		if (tid == tmp.tid) {
			query = tmp;
			break;
		}
	}

	return query;
}


///////////////////////////////////////////////////////////////////////////////
} /* namespace dns */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
