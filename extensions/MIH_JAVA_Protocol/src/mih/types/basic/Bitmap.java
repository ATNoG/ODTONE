//==============================================================================
// Brief   : BITMAP Data Type
// Authors : Carlos Guimarães <cguimaraes@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2013 Universidade Aveiro
// Copyright (C) 2009-2013 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

package mih.types.basic;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import mih.types.Serializeable;

public class Bitmap implements Serializeable {
	/**
	 * Construct an empty BITMAP data type.
	 */
	public Bitmap(int size) {
		assert (size % 8 == 0);

		bitmap = new byte[size / 8];
	}

	/**
	 * Construct an empty BITMAP data type.
	 */
	public Bitmap(Bitmap b) {
		assert (bitmap.length == b.bitmap.length);

		for (int i = 0; i < bitmap.length; ++i)
			bitmap[i] = b.bitmap[i];
	}

	/**
	 * Clear the BITMAP data type.
	 */
	public void clear() {
		for (int i = 0; i < bitmap.length; ++i)
			bitmap[i] = 0x00;
	}

	/**
	 * Clear the position.
	 *
	 * @param pos
	 *            The position on the bitmap to clear.
	 */
	public void clear(int pos) {
		bitmap[pos / 8] &= ~(1 << (pos % 8));
	}

	/**
	 * Set the position.
	 *
	 * @param pos
	 *            The position on the bitmap to set.
	 */
	public void set(int pos) {
		bitmap[pos / 8] |= (1 << (pos % 8));
	}

	/**
	 * Get the position value.
	 *
	 * @param pos
	 *            The position on the bitmap to get.
	 */
	public boolean get(int pos) {
		return ((bitmap[pos / 8] & (1 << (pos % 8)))) == 1;
	}

	public void toBytes(ByteArrayOutputStream stream) {
		for(int i = 0; i < bitmap.length; ++i)
			stream.write(bitmap[i]);
	}

	public void fromBytes(ByteArrayInputStream stream) {
		for(int i = 0; i < bitmap.length; ++i) {
			bitmap[i] = (byte) stream.read();
		}
	}

	private byte bitmap[];
}