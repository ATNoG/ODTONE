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
#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace dns {

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
static int getdnsip(struct dns &dns)
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
				dns.sa.sin_addr.s_addr = inet_addr(value);
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
				dns.sa.sin_addr.s_addr =
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

/**
 * Initializer the resolver descriptor.
 */
void resolver::dns_init()
{
	int		rcvbufsiz = 128 * 1024;

#ifdef _WIN32
	{ WSADATA data; WSAStartup(MAKEWORD(2,2), &data); }
#endif /* _WIN32 */

	if ((dns.sock = socket(PF_INET, SOCK_DGRAM, 17)) == -1)
		return;
	else if (nonblock(dns.sock) != 0)
		return;

	dns.sa.sin_family = AF_INET;
	dns.sa.sin_port = htons(53);

	/* Increase socket's receive buffer */
	(void) setsockopt(dns.sock, SOL_SOCKET, SO_RCVBUF,
	    (char *) &rcvbufsiz, sizeof(rcvbufsiz));
}

/*
 * Find host in host cache. Add it if not found.
 */
static boost::optional<struct query> find_cached_query(struct dns &dns, enum dns_query_type qtype, std::string name)
{
	boost::optional<struct query> query;

	BOOST_FOREACH(struct query tmp, dns.cached) {
		if(tmp.qtype == qtype && name.compare(tmp.name) == 0) {
			dns.cached.push_back(tmp);
			query = tmp;
			break;
		}
	}

	return query;
}

static boost::optional<struct query> find_active_query(struct dns &dns, uint16_t tid)
{
	boost::optional<struct query> query;

	BOOST_FOREACH(struct query tmp, dns.active) {
		if (tid == tmp.tid) {
			query = tmp;
			break;
		}
	}

	return query;
}

static void call_user(struct dns &dns, struct query query, enum dns_error error)
{
	struct dns_cb_data cbd;

	cbd.context	= query.ctx;
	cbd.query_type	= (enum dns_query_type) query.qtype;
	cbd.error	= error;
	cbd.name	= query.name;
	cbd.dns_message = query.dns_message;
	query.callback(&cbd);

	/* Cache the query */
	dns.cached.push_back(query);
}

static void parse_udp(struct dns &dns, const unsigned char *pkt, int len)
{
	const frame *pud = frame::cast(pkt, len);

	if(!pud)
		return;

	message dns_message(*pud);

	if (dns_message.nquery() < 1)
		return;

	/* Check if there is an active quuery */
	boost::optional<struct query> q;
	q = find_active_query(dns, dns_message.tid());
	if (!q.is_initialized())
		return;

	// Associate the DNS message with the query
	q->dns_message = dns_message;

	/* Received 0 answers */
	if (dns_message.nanswer() == 0) {
		call_user(dns, q.get(), DNS_DOES_NOT_EXIST);
		return;
	}

	BOOST_FOREACH(struct resource_record tmp, dns_message.answer()) {
		if (tmp._type == q->qtype) {
			call_user(dns, q.get(), DNS_OK);
			break;
		}
	}
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
	while ((n = recvfrom(dns.sock, pkt, sizeof(pkt), 0,
	    (struct sockaddr *) &sa, &len)) > 0 &&
	    n > (int) sizeof(struct header)) {
		parse_udp(dns, pkt, n);
	}

	/* Cleanup expired active queries */
	BOOST_FOREACH(struct query tmp, dns.active) {
		if (tmp.expire < now) {
			call_user(dns, tmp, DNS_TIMEOUT);
			dns.active.remove(tmp);
		}
	}

	/* Cleanup cached queries */
	BOOST_FOREACH(struct query tmp, dns.cached) {
		if (tmp.expire < now) {
			dns.cached.remove(tmp);
		}
	}
}

/**
 * Cleanup the resolver descriptor.
 */
void resolver::dns_fini()
{
	if (dns.sock != -1)
		(void) closesocket(dns.sock);

	BOOST_FOREACH(struct query tmp, dns.active) {
		dns.active.remove(tmp);
	}

	BOOST_FOREACH(struct query tmp, dns.cached) {
		dns.cached.remove(tmp);
	}
}

/**
 * Queue the resolution.
 *
 * @param ctx Query context.
 * @param name Query to be performed.
 * @param qtype Query type.
 * @param callback Callback function.
 */
void resolver::dns_queue(void *ctx, std::string name,
		enum dns_query_type qtype, dns_callback_t callback)
{
	time_t				now = time(NULL);
	struct dns_cb_data	cbd;

	/* Search the cache first */
	boost::optional<struct query> cached_query;
	cached_query = find_cached_query(dns, qtype, name);
	if (cached_query.is_initialized()) {
		cached_query->ctx = ctx;
		call_user(dns, cached_query.get(), DNS_OK);
		if (cached_query->expire < now) {
			dns.cached.remove(cached_query.get());
		}
		return;
	}

	/* DNS message */
	message dns_message;
	dns_message.tid(++(dns.tid));
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

	if (sendto(dns.sock, sbuff, slen, 0,
	    (struct sockaddr *) &dns.sa, sizeof(dns.sa)) < 0) {
		(void) memset(&cbd, 0, sizeof(cbd));
		cbd.error = DNS_ERROR;
		callback(&cbd);
		return;
	}

	// Store query as active
	struct query query_info;
	query_info.ctx	= ctx;
	query_info.qtype	= (uint16_t) qtype;
	query_info.tid	= dns_message.tid();
	query_info.callback	= callback;
	query_info.expire	= now + DNS_QUERY_TIMEOUT;
	boost::algorithm::to_lower(name);
	query_info.name = name;

	dns.active.push_back(query_info);
}

/**
 * Construct the DNS resolver.
 */
resolver::resolver()
{
	// Initialize the resolver descriptor
	dns_init();
}

/**
 * Destruct the DNS resolver.
 */
resolver::~resolver()
{
	dns_fini();
}

/**
 * Queries the DNS server.
 *
 * @param host Query to be performed.
 * @param type Query type.
 * @param callback Callback function.
 */
void resolver::queue(std::string host, enum dns_query_type type, dns_callback_t callback)
{
	fd_set set;
	struct timeval tv = {0, 100000};

	// Get the DNS Server IP address
	if (getdnsip(dns) != 0)
		return;

	dns_queue(&host, host, type, callback);

	FD_ZERO(&set);
	FD_SET(dns.sock, &set);

	if (select(dns.sock + 1, &set, NULL, NULL, &tv) == 1)
		dns_poll();
}

/**
 * Cancel the query.
 *
 * @param context The query context.
 */
void resolver::dns_cancel(const void *context)
{
	BOOST_FOREACH(struct query tmp, dns.active) {
		if (tmp.ctx == context) {
			dns.active.remove(tmp);
			break;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
} /* namespace dns */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
