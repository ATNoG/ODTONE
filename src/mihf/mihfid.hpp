//==============================================================================
// Brief   : MIHF ID
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

#ifndef ODTONE_MIHF_ID_HPP
#define ODTONE_MIHF_ID_HPP

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/identification.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * This class represents the MIHF MIH Identifier. It is implemented as a
 * singleton.
 */
class mihfid_t
{
public:
	/**
	 * Creates an instance of the MIHF MIH Identifier.
	 */
	static mih::id* instance();

	/**
	 * Destructor of the MIHF MIH Identifier.
	 */
	~mihfid_t();

private:
	/**
	 * Constructor of the MIHF MIH Identifier.
	 */
	mihfid_t();

	static mih::id *ptr_instance;	/**< MIHF MIH Identifier instance pointer.	*/
};

#define mihfid *mihfid_t::instance()

} /* namespace mihf */ } /* namespace odtone */

#endif
