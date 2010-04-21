//=============================================================================
// Brief   : MIH Message
// Authors : Bruno Santos <bsantos@av.it.pt>
//
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

#include <odtone/mih/message.hpp>
#include <odtone/mih/tlv_types.hpp>

///////////////////////////////////////////////////////////////////////////////
/**
 * \defgroup MIH
 *
 * <b> Introduction </b>
 *
 * The MIH API contains a set of classes to generate/parse MIH messages,
 * including the types present in the standard and template classes to ease the
 * definition of new types.
 *
 * <b> Types </b>
 *
 * The payload of a message is a sequence of types that require (de)serialization
 * support. In this particular case, the serialization is done with the TLV archive
 * odtone::mih::itlv and odtone::mih::otlv. The MIH types support (de)serialization
 * for the odtone::mih::iarchive and odtone::mih::oarchive, this particular archive
 * does not include the TLV field, this is necessary in order to support defining
 * new sequence types from existing MIH types. However, the TLV archive requieres
 * TLV encoding. The odtone::mih::tlv_fwd template class allows to easily typedef
 * TLV type helpers that perform forwarding from a specific MIH type with TLV
 * serialization support.
 *
 * Some template classes are available to easily define new types:
 * - BITMAP maps to odtone::mih::bitmap
 * - CHOICE maps to \a boost::variant
 * - ENUMERATED maps to odtone::mih::enumeration
 *
 * For optional parameters use \a boost::optional<T>, see odtone::mih::message for
 * more details.
 *
 * In the case of SEQUENCE types, this are implemented using class/struct that
 * must have a serialize() method (see the odtone::mih::archive).
 *
 * <b> MIH Messages </b>
 *
 * For generating/parsing messages, a mini DSL is provided for maximum flexibility
 * and extendability. For more details see odtone::mih::message.
 */

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
message::message()
	: _version(1), _ackreq(false), _ackrsp(false), _uir(false), _m(false),
	_fn(0), _mid(0), _tid(0)
{
}

message::message(const frame& fm)
{
	*this = fm;
}

message::~message()
{
}

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
	iarchive& in = ar.input();

	ar.append(fm.payload(), fm.payload() + fm.plength());
	in & tlv_source_id(_src);
	in & tlv_destination_id(_dst);

	_payload.clear();
	_payload.append(fm.payload() + ar.position(), fm.payload() + fm.plength());

	return *this;
}

/**
 * \brief Get the MIH Message Frame
 * \param fm a dynamic frame buffer to fill
 */
void message::get_frame(frame_vla& fm) const
{
	archive ar;
	oarchive& out = ar.output();

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

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
