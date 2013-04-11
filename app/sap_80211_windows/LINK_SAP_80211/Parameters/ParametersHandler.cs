//==============================================================================
// Brief   : Class representing a Protocol.cs entity
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

using MIH.DataTypes;


namespace LINK_SAP_CS_80211.Common.Parameters
{
    class ParametersHandler
    {
        private OneShotParameters oneShotParameters = null;
        private PeriodicParameters periodicParameters = null;

        public ParametersHandler()
        {
            oneShotParameters = new OneShotParameters();
            periodicParameters = new PeriodicParameters();
        }

        public void linkConfigureThresholds(List<Link_Cfg_Param> thresholdsToConfigure)
        {
            foreach (Link_Cfg_Param lcp in thresholdsToConfigure)
            {
                if (lcp.Timer_Interval == 0)
                {
                    oneShotParameters.HandleOneShotParamConf(lcp);
                }
                else
                {
                    periodicParameters.HandlePeriodicParameterConfig(lcp);
                }
            }
        }
        public void registerLinkGetParameters(Link_Get_Parameters_Request linkGetParametersRequest)
        {
            GetParameters gp = new GetParameters();
            gp.HandleLinkGetParametersRequest(linkGetParametersRequest);
        }
    }
}
