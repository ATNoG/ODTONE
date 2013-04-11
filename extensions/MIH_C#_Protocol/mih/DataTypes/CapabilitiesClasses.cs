//==============================================================================
// Brief   : Class representing a CapabilitiesClasses.cs entity
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
    /// This enumerator represents the multiple states of an operation, requested by the MIHF.
    /// </summary>
    public enum STATUS
    {
        /// <summary>
        /// The operation was a success.
        /// </summary>
        SUCCESS = 0,
        /// <summary>
        /// The operation result in an unspecified failure.
        /// </summary>
        UNSPECIFIED_FAILURE = 1,
        /// <summary>
        /// The operation was rejected by the request receiver.
        /// </summary>
        REJECTED = 2,
        /// <summary>
        /// The requester does not have permission to execute this operation.
        /// </summary>
        AUTHORIZATION_FAILURE = 3,
        /// <summary>
        /// The operation could not be concluded due to a network error.
        /// </summary>
        NETWORK_ERROR = 4
    }

    /// <summary>
    /// Represents an object of the Link_CMD_List type. A list of commands supported by the link layer.
    /// </summary>
    public class Link_CMD_List
    {
        /// <summary>
        /// If the Link_Event_Subscribe command is supported.
        /// </summary>
        public bool Link_Event_Subscribe {get; set; }
        /// <summary>
        /// If the Link_Event_Unsubscribe command is supported.
        /// </summary>
        public bool Link_Event_Unsubscribe { get; set; }
        /// <summary>
        /// If the Link_Get_Parameters command is supported.
        /// </summary>
        public bool Link_Get_Parameters { get; set; }
        /// <summary>
        /// If the Link_Configure_Thresholds command is supported.
        /// </summary>
        public bool Link_Configure_Thresholds { get; set; }
        /// <summary>
        /// If the Link_Action command is supported.
        /// </summary>
        public bool Link_Action { get; set; }

        /// <summary>
        /// Standard empty constructor.
        /// </summary>
        public Link_CMD_List() { }

        public Link_CMD_List(BitArray b)
        {
            Link_Event_Subscribe = b[1];
            Link_Event_Unsubscribe = b[2];
            Link_Get_Parameters = b[3];
            Link_Configure_Thresholds = b[4];
            Link_Action = b[5];
        }

        /// <summary>
        /// Serialized value of this object.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                BitArray data = new BitArray(32);
                data.SetAll(false);
                data.Set(1, Link_Event_Subscribe);
                data.Set(2, Link_Event_Unsubscribe);
                data.Set(3, Link_Get_Parameters);
                data.Set(4, Link_Configure_Thresholds);
                data.Set(5, Link_Action);
                return MIH.Utilities.Utilities.ToByteArray(data);
            }
        }
    }



    /// <summary>
    /// [NOT IN USE]
    /// This class represents a Link_Capability_Discover.Request
    /// </summary>
    public class Link_Capability_Discover_Request
    {
        /// <summary>
        /// String representation of this object.
        /// </summary>
        /// <returns>String representation of this object.</returns>
        public override string ToString()
        {
            return "LinkCapabilityDiscover.Request";
        }
    }

    /// <summary>
    /// [NOT IN USE]
    /// This class represents a Link_Capability_Discover.Confim
    /// </summary>
    public class Link_Capability_Discover_Confirm
    {
        /// <summary>
        /// The requested operation Status.
        /// </summary>
        public STATUS Status { get; set; }

        /// <summary>
        /// The EventList of supported commands, represented as a BitArray.
        /// </summary>
        public Link_CMD_List LinkCMDList { get; set; }

        /// <summary>
        /// The EventList of supported Events, represented as a BitArray.
        /// </summary>
        public Link_Event_List LinkEventList { get; set; }

        /// <summary>
        /// The Link_Capability_Discover_Confirm constructor.
        /// </summary>
        /// <param name="Status">The operation Status.</param>
        /// <param name="LinkCMDList">The EventList of supported commands.</param>
        /// <param name="LinkEventList">The EventList of link event.</param>
        public Link_Capability_Discover_Confirm(STATUS Status, Link_CMD_List LinkCMDList, Link_Event_List LinkEventList)
        {
            this.Status = Status;
            this.LinkCMDList = LinkCMDList;
            this.LinkEventList = LinkEventList;
        }

        /// <summary>
        /// Link_Capability_Discover_Confirm empty constructor.
        /// </summary>
        public Link_Capability_Discover_Confirm()
        { }

        /// <summary>
        /// Overrided ToString() method.
        /// </summary>
        /// <returns>A string representation of the Link_Capability_Discover_Confirm request.</returns>
        public override string ToString()
        {
            /*StringBuilder sb = new StringBuilder();

            if (LinkEventList != null)
            {
                for (int i = 0; i < LinkEventList.Length; i++)
                {
                    sb.Append(LinkEventList[i] ? "1" : "0");
                }
            }

            sb.Append(", LinkCMDList: ");

            if (LinkCMDList != null)
            {
                for (int i = 0; i < LinkCMDList.Length; i++)
                {
                    sb.Append(this.LinkCMDList[i] ? "1" : "0");
                }
            }*/

            return "LinkCapabilityDiscover.Confim: { Status: " + Status + ", LinkEventList: " + /*sb.ToString() +*/ "[TBI] }";
        }
    }
}
