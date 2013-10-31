//======================================================================================================
// Brief   : Dynamic Library Support
// Authors : Bruno Santos <bsantos@av.it.pt>
// -----------------------------------------------------------------------------------------------------
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
//======================================================================================================

#ifndef ODTONE_DYLIB__HPP_
#define ODTONE_DYLIB__HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/exception.hpp>
#include <odtone/string.hpp>
#include <odtone/win32.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/decay.hpp>
#if defined(__linux__)
#	include <dlfcn.h>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace odtone {

////////////////////////////////////////////////////////////////////////////////////////////////////////
class dylib_error : virtual public exception {
	friend class dylib;

public:
	dylib_error(std::string const& what)
		: _what(what)
	{ }

	virtual ~dylib_error() throw()
	{ }

	const char* what() const throw() { return _what.c_str(); }

private:
	std::string _what;
};

/**
 * Dynamic library loading and access
 */
class dylib {
	static void* open(const_string_ref filepath)
	{
	#ifdef _WIN32
		void* mod = win32::load_library(filepath);
		if (!mod)
			throw_exception(dylib_error(win32::error_string(win32::get_last_error())));
	#else
		void* mod = ::dlopen(filepath.data(), RTLD_NOW);
		if (!mod)
			throw_exception(dylib_error(::dlerror()));
	#endif
		return mod;
	}

	static void close(void* mod)
	{
	#ifdef _WIN32
		bool success = win32::free_library(mod);
		ODTONE_ASSERT(success != false);
	#else
		bool failure = ::dlclose(mod);
		ODTONE_ASSERT(failure != true);
	#endif
	}

	ODTONE_UNDEFINED_BOOL;

public:
	typedef void* native_type;

	dylib()
	{ }

	/**
	 * Loads a dynamic library onto the process memory
	 *
	 * @param filepath Path to the library file
	 */
	dylib(const_string_ref filepath)
		: _module(open(filepath), &dylib::close)
	{ }

	/**
	 * Looks up a function exported by the dynamic library
	 *
	 * @param name Name of the symbol function to look up
	 * @return A pointer to the specified symbol or null if not found.
	 */
	template<class Signature>
	typename boost::decay<Signature>::type get_symbol(const_string_ref name) const
	{
		typedef typename boost::decay<Signature>::type type;

	#ifdef _WIN32
		return reinterpret_cast<type>(win32::get_library_symbol(_module.get(), name));
	#else
		return reinterpret_cast<type>(::dlsym(_module.get(), name.data()));
	#endif
	}

	/**
	 * Returns the underlying plataform native dynamic library module
	 */
	native_type native() const { return _module.get(); }

	/**
	 * Check if it contains a loaded library
	 *
	 * @return true if a dynamic library is loaded
	 */
	operator undefined_bool() const
	{
		return _module.get() ? ODTONE_UNDEFINED_BOOL_TRUE : ODTONE_UNDEFINED_BOOL_FALSE;
	}

private:
	boost::shared_ptr<void> _module;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_DYLIB__HPP_ */
