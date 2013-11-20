namespace odtone { namespace mih {

/**
 * BCST_MMP_ID data type.
 */
typedef octet_string bcst_mmp_id;

/**
 * BCST_MMS_ID data type.
 */
typedef octet_string bcst_mms_id;

/**
 * GROUP_INFO data type.
 */
typedef boost::variant<bcst_mmp_id, bcst_mms_id> group_info;

} /*NS odtone*/	 	} /*NS mih*/
