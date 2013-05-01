//==============================================================================
// Brief   : Core Service
// Authors : Bruno Santos <bsantos@av.it.pt>
// -----------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2013 Universidade Aveiro
// Copyright (C) 2013 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#ifndef ODTONE_MIHF_PLUGIN__HPP_
#define ODTONE_MIHF_PLUGIN__HPP_

////////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mihf/service.hpp>
#include <boost/make_shared.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

////////////////////////////////////////////////////////////////////////////////
#define ODTONE_PLUGIN_EXPORT_SAP(name, type)                                                 \
extern "C" ::odtone::mihf::sap_ptr odtone_sap_create_##name##(::odtone::mihf::service& core) \
{                                                                                            \
	return boost::make_shared<type>(boost::ref(core));                                       \
}

////////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

////////////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIHF_PLUGIN__HPP_ */
