//==============================================================================
// Brief   : LIST Data Type
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
import java.util.ArrayList;

import mih.types.Serializeable;

public class List<T extends Serializeable> extends ArrayList<T> implements
		Serializeable {

	public List(Class<T> type) {
		this.type = type;
	}

	public List(List<T> value) {
		this.type = value.type;
		clear();
		for (int i = 0; i < value.size(); ++i)
			add(value.get(i));
	}

	public void toBytes(ByteArrayOutputStream stream) throws Exception {
		stream.write(this.size());

		for (int i = 0; i < this.size(); ++i)
			this.get(i).toBytes(stream);
	}

	public void fromBytes(ByteArrayInputStream stream) throws Exception {
		int size = stream.read();

		for (int i = 0; i < size; ++i) {
			T item;
			try {
				item = (T) Class.forName(type.getName()).newInstance();
				item.fromBytes(stream);
				this.add(item);
			} catch (InstantiationException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IllegalAccessException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (ClassNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	private Class<T> type;
}