using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Led_Simulator_v2._0_beta
{
    public struct gbVar
    {
        public static int TransferType = 0xFF;
    }

    public static class Constants
    {
        //Constants for data
        public const int MAX_LED = 100;
        public const int MAX_STATE = 100;
        public const int MAX_BRIGHT = 100;
        public const int DEFAULT_BRIGHT = 0;
        public const int DEFAULT_BRIGHTTIME = 5;
        public const int BRIGHT_STEP = 5;
        public const int FORLOOP_STEP = 1;
        public const int DEFAULT_LOOP_TIME = 1;
        public const int TYPE_NONE = 0;
        public enum StateType
        {
            Data = 0xF2,
            StartFor = 0xF0,
            Endfor = 0xF1,
            None = 0xFF
        }

        public enum DataType
        {
            SetInfoTime = 0xDE,
            SetInfoAlarm = 0xDD,
            SetInfoLed = 0xDF,
            SetInfo_1 = 0xD3,
            SetInfo_2 = 0xD4, 
            DataEffect = 0xD5,
            GetInfoFirmVer = 0xD6,
            GetInfo_1 = 0xD7,
            GetInfo_2 = 0xD8,
            GetInfo_3 = 0xD9,
            GetInfo_4 = 0xDA,
            GetInfo_5 = 0xDB,
            GetInfo_6 = 0xDC
        }

        //Constants for Undo/Redo
        public const int MAX_STEP = 6;
        //Constants for LedNode
        //public Color BgColor = Color.DarkSeaGreen;
        //Constants for change event
        public enum DisplayEvent
        {
            FormLoad,
            AddStateAbove,
            AddStateBelow,
            RemoveState,
            AddLedLeft,
            AddLedRight,
            RemoveLed,
            AddStartFor,
            AddEndFor,
            RemoveFor,
            StartSimu,
            PauseSimu,
            StopSimu,
            ChangeBright,
            Undo,
            Redo,
            NewFile,
            OpenFile,
            SaveFile,
            CloseFile
        }
        static public int clockPoint = 20;
    }
}
