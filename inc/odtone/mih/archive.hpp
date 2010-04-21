//=============================================================================
// Brief   : Archive for MIH Types Serialization
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2010 Universidade de Aveiro
// Copyrigth (C) 2009-2010 Instituto de Telecomunicações - Pólo de Aveiro
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
#include <odtone/mih/archive_fwd.hpp>
#include <odtone/mih/types/base.hpp>
#include <odtone/exception.hpp>
#include <boost/utility.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
struct iarchive_error : virtual public exception { };

struct iarchive_eof_error : virtual public iarchive_error {
	iarchive_eof_error() : exception("odtone::mih::iarchive: end of stream")
	{ }
};

///////////////////////////////////////////////////////////////////////////////
class archive {
	friend class iarchive;
	friend class oarchive;

public:
	typedef std::vector<uint8>::const_iterator const_iterator;

public:
	archive();
	~archive();

	void clear();
	void swap(std::vector<uint8>& buffer);
	void buffer(const uint8* buf, size_t len);

	template<class InputIteratorT>
	void append(InputIteratorT begin, InputIteratorT end)
	{
		_buf.insert(_buf.begin() + _pos, begin, end);
	}

	const_iterator begin() const { return _buf.begin(); }
	const_iterator end() const   { return _buf.end(); }

	std::vector<uint8>& buffer();

	iarchive input();
	oarchive output();

	void position(uint pos) { _pos = pos; }
	uint position() const   { return _pos; }

protected:
	std::vector<uint8> _buf;
	uint               _pos;
};

///////////////////////////////////////////////////////////////////////////////
class iarchive {
public:
	typedef iarchive iarchive_type;

public:
	typedef std::vector<uint8>::const_iterator const_iterator;

public:
	iarchive(archive& ar)
		: _buf(ar._buf), _pos(ar._pos), _begin(ar._pos), _length(ar._buf.size())
	{ }
	iarchive(archive& ar, uint length)
		: _buf(ar._buf), _pos(ar._pos), _begin(ar._pos), _length(length)
	{ }
	iarchive(iarchive& ar, uint length)
		: _buf(ar._buf), _pos(ar._pos), _begin(ar._pos), _length(length)
	{ }

	void reset(archive& ar)
	{
		new(this) iarchive(ar);
	}

	void position(uint pos) { _pos = _begin + pos; }
	uint position() const   { return _pos - _begin; }
	uint length() const     { return _length; }

	const_iterator begin() const { return _buf.begin() + _begin; }
	const_iterator end() const   { return _buf.begin() + _length; }

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

private:
	std::vector<uint8>& _buf;
	uint&               _pos;
	uint                _begin;
	uint                _length;
};

///////////////////////////////////////////////////////////////////////////////
class oarchive {
public:
	typedef oarchive oarchive_type;

public:
	oarchive(archive& ar)
		: _buf(ar._buf), _pos(ar._pos), _begin(ar._pos)
	{ }

	void reset(archive& ar)
	{
		new(this) oarchive(ar);
	}

	template<class InputIteratorT>
	void append(InputIteratorT begin, InputIteratorT end)
	{
		_buf.insert(_buf.begin() + _pos, begin, end);
	}

	void position(uint pos) { _pos = _begin + pos; }
	uint position() const   { return _pos - _begin; }
	uint length() const     { return _buf.size() - _begin; }

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

private:
	std::vector<uint8>& _buf;
	uint&               _pos;
	uint                _begin;
};

///////////////////////////////////////////////////////////////////////////////
inline iarchive archive::input()
{
	return iarchive(*this);
}

inline oarchive archive::output()
{
	return oarchive(*this);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/detail/archive.hpp>

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_ARCHIVE__HPP_ */
