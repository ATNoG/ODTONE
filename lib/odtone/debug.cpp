//==============================================================================
// Brief   : Debug Helpers
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
#include <boost/assert.hpp>
#include <cstring>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
/**
 * Bug code strings.
 */
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

/**
 * Get the top checkpoint in the list.
 *
 * @return The top checkpoint in the list.
 */
checkpoint* checkpoint::top()
{
	return check_point_list;
}

/**
 * Construct a checkpoint and add it to the checkpoint list.
 *
 * @param file file name of the checkpoint.
 * @param line line number of the checkpoint.
 * @param exp expression of the checkpoint.
 */
checkpoint::checkpoint(const char* file, uint line, const char* exp)
	: _prev(check_point_list), _file(file), _line(line), _exp(exp)
{
	ODTONE_CHECKPOINT_SET(this);
}

/**
 * Destruct a checkpoint and remove it from the checkpoint list.
 */
checkpoint::~checkpoint()
{
	ODTONE_CHECKPOINT_SET(_prev);
}

/**
 * Creates the crash context and dispatch it to its handler.
 *
 * @param code Crash bug code.
 * @param function Crash function.
 * @param file Crash file name.
 * @param line Crash line number.
 * @param expression Crash expression.
 */
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

/**
 * XXX Delete.
 */
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
