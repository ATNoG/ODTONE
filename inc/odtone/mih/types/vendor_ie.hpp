//=============================================================================
// Brief   : Vendor Information Element
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

#ifndef ODTONE_MIH_TYPES_VENDOR_IE__HPP_
#define ODTONE_MIH_TYPES_VENDOR_IE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/buffer.hpp>
#include <odtone/mih/archive.hpp>
#include <boost/function.hpp>
#include <algorithm>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
inline bool is_vendor_ie(uint32 id)
{
#ifdef NDEBUG
	return (id >= 0x20000000) && (id <= 0x7FFFFFFF);
#else
	return ((id >= 0x20000000) && (id <= 0x7FFFFFFF)) || ((id >= 0x80000000) && (id <= 0x82FFFFFF));
#endif
}

/**
 * Define VENDOR_IE data type.
 */
class vendor_ie {
public:
	vendor_ie()
		: _id(0)
	{ }

	vendor_ie(const vendor_ie& lhs)
		: _id(lhs._id)
	{
		_data.size(lhs._data.size());
		std::copy(lhs._data.get(), lhs._data.get() + lhs._data.size(), _data.get());
	}

	vendor_ie& operator=(const vendor_ie& lhs)
	{
		if (this != &lhs) {
			_id = lhs._id;
			_data.size(lhs._data.size());
			std::copy(lhs._data.get(), lhs._data.get() + lhs._data.size(), _data.get());
		}

		return *this;
	}

	uint32 id() const { return _id; }

	bool serialize(iarchive& ar)
	{
		uint32 type;
		uint   pos = ar.position();
		uint   len;

		ar & type;
		if (!is_vendor_ie(type)) {
			ar.position(pos);
			return false;
		}

		ar & len;
		_data.size(len);
		std::copy(ar.current(), ar.current() + len, _data.get());
		ar.advance(len);

		return true;
	}

	void serialize(oarchive& ar)
	{
		ar & _id;
		ar & _data.size();
		ar.append(_data.get(), _data.get() + _data.size());
	}

private:
	uint32        _id;
	buffer<uint8> _data;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LIST(VENDOR_IE) data type.
 */
class vendor_ie_list : std::vector<vendor_ie> {
	typedef std::vector<vendor_ie> base;

public:
	using base::iterator;
	using base::const_iterator;

	using base::push_back;
	using base::pop_back;
	using base::front;
	using base::back;
	using base::begin;
	using base::end;
	using base::size;
	using base::clear;
	using base::resize;
	using base::operator[];

	void serialize(oarchive& ar)
	{
		for (base::iterator i = base::begin(), e = base::end(); i != e; ++i)
			i->serialize(ar);
	}

	void serialize(iarchive& ar)
	{
		base::clear();

		while (ar.position() < ar.length()) {
			base::resize(base::size() + 1);
			vendor_ie& ie = base::back();

			if (!ie.serialize(ar)) {
				base::resize(base::size() - 1);
				return;
			}
		}
	}
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_VENDOR_IE__HPP_ */
