//=============================================================================
// Brief   : Message
// Authors : Bruno Santos <bsantos@cppdev.net>
// ----------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2012-2013 Universidade Aveiro
// Copyright (C) 2012-2013 Instituto de Telecomunicações - Pólo Aveiro
// Copyright (C) 2013 Bruno Santos
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#ifndef ODTONE_MIHF_MESSAGE__HPP_
#define ODTONE_MIHF_MESSAGE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <boost/utility.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/function.hpp>
#include <tuple>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

///////////////////////////////////////////////////////////////////////////////
class message : boost::noncopyable, public boost::enable_shared_from_this<message> {
protected:
	message(uint mid);
	message(std::string const& mihf, uint mid);
	virtual ~message();

public:
	std::string const& mihf() const { return _mihf; }
	uint               mid() const  { return _mid; }

	uchar  service() const { return (_mid >> 12  )      ; }
	uchar  opcode() const  { return (_mid >> 10  ) & 0x3; }
	ushort action() const  { return (_mid & 0x3ff)      ; }

private:
	std::string _mihf;
	uint        _mid;
};

////////////////////////////////////////////////////////////////////////////////
template<uint ServiceId, uint Opcode, uint ActionId, class ...Args>
class message_ : public message {
	typedef message_<ServiceId, Opcode, ActionId, Args...> this_type;

public:
	static const uint k_mid = ((ServiceId << 12) | ((Opcode << 10) & 0x3) | (ActionId & 0x3ff));

public:
	message_(Args&& ...args)
		: _args(std::forward<Args>(args)...)
	{ }

	message_(std::string const& mihf, Args&& ...args)
		: message(mihf), _args(std::forward<Args>(args)...)
	{ }

private:
	std::tuple<Args...> _args;
};

template<class T>
struct is_message : boost::mpl::false_ { };

template<uint ServiceId, uint Opcode, uint ActionId, class... Args>
struct is_message<message_<ServiceId, Opcode, ActionId, Args...>> : boost::mpl::true_ { };

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline typename boost::enable_if<is_message<T>, T>::type* message_cast(message* msg)
{
	if (msg->mid() != T::k_mid)
		return nullptr;
	return static_cast<T*>(msg);
}

template<class T>
inline typename boost::enable_if<is_message<T>, T>::type const* message_cast(message const* msg)
{
	if (msg->mid() != T::k_mid)
		return nullptr;
	return static_cast<T const*>(msg);
}

////////////////////////////////////////////////////////////////////////////////
class send_message_functor {
public:
	send_message_functor()
		: _func()
	{ }

	template<class F>
	send_message_functor(F f)
		: _func(f)
	{ }

	void operator()(message& msg) const
	{
		_func(msg);
	}

private:
	boost::function<void(message&)> _func;
};

extern send_message_functor send_message;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIHF_MESSAGE__HPP_ */
