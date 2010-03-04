//=============================================================================
// Brief   : Debug Helpers
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
#include <boost/assert.hpp>
#include <cstring>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
char const* k_bug_code_string[] = {
	"bug",
	"assert",
	"assert pointer",
	"not implemented",
	"never here",
	"floting point exception",
	"invalid opcode",
	"terminal interrupt",
	"page fault",
	"breakpoint"
};

///////////////////////////////////////////////////////////////////////////////
#if defined(__GNUC__)
	static __thread odtone::checkpoint* check_point_list;
#	define ODTONE_CHECKPOINT_SET(x) check_point_list = x
#elif defined(BOOST_MSVC)
	static __declspec(thread) odtone::checkpoint* check_point_list;
#	define ODTONE_CHECKPOINT_SET(x) check_point_list = x
#else
	static nullptr_t check_point_list = nullptr_t();
#	define ODTONE_CHECKPOINT_SET(x)
#endif

checkpoint* checkpoint::top()
{
	return check_point_list;
}

checkpoint::checkpoint(const char* file, uint line, const char* exp)
	: _prev(check_point_list), _file(file), _line(line), _exp(exp)
{
	ODTONE_CHECKPOINT_SET(this);
}

checkpoint::~checkpoint()
{
	ODTONE_CHECKPOINT_SET(_prev);
}

void crash(bug code, const char* function, const char* file, uint line, const char* expression)
{
	crash_ctx ctx;

	std::memset(&ctx, 0, sizeof(ctx));
	ctx.code = code;
	ctx.address = ODTONE_RETURN_ADDRESS;
	ctx.function = function;
	ctx.file = file;
	ctx.line = line;
	ctx.expression = expression;
	crash(ctx);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

///////////////////////////////////////////////////////////////////////////////
void boost::assertion_failed(char const* expr, char const* function, char const* file, long line)
{
	odtone::crash_ctx ctx;

	std::memset(&ctx, 0, sizeof(ctx));
	ctx.code = odtone::bug_assert;
	ctx.address = ODTONE_RETURN_ADDRESS;
	ctx.function = function;
	ctx.file = file;
	ctx.line = line;
	ctx.expression = expr;
	crash(ctx);
}

// EOF ////////////////////////////////////////////////////////////////////////
