//=============================================================================
// Brief   : Debug Helpers (platform dependent implementation - win32)
// Authors : Bruno Santos <bsantos@av.it.pt>
//
//
// Copyright (C) 2009 Universidade Aveiro - Instituto de Telecomunicacoes Polo Aveiro
//
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#include <odtone/debug.hpp>
#include <cstdlib>

///////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
void setup_crash_handler()
{
	//TODO: add unhandled exception suppport
}

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
