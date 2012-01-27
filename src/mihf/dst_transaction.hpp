//==============================================================================
// Brief   : Destination Transaction
// Authors : Simao Reis <sreis@av.it.pt>
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


#ifndef DST_TRANSACTION_HPP
#define DST_TRANSACTION_HPP

///////////////////////////////////////////////////////////////////////////////
#include "transaction.hpp"

#include <boost/shared_ptr.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Destination State Machine States.
 */
enum dst_transaction_state_t
{
	DST_INIT,				/**< Init state.				*/
	DST_WAIT_RESPONSE_PRM,	/**< Wait for response state.	*/
	DST_SEND_RESPONSE,		/**< Send response state.		*/
	DST_FAILURE,			/**< Failure state.				*/
	DST_SUCCESS				/**< Success state.				*/
};

/**
 * This class represents an instance of the Destination State Machine
 * transaction.
 */
class dst_transaction_t
	: public transaction_t
{
public:
	/**
	 * Constructor a Destination State Machine transaction.
	 *
	 * @param f The transaction handler.
	 * @param netsap The netsap module.
	 */
	dst_transaction_t(handler_t &process_message, net_sap &netsap);

	/**
	 * Run Destination State Machine transaction.
	 */
	void run();

	dst_transaction_state_t state;	/**< The current state of the transaction.	*/
};

typedef boost::shared_ptr< dst_transaction_t > dst_transaction_ptr;

typedef std::set<dst_transaction_ptr,
		 transaction_compare<dst_transaction_ptr > >dst_transaction_set;

  } /* namespace mihf */
} /* namespace odtone */


#endif
