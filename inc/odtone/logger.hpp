//=============================================================================
// Brief   : Logging Facilities
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#ifndef ODTONE_LOGGER__HPP_
#define ODTONE_LOGGER__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <ostream>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
/**
 * The BASE API offers support mechanisms for logging, using odtone::logger class.
 * The logger object is used to log messages for a specific system or application
 * component. Logger names can be arbitrary strings, but they should normally be
 * based on the application that invoke it.
 * Each logger has a level associated with it. This reflects the maximum level
 * that the logger cares about. So if you set level to 2 it only cares about log
 * messages belonging to level 0, 1 and 2.
 * It also has an std::ostream object associated with it. This defines how the
 * logger write and format output as sequences of characters. The log messages
 * can have up to 10 arguments.
 */
class logger : boost::noncopyable {
public:
	/**
	 * Construct a Logger.
	 *
	 * @param name logger's name.
	 * @param log logger from where extract the configurations for the new logger.
	 */
	logger(char const* const name, logger& log);

	/**
	 * Construct a Logger.
	 *
	 * @param name logger's name.
	 * @param sink std::ostream that defines how the logger will write and format output as sequences of characters.
	 */
	logger(char const* const name, std::ostream& sink);

	/**
	 * Destruct for Logger.
	 */
	~logger();

	/**
	 * Set the level configuration. Each logger has a level associated with it.
	 * This reflects the maximum level that the logger cares about. So if you
	 * set level to 2 it only cares about log messages belonging to level 0, 1 and 2.
	 *
	 * @param n logger level.
	 */
	void level(uint n) { _level = n; }

	/**
	 * Get the level configuration. Each logger has a level associated with it.
	 * This reflects the maximum level that the logger cares about. So if you
	 * set level to 2 it only cares about log messages belonging to level 0, 1 and 2.
	 *
	 * @return The logger level.
	 */
	uint level() const { return _level; }

	/**
	 * Get the std::ostream associated with the logger.
	 *
	 * @return The std::ostream associated with the logger.
	 */
	std::ostream& sink() const  { return _sink; }

	template<class T1>
	void operator()(uint level, const T1& arg1)
	{
		if (level > _level)
			return;

		boost::mutex::scoped_lock ml(*_lock);

		_sink << _name << ": " << arg1 << std::endl;
		std::flush(_sink);
	}

	template<class T1, class T2>
	void operator()(uint level, const T1& arg1, const T2& arg2)
	{
		if (level > _level)
			return;

		boost::mutex::scoped_lock ml(*_lock);

		_sink << _name << ": " << arg1 << arg2 << std::endl;
		std::flush(_sink);
	}

	template<class T1, class T2, class T3>
	void operator()(uint level, const T1& arg1, const T2& arg2, const T3& arg3)
	{
		if (level > _level)
			return;

		boost::mutex::scoped_lock ml(*_lock);

		_sink << _name << ": " << arg1 << arg2 << arg3 << std::endl;
		std::flush(_sink);
	}

	template<class T1, class T2, class T3, class T4>
	void operator()(uint level, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4)
	{
		if (level > _level)
			return;

		boost::mutex::scoped_lock ml(*_lock);

		_sink << _name << ": " << arg1 << arg2 << arg3 << arg4 << std::endl;
		std::flush(_sink);
	}

	template<class T1, class T2, class T3, class T4, class T5>
	void operator()(uint level, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5)
	{
		if (level > _level)
			return;

		boost::mutex::scoped_lock ml(*_lock);

		_sink << _name << ": " << arg1 << arg2 << arg3 << arg4 << arg5 << std::endl;
		std::flush(_sink);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6>
	void operator()(uint level, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6)
	{
		if (level > _level)
			return;

		boost::mutex::scoped_lock ml(*_lock);

		_sink << _name << ": " << arg1 << arg2 << arg3 << arg4 << arg5 << arg6 << std::endl;
		std::flush(_sink);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
	void operator()(uint level, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7)
	{
		if (level > _level)
			return;

		boost::mutex::scoped_lock ml(*_lock);

		_sink << _name << ": " << arg1 << arg2 << arg3 << arg4 << arg5 << arg6 << arg7 << std::endl;
		std::flush(_sink);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
	void operator()(uint level, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7, const T8& arg8)
	{
		if (level > _level)
			return;

		boost::mutex::scoped_lock ml(*_lock);

		_sink << _name << ": " << arg1 << arg2 << arg3 << arg4 << arg5 << arg6 << arg7 << arg8 << std::endl;
		std::flush(_sink);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
	void operator()(uint level, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7, const T8& arg8, const T9& arg9)
	{
		if (level > _level)
			return;

		boost::mutex::scoped_lock ml(*_lock);

		_sink << _name << ": " << arg1 << arg2 << arg3 << arg4 << arg5 << arg6 << arg7 << arg8 << arg9 << std::endl;
		std::flush(_sink);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
	void operator()(uint level, const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7, const T8& arg8, const T9& arg9, const T10& arg10)
	{
		if (level > _level)
			return;

		boost::mutex::scoped_lock ml(*_lock);

		_sink << _name << ": " << arg1 << arg2 << arg3 << arg4 << arg5 << arg6 << arg7 << arg8 << arg9 << arg10 << std::endl;
		std::flush(_sink);
	}

private:
	char const* const               _name;
	boost::shared_ptr<boost::mutex> _lock;
	std::ostream&                   _sink;
	uint                            _level;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_LOGGER__HPP_ */
