//==============================================================================
// Brief   : Debug Helpers (platform dependent implementation - win32)
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

#include <odtone/debug.hpp>
#include <cstdlib>

///////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////

/**
 * Setup the crash handler.
 *
 * @note Not implemented yet.
 */
void setup_crash_handler()
{
	//TODO: add unhandled exception suppport
}

/**
 * Handle the crash context.
 * Output the crash infromation and abort the application execution.
 *
 * @param ctx Crash context.
 */
void crash(const crash_ctx& ctx)
{
	std::fprintf(stderr,	 "\n"
							 "================================= Crash Dump ==================================\n"
							 "Code   : %s\n",
							 k_bug_code_string[ctx.code]);

	if (ctx.file) {
		std::fprintf(stderr, "Function  : %s\n"
							 "File      : %s\n"
							 "Line      : %u\n",
							 ctx.function,
							 ctx.file,
							 ctx.line);
	}

	if (ctx.expression) {
		std::fprintf(stderr, "Expression: %s\n",
							 ctx.expression);
	}

	std::fprintf(stderr,	 "===============================================================================\n"
							 "\n");
	std::abort();
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
