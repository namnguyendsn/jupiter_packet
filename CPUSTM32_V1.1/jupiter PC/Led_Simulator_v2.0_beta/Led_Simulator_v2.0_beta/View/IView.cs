using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Forms;
using System.Collections;
using System.IO.Ports;

namespace Led_Simulator_v2._0_beta
{
    public delegate void SendDataDelegate(SerialPort sendPort);
    public interface IView : INotifyPropertyChanged
    //: IModel - if it is a one to one mapping
    {
        //List<Command> CommandList{get;set;}
        DataLedArrayNode LedData { set; }
        ArrayList SimulateData { set; }
        LedNodeIndex CurIndex { get; set; }
        Boolean NodeSelected { get; }
        Mediator CommandHub{set;}
        Hashtable AllCommand{set;}
        //Command GetCommand(string commandName);
        #region Commands
        event EventHandler  FileNewCommand;
        event EventHandler  FileOpenCommand;
        event EventHandler  FileSaveCommand;
        event EventHandler  FileCloseCommand;
        event EventHandler  ExitCommand;

        event EventHandler  UndoCommand;
        event EventHandler  RedoCommand;

        event EventHandler  AddStateAboveCommand;
        event EventHandler  AddStateBelowCommand;
        event EventHandler  RemoveStateCommand;
        event EventHandler  AddStartForCommand;
        event EventHandler  AddEndForCommand;

        event EventHandler  AddLedLeftCommand;
        event EventHandler  AddLedRightCommand;
        event EventHandler  RemoveLedCommand;

        event EventHandler  StartSimulateCommand;
        event EventHandler  PauseSimulateCommand;
        event EventHandler  StopSimulateCommand;
        event EventHandler  ClearAllEffectCommand;
        event EventHandler  MaxBrightEffectCommand;
        event EventHandler  RevertEffectCommand;
        event EventHandler  BlindEffectCommand;
        event EventHandler  FireBallEffectCommand;

        event MouseEventHandler LedNodeMouseWheelCommand;
        event MouseEventHandler LedNodeMouseDoubleClickCommand;
        event SerialDataReceivedEventHandler SerialPort_DataReceived;

        //void SetNode(int newValue);
        int StateCommonInfo { get; set; }
        int Bright { get; set; }
        SendDataDelegate SendData { set; }
        #endregion
    }
}
