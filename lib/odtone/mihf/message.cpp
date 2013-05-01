//=============================================================================
// Brief   : Message
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2012-2013 Universidade Aveiro
// Copyright (C) 2012-2013 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#include <odtone/mihf/message.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

///////////////////////////////////////////////////////////////////////////////
message::message(uint mid)
	: _mid(mid)
{
}

message::message(std::string const& mihf, uint mid)
	: _mihf(mihf), _mid(mid)
{
}

message::~message()
{
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
