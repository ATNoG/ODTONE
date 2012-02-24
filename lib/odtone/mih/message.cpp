//==============================================================================
// Brief   : MIH Message
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

#include <odtone/mih/message.hpp>
#include <odtone/mih/tlv_types.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct an empty MIH Message.
 *
 * The defaults for each field are:
 *    version = 1;
 *    ackreq  = false;
 *    ackrsp  = false;
 *    uir     = false;
 *    m       = false;
 *    fn      = 0;
 *    mid     = 0;
 *    tid     = 0;
 */
message::message()
	: _version(1), _ackreq(false), _ackrsp(false), _uir(false), _m(false),
	_fn(0), _mid(0), _tid(0), _payload(), _in(_payload), _out(_payload)
{
}

/**
 * Construct a MIH Message by extracting the data from a frame.
 *
 * @param fm The frame from which extract the information.
 */
message::message(const frame& fm)
	: _payload(), _in(_payload), _out(_payload)
{
	*this = fm;
}

/**
 * Destruct a MIH Message.
 */
message::~message()
{
}

/**
 * Extract the message data from a frame.
 *
 * @param fm The frame from which extract the information.
 * @return The message with updated data.
 */
message& message::operator=(const frame& fm)
{
	_version = fm.version();
	_ackreq = fm.ackreq();
	_ackrsp = fm.ackrsp();
	_uir = fm.uir();
	_m = fm.m();
	_fn = fm.fn();
	_mid = fm.mid();
	_tid = fm.tid();

	archive ar;
	iarchive in(ar);

	ar.append(fm.payload(), fm.payload() + fm.plength());
	in & tlv_source_id(_src);
	in & tlv_destination_id(_dst);

	_payload.clear();
	_payload.append(fm.payload() + ar.position(), fm.payload() + fm.plength());
	_payload.position(0);

	return *this;
}

/**
 * Set the message payload by copying it from another message.
 * @note The source and destination TLVs are not copied.
 *
 * @param msg The message from which extract the payload.
 */
void message::payload(const message& msg)
{
	frame_vla fm;
	msg.get_frame(fm);

	archive ar;
	iarchive in(ar);

	id tmp;
	ar.append(fm->payload(), fm->payload() + fm->plength());
	in & tlv_source_id(tmp);
	in & tlv_destination_id(tmp);

	_payload.clear();
	_payload.append(fm->payload() + ar.position(), fm->payload() + fm->plength());
	_payload.position(0);
}

/**
 * Get the MIH Message Frame.
 *
 * @param fm A dynamic frame buffer to store the information.
 */
void message::get_frame(frame_vla& fm) const
{
	archive ar;
	oarchive out(ar);

	out & tlv_source_id(_src);
	out & tlv_destination_id(_dst);
	ar.append(_payload.buffer().begin(), _payload.buffer().end());

	fm.size(ar.buffer().size());
	fm.zero();
	fm->version(_version);
	fm->ackreq(_ackreq);
	fm->ackrsp(_ackrsp);
	fm->uir(_uir);
	fm->m(_m);
	fm->fn(_fn);
	fm->mid(_mid);
	fm->tid(_tid);
	fm->plength(truncate_cast<uint16>(ar.buffer().size()));
	std::copy(ar.buffer().begin(), ar.buffer().end(), fm->payload());
}

/**
 * Check if the MIH Message has service specific TLVs
 *
 * @return true if has service specific TLVs or false otherwise.
 */
bool message::has_service_specific_tlv()
{
	return !(_payload.begin() == _payload.end());
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
