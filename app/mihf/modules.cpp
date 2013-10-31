//=============================================================================
// Brief   : Modules
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

#include "modules.hpp"

#define ODTONE_MODS_PATH "./mods"

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

///////////////////////////////////////////////////////////////////////////////
//static modules::builtin s_builtin_mods[] = {
//};

///////////////////////////////////////////////////////////////////////////////
modules::modules(core& c)
	: _core(c)
{
}

modules::~modules()
{
}

bool modules::load_sap(std::string const& name)
{
	sap_factory* factory;
	entry e;

	size_t n = name.find('.');
	if (n != std::string::npos) {
		std::string tmp(ODTONE_MODS_PATH);
		tmp += name.substr(0, n);
		e.lib = dylib(tmp);
		tmp = "odtone_sap_create_";
		tmp += name.substr(n + 1, std::string::npos);
		factory = e.lib.get_symbol<sap_factory>(tmp);
	} else {
		//modules::builtin* bultin = ...
		factory = nullptr;
	}

	if (!factory)
		return false;

//	e.obj = factory(_core);
//	_core.add(e.obj);
	_mods[name] = e;
	return true;
}

bool modules::unload(std::string const& name)
{
	typedef std::map<std::string, entry>::iterator iterator;

	iterator i = _mods.find(name);
	if (i == _mods.end())
		return false;

//	_core.remove(i->second.obj);
	_mods.erase(i);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
