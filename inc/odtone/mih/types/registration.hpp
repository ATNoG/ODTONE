//=============================================================================
// Brief   : MIH Registration Types
// Authors : Bruno Santos <bsantos@av.it.pt>
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

#ifndef ODTONE_MIH_TYPES_REGISTRATION__HPP_
#define ODTONE_MIH_TYPES_REGISTRATION__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * REQ_REQUEST_CODE data type enumeration.
 */
enum reg_request_code_enum {
	reg_request_registration = 0,		/**< Registration.		*/
	reg_request_re_registration = 1,	/**< Re-Registration.	*/
};

/**
 * REQ_REQUEST_CODE data type.
 */
typedef enumeration<reg_request_code_enum> reg_request_code;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_REGISTRATION__HPP_ */
