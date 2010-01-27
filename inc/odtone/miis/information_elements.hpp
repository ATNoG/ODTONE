//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Simao Reis <sreis@av.it.pt>
//

#ifndef ODTONE_IES_HPP
#define ODTONE_IES_HPP

#include <odtone/mih/types/information.hpp>
#include <odtone/mih/types/address.hpp>
#include <odtone/mih/types/location.hpp>
#include <odtone/mih/types/link.hpp>
#include <odtone/mih/types/ipconfig.hpp>
#include <odtone/mih/types/qos.hpp>

namespace odtone { namespace miis {

// general information elements

typedef mih::network_type		ie_network_type;
typedef mih::operator_id		ie_operator_id;
typedef mih::sp_id				ie_service_provider_id;
typedef mih::cntry_code			ie_country_code;


// access network specific information elements

typedef mih::network_id			ie_network_id;
typedef mih::net_aux_id			ie_network_aux_id;
typedef mih::roaming_ptns		ie_roaming_partners;
typedef mih::cost				ie_cost;
typedef mih::qos_list			ie_network_qos;
typedef mih::data_rate			ie_network_data_rate;
typedef mih::regu_domain		ie_net_regulat_domain;
typedef mih::freq_bands			ie_net_frequency_bands;
typedef mih::ip_config			ie_net_ip_cfg_methods;
typedef mih::net_caps			ie_net_capabilities;
typedef mih::supported_lcp		ie_net_supported_lcp;
typedef mih::ip_mob_mgmt		ie_net_mob_mgmt_prot;
typedef mih::proxy_addr			ie_net_emserv_proxy;
typedef mih::proxy_addr			ie_net_ims_proxy_cscf;
typedef bool					ie_net_mobile_network;


// POA specific information elements

typedef mih::link_addr			ie_poa_link_addr;
typedef mih::location			ie_poa_location;
typedef mih::ch_range			ie_poa_channel_range;
typedef mih::system_info		ie_poa_system_info;


// POA specific higher layer service information elements

typedef mih::ip_subnet_info		ie_poa_subnet_info;
typedef mih::ip_addr			ie_poa_ip_addr;

} /* namespace miis */  }  /* namespace odtone */

#endif
