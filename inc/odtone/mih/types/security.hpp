#ifndef ODTONE_MIH_TYPES_SECURITY__HPP_
#define ODTONE_MIH_TYPES_SECURITY__HPP_

#include <odtone/mih/types/link.hpp>

namespace odtone { namespace mih {


/**
 * ID_TYPE data type enumeration.
 */
enum id_type_enum{
	id_type_tls_generated = 0,		/**< TLS generated.	*/
	id_type_eap_generated = 1,		/**< EAP generated.	*/

};

/**
 * ID_TYPE data type.
 */
typedef enumeration<id_type_enum> id_type;

/**
 * ID_VALUE data type.
 */
typedef octet_string id_value;

/**
 * TLS_CAP data type.
 */
typedef bool tls_cap;


///////////////////////////////////////////////////////////////////////////////
/**
 * KEY_DIST_LIST data type enumeration.
 */
enum key_dist_list_enum {
	push_key_dist		  = 0,	/**< Push key distribution.	*/
	opt_pro_pull_key_dist	  = 1,	/**< Optimized proactive pull key distribution.	*/
	react_pull_key_dist	  = 2,	/**< Reactive pull key distribution.		*/
};

/**
 * KEY_DIST_LIST data type.
 */
typedef bitmap<8, key_dist_list_enum> key_dist_list;


///////////////////////////////////////////////////////////////////////////////
/**
 * INT_ALG_LIST data type enumeration.
 */
enum int_alg_list_enum {
	intg_hmac_sha_96	  = 0,	/**< INTG_HMAC_SHA_96.	*/
	intg_hmac_cmac_aes	  = 1,	/**< INTG_HMAC_CMAC_AES.	*/
};

/**
 * INT_ALG_LIST data type.
 */
typedef bitmap<8, int_alg_list_enum> int_alg_list;


///////////////////////////////////////////////////////////////////////////////
/**
 * CIPH_ALG_LIST data type enumeration.
 */
enum ciph_alg_list_enum {
	encr_aes_cbc	  = 0,	/**< ENCR_AES_CBC.	*/
	auth_enc_aes_ccm  = 1,	/**< AUTH_ENC_AES_CCM.	*/
	encr_null	  = 2,	/**< ENCR_NULL.	*/
};

/**
 * CIPH_ALG_LIST data type.
 */
typedef bitmap<8, ciph_alg_list_enum> ciph_alg_list;


///////////////////////////////////////////////////////////////////////////////
/**
 * PRF_LIST data type enumeration.
 */
enum prf_list_enum {
	prf_aes_cmac	  = 0,	/**< PRF_AES_CMAC.	*/
	prf_hmac_sha1	  = 1,	/**< PRF_HMAC_SHA1.	*/
	prf_hmac_sha256	  = 2,	/**< PRF_HMAC_SHA256.	*/
};

/**
 * PRF_LIST data type.
 */
typedef bitmap<8, prf_list_enum> prf_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * SEQUENCE for EAP_CAP data type.
 */
struct eap_cap_seq {
	key_dist_list keydistlist;		/**< List of key distribution methods.	*/
	int_alg_list intalglist;		/**< List of integrity algorythms.	*/
	ciph_alg_list ciphalglist;		/**< List of encrption algorythms.	*/
	prf_list prflist;			/**< List of key derivation functions.	*/

	/**
	 * Serialize/deserialize the MIH_SEC_CAP data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & keydistlist;
		ar & intalglist;
		ar & ciphalglist;
		ar & prflist;
	}
};


/**
 * EAP_CAP data type.
 */
typedef boost::variant<null, eap_cap_seq> eap_cap;

///////////////////////////////////////////////////////////////////////////////
/**
 * MIH_SEC_CAP data type.
 */
struct mih_sec_cap {
	tls_cap tlscap;		/**< TLS-generated SA capability.	*/
	eap_cap eapcap;		/**< EAP-generated SA capability.	*/

	/**
	 * Serialize/deserialize the MIH_SEC_CAP data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & tlscap;
		ar & eapcap;
	}
};

/**
 * NONCE_VALUE data type.
 */
typedef uint16 nonce_value;

/**
 * AUTH_INFO_VALUE data type.
 */
typedef octet_string auth_info_value;

/**
 * AUTH_VALUE data type.
 */
typedef octet_string auth_value;

/**
 * KEY data type.
 */
typedef octet_string key;

/**
 * LIFETIME data type.
 */
typedef uint16 lifetime;

///////////////////////////////////////////////////////////////////////////////
/**
 * SEQUENCE for KEY_MAPPING data type.
 */
struct key_mapping_seq {
	link_tuple_id link_tup_id;		/**< LINK_TUPLE_ID.	*/
	key k;					/**< KEY.	*/
	lifetime life;				/**< LIFETIME.	*/

	/**
	 * Serialize/deserialize the MIH_SEC_CAP data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & link_tup_id;
		ar & k;
		ar & life;
	}
};

/**
 * KEY_MAPPING data type.
 */
typedef std::vector<key_mapping_seq> key_mapping;

///////////////////////////////////////////////////////////////////////////////
/**
 * LINK_AUTHENTICATOR_LIST data type.
 */
struct link_authenticator_list {
	link_type type;			/**< LINK_TYPE.	*/
	std::vector<link_addr> addresses;	/**< LIST(LINK_ADDR).	*/

	/**
	 * Serialize/deserialize the MIH_SEC_CAP data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & type;
		ar & addresses;
	}
};

/**
 * LL_FRAMES data type.
 */
typedef octet_string ll_frames;

/**
 * TLS_RECORD data type.
 */
typedef octet_string tls_record;

/**
 * ENCR_BLOCK data type.
 */
typedef octet_string encr_block;

/**
 * INTG_BLOCK data type.
 */
typedef octet_string intg_block;

///////////////////////////////////////////////////////////////////////////////
/**
 * MIH_SPS_RECORD data type.
 */
struct mih_sps_record {
	encr_block encr;			/**< Encrypted data.	*/
	boost::variant<intg_block, null> intg;	/**< Integrity protected data.	*/

	/**
	 * Serialize/deserialize the MIH_SEC_CAP data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & encr;
		ar & intg;
	}
};


/**
 * SECURITY data type.
 */
typedef boost::variant<tls_record, mih_sps_record> security;


} /*NS odtone*/	 	} /*NS mih*/

#endif
