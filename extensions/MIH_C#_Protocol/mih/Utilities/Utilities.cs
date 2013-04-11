//==============================================================================
// Brief   : Class representing a Utilities.cs entity
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

﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace MIH.Utilities
{
    /// <summary>
    /// A set of useful functions not specifically related to the MIH
    /// </summary>
    public class Utilities
    {
        /// <summary>
        /// Converts a bit array into a byte array.
        /// </summary>
        /// <param name="bits">The BitArray to convert.</param>
        /// <returns>The converted BitArray in byte[] form.</returns>
        public static byte[] ToByteArray(BitArray bits)
        {
            //Console.WriteLine("Received bits: " + bits.Count);
            int numBytes = bits.Count / 8;
            if (bits.Count % 8 != 0) numBytes++;
            //Console.WriteLine("Creating bytes: " + numBytes);
            byte[] bytes = new byte[numBytes];
            int byteIndex = 0, bitIndex = 0;

            for (int i = 0; i < bits.Count; i++)
            {
                if (bits[i])
                    bytes[byteIndex] |= (byte)(1 << (7 - bitIndex));

                bitIndex++;
                if (bitIndex == 8)
                {
                    bitIndex = 0;
                    byteIndex++;
                }
            }
            //Console.WriteLine("Bytes created: " + bytes.Length);
            return bytes;
        }

        /// <summary>
        /// Reverses the given BitArray.
        /// </summary>
        /// <param name="array">The array to be reversed.</param>
        public static void ReverseBitArray(BitArray array)
        {
            int length = array.Length;
            int mid = (length / 2);

            for (int i = 0; i < mid; i++)
            {
                bool bit = array[i];
                array[i] = array[length - i - 1];
                array[length - i - 1] = bit;
            }
        }

        /// <summary>
        /// Converts a Physical Address object in a XX:XX:XX:XX:XX format string corresponding to it's Mac Address.
        /// </summary>
        /// <param name="pa">The physical address to convert.</param>
        /// <returns>A formated string of the physical address' value.</returns>
        public static String PhysicalAddressToString(System.Net.NetworkInformation.PhysicalAddress pa)
        { return string.Join(":", (from z in pa.GetAddressBytes() select z.ToString("X2")).ToArray()); }

        /// <summary>
        /// Gets the maximum value in an array.
        /// </summary>
        /// <param name="vals">The array to analyze.</param>
        /// <returns>The highest value in this array.</returns>
        public static int getMax(ushort[] vals)
        {
            ushort max = 0;
            foreach (ushort val in vals)
                if (val > max)
                    max = val;
            return max;
        }
    }
}
