//==============================================================================
// Brief   : Generic Message Indication Message
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

package mih.message;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.util.ArrayList;

import mih.tlvs.DestinationMihfIdTlv;
import mih.tlvs.SourceMihfIdTlv;
import mih.tlvs.Tlv;
import mih.types.Serializeable;
import mih.types.basic.OctetString;

/**
 * The Message represents the means of communication in the MIHStack resource
 * adaptor defined protocol. It abstracts the underlying protocol information by
 * wrapping the protocol information into Java objects.<br>
 * Message follows the value object pattern and can only be constructed by a
 * factory object. The MessageImpl object implements the Message interface and
 * is the concrete implementation class of the more abstract interface which is
 * the only visible interface for the SBB.
 *
 * @author Carlos Guimarães
 */
public abstract class Message implements Serializeable {

	protected class TlvInfo {
		public TlvInfo(Tlv<?> tlv, boolean isOptional) {
			this.tlv = tlv;
			this.isOptional = isOptional;
		}

		public Tlv<?> getTlv() {
			return tlv;
		}

		public boolean isOptional() {
			return isOptional;
		}

		Tlv<?> tlv;
		boolean isOptional;
	}

	public final static int MIH_Capability_Discover_request = 5121;
	public final static int MIH_Capability_Discover_indication = 7169;
	public final static int MIH_Capability_Discover_response = 6145;
	public final static int MIH_Capability_Discover_confirm = 4097;

	public final static int MIH_Register_request = 5122;
	public final static int MIH_Register_indication = 7170;
	public final static int MIH_Register_response = 6146;
	public final static int MIH_Register_confirm = 4098;

	public final static int MIH_DeRegister_request = 5123;
	public final static int MIH_DeRegister_indication = 7171;
	public final static int MIH_DeRegister_response = 6147;
	public final static int MIH_DeRegister_confirm = 4099;

	public final static int MIH_Event_Subscribe_request = 5124;
	public final static int MIH_Event_Subscribe_indication = 7172;
	public final static int MIH_Event_Subscribe_response = 6148;
	public final static int MIH_Event_Subscribe_confirm = 4100;

	public final static int MIH_Event_Unsubscribe_request = 5125;
	public final static int MIH_Event_Unsubscribe_indication = 7173;
	public final static int MIH_Event_Unsubscribe_response = 6149;
	public final static int MIH_Event_Unsubscribe_confirm = 4101;

	public final static int MIH_Link_Detected_indication = 11265;
	public final static int MIH_Link_Up_indication = 11266;
	public final static int MIH_Link_Down_indication = 11267;
	public final static int MIH_Link_Parameters_Report_indication = 11269;
	public final static int MIH_Link_Going_Down_indication = 11270;
	public final static int MIH_Link_Handover_Imminent_indication = 11271;
	public final static int MIH_Link_Handover_Complete_indication = 11272;
	public final static int MIH_Link_PDU_Transmit_Status_indication = 11273;

	public final static int MIH_Link_Get_Parameters_request = 13313;
	public final static int MIH_Link_Get_Parameters_indication = 15361;
	public final static int MIH_Link_Get_Parameters_response = 14337;
	public final static int MIH_Link_Get_Parameters_confirm = 12289;

	public final static int MIH_Link_Configure_Thresholds_request = 13314;
	public final static int MIH_Link_Configure_Thresholds_indication = 15362;
	public final static int MIH_Link_Configure_Thresholds_response = 14338;
	public final static int MIH_Link_Configure_Thresholds_confirm = 12290;

	public final static int MIH_Link_Actions_request = 13315;
	public final static int MIH_Link_Actions_indication = 15363;
	public final static int MIH_Link_Actions_response = 14339;
	public final static int MIH_Link_Actions_confirm = 12291;

	public final static int MIH_Net_HO_Candidate_Query_request = 13316;
	public final static int MIH_Net_HO_Candidate_Query_indication = 15364;
	public final static int MIH_Net_HO_Candidate_Query_response = 14340;
	public final static int MIH_Net_HO_Candidate_Query_confirm = 12292;

	public final static int MIH_MN_HO_Candidate_Query_request = 13317;
	public final static int MIH_MN_HO_Candidate_Query_indication = 15365;
	public final static int MIH_MN_HO_Candidate_Query_response = 14341;
	public final static int MIH_MN_HO_Candidate_Query_confirm = 12293;

	public final static int MIH_N2N_HO_Query_Resoures_request = 13318;
	public final static int MIH_N2N_HO_Query_Resoures_indication = 15366;
	public final static int MIH_N2N_HO_Query_Resoures_response = 14342;
	public final static int MIH_N2N_HO_Query_Resoures_confirm = 12294;

	public final static int MIH_MN_HO_Commit_request = 13319;
	public final static int MIH_MN_HO_Commit_indication = 15367;
	public final static int MIH_MN_HO_Commit_response = 14343;
	public final static int MIH_MN_HO_Commit_confirm = 12295;

	public final static int MIH_Net_HO_Commit_request = 13320;
	public final static int MIH_Net_HO_Commit_indication = 15368;
	public final static int MIH_Net_HO_Commit_response = 14344;
	public final static int MIH_Net_HO_Commit_confirm = 12296;

	public final static int MIH_N2N_HO_Commit_request = 13321;
	public final static int MIH_N2N_HO_Commit_indication = 15369;
	public final static int MIH_N2N_HO_Commit_response = 14345;
	public final static int MIH_N2N_HO_Commit_confirm = 12297;

	public final static int MIH_MN_HO_Complete_request = 13322;
	public final static int MIH_MN_HO_Complete_indication = 15370;
	public final static int MIH_MN_HO_Complete_response = 14346;
	public final static int MIH_MN_HO_Complete_confirm = 12298;

	public final static int MIH_N2N_HO_Complete_request = 13323;
	public final static int MIH_N2N_HO_Complete_indication = 15371;
	public final static int MIH_N2N_HO_Complete_response = 14347;
	public final static int MIH_N2N_HO_Complete_confirm = 12299;

	public final static int MIH_Get_Information_request = 17409;
	public final static int MIH_Get_Information_indication = 19457;
	public final static int MIH_Get_Information_response = 18433;
	public final static int MIH_Get_Information_confirm = 16385;

	public final static int MIH_Push_Information_request = 17410;
	public final static int MIH_Push_Information_indication = 19458;

	int version;
	boolean ack_req;
	boolean ack_rsp;
	boolean uir;
	boolean m;
	int fn;
	boolean rsvd1;
	int mid;
	int rsvd2;
	int tid;
	int payloadLength;

	SourceMihfIdTlv sourceTlv;
	DestinationMihfIdTlv destinationTlv;
	ArrayList<TlvInfo> tlvList;

	public Message() {
		sourceTlv = new SourceMihfIdTlv();
		destinationTlv = new DestinationMihfIdTlv();
		tlvList = new ArrayList<TlvInfo>();
	}

	public Message(int version, boolean ack_req, boolean ack_rsp, boolean uir,
			boolean m, int fn, boolean rsvd1, int mid, int rsvd2, int tid) {
		this.version = version;
		this.ack_req = ack_req;
		this.ack_rsp = ack_rsp;
		this.uir = uir;
		this.m = m;
		this.fn = fn;
		this.rsvd1 = rsvd1;
		this.mid = mid;
		this.rsvd2 = rsvd2;
		this.tid = tid;
	}

	/**
	 * Access the message's version.
	 *
	 * @return the message's version
	 */
	public int getVersion() {
		return version;
	}

	public void setVersion(int version) {
		this.version = version;
	}

	/**
	 * Access the message's acknowledge request flag.
	 *
	 * @return the message's acknowledge request flag
	 */
	public boolean getAckReq() {
		return ack_req;
	}

	public void setAckReq(boolean ack_req) {
		this.ack_req = ack_req;
	}

	/**
	 * Access the message's acknowledge response flag.
	 *
	 * @return the message's acknowledge response flag
	 */
	public boolean getAckRsp() {
		return ack_rsp;
	}

	public void setAckRsp(boolean ack_rsp) {
		this.ack_rsp = ack_rsp;
	}

	/**
	 * Access the message's unauthenticated information request flag.
	 *
	 * @return the message's unauthenticated information request flag
	 */
	public boolean getUir() {
		return uir;
	}

	public void setUir(boolean uir) {
		this.uir = uir;
	}

	/**
	 * Access the message's more fragments flag.
	 *
	 * @return the message's more fragments flag
	 */
	public boolean getM() {
		return m;
	}

	public void setM(boolean m) {
		this.m = m;
	}

	/**
	 * Access the message's fragment number.
	 *
	 * @return the message's fragment number
	 */
	public int getFn() {
		return fn;
	}

	public void setFn(int fn) {
		this.fn = fn;
	}

	/**
	 * Access the message's reserved1 field.
	 *
	 * @return the message's reserved1 field
	 */
	public boolean getRsvd1() {
		return rsvd1;
	}

	public void setRsvd1(boolean rsvd1) {
		this.rsvd1 = rsvd1;
	}

	/**
	 * Access the message's MIH identifier.
	 *
	 * @return the message's MIH identifier
	 */
	public int getMid() {
		return mid;
	}

	public void getMid(int mid) {
		this.mid = mid;
	}

	/**
	 * Access the message's reserved2 field.
	 *
	 * @return the message's reserved2 field
	 */
	public int getRsvd2() {
		return rsvd2;
	}

	public void setRsvd2(int rsvd2) {
		this.rsvd2 = rsvd2;
	}

	/**
	 * Access the message's transaction identifier.
	 *
	 * @return the message's transaction identifier
	 */
	public int getTid() {
		return tid;
	}

	public void setTid(int tid) {
		this.tid = tid;
	}

	public int getPayloadLength() {
		return payloadLength;
	}

	public OctetString getSourceMihf() {
		return sourceTlv.getValue();
	}

	public void setSourceMihf(OctetString source) {
		sourceTlv = new SourceMihfIdTlv(source);
	}

	public OctetString getDestinationMihf() {
		return destinationTlv.getValue();
	}

	public void setDestinationMihf(OctetString source) {
		destinationTlv = new DestinationMihfIdTlv(source);
	}

	public void toBytes(ByteArrayOutputStream stream) throws Exception {
		ByteArrayOutputStream tmp = new ByteArrayOutputStream();
		sourceTlv.toBytes(tmp);
		destinationTlv.toBytes(tmp);
		for (int i = 0; i < tlvList.size(); ++i)
			tlvList.get(i).getTlv().toBytes(tmp);
		payloadLength = tmp.size();

		stream.write((byte) ((version << 4) | (ack_req ? 1 << 3 : 0 << 3)
				| (ack_rsp ? 1 << 2 : 0 << 2) | (uir ? 1 << 1 : 0 << 1) | (m ? 1
				: 0)));
		stream.write((byte) ((fn << 1) | (rsvd1 ? 1 : 0)));
		stream.write((byte) ((mid & 0xFF00) >> 8));
		stream.write((byte) (mid & 0x00FF));
		stream.write((byte) ((rsvd2 << 4) | ((tid & 0xF00) >> 8)));
		stream.write((byte) (tid & 0x00FF));
		stream.write((byte) ((payloadLength & 0xFF00) >> 8));
		stream.write((byte) (payloadLength & 0xFF));

		sourceTlv.toBytes(stream);
		destinationTlv.toBytes(stream);
		for (int i = 0; i < tlvList.size(); ++i) {
			if(tlvList.get(i).getTlv().isInitialized())
				tlvList.get(i).getTlv().toBytes(stream);
			else
				if(!tlvList.get(i).isOptional())
					throw new Exception("Bad TLV Exception");
		}
	}

	public void fromBytes(ByteArrayInputStream stream) throws Exception {
		int tmp;
		int tmp2;

		tmp = stream.read();
		version = (tmp & 0xF0)  >> 4;
		ack_req = ((tmp & 0x08) >> 3) == 1;
		ack_rsp = ((tmp & 0x04) >> 2) == 1;
		uir     = ((tmp & 0x02) >> 1) == 1;
		m       = ((tmp & 0x01))      == 1;

		tmp = stream.read();
		fn    = (tmp & 0xFE) >> 1;
		rsvd1 = ((tmp & 0x01))      == 1;

		tmp = stream.read();
		tmp2 = stream.read();
		mid = (tmp << 8) | tmp2;

		tmp = stream.read();
		rsvd2 = (tmp & 0xF0) >> 4;

		tmp2 = stream.read();
		tid = ((tmp & 0x0F) << 8) | tmp2;

		tmp = stream.read();
		tmp2 = stream.read();
		payloadLength = (tmp << 8) | tmp2;

		sourceTlv.fromBytes(stream);
		destinationTlv.fromBytes(stream);
		for (int i = 0; i < tlvList.size(); ++i) {
			tlvList.get(i).getTlv().fromBytes(stream);

			if(!tlvList.get(i).getTlv().isInitialized())
				if(!tlvList.get(i).isOptional())
					throw new Exception("Bad TLV Exception");;
		}

	}
}
