//==============================================================================
// Brief   : Class representing a Serialization.cs entity
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

namespace MIH.MIHProtocol
{
    /// <summary>
    /// This class contains methods to serialize MIH objects.
    /// </summary>
    public class Serialization
    {
        /// <summary>
        /// This method sequences 9 parameters in MIH Protocol order.
        /// </summary>
        /// <param name="first">First parameter.</param>
        /// <param name="second">Second parameter.</param>
        /// <param name="third">Third parameter.</param>
        /// <param name="fourth">Fourth parameter.</param>
        /// <param name="fifth">Fifth parameter.</param>
        /// <param name="sixth">Sixth parameter.</param>
        /// <param name="seventh">Seventh parameter.</param>
        /// <param name="eigth">Eigth parameter.</param>
        /// <param name="nineth">Nineth parameter.</param>
        /// <returns>A byte array containing the sequenced parameters.</returns>
        public static  byte[] Sequence(byte[] first, byte[] second, byte[] third, byte[] fourth, byte[] fifth, byte[] sixth, byte[] seventh, byte[] eigth, byte[] nineth)
        {
            int size = first.Length + second.Length + third.Length + fourth.Length + fifth.Length + sixth.Length + seventh.Length + eigth.Length + nineth.Length;
            byte[] output = new byte[size];

            int i, pos;
            for (i = 0, pos = 0; i < first.Length; i++, pos++)
            {

                output[i] = first[i];
            }
            for (i = 0; i < second.Length; i++, pos++)
            {

                output[pos] = second[i];
            }
            for (i = 0; i < third.Length; i++, pos++)
            {

                output[pos] = third[i];
            }
            for (i = 0; i < fourth.Length; i++, pos++)
            {

                output[pos] = fourth[i];
            }
            for (i = 0; i < fifth.Length; i++, pos++)
            {

                output[pos] = fifth[i];
            }
            for (i = 0; i < sixth.Length; i++, pos++)
            {

                output[pos] = sixth[i];
            }
            for (i = 0; i < seventh.Length; i++, pos++)
            {

                output[pos] = seventh[i];
            }
            for (i = 0; i < eigth.Length; i++, pos++)
            {

                output[pos] = eigth[i];
            }
            for (i = 0; i < nineth.Length; i++, pos++)
            {

                output[pos] = nineth[i];
            }


            return output;
        }

        /// <summary>
        /// This method sequences 8 parameters in MIH Protocol order.
        /// </summary>
        /// <param name="first">First parameter.</param>
        /// <param name="second">Second parameter.</param>
        /// <param name="third">Third parameter.</param>
        /// <param name="fourth">Fourth parameter.</param>
        /// <param name="fifth">Fifth parameter.</param>
        /// <param name="sixth">Sixth parameter.</param>
        /// <param name="seventh">Seventh parameter.</param>
        /// <param name="eigth">Eigth parameter.</param>
        /// <returns>A byte array containing the sequenced parameters.</returns>
        public static byte[] Sequence(byte[] first, byte[] second, byte[] third, byte[] fourth, byte[] fifth, byte[] sixth, byte[] seventh, byte[] eigth)
        {
            int size = first.Length + second.Length + third.Length + fourth.Length + fifth.Length + sixth.Length + seventh.Length + eigth.Length;
            byte[] output = new byte[size];

            int i, pos;
            for (i = 0, pos = 0; i < first.Length; i++, pos++)
            {

                output[i] = first[i];
            }
            for (i = 0; i < second.Length; i++, pos++)
            {

                output[pos] = second[i];
            }
            for (i = 0; i < third.Length; i++, pos++)
            {

                output[pos] = third[i];
            }
            for (i = 0; i < fourth.Length; i++, pos++)
            {

                output[pos] = fourth[i];
            }
            for (i = 0; i < fifth.Length; i++, pos++)
            {

                output[pos] = fifth[i];
            }
            for (i = 0; i < sixth.Length; i++, pos++)
            {

                output[pos] = sixth[i];
            }
            for (i = 0; i < seventh.Length; i++, pos++)
            {

                output[pos] = seventh[i];
            }
            for (i = 0; i < eigth.Length; i++, pos++)
            {

                output[pos] = eigth[i];
            }

            return output;
        }


        /// <summary>
        /// This method sequences 7 parameters in MIH Protocol order.
        /// </summary>
        /// <param name="first">First parameter.</param>
        /// <param name="second">Second parameter.</param>
        /// <param name="third">Third parameter.</param>
        /// <param name="fourth">Fourth parameter.</param>
        /// <param name="fifth">Fifth parameter.</param>
        /// <param name="sixth">Sixth parameter.</param>
        /// <param name="seventh">Seventh parameter.</param>
        /// <returns>A byte array containing the sequenced parameters.</returns>
        public static byte[] Sequence(byte[] first, byte[] second, byte[] third, byte[] fourth, byte[] fifth, byte[] sixth, byte[] seventh)
        {
            int size = first.Length + second.Length + third.Length + fourth.Length + fifth.Length + sixth.Length + seventh.Length;
            byte[] output = new byte[size];

            int i, pos;
            for (i = 0, pos = 0; i < first.Length; i++, pos++)
            {

                output[i] = first[i];
            }
            for (i = 0; i < second.Length; i++, pos++)
            {

                output[pos] = second[i];
            }
            for (i = 0; i < third.Length; i++, pos++)
            {

                output[pos] = third[i];
            }
            for (i = 0; i < fourth.Length; i++, pos++)
            {

                output[pos] = fourth[i];
            }
            for (i = 0; i < fifth.Length; i++, pos++)
            {

                output[pos] = fifth[i];
            }
            for (i = 0; i < sixth.Length; i++, pos++)
            {

                output[pos] = sixth[i];
            }
            for (i = 0; i < seventh.Length; i++, pos++)
            {

                output[pos] = seventh[i];
            }

            return output;
        }

        /// <summary>
        /// This method sequences 6 parameters in MIH Protocol order.
        /// </summary>
        /// <param name="first">First parameter.</param>
        /// <param name="second">Second parameter.</param>
        /// <param name="third">Third parameter.</param>
        /// <param name="fourth">Fourth parameter.</param>
        /// <param name="fifth">Fifth parameter.</param>
        /// <param name="sixth">Sixth parameter.</param>
        /// <returns>A byte array containing the sequenced parameters.</returns>
        public static byte[] Sequence(byte[] first, byte[] second, byte[] third, byte[] fourth, byte[] fifth, byte[] sixth)
        {
            int size = first.Length + second.Length + third.Length + fourth.Length + fifth.Length + sixth.Length;
            byte[] output = new byte[size];

            int i, pos;
            for (i = 0, pos = 0; i < first.Length; i++, pos++)
            {

                output[i] = first[i];
            }
            for (i = 0; i < second.Length; i++, pos++)
            {

                output[pos] = second[i];
            }
            for (i = 0; i < third.Length; i++, pos++)
            {

                output[pos] = third[i];
            }
            for (i = 0; i < fourth.Length; i++, pos++)
            {

                output[pos] = fourth[i];
            }
            for (i = 0; i < fifth.Length; i++, pos++)
            {

                output[pos] = fifth[i];
            }
            for (i = 0; i < sixth.Length; i++, pos++)
            {

                output[pos] = sixth[i];
            }


            return output;
        }

        /// <summary>
        /// This method sequences 5 parameters in MIH Protocol order.
        /// </summary>
        /// <param name="first">First parameter.</param>
        /// <param name="second">Second parameter.</param>
        /// <param name="third">Third parameter.</param>
        /// <param name="fourth">Fourth parameter.</param>
        /// <param name="fifth">Fifth parameter.</param>
        /// <returns>A byte array containing the sequenced parameters.</returns>
        public static byte[] Sequence(byte[] first, byte[] second, byte[] third, byte[] fourth, byte[] fifth)
        {
            int size = first.Length + second.Length + third.Length + fourth.Length + fifth.Length;
            byte[] output = new byte[size];

            int i, pos;
            for (i = 0, pos = 0; i < first.Length; i++, pos++)
            {

                output[i] = first[i];
            }
            for (i = 0; i < second.Length; i++, pos++)
            {

                output[pos] = second[i];
            }
            for (i = 0; i < third.Length; i++, pos++)
            {

                output[pos] = third[i];
            }
            for (i = 0; i < fourth.Length; i++, pos++)
            {

                output[pos] = fourth[i];
            }
            for (i = 0; i < fifth.Length; i++, pos++)
            {

                output[pos] = fifth[i];
            }

            return output;

        }


        /// <summary>
        /// This method sequences 4 parameters in MIH Protocol order.
        /// </summary>
        /// <param name="first">First parameter.</param>
        /// <param name="second">Second parameter.</param>
        /// <param name="third">Third parameter.</param>
        /// <param name="fourth">Fourth parameter.</param>
        /// <returns>A byte array containing the sequenced parameters.</returns>
        public static byte[] Sequence(byte[] first, byte[] second, byte[] third, byte[] fourth)
        {

            int size = first.Length + second.Length + third.Length + fourth.Length;
            byte[] output = new byte[size];

            int i, pos;
            for (i = 0, pos = 0; i < first.Length; i++, pos++)
            {

                output[i] = first[i];
            }
            for (i = 0; i < second.Length; i++, pos++)
            {

                output[pos] = second[i];
            }
            for (i = 0; i < third.Length; i++, pos++)
            {

                output[pos] = third[i];
            }
            for (i = 0; i < fourth.Length; i++, pos++)
            {

                output[pos] = fourth[i];
            }

            return output;

        }

        /// <summary>
        /// This method sequences 3 parameters in MIH Protocol order.
        /// </summary>
        /// <param name="first">First parameter.</param>
        /// <param name="second">Second parameter.</param>
        /// <param name="third">Third parameter.</param>
        /// <returns>A byte array containing the sequenced parameters.</returns>
        public static byte[] Sequence(byte[] first, byte[] second, byte[] third)
        {
            int size = first.Length + second.Length + third.Length;
            byte[] output = new byte[size];

            int i, pos;
            for (i = 0, pos = 0; i < first.Length; i++, pos++)
            {

                output[i] = first[i];
            }
            for (i = 0; i < second.Length; i++, pos++)
            {

                output[pos] = second[i];
            }
            for (i = 0; i < third.Length; i++, pos++)
            {

                output[pos] = third[i];
            }

            return output;
        }

        /// <summary>
        /// This method sequences 2 parameters in MIH Protocol order.
        /// </summary>
        /// <param name="first">First parameter.</param>
        /// <param name="second">Second parameter.</param>
        /// <returns>A byte array containing the sequenced parameters.</returns>
        public static byte[] Sequence(byte[] first, byte[] second)
        {
            int size = first.Length + second.Length;
            byte[] output = new byte[size];

            int i, pos;

            for (i = 0, pos = 0; i < first.Length; i++, pos++)
            {

                output[i] = first[i];
            }
            for (i = 0; i < second.Length; i++, pos++)
            {

                output[pos] = second[i];
            }

            return output;
        }

        /// <summary>
        /// Encodes a 1 parameter Choice MIH Object.
        /// </summary>
        /// <param name="data">Data</param>
        /// <param name="choice">Choice </param>
        /// <returns>A Choice MIH object in a byte array.</returns>
        public static byte[] Choice(byte[] data, int choice)
        {
            byte selector;
            byte[] out_choice = new byte[0];
            //choice = choice + 1;

            if (data != null)
            {
                byte[] selectorX = new byte[1];

                out_choice = new byte[1 + data.Length];

                selectorX = new byte[1];
                selectorX[0] = (byte)choice;


                out_choice = Sequence(selectorX, data);

            }
            else
            {
                //Encoding Null chooice
                selector = 0;

                out_choice = new byte[1];
                //Encoding Choice

                out_choice[0] = selector;
                // | 0 | 0 | 0 |
            }

            return out_choice;

        }

        /// <summary>
        /// Encodes an Array(byte[]) into a MIH List Object.
        /// </summary>
        /// <param name="list">Array(byte[]) to be encoded.</param>
        /// <returns>MIH List Object</returns>
        public static byte[] EncodingList(Array list)
        {
            int size = 0;
            int valueSize = 0;


            byte[] outList = new byte[0];
            for (int i = 0; i < list.Length; i++)
            {
                valueSize = valueSize + ((byte[])list.GetValue(i)).Length;
            }
            size = list.Length;
            if (size < 128)
            {
                //Instantiates the out_list array
                outList = new byte[1 + valueSize];
                //Sets the EventList size
                outList[0] = (byte)list.Length;
                int pos = 1;
                for (int i = 1; i <= list.Length; i++)
                {
                    for (int j = 0; j < ((byte[])list.GetValue(i - 1)).Length; j++)
                    {
                        outList[pos] = ((byte[])list.GetValue(i - 1))[j];
                        pos++;
                    }
                }
            }
            else
            {
                try
                {
                    int appendedSize = size - 128;

                    //Calculates the number of octets to be appended to the length field

                    int nOctetsLength = (int)Math.Ceiling(((double)appendedSize / 255));
                    if (nOctetsLength > 0xFF)
                    {
                        throw new Exception("Error: message size not supported");
                    }
                    //Instantiates the out_list array
                    outList = new byte[1 + nOctetsLength + valueSize];
                    outList[0] = (byte)0x80;
                    outList[0] = (byte)(outList[0] | nOctetsLength);
                    //Append the number of octets of the length field
                    for (int i = 1; i < nOctetsLength - 1; i++)
                    {
                        outList[i] = (byte)0xFF;
                    }

                    if (nOctetsLength > 1)
                    {
                        outList[nOctetsLength] = IntToSingleByte(nOctetsLength * 255 - appendedSize);
                    }
                    else
                    {
                        outList[nOctetsLength] = (byte)appendedSize;
                    }

                    //
                    int pos = nOctetsLength + 1;
                    for (int i = 1; i <= list.Length; i++)
                    {
                        for (int j = 0; j < ((byte[])list.GetValue(i - 1)).Length; j++)
                        {
                            outList[pos] = ((byte[])list.GetValue(i - 1))[j];
                            pos++;
                        }
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("!EXCEPTION: " + e.Message);
                    return new byte[0];
                }
            }
            return outList;
        }

        /// <summary>
        /// Encodes a MIH Object in byte[] form into a TLV object.
        /// </summary>
        /// <param name="TLV">TLV</param>
        /// <param name="ValueField">Value Field</param>
        /// <returns></returns>
        public static byte[] SerializeToTLV(int TLV, byte[] ValueField)
        {

            byte[] output;
            int i, j;


            if (ValueField.Length <= 128)
            {

                output = new byte[ValueField.Length + 2];

                //Inserting Type field
                output[0] = IntToSingleByte(TLV);

                //Inserting Length Field
                output[1] = IntToSingleByte(ValueField.Length);

                //Inserting Value Field
                for (i = 2, j = 0; j < ValueField.Length; i++, j++)
                {
                    output[i] = ValueField[j];
                }
            }
            else
            {
                double nOctets = 0;
                //Calculate the amount of octets needed to represent the value size

                nOctets = Math.Ceiling((double)(ValueField.Length - 128) / 255);

                try
                {
                    if (nOctets > 0x7F)
                    {
                        throw new Exception("Error: Message size not supported");
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("!EXCEPTION: " + e.Message);
                    return new byte[0];
                }

                //Instantiating the output array
                //System.output.println("Valuefield Size: " + ValueField.length);
                //System.output.println("Total size of frame: " + (ValueField.length + 1 + (int) nOctets));

                output = new byte[ValueField.Length + 1 + (int)nOctets + 1];

                //Inserting Type field
                output[0] = IntToSingleByte(TLV);

                //Insert the Length Field
                //First octet, when >128:
                output[1] = (byte)0x80;
                output[1] = (byte)(output[1] | (byte)(nOctets));

                /*//The rest of the Length field octets
                for (i = 0, j = 2; i < nOctets - 1; j++, i++)
                {
                    //Fill with 0xFF
                    output[j] = (byte)0xFF;

                }

                output[j] = (byte)(ValueField.Length - (255 * (nOctets - 2) + 128));

                j++;
                int offset = j;*/

                //byte[] aux = new byte[(int)nOctets];
                byte[] bA = BitConverter.GetBytes(ValueField.Length-128);
                for (i = 0, j=2; i < nOctets; i++, j++)
                    output[j] = bA[(int)nOctets-i-1];
                //Insert the Value Field
                for (i = 0; i < ValueField.Length; j++, i++)
                {
                    output[j] = ValueField[i];
                }
            }
            return output;
        }


        /// <summary>
        /// Encondes the info elements in a MIH Object.
        /// </summary>
        /// <param name="type">Type</param>
        /// <param name="ValueField">Value Field</param>
        /// <returns></returns>
        public static byte[] SerializeInfoElements(int type, byte[] ValueField)
        {
            int i, j;
            byte[] tp;
            byte[] output;
            if (ValueField.Length <= 128)
            {

                output = new byte[ValueField.Length + 1 + 4];
                tp = Uint32ToByteArray(Convert.ToUInt32(type));
                //Inserting Type field
                for (i = 0; i < 4; i++)
                {
                    output[i] = tp[i];
                }
                //Inserting Length Field
                output[4] = (byte)ValueField.Length;

                //Inserting Value Field
                for (i = 5, j = 0; j < ValueField.Length; i++, j++)
                {
                    output[i] = ValueField[j];
                }
            }
            else
            {
                //Calculate the amount of octets needed to represent the value size
                double nOctets = Math.Ceiling((double)(ValueField.Length - 128) / 255);
                //Instantiating the output array

                output = new byte[ValueField.Length + 4 + ((int)nOctets) + 1];
                //Inserting Type field
                tp = Uint32ToByteArray(Convert.ToUInt32(type));
                //Inserting Type field
                for (i = 0; i < 4; i++)
                {
                    output[i] = tp[i];
                }

                //Insert the Length Field
                //First octet, when >128:
                output[4] = (byte)0x80;
                output[4] = (byte)(output[4] | (byte)(nOctets));
                //The rest of the Length field octets
                for (i = 5, j = 0; j < nOctets - 1; i++, j++)
                {
                    //Fill with 0xFF
                    output[i] = (byte)0xFF;

                }

                output[i] = (byte)(ValueField.Length - (255 * (nOctets - 1) + 128));
                i++;
                //Insert the Value Field
                int offset = i;
                //Insert the Value Field

                for (j = 0; j < ValueField.Length; j++, i++)
                {
                    output[i] = ValueField[j];
                }
            }
            return output;
        }

        /// <summary>
        /// Auxiliar method that converts a Int to a Single Byte.
        /// </summary>
        /// <param name="value">Int value to be converted.</param>
        /// <returns></returns>
        private static byte IntToSingleByte(int value)
        {
            byte[] intBytes = BitConverter.GetBytes(value);
            if (!BitConverter.IsLittleEndian)
                Array.Reverse(intBytes);
            return intBytes[0];
        }

        /// <summary>
        /// Auxiliar method that converts a Uint32ToByteArray
        /// </summary>
        /// <param name="value">Uint32 value to be converted.</param>
        /// <returns></returns>
        private static byte[] Uint32ToByteArray(UInt32 value)
        {
            byte[] intBytes = BitConverter.GetBytes(value);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(intBytes);
            return intBytes;
        }

    }
}
