//==============================================================================
// Brief   : Class representing a EventClasses.cs entity
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
using System.Net;
using System.Collections;

using MIH.MIHProtocol;

namespace MIH.DataTypes
{
    #region 802.21 Data Types

    /// <summary>
    /// Enum that represents the possible technologies of a link, according to LINK_TYPE definition in IEEE 802.21 specification.
    /// </summary>
    public enum Link_Type
    {
        /// <summary>
        /// The value 0 is reserved.
        /// </summary>
        RESERVED = 0,
        /// <summary>
        /// Wireless - GSM.
        /// </summary>
        Wireless_GSM = 1,
        /// <summary>
        /// Wireless - GPRS.
        /// </summary>
        Wireless_GPRS = 2,
        /// <summary>
        /// Wireless - EDGE.
        /// </summary>
        Wireless_EDGE = 3,
        /// <summary>
        /// Ethernet.
        /// </summary>
        Ethernet = 15,
        /// <summary>
        /// Wireless - Other.
        /// </summary>
        Wireless_Other = 18,
        /// <summary>
        /// Wireless - IEEE 802.11.
        /// </summary>
        Wireless_IEEE80211 = 19,
        /// <summary>
        /// Wireless - CDMA2000.
        /// </summary>
        Wireless_CDMA2000 = 22,
        /// <summary>
        /// Wireless - UMTS.
        /// </summary>
        Wireless_UMTS = 23,
        /// <summary>
        /// Wireless - CDMA2000-HRPD.
        /// </summary>
        Wireless_cdma2000_HRPD = 24,
        /// <summary>
        /// Wireless IEEE 802.16.
        /// </summary>
        Wireless_IEEE80216 = 27,
        /// <summary>
        /// Wireless IEEE 802.20.
        /// </summary>
        Wireless_IEEE80220 = 28,
        /// <summary>
        /// Wireless IEEE 802.22.
        /// </summary>
        Wireless_IEEE80222 = 29
    };

    /// <summary>
    /// Enum that represents the multiple reasons of a link down event.
    /// </summary>
    public enum Link_Dn_Reason
    {
        /// <summary>
        /// The link is down because of explicit disconnect procedures either by MN or network.
        /// </summary>
        ExplicitDisconnect = 0,
        /// <summary>
        /// The link is down because no acknowledgements were received for transmitted packets within the specified time limit.
        /// </summary>
        PacketTimeout = 1,
        /// <summary>
        /// The link is down because there were no resources to maitain the connection.
        /// </summary>
        NoResource = 2,
        /// <summary>
        /// The link is down because broadcast messages (such as beacons in IEEE 802.11 management frames) could not be received by MN.
        /// </summary>
        NoBroadcast = 3,
        /// <summary>
        /// Authentication failure.
        /// </summary>
        AuthenticationFailure = 4,
        /// <summary>
        /// Billing failure.
        /// </summary>
        BillingFailure = 5
    }

    /// <summary>
    /// This class represents the LINK_ADDR data type.
    /// </summary>
    public class Link_Addr
    {
        /// <summary>
        /// The possible address types.
        /// </summary>
        public enum Address_Type
        {
            /// <summary>
            /// Represents a MAC address.
            /// </summary>
            MAC_ADDR,
            /// <summary>
            /// Represents a 3GPP 3G cell identifier.
            /// </summary>
            _3GPP_3G_CELL_ID,
            /// <summary>
            /// Represents a 3GPP 3G cell identifier.
            /// </summary>
            _3GPP_2G_CELL_ID,
            /// <summary>
            /// Represents a 3GPP transport address.
            /// </summary>
            _3GPP_ADDR,
            /// <summary>
            /// Represents a 3GPP2 transport address.
            /// </summary>
            _3GPP2_ADDR,
            /// <summary>
            /// A link layer address other than the address already defined. Example: SSID.
            /// </summary>
            OTHER_L2_ADDR
        }


        /// <summary>
        /// The address type.
        /// </summary>
        public Address_Type Address_type { get; set; }

        /// <summary>
        /// The value of the address.
        /// </summary>
        public string Address_value { get; set; }

        private byte[] byteVal;
        /// <summary>
        /// byte[] representation of a Link_Addr.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                GenerateValue();
                return byteVal;
            }
            private set { byteVal = value; }
        }

        /// <summary>
        /// Link_Class constructor.
        /// </summary>
        /// <param name="Address_type">The address type, chosen from the enum.</param>
        /// <param name="address_value">The ddress value.</param>
        public Link_Addr(Address_Type Address_type, string address_value)
        {
            this.Address_type = Address_type;
            this.Address_value = address_value;
        }

        /// <summary>
        /// String representation of this object.
        /// </summary>
        /// <returns>A string with detailed information on this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// String representation of this object.
        /// </summary>
        /// <param name="prefix">String to be added on the begining of each line.</param>
        /// <returns>A string with detailed information on this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Addr");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tType: "+Address_type);
            sb.AppendLine(prefix + "\tValue: "+Address_value);
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }

        /// <summary>
        /// Deserialization constructor for this object.
        /// </summary>
        /// <param name="bytes">The serialized Link_Addr object.</param>
        public Link_Addr(byte[] bytes)
        {
            this.Address_type = (Address_Type)bytes[0];
            this.Address_value = new String(Encoding.ASCII.GetChars(bytes.Skip(2 + (Address_type==Address_Type.MAC_ADDR ? 2 : 0)).Take(bytes[1 + (Address_type==Address_Type.MAC_ADDR ? 2 : 0)]).ToArray()));
        }

        /// <summary>
        /// Generates a byte[] representation of a Link_Addr.
        /// </summary>
        private void GenerateValue()
        {
            byte[] bval;
            switch (Address_type)
            {
                case Address_Type.MAC_ADDR: bval = new Transport_Addr(6, Address_value).ByteValue; break;
                default: bval = new OctetString(Address_value).ByteValue; break;
            }
            ByteValue = Serialization.Choice(bval, (int)Address_type);
        }
    }

    /// <summary>
    /// Class reperesentation of the Transport_Addr object.
    /// </summary>
    public class Transport_Addr
    {
        /// <summary>
        /// The type of address, from the address family numbers.
        /// </summary>
        /// <remarks>Reference from: http://www.iana.org/assignments/address-family-numbers/address-family-numbers.xml </remarks>
        public ushort AddressType { get; set; }
        /// <summary>
        /// The value of the address.
        /// </summary>
        public OctetString AddressValue { get; set; }

        /// <summary>
        /// Default constructor for this object.
        /// </summary>
        /// <param name="aType">The Link Address type. (More info: http://www.iana.org/assignments/address-family-numbers/address-family-numbers.xml ) </param>
        /// <param name="aVal">The actual address.</param>
        public Transport_Addr(ushort aType, string aVal)
        {
            AddressType = aType;
            AddressValue = new OctetString(aVal);
        }

        /// <summary>
        /// Serialized byte[] representation of this object.
        /// </summary>
        public byte[] ByteValue
        {
            get {
                byte[] result = new byte[2 + AddressValue.ByteValue.Length];
                result[0] = BitConverter.GetBytes(AddressType)[1];
                result[1] = BitConverter.GetBytes(AddressType)[0];
                for (int i = 0; i < AddressValue.ByteValue.Length; i++)
                    result[2 + i] = AddressValue.ByteValue[i];
                return result;
            }
        }
    }

    /// <summary>
    /// Class that represents the LINK_ID
    /// </summary>
    public class Link_Id
    {
        /// <summary>
        /// The LINK_TYPE, represented by the Link_Type enum.
        /// </summary>
        Link_Type Link_type { get; set; }

        /// <summary>
        /// The link_address
        /// </summary>
        Link_Addr Link_address { get; set; }

        private byte[] byteVal;
        /// <summary>
        /// byte[] representation of a Link_Id.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                GenerateValue();
                return byteVal;
            }
            private set { byteVal = value; }
        }

        /// <summary>
        /// The Link_Id constructor.
        /// </summary>
        /// <param name="link_type">The Link Type.</param>
        /// <param name="link_address">The Link Adress.</param>
        public Link_Id(Link_Type link_type, Link_Addr link_address)
        {
            this.Link_type = link_type;
            this.Link_address = link_address;
        }

        /// <summary>
        /// Deserialization constructor for the Link_Id object.
        /// </summary>
        /// <param name="data">Raw serialized Link_Id object.</param>
        public Link_Id(byte[] data)
        {
            this.Link_type = (Link_Type)data[0];
            this.Link_address = new Link_Addr(data.Skip(1).ToArray());
        }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Overloaded ToString() method.
        /// </summary>
        /// <param name="prefix">String to be written at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Id");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tLink Type: " + Link_type);
            sb.AppendLine(prefix + "\tLink Address: " + Link_address.ToString(prefix + "\t"));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }

        /// <summary>
        /// Generates the byte[] value of the LinkId object.
        /// </summary>
        private void GenerateValue()
        {
            if (Link_address != null)
                ByteValue = Serialization.Sequence(BitConverter.GetBytes((int)this.Link_type).Take(1).ToArray(), Link_address.ByteValue);
        }
    }

    /// <summary>
    /// The class that represents the LINK_TUPPLE_ID
    /// </summary>
    public class Link_Tuple_Id
    {
        /// <summary>
        /// The link_id
        /// </summary>
        public Link_Id Link_Id { get; set; }


        /// <summary>
        /// The link_address
        /// </summary>
        private Link_Addr Link_Addr { get; set; }


        private byte[] byteVal;
        /// <summary>
        /// byte[] representation of Link_Tuple_Id
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                GenerateValue();
                return byteVal;
            }
            private set { byteVal = value; }
        }

        /// <summary>
        /// Link_Tuple_Id main constructor.
        /// </summary>
        /// <param name="link_id">The Link Id.</param>
        /// <param name="link_address">The Link Address.</param>
        public Link_Tuple_Id(Link_Id link_id, Link_Addr link_address)
        {
            this.Link_Id = link_id;
            this.Link_Addr = link_address;
        }

        /// <summary>
        /// Deserialization constructor.
        /// </summary>
        /// <param name="fromBytes">Raw serialized Link_Tuple_Id object.</param>
        public Link_Tuple_Id(byte[] fromBytes)
        {
            this.Link_Id = new Link_Id(fromBytes.Take(3+(fromBytes[1]==0?fromBytes[4]+2:fromBytes[2])).ToArray());
            int next = Link_Id.ByteValue.Length;
            if (fromBytes[next] == 0) //choice = 0 -> null link address
                this.Link_Addr = null;
            else
                this.Link_Addr = new Link_Addr(fromBytes.Skip(next+1).ToArray());
        }

        /// <summary>
        /// Overrided ToString() method of the Link_Tuple_Id instance.
        /// </summary>
        /// <returns>String representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Overloaded ToString() method.
        /// </summary>
        /// <param name="prefix">String to be written at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Tuple_Id");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tLink ID: " + Link_Id.ToString(prefix+"\t"));
            if (Link_Addr == null)
                sb.AppendLine(prefix + "\tPoA Address: <empty>");
            else
                sb.AppendLine(prefix + "\tPoA Address: "+ Link_Addr.ToString("\t"+prefix));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }

        /// <summary>
        /// Generates the byte[] value of the Link_Tuple_Id object.
        /// </summary>
        private void GenerateValue()
        {
            if (this.Link_Addr == null)
            {
                ByteValue = Serialization.Sequence(this.Link_Id.ByteValue, Serialization.Choice(null, 0));
            }
            else
            {
                ByteValue = Serialization.Sequence(this.Link_Id.ByteValue, Serialization.Choice(this.Link_Addr.ByteValue, 1));
            }

        }
    }

    /// <summary>
    /// Representation of the Link_MIHCap_Flag. Represents MIH supported services.
    /// </summary>
    public class Link_MIHCap_Flag //bitmap(8)
    {
        public bool bit0, bit4, bit5, bit6, bit7;
        /// <summary>
        /// Whether or not the Event Service is supported.
        /// </summary>
        public bool ESSupported { get; set; }
        /// <summary>
        /// Whether or not the Command Service is supported.
        /// </summary>
        public bool CSSupported{ get; set; }
        /// <summary>
        /// Whether or not the Information Service is supported.
        /// </summary>
        public bool ISSupported { get; set; }

        /// <summary>
        /// A serialized byte representation of this object.
        /// </summary>
        public byte[] ByteValue { get { return getByteVal(); } }
        private byte[] getByteVal()
        {
            BitArray all = new BitArray(8);
            all.Set(0, bit0);
            all.Set(1, ESSupported);
            all.Set(2, CSSupported);
            all.Set(3, ISSupported);
            all.Set(4, bit4);
            all.Set(5, bit5);
            all.Set(6, bit6);
            all.Set(7, bit7);
            return Utilities.Utilities.ToByteArray(all);
        }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Overloaded ToString() method.
        /// </summary>
        /// <param name="prefix">String to be written at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_MIHCap_Flag");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tEvent Service: " + (ESSupported?"Yes": "No"));
            sb.AppendLine(prefix + "\tCommand Service: " + (CSSupported?"Yes": "No"));
            sb.AppendLine(prefix + "\tInformation Service: " + (ISSupported?"Yes": "No"));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }

        /// <summary>
        /// Normal constructor for this object.
        /// </summary>
        /// <param name="EventsSupported">Whether or not the Event Service is supported.</param>
        /// <param name="CommandsSupported">Whether or not the Commands Service is supported.</param>
        /// <param name="InformationSupported">Whether or not the Information Service is supported.</param>
        public Link_MIHCap_Flag(bool EventsSupported, bool CommandsSupported, bool InformationSupported)
        {
            //Reserved
            bit0 = false;
            bit4 = false;
            bit5 = false;
            bit6 = false;
            bit7 = false;

            ESSupported = EventsSupported;
            CSSupported = CommandsSupported;
            ISSupported = InformationSupported;
        }

        /// <summary>
        /// Special deserialization constructor using a byte, which corresponds to the 8 bits that compose tihs object.
        /// </summary>
        /// <param name="b">Serialized Link_MIHCap_Flag.</param>
        public Link_MIHCap_Flag(byte b)
        {
            byte[] bytes = { b };
            BitArray data = new BitArray(bytes);
            Utilities.Utilities.ReverseBitArray(data);
            //Reserved
            bit0 = data[0];
            bit4 = data[4];
            bit5 = data[5];
            bit6 = data[6];
            bit7 = data[7];

            ESSupported = data[1];
            CSSupported = data[2];
            ISSupported = data[3];
        }

        /// <summary>
        /// Deserialization constructor for this object.
        /// </summary>
        /// <param name="bytes">Raw serialized Link_MIHCap_Flag object.</param>
        public Link_MIHCap_Flag(byte[] bytes)
        {
            BitArray data = new BitArray(bytes);
            Utilities.Utilities.ReverseBitArray(data);
            //Reserved
            bit0 = data[0];
            bit4 = data[4];
            bit5 = data[5];
            bit6 = data[6];
            bit7 = data[7];

            ESSupported = data[1];
            CSSupported = data[2];
            ISSupported = data[3];
        }
    }

    /// <summary>
    /// Representation of the Net_Caps object. Represents Network Capabilities.
    /// </summary>
    public class Net_Caps //bitmap(32)
    {
        /// <summary>
        /// Reserved Bits (10-31)
        /// </summary>
        public BitArray reserved = new BitArray(22);

        /// <summary>
        /// Whether or not network security is supported.
        /// </summary>
        public bool Security { get; set; }
        /// <summary>
        /// Whether or not QoS class 0 is supported.
        /// </summary>
        public bool QoS0 { get; set; }
        /// <summary>
        /// Whether or not QoS class 1 is supported.
        /// </summary>
        public bool QoS1 { get; set; }
        /// <summary>
        /// Whether or not QoS class 2 is supported.
        /// </summary>
        public bool QoS2 { get; set; }
        /// <summary>
        /// Whether or not QoS class 3 is supported.
        /// </summary>
        public bool QoS3 { get; set; }
        /// <summary>
        /// Whether or not QoS class 4 is supported.
        /// </summary>
        public bool QoS4 { get; set; }
        /// <summary>
        /// Whether or not QoS class 5 is supported.
        /// </summary>
        public bool QoS5 { get; set; }
        /// <summary>
        /// Whether or not Internet Access is supported.
        /// </summary>
        public bool InternetAccess { get; set; }
        /// <summary>
        /// Whether or not Emergency Services are supported.
        /// </summary>
        public bool EmergencyServices { get; set; }
        /// <summary>
        /// Whether or not MIH is supported.
        /// </summary>
        public bool MIHSupport { get; set; }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Overloaded ToString() method.
        /// </summary>
        /// <param name="prefix">String to be written at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Net_Caps");
            sb.AppendLine(prefix + "{");
            sb.Append(prefix + "\tSecurity: " + (Security?"Yes": "No"));
            sb.AppendLine("\tQoS0: " + (QoS0?"Yes": "No"));
            sb.Append(prefix + "\tQoS2: " + (QoS2?"Yes": "No"));
            sb.AppendLine("\tQoS3: " + (QoS3?"Yes": "No"));
            sb.Append(prefix + "\tQoS4: " + (QoS4?"Yes": "No"));
            sb.AppendLine("\tQoS5: " + (QoS5?"Yes": "No"));
            sb.AppendLine(prefix+"\tInternet Access: " + (InternetAccess?"Yes":"No"));
            sb.AppendLine(prefix+"\tEmergency Services: " + (EmergencyServices?"Yes":"No"));
            sb.AppendLine(prefix+"\tMIH Support: " + (MIHSupport?"Yes":"No"));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }

        /// <summary>
        /// Serialized version of this object.
        /// </summary>
        public byte[] ByteValue { get { return getByteVal(); } }
        private byte[] getByteVal()
        {
            BitArray all = new BitArray(32);
            all.Set(0, Security);
            all.Set(1, QoS0);
            all.Set(2, QoS1);
            all.Set(3, QoS2);
            all.Set(4, QoS3);
            all.Set(5, QoS4);
            all.Set(6, QoS5);
            all.Set(7, InternetAccess);
            all.Set(8, EmergencyServices);
            all.Set(9, MIHSupport);
            for (int i = 0, j = 10; j < 32; i++, j++)
                all.Set(j, reserved.Get(i));
            Utilities.Utilities.ReverseBitArray(all);
            return Utilities.Utilities.ToByteArray(all);
        }

        /// <summary>
        /// Standard constructor for the NetCaps object.
        /// </summary>
        /// <param name="sec">Security services support.</param>
        /// <param name="qos0">QoS class 0 support.</param>
        /// <param name="qos1">QoS class 1 support.</param>
        /// <param name="qos2">QoS class 2 support.</param>
        /// <param name="qos3">QoS class 3 support.</param>
        /// <param name="qos4">QoS class 4 support.</param>
        /// <param name="qos5">QoS class 5 support.</param>
        /// <param name="internet">Internet access support.</param>
        /// <param name="emergency">Emergency services support.</param>
        /// <param name="mih">MIH support.</param>
        public Net_Caps(bool sec, bool qos0, bool qos1, bool qos2, bool qos3, bool qos4, bool qos5, bool internet, bool emergency, bool mih)
        {
            Security = sec;
            QoS0 = qos0;
            QoS1 = qos1;
            QoS2 = qos2;
            QoS3 = qos3;
            QoS4 = qos4;
            QoS5 = qos5;
            InternetAccess = internet;
            EmergencyServices = emergency;
            MIHSupport = mih;

            reserved.SetAll(false);
        }

        /// <summary>
        /// Deserialization constructor.
        /// </summary>
        /// <param name="bytes">Raw serialized Net_Caps object.</param>
        public Net_Caps(byte[] bytes)
        {
            byte[] reversedBytes = new byte[4];
            for (int j = 0; j < 4; j++)
                reversedBytes[j] = bytes[3 - j];
            BitArray data = new BitArray(reversedBytes);
            //Utilities.Utilities.ReverseBitArray(data);
            int i = 0;
            Security = data[i++];
            QoS0 = data[i++];
            QoS1 = data[i++];
            QoS2 = data[i++];
            QoS3 = data[i++];
            QoS4 = data[i++];
            QoS5 = data[i++];
            InternetAccess = data[i++];
            EmergencyServices = data[i++];
            MIHSupport = data[i++];
            for(int j = 0; j<12; j++)
                reserved[j]= data[i++];
        }

    }

    /// <summary>
    /// Class representing a Link_Det_Info object
    /// </summary>
    public class Link_Det_Info
    {
        /// <summary>
        /// The dectected Link.
        /// </summary>
        public Link_Tuple_Id LinkTuppleId { get; set; }
        /// <summary>
        /// The access network identifier.
        /// </summary>
        public OctetString NetworkID { get; set; }
        /// <summary>
        /// An auxiliary access network identifier if applicable.
        /// </summary>
        public OctetString NetworkAuxId { get; set; }
        /// <summary>
        /// The signal strength of the detected link (in percentage).
        /// </summary>
        public uint SigStrInPc { get; set; } //CHOICE(INTEGER(1)[indbm], PERCENTAGE)
        /// <summary>
        /// The signal strength of the detected link (in dBm).
        /// </summary>
        public int SigStrInDbm { get; set; } //
        /// <summary>
        /// The Signal/Noise ratio.
        /// </summary>
        public int SINR { get; set; }
        /// <summary>
        /// The maximum transmission rate on the detected link.
        /// </summary>
        public int LinkDataRate { get; set; }
        /// <summary>
        /// Indicates which MIH capabilities are supported on the detected link.
        /// </summary>
        public Link_MIHCap_Flag LinkMIHCapFlag { get; set; }
        /// <summary>
        /// The network capabilities supported by the network link.
        /// </summary>
        public Net_Caps NetCaps { get; set; }

        /// <summary>
        /// A string representation of this object.
        /// </summary>
        /// <returns>A string form of this Link_Det_Info object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// A string representation of this object.
        /// </summary>
        /// <param name="prefix">A string to be shown at the start of every line of the representation.</param>
        /// <returns>A string form of this Link_Det_Info object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Det_Info");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tLink Id: " + this.LinkTuppleId.ToString(prefix + "\t"));
            sb.AppendLine(prefix + "\tNetwork ID: " + NetworkID.StringValue);
            sb.AppendLine(prefix + "\tNetwork HESSID: " + NetworkAuxId.StringValue);
            sb.AppendLine(prefix + "\tSignal Strength: " + SigStrInPc+"%");
            sb.AppendLine(prefix + "\tSignal/Noise Ratio: " + SINR);
            sb.AppendLine(prefix + "\tData Rate: " + LinkDataRate);
            sb.AppendLine(prefix + "\tMIH Capabilities: " + this.LinkMIHCapFlag.ToString(prefix+"\t"));
            sb.AppendLine(prefix + "\tNetwork Capabilities: " + this.NetCaps.ToString(prefix+"\t"));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }

        /// <summary>
        /// Normal constructor for this object.
        /// </summary>
        /// <param name="lti">The link detected.</param>
        /// <param name="nid">The access network identifier if applicable.</param>
        /// <param name="naid">An auxiliary access network identifier if applicable.</param>
        /// <param name="sigStrPc">The signal strength of the detected link (in percentage).</param>
        /// <param name="sigStrDbm">The signal strength of the detected link (in dBm).</param>
        /// <param name="sinr">The Signal/Noise ratio.</param>
        /// <param name="ldr">The maximum transmission rate on the detected link.</param>
        /// <param name="lmcf">Indicates which MIH capabilities are supported on the detected link.</param>
        /// <param name="nc">The network capabilities supported by the network link.</param>
        public Link_Det_Info(Link_Tuple_Id lti, OctetString nid, OctetString naid, uint sigStrPc, int sigStrDbm, int sinr, int ldr, Link_MIHCap_Flag lmcf, Net_Caps nc)
        {
            this.LinkTuppleId = lti;
            this.NetworkID = nid;
            this.NetworkAuxId = naid;
            this.SigStrInPc = sigStrPc;
            this.SigStrInDbm = sigStrDbm;
            this.SINR = sinr;
            this.LinkDataRate = ldr;
            this.LinkMIHCapFlag = lmcf;
            this.NetCaps = nc;
        }

        /// <summary>
        /// Serialized version of this object.
        /// </summary>
        public byte[] ByteVal
        {
            get { return GenerateValue(); }
        }

        /// <summary>
        /// Deserialization constructor.
        /// </summary>
        /// <param name="data">The serialized Link_Det_Info object as raw bytes.</param>
        public Link_Det_Info(byte[] data)
        {
            BitArray bitData = new BitArray(data);
            int atByte = 0;
            this.LinkTuppleId = new Link_Tuple_Id(data);
            atByte+= this.LinkTuppleId.ByteValue.Length;
            this.NetworkID = new OctetString(data.Skip(atByte).Take(data[atByte] + 1).ToArray());
            atByte += data[atByte] + 1;
            this.NetworkAuxId = new OctetString(data.Skip(atByte).Take(data[atByte] + 1).ToArray());
            atByte += data[atByte] + 1;
            switch (data[atByte++])
            {
                case TLV_VALUES.CHOICE_SIG_STR_PERCENTAGE: this.SigStrInPc = data[atByte++];
                    break;
                case TLV_VALUES.CHOICE_SIG_STR_DBM: this.SigStrInDbm = data[atByte++];
                    break;
            }
            byte[] sinrInBytes = new byte[2];
            sinrInBytes[1] = data[atByte++];
            sinrInBytes[0] = data[atByte++];
            this.SINR = BitConverter.ToInt16(sinrInBytes,0);
            byte[] dataRateInBytes = new byte[4];
            dataRateInBytes[3] = data[atByte++];
            dataRateInBytes[2] = data[atByte++];
            dataRateInBytes[1] = data[atByte++];
            dataRateInBytes[0] = data[atByte++];
            this.LinkDataRate = BitConverter.ToInt32(dataRateInBytes, 0);
            this.LinkMIHCapFlag = new Link_MIHCap_Flag(data[atByte++]);
            this.NetCaps = new Net_Caps(data.Skip(atByte).ToArray());

        }

        private byte[] GenerateValue()
        {
            byte[] sigStrInBytes = new byte[1];
            sigStrInBytes[0] = BitConverter.GetBytes(SigStrInPc)[0];
            byte[] sinrInBytes = new byte[2];
            sinrInBytes[0] = 0;
            sinrInBytes[1] = 0;

            return Serialization.Sequence(
                /*Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_IDENTIFIER, LinkTuppleId.ByteValue),*/
                LinkTuppleId.ByteValue,
                NetworkID.ByteValue,
                NetworkAuxId.ByteValue,
                Serialization.Choice(sigStrInBytes, TLV_VALUES.CHOICE_SIG_STR_PERCENTAGE),
                sinrInBytes,
                BitConverter.GetBytes(LinkDataRate).Reverse().ToArray(),
                LinkMIHCapFlag.ByteValue,
                NetCaps.ByteValue);
        }
    }

    /*class Link_Action_Req
    {
        Link_Id LinkId;
        Link_Addr PoALinkAddr; //CHOICE (NULL, Link_Addr)
        Link_Action LinkAction;
        UInt16 Link_Ac_Ex_Time;

        public Link_Action_Req(Link_Id lid, Link_Addr laddr, Link_Action lact, UInt16 lextime)
        {
            this.LinkId = lid;
            this.PoALinkAddr = laddr;
            this.LinkAction = lact;
            this.Link_Ac_Ex_Time = lextime;
        }

        public Link_Action_Req(byte[] data)
        {
            //STRUCTURE: [ 59(MN Link ID) Length Val...Val | 0/1 [1-> 60 Length Val...Val] | LinkAction(2bytes) | LinkAcExTime(2bytes)]

            int[] offsets = new int[4];
            if (data[0] != TLV_VALUES.TLV_MN_LINK_ID)
                throw new InvalidOperationException("Wrong formatting of Link_Action_Req TLV");
            offsets[0] = 2;
            offsets[1] = offsets[0] + data[1]; //Length
            offsets[2] = data[offsets[1]]==0 ? offsets[1]+1 : offsets[1]+data[offsets[1]+2]+1;
            offsets[3] = offsets[2] + 2;
            //this.LinkId = MIHDeserializer.DeserializeLinkId(data.Skip(offsets[0]).Take(offsets[0]-1).ToArray());
            //this.PoALinkAddr = MIHDeserializer.DeserializeLinkId(stuffgoeshere);
            //this.LinkAction = MIHDeserializer.DeserializeLinkId(stuffgoeshere);
            //this.Link_Ac_Ex_Time = (ushort)BitConverter.ToInt16(data, data.Length-2);
        }

        public byte[] ByteValue { get { return getBytes(); } }

        public byte[] getBytes()
        {
            TLV_HELPERS.TLVLinkId(LinkId);
            Serialization.Choice(TLV_HELPERS.TLVPoALinkAddress(PoALinkAddr), 1);
            //LinkAction.ByteValue
            return null;

        }

    }*/

    /// <summary>
    /// Class representing a response to a Link_Scan_Request.
    /// </summary>
    public class Link_Scan_Rsp
    {
        /// <summary>
        /// The PoA Link Address.
        /// </summary>
        public Link_Addr linkAddr { get; set; }
        /// <summary>
        /// The associated Network ID.
        /// </summary>
        public OctetString NetworkID { get; set; }
        /// <summary>
        /// The signal strength for the given network ID, coming from the given PoA.
        /// </summary>
        public ushort Sig_Strength { get; set; }

        /// <summary>
        /// Default constructor for the Link_Scan_Rsp.
        /// </summary>
        /// <param name="la">The PoA link address.</param>
        /// <param name="nid">The network ID.</param>
        /// <param name="ss">The signal strength for the specified network ID.</param>
        public Link_Scan_Rsp(Link_Addr la, OctetString nid, ushort ss)
        {
            this.linkAddr = la;
            this.NetworkID = nid;
            this.Sig_Strength = ss;
        }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Overloaded ToString() method.
        /// </summary>
        /// <param name="prefix">String to be written at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Scan_Rsp");
            sb.AppendLine(prefix + "{");
            sb.Append(prefix+"\tPoint of Access: "+linkAddr.ToString(prefix+"\t"));
            sb.AppendLine(prefix + "\tNetwork ID: {" + NetworkID.StringValue.TrimEnd((char)0) + "}");
            sb.AppendLine(prefix + "\tSignal Strength: " + Sig_Strength + "%");
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }

        /// <summary>
        /// Serialzied byte[] representation for this object.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                byte[] data = new byte[linkAddr.ByteValue.Length+NetworkID.ByteValue.Length+1];
                int i = 0;
                for (int j = 0; j<linkAddr.ByteValue.Length; j++)
                    data[i++] = linkAddr.ByteValue[j];
                for (int j = 0; j<NetworkID.ByteValue.Length; j++)
                    data[i++] = NetworkID.ByteValue[j];
                data[i++] = BitConverter.GetBytes(Sig_Strength)[0];
                return data;
            }
        }

        /// <summary>
        /// Deserialization constructor.
        /// </summary>
        /// <param name="data">Raw serialized Link_Scan_Rsp object.</param>
        public Link_Scan_Rsp(byte[] data)
        {
            int bytePointer = 0;
            ushort linkAddrType = data[bytePointer++];

            switch ((Link_Addr.Address_Type)linkAddrType)
            {
                case Link_Addr.Address_Type.MAC_ADDR: this.linkAddr =  new Link_Addr((Link_Addr.Address_Type)linkAddrType,
                                        new String(Encoding.ASCII.GetChars(data.Skip(bytePointer+3).Take(data[bytePointer+2]).ToArray())));
                                        bytePointer += 3 + data[bytePointer + 2];
                                        break;
                default: this.linkAddr = new Link_Addr((Link_Addr.Address_Type)linkAddrType,
                                        new String(Encoding.ASCII.GetChars(data.Skip(bytePointer+1).Take(data[bytePointer]).ToArray())));
                                        bytePointer += 1 + data[bytePointer];
                                        break;
            }

            this.NetworkID = new OctetString(data.Skip(bytePointer).Take(data[bytePointer]+1).ToArray());
            bytePointer += data[bytePointer] + 1 ;

            this.Sig_Strength = data[bytePointer];
        }
    }

    /// <summary>
    /// A class representing a Link_Event_List.
    /// </summary>
    public class Link_Event_List
    {
        /// <summary>
        /// Converts this Link_Event_List into a BitArray.
        /// </summary>
        /// <returns></returns>
        public BitArray toBitArray()
            {
                BitArray bm = new BitArray(32);
                bm[0] = Link_Detected;
                bm[1] = Link_Up;
                bm[2] = Link_Down;
                bm[3] = Link_Parameters_Report;
                bm[4] = Link_Going_Down;
                bm[5] = Link_Handover_Imminent;
                bm[6] = Link_Handover_Complete;
                bm[7] = Link_PDU_Transmit_Status;
                for (int i = 8; i < 32; i++)
                    bm[i] = bit8to31[i - 8];
                Utilities.Utilities.ReverseBitArray(bm);
                return bm;
            }

        /// <summary>
        /// Serialized version of this instance.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                return Utilities.Utilities.ToByteArray(this.toBitArray());
            }
        }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Overloaded ToString method.
        /// </summary>
        /// <param name="prefix">A string to be printed at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Event_List");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tLink_Detected: " + (this.Link_Detected ? 1 : 0));
            sb.AppendLine(prefix + "\tLink_Up: " + (this.Link_Up ? 1 : 0));
            sb.AppendLine(prefix + "\tLink_Down: " + (this.Link_Down ? 1 : 0));
            sb.AppendLine(prefix + "\tLink_Parameters_Report: " + (this.Link_Parameters_Report ? 1 : 0));
            sb.AppendLine(prefix + "\tLink_Going_Down: " + (this.Link_Going_Down ? 1 : 0));
            sb.AppendLine(prefix + "\tLink_Handover_Imminent: " + (this.Link_Handover_Imminent ? 1 : 0));
            sb.AppendLine(prefix + "\tLink_Handover_Complete: " + (this.Link_Handover_Complete ? 1 : 0));
            sb.AppendLine(prefix + "\tLink_PDU_Transmit_Status: " + (this.Link_PDU_Transmit_Status ? 1 : 0));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }
        /// <summary>
        /// Reserved bits (8-31) that are unused for now.
        /// </summary>
        public BitArray bit8to31 { get; set; }
        /// <summary>
        /// Whether or not the Link_Detected event is supported.
        /// </summary>
        public bool Link_Detected { get; set; }
        /// <summary>
        /// Whether or not the Link_Up event is supported.
        /// </summary>
        public bool Link_Up { get; set; }
        /// <summary>
        /// Whether or not the Link_Down event is supported.
        /// </summary>
        public bool Link_Down { get; set; }
        /// <summary>
        /// Whether or not the Link_Parameters_Report event is supported.
        /// </summary>
        public bool Link_Parameters_Report { get; set; }
        /// <summary>
        /// Whether or not the Link_Going_Down event is supported.
        /// </summary>
        public bool Link_Going_Down { get; set; }
        /// <summary>
        /// Whether or not the Link_Handover_Imminent event is supported.
        /// </summary>
        public bool Link_Handover_Imminent { get; set; }
        /// <summary>
        /// Whether or not the Link_Handover_Complete event is supported.
        /// </summary>
        public bool Link_Handover_Complete { get; set; }
        /// <summary>
        /// Whether or not the Link_PDU_Transmit_Status event is supported.
        /// </summary>
        public bool Link_PDU_Transmit_Status { get; set; }

        /// <summary>
        /// Empty Constructor
        /// </summary>
        public Link_Event_List() { bit8to31 = new BitArray(24); bit8to31.SetAll(false); }

        /// <summary>
        /// Link_Event_List constructor.
        /// </summary>
        /// <param name="linkEventList">The LinkEventList.</param>
        public Link_Event_List(BitArray linkEventList)
        {
            Utilities.Utilities.ReverseBitArray(linkEventList);
            Link_Detected = linkEventList[0];
            Link_Up = linkEventList[1];
            Link_Down = linkEventList[2];
            Link_Parameters_Report = linkEventList[3];
            Link_Going_Down = linkEventList[4];
            Link_Handover_Imminent = linkEventList[5];
            Link_Handover_Complete = linkEventList[6];
            Link_PDU_Transmit_Status = linkEventList[7];
            bit8to31 = new BitArray(24);
            for (int i = 8; i < 32; i++)
                bit8to31[i - 8] = linkEventList[i];
        }

        /// <summary>
        /// Detailed Link_Event_List constructor.
        /// </summary>
        /// <param name="linkDet">Subscription of the Link_Detected event.</param>
        /// <param name="linkUp">Subscription of the Link_Up event.</param>
        /// <param name="linkDn">Subscription of the Link_Down event.</param>
        /// <param name="linkParam">Subscription of the Link_Parameters_Report event.</param>
        /// <param name="linkGD">Subscription of the Link_Going_Down event.</param>
        /// <param name="linkHI">Subscription of the Link_Handover_Imminent event.</param>
        /// <param name="linkHC">Subscription of the Link_Handover_Complete event.</param>
        /// <param name="linkPDU">Subscription of the Link_PDU_Transmit_Status event.</param>
        public Link_Event_List(bool linkDet, bool linkUp, bool linkDn, bool linkParam, bool linkGD, bool linkHI, bool linkHC, bool linkPDU)
        {
            Link_Detected = linkDet;
            Link_Up = linkUp;
            Link_Down = linkDn;
            Link_Parameters_Report = linkParam;
            Link_Going_Down = linkGD;
            Link_Handover_Imminent = linkHI;
            Link_Handover_Complete = linkHC;
            Link_PDU_Transmit_Status = linkPDU;
            bit8to31 = new BitArray(24);
            bit8to31.SetAll(false);
        }

        /// <summary>
        /// Constructor for a serialized Link_Event_Subscribe_Request
        /// </summary>
        /// <param name="data">The serialized (byte array) Link_Event_List (should be 32 bits).</param>
        public Link_Event_List(byte[] data) : this(new BitArray(data.Reverse().ToArray()))
        { }

    }

    #endregion

    #region MIH_Events

    /// <summary>
    /// This class represents the Link_Event_Subscribe request.
    /// </summary>
    public class Link_Event_Subscribe_Request
    {
        /// <summary>
        /// This parameter represents the LinkEventList.
        /// </summary>
        public Link_Event_List EventList {get;set;}

        /// <summary>
        /// Link_Event_Subscribe_Request constructor.
        /// </summary>
        /// <param name="linkEventList">The LinkEvent List in BitArray form.</param>
        public Link_Event_Subscribe_Request(BitArray linkEventList)
        {
            this.EventList = new Link_Event_List(linkEventList);
        }

        /// <summary>
        /// Link_Event_Subscribe_Request constructor.
        /// </summary>
        /// <param name="linkEventList">The LinkEvent List.</param>
        public Link_Event_Subscribe_Request(Link_Event_List linkEventList)
        {
            this.EventList = linkEventList;
        }

        /// <summary>
        /// Detailed Link_Event_Subscribe_Request constructor.
        /// </summary>
        /// <param name="linkDet">Subscription of the Link_Detected event.</param>
        /// <param name="linkUp">Subscription of the Link_Up event.</param>
        /// <param name="linkDn">Subscription of the Link_Down event.</param>
        /// <param name="linkParam">Subscription of the Link_Parameters_Report event.</param>
        /// <param name="linkGD">Subscription of the Link_Going_Down event.</param>
        /// <param name="linkHI">Subscription of the Link_Handover_Imminent event.</param>
        /// <param name="linkHC">Subscription of the Link_Handover_Complete event.</param>
        /// <param name="linkPDU">Subscription of the Link_PDU_Transmit_Status event.</param>
        public Link_Event_Subscribe_Request(bool linkDet, bool linkUp, bool linkDn, bool linkParam, bool linkGD, bool linkHI, bool linkHC, bool linkPDU)
        {
            this.EventList = new Link_Event_List(linkDet, linkUp, linkDn, linkParam, linkGD, linkHI, linkHC, linkPDU);
        }

        /// <summary>
        /// Link_Event_Subscribe_Request alternative Constructor.
        /// </summary>
        public Link_Event_Subscribe_Request() { }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Overloaded ToString() method.
        /// </summary>
        /// <param name="prefix">String to be written at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Event_Subscribe_Request");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tEventList: " + this.EventList.ToString(prefix + "\t"));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }

    }

    /// <summary>
    /// This class represents the Link_Event_Subscribe Confirmation
    /// </summary>
    public class Link_Event_Subscribe_Confirm
    {
        /// <summary>
        /// The Status of the operation.
        /// </summary>
        public STATUS Status { get; set; }

        /// <summary>
        /// This parameter represents the LinkEvent List of successfully subscribed events, represented as a BitArray.
        /// </summary>
        public Link_Event_List LinkEventList { get; set; }

        /// <summary>
        /// Link_Event_Subscribe_Confirm main constructor.
        /// </summary>
        /// <param name="status">The Status of the operation.</param>
        /// <param name="linkEventList">The LinkEvent EventList of sucessfully subscribed events.</param>
        public Link_Event_Subscribe_Confirm(STATUS status, Link_Event_List linkEventList)
        {
            this.Status = status;
            this.LinkEventList = linkEventList;
        }

        /// <summary>
        /// Link_Event_Subscribe_Confirm empty constructor.
        /// </summary>
        public Link_Event_Subscribe_Confirm() { }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Overloaded ToString() method.
        /// </summary>
        /// <param name="prefix">String to be written at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Event_Subscribe_Confirm");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tStatus: " + this.Status);
            sb.AppendLine(prefix + "\tEventList: " + this.LinkEventList.ToString(prefix + "\t"));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }
    }

    /// <summary>
    /// This class represents the Link_Event_Unsubscribe Request
    /// </summary>
    public class Link_Event_Unsubscribe_Request : Link_Event_Subscribe_Request
    {
        private Link_Event_List link_Event_List;

        /// <summary>
        /// Link_Event_Unsubscribe_Request main constructor.
        /// </summary>
        /// <param name="linkEventList">The EventList of LinkEvents to be unsubscribed.</param>
        public Link_Event_Unsubscribe_Request(BitArray linkEventList)
            : base(linkEventList)
        { }

        /// <summary>
        /// Link_Event_Unsubscribe_Request empty constructor.
        /// </summary>
        public Link_Event_Unsubscribe_Request()
        { }

        /// <summary>
        /// Default constructor for this object.
        /// </summary>
        /// <param name="link_Event_List">The Link_Event_List to be unsusbscribed.</param>
        public Link_Event_Unsubscribe_Request(Link_Event_List link_Event_List)
        {
            this.link_Event_List = link_Event_List;
        }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Overloaded ToString() method.
        /// </summary>
        /// <param name="prefix">String to be written at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        new public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Event_Unsubscribe_Request");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tEventList: " + this.EventList.ToString(prefix + "\t"));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }
    }

    /// <summary>
    /// This class represents the Link_Event_Unsubscribe Confirmation.
    /// </summary>
    public class Link_Event_Unsubscribe_Confirm : Link_Event_Subscribe_Confirm
    {

        /// <summary>
        /// Link_Event_Unsubscribe_Confirm empty constructor.
        /// </summary>
        public Link_Event_Unsubscribe_Confirm()
        { }

        /// <summary>
        /// Default constructor for this object.
        /// </summary>
        /// <param name="status">The status of the unsubscribe action.</param>
        /// <param name="link_Event_List">The unsubscribed Link_Events list.</param>
        public Link_Event_Unsubscribe_Confirm(STATUS status, Link_Event_List link_Event_List)
        {
            this.Status = status;
            this.LinkEventList = link_Event_List;
        }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Overloaded ToString() method.
        /// </summary>
        /// <param name="prefix">String to be written at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        new public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Event_Unsubscribe_Confirm");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tStatus: " + this.Status);
            sb.AppendLine(prefix + "\tEventList: " + this.LinkEventList.ToString(prefix + "\t"));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }
    }

    /// <summary>
    /// Primary class for Link_Event
    /// </summary>
    public class Link_Event
    {
        /// <summary>
        /// Identifier of the link associated with the event.
        /// </summary>
        public Link_Tuple_Id LinkIdentifier { get; set; }

        /// <summary>
        /// The Link Event Base Class constructor.
        /// </summary>
        /// <param name="LinkIdentifier"></param>
        public Link_Event(Link_Tuple_Id LinkIdentifier)
        {
            this.LinkIdentifier = LinkIdentifier;
        }

    }

    /// <summary>
    /// Class that represents the Link_Up.Indication, according to IEEE 802.21 specification.
    /// (OBS: IPRenewalFlag and MobilityManagementSupport attributes Not Implemented in this version.)
    /// </summary>
    public class Link_Up : Link_Event
    {

        /// <summary>
        /// Old Access Router link address
        /// </summary>
        public Link_Addr OldAccessRouter { get; set; }

        /// <summary>
        /// New Access Router link address
        /// </summary>
        public Link_Addr NewAccessRouter { get; set; }


        //IPRenewalFlag Not Implemented in this version
        //MobilityManagementSupport Not Implemented in this version


        /// <summary>
        /// Link UP Event Class constructor.
        /// </summary>
        /// <param name="LinkIdentifier">The Link Identifier.</param>
        /// <param name="OldAccessRouter">The Old Access Router Address.</param>
        /// <param name="NewAccessRouter">The New Access Router Address.</param>
        public Link_Up(Link_Tuple_Id LinkIdentifier, Link_Addr OldAccessRouter, Link_Addr NewAccessRouter)
            : base(LinkIdentifier)
        {
            this.NewAccessRouter = NewAccessRouter;
            this.OldAccessRouter = OldAccessRouter;
        }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Overloaded ToString() method.
        /// </summary>
        /// <param name="prefix">String to be written at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Up");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tLinkID: " + this.LinkIdentifier.ToString(prefix+"\t"));
            sb.AppendLine(prefix + "\tOld Access Router: " + OldAccessRouter);
            sb.AppendLine(prefix + "\tNew Access Router: " + NewAccessRouter);
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }
    }

    /// <summary>
    /// Class representing a Link_Detected message.
    /// </summary>
    public class Link_Detected
    {
        /// <summary>
        /// The information of the link.
        /// </summary>
        public Link_Det_Info Info { get; set; }

        /// <summary>
        /// Standard constructor.
        /// </summary>
        /// <param name="lInfo"></param>
        public Link_Detected(Link_Det_Info lInfo)
        {
            this.Info = lInfo;
        }

        /// <summary>
        /// Represents this object as a string.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Represents this object as a string.
        /// </summary>
        /// <param name="prefix">A string to be written at the beggining of every line of this representation.</param>
        /// <returns>A string representation of this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Detected");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tInfo: " + this.Info.ToString(prefix + "\t"));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }
    }

    /// <summary>
    /// This class represents the Link_Down.Indication, according to IEE 802.21 specification.
    /// </summary>
    public class Link_Down : Link_Event
    {

        /// <summary>
        /// Old Access Router link address.
        /// </summary>
        public Link_Addr OldAccessRouter { get; set; }

        /// <summary>
        /// Reason why the link went down.
        /// </summary>
        public Link_Dn_Reason ReasonCode { get; set; }

        /// <summary>
        /// The Link Down Event Class constructor.
        /// </summary>
        /// <param name="LinkIdentifier">The Link Identifier.</param>
        /// <param name="OldAccessRouter">The Old Access Router Address.</param>
        /// <param name="ReasonCode">The Reason Code, for the link down event.</param>
        public Link_Down(Link_Tuple_Id LinkIdentifier, Link_Addr OldAccessRouter, Link_Dn_Reason ReasonCode)
            : base(LinkIdentifier)
        {
            this.OldAccessRouter = OldAccessRouter;
            this.ReasonCode = ReasonCode;
        }

        /// <summary>
        /// Overrided ToString() method.
        /// </summary>
        /// <returns>A string representation of the LinkDown instance.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Auxiliary ToString() method.
        /// </summary>
        /// <param name="prefix">A string to be written at the beggining of every line of this string representation.</param>
        /// <returns>A string representation of the LinkDown instance.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Down");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tLinkID: " + this.LinkIdentifier.ToString(prefix + "\t"));
            sb.AppendLine(prefix + "\tOld Access Router: " + OldAccessRouter);
            sb.AppendLine(prefix + "\tReason: " + ReasonCode);
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }
    }

    #endregion
}
