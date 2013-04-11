//==============================================================================
// Brief   : Class representing a DataTypes.cs entity
// Authors : Marcelo Génio <marcelog@ua.pt>
//           Rui Fonseca <ruimfonseca@av.it.pt>
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

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MIH.DataTypes
{
    /// <summary>
    /// Class representing a Octect String.
    /// </summary>
    public class OctetString
    {
        /// <summary>
        /// The String value.
        /// </summary>
        public string StringValue { get; private set; }

        /// <summary>
        /// The Byte Value.
        /// </summary>
        public byte[] ByteValue { get; set; }

        /// <summary>
        /// OctectString Constructor.
        /// </summary>
        /// <param name="os">OctectString object.</param>
        public OctetString(OctetString os) : this(os.StringValue) {}

        /// <summary>
        /// OctectString Constructor.
        /// </summary>
        /// <param name="src">Serialized OctetString.</param>
        public OctetString(byte[] src) : this(new String(Encoding.ASCII.GetChars(src,1,src[0]))) { }

        /// <summary>
        /// OctectString constructor.
        /// </summary>
        /// <param name="value">String value.</param>
        public OctetString(String value)
        {
            StringValue = value;

            ByteValue = new byte[value.Length + 1];

            ByteValue[0] = IntToByte(value.Length);

            for (int i = 1, j = 0; j < value.Length; i++, j++)
            {
                ByteValue[i] = BitConverter.GetBytes(value[j])[0];
            }
        }

        /// <summary>
        /// Int to byte converter.
        /// </summary>
        /// <param name="value">int value.</param>
        /// <returns>byte Result.</returns>
        private static byte IntToByte(int value)
        {
            byte[] intBytes = BitConverter.GetBytes(value);
            if (!BitConverter.IsLittleEndian)
                Array.Reverse(intBytes);
            return intBytes[0];
        }

    }
    /// <summary>
    /// Class representing a MIHF ID.
    /// </summary>
    public class ID
    {
        /// <summary>
        /// id value, as a OctectString.
        /// </summary>
        private OctetString id;

        /// <summary>
        /// ByteValue of the ID object.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                return id.ByteValue;
            }

            set
            {
                id.ByteValue = value;
            }
        }

        /// <summary>
        /// ID constructor.
        /// </summary>
        /// <param name="id">id OctectString</param>
        public ID(OctetString id)
        {
            this.id = id;
        }

        /// <summary>
        /// Overrided ToString() method.
        /// </summary>
        /// <returns>String representation of ID object.</returns>
        public override string ToString()
        {
            return id.StringValue;
        }

    }


}
