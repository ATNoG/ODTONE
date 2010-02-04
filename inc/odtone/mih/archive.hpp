//=============================================================================
// Brief   : Archive for MIH Types Serialization
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

#ifndef ODTONE_MIH_ARCHIVE__HPP_
#define ODTONE_MIH_ARCHIVE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mih/types/base.hpp>
#include <odtone/exception.hpp>
#include <boost/utility.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

class iarchive;
class oarchive;

///////////////////////////////////////////////////////////////////////////////
class archive {
public:
	archive();
	~archive();

	void clear();
	void swap(std::vector<uint8>& buffer);
	void buffer(const uint8* buf, size_t len);

	template<class InputIteratorT>
	void append(InputIteratorT begin, InputIteratorT end)
	{
		_buf.insert(_buf.end(), begin, end);
	}

	std::vector<uint8>& buffer();

	iarchive& input();
	oarchive& output();

	void rewind(uint pos = 0);
	uint position() const { return _pos; }

protected:
	std::vector<uint8> _buf;
	uint               _pos;
};

///////////////////////////////////////////////////////////////////////////////
class iarchive : public archive {
public:
	uint list_length();

	iarchive& operator&(bool& val);
	iarchive& operator&(uint8& val);
	iarchive& operator&(uint16& val);
	iarchive& operator&(uint32& val);
	iarchive& operator&(uint64& val);
	iarchive& operator&(sint8& val);
	iarchive& operator&(sint16& val);
	iarchive& operator&(sint32& val);
	iarchive& operator&(sint64& val);
	iarchive& operator&(octet_string& val);
	iarchive& operator&(std::vector<uint8>& buf);
};

///////////////////////////////////////////////////////////////////////////////
class oarchive : public archive {
public:
	void list_length(uint len);

	oarchive& operator&(bool val);
	oarchive& operator&(uint8 val);
	oarchive& operator&(uint16 val);
	oarchive& operator&(uint32 val);
	oarchive& operator&(uint64 val);
	oarchive& operator&(sint8 val);
	oarchive& operator&(sint16 val);
	oarchive& operator&(sint32 val);
	oarchive& operator&(sint64 val);
	oarchive& operator&(std::string& val);
	oarchive& operator&(std::vector<uint8>& buf);
};

///////////////////////////////////////////////////////////////////////////////
inline iarchive& archive::input()
{
	return static_cast<iarchive&>(*this);
}

inline oarchive& archive::output()
{
	return static_cast<oarchive&>(*this);
}

///////////////////////////////////////////////////////////////////////////////
struct iarchive_error : virtual public exception { };

struct iarchive_eof_error : virtual public iarchive_error {
	iarchive_eof_error() : exception("odtone::mih::iarchive: end of stream")
	{ }
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/detail/archive.hpp>

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_ARCHIVE__HPP_ */
