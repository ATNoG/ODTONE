//==============================================================================
// Brief   : SEQUENCE Data Type
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

public abstract class Sequence<A extends Serializeable, B extends Serializeable, C extends Serializeable, D extends Serializeable, E extends Serializeable, F extends Serializeable, G extends Serializeable, H extends Serializeable, I extends Serializeable, J extends Serializeable, K extends Serializeable>
		implements Serializeable {

	public static class ObjectNull implements Serializeable {

		@Override
		public void toBytes(ByteArrayOutputStream stream) {
			// TODO Auto-generated method stub
		}

		@Override
		public void fromBytes(ByteArrayInputStream stream) {
			// TODO Auto-generated method stub
		}

	}

	public Sequence() {
		this.a = null;
		this.b = null;
		this.c = null;
		this.d = null;
		this.e = null;
		this.f = null;
		this.g = null;
		this.h = null;
		this.i = null;
		this.j = null;
		this.k = null;
	}

	public Sequence(A a) {
		this.a = a;
		this.b = null;
		this.c = null;
		this.d = null;
		this.e = null;
		this.f = null;
		this.g = null;
		this.h = null;
		this.i = null;
		this.j = null;
		this.k = null;
	}

	public Sequence(A a, B b) {
		this.a = a;
		this.b = b;
		this.c = null;
		this.d = null;
		this.e = null;
		this.f = null;
		this.g = null;
		this.h = null;
		this.i = null;
		this.j = null;
		this.k = null;
	}

	public Sequence(A a, B b, C c) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = null;
		this.e = null;
		this.f = null;
		this.g = null;
		this.h = null;
		this.i = null;
		this.j = null;
		this.k = null;
	}

	public Sequence(A a, B b, C c, D d) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = d;
		this.e = null;
		this.f = null;
		this.g = null;
		this.h = null;
		this.i = null;
		this.j = null;
		this.k = null;
	}

	public Sequence(A a, B b, C c, D d, E e) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = d;
		this.e = e;
		this.f = null;
		this.g = null;
		this.h = null;
		this.i = null;
		this.j = null;
		this.k = null;
	}

	public Sequence(A a, B b, C c, D d, E e, F f) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = d;
		this.e = e;
		this.f = f;
		this.g = null;
		this.h = null;
		this.i = null;
		this.j = null;
		this.k = null;
	}

	public Sequence(A a, B b, C c, D d, E e, F f, G g) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = d;
		this.e = e;
		this.f = f;
		this.g = g;
		this.h = null;
		this.i = null;
		this.j = null;
		this.k = null;
	}

	public Sequence(A a, B b, C c, D d, E e, F f, G g, H h) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = d;
		this.e = e;
		this.f = f;
		this.g = g;
		this.h = h;
		this.i = null;
		this.j = null;
		this.k = null;
	}

	public Sequence(A a, B b, C c, D d, E e, F f, G g, H h, I i) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = d;
		this.e = e;
		this.f = f;
		this.g = g;
		this.h = h;
		this.i = i;
		this.j = null;
		this.k = null;
	}

	public Sequence(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = d;
		this.e = e;
		this.f = f;
		this.g = g;
		this.h = h;
		this.i = i;
		this.j = j;
		this.k = null;
	}

	public Sequence(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = d;
		this.e = e;
		this.f = f;
		this.g = g;
		this.h = h;
		this.i = i;
		this.j = j;
		this.k = k;
	}

	protected A getA() {
		return a;
	}

	protected void setA(A a) {
		this.a = a;
	}

	protected B getB() {
		return b;
	}

	protected void setB(B b) {
		this.b = b;
	}

	protected C getC() {
		return c;
	}

	protected void setC(C c) {
		this.c = c;
	}

	protected D getD() {
		return d;
	}

	protected void setD(D d) {
		this.d = d;
	}

	protected E getE() {
		return e;
	}

	protected void setE(E e) {
		this.e = e;
	}

	protected F getF() {
		return f;
	}

	protected void setF(F f) {
		this.f = f;
	}

	protected G getG() {
		return g;
	}

	protected void setG(G g) {
		this.g = g;
	}

	protected H getH() {
		return h;
	}

	protected void setH(H h) {
		this.h = h;
	}

	protected I getI() {
		return i;
	}

	protected void setI(I i) {
		this.i = i;
	}

	protected J getJ() {
		return j;
	}

	protected void setJ(J j) {
		this.j = j;
	}

	protected K getK() {
		return k;
	}

	protected void setK(K k) {
		this.k = k;
	}

	public void toBytes(ByteArrayOutputStream stream) throws Exception {
		if (a == null)
			return;
		a.toBytes(stream);

		if (b == null)
			return;
		b.toBytes(stream);

		if (c == null)
			return;
		c.toBytes(stream);

		if (d == null)
			return;
		d.toBytes(stream);

		if (e == null)
			return;
		e.toBytes(stream);

		if (f == null)
			return;
		f.toBytes(stream);

		if (g == null)
			return;
		g.toBytes(stream);

		if (h == null)
			return;
		h.toBytes(stream);

		if (i == null)
			return;
		i.toBytes(stream);

		if (j == null)
			return;
		j.toBytes(stream);

		if (k == null)
			return;
		k.toBytes(stream);
	}

	public void fromBytes(ByteArrayInputStream stream) throws Exception {
		if (a == null)
			return;
		a.fromBytes(stream);

		if (b == null)
			return;
		b.fromBytes(stream);

		if (c == null)
			return;
		c.fromBytes(stream);

		if (d == null)
			return;
		d.fromBytes(stream);

		if (e == null)
			return;
		e.fromBytes(stream);

		if (f == null)
			return;
		f.fromBytes(stream);

		if (g == null)
			return;
		g.fromBytes(stream);

		if (h == null)
			return;
		h.fromBytes(stream);

		if (i == null)
			return;
		i.fromBytes(stream);

		if (j == null)
			return;
		j.fromBytes(stream);

		if (k == null)
			return;
		k.fromBytes(stream);
	}

	A a;
	B b;
	C c;
	D d;
	E e;
	F f;
	G g;
	H h;
	I i;
	J j;
	K k;
}