//=============================================================================
// Brief   : Archive for MIH Types Serialization
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
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
//=============================================================================

#ifndef ODTONE_MIH_ARCHIVE__HPP_
#define ODTONE_MIH_ARCHIVE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/mih/archive_fwd.hpp>
#include <odtone/mih/types/base.hpp>
#include <odtone/exception.hpp>
#include <boost/utility.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * iarchive error exception.
 */
struct iarchive_error : virtual public exception { };

/**
 * iarchive end of file error exception.
 */
struct iarchive_eof_error : virtual public iarchive_error {
	/**
	 * Construct an iarchive end of file error exception.
	 */
	iarchive_eof_error() : exception("odtone::mih::iarchive: end of stream")
	{ }
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Provides serialization/deserialization for the message payload.
 */
class archive {
	friend class iarchive;
	friend class oarchive;

public:
	typedef std::vector<uint8>::const_iterator const_iterator;

public:
	/**
	 * Construct an archive.
	 */
	archive();

	/**
	 * Destruct an archive.
	 */
	~archive();

	/**
	 * Clear the contents of the archive.
	 * Its size and actual position is set to 0 (zero).
	 */
	void clear();

	/**
	 * Exchanges the content of the archive by the content of buffer, which
	 * can have different sizes. All iterators, references and
	 * pointers remain valid for the swapped vectors.
	 *
	 * @param buffer A vector providing the elements to be swapped.
	 */
	void swap(std::vector<uint8>& buffer);

	/**
	 * Fills archive's contents.
	 *
	 * @param buf The elements to be copied to the archive.
	 * @param len The number of elements to be copied.
	 */
	void buffer(const uint8* buf, size_t len);

	/**
	 * Inserts an element, a number of elements or a range of elements into
	 * the archive at a specified position.
	 *
	 * @param begin The position of the first element to be copied.
	 * @param end The position of the last element to be copied.
	 */
	template<class InputIteratorT>
	void append(InputIteratorT begin, InputIteratorT end)
	{
		_buf.insert(_buf.begin() + _pos, begin, end);
	}

	/**
	 * A random-access iterator addressing the first element in the archive or
	 * to the location succeeding an empty archive. The iterator should always
	 * be compared with vector::end to ensure it is valid.
	 *
	 * @return A random-access iterator to the first element in
	 *		   the container.
	 */
	const_iterator begin() const
	{
		return _buf.begin();
	}

	/**
	 * A random-access iterator to the end of the archive object. If the
	 * archive is empty, vector::end == vector::begin.
	 *
	 * @return A random-access iterator that points just beyond
	 *			the end of the archive.
	 */
	const_iterator end() const
	{
		return _buf.end();
	}

	/**
	 * Get archive's contents.
	 *
	 * @return The archive's contents.
	 */
	std::vector<uint8>& buffer();

	/**
	 * Get the corresponding input archive.
	 *
	 * @return The input archive.
	 */
	iarchive input();

	/**
	 * Get the corresponding output archive.
	 *
	 * @return The output archive.
	 */
	oarchive output();

	/**
	 * Point to a new position in the archive.
	 *
	 * @param pos The new position in the archive where to point.
	 */
	void position(uint pos)
	{
		_pos = pos;
	}

	/**
	 * Get the current position in the archive.
	 *
	 * @return The current position in the archive.
	 */
	uint position() const
	{
		return _pos;
	}

protected:
	std::vector<uint8> _buf;	/**< Archive buffer. 			*/
	uint               _pos;	/**< Buffer current position.	*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * The MIH types support deserialization for the input archive. This
 * particular archive does not include the TLV field, which is necessary
 * to support the definition of new sequence types from existing MIH types.
 */
class iarchive {
public:
	typedef iarchive iarchive_type;

public:
	typedef std::vector<uint8>::const_iterator const_iterator;

public:
	/**
	 * Construct an input archive.
	 *
	 * @param ar The archive from where extract the data.
	 */
	iarchive(archive& ar)
		: _buf(ar._buf), _pos(ar._pos), _begin(ar._pos), _length(ar._buf.size() - ar._pos)
	{ }

	/**
	 * Construct an input archive.
	 *
	 * @param ar The archive from where extract the data.
	 * @param length Size of the data.
	 */
	iarchive(archive& ar, uint length)
		: _buf(ar._buf), _pos(ar._pos), _begin(ar._pos), _length(length)
	{ }

	/**
	 * Construct an input archive.
	 *
	 * @param ar The input archive from where extract the data.
	 * @param length Size of the data.
	 */
	iarchive(iarchive& ar, uint length)
		: _buf(ar._buf), _pos(ar._pos), _begin(ar._pos), _length(length)
	{ }

	/**
	 * Overwrites the current data.
	 *
	 * @param ar The archive from where extract the data.
	 */
	void reset(archive& ar)
	{
		new(this) iarchive(ar);
	}

	/**
	 * Point to a new position in the input archive.
	 *
	 * @param pos The new position to point in the input archive.
	 */
	void position(uint pos)
	{
		_pos = _begin + pos;
	}

	/**
	 * Get the current position in the input archive.
	 *
	 * @return The current position in the input archive.
	 */
	uint position() const
	{
		return _pos - _begin;
	}

	/**
	 * Get the length of the input archive.
	 *
	 * @return The length of the input archive.
	 */
	uint length() const
	{
		return _length;
	}

	/**
	 * Advance the position in the input archive.
	 *
	 * @param pos The number of positions to advance.
	 */
	void advance(uint pos)
	{
		ODTONE_ASSERT((_pos + pos) <= _buf.size());
		_pos += pos;
	}

	/**
	 * A random-access iterator addressing the first element in the input 
	 * archive or to the location succeeding an empty archive. The
	 * iterator should always be compared with vector::end to ensure it
	 * is valid.
	 *
	 * @return Returns a random-access iterator to the first element in
	 *		   the input archive.
	 */
	const_iterator begin() const
	{
		return _buf.begin() + _begin;
	}

	/**
	 * A random-access iterator addressing the current element in the input
	 * archive.
	 *
	 * @return A random-access iterator that points just beyond
	 *		   the end of the archive.
	 */
	const_iterator current() const { return _buf.begin() + _pos; }

	/**
	 * A random-access iterator to the end of the input archive object. If the
	 * archive is empty, vector::end == vector::begin.
	 *
	 * @return A random-access iterator that points just beyond
	 *		   the end of the input archive.
	 */
	const_iterator end() const
	{
		return _buf.begin() + _length;
	}

	/**
	 * Get the size of a list of a particular data type.
	 *
	 * @return The size of a list of a particular data type.
	 */
	uint list_length();

	/**
	 * Get a boolean type value from the current position in the input archive.
	 *
	 * @param val Reference to where save the value.
	 * @return The updated input archive.
	 */
	iarchive& operator&(bool& val);

	/**
	 * Get a odtone::uint8 type value from the current position in the input archive.
	 *
	 * @param val Reference to where save the value.
	 * @return The updated input archive.
	 */
	iarchive& operator&(uint8& val);

	/**
	 * Get a odtone::uint16 type value from the current position in the input archive.
	 *
	 * @param val Reference to where save the value.
	 * @return The updated input archive.
	 */
	iarchive& operator&(uint16& val);

	/**
	 * Get a odtone::uint32 type value from the current position in the input archive.
	 *
	 * @param val Reference to where save the value.
	 * @return The updated input archive.
	 */
	iarchive& operator&(uint32& val);

	/**
	 * Get a odtone::uint64 type value from the current position in the input archive.
	 *
	 * @param val Reference to where save the value.
	 * @return The updated input archive.
	 */
	iarchive& operator&(uint64& val);

	/**
	 * Get a odtone::sint8 type value from the current position in the input archive.
	 *
	 * @param val Reference to where save the value.
	 * @return The updated input archive.
	 */
	iarchive& operator&(sint8& val);

	/**
	 * Get a odtone::sint16 type value from the current position in the input archive.
	 *
	 * @param val Reference to where save the value.
	 * @return The updated input archive.
	 */
	iarchive& operator&(sint16& val);

	/**
	 * Get a odtone::sint32 type value from the current position in the input archive.
	 *
	 * @param val Reference to where save the value.
	 * @return The updated input archive.
	 */
	iarchive& operator&(sint32& val);

	/**
	 * Get a odtone::sint64 type value from the current position in the input archive.
	 *
	 * @param val Reference to where save the value.
	 * @return The updated input archive.
	 */
	iarchive& operator&(sint64& val);

	/**
	 * Get a odtone::mih::octet_string type value from the current position in the input archive.
	 *
	 * @param val Reference to where save the value.
	 * @return The updated input archive.
	 */
	iarchive& operator&(octet_string& val);

	/**
	 * Get a list of a particular type value from the current position in the input archive.
	 *
	 * @param buf Reference to where save the value.
	 * @return The updated input archive.
	 */
	iarchive& operator&(std::vector<uint8>& buf);
private:
	std::vector<uint8>& _buf;		/**< Input archive buffer.		*/
	uint&               _pos;		/**< Buffer current position.	*/
	uint                _begin;		/**< Buffer begin position.		*/
	uint                _length;	/**< Buffer size.				*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * The MIH types support serialization for the output archive. This
 * particular archive does not include the TLV field, which is necessary 
 * to support the definition of new sequence types from existing MIH types.
 */
class oarchive {
public:
	typedef oarchive oarchive_type;

public:
	/**
	 * Construct an output archive.
	 *
	 * @param ar The archive from where extract the data.
	 */
	oarchive(archive& ar)
		: _buf(ar._buf), _pos(ar._pos), _begin(ar._pos)
	{ }

	/**
	 * Overwrites the current data.
	 *
	 * @param ar The archive from where extract the data.
	 */
	void reset(archive& ar)
	{
		new(this) oarchive(ar);
	}

	/**
	 * Inserts elements at the output archive current position.
	 *
	 * @param begin The position of the first element to be copied.
	 * @param end The position of the first element to be copied.
	 */
	template<class InputIteratorT>
	void append(InputIteratorT begin, InputIteratorT end)
	{
		_buf.insert(_buf.begin() + _pos, begin, end);
	}

	/**
	 * Point to a new position in the output archive.
	 *
	 * @param pos The new position to point in the output archive.
	 */
	void position(uint pos)
	{
		_pos = _begin + pos;
	}

	/**
	 * Get the current position in the output archive.
	 *
	 * @return The current position in the output archive.
	 */
	uint position() const
	{
		return _pos - _begin;
	}

	/**
	 * Get the length of the output archive.
	 *
	 * @return The length of the output archive.
	 */
	uint length() const
	{
		return _buf.size() - _begin;
	}

	/**
	 * Inserts the size of a list of a particular data type.
	 *
	 * @param len the size of a list of a particular data type.
	 */
	void list_length(uint len);

	/**
	 * Inserts a boolean type value from the current position in the output archive.
	 *
	 * @param val The value to insert.
	 * @return Returns the output archive.
	 */
	oarchive& operator&(bool val);

	/**
	 * Inserts a odtone::uint8 type value from the current position in the output archive.
	 *
	 * @param val The value to insert.
	 * @return Returns the output archive.
	 */
	oarchive& operator&(uint8 val);

	/**
	 * Inserts a odtone::uint16 type value from the current position in the output archive.
	 *
	 * @param val The value to insert.
	 * @return Returns the output archive.
	 */
	oarchive& operator&(uint16 val);

	/**
	 * Inserts a odtone::uint32 type value from the current position in the output archive.
	 *
	 * @param val The value to insert.
	 * @return Returns the output archive.
	 */
	oarchive& operator&(uint32 val);

	/**
	 * Inserts a odtone::uint64 type value from the current position in the output archive.
	 *
	 * @param val The value to insert.
	 * @return Returns the output archive.
	 */
	oarchive& operator&(uint64 val);

	/**
	 * Inserts a odtone::sint8 type value from the current position in the output archive.
	 *
	 * @param val The value to insert.
	 * @return Returns the output archive.
	 */
	oarchive& operator&(sint8 val);

	/**
	 * Inserts a odtone::sint16 type value from the current position in the output archive.
	 *
	 * @param val The value to insert.
	 * @return Returns the output archive.
	 */
	oarchive& operator&(sint16 val);

	/**
	 * Inserts a odtone::sint32 type value from the current position in the output archive.
	 *
	 * @param val The value to insert.
	 * @return Returns the output archive.
	 */
	oarchive& operator&(sint32 val);

	/**
	 * Inserts a odtone::sint64 type value from the current position in the output archive.
	 *
	 * @param val The value to insert.
	 * @return Returns the output archive.
	 */
	oarchive& operator&(sint64 val);

	/**
	 * Inserts a odtone::mih::octet_string type value from the current position in the output archive.
	 *
	 * @param val Reference where to get the value to insert.
	 * @return Returns the output archive.
	 */
	oarchive& operator&(std::string& val);

	/**
	 * Inserts a list of a particular type value from the current position in the output archive.
	 *
	 * @param buf The value to insert.
	 * @return Returns the output archive.
	 */
	oarchive& operator&(std::vector<uint8>& buf);

private:
	std::vector<uint8>& _buf;	/**< Input archive buffer.		*/
	uint&               _pos;	/**< Buffer current position.	*/
	uint                _begin;	/**< Buffer begin position.		*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Get the corresponding input archive.
 *
 * @return The input archive.
 */
inline iarchive archive::input()
{
	return iarchive(*this);
}

/**
 * Get the corresponding output archive.
 *
 * @return The output archive.
 */
inline oarchive archive::output()
{
	return oarchive(*this);
}

///////////////////////////////////////////////////////////////////////////////
/**
 * This class allows to check if a given class is an input archive.
 * It has only a boolean value that is true when the given class is an input
 * archive, or false otherwise.
 */
template<class T>
class is_iarchive {
	typedef char true_t;
	class false_t { char dummy[2]; };

	template<class U> static true_t  test(typename U::iarchive_type* = 0);
	template<class U> static false_t test(...);

public:
	static const bool value = sizeof(test<T>(0)) == sizeof(true_t);
};

///////////////////////////////////////////////////////////////////////////////
/**
 * This class permits to check if a given class is an output archive.
 * It has only a boolean value that is true when the given class is an output
 * archive, or false otherwise.
 */
template<class T>
class is_oarchive {
	typedef char true_t;
	class false_t { char dummy[2]; };

	template<class U> static true_t  test(typename U::oarchive_type* = 0);
	template<class U> static false_t test(...);

public:
	static const bool value = sizeof(test<T>(0)) == sizeof(true_t);
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/detail/archive.hpp>

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_ARCHIVE__HPP_ */
