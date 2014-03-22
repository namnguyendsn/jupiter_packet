using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.IO;
using System.Windows.Forms;

namespace Led_Simulator_v2._0_beta
{
    class DataFile
    {
         string filePath;
         public DataFile(string newFilePath)
        {
            filePath = newFilePath;
        }
        public static Boolean SaveBinFile(DataLedArrayNode writeData, string targetPath)
        {
            try
            {
                using (BinaryWriter writer = new BinaryWriter(File.Open(targetPath, FileMode.Create)))
                {
                    writer.Write((byte)(0xFF));
                    writer.Write((byte)writeData.LedNumber);
                    writer.Write((byte)writeData.StateNumber);
                    writer.Write((byte)(0xFF));
                    for (int stateIndex = 0; stateIndex < writeData.StateNumber; stateIndex++)
                    {
                        ArrayList curState = (ArrayList)writeData.GetState(stateIndex);
                        Constants.StateType stateType = (Constants.StateType)curState[0];
                        writer.Write((byte)(stateType));
                        int temp;
                        switch (stateType)
                        {
                            case Constants.StateType.Data:
                                temp = (int)curState[1];// Get common value
                                writer.Write((byte)(temp));
                                for (int ledIndex = 0; ledIndex < writeData.LedNumber; ledIndex++)
                                {
                                    temp = (int)curState[ledIndex + 2];
                                    writer.Write((byte)(temp));
                                }
                                break;
                            case Constants.StateType.StartFor:
                                temp = (int)curState[1];
                                writer.Write((byte)(temp));
                                break;
                            case Constants.StateType.Endfor:
                                break;
                        }
                        writer.Write((Byte)0xFF);
                    }
                }
                return true;
            }
            catch(Exception e)
            {
                MessageBox.Show(e.Message);
                return false;
            }
        }
        public DataLedArrayNode ReadTextFile(string filePath)
        {
            if (File.Exists(filePath))
            {
                DataLedArrayNode temp_data = new DataLedArrayNode();
                return temp_data;
            }
            else
            {
                MessageBox.Show("Read_text_file: File path is invalid");
                return null;
            }
        }
        public static DataLedArrayNode ReadBinaryFile(string filePath)
        {
            if (File.Exists(filePath))
            {

                using (BinaryReader reader = new BinaryReader(File.Open(filePath, FileMode.Open)))
                {
                    int temp;
                    int ledNumber;
                    int stateNumber;
                    //Read global info
                    temp = reader.ReadByte();
                    if (temp != 0xFF)
                    {
#if __DEBUG
                        MessageBox.Show("Read_binary_file: File format is invalid");
#endif
                        return null;
                    }
                    ledNumber = reader.ReadByte();
                    stateNumber = reader.ReadByte();
                    temp = reader.ReadByte();
                    if (temp != 0xFF)
                    {
#if __DEBUG
                        MessageBox.Show("Read_binary_file: File format is invalid");
#endif
                        return null;
                    }
                    DataLedArrayNode dataRead= new DataLedArrayNode();
                    dataRead.LedNumber = ledNumber;
                    //dataRead.StateNumber = stateNumber;
                    //Read states
                    for (int stateIndex = 0; stateIndex < stateNumber; stateIndex++)
                    {
                        //Read state type
                        ArrayList curState= new ArrayList();
                        Constants.StateType stateType = (Constants.StateType)reader.ReadByte();
                        switch (stateType)
                        {
                            case Constants.StateType.Data:
                                curState.Add(stateType);//Add stateType
                                temp = reader.ReadByte();//Add common value
                                curState.Add(temp);
                                for (int ledIndex = 0; ledIndex < ledNumber; ledIndex++)
                                {
                                    temp = reader.ReadByte();
                                    if (temp > Constants.MAX_BRIGHT)
                                    {
                                        MessageBox.Show("Read_binary_file: File format is invalid");
                                        return null;
                                    }
                                    curState.Add(temp);
                                }
                                break;
                            case Constants.StateType.StartFor:
                                                                curState.Add(stateType);//Add stateType
                                temp = reader.ReadByte();//Add common value
                                curState.Add(temp);
                                break;
                            case Constants.StateType.Endfor:
                                 curState.Add(stateType);//Add stateType
                                break;
                            default:
#if __DEBUG
                                MessageBox.Show("Read_binary_file: File format is invalid");
#endif
                                return null;
                        }
                        temp = reader.ReadByte();
                        if (temp != 0xFF)
                        {
#if __DEBUG
                            MessageBox.Show("Read_binary_file: File format is invalid");
#endif
                            return null;
                        }
                        dataRead.InsertState(stateIndex,stateType);
                        dataRead.SetState(stateIndex,curState);
                    }
                    return dataRead;
                }
            }
            else
            {
#if __DEBUG
                MessageBox.Show("Read_text_file: File path is invalid");
#endif
                return null;
            }
        }
    }
}
