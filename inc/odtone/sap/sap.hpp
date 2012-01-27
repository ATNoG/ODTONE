//=============================================================================
// Brief   : SAP IO Service
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

#ifndef ODTONE_SAP_SAP__HPP_
#define ODTONE_SAP_SAP__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <boost/utility.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace sap {

///////////////////////////////////////////////////////////////////////////////
/**
 * SAP I/O Service. This is the base
 * This is the base class for all SAPs defined in the ODTONE.
 */
class sap : boost::noncopyable {
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_SAP_SAP__HPP_ */
