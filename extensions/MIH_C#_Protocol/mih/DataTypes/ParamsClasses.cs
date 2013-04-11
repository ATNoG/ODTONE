//==============================================================================
// Brief   : Class representing a ParamsClasses.cs entity
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

using MIH.MIHProtocol;

namespace MIH.DataTypes
{
    #region Threshold Enums
    /// <summary>
    /// This enum represents the possible directions of a threshold.
    /// </summary>
    public enum Threshold_X_Dir
    {
        /// <summary>
        /// With above-threshold, the threshold is considered crossed when the obtained value is greater than the specified threshold value.
        /// </summary>
        ABOVE_THRESHOLD = 0,
        /// <summary>
        /// With bellow-threshold, the threshold is considered crossed when the obtained value is less than the specified threshold value.
        /// </summary>
        BELOW_THRESHOLD = 1
    }

    /// <summary>
    /// The type of threshold.
    /// </summary>
    public enum TH_Action
    {
        /// <summary>
        /// With normal threshold, every time that the threshold value is crossed, a notification is sended.
        /// </summary>
        NORMAL_THRESHOLD = 0,
        /// <summary>
        /// With one-shot threshold action, every time the threshold is crossed, a notification is sended and the threshold is cancelled.
        /// </summary>
        ONE_SHOT_THRESHOLD = 1,
        /// <summary>
        /// With cancel-threshold action, the specified thresholds are cancelled.
        /// </summary>
        CANCEL_THRESHOLD = 2
    }
    #endregion

    #region Link_Param Enums

    /// <summary>
    /// An absolute representation of a Link_Param_Type (instead of type + subtype).
    /// </summary>
    public enum Link_Param_Abs_Type
    {
        /// <summary>
        /// The Data Rate parameter type (generic).
        /// </summary>
        GEN_Data_Rate,
        /// <summary>
        /// The Signal Strength parameter type (generic).
        /// </summary>
        GEN_Sig_Strenth,
        /// <summary>
        /// The Signal/Noise ratio parameter type (generic).
        /// </summary>
        GEN_SINR,
        /// <summary>
        /// The throughput parameter (generic).
        /// Throughput stands as "the number of bits successfully received divided by the time it took to transmit them".
        /// </summary>
        GEN_Throughput,
        /// <summary>
        /// The packet error rate parameter (generic).
        /// </summary>
        GEN_Packet_Error_Rate,
        /// <summary>
        /// The RSSI parameter (802.11 specific).
        /// </summary>
        P80211_RSSI,
        /// <summary>
        /// A parameter specifying whether or not QoS services are supported (802.11 specific).
        /// </summary>
        P80211_No_QoS,
        /// <summary>
        /// Parameter specifying the packet loss rate for multicast connections (802.11 specific).
        /// </summary>
        P80211_Multicast_Packet_Loss_Rate,
        /// <summary>
        /// The parameter for the Maximum number of Classes of Service (QoS specific).
        /// </summary>
        QOS_Max_CoS,
        /// <summary>
        /// Parameter for the minimum delay on the connection (QoS specific).
        /// </summary>
        QOS_Min_Delay,
        /// <summary>
        /// Parameter for the average delay on the connection (QoS specific).
        /// </summary>
        QOS_Avg_Delay,
        /// <summary>
        /// Parameter for the maximum delay on the connection (QoS specific).
        /// </summary>
        QOS_Max_Delay,
        /// <summary>
        /// Parameter for the ammount of jitter in the connection (QoS specific).
        /// </summary>
        QOS_Jitter,
        /// <summary>
        /// Parameter for the packet loss rate (QoS specific).
        /// </summary>
        QOS_Packet_Loss_Rate
    }

    /// <summary>
    /// This enum represents the several types of measurable parameters of an interface, according to IEEE 802.21 specification.
    /// </summary>
    public enum Link_Param_Types
    {
        /// <summary>
        /// A type to represent a generic link parameter that is applicable to any link type.
        /// </summary>
        LINK_PARAM_GEN = 0,
        /// <summary>
        /// A type to represent QualityOfSignal parameters.
        /// </summary>
        LINK_PARAM_QOS = 1,
        /// <summary>
        /// A type to represent a link parameter for GSM and GPRS.
        /// </summary>
        LINK_PARAM_GG = 2,
        /// <summary>
        /// A type to represent a link parameter for EDGE.
        /// </summary>
        LINK_PARAM_EDGE = 3,
        /// <summary>
        /// A type to represent a link parameter for Ethernet.
        /// </summary>
        LINK_PARAM_ETH = 4,
        /// <summary>
        /// A type to represent a link parameter for IEEE 802.11.
        /// </summary>
        LINK_PARAM_802_11 = 5,
        /// <summary>
        /// A type to represent a link parameter to CDMA2000.
        /// </summary>
        LINK_PARAM_C2K = 6,
        /// <summary>
        /// A type to represent a link parameter for UMTS.
        /// </summary>
        LINK_PARAM_FDD = 7,
        /// <summary>
        /// A type to represent a link parameter for CDMA2000 HRPD.
        /// </summary>
        LINK_PARAM_HRPD = 8,
        /// <summary>
        /// A type to represent a link parameter to IEEE 802.16.
        /// </summary>
        LINK_PARAM_802_16 = 9,
        /// <summary>
        /// A type to represent a link parameter for IEEE 802.20.
        /// </summary>
        LINK_PARAM_802_20 = 10,
        /// <summary>
        /// A type to represent a link parameter for IEEE 802.22.
        /// </summary>
        LINK_PARAM_802_22 = 11
    }

    /// <summary>
    /// This enum represents the LINK_PARAM_GEN group subtypes.
    /// </summary>
    public enum LINK_PARAM_GEN_SUBTYPES
    {
        /// <summary>
        /// The connection Data Rate expressed in Kb/s.
        /// </summary>
        DataRate = 0,
        /// <summary>
        /// Represents the signal strength in dBm unit or its relative value in a arbitrary percentage scale.
        /// </summary>
        SignalStrength = 1,
        /// <summary>
        /// Represents the connection Signal Over Interference plus Noise Ratio.
        /// </summary>
        SINR = 2,
        /// <summary>
        /// Represents the number of bits sucessfully received divided by the time it took to transmit them over the medium.
        /// </summary>
        Throughtput = 3,
        /// <summary>
        /// Represents the ration between the number of frames received in error and the total number of frames transmitted in a link population of interest (represented as a percentage).
        /// </summary>
        PacketErrorRate = 4
    }

    /// <summary>
    /// This enum represents the LINK_PARAM_802_11 group subtypes.
    /// </summary>
    public enum LINK_PARAM_802_11_SUBTYPES
    {
        /// <summary>
        /// The received signal strength indication of the beacon channel.
        /// </summary>
        RSSI = 0,
        /// <summary>
        /// The QoS availability.
        /// </summary>
        NoQoS = 1,
        /// <summary>
        /// The multicast packet loss rate.
        /// </summary>
        MulticastPacketLossRate = 2
    }

    /// <summary>
    /// This enum represents the LINK_PARAM_QOS group subtypes
    /// </summary>
    public enum LINK_PARAM_QOS_SUBTYPES
    {
        /// <summary>
        /// Maximum number of differentiable classes of service supported.
        /// </summary>
        MaxDifClasses = 0,
        /// <summary>
        /// Minimum packet transfer delay for all CoS, the minimum delay over a class population of interest.
        /// </summary>
        MinTransferDelay = 1,
        /// <summary>
        /// Average packet transfer delay for all CoS, the arithmetic mean of the delay over a class population of interest.
        /// </summary>
        AverageTransferDelay = 2,
        /// <summary>
        /// Maximum packet transfer delay for all CoS, the maximum delay over a class population of interest.
        /// </summary>
        MaxTransferDelay = 3,
        /// <summary>
        /// Packet transfer delay jitter for all CoS, the standard deviation of the delay over a class population of interest.
        /// </summary>
        TransferDelayJitter = 4,
        /// <summary>
        /// Packet loss rate for all CoS, the ratio between the number of frames that are transmitted but not received and the total number of frames transmitted over a class population of interest.
        /// </summary>
        PacketLossRate = 5
    }

    /// <summary>
    /// This enum represents the LINK_PARAM_GG group subtypes.
    /// </summary>
    enum LINK_PARAM_GG_SUBTYPES
    {
        RxQual = 0,
        RsLev = 1,
        MeanBEP = 2,
        StdDev = 3
    }

    /// <summary>
    /// This enumerator represents the different link power modes.
    /// </summary>
    public enum OP_MODES
    {
        NORMAL_MODE = 0,
        POWER_SAVING_MODE = 1,
        POWERED_DOWN = 2,
    }

    #endregion


    /// <summary>
    /// This class represents the association of a LinkParamType and its subtype.
    /// </summary>
    public class Link_Param_Type
    {
        /// <summary>
        /// The LinkParam main type.
        /// </summary>
        public Link_Param_Types Type { get; set; }

        /// <summary>
        /// The LinkParam sub type.
        /// </summary>
        public ushort SubType { get; set; }

        /// <summary>
        /// Link_Param_Type main constructor.
        /// </summary>
        /// <param name="type">The main type.</param>
        /// <param name="subType">The subtype.</param>
        public Link_Param_Type(Link_Param_Types type, ushort subType)
        {
            Type = type;
            SubType = subType;
        }

        /// <summary>
        /// Link_Param_Type deserialization constructor
        /// </summary>
        /// <param name="data"></param>
        public Link_Param_Type(byte[] data)
        {
            this.Type = (Link_Param_Types)data[0];
            this.SubType = data[1];
        }

        /// <summary>
        /// Returns an exact Link_Param_Type (integer-value-wise) according to a Link_Param_Abs_Type.
        /// </summary>
        /// <param name="lpat">The Link_Param_Type from the global enum.</param>
        /// <returns>A Link_ParamType which corresponds to the Link_Param_Abs_Type.</returns>
        public static Link_Param_Type FromAbsType(Link_Param_Abs_Type lpat)
        {
            switch (lpat)
            {
                case Link_Param_Abs_Type.GEN_Data_Rate: return new Link_Param_Type(Link_Param_Types.LINK_PARAM_GEN, (ushort)LINK_PARAM_GEN_SUBTYPES.DataRate);
                case Link_Param_Abs_Type.GEN_Sig_Strenth: return new Link_Param_Type(Link_Param_Types.LINK_PARAM_GEN, (ushort)LINK_PARAM_GEN_SUBTYPES.SignalStrength);
                case Link_Param_Abs_Type.GEN_Packet_Error_Rate: return new Link_Param_Type(Link_Param_Types.LINK_PARAM_GEN, (ushort)LINK_PARAM_GEN_SUBTYPES.PacketErrorRate);
                default: throw new NotImplementedException();
            }
        }

        /// <summary>
        /// Representation of the Link_Param_Type.
        /// </summary>
        public Link_Param_Abs_Type AbsoluteType
        {
            get
            {
                switch (this.Type)
                {
                    case Link_Param_Types.LINK_PARAM_GEN :
                        switch ((LINK_PARAM_GEN_SUBTYPES)SubType)
                        {
                            case LINK_PARAM_GEN_SUBTYPES.DataRate: return Link_Param_Abs_Type.GEN_Data_Rate;
                            case LINK_PARAM_GEN_SUBTYPES.PacketErrorRate: return Link_Param_Abs_Type.GEN_Packet_Error_Rate;
                            case LINK_PARAM_GEN_SUBTYPES.SignalStrength: return Link_Param_Abs_Type.GEN_Sig_Strenth;
                            case LINK_PARAM_GEN_SUBTYPES.SINR: return Link_Param_Abs_Type.GEN_SINR;
                            case LINK_PARAM_GEN_SUBTYPES.Throughtput: return Link_Param_Abs_Type.GEN_Throughput;
                        }
                        break;
                    case Link_Param_Types.LINK_PARAM_QOS:
                        switch ((LINK_PARAM_QOS_SUBTYPES)SubType)
                        {
                            case LINK_PARAM_QOS_SUBTYPES.AverageTransferDelay: return Link_Param_Abs_Type.QOS_Avg_Delay;
                            case LINK_PARAM_QOS_SUBTYPES.MaxDifClasses: return Link_Param_Abs_Type.QOS_Max_CoS;
                            case LINK_PARAM_QOS_SUBTYPES.MaxTransferDelay: return Link_Param_Abs_Type.QOS_Max_Delay;
                            case LINK_PARAM_QOS_SUBTYPES.MinTransferDelay: return Link_Param_Abs_Type.QOS_Min_Delay;
                            case LINK_PARAM_QOS_SUBTYPES.PacketLossRate: return Link_Param_Abs_Type.QOS_Packet_Loss_Rate;
                            case LINK_PARAM_QOS_SUBTYPES.TransferDelayJitter: return Link_Param_Abs_Type.QOS_Jitter;
                        }
                        break;
                    case Link_Param_Types.LINK_PARAM_802_11:
                        switch ((LINK_PARAM_802_11_SUBTYPES)SubType)
                        {
                            case LINK_PARAM_802_11_SUBTYPES.MulticastPacketLossRate : return Link_Param_Abs_Type.P80211_Multicast_Packet_Loss_Rate;
                            case LINK_PARAM_802_11_SUBTYPES.NoQoS: return Link_Param_Abs_Type.P80211_No_QoS;
                            case LINK_PARAM_802_11_SUBTYPES.RSSI: return Link_Param_Abs_Type.P80211_RSSI;
                        }
                        break;
                }
                throw new ApplicationException("Link Param Type/Subtype combination not found.");
            }
        }

        /// <summary>
        /// Serialized version of this object.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                byte[] aux = new byte[1];
                aux[0]=BitConverter.GetBytes(SubType)[0];
                return Serialization.Choice(aux, (int)Type);
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
        /// Overloaded ToString() method.
        /// </summary>
        /// <param name="prefix">String to be written at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append(prefix + "Link_Param_Type {"+this.AbsoluteType+"}");
            return sb.ToString();
        }
    }

    /// <summary>
    /// This class represents the LINK_PARAM data type, according to IEEE 802.21 definition.
    /// </summary>
    public class Link_Param
    {

        public class QoS_Param_Val
        {
            //TODO

            public QoS_Param_Val(byte[] data)
            {
                //TODO
            }

            public byte[] ByteValue
            {
                get
                {
                    //TODO
                    return new byte[1];
                }
            }

        }

        /// <summary>
        /// The Link_Param_Type specification.
        /// </summary>
        public Link_Param_Type LinkParamType { get; set; }

        /// <summary>
        /// The value of the Link_param.
        /// </summary>
        public ushort LinkParamVal { get; set; }

        /// <summary>
        /// The value of the Link_Param if the LinkParamValType is 1 (meaning it's a QoS parameter)
        /// </summary>
        public QoS_Param_Val LinkParamQoSVal
        { get; set; }

        /// <summary>
        /// The type of the value field.
        /// </summary>
        public ParamValType LinkParamValType { get; set; }

        /// <summary>
        /// The type of parameter described.
        /// </summary>
        public enum ParamValType { Link_Param_Val = 0, QoS_Param_Val = 1 }

        /// <summary>
        /// The Link_Param constructor.
        /// </summary>
        /// <param name="linkParamType">The Link_Param type.</param>
        /// <param name="linkParamVal">The Link_Param value.</param>
        /// <param name="linkParamValType">The Link_Param value type.</param>
        public Link_Param(Link_Param_Type linkParamType, ushort linkParamVal, ParamValType linkParamValType)
        {
            this.LinkParamType = linkParamType;
            this.LinkParamVal = linkParamVal;
            this.LinkParamValType = linkParamValType;

        }

        /// <summary>
        /// Constructor for a parameter with a normal value
        /// </summary>
        /// <param name="linkParamType">The parameter to be described</param>
        /// <param name="linkParamVal">The value of the parameter</param>
        public Link_Param(Link_Param_Type linkParamType, UInt16 linkParamVal)
        {
            this.LinkParamType = linkParamType;
            this.LinkParamVal = (ushort)linkParamVal;
            this.LinkParamValType = ParamValType.Link_Param_Val; //Generic Value (not QoS)
        }

        /// <summary>
        /// Constructor for a parameter with a QoS-type value
        /// </summary>
        /// <param name="linkParamType">The parameter to be described</param>
        /// <param name="qosParamVal">The value of the parameter</param>
        public Link_Param(Link_Param_Type linkParamType, QoS_Param_Val qosParamVal)
        {
            this.LinkParamType = linkParamType;
            this.LinkParamQoSVal = qosParamVal;
            this.LinkParamValType = ParamValType.QoS_Param_Val;
        }

        /// <summary>
        /// Alternative Link_Param empty constructor.
        /// </summary>
        public Link_Param() { }

        /// <summary>
        /// Standard deserialization constructor for Link_Param
        /// </summary>
        /// <param name="data">The raw data for the Link_Param</param>
        public Link_Param(byte[] data)
        {
            //Console.WriteLine("TEST#### ");
            //BitArray bt = new BitArray(data);
            //int i = 1;
            //foreach (bool b in bt)
            //{
            //    Console.Write(b ? 1 : 0);
            //    if (i++ % 8 == 0)
            //        Console.Write("\t");
            //}
            //Console.WriteLine("\n########");
            this.LinkParamType = new Link_Param_Type(data.Take(2).ToArray());
            this.LinkParamValType = (ParamValType) data[2];
            if (LinkParamValType == ParamValType.Link_Param_Val)
                this.LinkParamVal = BitConverter.ToUInt16(data, 3);
            else
                this.LinkParamQoSVal = new QoS_Param_Val(data.Skip(3).ToArray());
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
            sb.AppendLine(prefix + "Link_Param");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\t"+this.LinkParamType.ToString());
            sb.AppendLine(prefix + "\tValue ("+this.LinkParamValType+"): "+ (this.LinkParamValType==ParamValType.Link_Param_Val ? this.LinkParamVal.ToString() : this.LinkParamQoSVal.ToString()));
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }

        /// <summary>
        /// Serialized version of this object.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                return Serialization.Sequence(LinkParamType.ByteValue, Serialization.Choice(BitConverter.GetBytes((ushort)LinkParamVal), 0));
            }
        }

    }


    /// <summary>
    /// This class represents the threshold data type, according to IEEE 802.21 definition.
    /// </summary>
    public class Threshold
    {
        /// <summary>
        /// The threshold value.
        /// </summary>
        public short Threshold_Val { get; set; }

        /// <summary>
        /// The threshold direction, represented in the enumerator.
        /// </summary>
        public Threshold_X_Dir Threshold_dir { get; set; }

        /// <summary>
        /// The threshold action, represented in the enumerator.
        /// </summary>
        public TH_Action Threshold_action { get; set; }

        /// <summary>
        /// Threshold class constructor.
        /// </summary>
        /// <param name="threshold_Val">The threshold value.</param>
        /// <param name="threshold_dir">The threshold direction.</param>
        public Threshold(short threshold_Val, Threshold_X_Dir threshold_dir)
        {
            this.Threshold_Val = threshold_Val;
            this.Threshold_dir = threshold_dir;
        }

        /// <summary>
        /// Alternative empty Threshold constructor.
        /// </summary>
        public Threshold() { }

        /// <summary>
        /// Deserialization constructor.
        /// </summary>
        /// <param name="data">Raw serialized Threshold object.</param>
        public Threshold(byte[] data)
        {
            this.Threshold_Val = BitConverter.ToInt16(data.Take(2).Reverse().ToArray(), 0);
            this.Threshold_dir = (Threshold_X_Dir) data[2];
        }

        /// <summary>
        /// Serialized byte[] representation of this object.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                byte[] tvalBytes = new byte[2];
                byte[] tdirBytes = new byte[1];
                tvalBytes[0] = BitConverter.GetBytes(Threshold_Val)[0];
                tvalBytes[1] = BitConverter.GetBytes(Threshold_Val)[1];
                tdirBytes[0] = BitConverter.GetBytes((int)Threshold_dir)[0];
                return Serialization.Sequence(tvalBytes, tdirBytes);
            }
        }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return "Threshold { Value: " + Threshold_Val + ", Direction: " + Threshold_dir + ", Action: " + Threshold_action + " }";
        }
    }

    /// <summary>
    /// This class represents the Link_Parm_Rpt data type, wich gathers information about the measurable parameter and it correspondant threshold.
    /// </summary>
    public class Link_Param_Rpt
    {
        /// <summary>
        /// The link_param.
        /// </summary>
        public Link_Param LinkParam { get; set; }

        /// <summary>
        /// The threshold.
        /// </summary>
        public Threshold Threshold { get; set; }

        private byte[] byteVal;
        /// <summary>
        /// Link_Param_Rpt byte[] representation.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                GenerateByteValue();
                return byteVal;
            }
            private set
            {
                byteVal = value;
            }
        }

        /// <summary>
        /// The Link_Param_Rpt constructor.
        /// </summary>
        /// <param name="linkParam">The Link_Param.</param>
        /// <param name="threshold">Tha Threshold.</param>
        public Link_Param_Rpt(Link_Param linkParam, Threshold threshold)
        {
            this.LinkParam = linkParam;
            this.Threshold = threshold;
        }

        /// <summary>
        /// Alternative Link_Parm_Rpt constructor.
        /// </summary>
        public Link_Param_Rpt() { }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return "LinkParamRpt { LinkParam: " + LinkParam + ", Threshold: " + Threshold + " }";
        }

        /// <summary>
        /// Generates the Link_Param_Rpt byte value.
        /// </summary>
        private void GenerateByteValue()
        {
            if (Threshold!=null)
                ByteValue = Serialization.Sequence(LinkParam.ByteValue, Serialization.Choice(Threshold.ByteValue, 1 ));
            else
                ByteValue = Serialization.Sequence(LinkParam.ByteValue, Serialization.Choice(null, 0 ));
        }
    }

    /// <summary>
    /// This class represents the Link_Parameters_Report, wich gathers the information about several link parameters, according to IEEE 802.21 specification.
    /// </summary>
    public class Link_Parameters_Report
    {
        /// <summary>
        /// The link identifier, represented by the link tupple id.
        /// </summary>
        public Link_Tuple_Id LinkIdentifier { get; set; }

        /// <summary>
        /// The EventList of link parameters to be reported.
        /// </summary>
        public List<Link_Param_Rpt> LinkParametersReportList { get; set; }

        private byte[] linkParametersReportListByteValue;
        /// <summary>
        /// LinkParametersReportList as a Byte Value.
        /// </summary>
        public byte[] LinkParametersReportListByteValue
        {
            get
            {
                GenerateByteValueForLinkParametersReportList();
                return linkParametersReportListByteValue;
            }
            private set
            {
                linkParametersReportListByteValue = value;
            }
        }

        /// <summary>
        /// Link_Parameters_Report class constructor.
        /// </summary>
        /// <param name="LinkIdentifier">The Link Identifier.</param>
        /// <param name="LinkParametersReportList">The Link Parameter Report List.</param>
        public Link_Parameters_Report(Link_Tuple_Id LinkIdentifier, List<Link_Param_Rpt> LinkParametersReportList)
        {
            this.LinkIdentifier = LinkIdentifier;
            this.LinkParametersReportList = LinkParametersReportList;
        }

        /// <summary>
        /// Empty Link_Parameters_Report class constructor.
        /// </summary>
        public Link_Parameters_Report() { }

        /// <summary>
        /// Overriden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            foreach (Link_Param_Rpt lpr in LinkParametersReportList)
            {
                sb.Append(lpr.ToString());
                if (LinkParametersReportList.Count > 1)
                    sb.Append(", ");
            }
            return "LinkParametersReport { LinkIdentifier: " + LinkIdentifier + ", ReportList: " + sb.ToString() + " }";
        }

        private void GenerateByteValueForLinkParametersReportList()
        {
            List<byte[]> tempByteList = new List<byte[]>();

            foreach (var report in this.LinkParametersReportList)
            {
                tempByteList.Add(report.ByteValue);
            }

            this.LinkParametersReportListByteValue = Serialization.EncodingList(tempByteList.ToArray());
        }
    }

    /// <summary>
    /// Class representing a response to a Link_Configure_Thresholds_Request. Contains tha action status as well as a list of Link_Cfg_Status corresponding to the list requested.
    /// </summary>
    public class Link_Configure_Thresholds_Confirm
    {
        /// <summary>
        /// The status of this Link_Configure_Thresholds_Confirm response.
        /// </summary>
        public STATUS Status { get; set; }
        /// <summary>
        /// The List of Link_Configure_Status of this response.
        /// </summary>
        public List<Link_Cfg_Status> LinkConfigureStatusList { get; set; }

        /// <summary>
        /// Serialized version (in TLV list format) of the Link_Configure_Status_List.
        /// </summary>
        /// <returns></returns>
        public List<byte[]> cfgStatusAsByteArrayList()
        {
            List<byte[]> bList = new List<byte[]>(LinkConfigureStatusList.Count);
            foreach (Link_Cfg_Status lcp in LinkConfigureStatusList)
                bList.Add(lcp.ByteValue);
            return bList;
        }

        /// <summary>
        /// Normal constructor for this object.
        /// </summary>
        /// <param name="s">The status for this response.</param>
        /// <param name="lcs">The List of Link_Cfg_status for this response.</param>
        public Link_Configure_Thresholds_Confirm(STATUS s, List<Link_Cfg_Status> lcs)
        {
            this.Status = s;
            this.LinkConfigureStatusList = lcs;
        }
    }

    /// <summary>
    /// A list of Link_Configuration_Status
    /// </summary>
    public class Link_Cfg_Status
    {
        /// <summary>
        /// The type of Link Parameter that this Status refers to.
        /// </summary>
        public Link_Param_Type paramType { get; set; }
        /// <summary>
        /// The Threshold specified for the Link_Param_Type on this object.
        /// </summary>
        public Threshold threshold { get; set; }
        /// <summary>
        /// The status of the configuration. True for success or False for failure.
        /// </summary>
        public bool configStatus { get; set; }

        /// <summary>
        /// Constructor for a Link_Cfg_Status object.
        /// </summary>
        /// <param name="lpt">The Link Param Type</param>
        /// <param name="th">The threshold</param>
        /// <param name="cfgst">The config Status (false: failure, true: success)</param>
        public Link_Cfg_Status(Link_Param_Type lpt, Threshold th, bool cfgst)
        {
            this.paramType = lpt;
            this.threshold = th;
            this.configStatus = cfgst;
        }

        /// <summary>
        /// Serialized version of this object.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                byte[] result = new byte[6];
                result[0] = (byte)paramType.Type;
                result[1] = (byte)paramType.SubType;
                result[2] = BitConverter.GetBytes(threshold.Threshold_Val)[1];
                result[3] = BitConverter.GetBytes(threshold.Threshold_Val)[0];
                result[4] = (byte)threshold.Threshold_dir;
                result[5] = BitConverter.GetBytes(configStatus)[0];
                return result;
            }
        }

    }


    /// <summary>
    /// This class represents the Link_Cfg_Param, wich is reponsible for threshold configuration actions, according to IEEE 802.21 specification.
    /// </summary>
    public class Link_Cfg_Param
    {
        /// <summary>
        /// The link param type.
        /// </summary>
        public Link_Param_Type Link_Param_Type { get; set; }

        /// <summary>
        /// The timer interval, expressed in milliseconds.
        /// </summary>
        public ushort Timer_Interval { get; set; }

        /// <summary>
        /// The threshold action, represented in the enumerator.
        /// </summary>
        public TH_Action Th_Action { get; set; }

        /// <summary>
        /// The threshold EventList.
        /// </summary>
        public List<Threshold> ThresholdList { get; set; }

        /// <summary>
        /// The Link_Cfg_Param constructor.
        /// </summary>
        /// <param name="linkParamType">The Link Parameter Type.</param>
        /// <param name="linkParamSubType">The Link Parameter Subtype.</param>
        /// <param name="timerInterval">The timer interval (in ms).</param>
        /// <param name="thAction">The threshold action to be performed.</param>
        /// <param name="thresholdList">The threshold EventList.</param>
        public Link_Cfg_Param(Link_Param_Types linkParamType, ushort linkParamSubType, ushort timerInterval, TH_Action thAction, List<Threshold> thresholdList)
        {
            this.Link_Param_Type =  new Link_Param_Type(linkParamType, linkParamSubType);
            this.Timer_Interval = timerInterval;
            this.Th_Action = thAction;
            this.ThresholdList = thresholdList;
        }

        /// <summary>
        /// Link_Cfg_Param de-serialization constructor
        /// </summary>
        /// <param name="data">The serialized Link_Cfg_Param</param>
        public Link_Cfg_Param(byte[] data)
        {
            int i = 0;
            byte aux = data[i++];
            this.Link_Param_Type = new Link_Param_Type((Link_Param_Types)aux, data[i++]);
            if (data[i++] == 0)
                this.Timer_Interval = 0;
            else
            {
                byte[] tmp = new byte[2];
                tmp[1] = data[i++];
                tmp[0] = data[i++];
                this.Timer_Interval = BitConverter.ToUInt16(tmp, 0);
            }
            this.Th_Action = (TH_Action)data[i++];
            this.ThresholdList = MIHDeserializer.DeserializeThresholdList(data.Skip(i).ToArray());
        }

        /// <summary>
        /// Empty Link_Cfg_Param constructor.
        /// </summary>
        public Link_Cfg_Param() { }

        /// <summary>
        /// MIHProtocol of a Link_Cfg_Param element.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                byte[] result = new byte[3 + (Timer_Interval==0 ? 1 : 3) + 1 + (ThresholdList.Count*3)];
                int i = 0;
                result[i++] = (byte)Link_Param_Type.Type;
                result[i++] = (byte)Link_Param_Type.SubType;
                result[i++] = (byte)(Timer_Interval == 0 ? 0 : 1);
                if (Timer_Interval != 0)
                {
                    result[i++] = BitConverter.GetBytes(Timer_Interval)[1];
                    result[i++] = BitConverter.GetBytes(Timer_Interval)[0];
                }
                result[i++] = (byte)Th_Action;
                result[i++] = (byte)ThresholdList.Count;
                foreach (Threshold t in ThresholdList)
                {
                    result[i++] = BitConverter.GetBytes(t.Threshold_Val)[1];
                    result[i++] = BitConverter.GetBytes(t.Threshold_Val)[0];
                    result[i++] = (byte)t.Threshold_dir;
                }

                return result;
            }
        }

    }

    /// <summary>
    /// This class represents a LinkGetParameters.Request, usually sent by the local MIHF to obtain the current value of a set of link parameters of a specific link.
    /// </summary>
    public class Link_Get_Parameters_Request
    {

        /// <summary>
        /// A EventList of link parameters for which Status is requested.
        /// </summary>
        public List<Link_Param_Type> LinkParametersRequest { get; set; }

        /// <summary>
        /// The link states to be requested.
        /// </summary>
        public BitArray LinkStatesRequest { get; set; }

        /// <summary>
        /// The link descriptors to be requested.
        /// </summary>
        public BitArray LinkDescriptorsRequest { get; set; }

        /// <summary>
        /// Link_Get_Parameters_Request main constructor.
        /// </summary>
        /// <param name="linkParametersRequest">The EventList of link parameters for which Status is requested.</param>
        /// <param name="linkStatesRequest">The link states to be requested.</param>
        /// <param name="linkDescriptorsRequest">The link descriptors to be requested.</param>
        public Link_Get_Parameters_Request(List<Link_Param_Type> linkParametersRequest, BitArray linkStatesRequest, BitArray linkDescriptorsRequest)
        {
            this.LinkParametersRequest = linkParametersRequest;
            this.LinkStatesRequest = linkStatesRequest;
            this.LinkDescriptorsRequest = linkDescriptorsRequest;
        }

        /// <summary>
        /// Link_Get_Parameters_Request main constructor for deserialization.
        /// </summary>
        /// <param name="linkParametersRequest">The EventList of link parameters for which Status is requested.</param>
        /// <param name="linkStatesRequest">The link states to be requested.</param>
        /// <param name="linkDescriptorsRequest">The link descriptors to be requested.</param>
        public Link_Get_Parameters_Request(List<Link_Param_Type> linkParametersRequest, byte[] linkStatesRequest, byte[] linkDescriptorsRequest)
        {
            this.LinkParametersRequest = linkParametersRequest;
            this.LinkStatesRequest = new BitArray(linkStatesRequest.Reverse().ToArray()); ;
            this.LinkDescriptorsRequest = new BitArray(linkDescriptorsRequest.Reverse().ToArray());
        }

        /// <summary>
        /// Link_Get_Parameters_Request empty constructor.
        /// </summary>
        public Link_Get_Parameters_Request() { }

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
            sb.AppendLine(prefix + "Link_Get_Parameters_Request");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tLink Parameters Request List");
            sb.AppendLine(prefix + "\t{");
            foreach(Link_Param_Type lpt in this.LinkParametersRequest)
                sb.AppendLine(lpt.ToString(prefix + "\t\t"));
            sb.AppendLine(prefix + "\t}");
            sb.Append(prefix + "\tLink States List: ");
            sb.AppendLine(prefix + "{ OP_Mode: " + this.LinkStatesRequest[0] +", Channel_ID: " + this.LinkStatesRequest[1]+" }" );
            sb.Append(prefix + "\tLink Descriptors List: ");
            sb.AppendLine(prefix + "{ Number of CoS: " + this.LinkDescriptorsRequest[0] + ", Number of Queues: " + this.LinkDescriptorsRequest[1] + " }");
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }
    }

    /// <summary>
    /// This class represents a Link_Get_Parameters_Confirm, which is sent by a local MIHF in response to a Link_Get_Parameters.Request, providing the current values of the requested link parameters.
    /// </summary>
    public class Link_Get_Parameters_Confirm
    {
        /// <summary>
        /// Represents a Link_States_Rsp, used on the Link_Get_Parameters_Confirm message. Can represent either the opmode or the channel id for the link, and the corresponding value.
        /// </summary>
        public class Link_States_Rsp
        {
            /// <summary>
            /// The Type of a Link_States_Rsp.
            /// </summary>
            public enum Type { OP_MODE = 0, CHANNEL_ID = 1 }
            /// <summary>
            /// The type of this Link_States_Rsp.
            /// </summary>
            public Type ChoiceType {get;set;}
            /// <summary>
            /// The value corresponding to the Link_States_Rsp type.
            /// </summary>
            public UInt16 Value{get;set;}

            /// <summary>
            /// Overloaded ToString() method.
            /// </summary>
            /// <returns>A string representation of this object.</returns>
            public override string ToString()
            {
                return ToString("");
            }

            /// <summary>
            /// Overloaded ToString() method.
            /// </summary>
            /// <param name="prefix">A string to be printed at the beggining of each line.</param>
            /// <returns>A string representation of this object.</returns>
            public string ToString(string prefix)
            {
                StringBuilder sb = new StringBuilder();
                sb.AppendLine(prefix + "{ " + this.ChoiceType + ": " + ((this.ChoiceType==Type.OP_MODE) ? ((OP_MODES)this.Value).ToString() : this.Value+"") + " }");
                return sb.ToString();
            }

            /// <summary>
            /// Standard Link_States_Rsp constructor.
            /// </summary>
            /// <param name="t">The type of the Link_States_Rsp. You can use the numerals 0 for OP_MODE and 1 for CHANNEL_ID.</param>
            /// <param name="val">The value for the parameter. Keep in mind the value for OP_MODE is an 8-bit integer and the value for CHANNEL_ID is a 16-bit one.</param>
            public Link_States_Rsp(Type t, ushort val)
            {
                this.ChoiceType = t;
                this.Value=val;
            }

            /// <summary>
            /// Empty Link_States_Rsp constructor
            /// </summary>
            public Link_States_Rsp(){ }

            /// <summary>
            /// Constructor for a Link_States_Rsp object based on a serialized one.
            /// </summary>
            /// <param name="data">The serialized object</param>
            public Link_States_Rsp(byte[] data)
            {
                this.ChoiceType = (Type)data[0];
                this.Value = (ChoiceType == Type.OP_MODE ? data[1] : BitConverter.ToUInt16(data, 1));
            }

            /// <summary>
            /// Returns the raw serialized value of this entity.
            /// </summary>
            public byte[] ByteValue
            {
                get
                {
                    return Serialization.Choice(BitConverter.GetBytes(Value).Take((ChoiceType==Type.OP_MODE ? 1 : 2)).ToArray(), (int)ChoiceType);
                }
            }
        }

        /// <summary>
        /// Represents a Link_States_rsp, used on the Link_Get_Parameters_Confirm message. Can represent either the number of QoS Classes or the number of transmit queues supported.
        /// </summary>
        public class Link_Desc_Rsp
        {
            /// <summary>
            /// The type of a Link_Desc_Rsp
            /// </summary>
            public enum Type { NUM_CoS = 0, NUM_QUEUE = 1 }
            /// <summary>
            /// The type for this Link_Desc_Rsp
            /// </summary>
            public Type ChoiceType {get;set;}
            /// <summary>
            /// The value corresponding to the Type parameter.
            /// </summary>
            public byte Value{get;set;}

            /// <summary>
            /// Overrriden ToString() method.
            /// </summary>
            /// <returns>A string representation of this object.</returns>
            public override string ToString()
            {
                return ToString("");
            }

            /// <summary>
            /// Overloaded ToString() method.
            /// </summary>
            /// <param name="prefix">A string to be printed at the beggining of each line.</param>
            /// <returns>A string representation of this object.</returns>
            public string ToString(string prefix)
            {
                StringBuilder sb = new StringBuilder();
                sb.AppendLine(prefix + "{ " + this.ChoiceType + ": " + this.Value + " }");
                return sb.ToString();
            }

            /// <summary>
            /// Standard Link_Desc_Rsp constructor.
            /// </summary>
            /// <param name="t">The type of the Link_Desc_Rsp. You can use the numerals 0 for NUM_CoS and 1 for NUM_QUEUE.</param>
            /// <param name="val">The value for the parameter.</param>
            public Link_Desc_Rsp(Type t, byte val)
            {
                this.ChoiceType = t;
                this.Value=val;
            }

            /// <summary>
            /// Empty Link_Desc_Rsp constructor
            /// </summary>
            public Link_Desc_Rsp(){ }

            /// <summary>
            /// Deserialization constructor.
            /// </summary>
            /// <param name="data">Raw serialized Link_Desc_Rsp object.</param>
            public Link_Desc_Rsp(byte[] data)
            {
                this.ChoiceType = (Type)data[0];
                this.Value = data[1];
            }

            /// <summary>
            /// Returns the raw serialized value of this entity.
            /// </summary>
            public byte[] ByteValue
            {
                get
                {
                    return Serialization.Choice(BitConverter.GetBytes(Value).ToArray(), (int)ChoiceType);
                }
            }
        }

        /// <summary>
        /// The Status of the operation.
        /// </summary>
        public STATUS Status { get; set; }

        /// <summary>
        /// A EventList of measurable link parameters and their current values.
        /// </summary>
        public List<Link_Param> LinkParametersStatusList { get; set; }

        /// <summary>
        /// A list of the requested link states and their values.
        /// </summary>
        public List<Link_States_Rsp> LinkStatesRspList { get; set; }

        /// <summary>
        /// A list of the requested link descriptors and their values.
        /// </summary>
        public List<Link_Desc_Rsp> LinkDescRspList { get; set; }

        /// <summary>
        /// The Link_Get_Parameters_Confirm main constructor.
        /// </summary>
        /// <param name="status">The Status of the operation</param>
        /// <param name="linkParametersStatusList">The List of parameter values</param>
        /// <param name="linkStatesList">The List of the requested link states</param>
        /// <param name="linkDescList"></param>
        public Link_Get_Parameters_Confirm(STATUS status, List<Link_Param> linkParametersStatusList, List<Link_States_Rsp> linkStatesList, List<Link_Desc_Rsp> linkDescList)
        {
            this.Status = status;
            this.LinkParametersStatusList = linkParametersStatusList;
            this.LinkStatesRspList = linkStatesList;
            this.LinkDescRspList = linkDescList;
        }

        /// <summary>
        /// Link_Get_Parameters_Confirm empty constructor.
        /// </summary>
        public Link_Get_Parameters_Confirm() { }

        /// <summary>
        /// Overridden ToString() method.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return ToString("");
        }

        /// <summary>
        /// Overloaded ToString() method.
        /// </summary>
        /// <param name="prefix">A string to be printed at the beggining of each line.</param>
        /// <returns>A string representation of this object.</returns>
        public string ToString(string prefix)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(prefix + "Link_Get_Parameters_Confirm");
            sb.AppendLine(prefix + "{");
            sb.AppendLine(prefix + "\tStatus: " + this.Status);
            sb.AppendLine(prefix + "\tLink Parameters Status List:");
            sb.AppendLine(prefix + "\t{");
            foreach(Link_Param lp in this.LinkParametersStatusList)
                sb.AppendLine(lp.ToString(prefix + "\t\t"));
            sb.AppendLine(prefix + "\t}");
            sb.AppendLine(prefix + "\tLink States List:");
            sb.AppendLine(prefix + "\t{");
            foreach (Link_States_Rsp lsr in this.LinkStatesRspList)
                sb.AppendLine(lsr.ToString(prefix + "\t\t"));
            sb.AppendLine(prefix + "\t}");
            sb.AppendLine(prefix + "}");
            sb.AppendLine(prefix + "\tLink Descriptors List:");
            sb.AppendLine(prefix + "\t{");
            foreach (Link_Desc_Rsp ldr in this.LinkDescRspList)
                sb.AppendLine(ldr.ToString(prefix + "\t\t"));
            sb.AppendLine(prefix + "\t}");
            sb.AppendLine(prefix + "}");
            return sb.ToString();
        }

        /// <summary>
        /// Transforms the Link_Param_List attribute into a list of byte Arrays.
        /// </summary>
        /// <returns>An array of byte[] objects representing the List of Link_Params from this object.</returns>
        public Array LinkParamListAsByteArray()
        {
            List<byte[]> result = new List<byte[]> (this.LinkParametersStatusList.Count);

            foreach ( Link_Param lp in this.LinkParametersStatusList)
            {
                result.Add(lp.ByteValue);
            }
            return result.ToArray();
        }

        /// <summary>
        /// Transforms the Link_States_List attribute into a list of byte Arrays.
        /// </summary>
        /// <returns>An array of byte[] objects representing the List of Link_States from this object.</returns>
        public Array LinkStatesListAsByteArray()
        {
            List<byte[]> result = new List<byte[]>(this.LinkStatesRspList.Count);

            foreach (Link_States_Rsp lsr in this.LinkStatesRspList)
            {
                result.Add(lsr.ByteValue);
            }
            return result.ToArray();
        }

        /// <summary>
        /// Transforms the Link_Desc_List attribute into a list of byte Arrays.
        /// </summary>
        /// <returns>An array of byte[] objects representing the List of Link_Descriptors from this object.</returns>
        public Array LinkDescListAsByteArray()
        {
            List<byte[]> result = new List<byte[]>(this.LinkDescRspList.Count);

            foreach (Link_Desc_Rsp ldr in this.LinkDescRspList)
            {
                result.Add(ldr.ByteValue);
            }
            return result.ToArray();
        }
    }
}
