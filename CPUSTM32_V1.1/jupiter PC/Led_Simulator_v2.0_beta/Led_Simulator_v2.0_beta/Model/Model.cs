using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.ComponentModel;

namespace Led_Simulator_v2._0_beta
{
    public class LedNodeIndex
    {
        public int stateIndex;
        public int ledIndex;
        public LedNodeIndex(int newStateIndex, int newLedIndex)
        {
            stateIndex = newStateIndex;
            ledIndex = newLedIndex;
        }
        public static bool operator ==(LedNodeIndex firstIndex, LedNodeIndex secondIndex)
        {
            if ((firstIndex.ledIndex == secondIndex.ledIndex) && (firstIndex.stateIndex == secondIndex.stateIndex))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        public static bool operator !=(LedNodeIndex firstIndex, LedNodeIndex secondIndex)
        {
            if ((firstIndex.ledIndex == secondIndex.ledIndex) && (firstIndex.stateIndex == secondIndex.stateIndex))
            {
                return false;
            }
            if ((firstIndex.ledIndex == secondIndex.ledIndex) && (firstIndex.stateIndex == secondIndex.stateIndex))
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        public override bool Equals(object o)
        {
            if (!(o is LedNodeIndex))
            {
                return false;
            }
            return this == (LedNodeIndex)o;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }
    public class Model : IModel
    { 
        private DataLedArrayNode ledData;
        public DataLedArrayNode LedData
        {
            get { return ledData; }
        }

        public ArrayList undoList;
        public ArrayList redoList;
        

        public Model()
        {
            ledData = new DataLedArrayNode(1, 8);
            //CurIndex = new LedNodeIndex(0, 0);
            
            undoList = new ArrayList();
            DataLedArrayNode temp = new DataLedArrayNode(ledData);
            undoList.Insert(0, temp);
            redoList = new ArrayList();
    }

        #region IModel Members

        public event PropertyChangedEventHandler PropertyChanged;

        public int LedNumber 
        {
            get
            {
                return ledData.LedNumber;
            }
        }
        public int StateNumber
        {
            get
            {
                return ledData.StateNumber;
            }
        }

        public Boolean AddStateAbove(int stateIndex)
        {
            if (ledData.InsertState(stateIndex, Constants.StateType.Data))
            {
                AddUndoStep();
                return true;
            }
            return false;
        }

        public Boolean AddStateBelow(int stateIndex)
        {
            if (ledData.InsertState(stateIndex + 1, Constants.StateType.Data))
            {
                AddUndoStep();
                return true;
            }
            return false;
        }

        public Boolean ChangeState(int stateIndex,ArrayList newState)
        {
            if (ledData.ChangeState(stateIndex,newState))
            {
                AddUndoStep();
                return true;
            }
            return false;
        }

        public Boolean RemoveState(int stateIndex)
        {
            if (ledData.RemoveState(stateIndex))
            {
                AddUndoStep();
                return true;
            }
            return false;
        }
        public Boolean AddStartFor(int stateIndex)
        {
            if (ledData.InsertState(stateIndex, Constants.StateType.StartFor))
            {
                AddUndoStep();
                return true;
            }
            return false;
        }

        public Boolean AddEndFor(int stateIndex)
        {
            if (ledData.InsertState(stateIndex, Constants.StateType.Endfor))
            {
                AddUndoStep();
                return true;
            }
            return false;
        }

        public Boolean AddLedLeft(int ledIndex)
        {
            if (ledData.AddLed(ledIndex))
            {
                AddUndoStep();
                return true;
            }
            return false;
        }
        public Boolean AddLedRight(int ledIndex)
        {
            if (ledData.AddLed(ledIndex+1))
            {
                AddUndoStep();
                return true;
            }
            return false;
        }
        public Boolean RemoveLed(int ledIndex)
        {
            if (ledData.RemoveLed(ledIndex))
            {
                AddUndoStep();
                return true;
            }
            return false;
        }

        public int SetBright(LedNodeIndex index, int newBright)
        {
            int updateBright = ledData.SetBright(index.stateIndex, index.ledIndex, newBright);
            return updateBright;
        }
        public int GetBright(LedNodeIndex index)
        {
            int updateBright = ledData.GetBright(index.stateIndex, index.ledIndex);
            return updateBright;
        }
        public int SetStateInfo(int stateIndex,int newValue)
        {
            int updatedStateInfo = ledData.SetCommonValue(stateIndex, newValue);
            return updatedStateInfo;
        }

        public int GetStateInfo(int stateIndex)
        {
            int updatedStateInfo = ledData.GetCommonValue(stateIndex);
            return updatedStateInfo;
        }

        public Constants.StateType GetStateType(int stateIndex)
        {
            Constants.StateType stateType = ledData.GetStateType(stateIndex);
            return stateType;
        }

        public ArrayList GetBrightState(int stateIndex)
        {
            ArrayList brightState = new ArrayList();
            if (ledData.GetStateType(stateIndex) == Constants.StateType.Data)
            {
                brightState = ledData.GetState(stateIndex);
                return brightState;
            }
            else return null;
        }

        public Boolean SaveFile(string fileType, string filePath)
        {
            DataFile.SaveBinFile(ledData, filePath);
            return true;
        }

        public Boolean ReadFile(string fileType, string filePath)
        {
            ledData=DataFile.ReadBinaryFile(filePath);
            AddUndoStep();
            return true;
        }

        public Boolean NewFile()
        {
            ledData = new DataLedArrayNode(1, 8);
            AddUndoStep();
            return true;
        }
        #endregion

        private void AddUndoStep()
        {
            /* 
             * This function is used to add current date led into undoList and clear redoList
             * It's called when led data changed by user
             */
            if (undoList.Count >= Constants.MAX_STEP)
            {
                //Remove the last node of undoList
                undoList.RemoveAt(Constants.MAX_STEP-1);
            }
            //Add current date led at the first undoList
            DataLedArrayNode temp = new DataLedArrayNode(ledData);
            undoList.Insert(0,temp);
            //Clear redoList
            redoList.Clear();
        }
        public Boolean GetUndoStep()
        {
            /*
             * This function is called when run command undo
             * It will move the first node of undoList to redoList and update data led with the new first node of undoList
             */
            if (undoList.Count > 1)
            {
                //Get the first node of undoList
                DataLedArrayNode temp = (DataLedArrayNode)undoList[0];
                //Move first node of undoList to redoList
                redoList.Insert(0,temp);
                //Remove the first node of undoList
                undoList.RemoveAt(0);
                //Update data led
                ledData = new DataLedArrayNode((DataLedArrayNode)undoList[0]);
                return true;
            }
            return false;
        }
        public Boolean GetRedoStep()
        {
            /*
             * This function is called when run command redo
             * It will move the first node of redoList to undoList and update data led with the new first node of redoList
             */
            if (redoList.Count >= 1)
            {
                //Get the first node of undoList
                DataLedArrayNode temp = (DataLedArrayNode)redoList[0];
                //Move first node of undoList to redoList
                undoList.Insert(0,temp);
                //Remove the first node of undoList
                redoList.RemoveAt(0);
                //Update data led
                ledData = new DataLedArrayNode(temp);
                return true;
            }
            return false;
        }

        //private void NotifyChange(string propertyName)
        //{
        //    if (null != PropertyChanged)
        //        PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        //}

        //private void NotifyChange<T>(string propertyName,T value)
        //{
        //    if (null != PropertyChanged)
        //        PropertyChanged(this, new PropertyChangedExtendedEventArgs<T>(propertyName, value));
        //}
    }
}
