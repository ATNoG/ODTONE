//==============================================================================
// Brief   : Archive for MIH Types Serialization
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

#include <odtone/mih/archive.hpp>
#include <odtone/cast.hpp>

#ifdef BOOST_MSVC
#	pragma warning(push)
#	pragma warning(disable : 4800)
#endif

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct an archive.
 */
archive::archive() : _pos(0)
{
}

/**
 * Destruct an archive.
 */
archive::~archive()
{
}

/**
 * Clear the contents of the archive.
 * Its size and actual position is set to 0 (zero).
 */
void archive::clear()
{
	_buf.resize(0);
	_pos = 0;
}

/**
 * Exchanges the content of the archive by the content of buffer, which
 * can have different sizes. All iterators, references and
 * pointers remain valid for the swapped vectors.
 *
 * @param buffer A vector providing the elements to be swapped.
 */
void archive::swap(std::vector<uint8>& buffer)
{
	_buf.swap(buffer);
	_pos = 0;
}

/**
 * Fills archive's contents.
 *
 * @param buf The elements to be copied to the archive.
 * @param len The number of elements to be copied.
 */
void archive::buffer(const uint8* buf, size_t len)
{
	_buf.resize(len);
	_pos = 0;
	std::copy(buf, buf + len, _buf.begin());
}

/**
 * Get archive's contents.
 *
 * @return The archive's contents.
 */
std::vector<uint8>& archive::buffer()
{
	return _buf;
}

///////////////////////////////////////////////////////////////////////////////
/**
 * Get a boolean type value from the current position in the input archive.
 *
 * @param val Reference to where save the value.
 * @return The updated input archive.
 */
iarchive& iarchive::operator&(bool& val)
{
	uint8 tmp;

	*this & tmp;
	val = bool(tmp);

	return *this;
}

/**
 * Get a odtone::uint8 type value from the current position in the input archive.
 *
 * @param val Reference to where save the value.
 * @return The updated input archive.
 */
iarchive& iarchive::operator&(uint8& val)
{
	if ((_pos + 1) > _buf.size())
		boost::throw_exception(iarchive_eof_error());

	val = _buf[_pos];
	_pos += 1;

	return *this;
}

/**
 * Get a odtone::uint16 type value from the current position in the input archive.
 *
 * @param val Reference to where save the value.
 * @return The updated input archive.
 */
iarchive& iarchive::operator&(uint16& val)
{
	if ((_pos + 2) > _buf.size())
		boost::throw_exception(iarchive_eof_error());

	val = (uint16(_buf[_pos    ]) <<  8)
		| (uint16(_buf[_pos + 1])      );
	_pos += 2;

	return *this;
}

/**
 * Get a odtone::uint32 type value from the current position in the input archive.
 *
 * @param val Reference to where save the value.
 * @return The updated input archive.
 */
iarchive& iarchive::operator&(uint32& val)
{
	if ((_pos + 4) > _buf.size())
		boost::throw_exception(iarchive_eof_error());

	val = (uint32(_buf[_pos    ]) << 24)
		| (uint32(_buf[_pos + 1]) << 16)
		| (uint32(_buf[_pos + 2]) <<  8)
		| (uint32(_buf[_pos + 3])      );
	_pos += 4;

	return *this;
}

/**
 * Get a odtone::uint64 type value from the current position in the input archive.
 *
 * @param val Reference to where save the value.
 * @return The updated input archive.
 */
iarchive& iarchive::operator&(uint64& val)
{
	if ((_pos + 8) > _buf.size())
		boost::throw_exception(iarchive_eof_error());

	val = (uint64(_buf[_pos    ]) << 56)
		| (uint64(_buf[_pos + 1]) << 48)
		| (uint64(_buf[_pos + 2]) << 40)
		| (uint64(_buf[_pos + 3]) << 32)
		| (uint64(_buf[_pos + 4]) << 24)
		| (uint64(_buf[_pos + 5]) << 16)
		| (uint64(_buf[_pos + 6]) <<  8)
		| (uint64(_buf[_pos + 7])      );
	_pos += 8;

	return *this;
}

/**
 * Get a odtone::sint8 type value from the current position in the input archive.
 *
 * @param val Reference to where save the value.
 * @return The updated input archive.
 */
iarchive& iarchive::operator&(sint8& val)
{
	uint8 tmp;

	*this & tmp;

	if (tmp & (1 << 7))
		val = -sint8(~tmp + 1);
	else
		val = tmp;

	return *this;
}

/**
 * Get a odtone::sint16 type value from the current position in the input archive.
 *
 * @param val Reference to where save the value.
 * @return The updated input archive.
 */
iarchive& iarchive::operator&(sint16& val)
{
	uint16 tmp;

	*this & tmp;

	if (tmp & (1 << 15))
		val = -sint16(~tmp + 1);
	else
		val = tmp;

	return *this;
}


/**
 * Get a odtone::sint32 type value from the current position in the input archive.
 *
 * @param val Reference to where save the value.
 * @return The updated input archive.
 */
iarchive& iarchive::operator&(sint32& val)
{
	uint32 tmp;

	*this & tmp;

	if (tmp & (1 << 31))
		val = -sint32(~tmp + 1);
	else
		val = tmp;

	return *this;
}

/**
 * Get a odtone::sint64 type value from the current position in the input archive.
 *
 * @param val Reference to where save the value.
 * @return The updated input archive.
 */
iarchive& iarchive::operator&(sint64& val)
{
	uint64 tmp;

	*this & tmp;

	if (tmp & (1ll << 63))
		val = -sint64(~tmp + 1);
	else
		val = tmp;

	return *this;
}

/**
 * Get a odtone::mih::octet_string type value from the current position in the input archive.
 *
 * @param val Reference to where save the value.
 * @return The updated input archive.
 */
iarchive& iarchive::operator&(octet_string& val)
{
	uint pos = _pos;
	uint len = list_length();

	if ((pos + len) >= _buf.size()) {
		_pos = pos;
		boost::throw_exception(iarchive_eof_error());
	}

	try {
		val.resize(len);

	} catch (...) {
		_pos = pos;
		throw;
	}
	std::copy(_buf.begin() + _pos, _buf.begin() + _pos + len, val.begin());
	_pos += len;

	return *this;
}

/**
 * Get a list of a particular type value from the current position in the input archive.
 *
 * @param buf Reference to where save the value.
 * @return The updated input archive.
 */
iarchive& iarchive::operator&(std::vector<uint8>& buf)
{
	uint pos = _pos;
	uint len = list_length();

	if ((pos + len) >= _buf.size()) {
		_pos = pos;
		boost::throw_exception(iarchive_eof_error());
	}

	try {
		buf.resize(len);

	} catch (...) {
		_pos = pos;
		throw;
	}
	std::copy(_buf.begin() + _pos, _buf.begin() + _pos + len, buf.begin());
	_pos += len;

	return *this;
}

/**
 * Get the size of a list of a particular data type.
 *
 * @return The size of a list of a particular data type.
 */
uint iarchive::list_length()
{
	size_t size = _buf.size();
	uint pos = _pos;
	uint len = 0;
	uint8 n;

	if (pos >= size)
		boost::throw_exception(iarchive_eof_error());

	n = _buf[pos++];
	if (n > 128) {
		n &= 0x7F;
		if ((pos + n) >= size)
			boost::throw_exception(iarchive_eof_error());
		for (uint i = 0; i < n; ++i)
			len = (len << (i * 8)) | _buf[pos++];
		len += 128;

	} else {
		len = n;
	}
	_pos = pos;

	return len;
}

///////////////////////////////////////////////////////////////////////////////
/**
 * Inserts a boolean type value from the current position in the output archive.
 *
 * @param val The value to insert.
 * @return Returns the output archive.
 */
oarchive& oarchive::operator&(bool val)
{
	_buf.resize(_pos + 1);
	_buf[_pos] = uint8(val);
	_pos += 1;

	return *this;
}

/**
 * Inserts a odtone::uint8 type value from the current position in the output archive.
 *
 * @param val The value to insert.
 * @return Returns the output archive.
 */
oarchive& oarchive::operator&(uint8 val)
{
	_buf.resize(_pos + 1);
	_buf[_pos] = val;
	_pos += 1;

	return *this;
}

/**
 * Inserts a odtone::uint16 type value from the current position in the output archive.
 *
 * @param val The value to insert.
 * @return Returns the output archive.
 */
oarchive& oarchive::operator&(uint16 val)
{
	_buf.resize(_pos + 2);
	_buf[_pos    ] = (val >>  8) & 0xFF;
	_buf[_pos + 1] = (val      ) & 0xFF;
	_pos += 2;

	return *this;
}

/**
 * Inserts a odtone::uint32 type value from the current position in the output archive.
 *
 * @param val The value to insert.
 * @return Returns the output archive.
 */
oarchive& oarchive::operator&(uint32 val)
{
	_buf.resize(_pos + 4);
	_buf[_pos    ] = (val >> 24) & 0xFF;
	_buf[_pos + 1] = (val >> 16) & 0xFF;
	_buf[_pos + 2] = (val >>  8) & 0xFF;
	_buf[_pos + 3] = (val      ) & 0xFF;
	_pos += 4;

	return *this;
}

/**
 * Inserts a odtone::uint64 type value from the current position in the output archive.
 *
 * @param val The value to insert.
 * @return Returns the output archive.
 */
oarchive& oarchive::operator&(uint64 val)
{
	_buf.resize(_pos + 8);
	_buf[_pos    ] = (val >> 56) & 0xFF;
	_buf[_pos + 1] = (val >> 48) & 0xFF;
	_buf[_pos + 2] = (val >> 40) & 0xFF;
	_buf[_pos + 3] = (val >> 32) & 0xFF;
	_buf[_pos + 4] = (val >> 24) & 0xFF;
	_buf[_pos + 5] = (val >> 16) & 0xFF;
	_buf[_pos + 6] = (val >>  8) & 0xFF;
	_buf[_pos + 7] = (val      ) & 0xFF;
	_pos += 8;

	return *this;
}

#ifdef BOOST_MSVC
#	pragma warning(push)
#	pragma warning(disable : 4700)
#endif

/**
 * Inserts a odtone::sint8 type value from the current position in the output archive.
 *
 * @param val The value to insert.
 * @return Returns the output archive.
 */
oarchive& oarchive::operator&(sint8 val)
{
	uint8 tmp;

	if (val < 0) {
		tmp = -val;
		tmp = ~tmp + 1;
	} else {
		tmp = val;
	}
	return *this & tmp;
}

/**
 * Inserts a odtone::sint16 type value from the current position in the output archive.
 *
 * @param val The value to insert.
 * @return Returns the output archive.
 */
oarchive& oarchive::operator&(sint16 val)
{
	uint16 tmp;

	if (val < 0) {
		tmp = -val;
		tmp = ~tmp + 1;
	} else {
		tmp = val;
	}
	return *this & tmp;
}

/**
 * Inserts a odtone::sint32 type value from the current position in the output archive.
 *
 * @param val The value to insert.
 * @return Returns the output archive.
 */
oarchive& oarchive::operator&(sint32 val)
{
	uint32 tmp;

	if (val < 0) {
		tmp = -val;
		tmp = ~tmp + 1;
	} else {
		tmp = val;
	}
	return *this & tmp;
}

/**
 * Inserts a odtone::sint64 type value from the current position in the output archive.
 *
 * @param val The value to insert.
 * @return Returns the output archive.
 */
oarchive& oarchive::operator&(sint64 val)
{
	uint64 tmp;

	if (val < 0) {
		tmp = -val;
		tmp = ~tmp + 1;
	} else {
		tmp = val;
	}
	return *this & tmp;
}

#ifdef BOOST_MSVC
#	pragma warning(pop)
#endif

/**
 * Inserts a odtone::mih::octet_string type value from the current position in the output archive.
 *
 * @param val The value to insert.
 * @return Returns the output archive.
 */
oarchive& oarchive::operator&(octet_string& val)
{
	uint len = truncate_cast<uint>(val.length());
	uint pos = _pos;

	list_length(len);
	try {
		_buf.resize(_pos + len);

	} catch (...) {
		_pos = pos;
		throw;
	}
	std::copy(val.begin(), val.end(), _buf.begin() + _pos);
	_pos += len;

	return *this;
}

/**
 * Inserts a list of a particular data type value from the current position
 * in the output archive.
 *
 * @param buf The value to insert.
 * @return Returns the output archive.
 */
oarchive& oarchive::operator&(std::vector<uint8>& buf)
{
	uint len = truncate_cast<uint>(buf.size());
	uint pos = _pos;

	list_length(len);
	try {
		_buf.resize(_pos + len);

	} catch (...) {
		_pos = pos;
		throw;
	}
	std::copy(buf.begin(), buf.end(), _buf.begin() + _pos);
	_pos += len;

	return *this;
}

/**
 * Inserts the size of a list of a particular data type.
 *
 * @param len the size of a list of a particular data type.
 */
void oarchive::list_length(uint len)
{
	uint pos = _pos;

	if (len <= 128) {
		_buf.resize(pos + 1);
		_buf[pos++] = uint8(len);

	} else {
		uint n = 0;

		len -= 128;
		do
			++n;
		while (len >> (n * 8));

		_buf.resize(pos + n + 1);
		_buf[pos++] = 0x80 | uint8(n);

		while (n--)
			_buf[pos++] = (len >> (n * 8)) & 0xFF;
	}
	_pos = pos;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

#ifdef BOOST_MSVC
#	pragma warning(pop)
#endif

// EOF ////////////////////////////////////////////////////////////////////////
