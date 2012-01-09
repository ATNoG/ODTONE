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

#ifndef ODTONE_DNS_RESOLVER__HPP_
#define ODTONE_DNS_RESOLVER__HPP_

#include <list>
#include <netinet/in.h>

#include <boost/function.hpp>

#include <odtone/net/dns/message.hpp>

#define	DNS_PACKET_LEN		2048	/**< Buffer size for DNS packet.	*/
#define	DNS_QUERY_TIMEOUT	30		/**< Query timeout, seconds.		*/

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace dns {

///////////////////////////////////////////////////////////////////////////////

/**
 * Callback routine definition.
 */
typedef boost::function<void (struct dns_cb_data*)> dns_callback_t;

enum dns_query_type {
	DNS_A_RECORD		= 0x01,	/**< Lookup IPv4 address for host.	*/
	DNS_MX_RECORD		= 0x0f,	/**< Lookup MX for domain.			*/
	DNS_AAAA_RECORD		= 0x1c,	/**< Lookup IPv6 address for host.	*/
	DNS_SRV_RECORD		= 0x21,	/**< Lookup SRV for domain.			*/
	DNS_NAPTR_RECORD	= 0x23	/**< Lookup NAPTR	for domain.		*/
};

/**
 * User defined function that will be called when DNS reply arrives for
 * requested hostname.
 */
enum dns_error {
	DNS_OK,				/**< No error.					*/
	DNS_DOES_NOT_EXIST,	/**< Address does not exist.	*/
	DNS_TIMEOUT,		/**< Lookup time expired.		*/
	DNS_ERROR			/**< Generic error.				*/
};

/**
 * User query. Holds mapping from application-level ID to DNS transaction id,
 * and user defined callback function.
 */
struct query {
	time_t			expire;			/**< Time when this query expire.	*/
	uint16_t		tid;			/**< UDP DNS transaction ID.		*/
	uint16_t		qtype;			/**< Query type.					*/
	std::string		name;			/**< Host name.						*/
	void			*ctx;			/**< Application context.			*/
	dns_callback_t	callback;		/**< User callback routine.			*/
	message			dns_message;	/**< Response DNS message.			*/

	bool operator==(const struct query &other) const
	{
		return ((qtype == other.qtype) && (name.compare(other.name) == 0));
	}
};

/**
 * Structure that is passed to the user callback, which has an
 * error indicator, received packet, requested host name, etc.
 */
struct dns_cb_data {
	void				*context;				/**< Query context.			*/
	enum dns_error		error;					/**< Error type.			*/
	enum dns_query_type	query_type;				/**< Query type.			*/
	std::string			name;					/**< Requested host name.	*/
	message				dns_message;			/**< Response DNS message.	*/
};

/**
 * Resolver descriptor.
 */
struct dns {
	int					sock;		/**< UDP socket used for queries.	*/
	struct sockaddr_in	sa;			/**< DNS server socket address.		*/
	uint16_t			tid;		/**< Latest tid used.				*/
	std::list<struct query>	active;	/**< Active queries.				*/
	std::list<struct query>	cached;	/**< Cached queries.				*/
};

/**
 * DNS network packet.
 */
struct header {
	uint16_t		tid;		/**< Transaction ID.		*/
	uint16_t		flags;		/**< Flags.					*/
	uint16_t		nqueries;	/**< Questions.				*/
	uint16_t		nanswers;	/**< Answers.				*/
	uint16_t		nauth;		/**< Authority PRs.			*/
	uint16_t		nother;		/**< Other PRs.				*/
	unsigned char	data[1];	/**< Data, variable length.	*/
};

// TODO singleton
// TODO use boost sockets
// TODO replace header for DNS messages
class resolver {
public:
	/**
	 * Construct the DNS resolver.
	 */
	resolver();

	/**
	 * Destruct the DNS resolver.
	 */
	~resolver();

	/**
	 * Queries the DNS server.
	 *
	 * @param host Query to be performed.
	 * @param type Query type.
	 * @param callback Callback function.
	 */
	void queue(std::string host, enum dns_query_type type, dns_callback_t callback);

private:
	/**
	 * Initializer the resolver descriptor.
	 */
	void dns_init();

	/**
	 * Check if there are pending messages.
	 */
	void dns_poll();

	/**
	 * Cleanup the resolver descriptor.
	 */
	void dns_fini();

	/**
	 * Queue the resolution.
	 *
	 * @param ctx Query context.
	 * @param name Query to be performed.
	 * @param qtype Query type.
	 * @param callback Callback function.
	 */
	void dns_queue(void *ctx, std::string name, enum dns_query_type qtype, dns_callback_t callback);

	/**
	 * Cancel the query.
	 *
	 * @param context The query context.
	 */
	void dns_cancel(const void *context);

private:
	struct dns dns;	/**< DNS resolver descriptor.	*/
};


///////////////////////////////////////////////////////////////////////////////
} /* namespace dns */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_DNS_RESOLVER__HPP_ */
