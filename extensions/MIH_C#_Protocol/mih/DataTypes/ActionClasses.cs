//==============================================================================
// Brief   : Class representing a ActionClasses.cs entity
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
using System.Collections;


namespace MIH.DataTypes
{
    /// <summary>
    /// Contains the multiple link actions.
    /// </summary>
    public enum Actions
    {
        /// <summary>
        /// Disconnect the link connection directly.
        /// </summary>
        LINK_DISCONNECT,
        /// <summary>
        /// Cause the link to adjust its battery power level to be low power consumption.
        /// </summary>
        LINK_LOW_POWER,
        /// <summary>
        /// Cause the link to power down and turn off the radio.
        /// </summary>
        LINK_POWER_DOWN,
        /// <summary>
        /// Cause the link to power up and establish L2 connectivity.
        /// </summary>
        LINK_POWER_UP
    }

    /// <summary>
    /// Class representing a Link_Action_Response object.
    /// </summary>
    public class Link_Action_Response
    {
        /// <summary>
        /// The status associated with this response.
        /// </summary>
        public STATUS Status { get; set; }
        /// <summary>
        /// A list of Link_Scan_Rsp representing the results of the scan results.
        /// </summary>
        public List<Link_Scan_Rsp> ScanResults { get; set; }
        /// <summary>
        /// The result of the Link_Action requested on the Link_Action_Request.
        /// </summary>
        public Link_Ac_Result Result { get; set; }

        /// <summary>
        /// Constructor for the Link_Action_Response object.
        /// </summary>
        /// <param name="s">Status for the response.</param>
        /// <param name="scanR">List of serialized Link_Scan_Rsp objects.</param>
        /// <param name="res">Result for the requested Link_Action.</param>
        public Link_Action_Response(STATUS s, List<byte[]> scanR, Link_Ac_Result res)
        {
            Status = s;
            ScanResults = new List<Link_Scan_Rsp>();
            foreach (byte[] bArray in scanR)
            {
                ScanResults.Add(new Link_Scan_Rsp(bArray));
            }
            Result = res;
        }

        /// <summary>
        /// Standard constructor for the Link_Action_Response object.
        /// </summary>
        /// <param name="s">Status for the response.</param>
        /// <param name="scanR">List of Link_Scan_Rsp representing the scan results.</param>
        /// <param name="res">Result for the requested Link_Action</param>
        public Link_Action_Response(STATUS s, List<Link_Scan_Rsp> scanR, Link_Ac_Result res)
        {
            Status = s;
            ScanResults = scanR;
            Result = res;
        }

        /// <summary>
        /// Empty constructor
        /// </summary>
        public Link_Action_Response()
        { }

        /// <summary>
        /// String representation of this object.
        /// </summary>
        /// <returns>Detailed multi-lined description of this object and its components.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// String representation of this object.
        /// </summary>
        /// <param name="prefix">A string to be shown at the begining of every line.</param>
        /// <returns>Detailed multi-lined description of this object and its components.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Action.response");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tStatus: " + Status);
            sb.AppendLine(prefix + "\tResult: " + Result);
            sb.AppendLine(prefix + "\tScan Results (" + ScanResults.Count + "): ");
            sb.AppendLine(prefix + "\t{");
            foreach (Link_Scan_Rsp lsr in ScanResults)
                sb.Append(prefix + "\t" + lsr.ToString(prefix + "\t\t"));
            sb.AppendLine(prefix + "\t}");
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }

        /// <summary>
        /// Serializes all elements of the ScanResults.
        /// </summary>
        /// <returns>A list containing all Link_Scan_Rsp elements in their serialized form.</returns>
        public List<byte[]> scanResultsAsByteArrayList()
        {
            List<byte[]> bList = new List<byte[]>(ScanResults.Count);
            foreach (Link_Scan_Rsp lsr in ScanResults)
                bList.Add(lsr.ByteValue);
            return bList;
        }
    }

    /// <summary>
    /// Class reprenting a Link_Action_Request
    /// </summary>
    public class Link_Action_Request
    {
        /// <summary>
        /// The Action to be requested.
        /// </summary>
        public Link_Action LinkAction { get; set; }
        /// <summary>
        /// The delay (in ms) to be waited before executing this action.
        /// </summary>
        public UInt16 ExecutionDelay { get; set; }
        /// <summary>
        /// The PoA link address to forward data to. This parameter is used when DATA_FWD_REQ action is requested.
        /// </summary>
        public Link_Addr PoALinkAddress { get; set; }

        /// <summary>
        /// Main constructor for the Link_Action_Request object.
        /// </summary>
        /// <param name="lAct">The action to be taken.</param>
        /// <param name="eD">The execution delay.</param>
        /// <param name="lAddr">The link address to redirect the results to [NOT IMPLEMENTED]</param>
        public Link_Action_Request(Link_Action lAct, ushort eD, Link_Addr lAddr)
        {
            LinkAction = lAct;
            ExecutionDelay = eD;
            PoALinkAddress = lAddr;
        }

        /// <summary>
        /// String representation of this object.
        /// </summary>
        /// <returns>Detailed multi-lined description of this object and its components.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// String representation of this object.
        /// </summary>
        /// <param name="prefix">A string to be shown at the begining of every line.</param>
        /// <returns>Detailed multi-lined description of this object and its components.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Action.Request");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tAction: " + LinkAction.ToString(prefix + "\t"));
            sb.AppendLine(prefix + "\tExecution Delay: " + ExecutionDelay + " ms");
            sb.Append(prefix + "\tPoint of Access: ");
            if (PoALinkAddress == null)
                sb.AppendLine("<empty>");
            else
                sb.AppendLine(PoALinkAddress.ToString(prefix + "\t"));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }
    }

    /// <summary>
    /// Class representing a Link_Action object
    /// </summary>
    public class Link_Action
    {
        /// <summary>
        /// The type of action to be taken.
        /// </summary>
        public Link_Ac_Type LinkAcType { get; set; }
        /// <summary>
        /// Additional attributes assiciated with the request.
        /// </summary>
        public Link_Ac_Attr LinkAcAttr { get; set; }

        /// <summary>
        /// String representation of this object.
        /// </summary>
        /// <returns>Detailed multi-lined description of this object and its components.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// String representation of this object.
        /// </summary>
        /// <param name="prefix">A string to be shown at the begining of every line.</param>
        /// <returns>Detailed multi-lined description of this object and its components.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Action");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tType: " + LinkAcType);
            sb.AppendLine(prefix + "\tAttributes: " + LinkAcAttr.ToString());
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }

        /// <summary>
        /// Deserialization constructor for this object.
        /// </summary>
        /// <param name="bytes">Serialized instance of the object.</param>
        public Link_Action(byte[] bytes)
        {
            byte[] aux = new byte[1];
            aux[0] = bytes[1];
            LinkAcAttr = new Link_Ac_Attr(aux);
            LinkAcType = (Link_Ac_Type)bytes[0];
        }

        /// <summary>
        /// Standard consturctor for the Link_Action object.
        /// </summary>
        /// <param name="laa">The link action attributes.</param>
        /// <param name="lat">The link action type.</param>
        public Link_Action(Link_Ac_Attr laa, Link_Ac_Type lat)
        {
            this.LinkAcAttr = laa;
            this.LinkAcType = lat;
        }

        /// <summary>
        /// Serialized form of this object.
        /// </summary>
        public byte[] ByteValue
        {
            get { return getBytes(); }
        }

        private byte[] getBytes()
        {
            byte[] data = new byte[2];
            data[0] = LinkAcAttr.toByte();
            data[1] = (byte)LinkAcType;
            return data;
        }

    }

    /// <summary>
    /// Enum representing the possible results of a Link_Action_Request.
    /// </summary>
    public enum Link_Ac_Result
    {
        /// <summary>
        /// The link action was executed sucessfully.
        /// </summary>
        SUCCESS = 0,
        /// <summary>
        /// The link action's execution has failed.
        /// </summary>
        FAILURE = 1,
        /// <summary>
        /// The request to perform the link action was refused.
        /// </summary>
        REFUSED = 2,
        /// <summary>
        /// The SAP is unable to perform this link action.
        /// </summary>
        INCAPABLE = 3
    }

    /// <summary>
    /// Class associated with the Link_Ac_Attr object. Contains additional requests to be used on a Link_Action_Request.
    /// </summary>
    public class Link_Ac_Attr
    {
        /// <summary>
        /// Whether or not a scan is requested.
        /// </summary>
        public bool Link_Scan { get; set; } //bit0
        /// <summary>
        /// Whether or not the link resources will stay in memory after disconnecting for easier reconnecting. [NOT IMPLEMENTED]
        /// </summary>
        public bool Link_Res_Retain { get; set; } //bit1
        /// <summary>
        /// This indication requires the buffered data at the old serving PoA entity to be forwarded to the new target PoA entity in order to avoid data loss.
        /// </summary>
        public bool Data_Fwd_Req { get; set; } //bit2

        /// <summary>
        /// String representation of this object.
        /// </summary>
        /// <returns>Detailed multi-lined description of this object and its components.</returns>
        public override string ToString()
        {
            return "{Scan: " + (Link_Scan ? 1 : 0) + ", Res_Retain: " + (Link_Res_Retain ? 1 : 0) + ", Data_Fwd_Req: " + (Data_Fwd_Req ? 1 : 0) + "}";
        }

        /// <summary>
        /// Deserialization constructor for the Link_Ac_Attr class.
        /// </summary>
        /// <param name="bytes">Serialized Link_Ac_Attr object.</param>
        public Link_Ac_Attr(byte[] bytes)
        {
            BitArray b = new BitArray(bytes);
            Link_Scan = b.Get(0);
            Link_Res_Retain = b.Get(1);
            Data_Fwd_Req = b.Get(2);
        }

        /// <summary>
        /// Returns a serialized form of this object (a byte, since this object is an 8-element BitMap)
        /// </summary>
        /// <returns></returns>
        public byte toByte()
        {
            BitArray b = new BitArray(8);
            b.SetAll(false);
            b.Set(0, Link_Scan);
            b.Set(1, Link_Res_Retain);
            b.Set(2, Data_Fwd_Req);
            return Utilities.Utilities.ToByteArray(b)[0];
        }
    }

    /// <summary>
    /// Enum representing the type of a Link_Action
    /// </summary>
    public enum Link_Ac_Type
    {
        /// <summary>
        /// No link action.
        /// </summary>
        NONE = 0,
        /// <summary>
        /// A link action request asking for a disconnect.
        /// </summary>
        LINK_DISCONNECT = 1,
        /// <summary>
        /// A link action request asking for the LinkSap interface to switch to power save mode.
        /// </summary>
        LINK_LOW_POWER = 2,
        /// <summary>
        /// A link action request asking do disable the LinkSap interface.
        /// </summary>
        LINK_POWER_DOWN = 3,
        /// <summary>
        /// A link action request asking to enable the LinkSap interface.
        /// </summary>
        LINK_POWER_UP = 4
    }


}
