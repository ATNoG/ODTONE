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

import odtone_java.inc.Common.Datatypes.Octet_String;
import odtone_java.inc.Common.Datatypes.UInt16;
/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
public class Utils {

    byte[] frame;
    int headerSize;

    int sourceSize;
    int destinationSize;
    int sensorIdentifierSize;
    int timerIntervalSize;
    int aid;
    int opcode;
    int sid;

    public int getAid() {
        return aid;
    }

    public int getOpcode() {
        return opcode;
    }

    public int getSid() {
        return sid;
    }
    public Utils(byte[] frame) {
       
        headerSize = 8;
        sourceSize = frame[9];
        destinationSize = frame[headerSize + 1 + sourceSize +1+1];
        this.frame = frame;
        byte[] MID_ = new byte[2];


                MID_[0] = frame[2];
                MID_[1] = frame[3];

                sid = (MID_[0] & 0xF0) >> 4;
                opcode = (MID_[0] & 0x0C) >> 2;
                aid = MID_[1];
      
    }

    public String getSourceIdentifier() {
        int i=0;
        
        byte source[] = new byte[sourceSize];
        
        for ( i = 0; i < sourceSize; i++) {
             
            source[i] = frame[i + headerSize + 1 + 1];
        }

        return new Octet_String(source).get_String();
       
        
      
    }

    public String getDestinationIdentifier() {
        byte destination[] = new byte[destinationSize];
        
        for (int i = 0; i < destinationSize; i++) {
            destination[i] = frame[i + headerSize + 1 + sourceSize + 1 + 1+1];
        }
        return new Octet_String(destination).get_String();
    }

    public int getTID(){
     
     byte [] tmp = new byte[2];
     byte mask = 0x0F;
     
     tmp[0] = (byte)(mask & frame[4]);
     tmp[1] = frame[5];
     
     return new UInt16().UInt16ToInt(tmp);
    }
    public int getLinkAction(){

        return frame[headerSize + 1 + sourceSize + 1 +1 +destinationSize+1+1+1];

    }
}
