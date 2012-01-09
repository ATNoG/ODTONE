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
#include <boost/optional.hpp>

#include <odtone/net/dns/message.hpp>

#define	DNS_PACKET_LEN		2048	/**< Buffer size for DNS packet.	*/
#define	DNS_QUERY_TIMEOUT	30		/**< Query timeout, seconds.		*/

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace dns {

///////////////////////////////////////////////////////////////////////////////

/**
 * Callback routine definition.
 */
typedef boost::function<void (struct callback_info*)> dns_callback_t;

/**
 * DNS query type enumeration.
 */
enum dns_query_type {
	DNS_A_RECORD		= 0x01,	/**< Lookup IPv4 address for host.	*/
	DNS_MX_RECORD		= 0x0f,	/**< Lookup MX for domain.			*/
	DNS_AAAA_RECORD		= 0x1c,	/**< Lookup IPv6 address for host.	*/
	DNS_SRV_RECORD		= 0x21,	/**< Lookup SRV for domain.			*/
	DNS_NAPTR_RECORD	= 0x23	/**< Lookup NAPTR	for domain.		*/
};

/**
 * DNS query status enumeration
 */
enum dns_status {
	DNS_OK,				/**< No error.					*/
	DNS_DOES_NOT_EXIST,	/**< Address does not exist.	*/
	DNS_TIMEOUT,		/**< Lookup time expired.		*/
	DNS_ERROR			/**< Generic error.				*/
};

/**
 * Struct to store query information.
 */
struct query {
	void			*ctx;			/**< Context.						*/
	std::string		name;			/**< Host name.						*/
	uint16			qtype;			/**< Query type.					*/
	uint16			tid;			/**< UDP DNS transaction ID.		*/
	time_t			expire;			/**< Time when this query expire.	*/
	message			dns_message;	/**< Response DNS message.			*/
	dns_callback_t	callback;		/**< User callback routine.			*/

	bool operator==(const struct query &other) const
	{
		return ((qtype == other.qtype) && (name.compare(other.name) == 0));
	}
};

/**
 * Structure that is passed to the applciation callback, which as several
 * information about the query performed.
 */
struct callback_info {
	void				*context;				/**< Context.				*/
	std::string			name;					/**< Requested host name.	*/
	enum dns_query_type	query_type;				/**< Query type.			*/
	enum dns_status		error;					/**< Error type.			*/
	message				dns_message;			/**< Response DNS message.	*/
};

/**
 * DNS network packet.
 */
struct header {
	uint16			tid;		/**< Transaction ID.		*/
	uint16			flags;		/**< Flags.					*/
	uint16			nqueries;	/**< Questions.				*/
	uint16			nanswers;	/**< Answers.				*/
	uint16			nauth;		/**< Authority PRs.			*/
	uint16			nother;		/**< Other PRs.				*/
	unsigned char	data[1];	/**< Data, variable length.	*/
};

// TODO singleton
// TODO use boost sockets
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
	 * @param host The query to be performed.
	 * @param type The query type.
	 * @param app_callback The application callback function.
	 */
	void queue(std::string host, enum dns_query_type type, dns_callback_t app_callback);

private:
	/**
	 * Handle the reception of an asynchronous message.
	 *
	 * @param buff The input message bytes.
	 * @param rbytes The number of bytes of the input message.
	 */
	void receive_handler(const unsigned char *buff, int rbytes);

	/**
	 * Find out if a given query is active.
	 *
	 * @param query The query information.
	 * @param status The query status.
	 */
	void callback(struct query query, enum dns_status status);

	/**
	 * Queue the resolution.
	 *
	 * @param ctx The query context.
	 * @param name The query to be performed.
	 * @param qtype The query type.
	 * @param app_callback The application callback function.
	 */
	void dns_queue(void *ctx, std::string name, enum dns_query_type qtype, dns_callback_t app_callback);

	/**
	 * Check if there are pending messages.
	 */
	void dns_poll();

	/**
	 * Cancel the query.
	 *
	 * @param context The query context.
	 */
	void dns_cancel(const void *context);

	/**
	 * Find a given query in cache.
	 *
	 * @param qtype The query type.
	 * @param name The domain name.
	 * @return The query information.
	 */
	boost::optional<struct query> find_cached_query(enum dns_query_type qtype, std::string name);

	/**
	 * Find out if a given query is active.
	 *
	 * @param tid The transaction identifier.
	 * @return The query information if found.
	 */
	boost::optional<struct query> find_active_query(uint16_t tid);

private:
	int					sock;		/**< UDP socket used for queries.	*/
	struct sockaddr_in	sa;			/**< DNS server socket address.		*/
	uint16_t			tid;		/**< Latest tid used.				*/
	std::list<struct query>	active;	/**< Active queries.				*/
	std::list<struct query>	cached;	/**< Cached queries.				*/
};


///////////////////////////////////////////////////////////////////////////////
} /* namespace dns */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_DNS_RESOLVER__HPP_ */
