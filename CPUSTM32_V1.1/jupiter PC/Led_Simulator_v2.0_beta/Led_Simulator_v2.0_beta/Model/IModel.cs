using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Collections;

namespace Led_Simulator_v2._0_beta
{
    public interface IModel : INotifyPropertyChanged
    {
        DataLedArrayNode LedData { get; }
        int LedNumber { get; }
        int StateNumber { get; }
        Boolean GetRedoStep();
        Boolean GetUndoStep();
        Boolean AddStateAbove(int stateIndex);
        Boolean AddStateBelow(int stateIndex);
        Boolean RemoveState(int stateIndex);
        Boolean AddStartFor(int stateIndex);
        Boolean AddEndFor(int stateIndex);

        Boolean AddLedLeft(int ledIndex);
        Boolean AddLedRight(int ledIndex);
        Boolean RemoveLed(int ledIndex);

        int SetBright(LedNodeIndex index,int newBright);
        int GetBright(LedNodeIndex index);

        int SetStateInfo(int stateIndex, int newValue);
        int GetStateInfo(int stateIndex);
        Constants.StateType GetStateType(int stateIndex);

        ArrayList GetBrightState(int stateIndex);

        Boolean SaveFile(string fileType, string filePath);
        Boolean ReadFile(string fileType, string filePath);
        Boolean NewFile();
    }

    public class PropertyChangedExtendedEventArgs<T> : PropertyChangedEventArgs
    {
        public virtual T NewValue { get; private set; }

        public PropertyChangedExtendedEventArgs(string propertyName, T newValue)
            : base(propertyName)
        {
            NewValue = newValue;
        }
    }
}
