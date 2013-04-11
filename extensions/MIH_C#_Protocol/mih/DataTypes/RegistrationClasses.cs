//==============================================================================
// Brief   : Class representing a RegistrationClasses.cs entity
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

using MIH.MIHProtocol;

namespace MIH.DataTypes
{

    /// <summary>
    /// This class represents a Link_Register_Indication message.
    /// </summary>
    public class Link_Register_Indication
    {
        /// <summary>
        /// The LinkID.
        /// </summary>
        public Link_Id LinkID { get; set; }

        /// <summary>
        /// byte[] representation of a Link_Register_Indication message.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                GenerateValue();
                return ByteValue;
            }
            private set { ByteValue = value; }
        }

        /// <summary>
        /// Link_Register_Indication constructor.
        /// </summary>
        /// <param name="linkId">The LinkID.</param>
        public Link_Register_Indication(Link_Id linkId)
        {
            this.LinkID = linkId;
        }

        /// <summary>
        /// Link_Register_Indication empty constructor.
        /// </summary>
        public Link_Register_Indication() { }

        /// <summary>
        /// Link_Register_Indication constructor.
        /// </summary>
        /// <param name="linkType">The Link Type.</param>
        /// <param name="addressType">The Address Type.</param>
        /// <param name="addressValue">The Address Value.</param>
        public Link_Register_Indication(Link_Type linkType, Link_Addr.Address_Type addressType, String addressValue)
        {
            this.LinkID = new Link_Id(linkType, new Link_Addr(addressType, addressValue));
        }

        /// <summary>
        /// Link_Register_Indication constructor.
        /// </summary>
        /// <param name="linkType">The Link Type.</param>
        /// <param name="linkAddress">The Link Address.</param>
        public Link_Register_Indication(Link_Type linkType, Link_Addr linkAddress)
        {
            this.LinkID = new Link_Id(linkType, linkAddress);
        }

        /// <summary>
        /// Overrided ToString() method.
        /// </summary>
        /// <returns>A string representation of the Link_Register_Indication object.</returns>
        public override string ToString()
        {
            return "Link_Register.Indication: {LinkID: "+LinkID.ToString()+"}";
        }

        /// <summary>
        /// Generates the byte[] value of the LinkId object.
        /// </summary>
        private void GenerateValue()
        {
            // TODO implement method.
            throw new NotImplementedException();
        }

    }
}
