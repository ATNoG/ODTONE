//==============================================================================
// Brief   : Class representing a Protocol.cs entity
// Authors : Marcelo Génio <marcelog@ua.pt>
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
using System.Threading;
//using LINK_SAP_CS_80211.Events.EventClasses;
using MIH.DataTypes;

namespace LINK_SAP_CS_80211.LINK_SAP_80211.Events
{
    class TimedReport
    {
        public Link_Param_Abs_Type ParamType { get; set; }
        public Timer Timer { get; set; }
        private int interval;
        public int Interval { get { return interval; } set { Timer.Change(value, value); interval = value; } }

        public TimedReport(Link_Param_Abs_Type paramtype, int interval)
        {
            this.ParamType = paramtype;
            this.Timer = new Timer(Reports.PeriodicReport, paramtype, interval, interval);
            this.Interval = interval;
        }

        public static TimedReport FindTimedReport(Link_Param_Abs_Type param, int interval, List<TimedReport> list)
        {
            foreach (TimedReport tr in list)
            {
                if (tr.ParamType == param && tr.interval == interval)
                    return tr;
            }
            return null;
        }

        public override bool Equals(Object o)
        {
            try
            {
                TimedReport tr = (TimedReport)o;
                return (tr.Interval == this.Interval && tr.ParamType == this.ParamType);
            }
            catch (Exception e)
            { return false; }
        }

        public static bool operator ==(TimedReport tr1, TimedReport tr2)
        {
            return tr1.Equals(tr2);
        }

        public static bool operator !=(TimedReport tr1, TimedReport tr2)
        {
            return !tr1.Equals(tr2);
        }
    }
}
