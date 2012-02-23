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

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

/**
 *
 * Class designed to communicate or receive a MIH message
 * transport method: UDP
 *
 */
public class Message {

    public byte[] message_out;
    public byte[] message_in = new byte[700];

    public Message() {
    }

    public Message(byte[] message) {
        message_out = message;
    }

    /**
     *
     * Receive method, opens a socket and listens for a message
     *
     * @return byte []
     */
    public byte[] receive(int port, String IPAddress) {
        try {
            DatagramSocket socket = new DatagramSocket(port, InetAddress.getByName(IPAddress));
            DatagramPacket packet = new DatagramPacket(message_in, message_in.length);
            socket.receive(packet);
            socket.close();
            return message_in;
        } catch (IOException e) {
            System.out.println("Error: Listening socket failed");
            return (new byte[0]);
        }
    }

    /**
     *
     * Sending method, opens a socket and sends a message
     * Maximum size for each message is 65535, as imposed by the 16-bit total
     * length field in the IP header.
     * @param String
     * @return boolean
     *
     */
    public boolean send(byte[] msg, String destHost, int port) {
        try {
            
           InetAddress address = InetAddress.getByName(destHost);
            DatagramSocket socket = new DatagramSocket();
            DatagramPacket packet = new DatagramPacket(msg, msg.length, address, port);
            
            socket.send(packet);
            socket.close();
        } catch (UnknownHostException e) {
            e.printStackTrace();
            return false;
        } catch (SocketException e) {
           
            return false;
        } catch (java.io.IOException e) {
            
            return false;
        }
        return true;
    }
}
