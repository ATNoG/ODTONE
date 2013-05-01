//==============================================================================
// Brief   : Modules
// Authors : Bruno Santos <bsantos@av.it.pt>
// -----------------------------------------------------------------------------
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
//==============================================================================

#ifndef ODTONE_MIHF_MODULES__HPP_
#define ODTONE_MIHF_MODULES__HPP_

////////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/dylib.hpp>
#include <odtone/mihf/service.hpp>
#include <odtone/mihf/sap.hpp>
#include <boost/utility.hpp>
#include "core_service.hpp"
#include <map>

////////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

////////////////////////////////////////////////////////////////////////////////
class modules : boost::noncopyable {
	typedef sap_ptr sap_factory(service& srv);

	struct entry {
		sap_ptr obj;
		dylib   lib;
	};

public:
	struct builtin {
		const char*  name;
		sap_factory* factory;
	};

public:
	modules(core_service& core);
	~modules();

	bool load_sap(std::string const& name);
	bool unload(std::string const& name);

private:
	core_service&                _core;
	std::map<std::string, entry> _mods;
};

////////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

////////////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIHF_MODULES__HPP_ */
