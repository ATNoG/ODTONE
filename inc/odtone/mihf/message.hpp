//=============================================================================
// Brief   : Message
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

#ifndef ODTONE_MIHF_MESSAGE__HPP_
#define ODTONE_MIHF_MESSAGE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/buffer.hpp>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/tuple/tuple.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

///////////////////////////////////////////////////////////////////////////////
class message : boost::noncopyable {
protected:
	message(uint mid);
	message(std::string const& mihf, uint mid);
	virtual ~message();

public:
	std::string const& mihf() const { return _mihf; }
	uint               mid() const  { return _mid; }

	uint service_id() const { return (_mid >> 12  )      ; }
	uint opcode() const     { return (_mid >> 10  ) & 0x3; }
	uint action_id() const  { return (_mid & 0x3ff)      ; }

private:
	std::string   _mihf;
	uint          _mid;
};

typedef boost::shared_ptr<message> message_ptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
using boost::tuples::null_type;

template<uint ServiceId, uint Opcode, uint ActionId,
         class A1 = null_type, class A2 = null_type, class A3 = null_type,
         class A4 = null_type, class A5 = null_type, class A6 = null_type,
         class A7 = null_type, class A8 = null_type, class A9 = null_type>
class message_;

/*template<uint ServiceId, uint Opcode, uint ActionId, class... Args>
struct message_ : public message {
	typedef message_<ServiceId, Opcode, ActionId, Args...> this_type;

	static const uint k_mid = ((ServiceId << 12) | ((Opcode << 10) & 0x3) | (ActionId & 0x3ff));

	message_(Args&&... a)
		: message(k_mid), args(std::forward<Args>(a)...)
	{ }

	message_(std::string const& mihf, Args&&... a)
		: message(mihf, k_mid), args(std::forward<Args>(a)...)
	{ }

	~message_()
	{ }

	boost::tuple<Args...> args;
};*/

template<class T>
struct is_message : boost::mpl::false_ { };

//template<uint ServiceId, uint Opcode, uint ActionId, class... Args>
//struct is_message<message_<ServiceId, Opcode, ActionId, Args...>> : boost::mpl::true_ { };

template<uint ServiceId, uint Opcode, uint ActionId,
         class A1, class A2, class A3,
         class A4, class A5, class A6,
         class A7, class A8, class A9>
struct is_message<message_<ServiceId, Opcode, ActionId, A1, A2, A3, A4, A5, A6, A7, A8, A9> >
	: boost::mpl::true_ { };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline T* message_cast(message* msg)
{
	ODTONE_STATIC_ASSERT(is_message<T>::value, "T must be a message type");

	if (msg->mid() != T::k_mid)
		return false;
	return static_cast<T*>(msg);
}

template<class T>
inline T const* message_cast(message const* msg)
{
	ODTONE_STATIC_ASSERT(is_message<T>::value, "T must be a message type");

	if (msg->mid() != T::k_mid)
		return false;
	return static_cast<T const*>(msg);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIHF_MESSAGE__HPP_ */
