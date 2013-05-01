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

#ifndef ODTONE_MIHF_SERVICE__HPP_
#define ODTONE_MIHF_SERVICE__HPP_

////////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mihf/message.hpp>
#include <boost/utility.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

////////////////////////////////////////////////////////////////////////////////
using boost::system::error_code;

////////////////////////////////////////////////////////////////////////////////
typedef boost::function<void(error_code&, message const&)> response;

class service : boost::noncopyable {
public:
	class user;
	class access_point;

public:
	virtual ~service()
	{ }

	virtual bool indication(message const& msg) = 0;
	virtual bool indication(message const& msg, response resp) = 0;
	virtual bool request(message const& msg, response resp) = 0;
};

////////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

////////////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIHF_SERVICE__HPP_ */
