//
// Copyright (c) 2009-2012 2012 Universidade Aveiro - Instituto de
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
// Author:     Marcelo Lebre <marcelolebre@av.it.pt>
//
package org.sunspotworld;

import Handlers.MIHHandler;

public class SensorSAP {

 
    public void run() {
        System.exit(0);
    }

    
    public static void main(String[] args) {

        MIHHandler mhh = new MIHHandler("127.0.0.1");       
        mhh.start();

    }
}
