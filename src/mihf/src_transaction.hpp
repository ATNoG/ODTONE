//==============================================================================
// Brief   : Source Transaction
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

#ifndef SRC_TRANSACTION_HPP
#define SRC_TRANSACTION_HPP

///////////////////////////////////////////////////////////////////////////////
#include "transaction.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Source State Machine States.
 */
enum src_transaction_state_t
	{
        SRC_INIT,				/**< Init state.					*/
        SRC_WAIT_RESPONSE_MSG,	/**< Wait response message state.	*/
        SRC_PROCESS_MSG,		/**< Process message state.			*/
        SRC_WAIT_ACK,			/**< Wait acknowledge state.		*/
        SRC_FAILURE,			/**< Failure state.					*/
        SRC_SUCCESS				/**< Success state.					*/
	};

 /**
 * This class represents an instance of the Source State Machine
 * transaction.
 */
class src_transaction_t
	: public transaction_t
{
public:
	/**
	 * Constructor a Source State Machine transaction.
	 *
	 * @param f The transaction handler.
	 * @param netsap The netsap module.
	 */
	src_transaction_t(handler_t &f, net_sap &netsap);

	/**
	 * Run Source State Machine transaction.
	 */
	void run();

	src_transaction_state_t state;	/**< The current state of the transaction.	*/
};


typedef boost::shared_ptr< src_transaction_t > src_transaction_ptr;

typedef std::set<src_transaction_ptr,
		 transaction_compare<src_transaction_ptr > >src_transaction_set;

  } /* namespace mihf */
} /* namespace odtone */

#endif
