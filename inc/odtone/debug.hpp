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

#ifndef ODTONE_DEBUG__HPP_
#define ODTONE_DEBUG__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
enum bug {
	bug_on,
	bug_assert,
	bug_assert_ptr,
	bug_not_implemented,
	bug_never_here,
	bug_floting_point_exception,
	bug_invalid_opcode,
	bug_terminal_interrupt,
	bug_page_fault,
	bug_breakpoint,
};

extern char const* k_bug_code_string[];

struct crash_ctx {
	bug         code;
	void*       address;
	const char* function;
	const char* file;
	uint        line;
	const char* expression;
	void*       context;
};

class checkpoint {
public:
	static checkpoint* top();

	checkpoint(const char* file, uint line, const char* exp);
	~checkpoint();

	checkpoint* previous() const   { return _prev; }
	const char* file() const       { return _file; }
	uint        line() const       { return _line; }
	const char* expression() const { return _exp; }

	operator bool() const { return false; }

private:
	checkpoint* _prev;
	const char* _file;
	uint        _line;
	const char* _exp;
};

void setup_crash_handler();

void crash(bug code, const char* function, const char* file, uint line, const char* expression);
ODTONE_NORETURN_BEGIN void crash(const crash_ctx& ctx) ODTONE_NORETURN_END;

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

///////////////////////////////////////////////////////////////////////////////
#define ODTONE_SCOPED_CHECKPOINT(doing) ODTONE_SCOPED(odtone::checkpoint cp = odtone::checkpoint(__FILE__, __LINE__, doing))
#define ODTONE_CHECKPOINT(doing)        odtone::checkpoint BOOST_JOIN(cp_, __LINE__)(__FILE__, __LINE__, doing)
#define ODTONE_BUG_ON(exp, reason)      do { if(ODTONE_UNLIKELY(exp)) { odtone::crash(odtone::bug_on, __FUNCTION__, __FILE__, __LINE__, reason); } } while(0)
#define ODTONE_NOT_IMPLEMENTED          do { odtone::crash(odtone::bug_not_implemented, __FUNCTION__, __FILE__, __LINE__, reason); } while(0)

// DEBUG BUILDS ///////////////////////////////////////////////////////////////
#ifndef NDEBUG
#	define ODTONE_ASSERT(exp)              do { if(ODTONE_UNLIKELY(!(exp))) { odtone::crash(odtone::bug_assert, __FUNCTION__, __FILE__, __LINE__, #exp); } } while(0)
#	define ODTONE_ASSERT_PTR(exp)          do { if(ODTONE_UNLIKELY((exp) == nullptr)) { odtone::crash(odtone::bug_assert_ptr, __FUNCTION__, __FILE__, __LINE__, #exp); } } while(0)
#	define ODTONE_DBG_SCOPED_CHECKPOINT(x) ODTONE_SCOPED_CHECKPOINT(x)
#	define ODTONE_DBG_CHECKPOINT(x)        ODTONE_CHECKPOINT(x)
#	define ODTONE_NEVER_HERE               do { odtone::crash(odtone::bug_never_here, __FUNCTION__, __FILE__, __LINE__, nullptr); } while(0)
#else
#	define ODTONE_ASSERT(x)                ((void) 0)
#	define ODTONE_ASSERT_PTR(x)            ((void) 0)
#	define ODTONE_DBG_SCOPED_CHECKPOINT(x) ((void) 0)
#	define ODTONE_DBG_CHECKPOINT           ((void) 0)
#	ifdef BOOST_MSVC
#		define ODTONE_NEVER_HERE           __assume(0)
#	else
#		define ODTONE_NEVER_HERE           ((void) 0)
#	endif
#endif

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_DEBUG__HPP_ */
