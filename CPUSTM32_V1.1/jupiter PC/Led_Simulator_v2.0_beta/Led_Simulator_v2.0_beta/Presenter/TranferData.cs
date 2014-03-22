using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Collections;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace Led_Simulator_v2._0_beta
{
    public partial class Presenter
    {
        byte ACK;
        void serialPort_DataReceived(Object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort COMPort = (SerialPort)sender;
            try
            {
                ACK = (byte)COMPort.ReadByte();
            }
            catch(SystemException)
            {}
        }
        byte[] GetHexData()
        {
            try
            {
                List<byte> hexData = new List<byte>();
                DataLedArrayNode writeData = model.LedData;
                for (int stateIndex = 0; stateIndex < writeData.StateNumber; stateIndex++)
                {
                    ArrayList curState = (ArrayList)writeData.GetState(stateIndex);
                    Constants.StateType stateType = (Constants.StateType)curState[0];
                    hexData.Add((byte)(stateType));
                    int temp;
                    switch (stateType)
                    {
                        case Constants.StateType.Data:
                            temp = (int)curState[1];// Get common value
                            hexData.Add((byte)(temp));
                            for (int ledIndex = 0; ledIndex < writeData.LedNumber; ledIndex++)
                            {
                                temp = (int)curState[ledIndex + 2];
                                hexData.Add((byte)(temp));
                            }
                            break;
                        case Constants.StateType.StartFor:
                            temp = (int)curState[1];
                            hexData.Add((byte)(temp));
                            break;
                        case Constants.StateType.Endfor:
                            break;
                    }
                }
                byte[] returnData = new byte[hexData.Count];
                hexData.CopyTo(returnData);
                return returnData;
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                return null;
            }
        }

        byte[] getAlarmData()
        {
            if (gbVar.alarm_data.AlarmSelected == false)
            {
                MessageBox.Show("Chọn thời gian Tắt/Bật!!!");
                return null;
            }
            byte[] AlarmData = new byte[6];
            AlarmData[0] = 0x01;
            AlarmData[1] = 0xFF;
            AlarmData[2] = gbVar.alarm_data.H_On;
            AlarmData[3] = gbVar.alarm_data.M_On;
            AlarmData[4] = (byte)(gbVar.alarm_data.ontime/256);
            AlarmData[5] = (byte)gbVar.alarm_data.ontime;
            return AlarmData;
        }

        byte[] getTimeData()
        {
            if (gbVar.time_data.TimeSelected == false)
            {
                MessageBox.Show("Chọn thời gian hiện tại!!!");
                return null;
            }
            byte[] TimeData = new byte[5];
            TimeData[0] = gbVar.time_data.Cur_H;
            TimeData[1] = gbVar.time_data.Cur_Mi;
            TimeData[2] = gbVar.time_data.Cur_D;
            TimeData[3] = gbVar.time_data.Cur_Mo;
            TimeData[4] = gbVar.time_data.Cur_Y;
            return TimeData;
        }

        void SendData(SerialPort sendPort)
        {
            switch (gbVar.TransferType)
            {
                case (int)Constants.DataType.SetInfoAlarm:
                    if (getAlarmData() == null)
                        return;
                    byte[] data0 = getAlarmData();
                    commandHub.ReceiveCommand("StartSendData");
                    SendData(data0, sendPort);
                    break;
                case (int)Constants.DataType.SetInfoLed:
                    break;
                case (int)Constants.DataType.SetInfoTime:
                    if (getTimeData() == null)
                        return;
                    byte[] data2 = getTimeData();
                    commandHub.ReceiveCommand("StartSendData");
                    SendData(data2, sendPort);
                    break;
                case (int)Constants.DataType.DataEffect:
                    byte[] data3 = GetHexData();
                    commandHub.ReceiveCommand("StartSendData");
                    SendData(data3, sendPort);
                    break;
                default:
                    MessageBox.Show("Chọn kiểu dữ liệu!!!");
                    return;
                    break;
            }
            commandHub.ReceiveCommand("SendDataDone");
        }
        
        private byte CalcCRC8(byte[] data)
        {
            byte temp1, bitCounter;
            long feedbackBit;
            byte crc8Result = 0;
            int dataIndex=0;
            int numberByte = data.Length;
            while (numberByte > dataIndex)
            {
                temp1 = data[dataIndex];

                for (bitCounter = 8; bitCounter>0; bitCounter--)
                {
                    feedbackBit = (crc8Result & 0x01);
                    crc8Result >>= 1;
                    if ((feedbackBit ^ (temp1 & 0x01))==1)
                    {
                        crc8Result ^= 0x8c;
                    }
                    temp1 >>= 1;
                }
                dataIndex++;
            }
            return crc8Result;
        }
        /// <summary> Send the user's data currently entered in the 'send' box.</summary>
        int frameLength = 100;
        private void SendData(byte[] data, SerialPort sendPort)
        {
            int framenum;
            int frame_sent;
            int frame_remain;
            int frame_len;
            int offset = 0;
            int data_remain;
            byte[] effect_packed = new byte[10240];
            {
                try
                {
                    /* structure of Packet
                     * |SOP|Length|Data type|Data|EOP|
                      */
                    effect_packed[0] = 0xE0; // SOP
                    effect_packed[1] = (byte)(data.Length << 8); // length
                    effect_packed[2] = (byte)(data.Length); // length
                    switch (gbVar.TransferType)
                    { 
                        case (int)Constants.DataType.SetInfoAlarm:
                            effect_packed[3] = 0xDD;// data type set alarm
                            break;
                        case (int)Constants.DataType.SetInfoLed:
                            effect_packed[3] = 0xDF;// data type led info
                            break;
                        case (int)Constants.DataType.SetInfoTime:
                            effect_packed[3] = 0xDE;// data type set time
                            break;
                        case (int)Constants.DataType.DataEffect:
                            effect_packed[3] = 0xD5;// data type data effect
                            break;
                        default:
                            MessageBox.Show("Chọn kiểu dữ liệu!!!");
                            return;
                            break;
                    }

                    Array.Copy(data, 0, effect_packed, 4, data.Length);
                    effect_packed[data.Length + 4] = 0xE1;// EOP

                    byte[] PacketBuff = new byte[data.Length + 5];
                    Array.Copy(effect_packed, 0, PacketBuff, 0, data.Length + 5);

                    // split data into SCI frame
                    framenum = PacketBuff.Length / frameLength;// get data length
                    if (PacketBuff.Length % frameLength != 0)
                        framenum++;
                    frame_sent = 0;
                    for (int i = 0; i < framenum; i++)
                    {
                        frame_remain = framenum - frame_sent;
                        data_remain = PacketBuff.Length - frameLength * frame_sent;
                        if (data_remain > frameLength)
                            frame_len = frameLength;
                        else if (data_remain == frameLength)
                            frame_len = PacketBuff.Length - frameLength * frame_sent - 1;
                        else
                            frame_len = PacketBuff.Length - frameLength * frame_sent;
                        byte[] frame_packed = new byte[frame_len+4];
                        Array.Clear(frame_packed, 0, frame_packed.Length);

                        frame_packed[0] = 0xD0;// SOF
                        frame_packed[1] = (byte)(frame_len);// length
                        frame_packed[2] = CalcCRC8(PacketBuff);// crc
                        Array.Copy(PacketBuff, offset, frame_packed, 3, frame_len);
                        frame_packed[frame_len + 3] = 0xD1;// EOF

                        int tryingTime = 0;
                        ACK = 0xFF;
                        while ((tryingTime < 3) && (ACK == 0xFF))
                        {
                            try
                            {
                                sendPort.Write(frame_packed, 0, frame_len + 4);
                            }
                            catch (SystemException)
                            {
                                MessageBox.Show("Chưa mở COM port!!!");
                                return;
                            }

                            Thread.Sleep(100);
                            if (ACK == 0xFF)
                            { 
                                tryingTime++;
                            }
                            //Wait feedback data
                            //Start timer to wait feedback
                        }
                        if (ACK == 0xFF)
                        {
                            MessageBox.Show("Can't send data to board");
                            return;
                        }
                        ++frame_sent;
                        offset += frameLength;
                        // Show the hex digits on in the terminal window
                        //Log(LogMsgType.Outgoing, ByteArrayToHexString(frame_packed) + "\n");
                    }
                }
                catch (FormatException ex)
                {
                    // Inform the user if the hex string was not properly formatted
                    MessageBox.Show(ex.Message);
                }
            }
        }
    }
}