//=============================================================================
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

#ifndef ODTONE_DEBUG__HPP_
#define ODTONE_DEBUG__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////

/**
 * Bug code enumeration.
 */
enum bug {
	bug_on,							/**< On.						*/
	bug_assert,						/**< Assert.					*/
	bug_assert_ptr,					/**< Assert pointer.			*/
	bug_not_implemented,			/**< Not implemented.			*/
	bug_never_here,					/**< Never here.				*/
	bug_floting_point_exception,	/**< Floating point exception.	*/
	bug_invalid_opcode,				/**< Invalid opcode.			*/
	bug_terminal_interrupt,			/**< Terminal intterrupt.		*/
	bug_page_fault,					/**< Page fault.				*/
	bug_breakpoint,					/**< Breakpoint.				*/
};

/**
 * Bug code strings.
 */
extern char const* k_bug_code_string[];

/**
 * Crash context structure.
 */
struct crash_ctx {
	bug         code;		/**< Crash bug code.	*/
	void*       address;	/**< Crash address.		*/
	const char* function;	/**< Crash function.	*/
	const char* file;		/**< Crash file.		*/
	uint        line;		/**< Crash line.		*/
	const char* expression;	/**< Crash expression.	*/
	void*       context;	/**< Crash context.		*/
};

/**
 * Mechanism for debugging, which allows to follow the execution states of the
 * application. It can be viewed as a linked list of checkpoints that maintains
 * the execution states of the application. If a crash happens, the last
 * checkpoint will point to its occurence.
 */
class checkpoint {
public:
	/**
	 * Get the top checkpoint in the list.
	 *
	 * @return The top checkpoint in the list.
	 */
	static checkpoint* top();

	/**
	 * Construct a checkpoint and add it to the checkpoint list.
	 *
	 * @param file file name of the checkpoint.
	 * @param line line number of the checkpoint.
	 * @param exp expression of the checkpoint.
	 */
	checkpoint(const char* file, uint line, const char* exp);

	/**
	 * Destruct a checkpoint and remove it from the checkpoint list.
	 */
	~checkpoint();

	/**
	 * Get the previous checkpoint.
	 *
	 * @return The previous checkpoint.
	 */
	checkpoint* previous() const
	{
		return _prev;
	}

	/**
	 * Get the checkpoint's file name.
	 *
	 * @return The checkpoint's file name.
	 */
	const char* file() const
	{
		return _file;
	}

	/**
	 * Get the checkpoint's line number.
	 *
	 * @return The checkpoint's line number.
	 */
	uint line() const 
	{
		return _line; 
	}

	/**
	 * Get the checkpoint's expression.
	 *
	 * @return The checkpoint's expression.
	 */
	const char* expression() const
	{
		return _exp;
	}

	operator bool() const { return false; }

private:
	checkpoint* _prev;	/**< Checkpoint's previous checkpoint.	*/
	const char* _file;	/**< Checkpoint's file name.			*/
	uint        _line;	/**< Checkpoint's line number.			*/
	const char* _exp;	/**< Checkpoint's expression.			*/
};

/**
 * Setup the crash handler.
 */
void setup_crash_handler();

/**
 * Creates the crash context and dispatch it to its handler.
 *
 * @param code Crash bug code.
 * @param function Crash function.
 * @param file Crash file name.
 * @param line Crash line number.
 * @param expression Crash expression.
 */
void crash(bug code, const char* function, const char* file, uint line, const char* expression);

/**
 * Handles the crash context.
 *
 * @param ctx Crash context.
 */
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
